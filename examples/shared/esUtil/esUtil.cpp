#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"

EGLWindow::EGLWindow()
{
    _frames = 0;
    _totaltime = 0.0f;
}

EGLWindow::~EGLWindow()
{
}

GLboolean EGLWindow::esCreateWindow(const char *title, GLint width, GLint height, GLuint flags)
{
    EGLint attribList[] = {
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE};

    _width = width;
    _height = height;

    if (!WinCreate(title))
    {
        return GL_FALSE;
    }

    if (!CreateEGLContext(_hWnd, _eglDisplay, _eglContext, _eglSurface, attribList))
    {
        return GL_FALSE;
    }

    gettimeofday(&_t1, &_tz);

    return GL_TRUE;
}

EGLBoolean EGLWindow::WinCreate(const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    _display = XOpenDisplay(NULL);
    if (_display == NULL)
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(_display);

    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(_display, root, 0, 0, _width, _height, 0, CopyFromParent, InputOutput, CopyFromParent, CWEventMask, &swa);

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes(_display, win, CWOverrideRedirect, &xattr);

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(_display, win, &hints);

    XMapWindow(_display, win);
    XStoreName(_display, win, title);

    wm_state = XInternAtom(_display, "_NET_WM_STATE", FALSE);

    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = FALSE;
    XSendEvent(_display, DefaultRootWindow(_display), FALSE, SubstructureNotifyMask, &xev);

    _hWnd = (EGLNativeWindowType)win;
    return EGL_TRUE;
}

EGLBoolean EGLWindow::CreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay *eglDisplay, EGLContext *eglContext, EGLSurface *eglSurface, EGLint attribList[])
{
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE};

    display = eglGetDisplay((EGLNativeDisplayType)_display);
    if (display == EGL_NO_DISPLAY)
    {
        return EGL_FALSE;
    }

    if (!eglInitialize(display, &majorVersion, &minorVersion))
    {
        return EGL_FALSE;
    }

    if (!eglGetConfigs(display, NULL, 0, &numConfigs))
    {
        return EGL_FALSE;
    }

    if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
    {
        return EGL_FALSE;
    }

    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
    if (surface == EGL_NO_SURFACE)
    {
        return EGL_FALSE;
    }

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT)
    {
        return EGL_FALSE;
    }

    if (!eglMakeCurrent(display, surface, surface, context))
    {
        return EGL_FALSE;
    }

    *eglDisplay = display;
    *eglSurface = surface;
    *eglContext = context;
    return EGL_TRUE;
}

void EGLWindow::esLogMessage(const char *formatStr, ...)
{
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);

    printf("%s", buf);

    va_end(params);
}

GLuint EGLWindow::LoadShader(GLenum type, const char *shaderSrc)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if (shader == 0)
    {
        return 0;
    }

    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char *infoLog = (char *)malloc(sizeof(char) * infoLen);

            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            esLogMessage("Error compiling shader:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint EGLWindow::BuildProgram(GLuint vertexShader, GLuint fragmentShader, const std::vector<const char *> &attributeNames)
{
    GLuint programObject = glCreateProgram();
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    for (int i = 0; i < attributeNames.size(); i++)
    {
        glBindAttribLocation(programObject, i, attributeNames[i]);
    }

    glLinkProgram(programObject);

    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        std::cerr << "Program link error" << std::endl;
        glDeleteProgram(programObject);
        return 0;
    }

    return programObject;
}

void EGLWindow::run()
{
    // while(userInterrupt(esContext) == GL_FALSE)
    {
        gettimeofday(&_t2, &_tz);
        _deltatime = (float)(_t2.tv_sec - _t1.tv_sec + (_t2.tv_usec - _t1.tv_usec) * 1e-6);
        _t1 = _t2;

        update(_deltatime);
        draw();

        eglSwapBuffers(_eglDisplay, _eglSurface);

        _totaltime += _deltatime;
        _frames++;
        if (_totaltime > 2.0f)
        {
            _fps = _frames / _totaltime;
            _totaltime -= 2.0f;
            _frames = 0;
        }
    }
}

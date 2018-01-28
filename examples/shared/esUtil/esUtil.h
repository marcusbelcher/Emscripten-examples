#ifndef ESUTIL_H
#define ESUTIL_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <sys/time.h>
#include <string>
#include <vector>

#define ESUTIL_API
#define ESCALLBACK

#define ES_WINDOW_RGB 0
#define ES_WINDOW_ALPHA 1
#define ES_WINDOW_DEPTH 2
#define ES_WINDOW_STENCIL 4
#define ES_WINDOW_MULTISAMPLE 8

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

class EGLWindow
{
  public:
    EGLWindow();
    virtual ~EGLWindow();
    void run();
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void update(float deltaTime) = 0;
    void esLogMessage(const char *formatStr, ...);

  protected:
    GLboolean esCreateWindow(const char *title, GLint width, GLint height, GLuint flags);
    EGLBoolean WinCreate(const char *title);
    EGLBoolean CreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay *eglDisplay, EGLContext *eglContext, EGLSurface *eglSurface, EGLint attribList[]);
    GLuint LoadShader(GLenum type, const char *shaderSrc);
    GLuint BuildProgram(GLuint vertexShader, GLuint fragmentShader, const std::vector<const char *> &attributeNames);

    Display *_display;
    GLint _width;
    GLint _height;
    EGLNativeWindowType _hWnd;
    EGLDisplay *_eglDisplay;
    EGLContext *_eglContext;
    EGLSurface *_eglSurface;

    struct timeval _t1, _t2;
    struct timezone _tz;
    float _deltatime;
    float _totaltime;
    unsigned int _frames;
    unsigned int _fps;
};

#endif
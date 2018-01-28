#include "App.h"

const GLfloat vertices[] = {
    0.0f, 0.5f, 0.0f, 1.0, 0.0, 0.0,
    -0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
    0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0};

const char vertex[] =
    "attribute vec4 position;                   \n"
    "void main() {                              \n"
    "   gl_Position = position;                 \n"
    "}                                          \n";

const char fragment[] =
    "void main() {                              \n"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}                                          \n";

App::App()
{
    printf("App created\n");
}

void App::init()
{
    _screenWidth = 512;
    _screenHeight = 512;

    std::string windowName = "App window";
    esCreateWindow(windowName.c_str(), _screenWidth, _screenHeight, ES_WINDOW_RGB);

    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertex);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragment);
    _program = BuildProgram(vertexShader, fragmentShader, {"position"});

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    printf("App init\n");
}

void App::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_program);

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    printf("App draw\n");
}

void App::update(float deltaTime)
{
    printf("App update\n");
}
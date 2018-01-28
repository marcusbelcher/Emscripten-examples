#ifndef APP_H
#define APP_H

#include "esUtil.h"
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <time.h>
#include <fstream>

class App : public EGLWindow
{
  public:
    App();
    ~App();
    void init();
    void update(float delta);
    void draw();
    
  private:
    GLuint _program;
    GLuint _buffer;

    int _screenWidth;
    int _screenHeight;
    bool _initialised;
};

#endif
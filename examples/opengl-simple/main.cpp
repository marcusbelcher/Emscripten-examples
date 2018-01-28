#include "App.h"
#include "emscripten.h"
#include "emscripten/bind.h"

App app;

void init()
{
    app.init();
}

void render()
{
    app.draw();
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("init", &init);
    emscripten::function("render", &render);
}

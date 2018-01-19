#include <emscripten/emscripten.h>

// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/embind.html
#include "emscripten/bind.h"
#include <string>

std::string generate(unsigned int terms)
{
    unsigned int t1 = 0, t2 = 1, n = 0;

    terms--;
    std::string output = std::to_string(t1);

    for (int i = t2; i <= terms; ++i)
    {
        n = t1 + t2;
        t1 = t2;
        t2 = n;

        output += ", " + std::to_string(t1);
    }

    return output;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("generate", &generate);
}

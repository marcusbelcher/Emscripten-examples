#include <emscripten/emscripten.h>

// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/embind.html
#define USE_EMBIND
#ifdef USE_EMBIND
#include "emscripten/bind.h"
#include <iostream>
#include <string>

std::string str = "Hello World.";

void printString()
{
    std::cout << str << std::endl;
}

std::string getString()
{
    return str;
}

void setString(std::string s)
{
    str = s;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("printString", &printString);
    emscripten::function("getString", &getString);
    emscripten::function("setString", &setString);
}

#else

// As an alternative to Embind you can use extern "C" 
// https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm
extern "C" {
    #include <stdio.h>

    char HELLO_WORLD[] = "Hello World.";
    char* str = &HELLO_WORLD[0];

    void EMSCRIPTEN_KEEPALIVE printString()
    {
        printf("%s\n", str);
    }

    const char* EMSCRIPTEN_KEEPALIVE getString()
    {
        return &str[0];
    }

    void EMSCRIPTEN_KEEPALIVE setString(char* s)
    {
        str = s;
    }
}

#endif
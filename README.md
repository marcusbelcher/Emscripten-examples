# Emscripten-examples

Examples using Emscripten. The purpose of this repo is to show how to convert simple CPP code to a format which can be executed within a web browser.

## Technologies used

- CPP
- Emscripten
- Python 2.7.\*
- HTML + CSS + JavaScript

## Useful links

- https://caniuse.com/
- https://gist.github.com/paulirish/1579671
- https://webrtc.github.io/samples/

## Setup

- Tested and ran from macOS High Sierra (10.13.2) - Windows will most likely have slash ('\', '/') issues
- Clone this repo to your preferred location, for this example I presume `/Users/<NAME>/code/github/Emscripten-examples/`
- Install emscripten `/Users/<NAME>/code/github/Emscripten-examples/emscripten` http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

## Build

- `cd emscripten`
- `source ./emsdk_env.sh`
- `cd ..`
- `python build_all.py`
- `cd examples`
- `http-server`
- Open up a webpage and view `http://localhost:8080` or `http://127.0.0.1:8080` to view the examples directory
- Make sure you only build within the same terminal you set the source otherwise emscripten will error

## Donate

If you found this useful, and/or this has saved you time/money, please donate to one of the following charities:

- https://www.bhf.org.uk
- https://www.crisis.org.uk/
- https://girlswhocode.com/ and other female STEM initiatives

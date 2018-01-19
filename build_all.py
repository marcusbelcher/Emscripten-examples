
#!/usr/bin/env python

# Author: Marcus Belcher (@marcusbelcher)
# Description: Simple python script which iterates through the examples directory 
# and builds all the examples. If emmake throws an error make sure you have Emscripted
# added to your terminal session path via 'source ./emsdk_env.sh
# Date: 17/01/2018
# License: MIT

import os

for root, directories, filenames in os.walk('./examples'):
    for filename in filenames: 
        if 'makefile' in filename:
            os.chdir(root)
            os.system(r"emmake make clean")
            os.system(r"emmake make all")
            os.chdir('../../')
#!/bin/bash
emcc $@ config.c -o main.js -s ENVIRONMENT=node -s NODERAWFS=1
node main.js
rm -f main.js main.wasm

#!/bin/bash

ctags -R --fields=+l *;
compiledb make;

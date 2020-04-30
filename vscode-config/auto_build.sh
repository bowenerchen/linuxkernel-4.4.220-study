#! /usr/bin/bash

cp ./MAKE_CONFIG .config
make -j8
python3 .vscode/generate_compdb.py
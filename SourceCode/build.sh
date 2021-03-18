#! /bin/bash

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
cp ./config-template ./.config
make -j8
make dtbs

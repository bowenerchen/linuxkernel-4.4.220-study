#! /bin/bash

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
cp ./config-template ./.config
make bzImage -j8 ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
make dtbs -j8

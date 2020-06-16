#! /usr/bin/bash

qemu-system-arm \
-M vexpress-a9 \
-smp 4 \
-m 200M \
-kernel arch/arm/boot/zImage \
-append "rdinit=/linuxrc console=ttyAMA0 loglevel=8" \
-dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
-nographic

#! /usr/bin/bash

rm ./_install/etc -rf
rm ./_install/dev -rf
rm ./_install/mnt -rf

cd ./_install/ && bash init.sh && cd -

# 解决audio驱动错误问题
# 这里随便导入一个audio的驱动模块
export QEMU_AUDIO_DRV=wav

qemu-system-arm \
-M vexpress-a9 \
-smp 2 \
-m 128M \
-kernel arch/arm/boot/zImage \
-append "rdinit=/linuxrc console=ttyAMA0 loglevel=8 slub_debug kmemleak=on" \
-dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
-nographic \
--fsdev local,id=kmod_dev,path=$PWD/kmodules,security_model=none -device virtio-9p-device,fsdev=kmod_dev,mount_tag=kmod_mount 

#-S -s

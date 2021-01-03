#! /bin/bash

mkdir etc
mkdir dev
mkdir mnt
mkdir -p etc/init.d/

cd etc/init.d/
touch rcS
echo "mkdir -p /proc" >> rcS
echo "mkdir -p /tmp" >> rcS
echo "mkdir -p /sys" >> rcS
echo "mkdir -p /mnt" >> rcS
echo "/bin/mount -a" >> rcS
echo "mkdir -p /dev/pts" >> rcS
echo "mount -t devpts devpts /dev/pts" >> rcS
echo "echo /sbin/mdev > /proc/sys/kernel/hotplug" >> rcS
echo "mdev -s" >> rcS
chmod +x rcS

cd ..
touch fstab
echo "proc /proc proc defaults 0 0" >> fstab
echo "tmpfs /tmp tmpfs defaults 0 0" >> fstab
echo "sysfs /sys sysfs defaults 0 0" >> fstab
echo "tmpfs /dev tmpfs defaults 0 0" >> fstab
echo "debugfs /sys/kernel/debug debugfs defaults 0 0" >> fstab

touch inittab
echo "::sysinit:/etc/init.d/rcS" >> inittab
echo "::respawn:-/bin/sh" >> inittab
echo "::askfirst:-/bin/sh" >> inittab
echo "::ctrlaltdel:/bin/umount -a -r" >> inittab

cd ..
cd dev
sudo mknod console c 5 1
sudo mknod null c 1 3


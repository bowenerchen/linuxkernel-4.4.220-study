#! /usr/bin/bash 

sudo grubby --info=ALL | more |grep kernel | grep -v args | grep -v grep

kernel_version=`echo -n $1`

vmlinuz_version="/boot/vmlinuz-$kernel_version*"
initramfs_version="/boot/initramfs-$kernel_version*"
systemmap_version="/boot/System.map-$kernel_version*"
config_version="/boot/config-$kernel_version*"
libmodules_version="/lib/modules/$kernel_version/"

if [ $kernel_version ]
then
    echo "sudo rm $kernel_version $vmlinuz_version $initramfs_version $systemmap_version $config_version $libmodules_version -rf"
fi
echo "sudo grub2-mkconfig -o /boot/grub2/grub.cfg"

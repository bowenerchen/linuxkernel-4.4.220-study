#! /usr/bin/bash 

ALL_KERNEL_VERSIONS=
function get_local_kernel_versions
{
    all_kernel_list=`sudo grubby --info=ALL | more |grep kernel | grep -v args | grep -v grep`
    local index=0
    tmp=`echo "$all_kernel_list" | sed 's/kernel=\/boot\///g'`
    ALL_KERNEL_VERSIONS[$index]="$tmp"
    index=index+1
}

function show_versions
{
     get_local_kernel_versions
     for i in ${ALL_KERNEL_VERSIONS[*]}
     do
         echo -e "\033[32m $i \033[0m"
     done
}

function is_version_exists
{
    get_local_kernel_versions
    for i in ${ALL_KERNEL_VERSIONS[*]}
    do
        if [ "$i" == "$1" ]
        then
            echo -e "\033[31m kernel version $i exists in system \033[0m"
            return 1
        fi
    done
    return 0
}

kernel_version=`echo -n $1`

if [ $kernel_version ]
then
    is_version_exists "$kernel_version"
    exists=`echo $?`
    #echo $exists
    if [ ${exists} -eq 1 ]
    then
        vmlinuz_version="/boot/vmlinuz-$kernel_version*"
        initramfs_version="/boot/initramfs-$kernel_version*"
        systemmap_version="/boot/System.map-$kernel_version*"
        config_version="/boot/config-$kernel_version*"
        libmodules_version="/lib/modules/$kernel_version/"
        echo -e "\033[31m exec commands blew to total clean this kernel version from your system: \033[0m"
        echo -e "\033[32m sudo rm $kernel_version $vmlinuz_version $initramfs_version $systemmap_version $config_version $libmodules_version -rf \033[0m"
        echo -e "\033[32m sudo grub2-mkconfig -o /boot/grub2/grub.cfg \033[0m"
    else 
        echo -e "\033[31m kernel version $kernel_version not exists in this system \033[0m"
    fi
else
    echo -e "\033[31m no kernel version specified, list the kernel version(s) exists this system: \033[0m"
    show_versions
fi

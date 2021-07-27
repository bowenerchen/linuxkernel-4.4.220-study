#! /bin/bash

# echo "$# $@"
if [ $# != 1 ]
then 
    echo "./new_kernel_module_proj.sh proj_name"
    exit
fi

mkdir ./$1;
if [ $? != 0 ]
then
    exit
fi
mkdir ./$1/.vscode

cp ./vscode_project_config/c_cpp_properties.json ./$1/.vscode/ -r
echo "cp ./vscode_project_config/c_cpp_properties.json ./$1/.vscode/ -r"

cp ./vscode_project_config/settings.json ./$1/.vscode/ -r
echo "cp ./vscode_project_config/settings.json ./$1/.vscode/ -r"

cp ./vscode_project_config/Makefile ./$1/ -r
echo "cp ./vscode_project_config/Makefile ./$1/ -r"
sed -i "s/helloworld/$1/g" ./$1/Makefile

cp ./vscode_project_config/helloworld_module.c ./$1/$1_module.c -r
echo "cp ./vscode_project_config/helloworld_module.c ./$1/$1_module.c -r"

echo "--------------------"

echo "create $1 success!"

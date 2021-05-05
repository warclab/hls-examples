#!/bin/bash

git clone --depth 1 --branch 2019.2 https://github.com/Xilinx/Vitis_Libraries.git .vitis_libs || true

# Ubuntu 20.04 Missing Deps
version=$(lsb_release -a | grep Release)

if [[ "${version,,}" == *"20.04"* ]] ;then
    add-apt-repository ppa:linuxuprising/libpng12
    apt update
    apt install -y libpng12-0 libjpeg62
fi

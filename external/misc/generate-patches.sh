#!/bin/bash
export GZ_VERSION=$1

if [ -z $GZ_VERSION ]
then
    echo "You need to specify a version. Ex: generate-patches.sh 1.0"
    exit 1
fi

make clean

# This can be optimized but too lazy atm
export REGION="NTSCU"
make
romhack build --raw --patch
mv ./build/twwgz.patch ./$GZ_VERSION-ntscu.patch
make clean
export REGION="NTSCJ"
make
romhack build --raw --patch
mv ./build/twwgz.patch ./$GZ_VERSION-ntscj.patch
make clean
export REGION="PAL"
make
romhack build --raw --patch
mv ./build/twwgz.patch ./$GZ_VERSION-pal.patch
make clean
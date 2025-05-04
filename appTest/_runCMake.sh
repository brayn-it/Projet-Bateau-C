#!/bin/bash

cmake --version

if [ -z $1 ]; then
	echo Missing Config param
	exit 1
fi

src=$(pwd)
prj=$(basename $src)
cfg=$1
opt=$2
installPath=$src/../runApp

echo $installPath

mkdir -p ../build
mkdir -p ../build/$prj
mkdir -p ../build/$prj/$cfg$opt
mkdir -p $installPath

cd ../build/$prj/$cfg$opt

cmake -DCMAKE_BUILD_TYPE=$cfg -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH="~/Univ/L3/bateau/SFML/share/SFML/cmake/Modules;~/Univ/L3/bateau/libphysics/lib/cmake/libphysics" -DCMAKE_INSTALL_PREFIX=$installPath $src


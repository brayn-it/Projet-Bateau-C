#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../libphysics/Debug

#export LD_LIBRARY_PATH=/home/brayan/Univ/L3/bateau/libphysics/Debug

echo "Running App"
./Debug/bin/apptest

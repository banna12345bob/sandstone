#!/bin/bash


pushd ..
./vendor/bin/premake/premake5_linux gmake
#cat vendor/bin/premake/LICENSE.txt
popd
read -p "Press any key to resume ..."

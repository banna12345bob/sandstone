function PAUSE(){
    read -s -n 1 -p "Press any key to continue . . ."
    echo ""
}

cd $(dirname $0)
pushd ..
./vendor/bin/premake/premake5_macos xcode4
#cat vendor/bin/premake/LICENSE.txt
popd
PAUSE

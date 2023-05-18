#!/bin/bash

BUILD_DIR=build
EXEC=rp-scrabble
INSTALL_DIR=/usr/local/bin
SHARE_DIR=$HOME/.local/share/rp-scrabble

case $1 in
    "ubuntu")
        sudo apt update
        sudo apt install pkgconf build-essential cmake git libglfw3
        ;;

    "arch")
        sudo pacman -S base-devel git cmake pkgconf glfw-x11 --needed
        ;;

    "help")
        echo "Usage: ./install.sh [ arch | ubuntu | help | uninstall ]"
        exit 0
        ;;

    "uninstall")
        echo "Do you wish to uninstall rp-scrabble? (1 = Yes; 2 = No)"
        select yn in "Yes" "No"; do
            case $yn in
                Yes )
                    sudo rm -f --verbose $INSTALL_DIR/$EXEC
                    exit
                    ;;
                No ) exit
                    ;;
            esac
        done
        ;;

    *)
        echo "Invalid arguments"
        echo "Usage: ./install.sh [ arch | ubuntu | help | uninstall ]"
        exit 1
        ;;
esac

mkdir -vp $BUILD_DIR $SHARE_DIR/logs $SHARE_DIR/assets
install -Cv ./assets/layout.ini ./assets/twl06_wordlist.txt -t $SHARE_DIR/assets -m 644

cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Release && make -C $BUILD_DIR -j $(nproc)

sudo install -Cv $BUILD_DIR/$EXEC -t $INSTALL_DIR

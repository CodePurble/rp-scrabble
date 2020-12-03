#!/bin/bash

BUILD_DIR=build
EXEC=rp-scrabble
INSTALL_DIR=$HOME/.local/bin
LOG_DIR=$HOME/.local/share/rp-scrabble/logs
LOG_PARENT_DIR=$HOME/.local/share/rp-scrabble


case $1 in
	"debian")
		if ! meson --version > /dev/null 2>&1; then
			echo "meson not installed, it is required for building from source"
			echo "Installing meson..."
			if ! sudo apt update; then
				echo "Aborting install"
				exit 1
			fi
			if ! sudo apt install meson; then
				exit 1
			fi
		else
			echo "meson is installed"
		fi
		;;

	"arch")
		if ! meson --version > /dev/null 2>&1; then
			echo "meson not installed, it is required for building from source"
			echo "Installing meson..."
			if ! sudo pacman -S meson; then
				echo "Aborting install"
				exit 1
			fi
		else
			echo "meson is installed"
		fi
		;;

	"help")
		echo "Usage: ./install.sh [ arch | debian | help | uninstall | custom ]"
		exit 0
		;;

	"uninstall")
		echo "Uninstalling rp-scrabble..."
		rm -f --verbose $INSTALL_DIR/$EXEC
		rm -rdf --verbose $LOG_PARENT_DIR
		exit 0
		;;

	"custom")
		if ! meson --version > /dev/null 2>&1; then
			echo "meson not installed, it is required for building from source"
			echo "Please install it using your distribution's package manager and rerun this script"
			exit 1
		else
			echo "meson is installed"
		fi
		;;

	*)
		echo "Invalid arguments"
		echo "Usage: ./install.sh [ arch | debian | help | uninstall | custom ]"
		exit 1
		;;
esac


echo "Making build directories..."
if [ ! -d "$BUILD_DIR" ]; then mkdir -vp $BUILD_DIR; fi
if [ ! -d "$INSTALL_DIR" ]; then mkdir -vp $INSTALL_DIR; fi
if [ ! -d "$LOG_DIR" ]; then mkdir -vp $LOG_DIR; fi

echo "Building from source.."
meson --buildtype=release $BUILD_DIR && ninja -C $BUILD_DIR

echo "Installing..."
cp --verbose $BUILD_DIR/$EXEC $INSTALL_DIR
chmod 755 $INSTALL_DIR/$EXEC

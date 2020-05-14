#!/bin/sh

BUILD_DIR=build/
EXEC=rp-scrabble
INSTALL_DIR=$HOME/.local/bin
LOG_DIR=$HOME/.local/rp-scrabble/logs

CMAKE_CHECK=$(cmake --version | grep version)

case $1 in
	"debian")
		if [ "$CMAKE_CHECK" == "" ]; then
			echo "Installing cmake"
			sudo apt update
			sudo apt install cmake
		else
			echo "cmake is installed"
		fi
	;;

	"arch")
		if [ "$CMAKE_CHECK" == "" ]; then
			echo "Installing cmake"
			sudo pacman -S cmake
		else
			echo "cmake is installed"
		fi
	;;

	"help")
		echo "Usage: ./install.sh [ arch | debian | help | uninstall | custom ]"
		exit 0
	;;

	"uninstall")
		echo "Uninstalling rp-scrabble..."
		rm -f --verbose $INSTALL_DIR/$EXEC
		rm -rdf --verbose $LOG_DIR
		exit 0
	;;

	"custom")
		if [ "$CMAKE_CHECK" == "" ]; then
			echo "cmake is not installed. Please install it using your distribution's package manager and rerun this script"
			exit 1
		else
			echo "cmake is installed"
		fi
	;;

	*)
		echo "Invalid arguments"
		echo "Usage: ./install.sh [ arch | debian | help | uninstall | custom ]"
		exit 1
	;;
esac


echo "Making build directories..."
if [ ! -d "$BUILD_DIR" ]; then mkdir -p $BUILD_DIR; fi
if [ ! -d "$LOG_DIR" ]; then mkdir -p $LOG_DIR; fi

cd $BUILD_DIR

echo "Building from source.."
cmake -DCMAKE_BUILD_TYPE=Release .. && make

echo "Installing..."
cp --verbose $EXEC $INSTALL_DIR
chmod 755 $INSTALL_DIR/$EXEC

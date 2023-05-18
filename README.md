# rp-scrabble
This is a full GUI variant of the Scrabble game written in C++ to explore object oriented
programming. The UI is written using the help of the absolutely amazing
[Dear ImGui](https://github.com/ocornut/imgui) library.

## Build requirements
It is required that you have some kind of **Linux** environment available.
The build dependencies are:

* `cmake`
* `git`
* `make`
* `g++`
* `pkgconf`
* [GLFW](https://www.glfw.org/)

An [install
script](https://github.com/CodePurble/rp-scrabble/blob/imgui/install.sh) is
provided. It takes care of getting the dependencies for Ubuntu (should also
work with any other distro that uses the `apt` package manager, not tested) and Arch Linux (should also
work with any other distro that uses the `pacman` package manager, not tested)

If you aren't on any of these distributions, you will need to get the
dependencies yourself, before attempting to build this project.

## Build instructions
* Clone this repo
```sh
git clone -b imgui https://github.com/CodePurble/rp-scrabble.git
```

* Move into project directory
```sh
cd rp-scrabble
```

* Build and install (you can update `INSTALL_DIR` to any path you like)
```sh
BUILD_DIR=build
EXEC=rp-scrabble
INSTALL_DIR=/usr/local/bin
SHARE_DIR=$HOME/.local/share/rp-scrabble
mkdir -p $BUILD_DIR $SHARE_DIR/logs $SHARE_DIR/assets
cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Release && make -C $BUILD_DIR -j $(nproc)
install -C ./assets/layout.ini ./assets/twl06_wordlist.txt -t $SHARE_DIR/assets -m 644
sudo install -C $BUILD_DIR/$EXEC -t $INSTALL_DIR
```
* Now, simply running `rp-scrabble` should launch the game (provided `INSTALL_DIR` is in your `PATH`).
* If it doesn't launch, check the output of `$ echo $PATH`. If it does not
  contain `INSTALL_DIR`, add it to your `PATH` like this-
```sh
# You can replace $HOME/.bashrc with whatever shellrc you use
echo 'export PATH=$PATH:$INSTALL_DIR' >> $HOME/.bashrc
source $HOME/.bashrc
```

## Development
Once you have all the dependencies, build using the "Debug" build type:

```sh
mkdir build logs
cmake -B build -DCMAKE_BUILD_TYPE=Debug && make -C build -j $(nproc)
```

* The binary will be present in `build/`
* Log files will be written to `logs/`

## Other notes
* You can find the documentation for this project [here](https://codepurble.github.io/rp-scrabble/)
* Keep the repo up to date by running `git pull` every once in a while in the
  project directory, and re-running the install script.
* Log files are stored in `$HOME/.local/share/rp-scrabble/logs`
* To uninstall, run the install script with the `uninstall` argument in the project directory
```sh
$ ./install.sh uninstall
```
* If you find any problems, please open up an issue

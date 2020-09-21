# rp-scrabble
This is a command-line Scrabble game written in C++ to explore object oriented
programming.

# NOTICE for users of `v1.0`
* Users of `v1.0` **MUST** re-install the application, as the update to `v1.1` or higher contains breaking changes
* All future updates will conform to these changes

## Build requirements
It is required that you have some kind of **Linux** environment available. If you
are not on a Linux machine, either use a VM or, if you are on Windows, [set up
WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

The build dependencies are:

* `cmake`
* `git`
* `ninja`
* `g++`

To install them, run-

```sh
# For Arch and Arch-based distributions (Manjaro, Artix, etc)
$ sudo pacman -S cmake git gcc make

# For Debian and Debian-based distributions (Ubuntu, Pop_OS, etc)
$ sudo apt update && sudo apt install cmake git make g++
```

## Build instructions
* Clone this repo
```sh
$ git clone https://github.com/CodePurble/rp-scrabble.git
```

* Move into project directory
```sh
$ cd rp-scrabble
```

* Build

Run the install script with the appropriate argument-
```sh
$ ./install.sh arch # for Arch and Arch-based distributions (Manjaro, Artix, etc)
$ ./install.sh debian # for Debian and Debian-based distributions (Ubuntu, Pop_OS, etc)
$ ./install.sh custom # for other distributions
```
* Now, simply running `rp-scrabble` should launch the game.
* If it doesn't launch, check the output of `$ echo $PATH`. If it does not contain `your-home-dir/.local/bin`, add it to your `PATH` like this-
```sh
# You can replace $HOME/.bashrc with whatever shellrc you use
$ echo 'export PATH=$PATH:$HOME/.local/bin' >> $HOME/.bashrc
$ source $HOME/.bashrc
```

## Other notes
* You can find the documentation for this project [here](https://codepurble.github.io/rp-scrabble/)
* Keep the repo up to date by running `git pull` every once in a while in the project directory. Remember to rerun the install script after pulling to bring any changes into effect.
* Log files are stored in `$HOME/.local/share/rp-scrabble/logs`
* To uninstall, run the install script with the `uninstall` argument in the project directory
	```sh
	$ ./install.sh uninstall
	```
**NOTE** This will also remove any log files created
* If you find any problems, please open up an issue

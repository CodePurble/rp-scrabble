# scrabble
This is a command-line Scrabble game written in C++ to explore object oriented
programming.

## Build requirements
* `git`
* `make`
* `g++`

## Build instructions
* Clone this repo
	```sh
	$ git clone https://github.com/CodePurble/scrabble.git
	```

* Move into project directory
	```sh
	$ cd scrabble
	```

* Build
	```sh
	$ make && make install
	```
* Now, simply running `rp-scrabble` should launch the game.
* If it doesn't launch, check the output of `$ echo $PATH`. If it does not contain `your-home-dir/.local/bin`, add it to your `PATH` like this-
	```sh
	$ echo "export PATH=$PATH:$HOME/.local/bin" >> $HOME/.bashrc
	$ source $HOME/.bashrc
	```

## Other notes
* Keep the repo up to date by running `git pull` every once in a while in the project directory
* Log files are stored in
	```sh
	$HOME/.local/share/rp-scrabble/logs
	```
* To uninstall, run this command in the project directory
	```sh
	$ make uninstall
	```
	**NOTE** This will also remove any log files created


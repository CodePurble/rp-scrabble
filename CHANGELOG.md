# Changelog

## Version 1.0
* Basic playable version

#### Features
* Allows 1-4 players
* Player can place tiles on the board
* Player scores are calculated
* Tile placement validation
* Logging of games

## Version 1.1

#### Breaking Changes
* The build system has been changed to Cmake

#### Bug fixes
* Premium squares are applied only if tiles from the current play are placed on them
* Players prompted only if their racks are not empty, avoiding unplayable game state
* Infinite game loop fixed

#### Feature updates
* Perform input validation
* Show details of currently made play
* Play confirmation
* Added option to quit the game

#### Minor changes
* Remove lingering debug messages
* Correct board layout

## Version 1.1.1

#### Feature updates
* Added commands to show scores and skip turn
* Updated help text

#### Minor changes
* Cleaned up player prompt

## Version 1.1.4

#### Changelog
* Added Doxygen documentation


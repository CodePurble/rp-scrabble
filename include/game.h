/**
  * @file
  */
#ifndef GAME_H
#define GAME_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <vector>
#include <array>
#include <string>
#include "utils.h"

class Board;
class Bag;
class Player;
class Play;
class Logger;
class Dict;

/**
 * Implements the main game logic, UI, logging and other functionalities
 */
class Game {
private:
    FontCollection_t *gameFonts;
    bool game_started = false;
    Board* gameBoard;
    Bag* gameBag;
    Dict *gameDictionary;
    GLFWwindow *main_window;
    std::vector<Player*> players;
    Player *currPlayer;
    std::vector<Play*> plays;
    Play *currPlay;
    int turnCount;
    std::array<std::string, PLAYER_MAX> player_names;
    std::string gameID;
    std::string logFilePath;
    Logger *gameLogger;
    void init();
    bool firstTurnCheck(std::string str, int r, int c, char dir);
    void addPlayer(Player* p);
    std::string getInput(char *textbox_text);
    void undoPlay(std::vector<Tile*> tileStrVec, std::vector<Tile*> drawnTiles, int total_players, int *player_index);
    void undoPlay(std::vector<Tile*> tileStrVec);

public:
    Game(GLFWwindow *window, FontCollection_t *fonts);
    ~Game();

    int run();

};

#endif

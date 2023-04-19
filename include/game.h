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

/**
 * Implements the main game loop, logging and other functionalities
 */
class Game {
private:
    bool game_started = false;
    Board* gameBoard;
    Bag* gameBag;
    GLFWwindow *main_window;
    std::vector<Player*> players;
    std::vector<Play*> plays;
    std::array<std::string, PLAYER_MAX> player_names = {"", "", "", ""};
    std::string gameID;
    std::string logFilePath;
    void init();
    bool firstTurnCheck(std::string str, int r, int c, char dir);
    void addPlayer(Player* p);
    PlayerInput_t getInput(char *textbox_text);
    void printHelp();

public:
    Game(GLFWwindow *window);
    ~Game();

    int run();

};

#endif

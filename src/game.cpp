/**
  * @file
  */
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "game.h"
#include "bag.h"
#include "board.h"
#include "player.h"
#include "utils.h"
#include "play.h"
#include "tile.h"
#include "logger.h"

using namespace std;

/**
  * Initialise all data required for a Game, including log-files, gameID
  */
Game::Game(GLFWwindow *window)
{
    char filenameBuffer[60];
    time_t rawTime;
    time(&rawTime);
    strftime(filenameBuffer, 60, "-%F-scrabble.log", localtime(&rawTime));
    gameID = RawTimeToString(rawTime);
    logFilePath = LOG_PATH + gameID + string(filenameBuffer);

    // DEBUG_PRINT(" logFilePath", logFilePath);
    // cout << endl;

    main_window = window;
    gameBoard = new Board;
    gameBag = new Bag;
    logger = new Logger;
}

/**
  * Clean up game data
  */
Game::~Game()
{
    if(gameBag) {
        delete gameBag;
    }

    if(gameBoard) {
        delete gameBoard;
    }

    for(Player* p : players) {
        if(p) {
            delete p;
        }
    }
}

/**
 * Add a Player to the Game
 *
 * @param p Pointer to the new Player
 *
 * This function shall not throw exceptions.
 */
void Game::addPlayer(Player* p)
{
    if(p) {
        players.push_back(p);
    }
}

/**
 * Initialise and set up the game
 */
void Game::init()
{
    try {
        log(logFilePath, "Log start\n");
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }

    ImGui::Begin("Welcome");
    ImGui::TextWrapped("Welcome to Scrabble by Ramprakash!");
    static int start_pressed;
    static int player_count = 1;
    static int next_clicked = 0;
    static char hint[8] = "Player ";
    static char name[16] = "";
    if (ImGui::Button("Start")) {
        if(start_pressed == 0) {
            ++start_pressed;
        }
    }
    if(start_pressed == 1) {
        ImGui::BeginDisabled(game_started);
        // Draw UI elements
        ImGui::OpenPopup("Player details");
        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal("Player details", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            if(next_clicked == 0) {
                ImGui::InputInt("Number of players", &player_count);
                if(player_count > 4) {
                    ImGui::Text("Only upto 4 players allowed!");
                }
                else if (ImGui::Button("Next", ImVec2(120, 0))) {
                    ++next_clicked;
                }
            }
            else {
                hint[7] = '0' + next_clicked;
                ImGui::InputTextWithHint(
                    "##",
                    hint,
                    name,
                    IM_ARRAYSIZE(name)
                );
                if (ImGui::Button("Back", ImVec2(120, 0))) {
                    if(next_clicked != 0) {
                        --next_clicked;
                    }
                }
                ImGui::SameLine();
                if(next_clicked < player_count) {
                    if (ImGui::Button("Next", ImVec2(120, 0))) {
                        player_names[next_clicked - 1] = name;
                        ++next_clicked;
                        for(int i = 0; i < 16; ++i) {
                            name[i] = '\0';
                        }
                    }
                }
                else if(next_clicked == player_count) {
                    if(ImGui::Button("Play", ImVec2(120, 0))) {
                        player_names[next_clicked - 1] = name;
                        game_started = true;
                    }
                }
            }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
                start_pressed = 0;
                next_clicked = 0;
            }
            ImGui::EndPopup();
        }
        ImGui::EndDisabled();
    }
    ImGui::End();
}

/**
 * Check whether the first play is valid
 *
 * @param tileStr String of letters that represent the Tiles to be placed
 * @param r Row where the first Tile goes
 * @param c Column where first tile goes
 * @param dir Direction of placement
 *
 * @return true if valid, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Game::firstTurnCheck(string tileStr, int row, int col, char dir)
{
    if(dir == 'h') {
        for(unsigned long j = col; j < col + tileStr.length(); j++) {
            if(j == 7 && row == 7) {
                return true;
            }
        }
    }
    else if(dir == 'v') {
        for(unsigned long i = row; i < row + tileStr.length(); i++) {
            if(i == 7 && col == 7) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Used to take user input
 *
 * @return User input as a std::string
 *
 * @throws std::invalid_argument For integer inputs
 * @throws std::string containing the error message for other inputs
 */
PlayerInput_t Game::getInput(char *textbox_text)
{
    int comma_count = 0;
    std::string temp = "";
    PlayerInput_t player_inputs;
    player_inputs.raw = textbox_text;
    for(char ch : player_inputs.raw) {
        if(ch == ',') {
            temp = "";
            comma_count++;
            continue;
        }
        else {
            temp += ch;
            switch(comma_count) {
            case 0:
                player_inputs.tiles = temp;
                break;
            case 1:
                try {
                    player_inputs.row = stoi(temp);
                }
                catch(const std::invalid_argument &ia) {
                    throw(string("Invalid integer input for row\n"));
                }
                break;
            case 2:
                try {
                    player_inputs.col = stoi(temp);
                }
                catch(const std::invalid_argument &ia) {
                    throw(string("Invalid integer input for column\n"));
                }
                break;
            default:
                player_inputs.dir = temp[0];
                break;
            }
        }
    }

    return player_inputs;
}

/**
 * Print help information
 *
 * This function shall not throw exceptions.
 */
void Game::printHelp()
{
    PALE_GREEN_FG("\n The tiles you want to place are entered in order of placement using the respective letter\n\n");
    PALE_GREEN_FG(" The row and column of the square to place can be seen outside the edge of the board\n\n");
    PALE_GREEN_FG(" The placement direction can either be 'v' (place tiles vertically downward one after the other) or\n");
    PALE_GREEN_FG(" 'h' (place tiles horizontally from left to right one after the other)\n\n");

    BOLD(" Commands\n");
    BOLD(" --------\n");

    BOLD_BRIGHT_GREEN_FG(" ? ");
    cout << "Show this help text\t";
    BOLD_BRIGHT_GREEN_FG(" . ");
    cout << "Show the board\t";
    BOLD_BRIGHT_GREEN_FG(" ! ");
    cout << "Skip turn\n";
    BOLD_BRIGHT_GREEN_FG(" # ");
    cout << "Show scores\t\t";
    BOLD_BRIGHT_GREEN_FG(" - ");
    cout << "Quit the game\n\n";

    BOLD(" Board legend\n");
    BOLD(" ------------\n");

    cout << " ";
    RED_BG("   ");
    cout << " Triple Word Score\t";

    cout << " ";
    PINK_BG("   ");
    cout << " Double Word Score\t";

    cout << " ";
    DARK_BLUE_BG("   ");
    cout << " Triple Letter Score\t";

    cout << " ";
    LIGHT_BLUE_BG("   ");
    cout << " Double Letter Score\n\n";
}

/**
 * Main game logic. Contains main game loop
 *
 * This function shall not throw exceptions.
 */
int Game::run()
{
    int row, col;
    bool endTurn;
    bool allEmpty = false;
    bool playValid;
    bool firstTurn = true;
    string tileStr;
    PlayerInput_t in;
    string tempIn = "";
    char dir;
    static char textbox_text[128] = "";
    int display_w, display_h;
    Player *currPlayer = nullptr;
    int player_index = 0;
    bool confirm_status = false;
    bool players_added = false;
    int root_window_flags = 0;
    root_window_flags |= ImGuiWindowFlags_NoDecoration;
    root_window_flags |= ImGuiWindowFlags_NoResize;

    try {
        log(logFilePath, "\nGame start\n");
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }


    // Our state
    while (!glfwWindowShouldClose(main_window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Draw UI elements
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::Begin("RP Scrabble", nullptr, root_window_flags);
        ImGui::End();
        if (game_started) {
            if(firstTurn) {
                if(players_added) {
                    currPlayer = players.front();
                }
                else {
                    for(int i = 0; i < PLAYER_MAX; ++i) {
                        if(player_names[i] != "") {
                            addPlayer(new Player(player_names[i]));
                        }
                    }
                    for(Player *p : players) {
                        p->draw(7, gameBag);
                    }
                    players_added = true;
                }
            }
            ImGui::Begin("Input Box");
            ImGui::InputTextWithHint(
                "##",
                "Input your play",
                textbox_text,
                IM_ARRAYSIZE(textbox_text)
            );
            ImGui::SameLine();
            ImGui::HelpMarker(
                "The play is input in the following format:\nletters,row,column,direction\n---\n\n* 'letters' are the letters you want to place (in the order you want to place)\n\n* 'row' and 'column' are the respective row index and column index of the square where you want to place the first tile (The indices of the rows and columns are shown along the edges of the board)\n\n* 'direction' is the direction in which you want to place your tiles (valid values are 'h' or 'v')"
            );
            confirm_status = (ImGui::Button("Confirm Play"));
            ImGui::End();
            gameBoard->show();
            for(Player* pl : players) {
                pl->show();
            }
            logger->show("Logger");
        }
        else {
            init();
        }
        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(main_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(main_window);


        // Main game loop
        if (currPlayer){
            if(!allEmpty) {
                if(!currPlayer->rackIsEmpty()) {
                    plays.push_back(new Play(currPlayer));
                    Play* currPlay = plays.back();
                    row = col = 7;
                    endTurn = false;
                    tileStr = "";

                    // BOLD(" Bag: ");
                    // gameBag->show();
                    // cout << "\n";

                    if(!endTurn) {
                        try {
                            currPlayer = players[player_index];
                            currPlayer->setTurn(true); // Turn begins
                            if(confirm_status) {
                                in = getInput(textbox_text);
                                // Clear out the textbox after capturing input
                                for(int i = 0; i < IM_ARRAYSIZE(textbox_text); ++i) {
                                    textbox_text[i] = '\0';
                                }
                                vector<vector<Tile*>> connnectedWords;
                                vector<Tile*> tileStrVec;

                                try {
                                    log(logFilePath, in.raw);
                                }
                                catch(string err) {
                                    BOLD_RED_FG(" " + err);
                                    BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
                                    BOLD_RED_FG(" Aborting\n");
                                    exit(1);
                                }

                                tileStr = in.tiles;
                                row = in.row;
                                col = in.col;
                                dir = in.dir;
                                playValid = currPlay->validate(tileStr, gameBoard, row, col, dir);

                                // override playValid only for first turn
                                if(firstTurn) {
                                    if(!firstTurnCheck(tileStr, row, col, dir)) {
                                        firstTurn = true;
                                        playValid = false;
                                        logger->addLog("This is the first turn of the game, please make sure the centre square is covered by your word\n");
                                        BOLD_RED_FG(" This is the first turn of the game, please make sure the centre square is covered by your word\n");
                                    }
                                    else {
                                        playValid = true;
                                        firstTurn = false;
                                    }
                                }

                                if(playValid) {
                                    tileStrVec = currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
                                    connnectedWords = currPlay->getWords(tileStrVec, gameBoard, row, col, dir);
                                    currPlay->calculatePoints(connnectedWords, tileStrVec);
                                    currPlayer->updateScore(currPlay->getPointsMade());
                                    currPlayer->draw(tileStr.length(), gameBag);
                                    currPlayer->setTurn(false);
                                    ++player_index;
                                    if(player_index >= players.size()) {
                                        player_index = 0;
                                    }
                                    currPlay->show();
                                    currPlay->log(logger);
                                    endTurn = !endTurn; // Turn ends
                                }
                                else {
                                    currPlay->reset();
                                    clearPlayerInput(&in);
                                    logger->addLog("Invalid play\n");
                                    BOLD_RED_FG(" Invalid play\n");
                                }
                            }
                        }
                        catch(string ex) {
                            logger->addLog("Error: %s", ex.c_str());
                            BOLD_RED_FG(" Error: " + ex);
                        }
                    }
                }
                // Find out whether all racks are empty
                allEmpty = players.front()->rackIsEmpty();
                for(Player* p : players) {
                    allEmpty = allEmpty && p->rackIsEmpty();
                }
            }
            else {
                logger->addLog("\n\n------------------------------\nYou have placed all tiles!!! Final scores are-\n");
                BOLD(" You have placed all tiles!!! Final scores are-\n");
                for(Player* p : players) {
                    log(logFilePath, "\n");
                    log(logFilePath, p->getName() + ": " + to_string(p->getScore()) + "\n");
                    logger->addLog("%s: %d", p->getName().c_str(), p->getScore());
                    BOLD_WHITE_FG(p->getName() + ": " + to_string(p->getScore()) + "\n");
                }
            }
        }
    }


    return 0;
}

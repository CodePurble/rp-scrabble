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
#include "dict.h"

using namespace std;

/**
  * Initialise all data required for a Game, including log-files, gameID
  */
Game::Game(GLFWwindow *window, FontCollection_t *fonts)
{
    char filenameBuffer[60];
    time_t rawTime;
    time(&rawTime);
    strftime(filenameBuffer, 60, "-%F-scrabble.log", localtime(&rawTime));
    gameID = RawTimeToString(rawTime);
    logFilePath = LOG_PATH + gameID + string(filenameBuffer);
    gameFonts = fonts;
    main_window = window;
    gameBoard = new Board;
    gameBag = new Bag;
    gameDictionary = new Dict("/home/ramprakash/repos/rp-scrabble/assets/twl06_wordlist.txt");
    gameLogger = new Logger;
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
    int window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    try {
        log(logFilePath, "Log start\n");
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    // Always center this window when appearing
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    {
        ImGui::Begin("Welcome", nullptr, window_flags);
        ImGui::PushFont(gameFonts->title);
        ImGui::TextWrapped(" Welcome to Scrabble by Ramprakash!");
        ImGui::PopFont();
        static int start_pressed;
        static int player_count = 1;
        static int next_clicked = 0;
        static char hint[9] = "Player ";
        static char name[16] = "";
        ImGui::PushFont(gameFonts->bold);
        if (ImGui::Button("Start", ImVec2(ImGui::GetWindowSize().x - 15, 0))) {
            if(start_pressed == 0) {
                ++start_pressed;
            }
        }
        ImGui::PopFont();
        if(start_pressed == 1) {
            ImGui::BeginDisabled(game_started);
            // Draw UI elements
            ImGui::OpenPopup("Player details");
            // Always center this window when appearing
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            if(ImGui::BeginPopupModal("Player details", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                if(next_clicked == 0) {
                    ImGui::InputInt("Number of players", &player_count);
                    // if(player_count > 4) {
                    //     ImGui::Text("Only upto 4 players allowed!");
                    // }
                    // else if (ImGui::Button("Next", ImVec2(120, 0))) {
                    //     ++next_clicked;
                    // }
                    if(player_count < 1) {
                        player_count = 1;
                    }
                    if (ImGui::Button("Next", ImVec2(120, 0))) {
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
std::string Game::getInput(char *textbox_text)
{
    std::string text = "";
    text = textbox_text;
    return text;
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
    bool placementCheck = false;
    string firstIllegalWord = "";
    int turnCount = 0;
    string tileStr;
    string tempIn = "";
    char dir;
    static char textbox_text[128] = "";
    int display_w, display_h;
    Player *currPlayer = nullptr;
    int player_index = 0;
    bool players_added = false;
    bool endGame = false;
    bool skipTurn = false;
    static int directionSelected = 0; // 0 == horizontal; 1 == vertical
    int rootWindowFlags = 0;
    rootWindowFlags |= ImGuiWindowFlags_NoDecoration;
    rootWindowFlags |= ImGuiWindowFlags_NoResize;

    int childWindowFlags = ImGuiWindowFlags_None;
    childWindowFlags |= ImGuiWindowFlags_NoCollapse;

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
        ImGui::Begin("RP Scrabble", nullptr, rootWindowFlags);
        ImGui::End();
        if (game_started) {
            if(turnCount == 0) {
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
            gameBoard->show("Board", childWindowFlags, gameFonts);
            for(Player* p : players) {
                p->show("Player racks", childWindowFlags, gameFonts);
            }
            gameLogger->show("Logger", nullptr, childWindowFlags);
            {
                ImGui::Begin("Input Box", nullptr, childWindowFlags);
                if(gameBoard->getSquareClicked() || skipTurn) {
                    ImGui::SetKeyboardFocusHere();
                }
                ImGui::InputTextWithHint(
                    "##",
                    "Input your play",
                    textbox_text,
                    IM_ARRAYSIZE(textbox_text)
                );
                ImGui::SameLine();
                ImGui::HelpMarker(
                    "To make a play, follow the below steps:\n\n*Type in the letters that you want to place in the text-box (in the order you want to place them)\n* Select the direction you want to place the tiles in\n* Click the square on the board where you want to place the first tile"
                );
                ImGui::RadioButton("Horizontal", &directionSelected, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Vertical", &directionSelected, 1);
                ImGui::Text("Tiles remaining in the bag: ");
                ImGui::SameLine();
                ImGui::Text(to_string(gameBag->remainingTiles()).c_str());
                ImGui::End();
            }

            {
                ImGui::Begin("##", nullptr, childWindowFlags);
                endGame = ImGui::Button("End game");
                ImGui::SameLine();
                skipTurn = ImGui::Button("Skip turn");
                ImGui::End();
            }
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


        // Main game logic
        if (currPlayer){
            if(!allEmpty) {
                if(!currPlayer->rackIsEmpty()) {
                    plays.push_back(new Play(currPlayer));
                    Play* currPlay = plays.back();
                    row = col = 7;
                    endTurn = false;
                    tileStr = "";

                    if(!endTurn) {
                        try {
                            currPlayer = players[player_index];
                            currPlayer->setTurn(true); // Turn begins
                            if(skipTurn) {
                                currPlayer->setTurn(false);
                                ++player_index;
                                if(turnCount > 0) {
                                    ++turnCount;
                                }
                                if(player_index >= players.size()) {
                                    player_index = 0;
                                }
                                endTurn = !endTurn; // Turn ends
                            }
                            if(gameBoard->getSquareClicked()) {
                                tileStr = getInput(textbox_text);
                                row = gameBoard->getClickedSquare_x();
                                col = gameBoard->getClickedSquare_y();
                                if(directionSelected == 0) {
                                    dir = 'h';
                                }
                                else if(directionSelected == 1) {
                                    dir = 'v';
                                }
                                // Clear out the textbox after capturing input
                                for(int i = 0; i < IM_ARRAYSIZE(textbox_text); ++i) {
                                    textbox_text[i] = '\0';
                                }
                                vector<vector<Tile*>> connnectedWords;
                                vector<Tile*> tileStrVec;

                                try {
                                    log(logFilePath, tileStr + "," + to_string(row) + "," + to_string(col) + dir);
                                }
                                catch(string err) {
                                    BOLD_RED_FG(" " + err);
                                    BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
                                    BOLD_RED_FG(" Aborting\n");
                                    exit(1);
                                }

                                placementCheck = currPlay->checkPlacement(tileStr, gameBoard, row, col, dir);

                                // override playValid only for first turn
                                if(turnCount == 0) {
                                    if(!firstTurnCheck(tileStr, row, col, dir)) {
                                        turnCount = 0;
                                        placementCheck = false;
                                        gameLogger->addLog("This is the first turn of the game, please make sure the centre square is covered by your word\n");
                                        BOLD_RED_FG(" This is the first turn of the game, please make sure the centre square is covered by your word\n");
                                    }
                                    else {
                                        placementCheck = true;
                                    }
                                }

                                if(placementCheck) {
                                    tileStrVec = currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
                                    connnectedWords = currPlay->getWords(tileStrVec, gameBoard, row, col, dir);
                                    firstIllegalWord = currPlay->checkWords(gameDictionary);
                                    if(firstIllegalWord == "") {
                                        currPlay->calculatePoints(connnectedWords, tileStrVec);
                                        currPlayer->updateScore(currPlay->getPointsMade());
                                        currPlayer->draw(tileStr.length(), gameBag);
                                        currPlayer->setTurn(false);
                                        ++player_index;
                                        ++turnCount;
                                        if(player_index >= players.size()) {
                                            player_index = 0;
                                        }
                                        currPlay->show();
                                        currPlay->log(gameLogger);
                                        endTurn = !endTurn; // Turn ends
                                    }
                                    else {
                                        if(turnCount == 1) {
                                            turnCount = 0;
                                        }
                                        for(Tile* t : tileStrVec) {
                                            currPlayer->returnToRack(t, gameBoard);
                                        }
                                        currPlay->reset();
                                        tileStr.clear();
                                        row = 0;
                                        col = 0;
                                        gameLogger->addLog("Invalid word: %s\n", firstIllegalWord.c_str());
                                        BOLD_RED_FG(" Invalid word: " + firstIllegalWord + "\n");
                                        firstIllegalWord.clear();
                                    }
                                }
                                else {
                                    for(Tile* t : tileStrVec) {
                                        currPlayer->returnToRack(t, gameBoard);
                                    }
                                    currPlay->reset();
                                    tileStr.clear();
                                    row = 0;
                                    col = 0;
                                    gameLogger->addLog("Invalid tile placement, at least one of your tiles should touch an existing tile\n");
                                    firstIllegalWord.clear();
                                    BOLD_RED_FG("Invalid tile placement, at least one of your tiles should touch an existing tile\n");
                                }
                            }
                        }
                        catch(string ex) {
                            gameLogger->addLog("Error: %s", ex.c_str());
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
                gameLogger->addLog("\n\n------------------------------\nYou have placed all tiles!!! Final scores are-\n");
                BOLD(" You have placed all tiles, in " + to_string(turnCount + 1) + " turns! Final scores are-\n");
                for(Player* p : players) {
                    log(logFilePath, "\n");
                    log(logFilePath, p->getName() + ": " + to_string(p->getScore()) + "\n");
                    gameLogger->addLog("%s: %d", p->getName().c_str(), p->getScore());
                    BOLD_WHITE_FG(p->getName() + ": " + to_string(p->getScore()) + "\n");
                }
            }
        }
    }


    return 0;
}

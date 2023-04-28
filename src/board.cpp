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
#include <cstring>
#include "player.h"
#include "board.h"
#include "tile.h"
#include "rack.h"
#include "utils.h"

using namespace std;

/**
 * Board constructor.
 * Fills the 2D board matrix with pointers to Square objects of approproate type. Symmetry of the
 * board is used to easily construct the board. It is done in 2 steps- four square portions and then
 * the 4 strips
 */
Board::Board()
{
    enum_sqType quarterBoard[7][7] = {
        { TWS, N, N, DLS, N, N, N   },
        { N, DWS, N, N, N, TLS, N   },
        { N, N, DWS, N, N, N, DLS },
        { DLS, N, N, DWS, N, N, N   },
        { N, N, N, N, DWS, N, N   },
        { N, TLS, N, N, N, TLS, N   },
        { N, N, DLS, N, N, N, DLS }
    };

    enum_sqType strip[7] = {TWS, N, N, DLS, N, N, N};

    // Top Left quarter
    for(int i = 0; i < NUM_ROWS/2; i++) {
        for(int j = 0; j < NUM_COLS/2; j++) {
            board[i][j] = new Square(quarterBoard[i][j], i, j);
        }
    }

    // Top Right quarter
    for(int i = 0; i < NUM_ROWS/2; i++) {
        for(int j = 0; j < NUM_COLS/2; j++) {
            int j2 = NUM_COLS - 1 - j;
            board[i][j2] = new Square(quarterBoard[i][j], i, j2);
        }
    }

    // Bottom Left quarter
    for(int i = 0; i < NUM_ROWS/2; i++) {
        for(int j = 0; j < NUM_COLS/2; j++) {
            int i2 = NUM_ROWS - 1 - i;
            board[i2][j] = new Square(quarterBoard[i][j], i2, j);
        }
    }

    // Bottom Right quarter
    for(int i = 0; i < NUM_ROWS/2; i++) {
        for(int j = 0; j < NUM_COLS/2; j++) {
            int i2 = NUM_ROWS - 1 - i;
            int j2 = NUM_COLS - 1 - j;
            board[i2][j2] = new Square(quarterBoard[i][j], i2, j2);
        }
    }

    // Horizontal strips
    for(int j = 0; j < NUM_COLS/2; j++) {
        board[NUM_ROWS/2][j] = new Square(strip[j], NUM_ROWS/2, j);
    }

    for(int j = NUM_COLS - 1; j > NUM_COLS/2; j--) {
        board[NUM_ROWS/2][j] = new Square(strip[NUM_COLS - 1 - j], NUM_ROWS/2, j);
    }

    // Vertical strips
    for(int j = 0; j < NUM_ROWS/2; j++) {
        board[j][NUM_COLS/2] = new Square(strip[j], j, NUM_COLS/2);
    }

    for(int j = NUM_ROWS - 1; j > NUM_ROWS/2; j--) {
        board[j][NUM_COLS/2] = new Square(strip[NUM_ROWS - 1 - j], j, NUM_COLS/2);
    }

    // Center
    board[7][7] = new Square(DWS, 7, 7);

    // Set neighbours
    Square* currSquare = nullptr;
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            currSquare = board[i][j];
            if(j - 1 > -1) {
                currSquare->setLeft(board[i][j - 1]);
            }
            if(j + 1 < NUM_COLS) {
                currSquare->setRight(board[i][j + 1]);
            }
            if(i - 1 > -1) {
                currSquare->setAbove(board[i - 1][j]);
            }
            if(i + 1 < NUM_ROWS) {
                currSquare->setBelow(board[i + 1][j]);
            }
        }
    }
}

/**
  * Clean up all squares on Board
  */
Board::~Board()
{
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLS; j++) {
            delete board[i][j];
        }
    }
}

/**
 * "Pretty print" the board to stdout
 */
void Board::show(const char *window_title, int flags, FontCollection_t *fonts)
{
    string toPrint;
    Square* currSquare;
    square_clicked = false;

    ImGui::Begin(window_title, nullptr, flags);
    int id = 0;
    std::string letter_str;
    std::string button_label = "";
    ImGui::PushID(id);
    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
    ImGui::Button("##", ImVec2(25, 25));
    ImGui::SameLine();
    ImGui::PopStyleColor(3);
    ImGui::PopID();
    // top column numbers
    for(int i = 0; i < NUM_COLS; ++i) {
        button_label = to_string(i);
        ImGui::PushID(id);
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
        ImGui::Button(button_label.c_str(), ImVec2(50, 25));
        if(i != (NUM_COLS - 1)) {
            ImGui::SameLine();
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    for(int i = 0; i < NUM_ROWS; ++i) {
        // left side row numbers
        ImGui::PushID(id);
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
        ImGui::Button(to_string(i).c_str(), ImVec2(25, 50));
        ImGui::SameLine();
        ImGui::PopStyleColor(3);
        ImGui::PopID();
        for(int j = 0; j < NUM_COLS; ++j) {
            currSquare = board[i][j];
            ImGui::PushID(id);
            if(currSquare->isEmpty()) {
                ImGui::PushFont(fonts->small);
                // TODO: get clicked square data from the board
                if(i == 7 && j == 7) { // Center square is a double word square
                    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_PINK(0.7));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_PINK(0.8));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_PINK(0.9));
                    if(ImGui::Button("##", ImVec2(50, 50))){
                        square_clicked = true;
                        clicked_square_x = i;
                        clicked_square_y = j;
                    }
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                        ImGui::SetTooltip("DWS");
                    }
                }
                else {
                    switch(currSquare->getType()) {
                    case 0: // normal
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_DARK_BROWN(0.7));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_DARK_BROWN(0.8));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_DARK_BROWN(0.9));
                        if(ImGui::Button("##", ImVec2(50, 50))) {
                            square_clicked = true;
                            clicked_square_x = i;
                            clicked_square_y = j;
                        }
                        break;
                    case 1: // double word score
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_PINK(0.7));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_PINK(0.8));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_PINK(0.9));
                        if(ImGui::Button("##", ImVec2(50, 50))) {
                            square_clicked = true;
                            clicked_square_x = i;
                            clicked_square_y = j;
                        }
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                            ImGui::SetTooltip("DWS");
                        }
                        break;
                    case 2: // triple word score
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_RED(0.7));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_RED(0.8));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_RED(0.9));
                        if(ImGui::Button("##", ImVec2(50, 50))) {
                            square_clicked = true;
                            clicked_square_x = i;
                            clicked_square_y = j;
                        }
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                            ImGui::SetTooltip("TWS");
                        }
                        break;
                    case 3: // double letter score
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_LIGHT_BLUE(0.7));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_LIGHT_BLUE(0.8));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_LIGHT_BLUE(0.9));
                        if(ImGui::Button("##", ImVec2(50, 50))) {
                            square_clicked = true;
                            clicked_square_x = i;
                            clicked_square_y = j;
                        }
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                            ImGui::SetTooltip("DLS");
                        }
                        break;
                    case 4: // triple letter score
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_DARK_BLUE(0.7));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_DARK_BLUE(0.8));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_DARK_BLUE(0.9));
                        if(ImGui::Button("##", ImVec2(50, 50))) {
                            square_clicked = true;
                            clicked_square_x = i;
                            clicked_square_y = j;
                        }
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                            ImGui::SetTooltip("TLS");
                        }
                        break;
                    }
                }
                ImGui::PopStyleColor(3);
                ImGui::PopFont();
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_YELLOW(0.7));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_YELLOW(0.8));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_YELLOW(0.9));
                letter_str = currSquare->getTile()->getLetterStr();
                if (letter_str.empty()) {
                    ImGui::Button("##", ImVec2(50, 50));
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::HSV_BG(1.0));
                    ImGui::PushFont(fonts->title);
                    ImGui::Button(letter_str.c_str(), ImVec2(50, 50));
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
                ImGui::PushFont(fonts->small);
                switch(currSquare->getType()) {
                case 0: // normal
                    break;
                case 1: // double word score
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                        ImGui::SetTooltip("DWS");
                    }
                    break;
                case 2: // triple word score
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                        ImGui::SetTooltip("TWS");
                    }
                    break;
                case 3: // double letter score
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                        ImGui::SetTooltip("DLS");
                    }
                    break;
                case 4: // triple letter score
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                        ImGui::SetTooltip("TLS");
                    }
                    break;
                }
                ImGui::PopFont();
                ImGui::PopStyleColor(3);
            }
            ImGui::SameLine();
            ImGui::PopID();
            ++id;
        }
        // right side row numbers
        ImGui::PushID(id);
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
        ImGui::Button(to_string(i).c_str(), ImVec2(25, 50));
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    ImGui::PushID(id);
    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
    ImGui::Button("##", ImVec2(25, 25));
    ImGui::SameLine();
    ImGui::PopStyleColor(3);
    ImGui::PopID();
    // bottom column numbers
    for(int i = 0; i < NUM_COLS; ++i) {
        button_label = to_string(i);
        ImGui::PushID(id);
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_BG(1.0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_BG(1.0));
        ImGui::Button(button_label.c_str(), ImVec2(50, 25));
        if(i != (NUM_COLS - 1)) {
            ImGui::SameLine();
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    ImGui::End();
}

/**
 * Place a Tile on the Board
 *
 * @param t Pointer to the tile to be placed
 * @param r Row where the tile should be placed
 * @param c Column where the tile should be placed
 *
 * @return true if placed successfully, false otherwise
 *
 * @throws std::string containing the error message
 */
bool Board::placeTile(Tile* t, int r, int c)
{
    if(r < 0 || r > NUM_ROWS - 1) {
        throw string("Invalid row number\n");
    }
    else if (c < 0 || c > NUM_COLS - 1) {
        throw string("Invalid column number\n");
    }
    else {
        Square* curr = board[r][c];
        if(curr->isEmpty()) {
            curr->setTile(t);
            t->setSquare(curr);
            t->setLoc(2);
            return true;
        }
        else {
            return false;
        }
    }
}

/**
 * Place a series of Tiles on the Board
 *
 * @param rack Pointer to the Rack from where the Tiles are coming
 * @param tilesInStr A vector of pointers to the Tiles to be placed
 * @param r Row where the first Tile goes
 * @param c Column where the first Tile goes
 * @param dir Direction of placement ('h'/'v')
 *
 * @throws std::string containing the error message
 */
void Board::placeTileStr(Rack* rack, vector<Tile*> tilesInStr, int r, int c, char dir)
{
    auto it = tilesInStr.begin();
    int currRow = r;
    int currCol = c;
    vector<Tile*> placed;
    try {
        while(it != tilesInStr.end()) {
            if(dir == 'h') {
                if(placeTile(*it, currRow, currCol++)) {
                    placed.push_back(*it);
                    it++;
                }
            }
            else if(dir == 'v') {
                if(placeTile(*it, currRow++, currCol)) {
                    placed.push_back(*it);
                    it++;
                }
            }
            else {
                throw(string("Invalid direction\n"));
            }
        }
    }
    catch(string err) {
        int currRow = r;
        int currCol = c;
        if(dir == 'h') {
            for(unsigned long i = 0; i < placed.size(); i++) {
                rack->addTile(retrieve(currRow, currCol++));
            }
        }
        else if(dir == 'v') {
            for(unsigned long i = 0; i < placed.size(); i++) {
                rack->addTile(retrieve(currRow++, currCol));
            }
        }
        for(unsigned long i = placed.size(); i < tilesInStr.size(); i ++) {
            rack->addTile(tilesInStr[i]);
        }
        throw(err + " Because some of the tiles won't fit on the board\n");
    }
}

/**
 * Retrieve a Tile from the Board
 *
 * @param r Row where Tile to be retrieved is
 * @param c Column where Tile to be retrieved is
 *
 * @return A pointer to the returned Tile, nullptr if unsuccessful
 *
 * This function shall not throw exceptions.
 */
Tile* Board::retrieve(int r, int c)
{
    Tile* t = nullptr;
    if(!board[r][c]->isEmpty()) {
        t = board[r][c]->getTile();
        board[r][c]->setTile(nullptr);
    }
    return t;
}

/**
 * Get a square from the board
 *
 * @param r Row where Square to be returned is
 * @param c Column where Square to be returned is
 *
 * @return A pointer to the Square that is requested
 *
 * @throws std::string containing the error message
 */
Square* Board::getSquare(int r, int c)
{
    if(r > -1 && r < NUM_ROWS && c > -1 && c < NUM_COLS) {
        return board[r][c];
    }
    else {
        throw(string("Square out of bounds\n"));
    }
}

int Board::getClickedSquare_x()
{
    return clicked_square_x;
}

int Board::getClickedSquare_y()
{
    return clicked_square_y;
}

bool Board::getSquareClicked()
{
    return square_clicked;
}

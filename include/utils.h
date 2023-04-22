/**
  * @file
  */
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "imgui.h"

class Tile;
class Square;
class Play;

typedef struct PlayerInput_t {
    std::string raw;
    std::string tiles;
    int row;
    int col;
    char dir;
} PlayerInput_t;

void clearPlayerInput(PlayerInput_t *input);

/** Helper to print variables for debugging */
#define DEBUG_PRINT(x, y) std::cout << x << ":" << y << std::endl
/** Number of rows in the Board */
#define NUM_ROWS 15
/** Number of columns in the Board */
#define NUM_COLS 15
#define PLAYER_MAX 4

const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

/**
  * String of alphabets used for input validation
  */
const std::string alphabets = "abcdefghijklmnopqrstuvwxyz";

/*
 * ANSI escape codes for colour
 *
 * \033[38;2;<r>;<g>;<b>m     #Select RGB foreground color
 * \033[48;2;<r>;<g>;<b>m     #Select RGB background color
 *
 * Use like this-
 * Pinkish text on a brownish background
 * \033[38;2;255;82;197;48;2;155;106;0mHello
 */
// Start colour helper functions
inline void BOLD(std::string x)
{
    std::cout << "\033[1m" + x + "\033[0m";
}

inline void BOLD_BRIGHT_GREEN_FG(std::string x)
{
    std::cout << "\033[1;38;2;0;255;19m" + x + "\033[0m";
}

inline void BOLD_CYAN_FG(std::string x)
{
    std::cout << "\033[1;38;2;51;177;255m" + x + "\033[0m";
}

inline void BOLD_BLUE_FG(std::string x)
{
    std::cout << "\033[1;38;2;0;0;255m" + x + "\033[0m";
}

inline void BOLD_PINK_FG(std::string x)
{
    std::cout << "\033[1;38;2;203;6;104m" + x + "\033[0m";
}

inline void BOLD_ORANGE_FG(std::string x)
{
    std::cout << "\033[1;38;2;248;28;28m" + x + "\033[0m";
}

inline void BOLD_BROWN_FG(std::string x)
{
    std::cout << "\033[1;38;2;149;0;19m" + x + "\033[0m";
}

inline void BOLD_WHITE_FG(std::string x)
{
    std::cout << "\033[1;38;2;255;255;255m" + x + "\033[0m";
}

inline void BOLD_RED_FG(std::string x)
{
    std::cout << "\033[1;38;2;255;0;0m" + x + "\033[0m";
}

inline void PALE_GREEN_FG(std::string x)
{
    std::cout << "\033[38;2;50;193;110m" + x + "\033[0m";
}

inline void BOLD_LIGHT_GRAY_FG(std::string x)
{
    std::cout << "\033[1;38;2;232;232;232m" + x + "\033[0m";
}

inline void BOLD_BLACK_FG(std::string x)
{
    std::cout << "\033[1;38;2;0;0;0m" + x + "\033[0m";
}

inline void BROWN_BG(std::string x)
{
    std::cout << "\033[48;2;104;0;13m" + x + "\033[0m";
}

inline void RED_BG(std::string x)
{
    std::cout << "\033[48;2;255;26;26m" + x + "\033[0m";
}

inline void PINK_BG(std::string x)
{
    std::cout << "\033[48;2;225;0;109m" + x + "\033[0m";
}

inline void DARK_BLUE_BG(std::string x)
{
    std::cout << "\033[48;2;101;11;218m" + x + "\033[0m";
}

inline void LIGHT_BLUE_BG(std::string x)
{
    std::cout << "\033[48;2;145;128;255m" + x + "\033[0m";
}

inline void OFF_WHITE_BG(std::string x)
{
    std::cout << "\033[48;2;255;198;179m" + x + "\033[0m";
}

inline void TILE_COLOURS(std::string x)
{
    std::cout << "\033[1;38;2;0;0;0;48;2;255;255;255m" + x + "\033[0m";
}

inline void BOARD_COLOURS(std::string x)
{
    std::cout << "\033[1;38;2;232;232;232;48;2;77;0;9m" + x + "\033[0m";
}

namespace ImGui {
inline ImVec4 HSV_LIGHT_BROWN(float alpha)
{
    return (ImVec4)ImColor::HSV((360.0/360.0), 0.24, 0.96, alpha);
}

inline ImVec4 HSV_DARK_BROWN(float alpha)
{
    return (ImVec4)ImColor::HSV((353.0/360.0), 1.0, 0.408, alpha);
}

inline ImVec4 HSV_RED(float alpha)
{
    return (ImVec4)ImColor::HSV((0.0/360.0), 0.898, 1.0, alpha);
}

inline ImVec4 HSV_PINK(float alpha)
{
    return (ImVec4)ImColor::HSV((334.0/360.0), 1.0, 0.992, alpha);
}

inline ImVec4 HSV_DARK_BLUE(float alpha)
{
    return (ImVec4)ImColor::HSV((266.0/360.0), 0.95, 8.855, alpha);
}

inline ImVec4 HSV_LIGHT_BLUE(float alpha)
{
    return (ImVec4)ImColor::HSV((248.0/360.0), 0.498, 1.0, alpha);
}

inline ImVec4 HSV_OFF_WHITE(float alpha)
{
    return (ImVec4)ImColor::HSV((15.0/360.0), 0.298, 1.0, alpha);
}

inline ImVec4 HSV_GREEN(float alpha)
{
    return (ImVec4)ImColor::HSV((119.0/360.0), 0.98, 0.88, alpha);
}
inline ImVec4 HSV_BG(float alpha)
{
    return (ImVec4)ImColor::HSV((120.0/360.0), 0.07, 0.06, alpha);
}
inline void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(Help)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
}
// End colour helper functions

/**
 * Other helper functions
 */
bool squarePresent(std::vector<Square*> s, Square* target);
bool tilePresent(std::vector<Tile*> t, Tile* target);
bool charPresent(std::string str, char target);
bool onlyLetters(std::string str);
std::vector<std::string> parsePlay(std::string in);
void log(std::string logFilePath, std::string str);
std::string RawTimeToString(const time_t& t);

#endif

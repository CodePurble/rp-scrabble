#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <algorithm>
#include <vector>

class Tile;
class Square;
class Play;

#define DEBUG_PRINT(x, y) std::cout << x << ":" << y << std::endl
#define NUM_ROWS 15
#define NUM_COLS 15

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

/*
 * Colouring functions
 */
inline void TILE_COLOURS(std::string x)
{
	std::cout << "\033[1;38;2;0;0;0;48;2;255;255;255m" + x + "\033[0m";
}

inline void BOARD_COLOURS(std::string x)
{
	std::cout << "\033[1;38;2;232;232;232;48;2;77;0;9m" + x + "\033[0m";
}

/*
 * Other helper functions
 */
bool squarePresent(std::vector<Square*> s, Square* target);
bool tilePresent(std::vector<Tile*> t, Tile* target);
bool charPresent(std::string str, char target);
std::vector<std::string> parsePlay(std::string in);
void log(std::string logFilePath, std::string str);
std::string RawTimeToString(const time_t& t);

#endif

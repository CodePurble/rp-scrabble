/**
  * @file
  */
#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include "imgui.h"

/**
 * Based on Dear Imgui Logger example
 */
class Logger {
private:
    ImGuiTextBuffer imguiBuf;
    ImVector<int> lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.

public:
    Logger();
    ~Logger();
    void clear();
    void log(const char* fmt, ...) IM_FMTARGS(2);
    void fileLog(std::string logFilePath, const char* text);
    void show(const char* title, bool* p_open, int flags);
};

#endif


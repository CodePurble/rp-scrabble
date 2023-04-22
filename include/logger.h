/**
  * @file
  */
#ifndef LOGGER_H
#define LOGGER_H
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
    void addLog(const char* fmt, ...) IM_FMTARGS(2);
    void show(const char* title, bool* p_open = NULL);

};

#endif


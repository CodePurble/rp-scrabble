#include <fstream>
#include <sstream>
#include <string>
#include "logger.h"
#include "imgui.h"

using namespace std;

Logger::Logger()
{
    clear();
}

Logger::~Logger()
{
}

void Logger::clear()
{
    imguiBuf.clear();
    lineOffsets.clear();
    lineOffsets.push_back(0);
}

void Logger::log(const char* fmt, ...)
{
    int old_size = imguiBuf.size();
    va_list args;
    va_start(args, fmt);
    imguiBuf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = imguiBuf.size(); old_size < new_size; old_size++)
        if (imguiBuf[old_size] == '\n')
            lineOffsets.push_back(old_size + 1);
}

void Logger::fileLog(std::string logFilePath, const char* text)
{
    ofstream logFile(logFilePath, ios::app);

    if(logFile.is_open()) {
        logFile << text;
    }
    else {
        throw(string("Failed to open file at " + logFilePath + "\n"));
    }

    logFile.close();
}

void Logger::show(const char* title, bool* p_open, int flags)
{
    if (!ImGui::Begin(title, p_open, flags))
    {
        ImGui::End();
        return;
    }

    // Main window
    bool copy = ImGui::Button("Copy");
    ImGui::Separator();

    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = imguiBuf.begin();
        const char* buf_end = imguiBuf.end();
        // The simplest and easy way to display the entire buffer:
        //   ImGui::TextUnformatted(buf_begin, buf_end);
        // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
        // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
        // within the visible area.
        // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
        // on your side is recommended. Using ImGuiListClipper requires
        // - A) random access into your data
        // - B) items all being the  same height,
        // both of which we can handle since we have an array pointing to the beginning of each line of text.
        // When using the filter (in the block of code above) we don't have random access into the data to display
        // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
        // it possible (and would be recommended if you want to search through tens of thousands of entries).
        ImGuiListClipper clipper;
        clipper.Begin(lineOffsets.Size);
        while (clipper.Step())
        {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char* line_start = buf + lineOffsets[line_no];
                const char* line_end = (line_no + 1 < lineOffsets.Size) ? (buf + lineOffsets[line_no + 1] - 1) : buf_end;
                ImGui::TextUnformatted(line_start, line_end);
            }
        }
        clipper.End();
        ImGui::PopStyleVar();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}


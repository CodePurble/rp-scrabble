/**
  * @file
  */
#include <iostream>
#include "rack.h"
#include "tile.h"
#include "utils.h"

using namespace std;

/**
  * Init rack with nullptr
  */
Rack::Rack()
{
    rack.fill(nullptr);
}

/**
  * Clean up rack
  */
Rack::~Rack()
{
    for(Tile* t : rack) {
        if(t) {
            delete t;
        }
    }
}

/**
 * "Pretty print" the rack
 */
void Rack::show(const char *window_title, bool alt, int flags, ImFont *font)
{
    std::string letter_str;
    ImGui::Begin(window_title, nullptr, flags);
    for(unsigned long i = 0; i < rack.size(); i++) {
        if(rack[i]) {
            ImGui::PushID(i);
            ImGui::PushFont(font);
            letter_str = rack[i]->getLetterStr();
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::HSV_BG(1.0));
            if(alt) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_GREEN(0.7));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_GREEN(0.8));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_GREEN(0.9));
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::HSV_OFF_WHITE(0.7));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::HSV_OFF_WHITE(0.8));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::HSV_OFF_WHITE(0.9));
            }
            ImGui::Button(letter_str.c_str(), ImVec2(50, 50));
            ImGui::PopStyleColor(4);
            ImGui::PopFont();
            ImGui::PopID();
        }
        ImGui::SameLine();
    }
    ImGui::End();
}

/**
 * Request a Tile from the rack
 *
 * @param ch Character representing the Tile
 *
 * @return Pointer to the requested Tile if the Tile exists, nullptr otherwise
 *
 * This function shall not throw exceptions
 */
Tile* Rack::getTile(char ch)
{
    for(Tile* t : rack) {
        if(t) {
            if(t->getLetter() == ch) {
                return t;
            }
        }
    }
    return nullptr;
}

/**
 * Fill the rack with provided tiles
 *
 * @param t A vector of pointers to the Tiles to be put in the rack
 *
 * This function shall not throw exceptions.
 */
void Rack::fill(vector<Tile*> t)
{
    unsigned long i = 0;
    while(!t.empty() && i < rack.size()) {
        if(!rack[i]) {
            rack[i] = t.back();
            rack[i]->setLoc(1);
            rack[i]->setRack(this);
            t.pop_back();
        }
        i++;
    }
}

/**
 * Add a Tile to the rack
 *
 * @param t A pointer to the Tile to be placed in the rack
 *
 * This function shall not throw exceptions.
 */
void Rack::addTile(Tile* t)
{
    for(unsigned long i = 0; i < rack.size(); i++) {
        if(!rack[i]) {
            rack[i] = t;
            rack[i]->setLoc(1);
            rack[i]->setRack(this);
            break;
        }
    }
}

/**
 * Get a vector of the Tiles requested from the rack
 *
 * @param tileStr A string of letters that represent Tiles
 *
 * @return A vector of pointers to the requested Tiles
 *
 * @throws std::string containing the error message
 */
vector<Tile*> Rack::getTileStrVec(string tileStr)
{
    vector<Tile*> tileStrVec;
    bool found;

    for(char ch : tileStr) {
        found = false;
        for(auto& t: rack) {
            if(t && ch == t->getLetter()) {
                found = true;
                tileStrVec.push_back(t);
                t = nullptr; // "Remove" from rack
                break;
            }
        }
        if(!found) {
            // Abort!! Reset the rack and start again
            fill(tileStrVec);
            throw string("Tile '" + string(1, ch) + "' not found in the rack\n");
        }
    }
    return tileStrVec;
}

void Rack::returnToBag(Bag *gameBag, std::vector<Tile*> tiles)
{
    string tileStr = "";
    for(Tile *t : tiles) {
        tileStr += t->getLetter();
    }
    tiles = getTileStrVec(tileStr);
    gameBag->add(tiles);
}

/**
 * Check whether rack is empty
 *
 * @return true if empty, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Rack::isEmpty()
{
    for(unsigned long i = 0; i < rack.size(); i++) {
        if(rack[i]) {
            return false;
        }
    }
    return true;
}

void Rack::refresh(Bag *gameBag)
{
    std::vector<Tile*> tiles;
    for(Tile *t : rack) {
        tiles.push_back(t);
    }
    returnToBag(gameBag, tiles);
    fill(gameBag->draw(7));
}

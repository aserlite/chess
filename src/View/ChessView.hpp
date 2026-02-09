#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include "../Logic/Game.hpp"

class ChessView {
public:
    ChessView();

    void init();

    void draw();

private:
    ChessGame m_game;
    Position  m_selectedPos;
    ImFont*   m_font;

    void        drawBoardWindow();
    void        drawInfoWindow();
    std::string getPieceLabel(const Piece& p) const;

    bool fileExists(const std::string& name) const;
};
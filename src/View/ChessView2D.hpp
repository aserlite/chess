#pragma once
#include <imgui.h>
#include <string>
#include "../Logic/Game.hpp"

class ChessView2D {
public:
    ChessView2D();

    void init();
    void draw(ChessGame& game);

private:
    Position m_selectedPos;
    ImFont*  m_font;

    std::string getPieceLabel(const Piece& p) const;
    bool fileExists(const std::string& name) const;
};

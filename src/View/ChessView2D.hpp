#pragma once
#include <imgui.h>
#include <string>
#include "../Logic/Game.hpp"
#include "ViewContext.hpp"

class ChessView2D {
public:
    ChessView2D();

    void init();
    bool draw(ChessGame& game, ViewContext& ctx);

private:
    ImFont*  m_font;

    [[nodiscard]] std::string getPieceLabel(const Piece& p) const;
    [[nodiscard]] bool fileExists(const std::string& name) const;
};

#pragma once
#include <imgui.h>
#include "../Logic/AIController.hpp"
#include "../Logic/Game.hpp"
#include "ChessView2D.hpp"
#include "ChessView3D.hpp"
#include "MenuView.hpp"
#include <cstdint>

enum class AppState : std::uint8_t {
    Menu,
    Game
};

class ChessView {
public:
    ChessView(ChessGame& game, AIController& aiController);

    void init();

    void draw();

private:
    ChessGame&    m_game;
    AIController& m_aiController;
    MenuView      m_menu;
    AppState      m_appState;

    ChessView2D m_view2D;
    ChessView3D m_view3D;

    void drawInfoWindow();
    void drawChaosWindow();
};
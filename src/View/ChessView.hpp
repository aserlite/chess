#pragma once
#include <imgui.h>
#include "../Logic/Game.hpp"
#include "../Logic/AIController.hpp"
#include "MenuView.hpp"
#include "ChessView2D.hpp"
#include "ChessView3D.hpp"

enum class AppState {
    Menu,
    Game
};

class ChessView {
public:
    ChessView();

    void init();

    void draw();

private:
    ChessGame    m_game;
    AIController m_aiController;
    MenuView     m_menu;
    AppState     m_appState;

    ChessView2D m_view2D;
    ChessView3D m_view3D;

    void drawInfoWindow();
};
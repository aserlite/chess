#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include "../Logic/Game.hpp"
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
    ChessGame m_game;
    MenuView  m_menu;
    AppState  m_appState;

    ChessView2D m_view2D;
    ChessView3D m_view3D;

    void drawInfoWindow();
};
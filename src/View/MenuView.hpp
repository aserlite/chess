#pragma once
#include <imgui.h>
#include <string>
#include "Logic/AI.hpp"

enum class MenuAction {
    None,
    Start1v1,
    StartAI
};

class MenuView {
public:
    MenuView();

    MenuAction draw();

    std::string getEnteredFEN() const;

    AIDifficulty getSelectedDifficulty() const { return m_selectedDifficulty; }
    PieceColor   getSelectedColor() const { return m_selectedColor; }

private:
    char m_fenBuffer[128];

    AIDifficulty m_selectedDifficulty;
    PieceColor   m_selectedColor;
    bool         m_showAIConfigPopup;
};
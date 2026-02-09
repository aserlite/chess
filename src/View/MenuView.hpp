#pragma once
#include <imgui.h>
#include <string>

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

private:
    char m_fenBuffer[128];
};
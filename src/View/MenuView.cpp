#include "MenuView.hpp"
#include <cstring>

MenuView::MenuView()
{
    std::memset(m_fenBuffer, 0, sizeof(m_fenBuffer));
}

MenuAction MenuView::draw()
{
    MenuAction action = MenuAction::None;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(550, 350));

    ImGui::Begin("Menu Principal", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    float winWidth  = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("CHESS GAME").x;
    ImGui::SetCursorPosX((winWidth - textWidth) * 0.5f);
    ImGui::Text("CHESS GAME");

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Joueur vs Joueur", ImVec2(-1, 50)))
    {
        action = MenuAction::Start1v1;
    }

    ImGui::Spacing();

    if (ImGui::Button("Joueur vs IA (Ca arrive fort)", ImVec2(-1, 50)))
    {
        action = MenuAction::StartAI;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Charger une partie (FEN) :");

    ImGui::InputText("##fen", m_fenBuffer, sizeof(m_fenBuffer));

    ImGui::End();

    return action;
}

std::string MenuView::getEnteredFEN() const
{
    return std::string(m_fenBuffer);
}
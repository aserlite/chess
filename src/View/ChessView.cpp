#include "ChessView.hpp"
#include <fstream>
#include <iostream>

ChessView::ChessView()
    : m_appState(AppState::Menu)
{
}

void ChessView::init()
{
    m_view2D.init();
    m_view3D.init();
}

void ChessView::draw()
{
    if (m_appState == AppState::Menu)
    {
        MenuAction action = m_menu.draw();

        if (action == MenuAction::Start1v1)
        {
            std::string fen = m_menu.getEnteredFEN();
            if (!fen.empty())
            {
                m_game.loadFEN(fen);
            }
            m_appState = AppState::Game;
        }
        else if (action == MenuAction::StartAI)
        {
            m_game.setVsAI(true);
            m_game.setAIDifficulty(m_menu.getSelectedDifficulty());
            m_game.setPlayerColor(m_menu.getSelectedColor());
            m_appState = AppState::Game;
        }
    }
    else
    {
        m_view2D.draw(m_game);
        m_view3D.draw(m_game);
        drawInfoWindow();
    }
}

void ChessView::drawInfoWindow()
{
    ImGui::Begin("Infos Partie");

    ImGui::Text("FEN:");
    std::string fen = m_game.getFEN();
    ImGui::InputText("##fen", (char*)fen.c_str(), fen.size(), ImGuiInputTextFlags_ReadOnly);

    ImGui::Separator();

    bool isHistoryEmpty = m_game.getHistory().empty();

    ImGui::BeginDisabled(isHistoryEmpty);

    if (ImGui::Button("Annuler le dernier coup"))
    {
        m_game.undo();
    }

    ImGui::EndDisabled();

    ImGui::Separator();

    ImGui::Text("Historique:");
    ImGui::BeginChild("History", ImVec2(0, -1), false, ImGuiWindowFlags_HorizontalScrollbar);

    const auto& history = m_game.getHistory();
    for (size_t i = 0; i < history.size(); ++i)
    {
        if (i % 2 == 0)
            ImGui::Text("%d. %s", (int)(i / 2) + 1, history[i].c_str());
        else
        {
            ImGui::SameLine();
            ImGui::Text("%s", history[i].c_str());
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
    ImGui::End();
}
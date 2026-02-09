#include "MenuView.hpp"
#include <cstring>

MenuView::MenuView()
    : m_selectedDifficulty(AIDifficulty::Easy)
    , m_selectedColor(PieceColor::White)
    , m_showAIConfigPopup(false)
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
        m_showAIConfigPopup = true;
        ImGui::OpenPopup("Configuration IA");
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Charger une partie (FEN) :");

    ImGui::InputText("##fen", m_fenBuffer, sizeof(m_fenBuffer));

    if (m_showAIConfigPopup)
    {
        if (ImGui::BeginPopupModal("Configuration IA", &m_showAIConfigPopup, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Niveau de l'IA :");
            if (ImGui::RadioButton("Facile (Singe Ivre)", m_selectedDifficulty == AIDifficulty::Easy))
                m_selectedDifficulty = AIDifficulty::Easy;
            if (ImGui::RadioButton("Moyen (Gourmand)", m_selectedDifficulty == AIDifficulty::Medium))
                m_selectedDifficulty = AIDifficulty::Medium;
            if (ImGui::RadioButton("Difficile (Ca arrive fort)", m_selectedDifficulty == AIDifficulty::Hard))
                m_selectedDifficulty = AIDifficulty::Hard;

            ImGui::Separator();

            ImGui::Text("Votre Couleur :");
            bool isWhite = (m_selectedColor == PieceColor::White);
            if (ImGui::RadioButton("Blancs", isWhite))
                m_selectedColor = PieceColor::White;
            ImGui::SameLine();
            if (ImGui::RadioButton("Noirs", !isWhite))
                m_selectedColor = PieceColor::Black;

            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("Jouer", ImVec2(175, 0)))
            {
                action              = MenuAction::StartAI;
                m_showAIConfigPopup = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Retour", ImVec2(175, 0)))
            {
                m_showAIConfigPopup = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    ImGui::End();

    return action;
}

std::string MenuView::getEnteredFEN() const
{
    return std::string(m_fenBuffer);
}
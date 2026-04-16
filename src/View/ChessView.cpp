#include "ChessView.hpp"
#include <array>
#include <memory>
#include "../Logic/IGameRule.hpp"

ChessView::ChessView(ChessGame& game, AIController& aiController)
    : m_game(game)
    , m_aiController(aiController)
    , m_appState(AppState::Menu)
    , m_view3D([this](Position from, Position to) { m_game.move(from, to); })
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
        const MenuAction action = m_menu.draw();

        if (action == MenuAction::Start1v1)
        {
            m_aiController.setEnabled(false);
            const std::string fen = m_menu.getEnteredFEN();
            if (!fen.empty())
            {
                m_game.loadFEN(fen);
            }
            else
            {
                m_game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            }

            m_game.clearRules();
            for (auto& factory : RuleRegistry::getFactories())
            {
                if (factory.enabled)
                {
                    m_game.addRule(factory.create());
                }
            }

            m_appState = AppState::Game;
        }
        else if (action == MenuAction::StartAI)
        {
            m_aiController.setEnabled(true);
            m_aiController.setDifficulty(m_menu.getSelectedDifficulty());
            m_aiController.setPlayerColor(m_menu.getSelectedColor());
            const std::string fen = m_menu.getEnteredFEN();
            if (!fen.empty())
            {
                m_game.loadFEN(fen);
            }
            else
            {
                m_game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            }

            m_game.clearRules();
            for (auto& factory : RuleRegistry::getFactories())
            {
                if (factory.enabled)
                {
                    m_game.addRule(factory.create());
                }
            }

            m_appState = AppState::Game;
        }
    }
    else
    {
        const bool quit = m_view2D.draw(m_game, m_viewContext);
        m_view3D.draw(m_game, m_viewContext);
        drawInfoWindow();
        drawChaosWindow();

        if (quit)
        {
            m_appState = AppState::Menu;
        }
    }
}

void ChessView::drawInfoWindow()
{
    ImGui::Begin("Infos Partie");

    ImGui::Text("FEN:");
    const std::string           fen = m_game.getFEN();
    std::array<char, 256> fenBuffer{};
    std::strncpy(fenBuffer.data(), fen.c_str(), fenBuffer.size() - 1);
    fenBuffer[fenBuffer.size() - 1] = '\0';
    ImGui::InputText("##fen", fenBuffer.data(), fenBuffer.size(), ImGuiInputTextFlags_ReadOnly);

    ImGui::Separator();

    const bool isHistoryEmpty = m_game.getHistory().empty();

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
            ImGui::Text("%d. %s", (int)(i / 2) + 1, history[i].description.c_str());
        else
        {
            ImGui::SameLine();
            ImGui::Text("%s", history[i].description.c_str());
        }

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
    ImGui::End();
}

void ChessView::drawChaosWindow()
{
    const auto& rules = m_game.getActiveRules();
    if (rules.empty())
        return;

    ImGui::Begin("Infos mode Chaos");

    const std::string feedback = m_game.getLastFeedback();
    if (!feedback.empty())
    {
        ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "Action refusée :");
        ImGui::TextWrapped("%s", feedback.c_str());
        ImGui::Separator();
    }

    ImGui::Text("Modes Actifs :");
    for (const auto& r : rules)
    {
        ImGui::BulletText("%s (%s)", r->getRuleName().c_str(), r->getMathStats().c_str());
    }

    ImGui::End();
}
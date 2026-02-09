#include "ChessView.hpp"
#include <fstream>
#include <iostream>

ChessView::ChessView()
    : m_selectedPos{-1, -1}
    , m_font(nullptr)
    , m_appState(AppState::Menu)
{
}

void ChessView::init()
{
    ImGuiIO&             io             = ImGui::GetIO();
    static const ImWchar icons_ranges[] = {0x0020, 0x00FF, 0x2600, 0x26FF, 0};

    std::vector<std::string> potentialPaths = {
        "./src/DejaVuSans.ttf",
        "../../src/DejaVuSans.ttf",
        "DejaVuSans.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    };

    const char* foundPath = nullptr;
    for (const auto& path : potentialPaths)
    {
        if (fileExists(path))
        {
            foundPath = path.c_str();
            std::cout << "Police trouvee : " << path << "\n";
            break;
        }
    }

    if (foundPath)
    {
        m_font = io.Fonts->AddFontFromFileTTF(foundPath, 40.0f, NULL, icons_ranges);
    }
    else
    {
        std::cerr << "ERREUR: Police introuvable. Utilisation defaut.\n";
    }

    if (!m_font)
    {
        ImFontConfig config;
        config.SizePixels = 13.0f;
        m_font            = io.Fonts->AddFontDefault(&config);
    }
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
        drawBoardWindow();
        drawInfoWindow();
    }
}

void ChessView::drawBoardWindow()
{
    ImGui::Begin("Plateau de Jeu");

    if (m_game.isVsAI() && m_game.getCurrentTurn() != m_game.getPlayerColor() && m_game.getState() == GameState::Playing)
    {
        m_game.playAITurn();
    }

    if (m_game.getCurrentTurn() == PieceColor::White)
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "Trait aux BLANCS");
    else
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "Trait aux NOIRS");
    ImGui::Separator();

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        m_selectedPos = {-1, -1};

    const auto& board    = m_game.getBoard();
    float       cellSize = 60.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            bool   isDark = (x + y) % 2 != 0;
            ImVec4 bgCol  = isDark ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.8f, 0.8f, 0.8f, 1.f);

            if (m_selectedPos.x == x && m_selectedPos.y == y)
                bgCol = ImVec4(0.0f, 0.7f, 0.0f, 1.0f);
            else if (m_selectedPos.x != -1 && m_game.isValidMove(m_selectedPos, {x, y}))
                bgCol = ImVec4(0.0f, 0.4f, 0.8f, 0.8f);

            const Piece& p       = board.getPiece(x, y);
            ImVec4       textCol = (p.isEmpty()) ? ImVec4(0, 0, 0, 0) : ImVec4(0.1f, 0.1f, 0.1f, 1.f);

            ImGui::PushStyleColor(ImGuiCol_Button, bgCol);
            ImGui::PushStyleColor(ImGuiCol_Text, textCol);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(bgCol.x + 0.1f, bgCol.y + 0.1f, bgCol.z + 0.1f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(bgCol.x - 0.1f, bgCol.y - 0.1f, bgCol.z - 0.1f, 1.f));

            ImGui::PushID(y * 8 + x);

            if (m_font)
                ImGui::PushFont(m_font);
            bool clicked = ImGui::Button(getPieceLabel(p).c_str(), ImVec2(cellSize, cellSize));
            if (m_font)
                ImGui::PopFont();

            if (clicked)
            {
                if (m_selectedPos.x == -1)
                {
                    if (!p.isEmpty() && p.color == m_game.getCurrentTurn())
                        m_selectedPos = {x, y};
                }
                else
                {
                    Position targetPos = {x, y};
                    if (m_selectedPos.x == x && m_selectedPos.y == y)
                        m_selectedPos = {-1, -1};
                    else if (m_game.move(m_selectedPos, targetPos))
                        m_selectedPos = {-1, -1};
                    else if (!p.isEmpty() && p.color == m_game.getCurrentTurn())
                        m_selectedPos = {x, y};
                }
            }

            ImGui::PopID();
            ImGui::PopStyleColor(4);
            if (x < 7)
                ImGui::SameLine();
        }
    }
    ImGui::PopStyleVar();

    if (m_game.getState() == GameState::PromotionSelect)
    {
        ImGui::OpenPopup("Promotion");
    }

    if (ImGui::BeginPopupModal("Promotion", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::Button("Dame", ImVec2(120, 0)))
        {
            m_game.promotePawn(PieceType::Queen);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Tour", ImVec2(120, 0)))
        {
            m_game.promotePawn(PieceType::Rook);
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Fou", ImVec2(120, 0)))
        {
            m_game.promotePawn(PieceType::Bishop);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cavalier", ImVec2(120, 0)))
        {
            m_game.promotePawn(PieceType::Knight);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (m_game.getState() == GameState::WhiteWins || m_game.getState() == GameState::BlackWins)
    {
        ImGui::OpenPopup("gg");
    }

    if (ImGui::BeginPopupModal("gg", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (m_game.getState() == GameState::WhiteWins)
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "VICTOIRE DES BLANCS !");
        else
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "VICTOIRE DES NOIRS !");

        ImGui::Separator();

        if (ImGui::Button("Quitter"))
        {
            exit(0);
        }
        ImGui::EndPopup();
    }

    ImGui::End();
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
        m_selectedPos = {-1, -1};
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

bool ChessView::fileExists(const std::string& name) const
{
    std::ifstream f(name.c_str());
    return f.good();
}

std::string ChessView::getPieceLabel(const Piece& p) const
{
    if (p.type == PieceType::None)
        return " ";

    if (p.color == PieceColor::White)
    {
        switch (p.type)
        {
        case PieceType::Pawn: return "♙";
        case PieceType::Rook: return "♖";
        case PieceType::Knight: return "♘";
        case PieceType::Bishop: return "♗";
        case PieceType::Queen: return "♕";
        case PieceType::King: return "♔";
        default: return "?";
        }
    }
    else
    {
        switch (p.type)
        {
        case PieceType::Pawn: return "♟";
        case PieceType::Rook: return "♜";
        case PieceType::Knight: return "♞";
        case PieceType::Bishop: return "♝";
        case PieceType::Queen: return "♛";
        case PieceType::King: return "♚";
        default: return "?";
        }
    }
}
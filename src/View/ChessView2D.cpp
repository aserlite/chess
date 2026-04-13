#include "ChessView2D.hpp"
#include <iostream>
#include <filesystem>

ChessView2D::ChessView2D()
    : m_selectedPos{-1, -1}
    , m_font(nullptr)
{
}

void ChessView2D::init()
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

bool ChessView2D::draw(ChessGame& game)
{
    bool quitRequested = false;
    ImGui::Begin("Plateau de Jeu (2D)");

    if (game.getCurrentTurn() == PieceColor::White)
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "Trait aux BLANCS");
    else
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "Trait aux NOIRS");
    ImGui::Separator();

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        m_selectedPos = {-1, -1};

    const auto& board    = game.getBoard();
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
            else if (m_selectedPos.x != -1 && game.isValidMove(m_selectedPos, {x, y}))
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
                    if (!p.isEmpty() && p.color == game.getCurrentTurn())
                        m_selectedPos = {x, y};
                }
                else
                {
                    Position targetPos = {x, y};
                    if (m_selectedPos.x == x && m_selectedPos.y == y)
                        m_selectedPos = {-1, -1};
                    else if (game.move(m_selectedPos, targetPos))
                        m_selectedPos = {-1, -1};
                    else if (!p.isEmpty() && p.color == game.getCurrentTurn())
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

    if (game.getState() == GameState::PromotionSelect)
    {
        ImGui::OpenPopup("Promotion");
    }

    if (ImGui::BeginPopupModal("Promotion", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::Button("Dame", ImVec2(120, 0)))
        {
            game.promotePawn(PieceType::Queen);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Tour", ImVec2(120, 0)))
        {
            game.promotePawn(PieceType::Rook);
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Fou", ImVec2(120, 0)))
        {
            game.promotePawn(PieceType::Bishop);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cavalier", ImVec2(120, 0)))
        {
            game.promotePawn(PieceType::Knight);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (game.getState() == GameState::WhiteWins || game.getState() == GameState::BlackWins)
    {
        ImGui::OpenPopup("gg");
    }

    if (ImGui::BeginPopupModal("gg", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (game.getState() == GameState::WhiteWins)
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "VICTOIRE DES BLANCS !");
        else
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "VICTOIRE DES NOIRS !");

        ImGui::Separator();

        if (ImGui::Button("Quitter"))
        {
            ImGui::CloseCurrentPopup();
            quitRequested = true;
        }
        ImGui::EndPopup();
    }

    ImGui::End();
    return quitRequested;
}

bool ChessView2D::fileExists(const std::string& name) const
{
    return std::filesystem::exists(name);
}

std::string ChessView2D::getPieceLabel(const Piece& p) const
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

#include <imgui.h>
#include <iostream>
#include <string>
#include "Logic/Game.hpp"
#include "quick_imgui/quick_imgui.hpp"

std::string getPieceLabel(const Piece& p)
{
    if (p.color == PieceColor::None)
        return " ";

    std::string label;
    switch (p.type)
    {
    case PieceType::Pawn: label = "P"; break;
    case PieceType::Rook: label = "T"; break;   // Tour
    case PieceType::Knight: label = "C"; break; // Cavalier
    case PieceType::Bishop: label = "F"; break; // Fou
    case PieceType::Queen: label = "D"; break;  // Dame
    case PieceType::King: label = "R"; break;   // Roi
    default: label = "?";
    }
    return label;
}

int main()
{
    ChessGame game;

    quick_imgui::loop(
        "Chess Game",
        {
            .init = [&]() {},
            .loop = [&]() {
                
                ImGui::Begin("Plateau de Jeu");

                const auto& board = game.getBoard();

                float cellSize = 60.0f; 
                
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        
                        bool isDark = (x + y) % 2 != 0;
                        ImVec4 bgCol = isDark ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.8f, 0.8f, 0.8f, 1.f);
                        
                        const Piece& p = board.getPiece(x, y);
                        ImVec4 textCol = (p.color == PieceColor::White) ? ImVec4(1.f, 1.f, 1.f, 1.f) : ImVec4(0.f, 0.f, 0.f, 1.f);
                        if (p.isEmpty()) textCol = ImVec4(0,0,0,0);

                        ImGui::PushStyleColor(ImGuiCol_Button, bgCol);
                        ImGui::PushStyleColor(ImGuiCol_Text, textCol);
                        
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(bgCol.x + 0.1f, bgCol.y + 0.1f, bgCol.z + 0.1f, 1.f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(bgCol.x - 0.1f, bgCol.y - 0.1f, bgCol.z - 0.1f, 1.f));

                        ImGui::PushID(y * 8 + x);

                        std::string label = getPieceLabel(p);
                        if (ImGui::Button(label.c_str(), ImVec2(cellSize, cellSize))) {
                            std::cout << "Click case: " << x << ", " << y << "\n";
                        }

                        ImGui::PopID();

                        ImGui::PopStyleColor(4);

                        if (x < 7) ImGui::SameLine();
                    }
                }

                ImGui::PopStyleVar();
                ImGui::End(); },
        }
    );
}
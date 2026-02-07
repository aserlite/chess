#include <imgui.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Logic/Game.hpp"
#include "Logic/Piece.hpp"
#include "quick_imgui/quick_imgui.hpp"

bool fileExists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

std::string getPieceLabel(const Piece& p)
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

int main()
{
    ChessGame game;
    Position  selectedPos{-1, -1};
    ImFont*   mainFont = nullptr;

    quick_imgui::loop(
        "Chess Game",
        {
            .init = [&]() {
                ImGuiIO& io = ImGui::GetIO();
                static const ImWchar icons_ranges[] = { 0x0020, 0x00FF, 0x2600, 0x26FF, 0 };
                const char* fontPath = "./src/DejaVuSans.ttf";
                
                mainFont = io.Fonts->AddFontFromFileTTF(fontPath, 40.0f, NULL, icons_ranges);
                if (!mainFont) {
                     ImFontConfig config; config.SizePixels = 40.0f;
                     mainFont = io.Fonts->AddFontDefault(&config);
                } },

            .loop = [&]() {
                ImGui::Begin("Plateau de Jeu");

                if (game.getCurrentTurn() == PieceColor::White) {
                    ImGui::TextColored(ImVec4(1, 1, 1, 1), "Trait aux BLANCS");
                } else {
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1), "Trait aux NOIRS");
                }
                ImGui::Separator();

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) selectedPos = {-1, -1};

                const auto& board = game.getBoard();
                float cellSize = 60.0f; 
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

                for (int y = 0; y < 8; ++y) {
                    for (int x = 0; x < 8; ++x) {
                        
                        bool isDark = (x + y) % 2 != 0;
                        ImVec4 bgCol = isDark ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.8f, 0.8f, 0.8f, 1.f);
                        
                        if (selectedPos.x == x && selectedPos.y == y) bgCol = ImVec4(0.0f, 0.7f, 0.0f, 1.0f); 
                        else if (selectedPos.x != -1 && game.isValidMove(selectedPos, {x, y})) bgCol = ImVec4(0.0f, 0.4f, 0.8f, 0.8f);

                        const Piece& p = board.getPiece(x, y);
                        
                        ImVec4 textCol = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
                        if (p.isEmpty()) textCol = ImVec4(0,0,0,0);

                        ImGui::PushStyleColor(ImGuiCol_Button, bgCol);
                        ImGui::PushStyleColor(ImGuiCol_Text, textCol);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(bgCol.x + 0.1f, bgCol.y + 0.1f, bgCol.z + 0.1f, 1.f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(bgCol.x - 0.1f, bgCol.y - 0.1f, bgCol.z - 0.1f, 1.f));

                        ImGui::PushID(y * 8 + x);
                        std::string label = getPieceLabel(p);
                        
                        if (mainFont) ImGui::PushFont(mainFont);
                        bool clicked = ImGui::Button(label.c_str(), ImVec2(cellSize, cellSize));
                        if (mainFont) ImGui::PopFont();

                        if (clicked) {
                            if (selectedPos.x == -1) {
                                if (!p.isEmpty() && p.color == game.getCurrentTurn()) {
                                    selectedPos = {x, y};
                                }
                            }
                            else {
                                Position targetPos = {x, y};
                                
                                if (selectedPos.x == x && selectedPos.y == y) {
                                    selectedPos = {-1, -1};
                                }
                                else {
                                    if (game.move(selectedPos, targetPos)) {
                                        selectedPos = {-1, -1};
                                    } 
                                    else {
                                        if (!p.isEmpty() && p.color == game.getCurrentTurn()) {
                                            selectedPos = {x, y};
                                        }
                                    }
                                }
                            }
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
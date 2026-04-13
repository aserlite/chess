#include "View/ChessView.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    ChessGame    game;
    AIController aiController;
    ChessView    app(game, aiController);

    quick_imgui::loop(
        "Chess Game",
        {.init = [&]() { app.init(); },
         .loop = [&]() {
             aiController.playAITurn(game);
             app.draw();
         }}
    );
}
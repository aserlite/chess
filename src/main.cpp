#include "View/ChessView.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    ChessView app;

    quick_imgui::loop(
        "Chess Game",
        {.init = [&]() { app.init(); },
         .loop = [&]() { app.draw(); }}
    );
}
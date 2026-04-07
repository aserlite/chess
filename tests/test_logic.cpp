#include <catch2/catch_test_macros.hpp>
#include "Logic/Board.hpp"

void clearBoard(Board& board)
{
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            board.setPiece(x, y, Piece{PieceType::None, PieceColor::None});
        }
    }
}

TEST_CASE("Regles generales du plateau", "[Logic][General]")
{
    Board board;

    SECTION("Impossible de bouger une case vide")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 5}));
    }

    SECTION("Impossible de manger sa propre piece")
    {
        REQUIRE_FALSE(board.isMoveValid({0, 7}, {0, 6})); // La tour blanche mange le pion blanc
    }
}

TEST_CASE("Logique du Pion", "[Logic][Pawn]")
{
    Board board;

    SECTION("Avancement de base (Blanc)")
    {
        REQUIRE(board.isMoveValid({4, 6}, {4, 5})); // 1 case
        REQUIRE(board.isMoveValid({4, 6}, {4, 4})); // 2 cases depuis le départ
    }

    SECTION("Avancement de base (Noir)")
    {
        REQUIRE(board.isMoveValid({4, 1}, {4, 2})); // 1 case
        REQUIRE(board.isMoveValid({4, 1}, {4, 3})); // 2 cases depuis le départ
    }

    SECTION("Interdictions d'avancement")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 6}, {4, 7})); // Interdit de reculer
        REQUIRE_FALSE(board.isMoveValid({4, 6}, {4, 3})); // Interdit de faire 3 cases
    }

    SECTION("Manger en diagonale")
    {
        clearBoard(board);
        board.setPiece(4, 4, Piece{PieceType::Pawn, PieceColor::White});

        board.setPiece(5, 3, Piece{PieceType::Pawn, PieceColor::Black});
        REQUIRE(board.isMoveValid({4, 4}, {5, 3})); // Attaque valide

        board.setPiece(4, 3, Piece{PieceType::Pawn, PieceColor::Black});
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 3})); // Avancer bloqué par une pièce
    }
}

TEST_CASE("Logique du Cavalier", "[Logic][Knight]")
{
    Board board;
    clearBoard(board);
    board.setPiece(4, 4, Piece{PieceType::Knight, PieceColor::White});

    SECTION("Mouvements en L valides")
    {
        REQUIRE(board.isMoveValid({4, 4}, {5, 2})); // Haut-Droite
        REQUIRE(board.isMoveValid({4, 4}, {6, 3})); // Droite-Haut
        REQUIRE(board.isMoveValid({4, 4}, {3, 6})); // Bas-Gauche
    }

    SECTION("Mouvements invalides")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 2})); // Ligne droite
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {6, 6})); // Diagonale
    }

    SECTION("Saut au-dessus des pieces")
    {
        board.setPiece(4, 3, Piece{PieceType::Pawn, PieceColor::White});
        board.setPiece(5, 4, Piece{PieceType::Pawn, PieceColor::White});

        REQUIRE(board.isMoveValid({4, 4}, {6, 3}));
    }
}

TEST_CASE("Logique du Fou", "[Logic][Bishop]")
{
    Board board;
    clearBoard(board);
    board.setPiece(4, 4, Piece{PieceType::Bishop, PieceColor::White});

    SECTION("Diagonales valides")
    {
        REQUIRE(board.isMoveValid({4, 4}, {7, 1})); // Diagonale Haut-Droite
        REQUIRE(board.isMoveValid({4, 4}, {1, 7})); // Diagonale Bas-Gauche
    }

    SECTION("Mouvements non diagonaux invalides")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 1})); // Ligne droite
    }

    SECTION("Collision sur le chemin")
    {
        board.setPiece(6, 2, Piece{PieceType::Pawn, PieceColor::Black});

        REQUIRE(board.isMoveValid({4, 4}, {6, 2}));       // Peut manger l'obstacle
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {7, 1})); // Ne peut pas passer au travers
    }
}

TEST_CASE("Logique de la Tour", "[Logic][Rook]")
{
    Board board;
    clearBoard(board);
    board.setPiece(4, 4, Piece{PieceType::Rook, PieceColor::White});

    SECTION("Lignes droites valides")
    {
        REQUIRE(board.isMoveValid({4, 4}, {4, 0})); // Haut
        REQUIRE(board.isMoveValid({4, 4}, {7, 4})); // Droite
    }

    SECTION("Mouvements diagonaux invalides")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {6, 6})); // Diagonale
    }

    SECTION("Collision sur le chemin")
    {
        board.setPiece(4, 2, Piece{PieceType::Pawn, PieceColor::Black});

        REQUIRE(board.isMoveValid({4, 4}, {4, 2}));       // Peut manger l'obstacle
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 0})); // Ne peut pas passer au travers
    }
}

TEST_CASE("Logique de la Dame", "[Logic][Queen]")
{
    Board board;
    clearBoard(board);
    board.setPiece(4, 4, Piece{PieceType::Queen, PieceColor::White});

    SECTION("Mouvements valides (Tour + Fou)")
    {
        REQUIRE(board.isMoveValid({4, 4}, {4, 0})); // Ligne droite
        REQUIRE(board.isMoveValid({4, 4}, {7, 1})); // Diagonale
    }

    SECTION("Mouvements improbables invalides")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {6, 5})); // Mouvement de cavalier
    }
}

TEST_CASE("Logique du Roi", "[Logic][King]")
{
    Board board;
    clearBoard(board);
    board.setPiece(4, 4, Piece{PieceType::King, PieceColor::White});

    SECTION("1 case dans toutes les directions")
    {
        REQUIRE(board.isMoveValid({4, 4}, {4, 3})); // Haut
        REQUIRE(board.isMoveValid({4, 4}, {5, 5})); // Diagonale Bas-Droite
    }

    SECTION("Impossible de faire plus d'une case")
    {
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {4, 2})); // 2 cases haut
        REQUIRE_FALSE(board.isMoveValid({4, 4}, {6, 6})); // 2 cases diagonale
    }
}
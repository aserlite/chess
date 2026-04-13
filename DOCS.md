# Documentation

## Diagrammes de classes

### AI

```mermaid
classDiagram
    class C_0009094603417046821245["AI"]
    class C_0009094603417046821245 {
        +getBestMove(const Board & board, PieceColor myColor, AIDifficulty level, Move & outMove) bool$
        -getGreedyMove(const Board & board, PieceColor myColor, Move & outMove) bool$
        -getRandomMove(const Board & board, PieceColor myColor, Move & outMove) bool$
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### AIController

```mermaid
classDiagram
    class C_0004306397417237529713["AIController"]
    class C_0004306397417237529713 {
        +AIController() [default] void
        +getPlayerColor() [const] PieceColor
        +isEnabled() [const] bool
        +playAITurn(ChessGame & game) void
        +setDifficulty(AIDifficulty diff) void
        +setEnabled(bool active) void
        +setPlayerColor(PieceColor color) void
        -m_difficulty : AIDifficulty
        -m_enabled : bool
        -m_playerColor : PieceColor
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### Board

```mermaid
classDiagram
    class C_0002748255974922495785["Board"]
    class C_0002748255974922495785 {
        +Board() void
        -checkBishopMove(Position from, Position to) [const] bool
        -checkKnightMove(Position from, Position to) [const] bool
        -checkPawnMove(Position from, Position to, PieceColor color) [const] bool
        -checkRookMove(Position from, Position to) [const] bool
        +getPiece(int x, int y) [const] Piece
        +isMoveValid(Position from, Position to) [const] bool
        -isPathClear(Position from, Position to) [const] bool
        +resetBoard() void
        +setPiece(int x, int y, Piece p) void
        -setupNobleRow(int y, PieceColor color) void
        +SIZE : const std::size_t
        -m_grid : std::array&lt;std::array&lt;Piece,SIZE&gt;,SIZE&gt;
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### ChessGame

```mermaid
classDiagram
    class C_0004842393136000246713["ChessGame"]
    class C_0004842393136000246713 {
        +ChessGame() [default] void
        +addRule(std::shared_ptr&lt;IGameRule&gt; rule) void
        -changeTurn() void
        +clearRules() void
        +getBoard() [const] const Board &
        +getCurrentTurn() [const] PieceColor
        +getFEN() [const] std::string
        +getHistory() [const] const std::vector&lt;std::string&gt; &
        +getState() [const] GameState
        +isValidMove(Position from, Position to) [const] bool
        +loadFEN(const std::string & fen) void
        +move(Position from, Position to) bool
        +promotePawn(PieceType type) void
        -saveSnapshot() void
        +toChessNotation(Position p) [const] std::string
        +undo() void
        -m_activeRules : std::vector&lt;std::shared_ptr&lt;IGameRule&gt;&gt;
        -m_backupHistory : std::vector&lt;GameSnapshot&gt;
        -m_board : Board
        -m_currentTurn : PieceColor
        -m_history : std::vector&lt;std::string&gt;
        -m_promotionPos : Position
        -m_state : GameState
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### ChessView

```mermaid
classDiagram
    class C_0008047285621877002607["ChessView"]
    class C_0008047285621877002607 {
        +ChessView(ChessGame & game, AIController & aiController) void
        +draw() void
        -drawInfoWindow() void
        +init() void
        -m_aiController : AIController &
        -m_appState : AppState
        -m_game : ChessGame &
        -m_menu : MenuView
        -m_view2D : ChessView2D
        -m_view3D : ChessView3D
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### ChessView2D

```mermaid
classDiagram
    class C_0002531126229291306321["ChessView2D"]
    class C_0002531126229291306321 {
        +ChessView2D() void
        +draw(ChessGame & game) bool
        -fileExists(const std::string & name) [const] bool
        -getPieceLabel(const Piece & p) [const] std::string
        +init() void
        -m_font : ImFont *
        -m_selectedPos : Position
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### ChessView3D

```mermaid
classDiagram
    class C_0006761073196897303396["ChessView3D"]
    class C_0006761073196897303396 {
        +ChessView3D() void
        +~ChessView3D() void
        +draw(const ChessGame & game) void
        +init() void
        -resizeFBO(int width, int height) void
        -setupBuffers() void
        -m_cameraAngleX : float
        -m_cameraAngleY : float
        -m_cameraDistance : float
        -m_cubeVao : unsigned int
        -m_cubeVbo : unsigned int
        -m_fbo : unsigned int
        -m_height : int
        -m_program : std::unique_ptr&lt;glimac::Program&gt;
        -m_rbo : unsigned int
        -m_texture : unsigned int
        -m_width : int
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### GameSnapshot

```mermaid
classDiagram
    class C_0010267710733373613038["GameSnapshot"]
    class C_0010267710733373613038 {
        +board : Board
        +currentTurn : PieceColor
        +state : GameState
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### IGameRule

```mermaid
classDiagram
    class C_0004851280417930349063["IGameRule"]
    class C_0004851280417930349063 {
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### MenuView

```mermaid
classDiagram
    class C_0015974733186916866267["MenuView"]
    class C_0015974733186916866267 {
        +MenuView() void
        +draw() MenuAction
        +getEnteredFEN() [const] std::string
        +getSelectedColor() [const] PieceColor
        +getSelectedDifficulty() [const] AIDifficulty
        -m_fenBuffer : char[128]
        -m_selectedColor : PieceColor
        -m_selectedDifficulty : AIDifficulty
        -m_showAIConfigPopup : bool
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### Move

```mermaid
classDiagram
    class C_0007563864698956368175["Move"]
    class C_0007563864698956368175 {
        +from : Position
        +to : Position
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### Piece

```mermaid
classDiagram
    class C_0004777943177714336574["Piece"]
    class C_0004777943177714336574 {
        +isEmpty() [const,constexpr] bool
        +color : PieceColor
        +type : PieceType
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```

### Position

```mermaid
classDiagram
    class C_0017533998226253472530["Position"]
    class C_0017533998226253472530 {
        +operator==(const Position & other) [const,constexpr] bool
        +x : int
        +y : int
    }

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```


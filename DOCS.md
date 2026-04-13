# Documentation

## Diagramme de classes

```mermaid
classDiagram
    class C_0000933547394081598572["PieceColor"]
    class C_0000933547394081598572 {
        <<enumeration>>
        None
        White
        Black
    }
    class C_0003177176768377443572["PieceType"]
    class C_0003177176768377443572 {
        <<enumeration>>
        None
        Pawn
        Rook
        Knight
        Bishop
        Queen
        King
    }
    class C_0004777943177714336574["Piece"]
    class C_0004777943177714336574 {
        +isEmpty() [const,constexpr] bool
        +color : PieceColor
        +type : PieceType
    }
    class C_0017533998226253472530["Position"]
    class C_0017533998226253472530 {
        +operator==(const Position & other) [const,constexpr] bool
        +x : int
        +y : int
    }
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
    class C_0002280536835303751986["AIDifficulty"]
    class C_0002280536835303751986 {
        <<enumeration>>
        Easy
        Medium
        Hard
    }
    class C_0007563864698956368175["Move"]
    class C_0007563864698956368175 {
        +from : Position
        +to : Position
    }
    class C_0009094603417046821245["AI"]
    class C_0009094603417046821245 {
        +getBestMove(const Board & board, PieceColor myColor, AIDifficulty level, Move & outMove) bool$
        -getGreedyMove(const Board & board, PieceColor myColor, Move & outMove) bool$
        -getRandomMove(const Board & board, PieceColor myColor, Move & outMove) bool$
    }
    class C_0018077852919137909338["GameState"]
    class C_0018077852919137909338 {
        <<enumeration>>
        Playing
        PromotionSelect
        WhiteWins
        BlackWins
    }
    class C_0010267710733373613038["GameSnapshot"]
    class C_0010267710733373613038 {
        +board : Board
        +currentTurn : PieceColor
        +state : GameState
    }
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
    class C_0004851280417930349063["IGameRule"]
    class C_0004851280417930349063 {
    }
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
    class C_0017785097031180024373["GLFWvidmode"]
    class C_0017785097031180024373 {
        +blueBits : int
        +greenBits : int
        +height : int
        +redBits : int
        +refreshRate : int
        +width : int
    }
    class C_0013885031836770510049["GLFWgammaramp"]
    class C_0013885031836770510049 {
        +blue : unsigned short *
        +green : unsigned short *
        +red : unsigned short *
        +size : unsigned int
    }
    class C_0013161603514781355259["GLFWimage"]
    class C_0013161603514781355259 {
        +height : int
        +pixels : unsigned char *
        +width : int
    }
    class C_0003832180380787386966["GLFWgamepadstate"]
    class C_0003832180380787386966 {
        +axes : float[6]
        +buttons : unsigned char[15]
    }
    class C_0006267435463482043089["GLFWallocator"]
    class C_0006267435463482043089 {
        +allocate : GLFWallocatefun
        +deallocate : GLFWdeallocatefun
        +reallocate : GLFWreallocatefun
        +user : void *
    }
    class C_0017165406136470954566["glm::detail::is_int&lt;T&gt;"]
    class C_0017165406136470954566 {
    }
    class C_0014743839948111171689["glm::detail::is_int::test"]
    class C_0014743839948111171689 {
        <<enumeration>>
        value
    }
    class C_0018341899181759956368["glm::detail::is_int&lt;unsigned int&gt;"]
    class C_0018341899181759956368 {
    }
    class C_0001878113324719440692["glm::detail::is_int&lt;int&gt;"]
    class C_0001878113324719440692 {
    }
    class C_0002238266916699413146["glm::detail::is_aligned&lt;glm::qualifier P&gt;"]
    class C_0002238266916699413146 {
        +value : const bool
    }
    class C_0012832989951413576519["glm::detail::storage&lt;length_t L,T,_Bool is_aligned&gt;"]
    class C_0012832989951413576519 {
    }
    class C_0011108722095378127667["glm::detail::storage::type"]
    class C_0011108722095378127667 {
        +data : T[]
    }
    class C_0001287751108879850958["glm::detail::storage&lt;L,T,true&gt;"]
    class C_0001287751108879850958 {
    }
    class C_0002998106636798449075["glm::detail::storage&lt;3,T,true&gt;"]
    class C_0002998106636798449075 {
    }
    class C_0011330292752136108294["glm::detail::genTypeEnum"]
    class C_0011330292752136108294 {
        <<enumeration>>
        GENTYPE_VEC
        GENTYPE_MAT
        GENTYPE_QUAT
    }
    class C_0006743273674606620912["glm::detail::genTypeTrait&lt;genType&gt;"]
    class C_0006743273674606620912 {
    }
    class C_0015896199050460753952["glm::detail::genTypeTrait&lt;glm::mat&lt;C,R,T,glm::packed_highp&gt;&gt;"]
    class C_0015896199050460753952 {
        +GENTYPE : const genTypeEnum
    }
    class C_0007193098452303625212["glm::detail::init_gentype&lt;genType,genTypeEnum type&gt;"]
    class C_0007193098452303625212 {
    }
    class C_0003083707105962937990["glm::detail::init_gentype&lt;genType,glm::detail::GENTYPE_QUAT&gt;"]
    class C_0003083707105962937990 {
        +identity() [constexpr] genType$
    }
    class C_0015603389788290154537["glm::detail::init_gentype&lt;genType,glm::detail::GENTYPE_MAT&gt;"]
    class C_0015603389788290154537 {
        +identity() [constexpr] genType$
    }
    class C_0009311863672616278593["glm::detail::compute_equal&lt;T,_Bool isFloat&gt;"]
    class C_0009311863672616278593 {
        +call(T a, T b) [constexpr] bool$
    }
    class C_0010444049787743091084["glm::detail::is_int&lt;signed char&gt;"]
    class C_0010444049787743091084 {
    }
    class C_0007454676841364767438["glm::detail::is_int&lt;short&gt;"]
    class C_0007454676841364767438 {
    }
    class C_0011587924244531489778["glm::detail::is_int&lt;long long&gt;"]
    class C_0011587924244531489778 {
    }
    class C_0012373186198985777456["glm::detail::is_int&lt;unsigned char&gt;"]
    class C_0012373186198985777456 {
    }
    class C_0001447139119483475009["glm::detail::is_int&lt;unsigned short&gt;"]
    class C_0001447139119483475009 {
    }
    class C_0001207741522012001173["glm::detail::is_int&lt;unsigned long long&gt;"]
    class C_0001207741522012001173 {
    }
    class C_0008773260381889745120["glm::detail::compute_vec4_add&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0008773260381889745120 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0014180874808606960218["glm::detail::compute_vec4_sub&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0014180874808606960218 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0014721178274615561002["glm::detail::compute_vec4_mul&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0014721178274615561002 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0018293134536481637290["glm::detail::compute_vec4_div&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0018293134536481637290 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0008182436331049693656["glm::detail::compute_vec4_mod&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0008182436331049693656 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0009448542793109187229["glm::detail::compute_vec4_and&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0009448542793109187229 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0007394072018332501491["glm::detail::compute_vec4_or&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0007394072018332501491 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0007182033410364433853["glm::detail::compute_vec4_xor&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0007182033410364433853 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0008784057479259358475["glm::detail::compute_vec4_shift_left&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0008784057479259358475 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0011512554430276197142["glm::detail::compute_vec4_shift_right&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0011512554430276197142 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0015114459323685163119["glm::detail::compute_vec4_equal&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0015114459323685163119 {
        +call(const vec&lt;4,T,Q&gt; & v1, const vec&lt;4,T,Q&gt; & v2) [constexpr] bool$
    }
    class C_0001513586326169120888["glm::detail::compute_vec4_nequal&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0001513586326169120888 {
        +call(const vec&lt;4,T,Q&gt; & v1, const vec&lt;4,T,Q&gt; & v2) [constexpr] bool$
    }
    class C_0000879102544197822415["glm::detail::compute_vec4_bitwise_not&lt;T,qualifier Q,int IsInt,std::size_t Size,_Bool Aligned&gt;"]
    class C_0000879102544197822415 {
        +call(const vec&lt;4,T,Q&gt; & v) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0017686723680688667673["glm::detail::outerProduct_trait&lt;length_t C,length_t R,T,qualifier Q&gt;"]
    class C_0017686723680688667673 {
    }
    class C_0009697542087676983569["glm::detail::outerProduct_trait&lt;2,2,T,Q&gt;"]
    class C_0009697542087676983569 {
    }
    class C_0009367951713378955731["glm::detail::outerProduct_trait&lt;2,3,T,Q&gt;"]
    class C_0009367951713378955731 {
    }
    class C_0004129319365027099429["glm::detail::outerProduct_trait&lt;2,4,T,Q&gt;"]
    class C_0004129319365027099429 {
    }
    class C_0013919754403120507144["glm::detail::outerProduct_trait&lt;3,2,T,Q&gt;"]
    class C_0013919754403120507144 {
    }
    class C_0018250010645674283695["glm::detail::outerProduct_trait&lt;3,3,T,Q&gt;"]
    class C_0018250010645674283695 {
    }
    class C_0002465306396778682587["glm::detail::outerProduct_trait&lt;3,4,T,Q&gt;"]
    class C_0002465306396778682587 {
    }
    class C_0017006236639334178286["glm::detail::outerProduct_trait&lt;4,2,T,Q&gt;"]
    class C_0017006236639334178286 {
    }
    class C_0015474031542116761089["glm::detail::outerProduct_trait&lt;4,3,T,Q&gt;"]
    class C_0015474031542116761089 {
    }
    class C_0015405964719396265045["glm::detail::outerProduct_trait&lt;4,4,T,Q&gt;"]
    class C_0015405964719396265045 {
    }
    class C_0002560830178258722289["glm::detail::functor1&lt;vec&lt;&gt;,length_t L,R,T,qualifier Q&gt;"]
    class C_0002560830178258722289 {
    }
    class C_0016189112089169313067["glm::detail::functor1&lt;&lpar;anonymous&rpar;,1,R,T,Q&gt;"]
    class C_0016189112089169313067 {
        +call(R &lpar;*&rpar;&lpar;T&rpar; Func, const template-parameter-0-0&lt;1,T,Q&gt; & v) [constexpr] template-parameter-0-0&lt;1,R,Q&gt;$
    }
    class C_0010171364238334460824["glm::detail::functor1&lt;&lpar;anonymous&rpar;,2,R,T,Q&gt;"]
    class C_0010171364238334460824 {
        +call(R &lpar;*&rpar;&lpar;T&rpar; Func, const template-parameter-0-0&lt;2,T,Q&gt; & v) [constexpr] template-parameter-0-0&lt;2,R,Q&gt;$
    }
    class C_0018376621820078191272["glm::detail::functor1&lt;&lpar;anonymous&rpar;,3,R,T,Q&gt;"]
    class C_0018376621820078191272 {
        +call(R &lpar;*&rpar;&lpar;T&rpar; Func, const template-parameter-0-0&lt;3,T,Q&gt; & v) [constexpr] template-parameter-0-0&lt;3,R,Q&gt;$
    }
    class C_0007872976482775124051["glm::detail::functor1&lt;&lpar;anonymous&rpar;,4,R,T,Q&gt;"]
    class C_0007872976482775124051 {
        +call(R &lpar;*&rpar;&lpar;T&rpar; Func, const template-parameter-0-0&lt;4,T,Q&gt; & v) [constexpr] template-parameter-0-0&lt;4,R,Q&gt;$
    }
    class C_0012783099691243171930["glm::detail::functor2&lt;vec&lt;&gt;,length_t L,T,qualifier Q&gt;"]
    class C_0012783099691243171930 {
    }
    class C_0009201574913036764026["glm::detail::functor2&lt;&lpar;anonymous&rpar;,1,T,Q&gt;"]
    class C_0009201574913036764026 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;1,T,Q&gt; & a, const template-parameter-0-0&lt;1,T,Q&gt; & b) template-parameter-0-0&lt;1,T,Q&gt;$
    }
    class C_0017665908564292248117["glm::detail::functor2&lt;&lpar;anonymous&rpar;,2,T,Q&gt;"]
    class C_0017665908564292248117 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;2,T,Q&gt; & a, const template-parameter-0-0&lt;2,T,Q&gt; & b) template-parameter-0-0&lt;2,T,Q&gt;$
    }
    class C_0000566273510248472737["glm::detail::functor2&lt;&lpar;anonymous&rpar;,3,T,Q&gt;"]
    class C_0000566273510248472737 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;3,T,Q&gt; & a, const template-parameter-0-0&lt;3,T,Q&gt; & b) template-parameter-0-0&lt;3,T,Q&gt;$
    }
    class C_0014512950444228567886["glm::detail::functor2&lt;&lpar;anonymous&rpar;,4,T,Q&gt;"]
    class C_0014512950444228567886 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;4,T,Q&gt; & a, const template-parameter-0-0&lt;4,T,Q&gt; & b) template-parameter-0-0&lt;4,T,Q&gt;$
    }
    class C_0008652419597806869875["glm::detail::functor2_vec_sca&lt;vec&lt;&gt;,length_t L,T,qualifier Q&gt;"]
    class C_0008652419597806869875 {
    }
    class C_0003725676454125813013["glm::detail::functor2_vec_sca&lt;&lpar;anonymous&rpar;,1,T,Q&gt;"]
    class C_0003725676454125813013 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;1,T,Q&gt; & a, T b) template-parameter-0-0&lt;1,T,Q&gt;$
    }
    class C_0010422810831389303463["glm::detail::functor2_vec_sca&lt;&lpar;anonymous&rpar;,2,T,Q&gt;"]
    class C_0010422810831389303463 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;2,T,Q&gt; & a, T b) template-parameter-0-0&lt;2,T,Q&gt;$
    }
    class C_0002168626670454111484["glm::detail::functor2_vec_sca&lt;&lpar;anonymous&rpar;,3,T,Q&gt;"]
    class C_0002168626670454111484 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;3,T,Q&gt; & a, T b) template-parameter-0-0&lt;3,T,Q&gt;$
    }
    class C_0008315779048824656096["glm::detail::functor2_vec_sca&lt;&lpar;anonymous&rpar;,4,T,Q&gt;"]
    class C_0008315779048824656096 {
        +call(T &lpar;*&rpar;&lpar;T,T&rpar; Func, const template-parameter-0-0&lt;4,T,Q&gt; & a, T b) template-parameter-0-0&lt;4,T,Q&gt;$
    }
    class C_0014466946788244241872["glm::detail::functor2_vec_int&lt;length_t L,T,qualifier Q&gt;"]
    class C_0014466946788244241872 {
    }
    class C_0003563067956550835236["glm::detail::functor2_vec_int&lt;1,T,Q&gt;"]
    class C_0003563067956550835236 {
        +call(int &lpar;*&rpar;&lpar;T,int&rpar; Func, const vec&lt;1,T,Q&gt; & a, const vec&lt;1,int,Q&gt; & b) vec&lt;1,int,Q&gt;$
    }
    class C_0000141248975816736781["glm::detail::functor2_vec_int&lt;2,T,Q&gt;"]
    class C_0000141248975816736781 {
        +call(int &lpar;*&rpar;&lpar;T,int&rpar; Func, const vec&lt;2,T,Q&gt; & a, const vec&lt;2,int,Q&gt; & b) vec&lt;2,int,Q&gt;$
    }
    class C_0008441460645539462312["glm::detail::functor2_vec_int&lt;3,T,Q&gt;"]
    class C_0008441460645539462312 {
        +call(int &lpar;*&rpar;&lpar;T,int&rpar; Func, const vec&lt;3,T,Q&gt; & a, const vec&lt;3,int,Q&gt; & b) vec&lt;3,int,Q&gt;$
    }
    class C_0004853162657727430087["glm::detail::functor2_vec_int&lt;4,T,Q&gt;"]
    class C_0004853162657727430087 {
        +call(int &lpar;*&rpar;&lpar;T,int&rpar; Func, const vec&lt;4,T,Q&gt; & a, const vec&lt;4,int,Q&gt; & b) vec&lt;4,int,Q&gt;$
    }
    class C_0009393182619228299296["glm::detail::compute_log2&lt;length_t L,T,qualifier Q,_Bool isFloat,_Bool Aligned&gt;"]
    class C_0009393182619228299296 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,T,Q&gt;$
    }
    class C_0005416897660123406119["glm::detail::compute_sqrt&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0005416897660123406119 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0003016636279178888439["glm::detail::compute_inversesqrt&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0003016636279178888439 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0001779101269862389753["glm::detail::compute_inversesqrt&lt;L,float,glm::packed_lowp,Aligned&gt;"]
    class C_0001779101269862389753 {
        +call(const vec&lt;L,float,lowp&gt; & x) vec&lt;L,float,lowp&gt;$
    }
    class C_0003376541723311639984["glm::detail::compute_abs&lt;genFIType,_Bool&gt;"]
    class C_0003376541723311639984 {
    }
    class C_0010811338212008253318["glm::detail::compute_abs&lt;genFIType,true&gt;"]
    class C_0010811338212008253318 {
        +call(genFIType x) [constexpr] genFIType$
    }
    class C_0015159482233899751592["glm::detail::compute_abs&lt;genFIType,false&gt;"]
    class C_0015159482233899751592 {
        +call(genFIType x) [constexpr] genFIType$
    }
    class C_0001189108426468022122["glm::detail::compute_abs_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0001189108426468022122 {
        +call(const vec&lt;L,T,Q&gt; & x) [constexpr] vec&lt;L,T,Q&gt;$
    }
    class C_0018330992663782840373["glm::detail::compute_mix_vector&lt;length_t L,T,U,qualifier Q,_Bool Aligned&gt;"]
    class C_0018330992663782840373 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y, const vec&lt;L,U,Q&gt; & a) vec&lt;L,T,Q&gt;$
    }
    class C_0000377743384354775438["glm::detail::compute_mix_vector&lt;L,T,bool,Q,Aligned&gt;"]
    class C_0000377743384354775438 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y, const vec&lt;L,bool,Q&gt; & a) vec&lt;L,T,Q&gt;$
    }
    class C_0009646140591064684154["glm::detail::compute_mix_scalar&lt;length_t L,T,U,qualifier Q,_Bool Aligned&gt;"]
    class C_0009646140591064684154 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y, const U & a) vec&lt;L,T,Q&gt;$
    }
    class C_0008411158522264013301["glm::detail::compute_mix_scalar&lt;L,T,bool,Q,Aligned&gt;"]
    class C_0008411158522264013301 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y, const bool & a) vec&lt;L,T,Q&gt;$
    }
    class C_0018022014358682532439["glm::detail::compute_mix&lt;T,U&gt;"]
    class C_0018022014358682532439 {
        +call(const T & x, const T & y, const U & a) T$
    }
    class C_0008876595274360920253["glm::detail::compute_mix&lt;T,bool&gt;"]
    class C_0008876595274360920253 {
        +call(const T & x, const T & y, const bool & a) T$
    }
    class C_0007878523707059901808["glm::detail::compute_sign&lt;length_t L,T,qualifier Q,_Bool isFloat,_Bool Aligned&gt;"]
    class C_0007878523707059901808 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0013720283651865864113["glm::detail::compute_floor&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0013720283651865864113 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0016391944696740134914["glm::detail::compute_ceil&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0016391944696740134914 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0013966754841608355702["glm::detail::compute_fract&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0013966754841608355702 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0000605404021214105083["glm::detail::compute_trunc&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0000605404021214105083 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0000498928720602658223["glm::detail::compute_round&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0000498928720602658223 {
        +call(const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0012572651991728070948["glm::detail::compute_mod&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0012572651991728070948 {
        +call(const vec&lt;L,T,Q&gt; & a, const vec&lt;L,T,Q&gt; & b) vec&lt;L,T,Q&gt;$
    }
    class C_0009782709305793365194["glm::detail::compute_min_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0009782709305793365194 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y) vec&lt;L,T,Q&gt;$
    }
    class C_0004807050522189811263["glm::detail::compute_max_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0004807050522189811263 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & y) vec&lt;L,T,Q&gt;$
    }
    class C_0002297802655018725126["glm::detail::compute_clamp_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0002297802655018725126 {
        +call(const vec&lt;L,T,Q&gt; & x, const vec&lt;L,T,Q&gt; & minVal, const vec&lt;L,T,Q&gt; & maxVal) vec&lt;L,T,Q&gt;$
    }
    class C_0007879660818841049157["glm::detail::compute_step_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0007879660818841049157 {
        +call(const vec&lt;L,T,Q&gt; & edge, const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0013085828508809210422["glm::detail::compute_smoothstep_vector&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0013085828508809210422 {
        +call(const vec&lt;L,T,Q&gt; & edge0, const vec&lt;L,T,Q&gt; & edge1, const vec&lt;L,T,Q&gt; & x) vec&lt;L,T,Q&gt;$
    }
    class C_0010361331594249330371["glm::detail::compute_length&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0010361331594249330371 {
        +call(const vec&lt;L,T,Q&gt; & v) T$
    }
    class C_0006191377841247627706["glm::detail::compute_distance&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0006191377841247627706 {
        +call(const vec&lt;L,T,Q&gt; & p0, const vec&lt;L,T,Q&gt; & p1) T$
    }
    class C_0003995764588866141299["glm::detail::compute_dot&lt;V,T,_Bool Aligned&gt;"]
    class C_0003995764588866141299 {
    }
    class C_0005418326039960527079["glm::detail::compute_dot&lt;glm::vec&lt;1,T,Q&gt;,T,Aligned&gt;"]
    class C_0005418326039960527079 {
        +call(const vec&lt;1,T,Q&gt; & a, const vec&lt;1,T,Q&gt; & b) [constexpr] T$
    }
    class C_0006750956518445531872["glm::detail::compute_dot&lt;glm::vec&lt;2,T,Q&gt;,T,Aligned&gt;"]
    class C_0006750956518445531872 {
        +call(const vec&lt;2,T,Q&gt; & a, const vec&lt;2,T,Q&gt; & b) [constexpr] T$
    }
    class C_0010330400419319200686["glm::detail::compute_dot&lt;glm::vec&lt;3,T,Q&gt;,T,Aligned&gt;"]
    class C_0010330400419319200686 {
        +call(const vec&lt;3,T,Q&gt; & a, const vec&lt;3,T,Q&gt; & b) [constexpr] T$
    }
    class C_0006174179673291647203["glm::detail::compute_dot&lt;glm::vec&lt;4,T,Q&gt;,T,Aligned&gt;"]
    class C_0006174179673291647203 {
        +call(const vec&lt;4,T,Q&gt; & a, const vec&lt;4,T,Q&gt; & b) [constexpr] T$
    }
    class C_0015824183364641647648["glm::detail::compute_cross&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0015824183364641647648 {
        +call(const vec&lt;3,T,Q&gt; & x, const vec&lt;3,T,Q&gt; & y) [constexpr] vec&lt;3,T,Q&gt;$
    }
    class C_0009879403532153280824["glm::detail::compute_normalize&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0009879403532153280824 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,T,Q&gt;$
    }
    class C_0012787582606908899191["glm::detail::compute_faceforward&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0012787582606908899191 {
        +call(const vec&lt;L,T,Q&gt; & N, const vec&lt;L,T,Q&gt; & I, const vec&lt;L,T,Q&gt; & Nref) vec&lt;L,T,Q&gt;$
    }
    class C_0005715687668474009820["glm::detail::compute_reflect&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0005715687668474009820 {
        +call(const vec&lt;L,T,Q&gt; & I, const vec&lt;L,T,Q&gt; & N) vec&lt;L,T,Q&gt;$
    }
    class C_0006180436695447720838["glm::detail::compute_refract&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0006180436695447720838 {
        +call(const vec&lt;L,T,Q&gt; & I, const vec&lt;L,T,Q&gt; & N, T eta) vec&lt;L,T,Q&gt;$
    }
    class C_0010249294259649984273["glm::detail::compute_matrixCompMult&lt;length_t C,length_t R,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0010249294259649984273 {
        +call(const mat&lt;C,R,T,Q&gt; & x, const mat&lt;C,R,T,Q&gt; & y) mat&lt;C,R,T,Q&gt;$
    }
    class C_0002202497605370845773["glm::detail::compute_matrixCompMult_type&lt;length_t C,length_t R,T,qualifier Q,_Bool IsFloat,_Bool Aligned&gt;"]
    class C_0002202497605370845773 {
        +call(const mat&lt;C,R,T,Q&gt; & x, const mat&lt;C,R,T,Q&gt; & y) mat&lt;C,R,T,Q&gt;$
    }
    class C_0002764610822168181826["glm::detail::compute_outerProduct&lt;length_t DA,length_t DB,T,qualifier Q&gt;"]
    class C_0002764610822168181826 {
        +call(const vec&lt;DA,T,Q&gt; & c, const vec&lt;DB,T,Q&gt; & r) typename detail::outerProduct_trait&lt;DA,DB,T,Q&gt;::type$
    }
    class C_0005481292911835082602["glm::detail::compute_outerProduct_type&lt;length_t DA,length_t DB,T,qualifier Q,_Bool IsFloat&gt;"]
    class C_0005481292911835082602 {
        +call(const vec&lt;DA,T,Q&gt; & c, const vec&lt;DB,T,Q&gt; & r) typename detail::outerProduct_trait&lt;DA,DB,T,Q&gt;::type$
    }
    class C_0015729851752530164593["glm::detail::compute_transpose&lt;length_t C,length_t R,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0015729851752530164593 {
    }
    class C_0007881146451740919032["glm::detail::compute_transpose&lt;2,2,T,Q,Aligned&gt;"]
    class C_0007881146451740919032 {
        +call(const mat&lt;2,2,T,Q&gt; & m) mat&lt;2,2,T,Q&gt;$
    }
    class C_0001859500514412013469["glm::detail::compute_transpose&lt;2,3,T,Q,Aligned&gt;"]
    class C_0001859500514412013469 {
        +call(const mat&lt;2,3,T,Q&gt; & m) mat&lt;3,2,T,Q&gt;$
    }
    class C_0007787828887948791922["glm::detail::compute_transpose&lt;2,4,T,Q,Aligned&gt;"]
    class C_0007787828887948791922 {
        +call(const mat&lt;2,4,T,Q&gt; & m) mat&lt;4,2,T,Q&gt;$
    }
    class C_0004098227419831323395["glm::detail::compute_transpose&lt;3,2,T,Q,Aligned&gt;"]
    class C_0004098227419831323395 {
        +call(const mat&lt;3,2,T,Q&gt; & m) mat&lt;2,3,T,Q&gt;$
    }
    class C_0008188330762772437840["glm::detail::compute_transpose&lt;3,3,T,Q,Aligned&gt;"]
    class C_0008188330762772437840 {
        +call(const mat&lt;3,3,T,Q&gt; & m) mat&lt;3,3,T,Q&gt;$
    }
    class C_0009013912562976277181["glm::detail::compute_transpose&lt;3,4,T,Q,Aligned&gt;"]
    class C_0009013912562976277181 {
        +call(const mat&lt;3,4,T,Q&gt; & m) mat&lt;4,3,T,Q&gt;$
    }
    class C_0001558861689450681704["glm::detail::compute_transpose&lt;4,2,T,Q,Aligned&gt;"]
    class C_0001558861689450681704 {
        +call(const mat&lt;4,2,T,Q&gt; & m) mat&lt;2,4,T,Q&gt;$
    }
    class C_0003029586384935255756["glm::detail::compute_transpose&lt;4,3,T,Q,Aligned&gt;"]
    class C_0003029586384935255756 {
        +call(const mat&lt;4,3,T,Q&gt; & m) mat&lt;3,4,T,Q&gt;$
    }
    class C_0005400345805634604952["glm::detail::compute_transpose&lt;4,4,T,Q,Aligned&gt;"]
    class C_0005400345805634604952 {
        +call(const mat&lt;4,4,T,Q&gt; & m) mat&lt;4,4,T,Q&gt;$
    }
    class C_0004291393052584190979["glm::detail::compute_transpose_type&lt;length_t C,length_t R,T,qualifier Q,_Bool IsFloat,_Bool Aligned&gt;"]
    class C_0004291393052584190979 {
        +call(const mat&lt;C,R,T,Q&gt; & m) mat&lt;R,C,T,Q&gt;$
    }
    class C_0002216603726385707142["glm::detail::compute_determinant&lt;length_t C,length_t R,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0002216603726385707142 {
    }
    class C_0004603505941396452095["glm::detail::compute_determinant&lt;2,2,T,Q,Aligned&gt;"]
    class C_0004603505941396452095 {
        +call(const mat&lt;2,2,T,Q&gt; & m) T$
    }
    class C_0008544802141356008321["glm::detail::compute_determinant&lt;3,3,T,Q,Aligned&gt;"]
    class C_0008544802141356008321 {
        +call(const mat&lt;3,3,T,Q&gt; & m) T$
    }
    class C_0017355783167375359772["glm::detail::compute_determinant&lt;4,4,T,Q,Aligned&gt;"]
    class C_0017355783167375359772 {
        +call(const mat&lt;4,4,T,Q&gt; & m) T$
    }
    class C_0002490239562282425209["glm::detail::compute_determinant_type&lt;length_t C,length_t R,T,qualifier Q,_Bool IsFloat,_Bool Aligned&gt;"]
    class C_0002490239562282425209 {
        +call(const mat&lt;C,R,T,Q&gt; & m) T$
    }
    class C_0005825466840221447692["glm::detail::compute_inverse&lt;length_t C,length_t R,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0005825466840221447692 {
    }
    class C_0013007929996164545106["glm::detail::compute_inverse&lt;2,2,T,Q,Aligned&gt;"]
    class C_0013007929996164545106 {
        +call(const mat&lt;2,2,T,Q&gt; & m) mat&lt;2,2,T,Q&gt;$
    }
    class C_0007409851143889663669["glm::detail::compute_inverse&lt;3,3,T,Q,Aligned&gt;"]
    class C_0007409851143889663669 {
        +call(const mat&lt;3,3,T,Q&gt; & m) mat&lt;3,3,T,Q&gt;$
    }
    class C_0013263891568124544845["glm::detail::compute_inverse&lt;4,4,T,Q,Aligned&gt;"]
    class C_0013263891568124544845 {
        +call(const mat&lt;4,4,T,Q&gt; & m) mat&lt;4,4,T,Q&gt;$
    }
    class C_0017444295161574729351["glm::detail::uif32"]
    class C_0017444295161574729351 {
        +uif32() void
        +uif32(float f_) void
        +uif32(unsigned int i_) void
        +f : float
        +i : unsigned int
    }
    class C_0013552931000080767045["glm::detail::compute_bitfieldReverseStep&lt;length_t L,T,qualifier Q,_Bool Aligned,_Bool EXEC&gt;"]
    class C_0013552931000080767045 {
        +call(const vec&lt;L,T,Q&gt; & v, T, T) vec&lt;L,T,Q&gt;$
    }
    class C_0008368078235790091494["glm::detail::compute_bitfieldReverseStep&lt;L,T,Q,Aligned,true&gt;"]
    class C_0008368078235790091494 {
        +call(const vec&lt;L,T,Q&gt; & v, T Mask, T Shift) vec&lt;L,T,Q&gt;$
    }
    class C_0000410803817831491586["glm::detail::compute_bitfieldBitCountStep&lt;length_t L,T,qualifier Q,_Bool Aligned,_Bool EXEC&gt;"]
    class C_0000410803817831491586 {
        +call(const vec&lt;L,T,Q&gt; & v, T, T) vec&lt;L,T,Q&gt;$
    }
    class C_0015671549293778163470["glm::detail::compute_bitfieldBitCountStep&lt;L,T,Q,Aligned,true&gt;"]
    class C_0015671549293778163470 {
        +call(const vec&lt;L,T,Q&gt; & v, T Mask, T Shift) vec&lt;L,T,Q&gt;$
    }
    class C_0015054806346576091858["glm::detail::compute_findLSB&lt;genIUType,size_t Bits&gt;"]
    class C_0015054806346576091858 {
        +call(genIUType Value) int$
    }
    class C_0008456521682378646313["glm::detail::compute_findMSB_step_vec&lt;length_t L,T,qualifier Q,_Bool EXEC=true&gt;"]
    class C_0008456521682378646313 {
        +call(const vec&lt;L,T,Q&gt; & x, T Shift) vec&lt;L,T,Q&gt;$
    }
    class C_0014990534431396726446["glm::detail::compute_findMSB_step_vec&lt;L,T,Q,false&gt;"]
    class C_0014990534431396726446 {
        +call(const vec&lt;L,T,Q&gt; & x, T) vec&lt;L,T,Q&gt;$
    }
    class C_0003443302256699892724["glm::detail::compute_findMSB_vec&lt;length_t L,T,qualifier Q,int&gt;"]
    class C_0003443302256699892724 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,int,Q&gt;$
    }
    class C_0017854690719509684787["glm::detail::float_t&lt;T&gt;"]
    class C_0017854690719509684787 {
    }
    class C_0001471993262601684536["glm::detail::float_t&lt;float&gt;"]
    class C_0001471993262601684536 {
        +float_t(float_type Num = 0.0f) void
        +operator=(const glm::detail::float_t&lt;float&gt; & x) [constexpr] glm::detail::float_t&lt;float&gt; &
        +exponent() [const,constexpr] int_type
        +mantissa() [const,constexpr] int_type
        +negative() [const,constexpr] bool
        +f : float_type
        +i : int_type
    }
    class C_0008444656603509005298["glm::detail::float_t&lt;double&gt;"]
    class C_0008444656603509005298 {
        +float_t(float_type Num = static_cast&lt;float_type&gt;&lpar;0&rpar;) void
        +operator=(const glm::detail::float_t&lt;double&gt; & x) [constexpr] glm::detail::float_t&lt;double&gt; &
        +exponent() [const,constexpr] int_type
        +mantissa() [const,constexpr] int_type
        +negative() [const,constexpr] bool
        +f : float_type
        +i : int_type
    }
    class C_0014602532577836950841["glm::detail::genTypeTrait&lt;glm::qua&lt;T,glm::packed_highp&gt;&gt;"]
    class C_0014602532577836950841 {
        +GENTYPE : const genTypeEnum
    }
    class C_0017575668200705778502["glm::detail::compute_dot&lt;glm::qua&lt;T,Q&gt;,T,Aligned&gt;"]
    class C_0017575668200705778502 {
        +call(const qua&lt;T,Q&gt; & a, const qua&lt;T,Q&gt; & b) [constexpr] T$
    }
    class C_0017282521853691103935["glm::detail::compute_quat_add&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0017282521853691103935 {
        +call(const qua&lt;T,Q&gt; & q, const qua&lt;T,Q&gt; & p) [constexpr] qua&lt;T,Q&gt;$
    }
    class C_0012617079442092803171["glm::detail::compute_quat_sub&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0012617079442092803171 {
        +call(const qua&lt;T,Q&gt; & q, const qua&lt;T,Q&gt; & p) [constexpr] qua&lt;T,Q&gt;$
    }
    class C_0018394432602105543406["glm::detail::compute_quat_mul_scalar&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0018394432602105543406 {
        +call(const qua&lt;T,Q&gt; & q, T s) [constexpr] qua&lt;T,Q&gt;$
    }
    class C_0002124913055560694229["glm::detail::compute_quat_div_scalar&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0002124913055560694229 {
        +call(const qua&lt;T,Q&gt; & q, T s) [constexpr] qua&lt;T,Q&gt;$
    }
    class C_0008668887570412326500["glm::detail::compute_quat_mul_vec4&lt;T,qualifier Q,_Bool Aligned&gt;"]
    class C_0008668887570412326500 {
        +call(const qua&lt;T,Q&gt; & q, const vec&lt;4,T,Q&gt; & v) [constexpr] vec&lt;4,T,Q&gt;$
    }
    class C_0011439403360356034938["glm::detail::compute_compNormalize&lt;length_t L,T,floatType,qualifier Q,_Bool isInteger,_Bool signedType&gt;"]
    class C_0011439403360356034938 {
    }
    class C_0015411313640123734523["glm::detail::compute_compNormalize&lt;L,T,floatType,Q,true,true&gt;"]
    class C_0015411313640123734523 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,floatType,Q&gt;$
    }
    class C_0011784441873711350910["glm::detail::compute_compNormalize&lt;L,T,floatType,Q,true,false&gt;"]
    class C_0011784441873711350910 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,floatType,Q&gt;$
    }
    class C_0014062317156853742088["glm::detail::compute_compNormalize&lt;L,T,floatType,Q,false,true&gt;"]
    class C_0014062317156853742088 {
        +call(const vec&lt;L,T,Q&gt; & v) vec&lt;L,floatType,Q&gt;$
    }
    class C_0000051730753218865182["glm::detail::compute_compScale&lt;length_t L,T,floatType,qualifier Q,_Bool isInteger,_Bool signedType&gt;"]
    class C_0000051730753218865182 {
    }
    class C_0009544353725842918078["glm::detail::compute_compScale&lt;L,T,floatType,Q,true,true&gt;"]
    class C_0009544353725842918078 {
        +call(const vec&lt;L,floatType,Q&gt; & v) vec&lt;L,T,Q&gt;$
    }
    class C_0017541291380119939604["glm::detail::compute_compScale&lt;L,T,floatType,Q,true,false&gt;"]
    class C_0017541291380119939604 {
        +call(const vec&lt;L,floatType,Q&gt; & v) vec&lt;L,T,Q&gt;$
    }
    class C_0009623686183071842245["glm::detail::compute_compScale&lt;L,T,floatType,Q,false,true&gt;"]
    class C_0009623686183071842245 {
        +call(const vec&lt;L,floatType,Q&gt; & v) vec&lt;L,T,Q&gt;$
    }
    class C_0012656140945091034469["glm::detail::compute_length2&lt;length_t L,T,qualifier Q,_Bool Aligned&gt;"]
    class C_0012656140945091034469 {
        +call(const vec&lt;L,T,Q&gt; & v) T$
    }
    class C_0005502540817457157979["glm::detail::compute_rand&lt;length_t L,T,qualifier Q&gt;"]
    class C_0005502540817457157979 {
        +call() vec&lt;L,T,Q&gt;$
    }
    class C_0001603363853034486258["glm::detail::compute_rand&lt;1,unsigned char,P&gt;"]
    class C_0001603363853034486258 {
        +call() vec&lt;1,uint8,P&gt;$
    }
    class C_0002686830347748380728["glm::detail::compute_rand&lt;2,unsigned char,P&gt;"]
    class C_0002686830347748380728 {
        +call() vec&lt;2,uint8,P&gt;$
    }
    class C_0006090447241121061899["glm::detail::compute_rand&lt;3,unsigned char,P&gt;"]
    class C_0006090447241121061899 {
        +call() vec&lt;3,uint8,P&gt;$
    }
    class C_0001153560176141861826["glm::detail::compute_rand&lt;4,unsigned char,P&gt;"]
    class C_0001153560176141861826 {
        +call() vec&lt;4,uint8,P&gt;$
    }
    class C_0008574170526380206673["glm::detail::compute_rand&lt;L,unsigned short,Q&gt;"]
    class C_0008574170526380206673 {
        +call() vec&lt;L,uint16,Q&gt;$
    }
    class C_0009720305886431815002["glm::detail::compute_rand&lt;L,unsigned int,Q&gt;"]
    class C_0009720305886431815002 {
        +call() vec&lt;L,uint32,Q&gt;$
    }
    class C_0005069809328701172009["glm::detail::compute_rand&lt;L,unsigned long long,Q&gt;"]
    class C_0005069809328701172009 {
        +call() vec&lt;L,uint64,Q&gt;$
    }
    class C_0000785490213154692308["glm::detail::compute_linearRand&lt;length_t L,T,qualifier Q&gt;"]
    class C_0000785490213154692308 {
        +call(const vec&lt;L,T,Q&gt; & Min, const vec&lt;L,T,Q&gt; & Max) vec&lt;L,T,Q&gt;$
    }
    class C_0005512908233036887058["glm::detail::compute_linearRand&lt;L,signed char,Q&gt;"]
    class C_0005512908233036887058 {
        +call(const vec&lt;L,int8,Q&gt; & Min, const vec&lt;L,int8,Q&gt; & Max) vec&lt;L,int8,Q&gt;$
    }
    class C_0002483196794121134757["glm::detail::compute_linearRand&lt;L,unsigned char,Q&gt;"]
    class C_0002483196794121134757 {
        +call(const vec&lt;L,uint8,Q&gt; & Min, const vec&lt;L,uint8,Q&gt; & Max) vec&lt;L,uint8,Q&gt;$
    }
    class C_0000159143745571817136["glm::detail::compute_linearRand&lt;L,short,Q&gt;"]
    class C_0000159143745571817136 {
        +call(const vec&lt;L,int16,Q&gt; & Min, const vec&lt;L,int16,Q&gt; & Max) vec&lt;L,int16,Q&gt;$
    }
    class C_0007520649107592933480["glm::detail::compute_linearRand&lt;L,unsigned short,Q&gt;"]
    class C_0007520649107592933480 {
        +call(const vec&lt;L,uint16,Q&gt; & Min, const vec&lt;L,uint16,Q&gt; & Max) vec&lt;L,uint16,Q&gt;$
    }
    class C_0008964589233154078681["glm::detail::compute_linearRand&lt;L,int,Q&gt;"]
    class C_0008964589233154078681 {
        +call(const vec&lt;L,int32,Q&gt; & Min, const vec&lt;L,int32,Q&gt; & Max) vec&lt;L,int32,Q&gt;$
    }
    class C_0015417027955790789238["glm::detail::compute_linearRand&lt;L,unsigned int,Q&gt;"]
    class C_0015417027955790789238 {
        +call(const vec&lt;L,uint32,Q&gt; & Min, const vec&lt;L,uint32,Q&gt; & Max) vec&lt;L,uint32,Q&gt;$
    }
    class C_0014423018035884627438["glm::detail::compute_linearRand&lt;L,long long,Q&gt;"]
    class C_0014423018035884627438 {
        +call(const vec&lt;L,int64,Q&gt; & Min, const vec&lt;L,int64,Q&gt; & Max) vec&lt;L,int64,Q&gt;$
    }
    class C_0007865373373365576150["glm::detail::compute_linearRand&lt;L,unsigned long long,Q&gt;"]
    class C_0007865373373365576150 {
        +call(const vec&lt;L,uint64,Q&gt; & Min, const vec&lt;L,uint64,Q&gt; & Max) vec&lt;L,uint64,Q&gt;$
    }
    class C_0013698864996950055508["glm::detail::compute_linearRand&lt;L,float,Q&gt;"]
    class C_0013698864996950055508 {
        +call(const vec&lt;L,float,Q&gt; & Min, const vec&lt;L,float,Q&gt; & Max) vec&lt;L,float,Q&gt;$
    }
    class C_0003925512995191256877["glm::detail::compute_linearRand&lt;L,double,Q&gt;"]
    class C_0003925512995191256877 {
        +call(const vec&lt;L,double,Q&gt; & Min, const vec&lt;L,double,Q&gt; & Max) vec&lt;L,double,Q&gt;$
    }
    class C_0010178100644696197769["glm::detail::compute_linearRand&lt;L,long double,Q&gt;"]
    class C_0010178100644696197769 {
        +call(const vec&lt;L,long double,Q&gt; & Min, const vec&lt;L,long double,Q&gt; & Max) vec&lt;L,long double,Q&gt;$
    }
    class C_0012955433994405249287["glm::qualifier"]
    class C_0012955433994405249287 {
        <<enumeration>>
        packed_highp
        packed_mediump
        packed_lowp
        highp
        mediump
        lowp
        packed
        defaultp
    }
    class C_0006992479837074144199["glm::vec&lt;1,T,Q&gt;"]
    class C_0006992479837074144199 {
        +vec() [default] void
        +vec(const vec&lt;1,T,Q&gt; & v) [default] void
        +vec(T scalar) void
        +vec<qualifier P>(const vec&lt;1,T,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;2,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;3,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;4,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;1,U,P&gt; & v) void
        +operator=(const vec&lt;1,T,Q&gt; & v) [default,constexpr] vec&lt;1,T,Q&gt; &
        +operator<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator%=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator%=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator&=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator&=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator*=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator*=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator++() [constexpr] vec&lt;1,T,Q&gt; &
        +operator++(int) [constexpr] vec&lt;1,T,Q&gt;
        +operator+=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator+=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator--() [constexpr] vec&lt;1,T,Q&gt; &
        +operator--(int) [constexpr] vec&lt;1,T,Q&gt;
        +operator-=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator-=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator/=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator/=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator>>=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator>>=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator[](length_type i) [const,constexpr] const T &
        +operator[](length_type i) [constexpr] T &
        +operator^=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +operator^=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator|=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;1, T, Q&gt; &
        +operator|=<U>(U scalar) [constexpr] vec&lt;1, T, Q&gt; &
        +length() [constexpr] length_type$
        + : vec::&lpar;&rpar;
    }
    class C_0017729851466359107363["glm::vec&lt;2,T,Q&gt;"]
    class C_0017729851466359107363 {
        +vec() [default] void
        +vec(const vec&lt;2,T,Q&gt; & v) [default] void
        +vec(T scalar) void
        +vec(T x, T y) void
        +vec<qualifier P>(const vec&lt;2,T,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;1,U,P&gt; & v) void
        +vec<A,B>(A x, B y) void
        +vec<A,B>(const vec&lt;1,A,Q&gt; & x, B y) void
        +vec<A,B>(A x, const vec&lt;1,B,Q&gt; & y) void
        +vec<A,B>(const vec&lt;1,A,Q&gt; & x, const vec&lt;1,B,Q&gt; & y) void
        +vec<U,qualifier P>(const vec&lt;3,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;4,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;2,U,P&gt; & v) void
        +operator=(const vec&lt;2,T,Q&gt; & v) [default,constexpr] vec&lt;2,T,Q&gt; &
        +operator<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator%=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator%=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator%=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator&=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator&=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator&=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator*=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator*=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator*=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator++(int) [constexpr] vec&lt;2,T,Q&gt;
        +operator++() [constexpr] vec&lt;2,T,Q&gt; &
        +operator+=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator+=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator+=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator--(int) [constexpr] vec&lt;2,T,Q&gt;
        +operator--() [constexpr] vec&lt;2,T,Q&gt; &
        +operator-=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator-=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator-=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator/=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator/=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator/=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator>>=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator>>=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator>>=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator[](length_type i) [const,constexpr] const T &
        +operator[](length_type i) [constexpr] T &
        +operator^=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +operator^=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator^=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator|=<U>(const vec&lt;2,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator|=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;2, T, Q&gt; &
        +operator|=<U>(U scalar) [constexpr] vec&lt;2, T, Q&gt; &
        +length() [constexpr] length_type$
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
    }
    class C_0013826567149110357089["glm::vec&lt;3,T,Q&gt;"]
    class C_0013826567149110357089 {
        +vec() [default] void
        +vec(const vec&lt;3,T,Q&gt; & v) [default] void
        +vec(T scalar) void
        +vec(T a, T b, T c) void
        +vec<qualifier P>(const vec&lt;3,T,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;1,U,P&gt; & v) void
        +vec<X,Y,Z>(X x, Y y, Z z) void
        +vec<X,Y,Z>(const vec&lt;1,X,Q&gt; & _x, Y _y, Z _z) void
        +vec<X,Y,Z>(X _x, const vec&lt;1,Y,Q&gt; & _y, Z _z) void
        +vec<X,Y,Z>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _y, Z _z) void
        +vec<X,Y,Z>(X _x, Y _y, const vec&lt;1,Z,Q&gt; & _z) void
        +vec<X,Y,Z>(const vec&lt;1,X,Q&gt; & _x, Y _y, const vec&lt;1,Z,Q&gt; & _z) void
        +vec<X,Y,Z>(X _x, const vec&lt;1,Y,Q&gt; & _y, const vec&lt;1,Z,Q&gt; & _z) void
        +vec<X,Y,Z>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _y, const vec&lt;1,Z,Q&gt; & _z) void
        +vec<A,B,qualifier P>(const vec&lt;2,A,P&gt; & _xy, B _z) void
        +vec<A,B,qualifier P>(const vec&lt;2,A,P&gt; & _xy, const vec&lt;1,B,P&gt; & _z) void
        +vec<A,B,qualifier P>(A _x, const vec&lt;2,B,P&gt; & _yz) void
        +vec<A,B,qualifier P>(const vec&lt;1,A,P&gt; & _x, const vec&lt;2,B,P&gt; & _yz) void
        +vec<U,qualifier P>(const vec&lt;4,U,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;3,U,P&gt; & v) void
        +operator=(const vec&lt;3,T,Q&gt; & v) [default,constexpr] vec&lt;3,T,Q&gt; &
        +operator<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator%=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator%=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator%=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator&=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator&=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator&=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator*=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator*=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator*=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator++(int) [constexpr] vec&lt;3,T,Q&gt;
        +operator++() [constexpr] vec&lt;3,T,Q&gt; &
        +operator+=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator+=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator+=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator--(int) [constexpr] vec&lt;3,T,Q&gt;
        +operator--() [constexpr] vec&lt;3,T,Q&gt; &
        +operator-=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator-=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator-=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator/=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator/=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator/=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator>>=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator>>=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator>>=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator[](length_type i) [const,constexpr] const T &
        +operator[](length_type i) [constexpr] T &
        +operator^=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +operator^=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator^=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator|=<U>(const vec&lt;3,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator|=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;3, T, Q&gt; &
        +operator|=<U>(U scalar) [constexpr] vec&lt;3, T, Q&gt; &
        +length() [constexpr] length_type$
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
    }
    class C_0015117083025601782618["glm::vec&lt;4,T,Q&gt;"]
    class C_0015117083025601782618 {
        +vec() [default] void
        +vec(const vec&lt;4,T,Q&gt; & v) [default] void
        +vec(T scalar) void
        +vec(T x, T y, T z, T w) void
        +vec<qualifier P>(const vec&lt;4,T,P&gt; & v) void
        +vec<U,qualifier P>(const vec&lt;1,U,P&gt; & v) void
        +vec<X,Y,Z,W>(X _x, Y _y, Z _z, W _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, Y _y, Z _z, W _w) void
        +vec<X,Y,Z,W>(X _x, const vec&lt;1,Y,Q&gt; & _y, Z _z, W _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _y, Z _z, W _w) void
        +vec<X,Y,Z,W>(X _x, Y _y, const vec&lt;1,Z,Q&gt; & _z, W _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, Y _y, const vec&lt;1,Z,Q&gt; & _z, W _w) void
        +vec<X,Y,Z,W>(X _x, const vec&lt;1,Y,Q&gt; & _y, const vec&lt;1,Z,Q&gt; & _z, W _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _y, const vec&lt;1,Z,Q&gt; & _z, W _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, Y _y, Z _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(X _x, const vec&lt;1,Y,Q&gt; & _y, Z _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _y, Z _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(X _x, Y _y, const vec&lt;1,Z,Q&gt; & _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, Y _y, const vec&lt;1,Z,Q&gt; & _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(X _x, const vec&lt;1,Y,Q&gt; & _y, const vec&lt;1,Z,Q&gt; & _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<X,Y,Z,W>(const vec&lt;1,X,Q&gt; & _x, const vec&lt;1,Y,Q&gt; & _Y, const vec&lt;1,Z,Q&gt; & _z, const vec&lt;1,W,Q&gt; & _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;2,A,P&gt; & _xy, B _z, C _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;2,A,P&gt; & _xy, const vec&lt;1,B,P&gt; & _z, C _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;2,A,P&gt; & _xy, B _z, const vec&lt;1,C,P&gt; & _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;2,A,P&gt; & _xy, const vec&lt;1,B,P&gt; & _z, const vec&lt;1,C,P&gt; & _w) void
        +vec<A,B,C,qualifier P>(A _x, const vec&lt;2,B,P&gt; & _yz, C _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;1,A,P&gt; & _x, const vec&lt;2,B,P&gt; & _yz, C _w) void
        +vec<A,B,C,qualifier P>(A _x, const vec&lt;2,B,P&gt; & _yz, const vec&lt;1,C,P&gt; & _w) void
        +vec<A,B,C,qualifier P>(const vec&lt;1,A,P&gt; & _x, const vec&lt;2,B,P&gt; & _yz, const vec&lt;1,C,P&gt; & _w) void
        +vec<A,B,C,qualifier P>(A _x, B _y, const vec&lt;2,C,P&gt; & _zw) void
        +vec<A,B,C,qualifier P>(const vec&lt;1,A,P&gt; & _x, B _y, const vec&lt;2,C,P&gt; & _zw) void
        +vec<A,B,C,qualifier P>(A _x, const vec&lt;1,B,P&gt; & _y, const vec&lt;2,C,P&gt; & _zw) void
        +vec<A,B,C,qualifier P>(const vec&lt;1,A,P&gt; & _x, const vec&lt;1,B,P&gt; & _y, const vec&lt;2,C,P&gt; & _zw) void
        +vec<A,B,qualifier P>(const vec&lt;3,A,P&gt; & _xyz, B _w) void
        +vec<A,B,qualifier P>(const vec&lt;3,A,P&gt; & _xyz, const vec&lt;1,B,P&gt; & _w) void
        +vec<A,B,qualifier P>(A _x, const vec&lt;3,B,P&gt; & _yzw) void
        +vec<A,B,qualifier P>(const vec&lt;1,A,P&gt; & _x, const vec&lt;3,B,P&gt; & _yzw) void
        +vec<A,B,qualifier P>(const vec&lt;2,A,P&gt; & _xy, const vec&lt;2,B,P&gt; & _zw) void
        +vec<U,qualifier P>(const vec&lt;4,U,P&gt; & v) void
        +operator=(const vec&lt;4,T,Q&gt; & v) [default,constexpr] vec&lt;4,T,Q&gt; &
        +operator<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator%=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator%=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator%=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator&=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator&=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator&=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator*=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator*=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator*=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator++(int) [constexpr] vec&lt;4,T,Q&gt;
        +operator++() [constexpr] vec&lt;4,T,Q&gt; &
        +operator+=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator+=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator+=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator--(int) [constexpr] vec&lt;4,T,Q&gt;
        +operator--() [constexpr] vec&lt;4,T,Q&gt; &
        +operator-=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator-=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator-=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator/=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator/=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator/=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator>>=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator>>=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator>>=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator[](length_type i) [const,constexpr] const T &
        +operator[](length_type i) [constexpr] T &
        +operator^=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +operator^=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator^=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator|=<U>(const vec&lt;4,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator|=<U>(const vec&lt;1,U,Q&gt; & v) [constexpr] vec&lt;4, T, Q&gt; &
        +operator|=<U>(U scalar) [constexpr] vec&lt;4, T, Q&gt; &
        +length() [constexpr] length_type$
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
        + : vec::&lpar;&rpar;
    }
    class C_0007482356929151537282["glm::mat&lt;2,2,T,Q&gt;"]
    class C_0007482356929151537282 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(const T & x1, const T & y1, const T & x2, const T & y2) void
        +mat(const col_type & v1, const col_type & v2) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;2,2,T,P&gt; & m) void
        +mat<U,V,M,N>(const U & x1, const V & y1, const M & x2, const N & y2) void
        +mat<U,V>(const vec&lt;2,U,Q&gt; & v1, const vec&lt;2,V,Q&gt; & v2) void
        +mat<U,qualifier P>(const mat&lt;2,2,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;2, 2, T, Q&gt; &
        +operator*=<U>(const mat&lt;2,2,U,Q&gt; & m) mat&lt;2, 2, T, Q&gt; &
        +operator++() mat&lt;2,2,T,Q&gt; &
        +operator++(int) mat&lt;2,2,T,Q&gt;
        +operator+=<U>(U s) mat&lt;2, 2, T, Q&gt; &
        +operator+=<U>(const mat&lt;2,2,U,Q&gt; & m) mat&lt;2, 2, T, Q&gt; &
        +operator--() mat&lt;2,2,T,Q&gt; &
        +operator--(int) mat&lt;2,2,T,Q&gt;
        +operator-=<U>(U s) mat&lt;2, 2, T, Q&gt; &
        +operator-=<U>(const mat&lt;2,2,U,Q&gt; & m) mat&lt;2, 2, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;2, 2, T, Q&gt; &
        +operator/=<U>(const mat&lt;2,2,U,Q&gt; & m) mat&lt;2, 2, T, Q&gt; &
        +operator=<U>(const mat&lt;2,2,U,Q&gt; & m) mat&lt;2, 2, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[2]
    }
    class C_0016370386407813495429["glm::mat&lt;2,3,T,Q&gt;"]
    class C_0016370386407813495429 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T z0, T x1, T y1, T z1) void
        +mat(const col_type & v0, const col_type & v1) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;2,3,T,P&gt; & m) void
        +mat<X1,Y1,Z1,X2,Y2,Z2>(X1 x1, Y1 y1, Z1 z1, X2 x2, Y2 y2, Z2 z2) void
        +mat<U,V>(const vec&lt;3,U,Q&gt; & v1, const vec&lt;3,V,Q&gt; & v2) void
        +mat<U,qualifier P>(const mat&lt;2,3,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;2, 3, T, Q&gt; &
        +operator++() mat&lt;2,3,T,Q&gt; &
        +operator++(int) mat&lt;2,3,T,Q&gt;
        +operator+=<U>(U s) mat&lt;2, 3, T, Q&gt; &
        +operator+=<U>(const mat&lt;2,3,U,Q&gt; & m) mat&lt;2, 3, T, Q&gt; &
        +operator--() mat&lt;2,3,T,Q&gt; &
        +operator--(int) mat&lt;2,3,T,Q&gt;
        +operator-=<U>(U s) mat&lt;2, 3, T, Q&gt; &
        +operator-=<U>(const mat&lt;2,3,U,Q&gt; & m) mat&lt;2, 3, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;2, 3, T, Q&gt; &
        +operator=<U>(const mat&lt;2,3,U,Q&gt; & m) mat&lt;2, 3, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[2]
    }
    class C_0003496176270941337858["glm::mat&lt;2,4,T,Q&gt;"]
    class C_0003496176270941337858 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1) void
        +mat(const col_type & v0, const col_type & v1) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;2,4,T,P&gt; & m) void
        +mat<X1,Y1,Z1,W1,X2,Y2,Z2,W2>(X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2, Z2 z2, W2 w2) void
        +mat<U,V>(const vec&lt;4,U,Q&gt; & v1, const vec&lt;4,V,Q&gt; & v2) void
        +mat<U,qualifier P>(const mat&lt;2,4,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;2, 4, T, Q&gt; &
        +operator++() mat&lt;2,4,T,Q&gt; &
        +operator++(int) mat&lt;2,4,T,Q&gt;
        +operator+=<U>(U s) mat&lt;2, 4, T, Q&gt; &
        +operator+=<U>(const mat&lt;2,4,U,Q&gt; & m) mat&lt;2, 4, T, Q&gt; &
        +operator--() mat&lt;2,4,T,Q&gt; &
        +operator--(int) mat&lt;2,4,T,Q&gt;
        +operator-=<U>(U s) mat&lt;2, 4, T, Q&gt; &
        +operator-=<U>(const mat&lt;2,4,U,Q&gt; & m) mat&lt;2, 4, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;2, 4, T, Q&gt; &
        +operator=<U>(const mat&lt;2,4,U,Q&gt; & m) mat&lt;2, 4, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[2]
    }
    class C_0002644064770012110766["glm::mat&lt;3,2,T,Q&gt;"]
    class C_0002644064770012110766 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T x1, T y1, T x2, T y2) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;3,2,T,P&gt; & m) void
        +mat<X1,Y1,X2,Y2,X3,Y3>(X1 x1, Y1 y1, X2 x2, Y2 y2, X3 x3, Y3 y3) void
        +mat<V1,V2,V3>(const vec&lt;2,V1,Q&gt; & v1, const vec&lt;2,V2,Q&gt; & v2, const vec&lt;2,V3,Q&gt; & v3) void
        +mat<U,qualifier P>(const mat&lt;3,2,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;3, 2, T, Q&gt; &
        +operator++() mat&lt;3,2,T,Q&gt; &
        +operator++(int) mat&lt;3,2,T,Q&gt;
        +operator+=<U>(U s) mat&lt;3, 2, T, Q&gt; &
        +operator+=<U>(const mat&lt;3,2,U,Q&gt; & m) mat&lt;3, 2, T, Q&gt; &
        +operator--() mat&lt;3,2,T,Q&gt; &
        +operator--(int) mat&lt;3,2,T,Q&gt;
        +operator-=<U>(U s) mat&lt;3, 2, T, Q&gt; &
        +operator-=<U>(const mat&lt;3,2,U,Q&gt; & m) mat&lt;3, 2, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;3, 2, T, Q&gt; &
        +operator=<U>(const mat&lt;3,2,U,Q&gt; & m) mat&lt;3, 2, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[3]
    }
    class C_0005819674801799086687["glm::mat&lt;3,3,T,Q&gt;"]
    class C_0005819674801799086687 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T z0, T x1, T y1, T z1, T x2, T y2, T z2) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;3,3,T,P&gt; & m) void
        +mat<X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3>(X1 x1, Y1 y1, Z1 z1, X2 x2, Y2 y2, Z2 z2, X3 x3, Y3 y3, Z3 z3) void
        +mat<V1,V2,V3>(const vec&lt;3,V1,Q&gt; & v1, const vec&lt;3,V2,Q&gt; & v2, const vec&lt;3,V3,Q&gt; & v3) void
        +mat<U,qualifier P>(const mat&lt;3,3,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;3, 3, T, Q&gt; &
        +operator*=<U>(const mat&lt;3,3,U,Q&gt; & m) mat&lt;3, 3, T, Q&gt; &
        +operator++() mat&lt;3,3,T,Q&gt; &
        +operator++(int) mat&lt;3,3,T,Q&gt;
        +operator+=<U>(U s) mat&lt;3, 3, T, Q&gt; &
        +operator+=<U>(const mat&lt;3,3,U,Q&gt; & m) mat&lt;3, 3, T, Q&gt; &
        +operator--() mat&lt;3,3,T,Q&gt; &
        +operator--(int) mat&lt;3,3,T,Q&gt;
        +operator-=<U>(U s) mat&lt;3, 3, T, Q&gt; &
        +operator-=<U>(const mat&lt;3,3,U,Q&gt; & m) mat&lt;3, 3, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;3, 3, T, Q&gt; &
        +operator/=<U>(const mat&lt;3,3,U,Q&gt; & m) mat&lt;3, 3, T, Q&gt; &
        +operator=<U>(const mat&lt;3,3,U,Q&gt; & m) mat&lt;3, 3, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[3]
    }
    class C_0011458867993025185835["glm::mat&lt;3,4,T,Q&gt;"]
    class C_0011458867993025185835 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;3,4,T,P&gt; & m) void
        +mat<X1,Y1,Z1,W1,X2,Y2,Z2,W2,X3,Y3,Z3,W3>(X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2, Z2 z2, W2 w2, X3 x3, Y3 y3, Z3 z3, W3 w3) void
        +mat<V1,V2,V3>(const vec&lt;4,V1,Q&gt; & v1, const vec&lt;4,V2,Q&gt; & v2, const vec&lt;4,V3,Q&gt; & v3) void
        +mat<U,qualifier P>(const mat&lt;3,4,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;3, 4, T, Q&gt; &
        +operator++() mat&lt;3,4,T,Q&gt; &
        +operator++(int) mat&lt;3,4,T,Q&gt;
        +operator+=<U>(U s) mat&lt;3, 4, T, Q&gt; &
        +operator+=<U>(const mat&lt;3,4,U,Q&gt; & m) mat&lt;3, 4, T, Q&gt; &
        +operator--() mat&lt;3,4,T,Q&gt; &
        +operator--(int) mat&lt;3,4,T,Q&gt;
        +operator-=<U>(U s) mat&lt;3, 4, T, Q&gt; &
        +operator-=<U>(const mat&lt;3,4,U,Q&gt; & m) mat&lt;3, 4, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;3, 4, T, Q&gt; &
        +operator=<U>(const mat&lt;3,4,U,Q&gt; & m) mat&lt;3, 4, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[3]
    }
    class C_0005160671499566832302["glm::mat&lt;4,2,T,Q&gt;"]
    class C_0005160671499566832302 {
        +mat() [default] void
        +mat(T scalar) void
        +mat(T x0, T y0, T x1, T y1, T x2, T y2, T x3, T y3) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2, const col_type & v3) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;4,2,T,P&gt; & m) void
        +mat<X0,Y0,X1,Y1,X2,Y2,X3,Y3>(X0 x0, Y0 y0, X1 x1, Y1 y1, X2 x2, Y2 y2, X3 x3, Y3 y3) void
        +mat<V1,V2,V3,V4>(const vec&lt;2,V1,Q&gt; & v1, const vec&lt;2,V2,Q&gt; & v2, const vec&lt;2,V3,Q&gt; & v3, const vec&lt;2,V4,Q&gt; & v4) void
        +mat<U,qualifier P>(const mat&lt;4,2,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;4, 2, T, Q&gt; &
        +operator++() mat&lt;4,2,T,Q&gt; &
        +operator++(int) mat&lt;4,2,T,Q&gt;
        +operator+=<U>(U s) mat&lt;4, 2, T, Q&gt; &
        +operator+=<U>(const mat&lt;4,2,U,Q&gt; & m) mat&lt;4, 2, T, Q&gt; &
        +operator--() mat&lt;4,2,T,Q&gt; &
        +operator--(int) mat&lt;4,2,T,Q&gt;
        +operator-=<U>(U s) mat&lt;4, 2, T, Q&gt; &
        +operator-=<U>(const mat&lt;4,2,U,Q&gt; & m) mat&lt;4, 2, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;4, 2, T, Q&gt; &
        +operator=<U>(const mat&lt;4,2,U,Q&gt; & m) mat&lt;4, 2, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[4]
    }
    class C_0013207976060429267904["glm::mat&lt;4,3,T,Q&gt;"]
    class C_0013207976060429267904 {
        +mat() [default] void
        +mat(const T & x) void
        +mat(const T & x0, const T & y0, const T & z0, const T & x1, const T & y1, const T & z1, const T & x2, const T & y2, const T & z2, const T & x3, const T & y3, const T & z3) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2, const col_type & v3) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;4,4,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;4,3,T,P&gt; & m) void
        +mat<X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,X4,Y4,Z4>(const X1 & x1, const Y1 & y1, const Z1 & z1, const X2 & x2, const Y2 & y2, const Z2 & z2, const X3 & x3, const Y3 & y3, const Z3 & z3, const X4 & x4, const Y4 & y4, const Z4 & z4) void
        +mat<V1,V2,V3,V4>(const vec&lt;3,V1,Q&gt; & v1, const vec&lt;3,V2,Q&gt; & v2, const vec&lt;3,V3,Q&gt; & v3, const vec&lt;3,V4,Q&gt; & v4) void
        +mat<U,qualifier P>(const mat&lt;4,3,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;4, 3, T, Q&gt; &
        +operator++() mat&lt;4,3,T,Q&gt; &
        +operator++(int) mat&lt;4,3,T,Q&gt;
        +operator+=<U>(U s) mat&lt;4, 3, T, Q&gt; &
        +operator+=<U>(const mat&lt;4,3,U,Q&gt; & m) mat&lt;4, 3, T, Q&gt; &
        +operator--() mat&lt;4,3,T,Q&gt; &
        +operator--(int) mat&lt;4,3,T,Q&gt;
        +operator-=<U>(U s) mat&lt;4, 3, T, Q&gt; &
        +operator-=<U>(const mat&lt;4,3,U,Q&gt; & m) mat&lt;4, 3, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;4, 3, T, Q&gt; &
        +operator=<U>(const mat&lt;4,3,U,Q&gt; & m) mat&lt;4, 3, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[4]
    }
    class C_0011146366150305476558["glm::mat&lt;4,4,T,Q&gt;"]
    class C_0011146366150305476558 {
        +mat() [default] void
        +mat(const T & x) void
        +mat(const T & x0, const T & y0, const T & z0, const T & w0, const T & x1, const T & y1, const T & z1, const T & w1, const T & x2, const T & y2, const T & z2, const T & w2, const T & x3, const T & y3, const T & z3, const T & w3) void
        +mat(const col_type & v0, const col_type & v1, const col_type & v2, const col_type & v3) void
        +mat(const mat&lt;2,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,3,T,Q&gt; & x) void
        +mat(const mat&lt;2,3,T,Q&gt; & x) void
        +mat(const mat&lt;3,2,T,Q&gt; & x) void
        +mat(const mat&lt;2,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,2,T,Q&gt; & x) void
        +mat(const mat&lt;3,4,T,Q&gt; & x) void
        +mat(const mat&lt;4,3,T,Q&gt; & x) void
        +mat<qualifier P>(const mat&lt;4,4,T,P&gt; & m) void
        +mat<X1,Y1,Z1,W1,X2,Y2,Z2,W2,X3,Y3,Z3,W3,X4,Y4,Z4,W4>(const X1 & x1, const Y1 & y1, const Z1 & z1, const W1 & w1, const X2 & x2, const Y2 & y2, const Z2 & z2, const W2 & w2, const X3 & x3, const Y3 & y3, const Z3 & z3, const W3 & w3, const X4 & x4, const Y4 & y4, const Z4 & z4, const W4 & w4) void
        +mat<V1,V2,V3,V4>(const vec&lt;4,V1,Q&gt; & v1, const vec&lt;4,V2,Q&gt; & v2, const vec&lt;4,V3,Q&gt; & v3, const vec&lt;4,V4,Q&gt; & v4) void
        +mat<U,qualifier P>(const mat&lt;4,4,U,P&gt; & m) void
        +operator*=<U>(U s) mat&lt;4, 4, T, Q&gt; &
        +operator*=<U>(const mat&lt;4,4,U,Q&gt; & m) mat&lt;4, 4, T, Q&gt; &
        +operator++() mat&lt;4,4,T,Q&gt; &
        +operator++(int) mat&lt;4,4,T,Q&gt;
        +operator+=<U>(U s) mat&lt;4, 4, T, Q&gt; &
        +operator+=<U>(const mat&lt;4,4,U,Q&gt; & m) mat&lt;4, 4, T, Q&gt; &
        +operator--() mat&lt;4,4,T,Q&gt; &
        +operator--(int) mat&lt;4,4,T,Q&gt;
        +operator-=<U>(U s) mat&lt;4, 4, T, Q&gt; &
        +operator-=<U>(const mat&lt;4,4,U,Q&gt; & m) mat&lt;4, 4, T, Q&gt; &
        +operator/=<U>(U s) mat&lt;4, 4, T, Q&gt; &
        +operator/=<U>(const mat&lt;4,4,U,Q&gt; & m) mat&lt;4, 4, T, Q&gt; &
        +operator=<U>(const mat&lt;4,4,U,Q&gt; & m) mat&lt;4, 4, T, Q&gt; &
        +operator[](length_type i) col_type &
        +operator[](length_type i) [const,constexpr] const col_type &
        +length() [constexpr] length_type$
        -value : col_type[4]
    }
    class C_0011188896363051785620["glm::qua&lt;T,Q&gt;"]
    class C_0011188896363051785620 {
    }
    class C_0008671907212119285262["glm::mat&lt;C,R,T,glm::packed_highp&gt;"]
    class C_0008671907212119285262 {
    }
    class C_0002680935233270452008["glm::vec&lt;2,T,P&gt;"]
    class C_0002680935233270452008 {
    }
    class C_0006233718487001977294["glm::vec&lt;1,U,P&gt;"]
    class C_0006233718487001977294 {
    }
    class C_0007440443376641485314["glm::vec&lt;1,A,Q&gt;"]
    class C_0007440443376641485314 {
    }
    class C_0017297655928961336862["glm::vec&lt;1,B,Q&gt;"]
    class C_0017297655928961336862 {
    }
    class C_0014214357445942724006["glm::vec&lt;3,U,P&gt;"]
    class C_0014214357445942724006 {
    }
    class C_0003647233661022599932["glm::vec&lt;4,U,P&gt;"]
    class C_0003647233661022599932 {
    }
    class C_0009213554402760339732["glm::vec&lt;2,U,P&gt;"]
    class C_0009213554402760339732 {
    }
    class C_0008273115442750733243["glm::vec&lt;2,U,Q&gt;"]
    class C_0008273115442750733243 {
    }
    class C_0007349285277881282082["glm::vec&lt;1,U,Q&gt;"]
    class C_0007349285277881282082 {
    }
    class C_0009674406055978195782["glm::vec::&lpar;&rpar;"]
    class C_0009674406055978195782 {
        +r : T
        +s : T
        +x : T
    }
    class C_0000393330291159126666["glm::vec&lt;3,T,P&gt;"]
    class C_0000393330291159126666 {
    }
    class C_0007738342842735842760["glm::vec&lt;1,X,Q&gt;"]
    class C_0007738342842735842760 {
    }
    class C_0001480511873190358840["glm::vec&lt;1,Y,Q&gt;"]
    class C_0001480511873190358840 {
    }
    class C_0003169570570284995763["glm::vec&lt;1,Z,Q&gt;"]
    class C_0003169570570284995763 {
    }
    class C_0017579246165008318491["glm::vec&lt;2,A,P&gt;"]
    class C_0017579246165008318491 {
    }
    class C_0013264287076913777274["glm::vec&lt;1,B,P&gt;"]
    class C_0013264287076913777274 {
    }
    class C_0000584639886873075723["glm::vec&lt;2,B,P&gt;"]
    class C_0000584639886873075723 {
    }
    class C_0006108922882648812355["glm::vec&lt;1,A,P&gt;"]
    class C_0006108922882648812355 {
    }
    class C_0004416552121781064540["glm::vec&lt;3,U,Q&gt;"]
    class C_0004416552121781064540 {
    }
    class C_0006340795772159705450["glm::vec&lt;4,T,P&gt;"]
    class C_0006340795772159705450 {
    }
    class C_0001531959356999801914["glm::vec&lt;1,W,Q&gt;"]
    class C_0001531959356999801914 {
    }
    class C_0015297257712248839377["glm::vec&lt;1,C,P&gt;"]
    class C_0015297257712248839377 {
    }
    class C_0007799094981529459976["glm::vec&lt;2,C,P&gt;"]
    class C_0007799094981529459976 {
    }
    class C_0009885674740766927855["glm::vec&lt;3,A,P&gt;"]
    class C_0009885674740766927855 {
    }
    class C_0011515491856034123398["glm::vec&lt;3,B,P&gt;"]
    class C_0011515491856034123398 {
    }
    class C_0009113158509162214328["glm::vec&lt;4,U,Q&gt;"]
    class C_0009113158509162214328 {
    }
    class C_0002799507906886402350["glm::mat&lt;2,2,T,P&gt;"]
    class C_0002799507906886402350 {
    }
    class C_0000635961036550666236["glm::vec&lt;2,V,Q&gt;"]
    class C_0000635961036550666236 {
    }
    class C_0012618043414258396134["glm::mat&lt;2,2,U,P&gt;"]
    class C_0012618043414258396134 {
    }
    class C_0003628958744696471083["glm::mat&lt;2,2,U,Q&gt;"]
    class C_0003628958744696471083 {
    }
    class C_0008407781152313292760["glm::mat&lt;2,3,T,P&gt;"]
    class C_0008407781152313292760 {
    }
    class C_0015377508743783301968["glm::vec&lt;3,V,Q&gt;"]
    class C_0015377508743783301968 {
    }
    class C_0005252436267332410041["glm::mat&lt;2,3,U,P&gt;"]
    class C_0005252436267332410041 {
    }
    class C_0011645150379937564510["glm::mat&lt;2,3,U,Q&gt;"]
    class C_0011645150379937564510 {
    }
    class C_0007323870670253339346["glm::mat&lt;2,4,T,P&gt;"]
    class C_0007323870670253339346 {
    }
    class C_0002590457629089863094["glm::vec&lt;4,V,Q&gt;"]
    class C_0002590457629089863094 {
    }
    class C_0009262037211467414844["glm::mat&lt;2,4,U,P&gt;"]
    class C_0009262037211467414844 {
    }
    class C_0013406485112655065712["glm::mat&lt;2,4,U,Q&gt;"]
    class C_0013406485112655065712 {
    }
    class C_0007158558504198085640["glm::mat&lt;3,2,T,P&gt;"]
    class C_0007158558504198085640 {
    }
    class C_0002562295340752357913["glm::vec&lt;2,V1,Q&gt;"]
    class C_0002562295340752357913 {
    }
    class C_0000744013708021145905["glm::vec&lt;2,V2,Q&gt;"]
    class C_0000744013708021145905 {
    }
    class C_0009679823751851023587["glm::vec&lt;2,V3,Q&gt;"]
    class C_0009679823751851023587 {
    }
    class C_0013071341770184119338["glm::mat&lt;3,2,U,P&gt;"]
    class C_0013071341770184119338 {
    }
    class C_0005074114061636511327["glm::mat&lt;3,2,U,Q&gt;"]
    class C_0005074114061636511327 {
    }
    class C_0003014482284833559017["glm::mat&lt;3,3,T,P&gt;"]
    class C_0003014482284833559017 {
    }
    class C_0003041513342711788422["glm::vec&lt;3,V1,Q&gt;"]
    class C_0003041513342711788422 {
    }
    class C_0011641176337880010879["glm::vec&lt;3,V2,Q&gt;"]
    class C_0011641176337880010879 {
    }
    class C_0006752072813915976143["glm::vec&lt;3,V3,Q&gt;"]
    class C_0006752072813915976143 {
    }
    class C_0006967883322270155146["glm::mat&lt;3,3,U,P&gt;"]
    class C_0006967883322270155146 {
    }
    class C_0002829408754176877928["glm::mat&lt;3,3,U,Q&gt;"]
    class C_0002829408754176877928 {
    }
    class C_0006250433396300995200["glm::mat&lt;3,4,T,P&gt;"]
    class C_0006250433396300995200 {
    }
    class C_0018431782981220877824["glm::vec&lt;4,V1,Q&gt;"]
    class C_0018431782981220877824 {
    }
    class C_0005568870174902212529["glm::vec&lt;4,V2,Q&gt;"]
    class C_0005568870174902212529 {
    }
    class C_0001735402496744490083["glm::vec&lt;4,V3,Q&gt;"]
    class C_0001735402496744490083 {
    }
    class C_0002328100515583017229["glm::mat&lt;3,4,U,P&gt;"]
    class C_0002328100515583017229 {
    }
    class C_0003749456310058177537["glm::mat&lt;3,4,U,Q&gt;"]
    class C_0003749456310058177537 {
    }
    class C_0012939722395153742105["glm::mat&lt;4,2,T,P&gt;"]
    class C_0012939722395153742105 {
    }
    class C_0015343613012722578758["glm::vec&lt;2,V4,Q&gt;"]
    class C_0015343613012722578758 {
    }
    class C_0018137455377658113550["glm::mat&lt;4,2,U,P&gt;"]
    class C_0018137455377658113550 {
    }
    class C_0002612782377231333730["glm::mat&lt;4,2,U,Q&gt;"]
    class C_0002612782377231333730 {
    }
    class C_0005240039574280005964["glm::mat&lt;4,3,T,P&gt;"]
    class C_0005240039574280005964 {
    }
    class C_0013950690972887294632["glm::vec&lt;3,V4,Q&gt;"]
    class C_0013950690972887294632 {
    }
    class C_0015886820764840174752["glm::mat&lt;4,3,U,P&gt;"]
    class C_0015886820764840174752 {
    }
    class C_0005994545668144513265["glm::mat&lt;4,3,U,Q&gt;"]
    class C_0005994545668144513265 {
    }
    class C_0002542626888380986777["glm::mat&lt;4,4,T,P&gt;"]
    class C_0002542626888380986777 {
    }
    class C_0000666527147189690843["glm::vec&lt;4,V4,Q&gt;"]
    class C_0000666527147189690843 {
    }
    class C_0014752931553855831377["glm::mat&lt;4,4,U,P&gt;"]
    class C_0014752931553855831377 {
    }
    class C_0009066338652054392650["glm::mat&lt;4,4,U,Q&gt;"]
    class C_0009066338652054392650 {
    }
    class C_0006496420822577250664["glm::vec&lt;1,T,P&gt;"]
    class C_0006496420822577250664 {
    }
    class C_0014763068788445555214["glm::vec&lt;1,int,Q&gt;"]
    class C_0014763068788445555214 {
    }
    class C_0006913028124951340361["glm::vec&lt;2,int,Q&gt;"]
    class C_0006913028124951340361 {
    }
    class C_0006037099869997505870["glm::vec&lt;3,int,Q&gt;"]
    class C_0006037099869997505870 {
    }
    class C_0009987711875836095733["glm::vec&lt;4,int,Q&gt;"]
    class C_0009987711875836095733 {
    }
    class C_0013196630619216501404["glm::vec&lt;L,T,Q&gt;"]
    class C_0013196630619216501404 {
    }
    class C_0014681837414112849335["glm::vec&lt;L,float,lowp&gt;"]
    class C_0014681837414112849335 {
    }
    class C_0015533553309687146323["glm::vec&lt;L,U,Q&gt;"]
    class C_0015533553309687146323 {
    }
    class C_0002339717429297086658["glm::vec&lt;L,bool,Q&gt;"]
    class C_0002339717429297086658 {
    }
    class C_0012357224610396939295["glm::mat&lt;C,R,T,Q&gt;"]
    class C_0012357224610396939295 {
    }
    class C_0011796970895248346011["glm::vec&lt;DA,T,Q&gt;"]
    class C_0011796970895248346011 {
    }
    class C_0006078164231675980417["glm::vec&lt;DB,T,Q&gt;"]
    class C_0006078164231675980417 {
    }
    class C_0010515325766882995808["glm::mat&lt;R,C,T,Q&gt;"]
    class C_0010515325766882995808 {
    }
    class C_0005910766257447474394["glm::vec&lt;L,int,Q&gt;"]
    class C_0005910766257447474394 {
    }
    class C_0017876784243538906311["glm::qua&lt;T,P&gt;"]
    class C_0017876784243538906311 {
    }
    class C_0014354026446901727947["glm::qua&lt;U,P&gt;"]
    class C_0014354026446901727947 {
    }
    class C_0007055789189056520623["glm::qua&lt;U,Q&gt;"]
    class C_0007055789189056520623 {
    }
    class C_0004374069224809106111["glm::qua&lt;T,qualifier Q=defaultp&gt;"]
    class C_0004374069224809106111 {
        +qua() [default] void
        +qua(const qua&lt;T,Q&gt; & q) [default] void
        +qua(T s, const vec&lt;3,T,Q&gt; & v) void
        +qua(T w, T x, T y, T z) void
        +qua(const vec&lt;3,T,Q&gt; & u, const vec&lt;3,T,Q&gt; & v) void
        +qua(const vec&lt;3,T,Q&gt; & eulerAngles) void
        +qua(const mat&lt;3,3,T,Q&gt; & q) void
        +qua(const mat&lt;4,4,T,Q&gt; & q) void
        +qua<qualifier P>(const qua&lt;T,P&gt; & q) void
        +qua<U,qualifier P>(const qua&lt;U,P&gt; & q) void
        +operator=(const qua&lt;T,Q&gt; & q) [default,constexpr] qua&lt;T,Q&gt; &
        +operator*=<U>(const qua&lt;U,Q&gt; & q) [constexpr] qua&lt;T, Q&gt; &
        +operator*=<U>(U s) [constexpr] qua&lt;T, Q&gt; &
        +operator+=<U>(const qua&lt;U,Q&gt; & q) [constexpr] qua&lt;T, Q&gt; &
        +operator-=<U>(const qua&lt;U,Q&gt; & q) [constexpr] qua&lt;T, Q&gt; &
        +operator/=<U>(U s) [constexpr] qua&lt;T, Q&gt; &
        +operator=<U>(const qua&lt;U,Q&gt; & q) [constexpr] qua&lt;T, Q&gt; &
        +operator[](length_type i) [constexpr] T &
        +operator[](length_type i) [const,constexpr] const T &
        +length() [constexpr] length_type$
        +operator mat() [const] mat&lt;3,3,T,Q&gt;
        +operator mat() [const] mat&lt;4,4,T,Q&gt;
        +w : T
        +x : T
        +y : T
        +z : T
    }
    class C_0011488344290179284903["glm::qua&lt;T,glm::packed_highp&gt;"]
    class C_0011488344290179284903 {
    }
    class C_0013254656602862708639["glm::vec&lt;L,floatType,Q&gt;"]
    class C_0013254656602862708639 {
    }
    class C_0000992201366918662950["glm::io::order_type"]
    class C_0000992201366918662950 {
        <<enumeration>>
        column_major
        row_major
    }
    class C_0015287454434830901127["glm::io::format_punct&lt;CTy&gt;"]
    class C_0015287454434830901127 {
        +format_punct(size_t a = 0) void
        +format_punct(const format_punct&lt;CTy&gt; &) void
        +delim_left : char_type
        +delim_right : char_type
        +formatted : bool
        +id : std::locale::id
        +newline : char_type
        +order : order_type
        +precision : unsigned int
        +separator : char_type
        +space : char_type
        +width : unsigned int
    }
    class C_0008924982355675107846["glm::io::basic_state_saver&lt;CTy,CTr=std::char_traits&lt;CTy&gt;&gt;"]
    class C_0008924982355675107846 {
        +basic_state_saver(std::basic_ios&lt;CTy,CTr&gt; &) void
        +~basic_state_saver() void
        -operator=(const basic_state_saver&lt;CTy,CTr&gt; &) basic_state_saver&lt;CTy,CTr&gt; &
        -fill_ : char_type
        -flags_ : flags_type
        -locale_ : locale_type
        -precision_ : streamsize_type
        -state_ : state_type &
        -width_ : streamsize_type
    }
    class C_0015686980712366425392["glm::io::basic_state_saver&lt;CTy&gt;"]
    class C_0015686980712366425392 {
    }
    class C_0018214676362562519909["glm::io::basic_format_saver&lt;CTy,CTr=std::char_traits&lt;CTy&gt;&gt;"]
    class C_0018214676362562519909 {
        +basic_format_saver(std::basic_ios&lt;CTy,CTr&gt; &) void
        +~basic_format_saver() void
        -operator=(const basic_format_saver&lt;CTy,CTr&gt; &) basic_format_saver&lt;CTy,CTr&gt; &
        -bss_ : const basic_state_saver&lt;CTy&gt;
    }
    class C_0014123676234814588829["glm::io::precision"]
    class C_0014123676234814588829 {
        +precision(unsigned int) void
        +value : unsigned int
    }
    class C_0017562535754701680136["glm::io::width"]
    class C_0017562535754701680136 {
        +width(unsigned int) void
        +value : unsigned int
    }
    class C_0008988178118631373465["glm::io::delimeter&lt;CTy&gt;"]
    class C_0008988178118631373465 {
        +delimeter(CTy, CTy, CTy  = ',') void
        +value : CTy[3]
    }
    class C_0000983062377794867882["glm::io::order"]
    class C_0000983062377794867882 {
        +order(order_type) void
        +value : order_type
    }
    class C_0007292912074049978292["glm::tdualquat&lt;T,Q&gt;"]
    class C_0007292912074049978292 {
    }
    class C_0007842129001496693911["glm::tdualquat&lt;T,P&gt;"]
    class C_0007842129001496693911 {
    }
    class C_0011936113789382667383["glm::tdualquat&lt;U,P&gt;"]
    class C_0011936113789382667383 {
    }
    class C_0005173775244095450180["glm::tdualquat&lt;U,Q&gt;"]
    class C_0005173775244095450180 {
    }
    class C_0005525107945907675659["glm::tdualquat&lt;T,qualifier Q=defaultp&gt;"]
    class C_0005525107945907675659 {
        +tdualquat() [default] void
        +tdualquat(const tdualquat&lt;T,Q&gt; & d) [default] void
        +tdualquat(const qua&lt;T,Q&gt; & real) void
        +tdualquat(const qua&lt;T,Q&gt; & orientation, const vec&lt;3,T,Q&gt; & translation) void
        +tdualquat(const qua&lt;T,Q&gt; & real, const qua&lt;T,Q&gt; & dual) void
        +tdualquat(const mat&lt;2,4,T,Q&gt; & holder_mat) void
        +tdualquat(const mat&lt;3,4,T,Q&gt; & aug_mat) void
        +tdualquat<qualifier P>(const tdualquat&lt;T,P&gt; & d) void
        +tdualquat<U,qualifier P>(const tdualquat&lt;U,P&gt; & q) void
        +operator=(const tdualquat&lt;T,Q&gt; & m) [default] tdualquat&lt;T,Q&gt; &
        +operator*=<U>(U s) tdualquat&lt;T, Q&gt; &
        +operator/=<U>(U s) tdualquat&lt;T, Q&gt; &
        +operator=<U>(const tdualquat&lt;U,Q&gt; & m) tdualquat&lt;T, Q&gt; &
        +operator[](length_type i) part_type &
        +operator[](length_type i) [const] const part_type &
        +length() [constexpr] length_type$
        +dual : qua&lt;T,Q&gt;
        +real : qua&lt;T,Q&gt;
    }
    class C_0011998453723586013173["glm::type&lt;T&gt;"]
    class C_0011998453723586013173 {
        +cols : const length_t
        +components : const length_t
        +is_mat : const bool
        +is_quat : const bool
        +is_vec : const bool
        +rows : const length_t
    }
    class C_0004783552046564859349["glm::type&lt;glm::vec&lt;L,T,Q&gt;&gt;"]
    class C_0004783552046564859349 {
        +components : const length_t
        +is_mat : const bool
        +is_quat : const bool
        +is_vec : const bool
    }
    class C_0008955661703058417682["glm::type&lt;glm::mat&lt;C,R,T,Q&gt;&gt;"]
    class C_0008955661703058417682 {
        +cols : const length_t
        +components : const length_t
        +is_mat : const bool
        +is_quat : const bool
        +is_vec : const bool
        +rows : const length_t
    }
    class C_0002068548501378321393["glm::type&lt;glm::qua&lt;T,Q&gt;&gt;"]
    class C_0002068548501378321393 {
        +components : const length_t
        +is_mat : const bool
        +is_quat : const bool
        +is_vec : const bool
    }
    class C_0005096865161113873283["glm::type&lt;glm::tdualquat&lt;T,Q&gt;&gt;"]
    class C_0005096865161113873283 {
        +components : const length_t
        +is_mat : const bool
        +is_quat : const bool
        +is_vec : const bool
    }
    class C_0015845617936909777618["glm::vec&lt;1,glm::detail::uint8,P&gt;"]
    class C_0015845617936909777618 {
    }
    class C_0000988119665543839647["glm::vec&lt;2,glm::detail::uint8,P&gt;"]
    class C_0000988119665543839647 {
    }
    class C_0002150523681706585836["glm::vec&lt;3,glm::detail::uint8,P&gt;"]
    class C_0002150523681706585836 {
    }
    class C_0007936313636513776711["glm::vec&lt;4,glm::detail::uint8,P&gt;"]
    class C_0007936313636513776711 {
    }
    class C_0018152860825089234728["glm::vec&lt;L,glm::detail::uint16,Q&gt;"]
    class C_0018152860825089234728 {
    }
    class C_0000681432894223718122["glm::vec&lt;L,glm::detail::uint32,Q&gt;"]
    class C_0000681432894223718122 {
    }
    class C_0009222464995968348686["glm::vec&lt;L,glm::detail::uint64,Q&gt;"]
    class C_0009222464995968348686 {
    }
    class C_0008853184901211021314["glm::vec&lt;L,glm::detail::int8,Q&gt;"]
    class C_0008853184901211021314 {
    }
    class C_0012032323483750771488["glm::vec&lt;L,glm::detail::uint8,Q&gt;"]
    class C_0012032323483750771488 {
    }
    class C_0007809409934040091628["glm::vec&lt;L,glm::detail::int16,Q&gt;"]
    class C_0007809409934040091628 {
    }
    class C_0018322837704872918466["glm::vec&lt;L,glm::detail::int32,Q&gt;"]
    class C_0018322837704872918466 {
    }
    class C_0010754039428584179960["glm::vec&lt;L,glm::detail::int64,Q&gt;"]
    class C_0010754039428584179960 {
    }
    class C_0006841163757347700305["glm::vec&lt;L,float,Q&gt;"]
    class C_0006841163757347700305 {
    }
    class C_0004114593519074939539["glm::vec&lt;L,double,Q&gt;"]
    class C_0004114593519074939539 {
    }
    class C_0002753253780038737632["glm::vec&lt;L,long double,Q&gt;"]
    class C_0002753253780038737632 {
    }
    class C_0003341249818467524825["glm::mat&lt;length_t C,length_t R,T,qualifier Q=defaultp&gt;"]
    class C_0003341249818467524825 {
    }
    class C_0004644561222112553426["glm::vec&lt;length_t L,T,qualifier Q=defaultp&gt;"]
    class C_0004644561222112553426 {
    }
    class C_0018228047224236063346["glm::vec::&lpar;anonymous_5976849&rpar;"]
    class C_0018228047224236063346 {
        +r : T
        +s : T
        +x : T
    }
    class C_0008038137780939689251["glm::vec::&lpar;anonymous_5976993&rpar;"]
    class C_0008038137780939689251 {
        +g : T
        +t : T
        +y : T
    }
    class C_0001417751542291487823["glm::vec::&lpar;anonymous_6049877&rpar;"]
    class C_0001417751542291487823 {
        +r : T
        +s : T
        +x : T
    }
    class C_0015866809064465718629["glm::vec::&lpar;anonymous_6050021&rpar;"]
    class C_0015866809064465718629 {
        +g : T
        +t : T
        +y : T
    }
    class C_0014921205267279683439["glm::vec::&lpar;anonymous_6050165&rpar;"]
    class C_0014921205267279683439 {
        +b : T
        +p : T
        +z : T
    }
    class C_0004703268121498952559["glm::vec::&lpar;anonymous_6131691&rpar;"]
    class C_0004703268121498952559 {
        +r : T
        +s : T
        +x : T
    }
    class C_0001455961796051902145["glm::vec::&lpar;anonymous_6131835&rpar;"]
    class C_0001455961796051902145 {
        +g : T
        +t : T
        +y : T
    }
    class C_0014977050323646495846["glm::vec::&lpar;anonymous_6131979&rpar;"]
    class C_0014977050323646495846 {
        +b : T
        +p : T
        +z : T
    }
    class C_0015541434054655615251["glm::vec::&lpar;anonymous_6132123&rpar;"]
    class C_0015541434054655615251 {
        +a : T
        +q : T
        +w : T
    }
    class C_0009640856222085335899["glm::vec::&lpar;anonymous_6656351&rpar;"]
    class C_0009640856222085335899 {
        +r : T
        +s : T
        +x : T
    }
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
    class C_0010142888260877035828["GLFWmonitor"]
    class C_0010142888260877035828 {
    }
    class C_0011351004110183750961["GLFWcursor"]
    class C_0011351004110183750961 {
    }
    class C_0011520313121886889649["GLFWwindow"]
    class C_0011520313121886889649 {
    }
    class C_0002649638607837852567["MenuAction"]
    class C_0002649638607837852567 {
        <<enumeration>>
        None
        Start1v1
        StartAI
    }
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
    class C_0004693359074816351727["AppState"]
    class C_0004693359074816351727 {
        <<enumeration>>
        Menu
        Game
    }
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
    C_0004777943177714336574 o-- C_0003177176768377443572 : +type
    C_0004777943177714336574 o-- C_0000933547394081598572 : +color
    C_0002748255974922495785 ..> C_0017533998226253472530 : 
    C_0002748255974922495785 ..> C_0000933547394081598572 : 
    C_0002748255974922495785 o-- C_0004777943177714336574 : -m_grid
    C_0007563864698956368175 o-- C_0017533998226253472530 : +from
    C_0007563864698956368175 o-- C_0017533998226253472530 : +to
    C_0009094603417046821245 ..> C_0002748255974922495785 : 
    C_0009094603417046821245 ..> C_0000933547394081598572 : 
    C_0009094603417046821245 ..> C_0002280536835303751986 : 
    C_0009094603417046821245 ..> C_0007563864698956368175 : 
    C_0010267710733373613038 o-- C_0002748255974922495785 : +board
    C_0010267710733373613038 o-- C_0000933547394081598572 : +currentTurn
    C_0010267710733373613038 o-- C_0018077852919137909338 : +state
    C_0004842393136000246713 ..> C_0003177176768377443572 : 
    C_0004842393136000246713 o-- C_0002748255974922495785 : -m_board
    C_0004842393136000246713 o-- C_0000933547394081598572 : -m_currentTurn
    C_0004842393136000246713 o-- C_0018077852919137909338 : -m_state
    C_0004842393136000246713 o-- C_0017533998226253472530 : -m_promotionPos
    C_0004842393136000246713 o-- C_0004851280417930349063 : -m_activeRules
    C_0004842393136000246713 o-- C_0010267710733373613038 : -m_backupHistory
    C_0004306397417237529713 ..> C_0004842393136000246713 : 
    C_0004306397417237529713 o-- C_0002280536835303751986 : -m_difficulty
    C_0004306397417237529713 o-- C_0000933547394081598572 : -m_playerColor
    C_0002531126229291306321 ..> C_0004842393136000246713 : 
    C_0002531126229291306321 ..> C_0004777943177714336574 : 
    C_0002531126229291306321 o-- C_0017533998226253472530 : -m_selectedPos
    C_0017165406136470954566 ()-- C_0014743839948111171689 : 
    C_0018341899181759956368 ..|> C_0017165406136470954566 : 
    C_0001878113324719440692 ..|> C_0017165406136470954566 : 
    C_0012832989951413576519 ()-- C_0011108722095378127667 : 
    C_0001287751108879850958 ..|> C_0012832989951413576519 : 
    C_0002998106636798449075 ..|> C_0012832989951413576519 : 
    C_0015896199050460753952 ..> C_0008671907212119285262 : 
    C_0015896199050460753952 ..|> C_0006743273674606620912 : 
    C_0015896199050460753952 --> C_0011330292752136108294 : +GENTYPE
    C_0003083707105962937990 ..|> C_0007193098452303625212 : 
    C_0015603389788290154537 ..|> C_0007193098452303625212 : 
    C_0010444049787743091084 ..|> C_0017165406136470954566 : 
    C_0007454676841364767438 ..|> C_0017165406136470954566 : 
    C_0011587924244531489778 ..|> C_0017165406136470954566 : 
    C_0012373186198985777456 ..|> C_0017165406136470954566 : 
    C_0001447139119483475009 ..|> C_0017165406136470954566 : 
    C_0001207741522012001173 ..|> C_0017165406136470954566 : 
    C_0008773260381889745120 ..> C_0015117083025601782618 : 
    C_0008773260381889745120 ..> C_0004644561222112553426 : 
    C_0014180874808606960218 ..> C_0015117083025601782618 : 
    C_0014180874808606960218 ..> C_0004644561222112553426 : 
    C_0014721178274615561002 ..> C_0015117083025601782618 : 
    C_0014721178274615561002 ..> C_0004644561222112553426 : 
    C_0018293134536481637290 ..> C_0015117083025601782618 : 
    C_0018293134536481637290 ..> C_0004644561222112553426 : 
    C_0008182436331049693656 ..> C_0015117083025601782618 : 
    C_0008182436331049693656 ..> C_0004644561222112553426 : 
    C_0009448542793109187229 ..> C_0015117083025601782618 : 
    C_0009448542793109187229 ..> C_0004644561222112553426 : 
    C_0007394072018332501491 ..> C_0015117083025601782618 : 
    C_0007394072018332501491 ..> C_0004644561222112553426 : 
    C_0007182033410364433853 ..> C_0015117083025601782618 : 
    C_0007182033410364433853 ..> C_0004644561222112553426 : 
    C_0008784057479259358475 ..> C_0015117083025601782618 : 
    C_0008784057479259358475 ..> C_0004644561222112553426 : 
    C_0011512554430276197142 ..> C_0015117083025601782618 : 
    C_0011512554430276197142 ..> C_0004644561222112553426 : 
    C_0015114459323685163119 ..> C_0015117083025601782618 : 
    C_0015114459323685163119 ..> C_0004644561222112553426 : 
    C_0001513586326169120888 ..> C_0015117083025601782618 : 
    C_0001513586326169120888 ..> C_0004644561222112553426 : 
    C_0000879102544197822415 ..> C_0015117083025601782618 : 
    C_0000879102544197822415 ..> C_0004644561222112553426 : 
    C_0009697542087676983569 ..|> C_0017686723680688667673 : 
    C_0009367951713378955731 ..|> C_0017686723680688667673 : 
    C_0004129319365027099429 ..|> C_0017686723680688667673 : 
    C_0013919754403120507144 ..|> C_0017686723680688667673 : 
    C_0018250010645674283695 ..|> C_0017686723680688667673 : 
    C_0002465306396778682587 ..|> C_0017686723680688667673 : 
    C_0017006236639334178286 ..|> C_0017686723680688667673 : 
    C_0015474031542116761089 ..|> C_0017686723680688667673 : 
    C_0015405964719396265045 ..|> C_0017686723680688667673 : 
    C_0016189112089169313067 ..|> C_0002560830178258722289 : 
    C_0010171364238334460824 ..|> C_0002560830178258722289 : 
    C_0018376621820078191272 ..|> C_0002560830178258722289 : 
    C_0007872976482775124051 ..|> C_0002560830178258722289 : 
    C_0009201574913036764026 ..|> C_0012783099691243171930 : 
    C_0017665908564292248117 ..|> C_0012783099691243171930 : 
    C_0000566273510248472737 ..|> C_0012783099691243171930 : 
    C_0014512950444228567886 ..|> C_0012783099691243171930 : 
    C_0003725676454125813013 ..|> C_0008652419597806869875 : 
    C_0010422810831389303463 ..|> C_0008652419597806869875 : 
    C_0002168626670454111484 ..|> C_0008652419597806869875 : 
    C_0008315779048824656096 ..|> C_0008652419597806869875 : 
    C_0003563067956550835236 ..> C_0006992479837074144199 : 
    C_0003563067956550835236 ..> C_0004644561222112553426 : 
    C_0003563067956550835236 ..> C_0014763068788445555214 : 
    C_0003563067956550835236 ..|> C_0014466946788244241872 : 
    C_0000141248975816736781 ..> C_0017729851466359107363 : 
    C_0000141248975816736781 ..> C_0004644561222112553426 : 
    C_0000141248975816736781 ..> C_0006913028124951340361 : 
    C_0000141248975816736781 ..|> C_0014466946788244241872 : 
    C_0008441460645539462312 ..> C_0013826567149110357089 : 
    C_0008441460645539462312 ..> C_0004644561222112553426 : 
    C_0008441460645539462312 ..> C_0006037099869997505870 : 
    C_0008441460645539462312 ..|> C_0014466946788244241872 : 
    C_0004853162657727430087 ..> C_0015117083025601782618 : 
    C_0004853162657727430087 ..> C_0004644561222112553426 : 
    C_0004853162657727430087 ..> C_0009987711875836095733 : 
    C_0004853162657727430087 ..|> C_0014466946788244241872 : 
    C_0009393182619228299296 ..> C_0013196630619216501404 : 
    C_0009393182619228299296 ..> C_0004644561222112553426 : 
    C_0005416897660123406119 ..> C_0013196630619216501404 : 
    C_0005416897660123406119 ..> C_0004644561222112553426 : 
    C_0003016636279178888439 ..> C_0013196630619216501404 : 
    C_0003016636279178888439 ..> C_0004644561222112553426 : 
    C_0001779101269862389753 ..> C_0014681837414112849335 : 
    C_0001779101269862389753 ..> C_0004644561222112553426 : 
    C_0001779101269862389753 ..|> C_0003016636279178888439 : 
    C_0010811338212008253318 ..|> C_0003376541723311639984 : 
    C_0015159482233899751592 ..|> C_0003376541723311639984 : 
    C_0001189108426468022122 ..> C_0013196630619216501404 : 
    C_0001189108426468022122 ..> C_0004644561222112553426 : 
    C_0018330992663782840373 ..> C_0013196630619216501404 : 
    C_0018330992663782840373 ..> C_0004644561222112553426 : 
    C_0018330992663782840373 ..> C_0015533553309687146323 : 
    C_0000377743384354775438 ..> C_0013196630619216501404 : 
    C_0000377743384354775438 ..> C_0004644561222112553426 : 
    C_0000377743384354775438 ..> C_0002339717429297086658 : 
    C_0000377743384354775438 ..|> C_0018330992663782840373 : 
    C_0009646140591064684154 ..> C_0013196630619216501404 : 
    C_0009646140591064684154 ..> C_0004644561222112553426 : 
    C_0008411158522264013301 ..> C_0013196630619216501404 : 
    C_0008411158522264013301 ..> C_0004644561222112553426 : 
    C_0008411158522264013301 ..|> C_0009646140591064684154 : 
    C_0008876595274360920253 ..|> C_0018022014358682532439 : 
    C_0007878523707059901808 ..> C_0013196630619216501404 : 
    C_0007878523707059901808 ..> C_0004644561222112553426 : 
    C_0013720283651865864113 ..> C_0013196630619216501404 : 
    C_0013720283651865864113 ..> C_0004644561222112553426 : 
    C_0016391944696740134914 ..> C_0013196630619216501404 : 
    C_0016391944696740134914 ..> C_0004644561222112553426 : 
    C_0013966754841608355702 ..> C_0013196630619216501404 : 
    C_0013966754841608355702 ..> C_0004644561222112553426 : 
    C_0000605404021214105083 ..> C_0013196630619216501404 : 
    C_0000605404021214105083 ..> C_0004644561222112553426 : 
    C_0000498928720602658223 ..> C_0013196630619216501404 : 
    C_0000498928720602658223 ..> C_0004644561222112553426 : 
    C_0012572651991728070948 ..> C_0013196630619216501404 : 
    C_0012572651991728070948 ..> C_0004644561222112553426 : 
    C_0009782709305793365194 ..> C_0013196630619216501404 : 
    C_0009782709305793365194 ..> C_0004644561222112553426 : 
    C_0004807050522189811263 ..> C_0013196630619216501404 : 
    C_0004807050522189811263 ..> C_0004644561222112553426 : 
    C_0002297802655018725126 ..> C_0013196630619216501404 : 
    C_0002297802655018725126 ..> C_0004644561222112553426 : 
    C_0007879660818841049157 ..> C_0013196630619216501404 : 
    C_0007879660818841049157 ..> C_0004644561222112553426 : 
    C_0013085828508809210422 ..> C_0013196630619216501404 : 
    C_0013085828508809210422 ..> C_0004644561222112553426 : 
    C_0010361331594249330371 ..> C_0013196630619216501404 : 
    C_0010361331594249330371 ..> C_0004644561222112553426 : 
    C_0006191377841247627706 ..> C_0013196630619216501404 : 
    C_0006191377841247627706 ..> C_0004644561222112553426 : 
    C_0005418326039960527079 ..> C_0006992479837074144199 : 
    C_0005418326039960527079 ..> C_0004644561222112553426 : 
    C_0005418326039960527079 ..|> C_0003995764588866141299 : 
    C_0006750956518445531872 ..> C_0017729851466359107363 : 
    C_0006750956518445531872 ..> C_0004644561222112553426 : 
    C_0006750956518445531872 ..|> C_0003995764588866141299 : 
    C_0010330400419319200686 ..> C_0013826567149110357089 : 
    C_0010330400419319200686 ..> C_0004644561222112553426 : 
    C_0010330400419319200686 ..|> C_0003995764588866141299 : 
    C_0006174179673291647203 ..> C_0015117083025601782618 : 
    C_0006174179673291647203 ..> C_0004644561222112553426 : 
    C_0006174179673291647203 ..|> C_0003995764588866141299 : 
    C_0015824183364641647648 ..> C_0013826567149110357089 : 
    C_0015824183364641647648 ..> C_0004644561222112553426 : 
    C_0009879403532153280824 ..> C_0013196630619216501404 : 
    C_0009879403532153280824 ..> C_0004644561222112553426 : 
    C_0012787582606908899191 ..> C_0013196630619216501404 : 
    C_0012787582606908899191 ..> C_0004644561222112553426 : 
    C_0005715687668474009820 ..> C_0013196630619216501404 : 
    C_0005715687668474009820 ..> C_0004644561222112553426 : 
    C_0006180436695447720838 ..> C_0013196630619216501404 : 
    C_0006180436695447720838 ..> C_0004644561222112553426 : 
    C_0010249294259649984273 ..> C_0012357224610396939295 : 
    C_0010249294259649984273 ..> C_0003341249818467524825 : 
    C_0002202497605370845773 ..> C_0012357224610396939295 : 
    C_0002202497605370845773 ..> C_0003341249818467524825 : 
    C_0002764610822168181826 ..> C_0011796970895248346011 : 
    C_0002764610822168181826 ..> C_0004644561222112553426 : 
    C_0002764610822168181826 ..> C_0006078164231675980417 : 
    C_0005481292911835082602 ..> C_0011796970895248346011 : 
    C_0005481292911835082602 ..> C_0004644561222112553426 : 
    C_0005481292911835082602 ..> C_0006078164231675980417 : 
    C_0007881146451740919032 ..> C_0007482356929151537282 : 
    C_0007881146451740919032 ..> C_0003341249818467524825 : 
    C_0007881146451740919032 ..|> C_0015729851752530164593 : 
    C_0001859500514412013469 ..> C_0016370386407813495429 : 
    C_0001859500514412013469 ..> C_0003341249818467524825 : 
    C_0001859500514412013469 ..> C_0002644064770012110766 : 
    C_0001859500514412013469 ..|> C_0015729851752530164593 : 
    C_0007787828887948791922 ..> C_0003496176270941337858 : 
    C_0007787828887948791922 ..> C_0003341249818467524825 : 
    C_0007787828887948791922 ..> C_0005160671499566832302 : 
    C_0007787828887948791922 ..|> C_0015729851752530164593 : 
    C_0004098227419831323395 ..> C_0002644064770012110766 : 
    C_0004098227419831323395 ..> C_0003341249818467524825 : 
    C_0004098227419831323395 ..> C_0016370386407813495429 : 
    C_0004098227419831323395 ..|> C_0015729851752530164593 : 
    C_0008188330762772437840 ..> C_0005819674801799086687 : 
    C_0008188330762772437840 ..> C_0003341249818467524825 : 
    C_0008188330762772437840 ..|> C_0015729851752530164593 : 
    C_0009013912562976277181 ..> C_0011458867993025185835 : 
    C_0009013912562976277181 ..> C_0003341249818467524825 : 
    C_0009013912562976277181 ..> C_0013207976060429267904 : 
    C_0009013912562976277181 ..|> C_0015729851752530164593 : 
    C_0001558861689450681704 ..> C_0005160671499566832302 : 
    C_0001558861689450681704 ..> C_0003341249818467524825 : 
    C_0001558861689450681704 ..> C_0003496176270941337858 : 
    C_0001558861689450681704 ..|> C_0015729851752530164593 : 
    C_0003029586384935255756 ..> C_0013207976060429267904 : 
    C_0003029586384935255756 ..> C_0003341249818467524825 : 
    C_0003029586384935255756 ..> C_0011458867993025185835 : 
    C_0003029586384935255756 ..|> C_0015729851752530164593 : 
    C_0005400345805634604952 ..> C_0011146366150305476558 : 
    C_0005400345805634604952 ..> C_0003341249818467524825 : 
    C_0005400345805634604952 ..|> C_0015729851752530164593 : 
    C_0004291393052584190979 ..> C_0012357224610396939295 : 
    C_0004291393052584190979 ..> C_0003341249818467524825 : 
    C_0004291393052584190979 ..> C_0010515325766882995808 : 
    C_0004603505941396452095 ..> C_0007482356929151537282 : 
    C_0004603505941396452095 ..> C_0003341249818467524825 : 
    C_0004603505941396452095 ..|> C_0002216603726385707142 : 
    C_0008544802141356008321 ..> C_0005819674801799086687 : 
    C_0008544802141356008321 ..> C_0003341249818467524825 : 
    C_0008544802141356008321 ..|> C_0002216603726385707142 : 
    C_0017355783167375359772 ..> C_0011146366150305476558 : 
    C_0017355783167375359772 ..> C_0003341249818467524825 : 
    C_0017355783167375359772 ..|> C_0002216603726385707142 : 
    C_0002490239562282425209 ..> C_0012357224610396939295 : 
    C_0002490239562282425209 ..> C_0003341249818467524825 : 
    C_0013007929996164545106 ..> C_0007482356929151537282 : 
    C_0013007929996164545106 ..> C_0003341249818467524825 : 
    C_0013007929996164545106 ..|> C_0005825466840221447692 : 
    C_0007409851143889663669 ..> C_0005819674801799086687 : 
    C_0007409851143889663669 ..> C_0003341249818467524825 : 
    C_0007409851143889663669 ..|> C_0005825466840221447692 : 
    C_0013263891568124544845 ..> C_0011146366150305476558 : 
    C_0013263891568124544845 ..> C_0003341249818467524825 : 
    C_0013263891568124544845 ..|> C_0005825466840221447692 : 
    C_0013552931000080767045 ..> C_0013196630619216501404 : 
    C_0013552931000080767045 ..> C_0004644561222112553426 : 
    C_0008368078235790091494 ..> C_0013196630619216501404 : 
    C_0008368078235790091494 ..> C_0004644561222112553426 : 
    C_0008368078235790091494 ..|> C_0013552931000080767045 : 
    C_0000410803817831491586 ..> C_0013196630619216501404 : 
    C_0000410803817831491586 ..> C_0004644561222112553426 : 
    C_0015671549293778163470 ..> C_0013196630619216501404 : 
    C_0015671549293778163470 ..> C_0004644561222112553426 : 
    C_0015671549293778163470 ..|> C_0000410803817831491586 : 
    C_0008456521682378646313 ..> C_0013196630619216501404 : 
    C_0008456521682378646313 ..> C_0004644561222112553426 : 
    C_0014990534431396726446 ..> C_0013196630619216501404 : 
    C_0014990534431396726446 ..> C_0004644561222112553426 : 
    C_0014990534431396726446 ..|> C_0008456521682378646313 : 
    C_0003443302256699892724 ..> C_0013196630619216501404 : 
    C_0003443302256699892724 ..> C_0004644561222112553426 : 
    C_0003443302256699892724 ..> C_0005910766257447474394 : 
    C_0001471993262601684536 ..|> C_0017854690719509684787 : 
    C_0008444656603509005298 ..|> C_0017854690719509684787 : 
    C_0014602532577836950841 ..> C_0011488344290179284903 : 
    C_0014602532577836950841 ..|> C_0006743273674606620912 : 
    C_0014602532577836950841 --> C_0011330292752136108294 : +GENTYPE
    C_0017575668200705778502 ..> C_0011188896363051785620 : 
    C_0017575668200705778502 ..> C_0004374069224809106111 : 
    C_0017575668200705778502 ..|> C_0003995764588866141299 : 
    C_0017282521853691103935 ..> C_0011188896363051785620 : 
    C_0017282521853691103935 ..> C_0004374069224809106111 : 
    C_0012617079442092803171 ..> C_0011188896363051785620 : 
    C_0012617079442092803171 ..> C_0004374069224809106111 : 
    C_0018394432602105543406 ..> C_0011188896363051785620 : 
    C_0018394432602105543406 ..> C_0004374069224809106111 : 
    C_0002124913055560694229 ..> C_0011188896363051785620 : 
    C_0002124913055560694229 ..> C_0004374069224809106111 : 
    C_0008668887570412326500 ..> C_0011188896363051785620 : 
    C_0008668887570412326500 ..> C_0004374069224809106111 : 
    C_0008668887570412326500 ..> C_0015117083025601782618 : 
    C_0008668887570412326500 ..> C_0004644561222112553426 : 
    C_0015411313640123734523 ..> C_0013196630619216501404 : 
    C_0015411313640123734523 ..> C_0004644561222112553426 : 
    C_0015411313640123734523 ..> C_0013254656602862708639 : 
    C_0015411313640123734523 ..|> C_0011439403360356034938 : 
    C_0011784441873711350910 ..> C_0013196630619216501404 : 
    C_0011784441873711350910 ..> C_0004644561222112553426 : 
    C_0011784441873711350910 ..> C_0013254656602862708639 : 
    C_0011784441873711350910 ..|> C_0011439403360356034938 : 
    C_0014062317156853742088 ..> C_0013196630619216501404 : 
    C_0014062317156853742088 ..> C_0004644561222112553426 : 
    C_0014062317156853742088 ..> C_0013254656602862708639 : 
    C_0014062317156853742088 ..|> C_0011439403360356034938 : 
    C_0009544353725842918078 ..> C_0013254656602862708639 : 
    C_0009544353725842918078 ..> C_0004644561222112553426 : 
    C_0009544353725842918078 ..> C_0013196630619216501404 : 
    C_0009544353725842918078 ..|> C_0000051730753218865182 : 
    C_0017541291380119939604 ..> C_0013254656602862708639 : 
    C_0017541291380119939604 ..> C_0004644561222112553426 : 
    C_0017541291380119939604 ..> C_0013196630619216501404 : 
    C_0017541291380119939604 ..|> C_0000051730753218865182 : 
    C_0009623686183071842245 ..> C_0013254656602862708639 : 
    C_0009623686183071842245 ..> C_0004644561222112553426 : 
    C_0009623686183071842245 ..> C_0013196630619216501404 : 
    C_0009623686183071842245 ..|> C_0000051730753218865182 : 
    C_0012656140945091034469 ..> C_0013196630619216501404 : 
    C_0012656140945091034469 ..> C_0004644561222112553426 : 
    C_0005502540817457157979 ..> C_0013196630619216501404 : 
    C_0005502540817457157979 ..> C_0004644561222112553426 : 
    C_0001603363853034486258 ..> C_0015845617936909777618 : 
    C_0001603363853034486258 ..> C_0004644561222112553426 : 
    C_0001603363853034486258 ..|> C_0005502540817457157979 : 
    C_0002686830347748380728 ..> C_0000988119665543839647 : 
    C_0002686830347748380728 ..> C_0004644561222112553426 : 
    C_0002686830347748380728 ..|> C_0005502540817457157979 : 
    C_0006090447241121061899 ..> C_0002150523681706585836 : 
    C_0006090447241121061899 ..> C_0004644561222112553426 : 
    C_0006090447241121061899 ..|> C_0005502540817457157979 : 
    C_0001153560176141861826 ..> C_0007936313636513776711 : 
    C_0001153560176141861826 ..> C_0004644561222112553426 : 
    C_0001153560176141861826 ..|> C_0005502540817457157979 : 
    C_0008574170526380206673 ..> C_0018152860825089234728 : 
    C_0008574170526380206673 ..> C_0004644561222112553426 : 
    C_0008574170526380206673 ..|> C_0005502540817457157979 : 
    C_0009720305886431815002 ..> C_0000681432894223718122 : 
    C_0009720305886431815002 ..> C_0004644561222112553426 : 
    C_0009720305886431815002 ..|> C_0005502540817457157979 : 
    C_0005069809328701172009 ..> C_0009222464995968348686 : 
    C_0005069809328701172009 ..> C_0004644561222112553426 : 
    C_0005069809328701172009 ..|> C_0005502540817457157979 : 
    C_0000785490213154692308 ..> C_0013196630619216501404 : 
    C_0000785490213154692308 ..> C_0004644561222112553426 : 
    C_0005512908233036887058 ..> C_0008853184901211021314 : 
    C_0005512908233036887058 ..> C_0004644561222112553426 : 
    C_0005512908233036887058 ..|> C_0000785490213154692308 : 
    C_0002483196794121134757 ..> C_0012032323483750771488 : 
    C_0002483196794121134757 ..> C_0004644561222112553426 : 
    C_0002483196794121134757 ..|> C_0000785490213154692308 : 
    C_0000159143745571817136 ..> C_0007809409934040091628 : 
    C_0000159143745571817136 ..> C_0004644561222112553426 : 
    C_0000159143745571817136 ..|> C_0000785490213154692308 : 
    C_0007520649107592933480 ..> C_0018152860825089234728 : 
    C_0007520649107592933480 ..> C_0004644561222112553426 : 
    C_0007520649107592933480 ..|> C_0000785490213154692308 : 
    C_0008964589233154078681 ..> C_0018322837704872918466 : 
    C_0008964589233154078681 ..> C_0004644561222112553426 : 
    C_0008964589233154078681 ..|> C_0000785490213154692308 : 
    C_0015417027955790789238 ..> C_0000681432894223718122 : 
    C_0015417027955790789238 ..> C_0004644561222112553426 : 
    C_0015417027955790789238 ..|> C_0000785490213154692308 : 
    C_0014423018035884627438 ..> C_0010754039428584179960 : 
    C_0014423018035884627438 ..> C_0004644561222112553426 : 
    C_0014423018035884627438 ..|> C_0000785490213154692308 : 
    C_0007865373373365576150 ..> C_0009222464995968348686 : 
    C_0007865373373365576150 ..> C_0004644561222112553426 : 
    C_0007865373373365576150 ..|> C_0000785490213154692308 : 
    C_0013698864996950055508 ..> C_0006841163757347700305 : 
    C_0013698864996950055508 ..> C_0004644561222112553426 : 
    C_0013698864996950055508 ..|> C_0000785490213154692308 : 
    C_0003925512995191256877 ..> C_0004114593519074939539 : 
    C_0003925512995191256877 ..> C_0004644561222112553426 : 
    C_0003925512995191256877 ..|> C_0000785490213154692308 : 
    C_0010178100644696197769 ..> C_0002753253780038737632 : 
    C_0010178100644696197769 ..> C_0004644561222112553426 : 
    C_0010178100644696197769 ..|> C_0000785490213154692308 : 
    C_0006992479837074144199 ..|> C_0004644561222112553426 : 
    C_0006992479837074144199 ..> C_0006496420822577250664 : 
    C_0006992479837074144199 ..> C_0009213554402760339732 : 
    C_0006992479837074144199 ..> C_0014214357445942724006 : 
    C_0006992479837074144199 ..> C_0003647233661022599932 : 
    C_0006992479837074144199 ..> C_0006233718487001977294 : 
    C_0006992479837074144199 ..> C_0007349285277881282082 : 
    C_0006992479837074144199 o-- C_0009674406055978195782 : 
    C_0017729851466359107363 ..|> C_0004644561222112553426 : 
    C_0017729851466359107363 ..> C_0002680935233270452008 : 
    C_0017729851466359107363 ..> C_0006233718487001977294 : 
    C_0017729851466359107363 ..> C_0007440443376641485314 : 
    C_0017729851466359107363 ..> C_0017297655928961336862 : 
    C_0017729851466359107363 ..> C_0014214357445942724006 : 
    C_0017729851466359107363 ..> C_0003647233661022599932 : 
    C_0017729851466359107363 ..> C_0009213554402760339732 : 
    C_0017729851466359107363 ..> C_0008273115442750733243 : 
    C_0017729851466359107363 ..> C_0007349285277881282082 : 
    C_0017729851466359107363 o-- C_0009674406055978195782 : 
    C_0013826567149110357089 ..|> C_0004644561222112553426 : 
    C_0013826567149110357089 ..> C_0000393330291159126666 : 
    C_0013826567149110357089 ..> C_0006233718487001977294 : 
    C_0013826567149110357089 ..> C_0007738342842735842760 : 
    C_0013826567149110357089 ..> C_0001480511873190358840 : 
    C_0013826567149110357089 ..> C_0003169570570284995763 : 
    C_0013826567149110357089 ..> C_0017579246165008318491 : 
    C_0013826567149110357089 ..> C_0013264287076913777274 : 
    C_0013826567149110357089 ..> C_0000584639886873075723 : 
    C_0013826567149110357089 ..> C_0006108922882648812355 : 
    C_0013826567149110357089 ..> C_0003647233661022599932 : 
    C_0013826567149110357089 ..> C_0014214357445942724006 : 
    C_0013826567149110357089 ..> C_0004416552121781064540 : 
    C_0013826567149110357089 ..> C_0007349285277881282082 : 
    C_0013826567149110357089 o-- C_0009674406055978195782 : 
    C_0015117083025601782618 ..|> C_0004644561222112553426 : 
    C_0015117083025601782618 ..> C_0006340795772159705450 : 
    C_0015117083025601782618 ..> C_0006233718487001977294 : 
    C_0015117083025601782618 ..> C_0007738342842735842760 : 
    C_0015117083025601782618 ..> C_0001480511873190358840 : 
    C_0015117083025601782618 ..> C_0003169570570284995763 : 
    C_0015117083025601782618 ..> C_0001531959356999801914 : 
    C_0015117083025601782618 ..> C_0017579246165008318491 : 
    C_0015117083025601782618 ..> C_0013264287076913777274 : 
    C_0015117083025601782618 ..> C_0015297257712248839377 : 
    C_0015117083025601782618 ..> C_0000584639886873075723 : 
    C_0015117083025601782618 ..> C_0006108922882648812355 : 
    C_0015117083025601782618 ..> C_0007799094981529459976 : 
    C_0015117083025601782618 ..> C_0009885674740766927855 : 
    C_0015117083025601782618 ..> C_0011515491856034123398 : 
    C_0015117083025601782618 ..> C_0003647233661022599932 : 
    C_0015117083025601782618 ..> C_0009113158509162214328 : 
    C_0015117083025601782618 ..> C_0007349285277881282082 : 
    C_0015117083025601782618 o-- C_0009674406055978195782 : 
    C_0007482356929151537282 ..|> C_0003341249818467524825 : 
    C_0007482356929151537282 ..> C_0004644561222112553426 : 
    C_0007482356929151537282 ..> C_0005819674801799086687 : 
    C_0007482356929151537282 ..> C_0011146366150305476558 : 
    C_0007482356929151537282 ..> C_0016370386407813495429 : 
    C_0007482356929151537282 ..> C_0002644064770012110766 : 
    C_0007482356929151537282 ..> C_0003496176270941337858 : 
    C_0007482356929151537282 ..> C_0005160671499566832302 : 
    C_0007482356929151537282 ..> C_0011458867993025185835 : 
    C_0007482356929151537282 ..> C_0013207976060429267904 : 
    C_0007482356929151537282 ..> C_0002799507906886402350 : 
    C_0007482356929151537282 ..> C_0008273115442750733243 : 
    C_0007482356929151537282 ..> C_0000635961036550666236 : 
    C_0007482356929151537282 ..> C_0012618043414258396134 : 
    C_0007482356929151537282 ..> C_0003628958744696471083 : 
    C_0007482356929151537282 o-- "2" C_0017729851466359107363 : -value
    C_0016370386407813495429 ..|> C_0003341249818467524825 : 
    C_0016370386407813495429 ..> C_0004644561222112553426 : 
    C_0016370386407813495429 ..> C_0007482356929151537282 : 
    C_0016370386407813495429 ..> C_0005819674801799086687 : 
    C_0016370386407813495429 ..> C_0011146366150305476558 : 
    C_0016370386407813495429 ..> C_0003496176270941337858 : 
    C_0016370386407813495429 ..> C_0002644064770012110766 : 
    C_0016370386407813495429 ..> C_0011458867993025185835 : 
    C_0016370386407813495429 ..> C_0005160671499566832302 : 
    C_0016370386407813495429 ..> C_0013207976060429267904 : 
    C_0016370386407813495429 ..> C_0008407781152313292760 : 
    C_0016370386407813495429 ..> C_0004416552121781064540 : 
    C_0016370386407813495429 ..> C_0015377508743783301968 : 
    C_0016370386407813495429 ..> C_0005252436267332410041 : 
    C_0016370386407813495429 ..> C_0011645150379937564510 : 
    C_0016370386407813495429 o-- "2" C_0013826567149110357089 : -value
    C_0003496176270941337858 ..|> C_0003341249818467524825 : 
    C_0003496176270941337858 ..> C_0004644561222112553426 : 
    C_0003496176270941337858 ..> C_0007482356929151537282 : 
    C_0003496176270941337858 ..> C_0005819674801799086687 : 
    C_0003496176270941337858 ..> C_0011146366150305476558 : 
    C_0003496176270941337858 ..> C_0016370386407813495429 : 
    C_0003496176270941337858 ..> C_0002644064770012110766 : 
    C_0003496176270941337858 ..> C_0011458867993025185835 : 
    C_0003496176270941337858 ..> C_0005160671499566832302 : 
    C_0003496176270941337858 ..> C_0013207976060429267904 : 
    C_0003496176270941337858 ..> C_0007323870670253339346 : 
    C_0003496176270941337858 ..> C_0009113158509162214328 : 
    C_0003496176270941337858 ..> C_0002590457629089863094 : 
    C_0003496176270941337858 ..> C_0009262037211467414844 : 
    C_0003496176270941337858 ..> C_0013406485112655065712 : 
    C_0003496176270941337858 o-- "2" C_0015117083025601782618 : -value
    C_0002644064770012110766 ..|> C_0003341249818467524825 : 
    C_0002644064770012110766 ..> C_0004644561222112553426 : 
    C_0002644064770012110766 ..> C_0007482356929151537282 : 
    C_0002644064770012110766 ..> C_0005819674801799086687 : 
    C_0002644064770012110766 ..> C_0011146366150305476558 : 
    C_0002644064770012110766 ..> C_0016370386407813495429 : 
    C_0002644064770012110766 ..> C_0003496176270941337858 : 
    C_0002644064770012110766 ..> C_0011458867993025185835 : 
    C_0002644064770012110766 ..> C_0005160671499566832302 : 
    C_0002644064770012110766 ..> C_0013207976060429267904 : 
    C_0002644064770012110766 ..> C_0007158558504198085640 : 
    C_0002644064770012110766 ..> C_0002562295340752357913 : 
    C_0002644064770012110766 ..> C_0000744013708021145905 : 
    C_0002644064770012110766 ..> C_0009679823751851023587 : 
    C_0002644064770012110766 ..> C_0013071341770184119338 : 
    C_0002644064770012110766 ..> C_0005074114061636511327 : 
    C_0002644064770012110766 o-- "3" C_0017729851466359107363 : -value
    C_0005819674801799086687 ..|> C_0003341249818467524825 : 
    C_0005819674801799086687 ..> C_0004644561222112553426 : 
    C_0005819674801799086687 ..> C_0007482356929151537282 : 
    C_0005819674801799086687 ..> C_0011146366150305476558 : 
    C_0005819674801799086687 ..> C_0016370386407813495429 : 
    C_0005819674801799086687 ..> C_0002644064770012110766 : 
    C_0005819674801799086687 ..> C_0003496176270941337858 : 
    C_0005819674801799086687 ..> C_0005160671499566832302 : 
    C_0005819674801799086687 ..> C_0011458867993025185835 : 
    C_0005819674801799086687 ..> C_0013207976060429267904 : 
    C_0005819674801799086687 ..> C_0003014482284833559017 : 
    C_0005819674801799086687 ..> C_0003041513342711788422 : 
    C_0005819674801799086687 ..> C_0011641176337880010879 : 
    C_0005819674801799086687 ..> C_0006752072813915976143 : 
    C_0005819674801799086687 ..> C_0006967883322270155146 : 
    C_0005819674801799086687 ..> C_0002829408754176877928 : 
    C_0005819674801799086687 o-- "3" C_0013826567149110357089 : -value
    C_0011458867993025185835 ..|> C_0003341249818467524825 : 
    C_0011458867993025185835 ..> C_0004644561222112553426 : 
    C_0011458867993025185835 ..> C_0007482356929151537282 : 
    C_0011458867993025185835 ..> C_0005819674801799086687 : 
    C_0011458867993025185835 ..> C_0011146366150305476558 : 
    C_0011458867993025185835 ..> C_0016370386407813495429 : 
    C_0011458867993025185835 ..> C_0002644064770012110766 : 
    C_0011458867993025185835 ..> C_0003496176270941337858 : 
    C_0011458867993025185835 ..> C_0005160671499566832302 : 
    C_0011458867993025185835 ..> C_0013207976060429267904 : 
    C_0011458867993025185835 ..> C_0006250433396300995200 : 
    C_0011458867993025185835 ..> C_0018431782981220877824 : 
    C_0011458867993025185835 ..> C_0005568870174902212529 : 
    C_0011458867993025185835 ..> C_0001735402496744490083 : 
    C_0011458867993025185835 ..> C_0002328100515583017229 : 
    C_0011458867993025185835 ..> C_0003749456310058177537 : 
    C_0011458867993025185835 o-- "3" C_0015117083025601782618 : -value
    C_0005160671499566832302 ..|> C_0003341249818467524825 : 
    C_0005160671499566832302 ..> C_0004644561222112553426 : 
    C_0005160671499566832302 ..> C_0007482356929151537282 : 
    C_0005160671499566832302 ..> C_0005819674801799086687 : 
    C_0005160671499566832302 ..> C_0011146366150305476558 : 
    C_0005160671499566832302 ..> C_0016370386407813495429 : 
    C_0005160671499566832302 ..> C_0002644064770012110766 : 
    C_0005160671499566832302 ..> C_0003496176270941337858 : 
    C_0005160671499566832302 ..> C_0013207976060429267904 : 
    C_0005160671499566832302 ..> C_0011458867993025185835 : 
    C_0005160671499566832302 ..> C_0012939722395153742105 : 
    C_0005160671499566832302 ..> C_0002562295340752357913 : 
    C_0005160671499566832302 ..> C_0000744013708021145905 : 
    C_0005160671499566832302 ..> C_0009679823751851023587 : 
    C_0005160671499566832302 ..> C_0015343613012722578758 : 
    C_0005160671499566832302 ..> C_0018137455377658113550 : 
    C_0005160671499566832302 ..> C_0002612782377231333730 : 
    C_0005160671499566832302 o-- "4" C_0017729851466359107363 : -value
    C_0013207976060429267904 ..|> C_0003341249818467524825 : 
    C_0013207976060429267904 ..> C_0004644561222112553426 : 
    C_0013207976060429267904 ..> C_0007482356929151537282 : 
    C_0013207976060429267904 ..> C_0005819674801799086687 : 
    C_0013207976060429267904 ..> C_0011146366150305476558 : 
    C_0013207976060429267904 ..> C_0016370386407813495429 : 
    C_0013207976060429267904 ..> C_0002644064770012110766 : 
    C_0013207976060429267904 ..> C_0003496176270941337858 : 
    C_0013207976060429267904 ..> C_0005160671499566832302 : 
    C_0013207976060429267904 ..> C_0011458867993025185835 : 
    C_0013207976060429267904 ..> C_0005240039574280005964 : 
    C_0013207976060429267904 ..> C_0003041513342711788422 : 
    C_0013207976060429267904 ..> C_0011641176337880010879 : 
    C_0013207976060429267904 ..> C_0006752072813915976143 : 
    C_0013207976060429267904 ..> C_0013950690972887294632 : 
    C_0013207976060429267904 ..> C_0015886820764840174752 : 
    C_0013207976060429267904 ..> C_0005994545668144513265 : 
    C_0013207976060429267904 o-- "4" C_0013826567149110357089 : -value
    C_0011146366150305476558 ..|> C_0003341249818467524825 : 
    C_0011146366150305476558 ..> C_0004644561222112553426 : 
    C_0011146366150305476558 ..> C_0007482356929151537282 : 
    C_0011146366150305476558 ..> C_0005819674801799086687 : 
    C_0011146366150305476558 ..> C_0016370386407813495429 : 
    C_0011146366150305476558 ..> C_0002644064770012110766 : 
    C_0011146366150305476558 ..> C_0003496176270941337858 : 
    C_0011146366150305476558 ..> C_0005160671499566832302 : 
    C_0011146366150305476558 ..> C_0011458867993025185835 : 
    C_0011146366150305476558 ..> C_0013207976060429267904 : 
    C_0011146366150305476558 ..> C_0002542626888380986777 : 
    C_0011146366150305476558 ..> C_0018431782981220877824 : 
    C_0011146366150305476558 ..> C_0005568870174902212529 : 
    C_0011146366150305476558 ..> C_0001735402496744490083 : 
    C_0011146366150305476558 ..> C_0000666527147189690843 : 
    C_0011146366150305476558 ..> C_0014752931553855831377 : 
    C_0011146366150305476558 ..> C_0009066338652054392650 : 
    C_0011146366150305476558 o-- "4" C_0015117083025601782618 : -value
    C_0011188896363051785620 ..|> C_0004374069224809106111 : 
    C_0008671907212119285262 ..|> C_0003341249818467524825 : 
    C_0002680935233270452008 ..|> C_0004644561222112553426 : 
    C_0006233718487001977294 ..|> C_0004644561222112553426 : 
    C_0007440443376641485314 ..|> C_0006992479837074144199 : 
    C_0017297655928961336862 ..|> C_0006992479837074144199 : 
    C_0014214357445942724006 ..|> C_0004644561222112553426 : 
    C_0003647233661022599932 ..|> C_0004644561222112553426 : 
    C_0009213554402760339732 ..|> C_0002680935233270452008 : 
    C_0008273115442750733243 ..|> C_0017729851466359107363 : 
    C_0007349285277881282082 ..|> C_0006992479837074144199 : 
    C_0000393330291159126666 ..|> C_0014214357445942724006 : 
    C_0007738342842735842760 ..|> C_0006992479837074144199 : 
    C_0001480511873190358840 ..|> C_0006992479837074144199 : 
    C_0003169570570284995763 ..|> C_0006992479837074144199 : 
    C_0017579246165008318491 ..|> C_0002680935233270452008 : 
    C_0013264287076913777274 ..|> C_0006233718487001977294 : 
    C_0000584639886873075723 ..|> C_0002680935233270452008 : 
    C_0006108922882648812355 ..|> C_0006233718487001977294 : 
    C_0004416552121781064540 ..|> C_0013826567149110357089 : 
    C_0006340795772159705450 ..|> C_0003647233661022599932 : 
    C_0001531959356999801914 ..|> C_0006992479837074144199 : 
    C_0015297257712248839377 ..|> C_0006233718487001977294 : 
    C_0007799094981529459976 ..|> C_0002680935233270452008 : 
    C_0009885674740766927855 ..|> C_0014214357445942724006 : 
    C_0011515491856034123398 ..|> C_0014214357445942724006 : 
    C_0009113158509162214328 ..|> C_0015117083025601782618 : 
    C_0002799507906886402350 ..|> C_0003341249818467524825 : 
    C_0000635961036550666236 ..|> C_0017729851466359107363 : 
    C_0012618043414258396134 ..|> C_0002799507906886402350 : 
    C_0003628958744696471083 ..|> C_0007482356929151537282 : 
    C_0008407781152313292760 ..|> C_0003341249818467524825 : 
    C_0015377508743783301968 ..|> C_0013826567149110357089 : 
    C_0005252436267332410041 ..|> C_0008407781152313292760 : 
    C_0011645150379937564510 ..|> C_0016370386407813495429 : 
    C_0007323870670253339346 ..|> C_0003341249818467524825 : 
    C_0002590457629089863094 ..|> C_0015117083025601782618 : 
    C_0009262037211467414844 ..|> C_0007323870670253339346 : 
    C_0013406485112655065712 ..|> C_0003496176270941337858 : 
    C_0007158558504198085640 ..|> C_0003341249818467524825 : 
    C_0002562295340752357913 ..|> C_0017729851466359107363 : 
    C_0000744013708021145905 ..|> C_0017729851466359107363 : 
    C_0009679823751851023587 ..|> C_0017729851466359107363 : 
    C_0013071341770184119338 ..|> C_0007158558504198085640 : 
    C_0005074114061636511327 ..|> C_0002644064770012110766 : 
    C_0003014482284833559017 ..|> C_0003341249818467524825 : 
    C_0003041513342711788422 ..|> C_0013826567149110357089 : 
    C_0011641176337880010879 ..|> C_0013826567149110357089 : 
    C_0006752072813915976143 ..|> C_0013826567149110357089 : 
    C_0006967883322270155146 ..|> C_0003014482284833559017 : 
    C_0002829408754176877928 ..|> C_0005819674801799086687 : 
    C_0006250433396300995200 ..|> C_0003341249818467524825 : 
    C_0018431782981220877824 ..|> C_0015117083025601782618 : 
    C_0005568870174902212529 ..|> C_0015117083025601782618 : 
    C_0001735402496744490083 ..|> C_0015117083025601782618 : 
    C_0002328100515583017229 ..|> C_0006250433396300995200 : 
    C_0003749456310058177537 ..|> C_0011458867993025185835 : 
    C_0012939722395153742105 ..|> C_0003341249818467524825 : 
    C_0015343613012722578758 ..|> C_0017729851466359107363 : 
    C_0018137455377658113550 ..|> C_0012939722395153742105 : 
    C_0002612782377231333730 ..|> C_0005160671499566832302 : 
    C_0005240039574280005964 ..|> C_0003341249818467524825 : 
    C_0013950690972887294632 ..|> C_0013826567149110357089 : 
    C_0015886820764840174752 ..|> C_0005240039574280005964 : 
    C_0005994545668144513265 ..|> C_0013207976060429267904 : 
    C_0002542626888380986777 ..|> C_0003341249818467524825 : 
    C_0000666527147189690843 ..|> C_0015117083025601782618 : 
    C_0014752931553855831377 ..|> C_0002542626888380986777 : 
    C_0009066338652054392650 ..|> C_0011146366150305476558 : 
    C_0006496420822577250664 ..|> C_0006233718487001977294 : 
    C_0014763068788445555214 ..|> C_0006992479837074144199 : 
    C_0006913028124951340361 ..|> C_0017729851466359107363 : 
    C_0006037099869997505870 ..|> C_0013826567149110357089 : 
    C_0009987711875836095733 ..|> C_0015117083025601782618 : 
    C_0013196630619216501404 ..|> C_0004644561222112553426 : 
    C_0014681837414112849335 ..|> C_0004644561222112553426 : 
    C_0015533553309687146323 ..|> C_0013196630619216501404 : 
    C_0002339717429297086658 ..|> C_0013196630619216501404 : 
    C_0012357224610396939295 ..|> C_0003341249818467524825 : 
    C_0011796970895248346011 ..|> C_0004644561222112553426 : 
    C_0006078164231675980417 ..|> C_0004644561222112553426 : 
    C_0010515325766882995808 ..|> C_0003341249818467524825 : 
    C_0005910766257447474394 ..|> C_0013196630619216501404 : 
    C_0017876784243538906311 ..|> C_0004374069224809106111 : 
    C_0014354026446901727947 ..|> C_0017876784243538906311 : 
    C_0007055789189056520623 ..|> C_0011188896363051785620 : 
    C_0004374069224809106111 ..> C_0011188896363051785620 : 
    C_0004374069224809106111 ..> C_0013826567149110357089 : 
    C_0004374069224809106111 ..> C_0004644561222112553426 : 
    C_0004374069224809106111 ..> C_0005819674801799086687 : 
    C_0004374069224809106111 ..> C_0003341249818467524825 : 
    C_0004374069224809106111 ..> C_0011146366150305476558 : 
    C_0004374069224809106111 ..> C_0017876784243538906311 : 
    C_0004374069224809106111 ..> C_0014354026446901727947 : 
    C_0004374069224809106111 ..> C_0007055789189056520623 : 
    C_0011488344290179284903 ..|> C_0004374069224809106111 : 
    C_0013254656602862708639 ..|> C_0013196630619216501404 : 
    C_0015287454434830901127 o-- C_0000992201366918662950 : +order
    C_0015686980712366425392 ..|> C_0008924982355675107846 : 
    C_0018214676362562519909 o-- C_0015686980712366425392 : -bss_
    C_0000983062377794867882 o-- C_0000992201366918662950 : +value
    C_0007292912074049978292 ..|> C_0005525107945907675659 : 
    C_0007842129001496693911 ..|> C_0005525107945907675659 : 
    C_0011936113789382667383 ..|> C_0007842129001496693911 : 
    C_0005173775244095450180 ..|> C_0007292912074049978292 : 
    C_0005525107945907675659 ..> C_0004374069224809106111 : 
    C_0005525107945907675659 ..> C_0007292912074049978292 : 
    C_0005525107945907675659 ..> C_0013826567149110357089 : 
    C_0005525107945907675659 ..> C_0004644561222112553426 : 
    C_0005525107945907675659 ..> C_0003496176270941337858 : 
    C_0005525107945907675659 ..> C_0003341249818467524825 : 
    C_0005525107945907675659 ..> C_0011458867993025185835 : 
    C_0005525107945907675659 ..> C_0007842129001496693911 : 
    C_0005525107945907675659 ..> C_0011936113789382667383 : 
    C_0005525107945907675659 ..> C_0005173775244095450180 : 
    C_0005525107945907675659 o-- C_0011188896363051785620 : +real
    C_0005525107945907675659 o-- C_0011188896363051785620 : +dual
    C_0004783552046564859349 ..> C_0013196630619216501404 : 
    C_0004783552046564859349 ..|> C_0011998453723586013173 : 
    C_0008955661703058417682 ..> C_0012357224610396939295 : 
    C_0008955661703058417682 ..|> C_0011998453723586013173 : 
    C_0002068548501378321393 ..> C_0011188896363051785620 : 
    C_0002068548501378321393 ..|> C_0011998453723586013173 : 
    C_0005096865161113873283 ..> C_0007292912074049978292 : 
    C_0005096865161113873283 ..|> C_0011998453723586013173 : 
    C_0015845617936909777618 ..|> C_0006233718487001977294 : 
    C_0000988119665543839647 ..|> C_0002680935233270452008 : 
    C_0002150523681706585836 ..|> C_0014214357445942724006 : 
    C_0007936313636513776711 ..|> C_0003647233661022599932 : 
    C_0018152860825089234728 ..|> C_0013196630619216501404 : 
    C_0000681432894223718122 ..|> C_0013196630619216501404 : 
    C_0009222464995968348686 ..|> C_0013196630619216501404 : 
    C_0008853184901211021314 ..|> C_0013196630619216501404 : 
    C_0012032323483750771488 ..|> C_0013196630619216501404 : 
    C_0007809409934040091628 ..|> C_0013196630619216501404 : 
    C_0018322837704872918466 ..|> C_0013196630619216501404 : 
    C_0010754039428584179960 ..|> C_0013196630619216501404 : 
    C_0006841163757347700305 ..|> C_0013196630619216501404 : 
    C_0004114593519074939539 ..|> C_0013196630619216501404 : 
    C_0002753253780038737632 ..|> C_0013196630619216501404 : 
    C_0006761073196897303396 ..> C_0004842393136000246713 : 
    C_0015974733186916866267 ..> C_0002649638607837852567 : 
    C_0015974733186916866267 o-- C_0002280536835303751986 : -m_selectedDifficulty
    C_0015974733186916866267 o-- C_0000933547394081598572 : -m_selectedColor
    C_0008047285621877002607 --> C_0004842393136000246713 : -m_game
    C_0008047285621877002607 --> C_0004306397417237529713 : -m_aiController
    C_0008047285621877002607 o-- C_0015974733186916866267 : -m_menu
    C_0008047285621877002607 o-- C_0004693359074816351727 : -m_appState
    C_0008047285621877002607 o-- C_0002531126229291306321 : -m_view2D
    C_0008047285621877002607 o-- C_0006761073196897303396 : -m_view3D

%% Generated with clang-uml, version 0.6.2
%% LLVM version Homebrew clang version 21.1.8
```


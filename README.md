CHESS
(multiplayer chess game for two players)
1.	Application consists of 7 scenes and tests for main logic:
-	GameMenu scene;
-	MainGame scene (player vs player);
-	SaveGame scene;
-	LoadGame scene;
-	CustomGame scene;
-	GameSettings scene;
-	QuitGame scene.
2.	App validates all moves (if a player wants to make a move that is not allowed by chess rules, app blocks such attempt and shows corresponding notification).
3.	App correctly handles such chess rules:
-	castling;
-	En passant move;
-	promotion (to Queen, Bishop, Knight, Rook);
-	check;
-	checkmate;
-	draw (stalemate, impossibility of checkmate (two kings left, king and knight versus king, king with/without bishop versus king and bishop/bishops on the same color);
4.	Games can be saved and resumed after loading (including information for castling, En passant, previous moves and used time for both players).
5.	CustomGame scene allows to deploy figures manually and start new game.
6.	GameSettings scene provides management for music / sounds volume.
7.	Couldn’t connect Google tests to solution properly (placed topic on https://discuss.cocos2d-x.org), so I implemented own tests for main game logic            (needs to “#define PERFORM_TESTS 1” in AppDelegate.cpp to run and in NewGameScene.cpp to show result in scrollView).

IDE: Microsoft Visual Studio 2019 Community edition
Cocos2d-x-3.17.2

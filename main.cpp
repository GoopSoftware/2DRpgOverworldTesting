#include "raylib.h"
#include "raymath.h"
#include "Game.h"


const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 600;

Game game;

int main() {

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Overworld Testing");
	SetTargetFPS(60);
	game.gameStartup();

	while (!WindowShouldClose()) {
		
		game.gameUpdate();

		BeginDrawing();
		ClearBackground(GRAY);
		game.gameRender();
		EndDrawing();
	
	}

	CloseWindow();
	game.gameShutdown();
	return 0;
}
#include "Game.h"



void Game::gameStartup() {
	InitAudioDevice();

	Image image = LoadImage("assets/colored_tilemap_packed.png");
	textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
	UnloadImage(image);

	for (int i = 0; i < WORLD_WIDTH; i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			world[i][j] = sTile
			{
				i, 
				j 
			};
		}
	}

	player.x = TILE_WIDTH * 3;
	player.y = TILE_HEIGHT* 3;

	camera.target = Vector2{ static_cast<float>(player.x), static_cast<float>(player.y) };
	camera.offset = Vector2{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	camera.rotation = 0.f;
	camera.zoom = 3.f;

}

void Game::gameUpdate() {

	float x = player.x;
	float y = player.y;

	if (IsKeyPressed(KEY_LEFT)) x -= 1 * TILE_WIDTH;
	if (IsKeyPressed(KEY_RIGHT)) x += 1 * TILE_WIDTH;
	if (IsKeyPressed(KEY_UP)) y -= 1 * TILE_WIDTH;
	if (IsKeyPressed(KEY_DOWN)) y += 1 * TILE_WIDTH;

	float wheel = GetMouseWheelMove();

	if (wheel != 0) {
		const float zoomIncrement = 0.250f;
		camera.zoom += (wheel * zoomIncrement);
		if (camera.zoom < 3.f) camera.zoom = 3.f;
		if (camera.zoom > 8.f) camera.zoom = 8.f;
	}

	player.x = x;
	player.y = y;

	camera.target = (Vector2{ static_cast<float>(player.x), static_cast<float>(player.y) });
}

void Game::drawTile(int posX, int posY, int texture_index_x, int texture_index_y) {

	Rectangle source = { static_cast<float>(texture_index_x * TILE_WIDTH),
								 static_cast<float>(texture_index_y * TILE_HEIGHT),
								 static_cast<float>(TILE_WIDTH),
								 static_cast<float>(TILE_HEIGHT) };
	Rectangle dest = { static_cast<float>(posX),
							 static_cast<float>(posY),
							 static_cast<float>(TILE_WIDTH),
							 static_cast<float>(TILE_HEIGHT) };
	Vector2 origin = { 0, 0 };

	DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
}

void Game::gameRender() {

	BeginMode2D(camera);

	sTile tile;
	int texture_index_x = 0;
	int texture_index_y = 0;
	for (int i = 0; i < WORLD_WIDTH; i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			tile = world[i][j];

			texture_index_x = 4;
			texture_index_y = 4;

			drawTile(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y);

		}
	}

	drawTile(camera.target.x, camera.target.y, 4, 0);



	EndMode2D();

	DrawRectangle(5, 5, 330, 120, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(5, 5, 330, 120, BLUE);
	DrawText(TextFormat("Camera Target: (%06.2f, %06.2f)", camera.target.x, camera.target.y), 15, 10, 14, YELLOW);
	DrawText(TextFormat("Camera Zoom: %06.2f", camera.zoom), 15, 30, 14, YELLOW);

}


void Game::gameShutdown() {

	CloseAudioDevice();
	for (int i = 0; i < MAX_TEXTURES; i++) {
		UnloadTexture(textures[i]);
	}

}
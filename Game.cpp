#include "Game.h"
#include "InputHandler.h"
#include <iostream>
#include <string>


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
				j,
				GetRandomValue(TILE_TYPE_DIRT, TILE_TYPE_STONE)
			};

			dungeon[i][j] = sTile
			{
				i,
				j,
				TILE_TYPE_DIRT
			};
		}
	}

	// initialized locations
	player->initialize(4, 4, ZONE_WORLD);
	dungeonGate->initialize(10, 10, ZONE_ALL);
	orc->initialize(5, 5, ZONE_DUNGEON);


	// Make camera follow player
	camera.target = Vector2{ static_cast<float>(player->i_), static_cast<float>(player->j_) };
	camera.offset = Vector2{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	camera.rotation = 0.f;
	camera.zoom = 3.f;

}

void Game::gameUpdate() {

	interactTarget = nullptr;

	int oi = abs(player->i_ - orc->i_);
	int oj = abs(player->j_ - orc->j_);
	if (oi + oj <= TILE_WIDTH && player->zone_ == ZONE_DUNGEON && orc->isAlive_) {
		interactTarget = orc;
	}

	int di = abs(player->i_ - dungeonGate->i_);
	int dj = abs(player->j_ - dungeonGate->j_);
	if (di + dj <= TILE_WIDTH) {
		interactTarget = dungeonGate;
	}

	Command* command = InputHandler::handleInput(player, interactTarget);

	if (command) {
		command->execute();
		delete command;
	}

	if (interactTarget == orc) {
		if (IsKeyPressed(KEY_SPACE)) {
			
			orc->health_ -= player->attack();
			std::cout << orc->health_ << std::endl;

			if (!combatTextTimer.isActive) {
				combatTextTimer.isActive = true;
				startTimer(&combatTextTimer, .50f);
			}
		}
	}
	if (orc->health_ <= 0) {
		orc->isAlive_ = false;
	}


	float wheel = GetMouseWheelMove();

	if (wheel != 0) {
		const float zoomIncrement = 0.250f;
		camera.zoom += (wheel * zoomIncrement);
		if (camera.zoom < 3.f) camera.zoom = 3.f;
		if (camera.zoom > 8.f) camera.zoom = 8.f;
	}

	camera.target = (Vector2{ static_cast<float>(player->i_), static_cast<float>(player->j_) });

	if (isTimerDone(combatTextTimer)) {
		combatTextTimer.isActive = false;
	}

	
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
			
			if (player->zone_ == ZONE_WORLD) {
				tile = world[i][j];
			}
			else if (player->zone_ == ZONE_DUNGEON) {
				tile = dungeon[i][j];
			}

			switch (tile.type) {
			case TILE_TYPE_DIRT:
				texture_index_x = 1;
				texture_index_y = 1;
				break;
			case TILE_TYPE_GRASS:
				texture_index_x = 5;
				texture_index_y = 4;
				break;
			case TILE_TYPE_TREE:
				texture_index_x = 5;
				texture_index_y = 5;
				break;
			case TILE_TYPE_STONE:
				texture_index_x = 4;
				texture_index_y = 4;
				break;
			}

			drawTile(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y);

		}
	}

	// Render dungeon gate
	drawTile(dungeonGate->i_, dungeonGate->j_, 8, 9);

	if (orc->zone_ == player->zone_ && orc->isAlive_) {
		drawTile(orc->i_, orc->j_, 11, 0);
	}
	if (combatTextTimer.isActive) {
		DrawText(TextFormat("%d", player->damage_), orc->i_, orc->j_ - 10, 9, YELLOW);
	}
	
	// Render Player
	drawTile(player->i_, player->j_, 4, 0);


	EndMode2D();

	DrawRectangle(5, 5, 330, 120, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(5, 5, 330, 120, BLUE);
	DrawText(TextFormat("Camera Target: (%6.2f, %6.2f)", (camera.target.x / TILE_WIDTH), (camera.target.y / TILE_WIDTH)), 15, 10, 19, YELLOW);
	DrawText(TextFormat("Camera Zoom: %06.2f", camera.zoom), 15, 30, 19, YELLOW);
	if (interactTarget != nullptr) {
		DrawText(TextFormat("Interact Target: %s", interactTarget->debugName_), 15, 50, 19, YELLOW);
	}
	else {
		DrawText("Interact Target: ", 15, 50, 19, YELLOW);
	}

}


void Game::gameShutdown() {

	CloseAudioDevice();
	for (int i = 0; i < MAX_TEXTURES; i++) {
		UnloadTexture(textures[i]);
	}


	delete dungeonGate;
	dungeonGate = nullptr;
	delete player;
	player = nullptr;
	delete orc;
	orc = nullptr;

}


void Game::startTimer(Timer* timer, double lifetime) {
	timer->startTime = GetTime();
	timer->lifeTime = lifetime;
}

bool Game::isTimerDone(Timer timer) {
	return GetTime() - timer.startTime >= timer.lifeTime;
}

double Game::getElapsed(Timer timer) {
	return GetTime() - timer.startTime;
}
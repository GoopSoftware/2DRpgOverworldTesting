#include "Game.h"
#include "InputHandler.h"
#include <iostream>
#include <string>
#include "Combat.h"
#include "Spawner.h"
#include "raylib.h"
#include "LevelManager.h"

void Game::gameStartup() {
	InitAudioDevice();

	Image image = LoadImage("assets/colored_tilemap_packed.png");
	textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
	UnloadImage(image);

	levelManager = new LevelManager();
	levelManager->initializeOverWorld();
	levelManager->enterOverWorld();

	interactionSystem = new InteractionSystem(levelManager);

	levelRenderer = new LevelRenderer(textures);

	// This gets moved into LevelManager
	player = new Player(4, 4, ZONE_OVERWORLD);
	dungeonGate = new DungeonDoor(10, 10, ZONE_WORLD_AND_DUNGEON);

	// Spawner proof of concept
	Orc* prototype = new Orc(5, 5, ZONE_DUNGEON, 100, 12, 6);
	Spawner spawner(prototype);

	enemy1 = spawner.spawnEnemy(16, 14);
	enemy2 = spawner.spawnEnemy(14, 14);
	enemies.push_back(enemy1);
	enemies.push_back(enemy2);



	// Make camera follow player
	camera.target = Vector2{ static_cast<float>(player->i_), static_cast<float>(player->j_) };
	camera.offset = Vector2{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	camera.rotation = 0.f;
	camera.zoom = 3.f;

}

void Game::gameUpdate() {

	if (IsKeyPressed(KEY_Y)) {
		player->zone_ = ZONE_OVERWORLD;
		levelManager->enterOverWorld();
	}
	
	if (IsKeyPressed(KEY_U)) {
		player->zone_ = ZONE_WORLD;
		levelManager->enterWorld();
	}
	
	if (IsKeyPressed(KEY_I)) {
		player->zone_ = ZONE_DUNGEON;
		levelManager->enterDungeon();
	}

	// If player is + or -  allow interaction
	// interact target gets reset to nullptr every frame if there is no interaction target
	// Create an entity called interactTarget
	interactTarget = nullptr;
	for (Enemy* enemy : enemies) {
		int oi = abs(player->i_ - enemy->i_);
		int oj = abs(player->j_ - enemy->j_);
		if (oi + oj <= TILE_SIZE && player->zone_ == enemy->zone_ && enemy->isAlive_) {
			interactTarget = enemy;
		}
	}

	int di = abs(player->i_ - dungeonGate->i_);
	int dj = abs(player->j_ - dungeonGate->j_);
	if (di + dj <= TILE_SIZE && (player->zone_ == ZONE_WORLD || player->zone_ == ZONE_DUNGEON)) {
		interactTarget = dungeonGate;
	}

	// This is not a memory leak, handleInput() returns a nullptr if no command
	Command* command = InputHandler::handleInput(player, interactTarget, interactionSystem);


	if (command) {
		command->execute();
		delete command;
		command = nullptr;
	}

	for (Enemy* enemy : enemies) {
		if (interactTarget == enemy) {
			if (IsKeyPressed(KEY_SPACE)) {
				std::cout << enemy->health_ << std::endl;
				if (!combatTextTimer.isActive) {
					combatTextTimer.isActive = true;
					startTimer(&combatTextTimer, .50f);
				}
			}
		}
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

	Rectangle source = { static_cast<float>(texture_index_x * TILE_SIZE),
								 static_cast<float>(texture_index_y * TILE_SIZE),
								 static_cast<float>(TILE_SIZE),
								 static_cast<float>(TILE_SIZE) };
	Rectangle dest = { static_cast<float>(posX),
							 static_cast<float>(posY),
							 static_cast<float>(TILE_SIZE),
							 static_cast<float>(TILE_SIZE) };
	Vector2 origin = { 0, 0 };

	DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
}

void Game::gameRender() {

	BeginMode2D(camera);

	Level* currentLevel = levelManager->getCurrentLevel();
	if (levelRenderer != nullptr && currentLevel != nullptr) {
		levelRenderer->renderLevel(*currentLevel);
	}
	
	
	// temp old object rendering
	if (dungeonGate != nullptr && (player->zone_ == ZONE_WORLD || player->zone_ == ZONE_DUNGEON)) {
		drawTile(dungeonGate->i_, dungeonGate->j_, 8, 9);
	}


	// spawner rendering
	for (Enemy* enemy : enemies) {
		if (enemy->zone_ == player->zone_ && enemy->isAlive_) {
			drawTile(enemy->i_, enemy->j_, 11, 0);
		}
	}

	if (combatTextTimer.isActive && interactTarget != nullptr) {

		DrawText(TextFormat("%d", player->damage_), interactTarget->i_, interactTarget->j_ - 10, 9, YELLOW);
	}
	
	
	// Render Player
	drawTile(player->i_, player->j_, 4, 0);


	EndMode2D();

	DrawRectangle(5, 5, 330, 120, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(5, 5, 330, 120, BLUE);
	DrawText(TextFormat("Camera Target: (%6.2f, %6.2f)", (camera.target.x / TILE_SIZE), (camera.target.y / TILE_SIZE)), 15, 10, 19, YELLOW);
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

	delete levelRenderer;
	levelRenderer = nullptr;
	
	delete levelManager;
	levelManager = nullptr;

	delete dungeonGate;
	dungeonGate = nullptr;
	
	delete player;
	player = nullptr;

	delete interactionSystem;
	interactionSystem = nullptr;
	
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();

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
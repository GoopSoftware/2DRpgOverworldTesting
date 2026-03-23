#include "../game/Game.h"



void Game::gameStartup() {
	InitAudioDevice();

	overWorld = LoadTexture("assets/Overworld.png");
	playerTexture = LoadTexture("assets/Sprite1.png");
	
	Image image = LoadImage("assets/tilePack.png");
	
	textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
	UnloadImage(image);

	levelManager = new LevelManager();
	levelManager->initializeOverWorld();
	levelManager->enterOverWorld();

	interactionSystem = new InteractionSystem(levelManager);
	targetSystem = new TargetSystem();

	levelRenderer = new LevelRenderer(textures);

	player = new Player(1, 16, ZONE_OVERWORLD);

	// Make camera follow player
	camera.target = Vector2{ static_cast<float>(player->i_), static_cast<float>(player->j_) };
	camera.offset = Vector2{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	camera.rotation = 0.f;
	camera.zoom = 6.f;

}

void Game::gameUpdate() {

	// player animation
	timer += GetFrameTime();
	if (timer >= speed) {
		timer = 0;
		frame = (frame + 1) % 6;
	}


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

	targetSystem->update(player, levelManager);
	interactTarget = targetSystem->getCurrentTarget();


	// This is not a memory leak, handleInput() returns a nullptr if no command
	Command* command = InputHandler::handleInput(player, interactTarget, interactionSystem, targetSystem);


	if (command) {
		command->execute();
		delete command;
		command = nullptr;
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

void Game::drawTile(int posX, int posY, int texture_index_x, int texture_index_y, Color color) {

	Rectangle source = { static_cast<float>(texture_index_x * TILE_SIZE),
								 static_cast<float>(texture_index_y * TILE_SIZE),
								 static_cast<float>(TILE_SIZE),
								 static_cast<float>(TILE_SIZE) };
	Rectangle dest = { static_cast<float>(posX),
							 static_cast<float>(posY),
							 static_cast<float>(TILE_SIZE),
							 static_cast<float>(TILE_SIZE) };
	Vector2 origin = { 0, 0 };

	DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, color);
}



void Game::gameRender() {

	BeginMode2D(camera);

	Level* currentLevel = levelManager->getCurrentLevel();
	if (levelRenderer != nullptr && currentLevel != nullptr) {
		levelRenderer->renderLevel(*currentLevel);
	}
	
	
	if (levelManager->dungeonGate != nullptr && (player->zone_ == ZONE_WORLD || player->zone_ == ZONE_DUNGEON)) {
		drawTile(levelManager->dungeonGate->i_, levelManager->dungeonGate->j_, 8, 9, WHITE);
	}


	// spawner rendering
	for (Enemy* enemy : levelManager->worldEnemies) {
		if (enemy->zone_ == player->zone_ && enemy->isAlive_) {
			drawTile(enemy->i_, enemy->j_, 11, 0, WHITE);
		}
	}

	// spawner rendering
	for (Enemy* enemy : levelManager->dungeonEnemies) {
		if (enemy->zone_ == player->zone_ && enemy->isAlive_) {
			drawTile(enemy->i_, enemy->j_, 11, 0, WHITE);
		}
	}

	if (combatTextTimer.isActive && interactTarget != nullptr) {
		DrawText(TextFormat("%d", player->damage_), interactTarget->i_, interactTarget->j_ - 10, 9, YELLOW);
	}
	
	
	// Render Player
	int frameWidth = playerTexture.width / 6;

	Rectangle src = {
		static_cast<float>(frame * frameWidth),
		0,
		static_cast<float>(frameWidth),
		static_cast<float>(playerTexture.height)
	};

	if (player->zone_ == ZONE_OVERWORLD) {
		DrawTextureEx(overWorld, Vector2(0.f, 0.f), 0.f, 1.f, WHITE);
		DrawTextureRec(playerTexture, src, { static_cast<float>(player->i_), static_cast<float>(player->j_)}, WHITE);
	}
	else {
		DrawTextureRec(playerTexture, src, { static_cast<float>(player->i_), static_cast<float>(player->j_) }, WHITE);
	}


	EndMode2D();

	/*DrawRectangle(5, 5, 330, 120, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(5, 5, 330, 120, BLUE);
	DrawText(TextFormat("Camera Target: (%6.2f, %6.2f)", (camera.target.x / TILE_SIZE), (camera.target.y / TILE_SIZE)), 15, 10, 19, YELLOW);
	DrawText(TextFormat("Camera Zoom: %06.2f", camera.zoom), 15, 30, 19, YELLOW);
	if (interactTarget != nullptr) {
		DrawText(TextFormat("Interact Target: %s", interactTarget->debugName_), 15, 50, 19, YELLOW);
	}
	else {
		DrawText("Interact Target: ", 15, 50, 19, YELLOW);
	}*/

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
	
	delete player;
	player = nullptr;

	delete interactionSystem;
	interactionSystem = nullptr;

	delete targetSystem;
	targetSystem = nullptr;

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
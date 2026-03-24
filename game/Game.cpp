#include "../game/Game.h"



void Game::gameStartup() {
	InitAudioDevice();

	hitSound = LoadSound("assets/hitHurt.wav");

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

	deltaTime = GetFrameTime();
	updateFloatingText(deltaTime);

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

		handleCommandResult(command);

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

	renderFloatingText();

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

	// highlight current target
	if (interactTarget != nullptr && interactTarget->isAlive_) {
		DrawRectangleLinesEx(
			Rectangle{  static_cast<float>(interactTarget->i_),
						static_cast<float>(interactTarget->j_),
						static_cast<float>(TILE_SIZE),
						static_cast<float>(TILE_SIZE) },
						.25f,
						YELLOW
						);
	}

	EndMode2D();

	if (IsKeyPressed(KEY_P)) {
		debugWindow = !debugWindow;
	}
	if (debugWindow) {
		renderDebugWindow();
	}
}


void Game::gameShutdown() {

	UnloadSound(hitSound);
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

void Game::spawnFloatingText(const std::string& text, float x, float y) {
	FloatingText floatingText;
	floatingText.text = text;
	floatingText.x = x;
	floatingText.y = y;
	floatingText.elapsed = 0.0f;
	floatingText.lifetime = 0.75f;
	floatingText.active = true;

	floatingTexts.push_back(floatingText);
}

void Game::updateFloatingText(float deltaTime) {
	for (auto& floatingText : floatingTexts) {
		if (!floatingText.active) continue;

		floatingText.elapsed += deltaTime;
		floatingText.y -= 20.f * deltaTime;

		if (floatingText.elapsed >= floatingText.lifetime) {
			floatingText.active = false;
		}
	}

	// we want to control the iteration here to prevent erase messing up the iteration
	for (auto iteration = floatingTexts.begin(); iteration != floatingTexts.end();) {
		if (!iteration->active) {
			iteration = floatingTexts.erase(iteration);
		}
		else {
			iteration++;
		}
	}

}

void Game::renderFloatingText() {
	for (const auto& floatingText : floatingTexts) {
		DrawTextEx(GetFontDefault(), floatingText.text.c_str(), Vector2(floatingText.x + 1.5f, floatingText.y), 5.f, 1.f, YELLOW);
	}

}

void Game::handleCommandResult(Command* command) {

	// Derived* ptr = dynamic_cast<Derived*>(basePtr);
	// Convert base class to a derived class
	// For this case we need to turn that basic Command into a CombatCommand
	CombatCommand* combatCommand = dynamic_cast<CombatCommand*>(command);
	if (combatCommand) {
		PlaySound(hitSound);
		CombatResult result = combatCommand->getCombatResult();

		if (result.successfulHit && result.target) {
			spawnFloatingText(
				std::to_string(result.damage),
				static_cast<float>(result.target->i_),
				static_cast<float>(result.target->j_)
				);
		}
	}


}

void Game::renderDebugWindow() {
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

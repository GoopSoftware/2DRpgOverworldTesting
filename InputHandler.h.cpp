#include "InputHandler.h"
#include <raylib.h>
#include "MoveCommand.h"
#include <iostream>
#include "InteractCommand.h"
#include "CombatCommand.h"
#include "Combat.h"

static constexpr int TILE_SIZE = 8;

Command* InputHandler::handleInput(Entity* player, Entity* interactTarget) {

	if (IsKeyPressed(KEY_W)) { return new MoveCommand(player, 0, -TILE_SIZE); }
	if (IsKeyPressed(KEY_S)) { return new MoveCommand(player, 0, TILE_SIZE); }
	if (IsKeyPressed(KEY_A)) { return new MoveCommand(player, -TILE_SIZE, 0); }
	if (IsKeyPressed(KEY_D)) { return new MoveCommand(player, TILE_SIZE, 0); }

	if (IsKeyPressed(KEY_ENTER) && interactTarget) { return new InteractCommand(player, interactTarget); }
	if (IsKeyPressed(KEY_SPACE) && interactTarget) { return new CombatCommand(player, interactTarget); }
	
	return nullptr;
}

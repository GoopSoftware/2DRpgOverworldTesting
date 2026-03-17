#include "../input/InputHandler.h"


Command* InputHandler::handleInput(Entity* player, Entity* interactTarget, InteractionSystem* interactionSystem, TargetSystem* targetSystem) {

	if (IsKeyPressed(KEY_W)) { return new MoveCommand(player, 0, -TILE_SIZE); }
	if (IsKeyPressed(KEY_S)) { return new MoveCommand(player, 0, TILE_SIZE); }
	if (IsKeyPressed(KEY_A)) { return new MoveCommand(player, -TILE_SIZE, 0); }
	if (IsKeyPressed(KEY_D)) { return new MoveCommand(player, TILE_SIZE, 0); }

	if (IsKeyPressed(KEY_ENTER)) { return new InteractCommand(player, interactTarget, interactionSystem);}	
	if (IsKeyPressed(KEY_SPACE) && interactTarget) { return new CombatCommand(player, interactTarget); }
	if (IsKeyPressed(KEY_TAB)) { return new SwitchTargetCommand(targetSystem); }

	return nullptr;
}

#pragma once

#include <raylib.h>
#include <iostream>

#include "../commands/Command.h"
#include "../commands/MoveCommand.h"
#include "../commands/CombatCommand.h"
#include "../input/InputHandler.h"
#include "../input/InputHandler.h"
#include "../commands/InteractCommand.h"
#include "../interaction/InteractionSystem.h"
#include "../entities/Entity.h"
#include "../Constants.h"

class InputHandler
{

public:

	static Command* handleInput(Entity* player, Entity* interactTarget, InteractionSystem* interactionSystem);


private:




};
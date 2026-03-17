#pragma once

#include <raylib.h>
#include <iostream>

#include "../commands/Command.h"
#include "../commands/MoveCommand.h"
#include "../commands/CombatCommand.h"
#include "../commands/InteractCommand.h"
#include "../interaction/InteractionSystem.h"
#include "../entities/Entity.h"
#include "../Constants.h"
#include "../commands/SwitchTargetCommand.h"
#include "../interaction/TargetSystem.h"


class InputHandler
{

public:

	static Command* handleInput(Entity* player, Entity* interactTarget, InteractionSystem* interactionSystem, TargetSystem* targetSystem);


private:




};
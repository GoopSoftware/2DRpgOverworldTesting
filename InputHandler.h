#pragma once

#include "Command.h"
#include "InteractionSystem.h"

class InputHandler
{

public:

	static Command* handleInput(Entity* player, Entity* interactTarget, InteractionSystem* interactionSystem);


private:




};
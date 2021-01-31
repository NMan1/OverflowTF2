#pragma once
#include "../utils/game/misc.hpp"

class IEngineVGui
{
public:
	virtual					~IEngineVGui(void) { }
	virtual unsigned int	get_panel(VGuiPanel_t type) = 0;
	virtual bool			is_game_ui_visible() = 0;
};

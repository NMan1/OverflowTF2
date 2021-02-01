#pragma once
#include "../utils/game/structs.hpp"

class i_engine_vgui
{
public:
	virtual					~i_engine_vgui(void) { }
	virtual unsigned int	get_panel(vgui_panel_t type) = 0;
	virtual bool			is_game_ui_visible() = 0;
};

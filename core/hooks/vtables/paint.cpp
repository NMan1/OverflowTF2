#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../utils/game/draw.hpp"
#include "../../features/visuals/esp.hpp"

namespace ICONS
{
	 constexpr int WIDHT = 64;
	 constexpr int HEIGHT = 64;
	 constexpr int TEXTURE_AMOUNT = 30;
	 constexpr int UNDEFINED = -1;

	 int ID[TEXTURE_AMOUNT] =
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};

	 std::string TEXTURE[TEXTURE_AMOUNT] =
	{
		"hud/leaderboard_class_teleporter.vtf",
		"hud/leaderboard_class_scout.vtf",
		"hud/leaderboard_class_sniper.vtf",
		"hud/leaderboard_class_soldier.vtf",
		"hud/leaderboard_class_demo.vtf",
		"hud/leaderboard_class_medic.vtf",
		"hud/leaderboard_class_heavy.vtf",
		"hud/leaderboard_class_pyro.vtf",
		"hud/leaderboard_class_spy.vtf",
		"hud/leaderboard_class_engineer.vtf",
		"hud/eng_build_sentry.vtf",
		"hud/class_scoutred.vtf",
		"hud/class_sniperred.vtf",
		"hud/class_soldierred.vtf",
		"hud/class_demored.vtf",
		"hud/class_medicred.vtf",
		"hud/class_heavyred.vtf",
		"hud/class_pyrored.vtf",
		"hud/class_spyred.vtf",
		"hud/class_engired.vtf",
		"vgui/class_portraits/spy_blue_grey.vtf",
		"hud/class_scoutblue.vtf",
		"hud/class_sniperblue.vtf",
		"hud/class_soldierblue.vtf",
		"hud/class_demoblue.vtf",
		"hud/class_medicblue.vtf",
		"hud/class_heavyblue.vtf",
		"hud/class_pyroblue.vtf",
		"hud/class_spyblue.vtf",
		"hud/class_engiblue.vtf",
	};
}

void Texture(int x, int y, int w, int h, int nIndex)
{
	static int nTexture = 0;

	if (ICONS::ID[nIndex] != ICONS::UNDEFINED)
	{
		nTexture = ICONS::ID[nIndex];
	}
	else
	{
		nTexture = interfaces::surface->CreateNewTextureID();
		interfaces::surface->DrawSetTextureFile(nTexture, ICONS::TEXTURE[nIndex].c_str(), true, true);
		ICONS::ID[nIndex] = nTexture;
	}

	interfaces::surface->set_color(255, 255, 255, 255);
	interfaces::surface->DrawSetTexture(nTexture);
	interfaces::surface->DrawTexturedRect(x, y, w, h);
}


void __stdcall hooks::engine_vgui::paint::fn(int mode) {
	static auto start_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto finish_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));
	static auto init = false;

	if (!init) {
		draw::init();
		init = true;
	}

	m_paint->get_original<t>(index)(interfaces::engine_vgui, mode);

	if (mode & PAINT_UIPANELS) {
		start_drawing(interfaces::surface);

		draw::text("Overflow", vector2D(10, 10), color(255, 0, 0));
		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected()) {
			esp::run();
		}

		finish_drawing(interfaces::surface);
	}
}
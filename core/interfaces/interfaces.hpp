#pragma once

#include "..\source-sdk\CHandle.h"
#include "..\source-sdk\IClientNetworkable.h"
#include "..\source-sdk\IBaseClientDLL.h"
#include "..\source-sdk\IVEngineClient.h"
#include "..\source-sdk\IEntity.h"
#include "..\source-sdk\Panels.h"
#include "..\source-sdk\ISurface.h"
#include "..\source-sdk\IVDebugOverlay.h"
#include "..\source-sdk\IPlayerInfoManager.h"
#include "../source-sdk/EngineVGui.h"

namespace interfaces {
	extern IBaseClientDLL* client_dll;
	extern IVEngineClient* engine;
	extern IClientEntityList* entity_list;
	extern IGlobalVars* globals;
	extern IClientModeShared* client_mode;
	extern Panel* panels;
	extern ISurface* surface;
	extern IEngineVGui* engine_vgui;
	extern IVDebugOverlay* debug_overlay;
	extern IPlayerInfoManager* player_info;

	void init_interfaces();
}
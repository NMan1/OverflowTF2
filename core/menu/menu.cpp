#include "menu.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/dx9/imgui_impl_dx9.h"

#include <vector>

#include "..\utils\utils.hpp"
#include "../utils/color.hpp"
#include "../interfaces/interfaces.hpp"
#include "../utils/settings/settings.hpp"

void* utils::tf2_window;

namespace menu {
	bool open = false;

	ImFont* font_tabs = nullptr;

	ImFont* font_normal = nullptr;

	IDirect3DStateBlock9* state_block = nullptr;

	void aimbot_page();

	void visuals_page();

	void misc_page();

	void others_page();

	void players_page();

	void settings_page();

	void __stdcall create_objects(IDirect3DDevice9* device) {
		if (utils::tf2_window)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	void __stdcall invalidate_objects() {
		ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void setup_fonts() {
		ImGui::CreateContext();

		font_tabs = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16);
		font_normal = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14);
	}

	float clip(float n, float lower, float upper) {
		n = (n > lower) * n + !(n > lower) * lower;
		return (n < upper) * n + !(n < upper) * upper;
	}

	void __stdcall end_present(IDirect3DDevice9* device) {
		//if (open) 
		//{
		//	if (ImGui::GetStyle().Alpha > 1.f)
		//		ImGui::GetStyle().Alpha = 1.f;
		//	else if (ImGui::GetStyle().Alpha != 1.f)
		//		ImGui::GetStyle().Alpha += 0.008f;
		//}
		//else
		//	ImGui::GetStyle().Alpha = 0.f;

		ImGui::Render();

		state_block->Apply();
		state_block->Release();
	}

	void __stdcall pre_render(IDirect3DDevice9* device) {
		D3DVIEWPORT9 d3d_viewport;
		device->GetViewport(&d3d_viewport);

		device->CreateStateBlock(D3DSBT_ALL, &state_block);
		state_block->Capture();

		device->SetVertexShader(nullptr);
		device->SetPixelShader(nullptr);
		device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

		device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetRenderState(D3DRS_FOGENABLE, FALSE);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

		device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
	}

	void __stdcall post_render() {
		ImGui_ImplDX9_NewFrame();
	}

	void __stdcall setup_resent(IDirect3DDevice9* device) {
		ImGui_ImplDX9_Init(utils::tf2_window, device);

		ImGuiStyle& style = ImGui::GetStyle();
		style.Alpha = 1.f;
		style.WindowPadding = ImVec2(0, 0); // 8 or 9 x
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 0.0f;
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.ChildWindowRounding = 0.0f;
		style.FramePadding = ImVec2(4, 3);
		style.FrameRounding = 0.0f;
		style.ItemSpacing = ImVec2(8, 8);
		style.ItemInnerSpacing = ImVec2(8, 8);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 0.0f;
		style.ScrollbarSize = 6.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 0.0f;
		style.ButtonTextAlign = ImVec2(0.0f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;
		style.AntiAliasedShapes = false;
		style.CurveTessellationTol = 1.f;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1, 1, 1, .8); // grey
		//colors[ImGuiCol_Text] = ImVec4(.6f, .6f, .6f, 1.00f); // grey
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
		colors[ImGuiCol_WindowBg] = { 0.133, 0.133, 0.133, 1.0f};
		colors[ImGuiCol_ChildWindowBg] = { 0.149, 0.149, 0.149, 1 };
		colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
		colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 1.f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.f, 0, 0, .0f);
		colors[ImGuiCol_FrameBg] = { 0.149, 0.149, 0.149, 1 };
		colors[ImGuiCol_FrameBgHovered] = ImVec4(.6f, .6f, .6f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.25f, 0.30f, 1.0f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
		colors[ImGuiCol_ScrollbarGrab] = { 1, 0.321, 0.321, .70f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1, 0.321, 0.321, .80f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1, 0.321, 0.321, .80f);
		colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
		colors[ImGuiCol_Separator] = ImVec4(0.654, 0.094, 0.278, 1.f);
		//colors[ImGuiCol_CheckMark] = { 1, 1, 1, .6 };
		colors[ImGuiCol_CheckMark] = { 1, 0.027, 0.227, 1 };
		colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.); //multicombo, combo selected item color.
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
		colors[ImGuiCol_CloseButton] = ImVec4(0.10f, 0.10f, 0.10f, 0.50f);
		colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		create_objects(device);
	}

	void render() {
		const ImVec2 window_size = { 500, 300 };
		static int page = 0;
		const std::vector<std::pair<std::string, void(*)()>> tabs = { {"aimbot", aimbot_page}, {"visuals", visuals_page}, {"misc", misc_page},
															  {"others", others_page}, {"players", players_page}, {"settings", settings_page} };

		ImGui::SetNextWindowSize(ImVec2(utils::screen_x, utils::screen_y));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Background", &menu::open, ImVec2(utils::screen_x, utils::screen_y), .45, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove); {
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.568, 0.533, 0.533, .2f));
			ImGui::PopStyleColor();
		}
		ImGui::End();
	
		ImGui::SetNextWindowSize(window_size);
		ImGui::Begin("overflow", &menu::open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar); {
			ImGui::PushStyleColor(ImGuiCol_Border, { 0.254, 0.254, 0.254, 1.0f });
			ImGui::SetCursorPos({5, 5}); // our "margins"
			ImGui::BeginChild("background pane", { window_size.x - 10, window_size.y - 10 }, true); { // gives 5 pixel space on every side 
				auto window_pos = ImGui::GetWindowPos();
				ImGui::GetWindowDrawList()->AddRectFilled({ window_pos.x, window_pos.y }, { window_pos.x + window_size.x, window_pos.y  + 2 }, ImGui::ColorConvertFloat4ToU32({ 1, 0.027, 0.227, 1 }));
			}
			ImGui::EndChild();

			ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, { 0.176, 0.176, 0.176, 1.0 });
			ImGui::SetCursorPos({ 20, 20 }); 
			ImGui::BeginChild("tabs pane", { 100, 260 }, true); {
				ImGui::PushFont(font_tabs);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 100 * .10);
				for (auto &tab : tabs) {
					auto index = std::find(tabs.begin(), tabs.end(), tab) - tabs.begin();
					auto size = ImGui::CalcTextSize(tab.first.c_str());
					size = { size.x + 5, size.y + 4 };

					ImGui::SetCursorPosX(100 * .10);
					if (ImGui::ButtonT(tab.first.c_str(), size, page, index, false, false)) {
						page = index;
					}
				}
				ImGui::PopFont();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos({ 20 + 100 + 15, 20 });
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(13, 16));
			ImGui::BeginChild("settings pane", { 345, 260 }, true); {
				tabs.at(page).second();
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		ImGui::End();
	}

	void aimbot_page() {
		ImGui::Checkbox("enable aimbot", &settings::aimbot);
		ImGui::SliderInt("fov", &settings::aimbot_fov, 0, 360);
		ImGui::SliderFloat("smoothness", &settings::aimbot_smoothness, 0, 10, "%.1f");
	}	
	
	void visuals_page() {
		ImGui::Checkbox("enable visuals", &settings::visuals);

		ImGui::Checkbox("box", &settings::box);
		ImGui::ColorPicker("box color", &settings::box_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("health bar", &settings::health_bar);

		ImGui::Checkbox("skeleton", &settings::skeleton);
		ImGui::ColorPicker("skeleton color", &settings::skeleton_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("snap lines", &settings::snap_lines);
		ImGui::ColorPicker("snap lines color", &settings::snap_lines_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("direction lines", &settings::direction_line);
		ImGui::ColorPicker("direction lines color", &settings::direction_line_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("health text", &settings::health_text);

		ImGui::Checkbox("class names", &settings::class_name);
		ImGui::ColorPicker("class names color", &settings::class_name_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("teleporter esp", &settings::teleporter_esp);
		ImGui::ColorPicker("teleporter color", &settings::teleporter_esp_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("turret esp", &settings::turret_esp);
		ImGui::ColorPicker("turret color", &settings::turret_esp_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("dispenser esp", &settings::dispenser_esp);
		ImGui::ColorPicker("dispenser color", &settings::dispenser_esp_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("health pack esp", &settings::health_pack_esp);
		ImGui::ColorPicker("health pack color", &settings::health_pack_esp_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("ammo pack esp", &settings::ammo_box_esp);
		ImGui::ColorPicker("ammo pack color", &settings::ammo_box_esp_color, ImGuiColorEditFlags_NoInputs);

		ImGui::Checkbox("chams", &settings::chams);
	}
	
	void misc_page() {
		ImGui::Checkbox("enable misc", &settings::misc);
		ImGui::Checkbox("bunny hop", &settings::bunny_hop);
		ImGui::Checkbox("auto backstab", &settings::auto_backstab);
	}	
	
	void others_page() {

	}
	
	void players_page() {

	}	
	
	void settings_page() {

	}

}
#pragma once
#include "i_entity.hpp"
#include "..\..\utils\netvars\netvars.hpp"
#include "..\..\utils\helpers.hpp"
#include "..\..\utils\math\vector.hpp"
#include "..\..\utils\utils.hpp"
#include "..\..\utils\memory\memory.hpp"
#include "..\structs\structs.hpp"
#include "..\..\utils\math\math.hpp"
#include "..\..\interfaces\interfaces.hpp"

class c_base_combat_weapon;

model_t* c_base_entity::get_model() {
	PVOID renderable = (PVOID)(this + 0x4);
	typedef model_t* (__thiscall* fn)(void*);
	return utils::get_vfunc<fn>(renderable, 9)(renderable);
}

const char* c_base_entity::get_model_name() {
	return interfaces::model_info->get_model_name(get_model());
}

bool c_base_entity::get_life_state() {
	static int m_lifeState = g_netvar->get_offset("DT_BasePlayer", "m_lifeState");
	return get_value<bool>(m_lifeState);
}

bool c_base_entity::is_alive() {
	return (this->get_life_state() == life_states::ALIVE);
}

bool c_base_entity::is_player() {
	return (get_client_class()->class_id == class_ids::CTFPlayer);
}

int c_base_entity::get_health() {
	static int m_iHealth = g_netvar->get_offset("DT_BasePlayer", "m_iHealth");
	return get_value<int>(m_iHealth);
}

int c_base_entity::get_team_num() {
	static int m_iTeamNum = g_netvar->get_offset("DT_BaseEntity", "m_iTeamNum");
	return get_value<int>(m_iTeamNum);
}

int c_base_entity::get_fov() {
	static int m_iFOV = g_netvar->get_offset("DT_BasePlayer", "m_iFOV");
	auto fov = get_value<int>(m_iFOV);

	if (!fov) {
		static int m_IDefualtFov = g_netvar->get_offset("DT_BasePlayer", "m_iDefaultFOV");
		return get_value<int>(m_IDefualtFov);
	}
	return fov;
}

vector c_base_entity::get_origin() {
	static int m_vecOrigin = g_netvar->get_offset("DT_BaseEntity", "m_vecOrigin");
	return get_value<vector>(m_vecOrigin);
}

vector c_base_entity::get_abs_origin() {
	typedef vector& (__thiscall* fn)(void*);
	return utils::get_vfunc<fn>(this, 9)(this);
}

vector c_base_entity::get_eye_position() {
	static int eye_position = g_netvar->get_offset("DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
	return get_value<vector>(eye_position) + this->get_abs_origin();
}

int c_base_entity::get_class_name() {
	static int m_PlayerClass = g_netvar->get_offset("DT_TFPlayer", "m_PlayerClass", "m_iClass");
	return get_value<int>(m_PlayerClass);
}

int c_base_entity::get_condition() {
	static int m_nPlayerCond = g_netvar->get_offset("DT_TFPlayer", "m_Shared", "m_nPlayerCond");
	return get_value<int>(m_nPlayerCond);
}

int c_base_entity::get_flags() {
	static int m_fFlags = g_netvar->get_offset("DT_BasePlayer", "m_fFlags");
	return get_value<int>(m_fFlags);
}

bool c_base_entity::is_dormant() {
	void* networkable = (void*)(this + 0x8);
	typedef bool(__thiscall* fn)(void*);
	return utils::get_vfunc< fn >(networkable, 8)(networkable);
}

bool c_base_entity::is_taunting() {
	return (this->get_condition() & conditions::TAUNTING);
}

bool c_base_entity::is_ducking() {
	return (this->get_flags() & entity_flags::DUCKING);
}

bool c_base_entity::is_ubered() {
	return (this->get_condition() & conditions::UBERCHARGED);
}

bool c_base_entity::is_bonked() {
	return (this->get_condition() & conditions::BONKED);
}

bool c_base_entity::is_cloaked() {
	return (this->get_condition() & conditions::CLOAKED);
}

bool c_base_entity::is_health_pack() {
	if (get_client_class()->class_id == class_ids::CBaseAnimating) {
		auto hash = hash_string(interfaces::model_info->get_model_name(get_model()));
		return is_health_hash(hash);
	}
	return false;
}

bool c_base_entity::is_ammo_pack() {
	if (get_client_class()->class_id == class_ids::CBaseAnimating) {
		auto hash = hash_string(interfaces::model_info->get_model_name(get_model()));
		return is_ammo_hash(hash);
	}
	return false;
}

client_class* c_base_entity::get_client_class() {
	void* pNetworkable = (void*)(this + 0x8);
	typedef client_class* (__thiscall* fn)(void*);
	return utils::get_vfunc <fn>(pNetworkable, 2)(pNetworkable);
}

bool c_base_entity::is_visible(c_base_entity* local_player, int hitbox) {
	trace_t Trace;
	Ray_t Ray;			 // the future of variable naming
	c_trace_filter Filter;

	Filter.pSkip = local_player;

	auto eye = local_player->get_eye_position();
	auto hit_box = this->get_hit_box_pos(hitbox);
	Ray.Init(eye, hit_box);

	interfaces::trace->trace_ray(Ray, MASK_SOLID, &Filter, &Trace);

	return (Trace.m_pEnt == this);
}

int c_base_entity::get_hitbox_set() {
	static int hitbox = g_netvar->get_offset("DT_BaseAnimating", "m_nHitboxSet");
	return get_value<int>(hitbox);
}

bool c_base_entity::setup_bones(matrix3x4* bone_to_world_out, int max_bones, int bone_mask, float current_time) {
	PVOID renderable = (void*)(this + 0x4);
	typedef bool(__thiscall* fn)(void*, matrix3x4*, int, int, float);
	return utils::get_vfunc <fn>(renderable, 16)(renderable, bone_to_world_out, max_bones, bone_mask, current_time);
}

vector c_base_entity::get_hit_box_pos(int hitbox) {
	model_t* model = get_model();
	if (!model)
		return {};

	studiohdr_t* hdr = (studiohdr_t*)interfaces::model_info->get_studio_model(model);
	if (!hdr)
		return {};

	matrix3x4 BoneMatrix[128];
	if (!setup_bones(BoneMatrix, 128, 0x100, interfaces::globals->curtime))
		return {};

	mstudiohitboxset_t* set = hdr->pHitboxSet(get_hitbox_set());
	if (!set)
		return {};

	mstudiobbox_t* box = set->hitbox(hitbox);
	if (!box)
		return {};

	vector pos = (box->bbmin + box->bbmax) * 0.5f;
	vector out;

	math::vector_transform(pos, BoneMatrix[box->bone], out);

	return out;
}

vector c_base_entity::get_shoot_pos() {
	static auto fn = reinterpret_cast<float* (__thiscall*)(PVOID, vector*)>(memory::find_pattern("client.dll", "55 8B EC 56 8B 75 08 57 8B F9 56 8B 07 FF 90"));
	vector out;
	fn(this, &out);
	return out;
}

matrix3x4& c_base_entity::get_rgfl_coordinate_frame() {
	PVOID renderable = (PVOID)(this + 0x4);
	typedef matrix3x4& (__thiscall* fn)(PVOID);
	return utils::get_vfunc<fn>(renderable, 34)(renderable);
}

vector c_base_entity::get_collideable_mins() {
	static int hitbox = g_netvar->get_offset("DT_BaseEntity", "m_Collision", "m_vecMins");
	return get_value<vector>(hitbox);
}

vector c_base_entity::get_collideable_max() {
	static int hitbox = g_netvar->get_offset("DT_BaseEntity", "m_Collision", "m_vecMaxs");
	return get_value<vector>(hitbox);
}

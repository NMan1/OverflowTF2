#pragma once
#include "..\..\utils\math\vector.hpp"

class c_base_combat_weapon;
class client_class;
struct model_t;
typedef float matrix3x4[3][4];

class c_base_entity
{
private:
	template<class T>
	T get_value(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
public:
	model_t* get_model();

	bool get_life_state();

	bool is_alive();

	int get_health();

	int get_team_num();

	vector get_origin();

	vector get_abs_origin();

	vector get_eye_position();

	int get_class_name();

	int get_condition();

	int get_flags();

	bool is_dormant();

	bool is_taunting();

	bool is_ducking();

	bool is_ubered();

	bool is_bonked();

	bool is_cloaked();

	client_class* get_client_class();

	bool is_visible(c_base_entity* local_player, int hitbox);

	int get_hitbox_set();

	bool setup_bones(matrix3x4* bone_to_world_out, int max_bones, int bone_mask, float current_time);

	vector get_hit_box_pos(int hitbox);

	vector get_shoot_pos();
};


class c_base_combat_weapon : public c_base_entity
{
private:

public:

};

struct spatialization_info_t;
class i_client_entity
{
public:
	// Delete yourself.
	virtual void			release(void) = 0;

	// Network origin + angles
	virtual const vector& get_abs_origin(void) const = 0;
	virtual const QAngle& get_abs_angles(void) const = 0;

	virtual unsigned long* get_mouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			get_sound_spatialization(spatialization_info_t& info) = 0;
};

class i_client_networkable;
class i_client_unknown;
class c_base_handle;
class i_client_entityList
{
public:
	virtual i_client_networkable*	get_client_networkable(int entnum) = 0;
	virtual i_client_networkable*	get_client_networkable_from_handle(c_base_handle hEnt) = 0;
	virtual i_client_unknown*		get_client_unknown_from_handle(c_base_handle hEnt) = 0;
	virtual c_base_entity*			get_client_entity(int entnum) = 0;
	virtual i_client_entity*		get_client_entity_from_handle(c_base_handle hEnt) = 0;
	virtual int						number_of_entities(bool bIncludeNonNetworkable) = 0;
	virtual int						get_highest_entity_index(void) = 0;
	virtual void					set_max_entities(int maxents) = 0;
	virtual int						get_max_entitys() = 0;
};
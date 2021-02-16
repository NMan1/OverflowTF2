#pragma once

class c_base_combat_weapon;
class client_class;
class vector;
struct model_t;
typedef float matrix3x4[3][4];

class c_base_entity
{
private:
	template<class t>
	t get_value(const int offset);
public:
	model_t* get_model();

    int get_owner();

	const char* get_model_name();

	bool get_life_state();

	bool is_alive();

	bool is_player();

	int get_health();

	int get_max_health();

	int get_team_num();

    bool is_in_valid_team();

	int get_fov();

	vector get_origin();

	vector get_abs_origin();

	vector get_eye_position();

    vector get_view_angles();

	int get_class_name();

	int get_condition();

	int get_flags();

    bool can_backstab();

	bool is_dormant();

	bool is_taunting();

	bool is_ducking();

	bool is_ubered();

	bool is_scoped();

	bool is_bonked();

	bool is_cloaked();

    bool is_health_pack();

    bool is_ammo_pack();

	client_class* get_client_class();

	bool is_visible(c_base_entity* local_player, int hitbox);

	int get_hitbox_set();

	bool setup_bones(matrix3x4* bone_to_world_out, int max_bones, int bone_mask, float current_time);

    vector get_bone_pos(int bone);

	vector get_hitbox_pos(int hitbox);

	vector get_shoot_pos();

	matrix3x4& get_rgfl_coordinate_frame();

	vector get_collideable_mins();

	vector get_collideable_max();

	c_base_combat_weapon* get_active_weapon();

    bool& glow_enabled();

	void update_glow_effect();

	void destroy_glow_effect();

    int get_entity_index();

};

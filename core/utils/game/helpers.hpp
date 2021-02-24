#pragma once

class color;
class c_base_entity;

const char* get_class_name_string(int class_id);

color get_team_color(c_base_entity* entity);

int hash_string(const char* szOrg);

bool is_health_hash(int nHash);

bool is_ammo_hash(int nHash);

// credits to project_ic for the values
bool get_projectile_info(c_base_entity* local_player, float& speed, float& gravity);
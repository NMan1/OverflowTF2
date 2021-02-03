#pragma once

class i_client_networkable;
class i_client_unknown;
class c_base_handle;
class c_base_entity;
class vector;

struct spatialization_info_t;
class i_client_entity
{
public:
	// Delete yourself.
	virtual void			release(void) = 0;

	// Network origin + angles
	virtual const vector& get_abs_origin(void) const = 0;
	virtual const vector& get_abs_angles(void) const = 0;

	virtual unsigned long* get_mouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			get_sound_spatialization(spatialization_info_t& info) = 0;
};

class i_client_entity_list
{
public:
	virtual i_client_networkable* get_client_networkable(int entnum) = 0;
	virtual i_client_networkable* get_client_networkable_from_handle(c_base_handle hEnt) = 0;
	virtual i_client_unknown* get_client_unknown_from_handle(c_base_handle hEnt) = 0;
	virtual c_base_entity* get_client_entity(int entnum) = 0;
	virtual i_client_entity* get_client_entity_from_handle(c_base_handle hEnt) = 0;
	virtual int						number_of_entities(bool bIncludeNonNetworkable) = 0;
	virtual int						get_highest_entity_index(void) = 0;
	virtual void					set_max_entities(int maxents) = 0;
	virtual int						get_max_entitys() = 0;
};
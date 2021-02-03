#pragma once

class c_base_entity;
class vector;
class c_move_data;

class c_game_movement
{
public:
	virtual			~c_game_movement(void) {}

	// Process the current movement command
	virtual void	process_movement(c_base_entity* pPlayer, c_move_data* pMove) = 0;
	virtual void	start_track_prediction_errors(c_base_entity* pPlayer) = 0;
	virtual void	finish_track_prediction_errors(c_base_entity* pPlayer) = 0;
	virtual void	diff_print(char const* fmt, ...) = 0;

	// Allows other parts of the engine to find out the normal and ducked player bbox sizes
	virtual vector get_player_mins(bool ducked) const = 0;
	virtual vector get_player_maxs(bool ducked) const = 0;
	virtual vector get_player_view_offset(bool ducked) const = 0;
};


#ifndef TOWER_STRUCT_H
#define TOWER_STRUCT_H

struct tower_struct
{
	size_t tower_number = 0, max_calls_number = 0, curr_calls_number = 0;
	vector<size_t> neighboring_towers_list = {};

	string tower_stats = "";
};

#endif // !TOWER_STRUCT_H
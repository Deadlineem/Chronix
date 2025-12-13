#pragma once
#include "core/scr_globals.hpp"

namespace big::outfit
{
	struct outfit_t
	{
		int id;
		std::string label;
		int drawable_id     = 0;
		int drawable_id_max = 0;
		int texture_id      = 0;
		int texture_id_max  = 0;
	};

	struct components_t
	{
		std::vector<outfit_t> items = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_MASKS"_T.data()},
		    {2, "OUTFIT_HAIR"_T.data()},
		    {3, "OUTFIT_HANDS"_T.data()},
		    {4, "OUTFIT_PANTS"_T.data()},
		    {5, "OUTFIT_BACK"_T.data()},
		    {6, "OUTFIT_FEET"_T.data()},
		    {7, "OUTFIT_SCARF"_T.data()},
		    {8, "OUTFIT_ACCS"_T.data()},
		    {9, "OUTFIT_VEST"_T.data()},
		    {10, "OUTFIT_DECL"_T.data()},
		    {11, "OUTFIT_SHIRT"_T.data()}};
	};

	struct props_t
	{
		std::vector<outfit_t> items = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_GLASSES"_T.data()},
		    {2, "OUTFIT_EARS"_T.data()},
		    {6, "OUTFIT_WATCH"_T.data()},
		    {7, "OUTFIT_WRIST"_T.data()}};
	};

	inline void check_bounds_drawable(outfit_t* item, const int lower)
	{
		if (item->drawable_id > item->drawable_id_max)
		{
			item->drawable_id = item->drawable_id_max;
		}
		if (item->drawable_id < lower)
		{
			item->drawable_id = lower;
		}
	}

	inline void check_bounds_texture(outfit_t* item, const int lower)
	{
		if (item->texture_id > item->texture_id_max)
		{
			item->texture_id = item->texture_id_max;
		}
		if (item->texture_id < lower)
		{
			item->texture_id = lower;
		}
	}

	// usually each update increases 1//
	inline char* get_slot_name_address(int slot)
	{
		return scr_globals::stats.at(0, 5574).at(681).at(2466).at(slot, 8).as<char*>();
	}

	inline int* get_component_drawable_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5574).at(681).at(1342).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_component_texture_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5574).at(681).at(1616).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_prop_drawable_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5574).at(681).at(1890).at(slot, 10).at(id, 1).as<int*>();
	}

	inline int* get_prop_texture_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5574).at(681).at(2101).at(slot, 10).at(id, 1).as<int*>();
	}
}
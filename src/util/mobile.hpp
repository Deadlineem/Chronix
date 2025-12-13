#pragma once
#include "core/enums.hpp"
#include "core/scr_globals.hpp"
#include "globals.hpp"
#include "gta_util.hpp"
#include "misc.hpp"
#include "natives.hpp"
#include "notify.hpp"
#include "script.hpp"
#include "script_local.hpp"
#include "vehicle.hpp"

namespace big::mobile
{
	namespace util
	{
		int get_current_personal_vehicle(); // forward declare
		inline void despawn_current_personal_vehicle()
		{
			misc::clear_bits(scr_globals::vehicle_global.at(get_current_personal_vehicle(), 143).at(104).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE);
		}

		inline int get_current_personal_vehicle()
		{
			return *scr_globals::stats.at(0, 5571).at(681).at(2).as<int*>();
		}
	}

	namespace merry_weather
	{
		inline void request_ammo_drop()
		{
			*scr_globals::freemode_global.at(538).as<int*>() = 1; // REGEX: if \(Global_.*?.f_.*?\)\n.*?\{\n.*?if \(!NETWORK::NETWORK_IS_SCRIPT_ACTIVE\("AM_AMMO_DROP", PLAYER::PLAYER_ID\(\), true, 0\)\)
		}

		inline void request_boat_pickup()
		{
			*scr_globals::freemode_global.at(539).as<int*>() = 1; // REGEX: if \(!NETWORK::NETWORK_IS_SCRIPT_ACTIVE\("AM_BOAT_TAXI", PLAYER::PLAYER_ID\(\), true, 0\)\)\n.*?\{\n.*?if \(Global_.*?.f_.*? == 1\)
		}

		inline void request_helicopter_pickup()
		{
			*scr_globals::freemode_global.at(540).as<int*>() = 1; // REGEX: if \(Global_.*?.f_.*? == true\)\n.*?\{\n.*?if \(!NETWORK::NETWORK_IS_SCRIPT_ACTIVE\("AM_HELI_TAXI", -1, true, 0\)\)
		}

		inline void request_backup_helicopter()
		{
			*scr_globals::freemode_global.at(3578).as<int*>() = 1; // REGEX: if \(SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH\(joaat\("am_backup_heli"\)\) <= 0\)\n.*?\{\n.*?Global_.*?.f_.*? = 0;
		}

		inline void request_airstrike()
		{
			*scr_globals::freemode_global.at(3579).as<int*>() = 1; //REGEX: if \(SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH\(joaat\("am_airstrike"\)\) <= 0\)\n.*?\{\n.*?Global_.*?.f_.*? = 0;
		}
	}

	namespace mors_mutual
	{
		inline bool fix_index(int veh_idx, bool spawn_veh = false)
		{
			bool can_be_fixed = misc::has_bits_set(scr_globals::vehicle_global.at(veh_idx, 143).at(104).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::HAS_INSURANCE);

			if (can_be_fixed)
			{
				misc::clear_bits(scr_globals::vehicle_global.at(veh_idx, 143).at(104).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::IMPOUNDED | eVehicleFlags::UNK2);

				if (spawn_veh)
				{
					misc::set_bits(scr_globals::vehicle_global.at(veh_idx, 143).at(104).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::SPAWN_AT_MORS_MUTUAL);
				}
			}
			return can_be_fixed;
		}

		inline int fix_all()
		{
			int fixed_count = 0;

			const int arr_size = *scr_globals::vehicle_global.as<int*>();
			for (int i = 0; i < arr_size; i++)
			{
				if (fix_index(i, true))
				{
					fixed_count++;
				}
			}

			return fixed_count;
		}
	}

	namespace ceo_abilities
	{
		inline void request_bullshark_testosterone()
		{
			*scr_globals::freemode_global.at(546).as<int*>() = 1; // REGEX: if \(Global_.*?.f_.*?\)\n.*?\{\n.*?if \(!NETWORK::NETWORK_IS_SCRIPT_ACTIVE\("AM_BRU_BOX", PLAYER::PLAYER_ID\(\), true, 0\)\)
		}

		inline void request_ballistic_armor() //i think this is a ceo ability atleast?
		{
			*scr_globals::freemode_global.at(548).as<int*>() = 1; // REGEX: if \(Global_.*?.f_.*?\)\n.*?\{\n.*?if \(!NETWORK::NETWORK_IS_SCRIPT_ACTIVE\("AM_AMMO_DROP", PLAYER::PLAYER_ID\(\), true, 0\)\)
		}
	}

	namespace services
	{
		inline void request_avenger()
		{
			*scr_globals::freemode_global.at(585).as<int*>() = 1; // Look for if (IS_BIT_SET(Global_.*?.f_.*?, 1)) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle2, false))
		}

		inline void request_kosatka()
		{
			*scr_globals::freemode_global.at(613).as<int*>() = 1; // Look for if (Global_.*?.f_.*?) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle6, false))
		}

		inline void request_mobile_operations_center()
		{
			*scr_globals::freemode_global.at(577).as<int*>() = 1; // Look for if (Global_.*?.f_.*?) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle2, false))
		}

		inline void request_terrorbyte()
		{
			*scr_globals::freemode_global.at(591).as<int*>() = 1; // Look for if (Global_.*?.f_.*?) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle4, false))
		}

		inline void request_acidlab()
		{
			*scr_globals::freemode_global.at(592).as<int*>() = 1; // Look for if (Global_.*?.f_.*?) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle5, false))
		}

		inline void request_acidlab_bike()
		{
			*scr_globals::freemode_global.at(647).as<int*>() = 1; // Look for if (Global_.*?.f_.*?) { BUNCH OF CODE BETWEEN if (!ENTITY::IS_ENTITY_DEAD(vehicle8, false))
		}
	}

	namespace mechanic
	{
		inline Vehicle get_personal_vehicle()
		{
			return *scr_globals::freemode_global.at(301).as<Vehicle*>();
		}

		inline CVehicle* get_personal_cvehicle()
		{
			Vehicle personal_vehicle = get_personal_vehicle();
			if (personal_vehicle != -1 && ENTITY::DOES_ENTITY_EXIST(personal_vehicle))
			{
				return reinterpret_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(personal_vehicle));
			}

			return nullptr;
		}

		inline void summon_vehicle_by_index(int veh_idx)
		{
			if (*scr_globals::freemode_global.at(638).as<int*>() != -1) // REGEX: NETWORK::NET_TO_VEH\(.*?\), Global_.*?.f_.*?, false, false, true, false, false, false, false, -1, 0, false\);
			{
				return g_notification_service.push_warning("VEHICLE"_T.data(), "VEHICLE_MECHANIC_BUSY"_T.data());
			}

			if (g.clone_pv.spawn_inside && self::veh)
			{
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			}

			// despawn current veh
			util::despawn_current_personal_vehicle();
			mors_mutual::fix_index(veh_idx);

			script::get_current()->yield(100ms);

			// only do this when spawn inside is enabled otherwise the vehicle will spawn relatively far away from players
			if (g.clone_pv.spawn_inside)
			{
				*scr_globals::freemode_global.at(590).as<int*>() = 1; // disable vehicle node distance check
			}
			*scr_globals::freemode_global.at(575).as<int*>() = 1; // tell freemode to spawn our vehicle | HOW TO FIND: https://imgur.com/8q2P1wB
			*scr_globals::freemode_global.at(641).as<int*>() = 0; // required | REGEX: if \(BUILTIN::VDIST2\(.*?\) > 50f \* 50f && !Global_.*?.f_.*?\)
			*scr_globals::freemode_global.at(638).as<int*>() = veh_idx; // REGEX: REGEX: NETWORK::NET_TO_VEH\(.*?\), Global_.*?.f_.*?, false, false, true, false, false, false, false, -1, 0, false\);

			script::get_current()->yield(100ms);

			GtaThread* freemode_thread = gta_util::find_script_thread("freemode"_J);
			if (freemode_thread)
			{
				// regex to find this shit easily
				// \(func_\d{3}\(&\(uParam0->f_\d{3}\), \d+000, 0\) \|\| func
				// or if you prefer a string "VD_FAIL4"
				// or if you really prefer an image https://i.imgur.com/K8vMILe.png
				*scr_locals::freemode::mobile.set(freemode_thread).at(176).as<int*>() = 0; // spawn vehicle instantly
			}

			// blocking call till vehicle is delivered
			notify::busy_spinner("Delivering vehicle...", scr_globals::freemode_global.at(638).as<int*>(), -1); // REGEX: REGEX: NETWORK::NET_TO_VEH\(.*?\), Global_.*?.f_.*?, false, false, true, false, false, false, false, -1, 0, false\);

			if (g.clone_pv.spawn_inside)
			{
				vehicle::bring(get_personal_vehicle(), self::pos, true);
			}
		}
	}

	namespace mobile_misc
	{
		inline void request_taxi()
		{
			*scr_globals::freemode_global.at(509).as<int*>() = 1;
		}

		inline void request_gun_van()
		{
			auto local_pos      = self::pos;
			auto forward_vector = ENTITY::GET_ENTITY_FORWARD_VECTOR(self::ped);
			Vector3 spawn_point;

			if (MISC::FIND_SPAWN_POINT_IN_DIRECTION(local_pos.x,
			        local_pos.y,
			        local_pos.z,
			        forward_vector.x,
			        forward_vector.y,
			        forward_vector.z,
			        25.f,
			        &spawn_point))
			{
				*scr_globals::gun_van.as<Vector3*>() = spawn_point;

				return g_notification_service.push_success("GUI_TAB_MOBILE"_T.data(), "REQUEST_GUN_VAN_NOTIFY_SUCCESS"_T.data());
			}

			g_notification_service.push_warning("GUI_TAB_MOBILE"_T.data(), "REQUEST_GUN_VAN_NOTIFY_FAILED"_T.data());
		}
	}
}
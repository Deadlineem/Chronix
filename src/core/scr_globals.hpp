#pragma once
#include "script_global.hpp"
#include "script_local.hpp"

namespace big::scr_globals
{
	static inline const script_global gsbd(2648929);
	static inline const script_global gsbd_kicking(1876908);
	static inline const script_global gsbd_fm_events(1918241);

	static inline const script_global globalplayer_bd(2658016);
	static inline const script_global gpbd_fm_3(1888737);
	static inline const script_global gpbd_fm_1(1845225);
	static inline const script_global interiors(1945923);

	static inline const script_global launcher_global(2699544);

	// creator globals usually remain the same after updates
	static inline const script_global terminate_creator(1574607); // NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline const script_global switch_struct(1574634);
	static inline const script_global mission_creator_radar_follows_camera(2621443);
	static inline const script_global mission_creator_exited(1574530);

	static inline const script_global transition_state(1575014);
	static inline const script_global sctv_spectator(2698102); // pausemenu_multiplayer function 0xE49C42EC

	static inline const script_global vehicle_global(1586540);

	static inline const script_global freemode_properties(2672964);
	static inline const script_global freemode_global(2740054);

	static inline const script_global spawn_global(2696579);

	static inline const script_global transaction_overlimit(4538671);

	static inline const script_global stats(2359296);

	static inline const script_global session(1574589);
	static inline const script_global session2(1575038);
	static inline const script_global session3(33282);
	static inline const script_global session4(1574943);
	static inline const script_global session5(1575013);
	static inline const script_global session6(2696496); // freemode -> if (NETWORK::NETWORK_IS_GAME_IN_PROGRESS() && !NETWORK::NETWORK_IS_ACTIVITY_SESSION())

	static inline const script_global interaction_menu_access(2711261); // am_pi_menu -> if (NETWORK::NETWORK_IS_SIGNED_ONLINE()) first global after that

	static inline const script_global disable_wasted_sound(2708261); // freemode -> AUDIO::PLAY_SOUND_FRONTEND(-1, "Wasted", "POWER_PLAY_General_Soundset", true);

	static inline const script_global passive(1574582); // if (((!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(bVar1), false) || Global_

	static inline const script_global property_garage(1940049);
	static inline const script_global property_names(1312335);

	static inline const script_global reset_clothing(104448); // freemode 75, &iLocal_.*, 2\);

	static inline const script_global gun_van(1952452); // return -29.532f, 6435.136f, 31.162f;

	static inline const script_global disable_phone(21205);

	static inline const script_global should_reset_fm_weapons(1578044);
}

namespace big::scr_locals
{
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx        = 624;  // (bParam0) != 0;
		constexpr static auto player_broadcast_idx = 2608; // if (NETWORK::PARTICIPANT_ID_TO_INT() != -1)
	}

	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 119; // /* Tunable: CRIMINAL_DAMAGE_DISABLE_SHARE_CASH */)
		constexpr static auto score_idx = 114; // AUDIO::PLAY_SOUND_FRONTEND(-1, "Criminal_Damage_High_Value", "GTAO_FM_Events_Soundset", false);
	}

	namespace am_cp_collection
	{
		constexpr static auto broadcast_idx = 824; // bVar1 = NETWORK::NETWORK_GET_PLAYER_INDEX(PLAYER::INT_TO_PARTICIPANTINDEX(iVar0));
		constexpr static auto player_broadcast_idx = 3465; // bVar1 = NETWORK::NETWORK_GET_PLAYER_INDEX(PLAYER::INT_TO_PARTICIPANTINDEX(iVar0));
	}

	namespace am_king_of_the_castle
	{
		constexpr static auto broadcast_idx = 102; // KING_OF_THE_CASTLE_EVENT_TIME_LIMIT
	}

	namespace fmmc_launcher
	{
		constexpr static auto broadcast_idx = 12827; // if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(PLAYER::INT_TO_PLAYERINDEX(Global_
	}

	namespace fm_mission_controller
	{
		constexpr static auto mission_controller_wanted_state_flags = 60892; // if (PLAYER::GET_PLAYER_WANTED_LEVEL(bLocal_
	}

	namespace freemode
	{
		// first uLocal_ in this function call
		// func_\d+\((&.Local_\d+(, )?){9}\);
		inline static script_local mobile(19361);
	}
}
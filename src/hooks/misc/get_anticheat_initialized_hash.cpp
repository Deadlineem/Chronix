#include "hooking/hooking.hpp"
#include "pointers.hpp"

struct CAnticheatContext
{
	rage::Obf32 m_LastScanTime;
	rage::Obf32 m_ScanInterval;
	void* m_ScanData;
	rage::Obf32 m_ScanDataSize;
	rage::Obf32 m_ScanDataSize2;
	rage::Obf32 m_GameBuild;
	std::uint64_t qword58;
	std::uint32_t dword60;
	char gap64[2572];
	std::uint32_t dwordA70;
	std::uint64_t qwordA78;
	std::uint32_t dwordA80;
	char gapA84[3];
	char byteA87[9];
	bool m_DebugBattlEyeEnabled;
	bool m_BattlEyeEnabled; // 0xA91
	bool m_IsDebugMode;
	volatile __int32 m_CurrentScanIndex;
	std::uint64_t qwordA98;
};
static_assert(sizeof(CAnticheatContext) == 0xAA0);

namespace big
{
	std::uint32_t hooks::get_anticheat_initialized_hash()
	{
		return 0x124EA49D;
	}

	std::uint32_t hooks::get_anticheat_initialized_hash_2(void* ac_var, std::uint32_t seed)
	{
		auto orig = (*g_pointers->m_gta.m_anticheat_context) ? (*g_pointers->m_gta.m_anticheat_context)->m_BattlEyeEnabled : false;

		if (*g_pointers->m_gta.m_anticheat_context)
		{
			(*g_pointers->m_gta.m_anticheat_context)->m_BattlEyeEnabled = true; // integ checks will boot us out if we set this outside this function
		}

		auto ret = g_hooking->get_original<get_anticheat_initialized_hash_2>()(ac_var, seed);

		if (*g_pointers->m_gta.m_anticheat_context)
		{
			(*g_pointers->m_gta.m_anticheat_context)->m_BattlEyeEnabled = orig;
		}

		return ret;
	}
}
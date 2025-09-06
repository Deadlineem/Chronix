#include "hooking/hooking.hpp"
#include "script_mgr.hpp"

#include <curl/curl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace big
{
	bool hooks::run_script_threads(uint32_t ops_to_execute)
	{
		if (g_running) [[likely]]
		{
			g_script_mgr.tick();
			download_lua_script_bundle();
		}
			 
		return g_hooking->get_original<run_script_threads>()(ops_to_execute);
	}

	size_t WriteToFile(void* ptr, size_t size, size_t nmemb, std::ofstream& outFile)
	{
		outFile.write(static_cast<char*>(ptr), size * nmemb);
		return size * nmemb;
	}

	std::string get_appdata_directory()
	{
		char* appdata = nullptr;
		size_t len    = 0;

		// Get the environment variable for APPDATA
		_dupenv_s(&appdata, &len, "APPDATA");
		std::string appdataPath(appdata);
		free(appdata);

		return appdataPath;
	}

	void hooks::download_lua_script_bundle()
	{
		const std::vector<std::string> urls = {
		    "https://raw.githubusercontent.com/Deadlineem/VehicleReward/refs/heads/main/vehicle_reward.lua" // Claim Vehicle as Personal ShinyWasabi
		};

		std::string appDataPath = get_appdata_directory();
		std::string targetDir   = appDataPath + "\\Chronix\\scripts";
		std::filesystem::create_directories(targetDir);

		CURL* curl;
		CURLcode res;

		for (const auto& url : urls)
		{
			std::string fileName = std::filesystem::path(url).filename().string();
			std::string filePath = targetDir + "\\" + fileName;

			if (std::filesystem::exists(filePath))
			{
				// DEBUG ONLY -- LOG(WARNING) << "File already exists, skipping download: " << filePath << std::endl;
				continue;
			}

			std::ofstream outFile(filePath, std::ios::binary);
			if (!outFile.is_open())
			{
				LOG(FATAL) << "Failed to open file: " << filePath << std::endl;
				continue;
			}

			curl_global_init(CURL_GLOBAL_DEFAULT);
			curl = curl_easy_init();

			if (curl)
			{
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToFile);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, std::ref(outFile));
				curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

				res = curl_easy_perform(curl);

				if (res != CURLE_OK)
				{
					LOG(FATAL) << "Failed to download: " << url << " - " << curl_easy_strerror(res) << std::endl;
				}
				else
				{
					LOG(INFO) << "Successfully downloaded: " << fileName << std::endl;
				}

				curl_easy_cleanup(curl);
			}
			else
			{
				LOG(FATAL) << "Failed to initialize CURL." << std::endl;
			}

			curl_global_cleanup();
		}
	}
}

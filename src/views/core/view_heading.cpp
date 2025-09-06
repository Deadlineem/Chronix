#include "lua/lua_manager.hpp"
#include "views/view.hpp"
#include "renderer/renderer.hpp"
#include <comdef.h>
#include <d3d11.h>
#include <filesystem>
#include <imgui.h>
#include <iostream>
#include <string>
#include <curl/curl.h>  // Make sure you have libcurl installed for URL loading

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <random>

namespace big
{
	ID3D11Device* g_device = nullptr;

	size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::vector<unsigned char>*)userp)->insert(((std::vector<unsigned char>*)userp)->end(), (unsigned char*)contents, (unsigned char*)contents + size * nmemb);
		return size * nmemb;
	}

	ID3D11ShaderResourceView* LoadTextureFromURL(const std::string& imageUrl, ID3D11Device* device)
	{
		std::vector<unsigned char> buffer;
		CURL* curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, imageUrl.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				//LOG(FATAL) << "Failed to download image: " << curl_easy_strerror(res);
				curl_easy_cleanup(curl);
				return nullptr;
			}
			curl_easy_cleanup(curl);
		}

		int width, height, channels;
		unsigned char* image_data = stbi_load_from_memory(buffer.data(), buffer.size(), &width, &height, &channels, 4);

		if (!image_data)
		{
			//LOG(FATAL) << "Failed to load image from memory.";
			return nullptr;
		}

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width                = width;
		textureDesc.Height               = height;
		textureDesc.MipLevels            = 1;
		textureDesc.ArraySize            = 1;
		textureDesc.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count     = 1;
		textureDesc.Usage                = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags            = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = image_data;
		initData.SysMemPitch            = width * 4;

		ID3D11Texture2D* texture = nullptr;
		HRESULT hr               = device->CreateTexture2D(&textureDesc, &initData, &texture);

		if (FAILED(hr))
		{
			LOG(FATAL) << "Failed to create texture: " << hr << std::endl;
			stbi_image_free(image_data);
			return nullptr;
		}

		ID3D11ShaderResourceView* textureView   = nullptr;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format                          = textureDesc.Format;
		srvDesc.ViewDimension                   = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels             = 1;

		hr = device->CreateShaderResourceView(texture, &srvDesc, &textureView);
		texture->Release();

		stbi_image_free(image_data);

		if (FAILED(hr))
		{
			LOG(FATAL) << "Failed to create shader resource view: " << hr << std::endl;
			return nullptr;
		}

		return textureView;
	}

	void view::heading()
	{
		CURL* curl                                     = curl_easy_init();
		static bool headerTextureLoaded                = false;
		static ID3D11ShaderResourceView* headerTexture = nullptr;
		static int loadAttempts                        = 0; // Track the number of attempts
		const int maxAttempts                          = 3; // Maximum allowed attempts
		static bool errorLogged                        = false;

		std::string headerImageUrl = "https://kaos.fpr.net/images/header/" + g.window.selected_header_image;

		if ((!headerTextureLoaded || g.window.selected_header_image_changed) && loadAttempts < maxAttempts)
		{
			if (headerTexture)
			{
				headerTexture->Release();
				headerTexture = nullptr;
			}

			headerTexture = LoadTextureFromURL(headerImageUrl, g_device);

			if (headerTexture)
			{
				headerTextureLoaded                    = true;
				g.window.selected_header_image_changed = false;
				loadAttempts                           = 0; // Reset attempts on successful load
			}
			else
			{
				++loadAttempts; // Increment attempts on failure
				LOG(WARNING) << "Failed to load header texture. Attempt " << loadAttempts << " of " << maxAttempts << ".\n";
			}
		}

		if (headerTexture)
		{
			ImGui::SetNextWindowSize({315.f * g.window.gui_scale, 120.f * g.window.gui_scale});
			ImGui::SetNextWindowPos({10.f, 10.f});
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
			{
				ImGui::PopStyleVar();

				ImVec2 imgSize = ImGui::GetContentRegionAvail();
				ImGui::GetWindowDrawList()->AddImage((void*)headerTexture,
				    ImGui::GetWindowPos(),
				    ImVec2(ImGui::GetWindowPos().x + imgSize.x, ImGui::GetWindowPos().y + imgSize.y));

				ImGui::BeginGroup();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.259f, 0.910f, 0.173f, 1.f));
				if (g_local_player == nullptr || g_local_player->m_player_info == nullptr)
				{
					if (components::header_button("Welcome!", 112.5f, 2.f, ""))
					{
					}
				}
				else
				{
					std::string playerName     = g_local_player->m_player_info->m_net_player_data.m_name;
					std::string welcomeMessage = "Welcome, " + playerName + "!";
					if (components::header_button(welcomeMessage.c_str(), 50.f, 2.f, ""))
					{
					}
				}
				ImGui::PopStyleColor();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
				if (components::header_button("Unload", 235.f, 85.f, "Unload Chronix from GTA (May cause Instability/Crashing)"))
				{
					g_lua_manager->trigger_event<menu_event::MenuUnloaded>();
					g_running = false;
				}
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::EndGroup();
			}
			ImGui::End();
		}
		else
		{
			// Fallback content if texture loading fails
			if (loadAttempts >= maxAttempts && !errorLogged)
			{
				LOG(FATAL) << "Maximum attempts reached. Header texture could not be loaded.\n";
				errorLogged = true; // Ensure the error is only logged once
			}
			ImGui::SetNextWindowSize({315.f * g.window.gui_scale, 80.f * g.window.gui_scale});
			ImGui::SetNextWindowPos({10.f, 10.f});
			if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
			{
				ImGui::BeginGroup();
				ImGui::Text("~Chronix~");
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.259f, 0.910f, 0.173f, 1.f));
				if (g_local_player == nullptr || g_local_player->m_player_info == nullptr)
				{
					ImGui::Text("Welcome!");
				}
				else
				{
					ImGui::Text("Welcome, %s!", g_local_player->m_player_info->m_net_player_data.m_name);
				}
				ImGui::PopStyleColor();
				ImGui::EndGroup();

				ImGui::SameLine();
				ImGui::SetCursorPos({(307.5f * g.window.gui_scale) - ImGui::CalcTextSize("UNLOAD"_T.data()).x
				        - ImGui::GetStyle().ItemSpacing.x,
				    ImGui::GetStyle().WindowPadding.y / 2 + ImGui::GetStyle().ItemSpacing.y + (ImGui::CalcTextSize("W").y / 2)});
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
				if (components::nav_button("UNLOAD"_T))
				{
					g_lua_manager->trigger_event<menu_event::MenuUnloaded>();
					g_running = false;
				}
				ImGui::PopStyleColor();
			}
			ImGui::End();
		}
	}
}

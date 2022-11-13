#include "pch.h"
#include "DumpPacketsWnd.h"

#include <sniffer/packet/PacketManager.h>

namespace sniffer::gui
{
	DumpPacketsWnd::DumpPacketsWnd()
	{ }

	DumpPacketsWnd& DumpPacketsWnd::instance()
	{
		static DumpPacketsWnd instance;
		return instance;
	}

	void DumpPacketsWnd::Draw()
	{
		if (ImGui::BeginGroupPanel("Settings"))
		{
			ImGui::InputText("Dump path", &m_DumpPath);
		}
		ImGui::EndGroupPanel();

		if (ImGui::Button("Dump"))
		{
			if (sniffer::packet::PacketManager::GetPacketCount())
			{
				nlohmann::json j;
				auto packet_array = nlohmann::json::array();

				for (auto& packet : sniffer::packet::PacketManager::GetPackets())
				{
					nlohmann::json packet_json;
					packet_json["direction"] = config::Enum(packet.direction());
					packet_json["cmd_id"] = packet.mid();
					packet_json["timestamp"] = packet.timestamp();
					packet_json["raw_head"] = util::base64_encode(packet.raw().head.data(), packet.raw().head.size());
					packet_json["raw_content"] = util::base64_encode(packet.raw().content.data(), packet.raw().content.size());
					packet_array.push_back(packet_json);
				}

				j["packets"] = packet_array;

				std::ofstream output_file(m_DumpPath);
				output_file << j.dump(4);
				output_file.close();
			}
		}
	}

	WndInfo& DumpPacketsWnd::GetInfo()
	{
		static WndInfo info = { "Packet Dumper", true };
		return info;
	}
}
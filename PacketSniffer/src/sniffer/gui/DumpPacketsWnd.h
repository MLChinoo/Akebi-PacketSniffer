#include "IWindow.h"
#include "PacketView.h"

namespace sniffer::gui
{
	class DumpPacketsWnd : public IWindow
	{
	public:
		static DumpPacketsWnd& instance();
		void Draw() override;

		WndInfo& GetInfo() override;

	private:
		DumpPacketsWnd();
		std::string m_DumpPath;
	public:
		DumpPacketsWnd(DumpPacketsWnd const&) = delete;
		void operator=(DumpPacketsWnd const&) = delete;
	};
}

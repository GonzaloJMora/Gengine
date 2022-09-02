#include "Types.h"

namespace Graphics {

	class GraphicsManager {

		public:
			void GStartup(int window_width, int window_height, Foo::string window_name, bool window_fullscreen);
			void GShutdown();
	};
}

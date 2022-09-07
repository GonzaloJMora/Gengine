#pragma once
#include "Types.h"
#include <filesystem>

namespace Resource {
	class ResourceManager {
		public:
			Foo::string resolvePath(Foo::string file);
	};
}
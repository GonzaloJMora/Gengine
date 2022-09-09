#pragma once
#include "Types.h"
#include <filesystem>

typedef std::filesystem::path path;

namespace Resource {
	class ResourceManager {
		public:
			Foo::string resolvePath(Foo::string file);
	};
}
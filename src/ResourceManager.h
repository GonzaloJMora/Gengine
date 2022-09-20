#pragma once

#include <filesystem>
#include "Types.h"

typedef std::filesystem::path path;
//make different path resolve functions based on which piece of data you give ie sounds or textures
namespace Resource {
	class ResourceManager {
		public:
			Foo::string resolvePath(Foo::string file);
	};
}
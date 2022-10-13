#pragma once

#include <sol/sol.hpp>
#include "Types.h"
#include <unordered_map>

namespace Script {
	class ScriptManager {
		public:
			std::unordered_map<std::string, sol::load_result> scriptMap;
			sol::state lua;

			void startUp();
			bool loadScript(const Foo::string& name, const Foo::string& path);
			void Update();
			void init();
	};
}
#pragma once
#include "soloud.h"
#include "soloud_wav.h"
#include <unordered_map>
#include <string>

namespace Sound {
	class SoundManager {
		public:
			SoLoud::Soloud s;
			std::unordered_map<std::string, SoLoud::Wav> soundMap;
			
			void loadSound(const std::string& name, const std::string& path);
			void destroySound(const std::string& name);
			void playSound(const std::string& name);
	};
}
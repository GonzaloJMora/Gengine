#include "SoundManager.h"
#include "ResourceManager.h"
#include "spdlog/spdlog.h"

using namespace Sound;
using namespace Resource;

Resource::ResourceManager resource;

void Sound::SoundManager::loadSound(const std::string& name, const std::string& path)
{
	soundMap[name].load(resource.resolvePath(path).c_str());
}

void Sound::SoundManager::destroySound(const std::string& name)
{
	if (soundMap.count(name) != 0) {
		soundMap.erase(name);
	}
	else {
		spdlog::info("name to delete doesn't exist");
	}
}

void Sound::SoundManager::playSound(const std::string& name)
{
	if (soundMap.count(name) != 0) {
		s.play(soundMap[name]);
	}
	else {
		spdlog::info("name to play doesn't exist");
	}
}

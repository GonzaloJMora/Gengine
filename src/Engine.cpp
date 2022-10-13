#include "Engine.h"
#include "spdlog/spdlog.h"
#include <filesystem>

using namespace Gengine;
using namespace Foo;
using namespace Graphics;
using namespace Input;
using namespace Sound;
using namespace Resource;
using namespace Entity;
using namespace Script;

void callback();

void Gengine::Engine::Startup(const UpdateCallback& callback) {
	graphics.GStartup(1280, 960, "Gengine Collision", false);

	script.startUp();

	sound.s.init();

	for (const auto& file : std::filesystem::directory_iterator("./assets/scripts/")) {
		string name = file.path().filename().string();
		name.erase(name.find(".lua"), name.length());
		engine.script.loadScript(name, (path("scripts") / file.path().filename().string()).string());
	}

	script.init();

	RunGameLoop(callback);
}

void Gengine::Engine::Shutdown() {

	for (std::pair<string, SoLoud::Wav> soundPair : sound.soundMap) {
		sound.destroySound(soundPair.first);
	}

	for (std::pair<string, Image> imagePair : graphics.imageMap) {
		graphics.destroyImage(imagePair.first);
	}

	for (int i = 0; i < ecs.ids.size(); i++) {
		ecs.Destroy(ecs.ids[i]);
	}

	sound.s.deinit();
	graphics.GShutdown();

	exit(EXIT_SUCCESS);
}

void Gengine::Engine::RunGameLoop(const UpdateCallback& callback) {

	auto oneFrame = std::chrono::duration<real, std::milli>(1.0/60.0);

	while (true) {
		std::chrono::time_point frameStart = std::chrono::steady_clock::now();

		callback();

		// close button is clicked
		if (glfwWindowShouldClose(graphics.w)) {
			Shutdown();
		}

		std::chrono::time_point currTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = oneFrame - (currTime - frameStart);

		std::this_thread::sleep_for(diff);
	}
}

void callback()
{
	engine.input.Update();
	engine.script.Update();
	engine.graphics.Draw();
}

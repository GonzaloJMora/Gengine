#include "Engine.h"
#include "spdlog/spdlog.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include <thread>
#include <chrono>

using namespace Gengine;
using namespace Foo;
using namespace Graphics;
using namespace Input;
using namespace Sound;

Graphics::GraphicsManager graphics;
Input::InputManager input;
Sound::SoundManager sound;

void Gengine::Engine::Startup() {
	//at some other point i will allow for user input here
	graphics.GStartup(1280, 960, "Gengine Collision", false);
	sound.s.init();
	sound.loadSound("golds", "./assets/golds.wav");
	sound.loadSound("stop", "./assets/stop.wav");
	sound.loadSound("moyai", "./assets/moyai.wav");
	RunGameLoop();
}

void Gengine::Engine::Shutdown() {
	sound.destroySound("golds");
	sound.destroySound("stop");
	sound.destroySound("moyai");
	sound.s.deinit();
	graphics.GShutdown();
}

//FIXME: figure out how to do callback stuff
void Gengine::Engine::RunGameLoop(){//const UpdateCallback& callback) {

	const std::chrono::time_point startTime = std::chrono::steady_clock::now();
	const auto oneFrame = std::chrono::duration<real, std::milli>(1.0/120.0);

	while (true) {
		std::chrono::time_point currTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = currTime - startTime;
		input.Update();

		if (input.isKeyPressed(graphics.w, GLFW_KEY_F) == GLFW_PRESS) {
			sound.playSound("moyai");
			spdlog::info("F go brrrrrr");
		}

		if (input.isKeyPressed(graphics.w, GLFW_KEY_L) == GLFW_PRESS) {
			sound.playSound("golds");
			spdlog::info("L go brrrrrr");
		}

		if (input.isKeyPressed(graphics.w, GLFW_KEY_G) == GLFW_PRESS) {
			sound.playSound("stop");
			spdlog::info("G go brrrrrr");
		}

		if (glfwWindowShouldClose(graphics.w)) {
			Shutdown();
			return;
		}

		/*else {
			spdlog::info("Ran Game Loop");
		}*/

		//ask about if i messed up running this at 60 fps cause it seems like its running less than that
		std::this_thread::sleep_for(oneFrame);
	}
}

#include "Engine.h"
#include "spdlog/spdlog.h"

using namespace Gengine;
using namespace Foo;
using namespace Graphics;
using namespace Input;
using namespace Sound;

Graphics::GraphicsManager graphics;
Input::InputManager input;
Sound::SoundManager sound;
bool fFlag = true, gFlag = true, lFlag = true, curtainCall = false;

void inputCallback();

void Gengine::Engine::Startup(const UpdateCallback& callback) {
	//at some other point i will allow for user input for the window
	graphics.GStartup(1280, 960, "Gengine Collision", false);
	sound.s.init();
	sound.loadSound("golds", "sounds/golds.wav");
	sound.loadSound("stop", "sounds/stop.wav");
	sound.loadSound("moyai", "sounds/moyai.wav");
	graphics.loadImage("closed", "textures/closed.png");
	graphics.loadImage("open", "textures/open.png");
	spdlog::info("Press F for a spectacle.");
	RunGameLoop(callback);
}

void Gengine::Engine::Shutdown() {
	sound.destroySound("golds");
	sound.destroySound("stop");
	sound.destroySound("moyai");
	sound.s.deinit();
	graphics.destroyImage("open");
	graphics.destroyImage("closed");
	graphics.GShutdown();
}

void Gengine::Engine::RunGameLoop(const UpdateCallback& callback) {

	auto oneFrame = std::chrono::duration<real, std::milli>(1.0/60.0);

	while (true) {
		std::chrono::time_point frameStart = std::chrono::steady_clock::now();

		input.Update();

		callback();

		if (glfwWindowShouldClose(graphics.w)) {
			Shutdown();
			return;
		}

		//make a sprite struct that contains all important info on sprites TODO
		if (curtainCall) {
			graphics.Draw("open");
		}
		else {
			graphics.Draw("closed");
		}

		std::chrono::time_point currTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = oneFrame - (currTime - frameStart);

		std::this_thread::sleep_for(diff);
	}
}

void inputCallback()
{
	if (input.isKeyPressed(graphics.w, GLFW_KEY_F) == GLFW_PRESS && fFlag) {
		sound.playSound("moyai");
		spdlog::info("F go brrrrrr");
		fFlag = false;
		curtainCall = true;
	}

	else if (input.isKeyPressed(graphics.w, GLFW_KEY_G) == GLFW_PRESS && gFlag) {
		sound.playSound("stop");
		spdlog::info("G go brrrrrr");
		gFlag = false;
	}

	else if (input.isKeyPressed(graphics.w, GLFW_KEY_L) == GLFW_PRESS && lFlag) {
		sound.playSound("golds");
		spdlog::info("L go brrrrrr");
		lFlag = false;
	}

	if (input.isKeyPressed(graphics.w, GLFW_KEY_F) == GLFW_RELEASE) {
		fFlag = true;
		curtainCall = false;
	}

	if (input.isKeyPressed(graphics.w, GLFW_KEY_G) == GLFW_RELEASE) {
		gFlag = true;
	}

	if (input.isKeyPressed(graphics.w, GLFW_KEY_L) == GLFW_RELEASE) {
		lFlag = true;
	}
}

#include "Engine.h"
#include "spdlog/spdlog.h"

using namespace Gengine;
using namespace Foo;
using namespace Graphics;
using namespace Input;
using namespace Sound;
using namespace temp;

Graphics::GraphicsManager graphics;
Input::InputManager input;
Sound::SoundManager sound;
bool fFlag = true, gFlag = true, lFlag = true, curtainCall = false;

void callback();

void Gengine::Engine::Startup(const UpdateCallback& callback) {
	graphics.GStartup(1280, 960, "Gengine Collision", false);

	sound.s.init();
	sound.loadSound("golds", "sounds/golds.wav");
	sound.loadSound("stop", "sounds/stop.wav");
	sound.loadSound("moyai", "sounds/moyai.wav");

	graphics.loadImage("closed", "textures/closed.png");
	graphics.loadImage("open", "textures/open.png");
	graphics.loadImage("rock", "textures/rock.png");
	graphics.loadImage("rock_closed", "textures/rock_closed.png");

	graphics.sprites.resize(6);
	graphics.sprites[0].name = "closed";
	graphics.sprites[0].translate = vec3(0, 0, 0);
	graphics.sprites[0].scale = vec3(150, 150, 1);
	graphics.sprites[0].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[0].rotateAngle = 180.0;

	graphics.sprites[1].name = "open";
	graphics.sprites[1].translate = vec3(0, 0, 0.9);
	graphics.sprites[1].scale = vec3(150, 150, 1);
	graphics.sprites[1].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[1].rotateAngle = 180.0;

	graphics.sprites[2].name = "rock_closed";
	graphics.sprites[2].translate = vec3(100, -50, 0);
	graphics.sprites[2].scale = vec3(20, 20, 1);
	graphics.sprites[2].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[2].rotateAngle = 170.0;

	graphics.sprites[3].name = "rock";
	graphics.sprites[3].translate = vec3(100, -50, 1);
	graphics.sprites[3].scale = vec3(20, 20, 1);
	graphics.sprites[3].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[3].rotateAngle = 170.0;

	graphics.sprites[4].name = "rock_closed";
	graphics.sprites[4].translate = vec3(-100, -50, 0);
	graphics.sprites[4].scale = vec3(-20, 20, 1);
	graphics.sprites[4].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[4].rotateAngle = 190.0;

	graphics.sprites[5].name = "rock";
	graphics.sprites[5].translate = vec3(-100, -50, 1);
	graphics.sprites[5].scale = vec3(-20, 20, 1);
	graphics.sprites[5].rotateAxis = vec3(0, 0, 1);
	graphics.sprites[5].rotateAngle = 190.0;

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
	graphics.destroyImage("rock");
	graphics.destroyImage("rock_closed");
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

		std::chrono::time_point currTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = oneFrame - (currTime - frameStart);

		std::this_thread::sleep_for(diff);
	}
}

void callback()
{
	if (input.isKeyPressed(graphics.w, GLFW_KEY_F) == GLFW_PRESS && fFlag) {
		sound.playSound("moyai");
		spdlog::info("F go brrrrrr");
		fFlag = false;

		graphics.sprites[0].translate = vec3(0, 0, 0.9);
		graphics.sprites[1].translate = vec3(0, 0, 0);
		graphics.sprites[2].translate = vec3(100, -50, 1);
		graphics.sprites[3].translate = vec3(100, -50, 0);
		graphics.sprites[4].translate = vec3(-100, -50, 1);
		graphics.sprites[5].translate = vec3(-100, -50, 0);
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

		graphics.sprites[0].translate = vec3(0, 0, 0);
		graphics.sprites[1].translate = vec3(0, 0, 0.9);
		graphics.sprites[2].translate = vec3(100, -50, 0);
		graphics.sprites[3].translate = vec3(100, -50, 1);
		graphics.sprites[4].translate = vec3(-100, -50, 0);
		graphics.sprites[5].translate = vec3(-100, -50, 1);
	}

	if (input.isKeyPressed(graphics.w, GLFW_KEY_G) == GLFW_RELEASE) {
		gFlag = true;
	}

	if (input.isKeyPressed(graphics.w, GLFW_KEY_L) == GLFW_RELEASE) {
		lFlag = true;
	}

	graphics.Draw(graphics.sprites);
}

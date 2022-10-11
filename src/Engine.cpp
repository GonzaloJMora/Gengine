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

//write a lua script that does the same stuff that is commented out below and make the rock pictures rotate in real time (also test if dynamic scripting works)

//bool fFlag = true, gFlag = true, lFlag = true, curtainCall = false;

void callback();

void Gengine::Engine::Startup(const UpdateCallback& callback) {
	graphics.GStartup(1280, 960, "Gengine Collision", false);

	script.startUp();

	sound.s.init();

	for (const auto& file : std::filesystem::directory_iterator("./assets/sounds/")) {
		string name = file.path().filename().string();
		name.erase(name.find(".wav"), name.length());
		engine.sound.loadSound(name, (path("sounds") / file.path().filename().string()).string());
	}

	for (const auto& file : std::filesystem::directory_iterator("./assets/textures/")) {
		string name = file.path().filename().string();
		name.erase(name.find(".png"), name.length());
		engine.graphics.loadImage(name, (path("textures") / file.path().filename().string()).string());
	}
	/*sound.loadSound("golds", "sounds/golds.wav");
	sound.loadSound("stop", "sounds/stop.wav");
	sound.loadSound("moyai", "sounds/moyai.wav");

	graphics.loadImage("closed", "textures/closed.png");
	graphics.loadImage("open", "textures/open.png");
	graphics.loadImage("rock", "textures/rock.png");
	graphics.loadImage("rock_closed", "textures/rock_closed.png");*/

	/*ecs.ids.resize(6);
	ecs.ids[0] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[0]).name = "closed";
	ecs.get<Foo::Sprite>(ecs.ids[0]).translate = vec3(0, 0, 0);
	ecs.get<Foo::Sprite>(ecs.ids[0]).scale = vec3(150, 150, 1);
	ecs.get<Foo::Sprite>(ecs.ids[0]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[0]).rotateAngle = 180.0;
	ecs.get<Foo::Position>(ecs.ids[0]).pos = vec2(0, 0);

	ecs.ids[1] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[1]).name = "open";
	ecs.get<Foo::Sprite>(ecs.ids[1]).translate = vec3(0, 0, 0.9);
	ecs.get<Foo::Sprite>(ecs.ids[1]).scale = vec3(150, 150, 1);
	ecs.get<Foo::Sprite>(ecs.ids[1]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[1]).rotateAngle = 180.0;
	ecs.get<Foo::Position>(ecs.ids[1]).pos = vec2(0, 0);

	ecs.ids[2] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[2]).name = "rock_closed";
	ecs.get<Foo::Sprite>(ecs.ids[2]).translate = vec3(100, -50, 0);
	ecs.get<Foo::Sprite>(ecs.ids[2]).scale = vec3(20, 20, 1);
	ecs.get<Foo::Sprite>(ecs.ids[2]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[2]).rotateAngle = 170.0;
	ecs.get<Foo::Position>(ecs.ids[2]).pos = vec2(100, -50);

	ecs.ids[3] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[3]).name = "rock";
	ecs.get<Foo::Sprite>(ecs.ids[3]).translate = vec3(100, -50, 1);
	ecs.get<Foo::Sprite>(ecs.ids[3]).scale = vec3(20, 20, 1);
	ecs.get<Foo::Sprite>(ecs.ids[3]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[3]).rotateAngle = 170.0;
	ecs.get<Foo::Position>(ecs.ids[3]).pos = vec2(100, -50);

	ecs.ids[4] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[4]).name = "rock_closed";
	ecs.get<Foo::Sprite>(ecs.ids[4]).translate = vec3(-100, -50, 0);
	ecs.get<Foo::Sprite>(ecs.ids[4]).scale = vec3(-20, 20, 1);
	ecs.get<Foo::Sprite>(ecs.ids[4]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[4]).rotateAngle = 190.0;
	ecs.get<Foo::Position>(ecs.ids[4]).pos = vec2(-100, -50);

	ecs.ids[5] = ecs.create("ip");
	ecs.get<Foo::Sprite>(ecs.ids[5]).name = "rock";
	ecs.get<Foo::Sprite>(ecs.ids[5]).translate = vec3(-100, -50, 1);
	ecs.get<Foo::Sprite>(ecs.ids[5]).scale = vec3(-20, 20, 1);
	ecs.get<Foo::Sprite>(ecs.ids[5]).rotateAxis = vec3(0, 0, 1);
	ecs.get<Foo::Sprite>(ecs.ids[5]).rotateAngle = 190.0;
	ecs.get<Foo::Position>(ecs.ids[5]).pos = vec2(-100, -50);*/

	engine.script.loadScript("test", "scripts/test.lua");

	spdlog::info("Press F for a spectacle.");
	RunGameLoop(callback);
}

void Gengine::Engine::Shutdown() {
	/*sound.destroySound("golds");
	sound.destroySound("stop");
	sound.destroySound("moyai");*/

	for (std::pair<string, SoLoud::Wav> soundPair : sound.soundMap) {
		sound.destroySound(soundPair.first);
	}

	for (std::pair<string, Image> imagePair : graphics.imageMap) {
		graphics.destroyImage(imagePair.first);
	}

	for (int i = 0; i < ecs.ids.size(); i++) {
		ecs.Destroy(ecs.ids[i]);
	}

	/*graphics.destroyImage("open");
	graphics.destroyImage("closed");
	graphics.destroyImage("rock");
	graphics.destroyImage("rock_closed");*/

	sound.s.deinit();
	graphics.GShutdown();

	exit(EXIT_SUCCESS);
}

void Gengine::Engine::RunGameLoop(const UpdateCallback& callback) {

	auto oneFrame = std::chrono::duration<real, std::milli>(1.0/60.0);

	while (true) {
		std::chrono::time_point frameStart = std::chrono::steady_clock::now();
		
		// updates scripts in real time (does not work)
		/*for (const auto& file : std::filesystem::directory_iterator("./assets/scripts/")) {
			string name = file.path().filename().string();
			name.erase(name.find(".lua"), name.length());
			engine.script.loadScript(name, (path("scripts") / file.path().filename().string()).string());
		}*/

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

	/*if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_F) == GLFW_PRESS && fFlag) {
		engine.sound.playSound("moyai");
		spdlog::info("F go brrrrrr");
		fFlag = false;

		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[0]).translate = vec3(0, 0, 0.9);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[1]).translate = vec3(0, 0, 0);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[2]).translate = vec3(100, -50, 1);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[3]).translate = vec3(100, -50, 0);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[4]).translate = vec3(-100, -50, 1);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[5]).translate = vec3(-100, -50, 0);
	}
	
	else if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_G) == GLFW_PRESS && gFlag) {
		engine.sound.playSound("stop");
		spdlog::info("G go brrrrrr");
		gFlag = false;
	}
	
	else if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_L) == GLFW_PRESS && lFlag) {
		engine.sound.playSound("golds");
		spdlog::info("L go brrrrrr");
		lFlag = false;
	}

	if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_F) == GLFW_RELEASE) {
		fFlag = true;
		curtainCall = false;

		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[0]).translate = vec3(0, 0, 0);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[1]).translate = vec3(0, 0, 0.9);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[2]).translate = vec3(100, -50, 0);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[3]).translate = vec3(100, -50, 1);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[4]).translate = vec3(-100, -50, 0);
		engine.ecs.get<Foo::Sprite>(engine.ecs.ids[5]).translate = vec3(-100, -50, 1);
	}

	if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_G) == GLFW_RELEASE) {
		gFlag = true;
	}

	if (engine.input.isKeyPressed(engine.graphics.w, GLFW_KEY_L) == GLFW_RELEASE) {
		lFlag = true;
	}*/

	engine.graphics.Draw();
}

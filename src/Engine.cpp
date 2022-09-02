#include "Engine.h"
#include "spdlog/spdlog.h"
#include "GraphicsManager.h"
#include <thread>
#include <chrono>

using namespace Eng;
using namespace Foo;
using namespace Graphics;

Graphics::GraphicsManager graphics;

void RunGameLoop();

void Startup() {
	//at some other point i will allow for user input here
	graphics.GStartup(1280, 960, "Amogus Sussy Text Test", false);
	RunGameLoop();
}

void Shutdown() {
	graphics.GShutdown();
}

void RunGameLoop() {

	const std::chrono::time_point startTime = std::chrono::steady_clock::now();
	const auto oneFrame = std::chrono::duration<real, std::milli>(1.0/120.0);

	while (true) {
		std::chrono::time_point currTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = currTime - startTime;

		if (diff.count() >= 5.0) {
			Shutdown();
			return;
		}

		spdlog::info("Ran game loop!!!");
		//ask about if i messed up running this at 60 fps cause it seems like its running less than that
		std::this_thread::sleep_for(oneFrame);
	}
}

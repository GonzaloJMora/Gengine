#include "ScriptManager.h"
#include "Engine.h"
#include "spdlog/spdlog.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

using namespace Entity;
using namespace Script;
using namespace Gengine;

void Script::ScriptManager::startUp()
{
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);

	// expose shutdown function to lua
	lua.set_function("quit", [&]() {engine.Shutdown();});

	// allow users to expose their own functions and usertypes to lua
	lua.set_function("getLua", [&]() -> sol::state& {return Script::ScriptManager::lua;});

	// expose functionality to load and play sounds to lua (file path for loading must include folder and file e.g. "sounds/moyai.wav")
	lua.set_function("playSound", [&](const std::string& name) {engine.sound.playSound(name);});
	lua.set_function("loadSound", [&](const std::string& name, const std::string& path) {engine.sound.loadSound(name, path);});

	// expose funtionality to load textures to lua (file path for loading must include folder and file e.g. "textures/rock.png")
	lua.set_function("loadImage", [&](const std::string& name, const std::string& path) {engine.graphics.loadImage(name, path);});

	// expose ecs functionality to lua
	// components for create include p -> Position, v -> Velocity, g -> Gravity, h -> Health, s -> Script, i -> Sprite, n -> Sound
	lua.set_function("createEntity", [&](std::string components) {return engine.ecs.create(components);});
	lua.set_function("destroyEntity", [&](long long id) {engine.ecs.Destroy(id);});

	lua.new_usertype<Foo::Position>("Position",
		sol::constructors<Foo::Position()>(),
		"pos", &Foo::Position::pos
		);
	lua.new_usertype<Foo::Velocity>("Velocity",
		sol::constructors<Foo::Velocity()>(),
		"vel", &Foo::Velocity::vel
		);
	lua.new_usertype<Foo::Gravity>("Gravity",
		sol::constructors<Foo::Gravity()>(),
		"mps", &Foo::Gravity::meters_per_second
		);
	lua.new_usertype<Foo::Health>("Health",
		sol::constructors<Foo::Health()>(),
		"percent", &Foo::Health::percent
		);
	lua.new_usertype<Foo::Script>("Script",
		sol::constructors<Foo::Script()>(),
		"name", &Foo::Script::name
		);
	lua.new_usertype<Foo::Sound>("Sound",
		sol::constructors<Foo::Sound()>(),
		"name", &Foo::Sound::name
		);
	lua.new_usertype<Foo::Sprite>("Sprite",
		sol::constructors<Foo::Sprite()>(),
		"name", &Foo::Sprite::name,
		"translate", &Foo::Sprite::translate,
		"scale", &Foo::Sprite::scale,
		"rotateAxis", & Foo::Sprite::rotateAxis,
		"rotateAngle", & Foo::Sprite::rotateAngle
		);

	lua.set_function("getPosition", [&](long long e) -> Foo::Position& {return engine.ecs.get<Foo::Position>(e);});
	lua.set_function("getVelocity", [&](long long e) -> Foo::Velocity& {return engine.ecs.get<Foo::Velocity>(e);});
	lua.set_function("getGravity", [&](long long e) -> Foo::Gravity& {return engine.ecs.get<Foo::Gravity>(e);});
	lua.set_function("getHealth", [&](long long e) -> Foo::Health& {return engine.ecs.get<Foo::Health>(e);});
	lua.set_function("getScript", [&](long long e) -> Foo::Script& {return engine.ecs.get<Foo::Script>(e);});
	lua.set_function("getSound", [&](long long e) -> Foo::Sound& {return engine.ecs.get<Foo::Sound>(e);});
	lua.set_function("getSprite", [&](long long e) -> Foo::Sprite& {return engine.ecs.get<Foo::Sprite>(e);});

	// expose vec3 to lua
	lua.new_usertype<glm::vec3>("vec3",
		sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		sol::meta_function::addition, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; }),
		sol::meta_function::subtraction, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; }),
		sol::meta_function::multiplication, sol::overload(
			[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
			[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
			[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
		)
		);

	// expose vec2 to lua
	lua.new_usertype<glm::vec2>("vec2",
		sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y,
		sol::meta_function::addition, sol::overload([](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 + v2; }),
		sol::meta_function::subtraction, sol::overload([](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 - v2; }),
		sol::meta_function::multiplication, sol::overload(
			[](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1 * v2; },
			[](const glm::vec2& v1, float f) -> glm::vec2 { return v1 * f; },
			[](float f, const glm::vec2& v1) -> glm::vec2 { return f * v1; }
		)
		);

	// expose input to lua (add mouse/controller functionality)
	lua.set_function("isKeyDown", [&](const int keycode) {return engine.input.isKeyPressed(engine.graphics.w, keycode);});
	lua.new_enum("KEYBOARD",
		"SPACE", GLFW_KEY_SPACE,
		"APOSTROPHE", GLFW_KEY_APOSTROPHE,
		"COMMA", GLFW_KEY_COMMA,
		"MINUS", GLFW_KEY_MINUS,
		"PERIOD", GLFW_KEY_PERIOD,
		"SLASH", GLFW_KEY_SLASH,
		"0", GLFW_KEY_0,
		"1", GLFW_KEY_1,
		"2", GLFW_KEY_2,
		"3", GLFW_KEY_3,
		"4", GLFW_KEY_4,
		"5", GLFW_KEY_5,
		"6", GLFW_KEY_6,
		"7", GLFW_KEY_7,
		"8", GLFW_KEY_8,
		"9", GLFW_KEY_9,
		"SEMICOLON", GLFW_KEY_SEMICOLON,
		"EQUAL", GLFW_KEY_EQUAL,
		"A", GLFW_KEY_A,
		"B", GLFW_KEY_B,
		"C", GLFW_KEY_C,
		"D", GLFW_KEY_D,
		"E", GLFW_KEY_E,
		"F", GLFW_KEY_F,
		"G", GLFW_KEY_G,
		"H", GLFW_KEY_H,
		"I", GLFW_KEY_I,
		"J", GLFW_KEY_J,
		"K", GLFW_KEY_K,
		"L", GLFW_KEY_L,
		"M", GLFW_KEY_M,
		"N", GLFW_KEY_N,
		"O", GLFW_KEY_O,
		"P", GLFW_KEY_P,
		"Q", GLFW_KEY_Q,
		"R", GLFW_KEY_R,
		"S", GLFW_KEY_S,
		"T", GLFW_KEY_T,
		"U", GLFW_KEY_U,
		"V", GLFW_KEY_V,
		"W", GLFW_KEY_W,
		"X", GLFW_KEY_X,
		"Y", GLFW_KEY_Y,
		"Z", GLFW_KEY_Z,
		"ESCAPE", GLFW_KEY_ESCAPE,
		"ENTER", GLFW_KEY_ENTER,
		"TAB", GLFW_KEY_TAB,
		"BACKSPACE", GLFW_KEY_BACKSPACE,
		"RIGHT", GLFW_KEY_RIGHT,
		"LEFT", GLFW_KEY_LEFT,
		"DOWN", GLFW_KEY_DOWN,
		"UP", GLFW_KEY_UP,
		"KEYPAD_0", GLFW_KEY_KP_0,
		"KEYPAD_1", GLFW_KEY_KP_1,
		"KEYPAD_2", GLFW_KEY_KP_2,
		"KEYPAD_3", GLFW_KEY_KP_3,
		"KEYPAD_4", GLFW_KEY_KP_4,
		"KEYPAD_5", GLFW_KEY_KP_5,
		"KEYPAD_6", GLFW_KEY_KP_6,
		"KEYPAD_7", GLFW_KEY_KP_7,
		"KEYPAD_8", GLFW_KEY_KP_8,
		"KEYPAD_9", GLFW_KEY_KP_9,
		"KEYPAD_DECIMAL", GLFW_KEY_KP_DECIMAL,
		"KEYPAD_DIVIDE", GLFW_KEY_KP_DIVIDE,
		"KEYPAD_MULTIPLY", GLFW_KEY_KP_MULTIPLY,
		"KEYPAD_SUBTRACT", GLFW_KEY_KP_SUBTRACT,
		"KEYPAD_ADD", GLFW_KEY_KP_ADD,
		"KEYPAD_ENTER", GLFW_KEY_KP_ENTER,
		"KEYPAD_EQUAL", GLFW_KEY_KP_EQUAL,
		"LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT,
		"LEFT_CTRL", GLFW_KEY_LEFT_CONTROL,
		"RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT,
		"RIGHT_CTRL", GLFW_KEY_RIGHT_CONTROL
		// TODO add input for mouse and controller glfw.h source code has definitions if i have time
		);
}

bool Script::ScriptManager::loadScript(const Foo::string& name, const Foo::string& path)
{
	bool isUpdate = false;

	if (scriptMap.count(name) > 0) {
		isUpdate = true;
	}

	scriptMap[name] = lua.load_file(engine.resource.resolvePath(path).c_str());

	if (!scriptMap[name].valid()) {
		spdlog::info("Failed to load one or more scripts.");
		return false;
	}

	if (!isUpdate) {
		Entity::EntityID id = engine.ecs.create("s");
		engine.ecs.ids.push_back(id);
		engine.ecs.get<Foo::Script>(id).name = name;
	}

	return true;
}

void Script::ScriptManager::Update() {
	engine.ecs.ForEach<Foo::Script>([&](EntityID e) {

		Foo::Script& s = engine.ecs.get<Foo::Script>(e);

		Script::ScriptManager::scriptMap[s.name](1);

		});
}

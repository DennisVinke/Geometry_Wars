#pragma once

#include <chrono>
#include <cstdint>

#include "EntityManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ShaderManager.h"
#include "GameObjectSpawner.h"
#include "ActionController.h"


class Renderer;

//TODO: Incorperate new SoundManager!

class Game {

public:

    enum class State :int {
        WELCOME,
        PLAYING,
        PAUSE,
        GAMEOVER
    };

private:

	EntityManager entity_manager;
	InputManager input_manager;
	CollisionManager collision_manager;
	std::unique_ptr<Renderer> renderer;
	SoundManager sound_manager;

	GameObjectSpawner object_spawner; //Ik ben hier echt nu om aan het huilen. Bijna een uur hieraan besteed om het werkend te kijgen. RAGE!!!!!!!!!!

	ActionController stateHandler;

	int score;
	int lifes;

	void reset();
	void load_shaders();

	State current_state;
	
public:

	Game();
	~Game();

	void init();
	void update(float delta_time);

	InputManager& get_input_manager();
	Renderer& get_renderer();
	EntityManager& get_entity_manager();
	CollisionManager& get_collision_manager();
		
	void Test();
	void init_level();
	/*
	void onKeyDown(uint32_t key, bool repeated);
	void onKeyUp(uint32_t key, bool repeated);
	void onMouseDown(uint32_t button, uint8_t numOfClicks);
	void onMouseUp(uint32_t button, uint8_t numOfClicks);
	void onMouseMove(uint32_t mouseX, uint32_t mouseY, uint32_t mouseDeltaX, uint32_t mouseDeltaY);
	*/
	State get_game_state();
	void set_game_state(Game::State);

};

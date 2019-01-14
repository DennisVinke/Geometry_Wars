#include "Game.h"
#include "Renderer.h"


Game::Game() : renderer{ std::make_unique<Renderer>() }, object_spawner(GameObjectSpawner(*this)) {
    init();
	init_level();
}

Game::~Game() {
	
}

void Game::init() {
	reset();
	renderer->resized(1280, 720);
	SoundManager::initialize();
	SoundManager::play(Sounds::THEME, true);
	input_manager.addKeyControl(SDL_SCANCODE_SPACE, stateHandler, 1.f);
}

void Game::reset() {
	score = 0;
	lifes = 0;
}

void Game::load_shaders() {
	GaussianBlur::load_shaders();
	ShaderManager::load_shaders();
}

void Game::update(float delta_time) {
	if (get_game_state() == Game::State::PLAYING) {
		entity_manager.update();
		input_manager.update();
		collision_manager.update();
	}
	else if (get_game_state() == Game::State::WELCOME || get_game_state() == Game::State::PAUSE) {
		if (stateHandler.getValue() >= 1) {
			set_game_state(Game::State::PLAYING);
		}
	}

	renderer->render_frame(current_state);
	entity_manager.clean();

}

void Game::set_game_state(Game::State game_state) {
	current_state = game_state;
}
Game::State Game::get_game_state() {
	return current_state;
}

void Game::init_level() {
	object_spawner.spawn_player();
	//object_spawner.spawn
}

InputManager& Game::get_input_manager() {
	return input_manager;
}

Renderer& Game::get_renderer() {
	return *renderer;
}

EntityManager& Game::get_entity_manager() {
	return entity_manager;
}
CollisionManager& Game::get_collision_manager() {
	return collision_manager;
}

/*
#include "MovementComponent.h"
#include "InputComponent.h"
#include "RenderComponent.h"
*/
void Game::Test() {}/*
	blok = entity_manager.CreateEntity();
	blok->setComponent<MovementComponent>(glm::vec2(0, 0));
	blok->setComponent<InputComponent>();
	input_manager.addInputComponent(blok->getComponent<InputComponent>());
	input_manager.addKeyControl(SDL_SCANCODE_A, blok->getComponent<InputComponent>()->getActionController(0), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_D, blok->getComponent<InputComponent>()->getActionController(0), 1.0f);

	input_manager.addKeyControl(SDL_SCANCODE_W, blok->getComponent<InputComponent>()->getActionController(1), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_S, blok->getComponent<InputComponent>()->getActionController(1), 1.0f);

	//ActionController ac, cac, cacr;
	//input_manager.addKeyControl(SDL_SCANCODE_P, ac, 1.f);
	//input_manager.addMouseControl(1, cac, 1.f);
	//input_manager.addMouseControl(3, cacr, 1.f);
	blok->setComponent<RenderComponent>(renderer);

	blok->setComponent<CollideComponent>(collision_manager, CollideMask::PLAYER);
	blok->getComponent<CollideComponent>()->SetCollisionRadius(10);

	for (int i = 0;i < 200; i++) {
		auto test = entity_manager.CreateEntity();
		glm::vec2 spawn(i%600,i%600);//(cac.getClickedPosition() - pos) / glm::distance(cac.getClickedPosition(), pos));
		test->setComponent<MovementComponent>(glm::vec2(sin(i),50)+spawn);
		//spawn.x *= 5;
		//spawn.y *= 5;
		test->getComponent<MovementComponent>()->setConstantMovement(glm::vec2(5,5));
		test->setComponent<RenderComponent>(renderer);
		test->setComponent<CollideComponent>(collision_manager, CollideMask::BULLET);
		test->getComponent<CollideComponent>()->SetCollisionRadius(10);
		auto render_component = test->getComponent<RenderComponent>();
		render_component->shape.set_line_width(7);
		render_component->shape.set_draw_mode(GL_POINTS);
		render_component->shape.set_shape({ {0, 0} });
		render_component->setColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
	}
}



//Op deze manier doorgeven of willen we een get geven aan game? Kunnen ook een event en case van maken en dit in game dan doorverwijzen
//Dus per case iets van handleEvent(event.type, event); Dan kan die andere meuk rechtstreeks in game

//TODO: Dit overleggen!
/*
void Game::onKeyDown(uint32_t key, bool repeated) {
	input_manager.onKeyDown(uint32_t key, bool repeated);
}

void Game::onKeyUp(uint32_t key, bool repeated);
void Game::onMouseDown(uint32_t button, uint8_t numOfClicks);
void Game::onMouseUp(uint32_t button, uint8_t numOfClicks);
void Game::onMouseMove(uint32_t mouseX, uint32_t mouseY, uint32_t mouseDeltaX, uint32_t mouseDeltaY);
*/
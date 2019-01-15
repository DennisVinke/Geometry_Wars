#include <iostream>
#include <vector>
#include <cstdlib>

#include <SDL.h>

#include <glad/glad.h>

#include "components/components.h"

#include "graphics/ShaderManager.h"

#include "engine/InputManager.h"
#include "engine/EntityManager.h"
#include "engine/CollisionManager.h"

#include "sound/SoundManager.h"

#include "Game.h"

#undef main





void configure_context()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
}


void print_context_status()
{
	int profile, major_version, minor_version, double_buffering;
	int red_bits, green_bits, blue_bits, alpha_bits;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &double_buffering);
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red_bits);
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &green_bits);
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &blue_bits);
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &alpha_bits);

	std::cout << "version:\t" << major_version << "." << minor_version << "\n";
	std::cout << "core profile:\t" << ((profile == SDL_GL_CONTEXT_PROFILE_CORE) ? "true" : "false") << "\n";
	std::cout << "vsync:\t\t" << (double_buffering == 1 ? "true" : "false") << "\n";
	std::cout << "rgba bits:\t" << red_bits << ", " << green_bits << ", " << blue_bits << ", " << alpha_bits << "\n";
}

#include "graphics/glm_type_registration.h"

#include "graphics/Renderer.h"

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Error initializing SDL";
		std::exit(1);
	}

	SDL_Window * window = nullptr;
	SDL_GLContext opengl_context = nullptr;

	window = SDL_CreateWindow("test", 100, 100, 1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


	configure_context();

	opengl_context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	SDL_GL_SetSwapInterval(1);

	print_context_status();


	// * *************************************************

	//Application


	GaussianBlur::load_shaders();
	ShaderManager::initialize();
	Game game;//(window);
	float delta_time = 0;

	//Renderer renderer;

	//renderer.resized(640, 480);
	
	// * *************************************************

	//****** Game Loop\\
	//Todo DENNIS: Maak hier nog een apparte game class voor!\\



	/*
	std::cout << "Creating Entity manager" << std::endl;
	EntityManager * eManager = new EntityManager();

	InputManager inputHandler;
	CollisionManager collisionManager;

	


	//GameObject * playerEntity = new PlayerShip(eManager->CreateEntity());

	eManager->update();

	/*auto test = eManager->CreateEntity();
	eManager->update();

	std::cout << "The component is being added!" << std::endl;
	test->setComponent<HealthComponent>();
	eManager->update();

	std::cout << "The component is got!" << std::endl;
	test->getComponent<HealthComponent>()->print();

	std::cout<<"The component is being removed!" << std::endl;
	test->removeComponent<HealthComponent>();
	test->setComponent<MovementComponent>();
	test->getComponent<MovementComponent>()->setConstantMovement(glm::vec2(1, 1));
	//test.setComponent<RenderComponent>(renderer);
	*/

	
	/*int j = 0;
	for (int i = 0; i < 15000;i++) {
		if (i % 100 == 0) ++j;
		gameObjects.emplace_back(eManager->CreateEntity());
		gameObjects.back()->setComponent<MovementComponent>(glm::vec2(i%100, j));
		gameObjects.back()->getComponent<MovementComponent>()->setConstantMovement(glm::vec2(10, 10));
		gameObjects.back()->setComponent<RenderComponent>(renderer);
		gameObjects.back()->getComponent<RenderComponent>()->setColor(20, 200, 10, 120);
		if (i % 1000 == 0) {
			std::cout << "1000 more created" << std::endl;
		}
	}*/


	/*
	auto tower = eManager->CreateEntity();
	tower->setComponent<TransformationComponent>();
	tower->setComponent<RenderComponent>(renderer);

	tower->getComponent<TransformationComponent>()->translate(100, 100);
	tower->getComponent<TransformationComponent>()->rotate(3.14);
	tower->getComponent<TransformationComponent>()->translate(100, 100);
	
	tower->getComponent<RenderComponent>()->shape.set_shape({ {0, 20}, {20, -20}, {-20, -20} });

	tower->setComponent<CollideComponent>(collisionManager, CollideMask::ENEMY);
	tower->getComponent<CollideComponent>()->SetCollisionRadius(20);
	tower->setComponent<MovementComponent>(glm::vec2(400,400));
	/*EntityManager::getLastComponentID<T>();
	*/

	//playerEntity->update();
	//DefaultShader default_shader;
	//default_shader.start();

	// * *************************************************



	for (bool quit = false; !quit;)
	{

		auto start = std::chrono::system_clock::now();
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type) {
			case SDL_KEYDOWN:
				game.get_input_manager().onKeyDown(event.key.keysym.scancode, event.key.repeat != 0);
				break;
			case SDL_KEYUP:
				game.get_input_manager().onKeyUp(event.key.keysym.scancode, event.key.repeat != 0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				game.get_input_manager().onMouseDown(event.button.button, event.button.clicks);
                game.get_renderer().shake(25, 4);
				std::cout << "MouseClicked " << event.button.button<<std::endl;
				break;
			case SDL_MOUSEBUTTONUP:
				game.get_input_manager().onMouseUp(event.button.button, event.button.clicks);
				break;
			case SDL_MOUSEMOTION:
				game.get_input_manager().onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					game.get_renderer().resized(event.window.data1, event.window.data2);
					std::cout << "Window resized to: " << event.window.data1 << ", " << event.window.data2 << "\n";
					break;
				}
			}
		}

		game.update(delta_time);
		

		SDL_GL_SwapWindow(window);
		
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		delta_time = diff.count();
		std::cout << diff.count() << std::endl;
	}

	SoundManager::shutdown();
	SDL_DestroyWindow(window);


	SDL_Quit();

	return 0;
}

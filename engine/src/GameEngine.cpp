#include "GameEngine.hpp"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Scene.hpp"

GameEngine::GameEngine() {
	init();
}

void GameEngine::init() {
	m_window.create(sf::VideoMode({ 1920, 1080 }), "Game Engine", sf::State::Fullscreen);
	m_window.setFramerateLimit(60);

	if (!ImGui::SFML::Init(m_window))
	{
		std::cerr << "Failed to initialize ImGui" << std::endl;
	}
}

void GameEngine::run() {
	while (m_running)
	{
		update();
	}
}

void GameEngine::update() {
	ImGui::SFML::Update(m_window, m_deltaClock.restart());

	if (!m_running)
	{
		return;
	}

	if (m_sceneMap.empty())
	{
		return;
	}

	sUserInput();

	m_window.clear();
	currentScene()->update();
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void GameEngine::quit() {
	m_running = false;
}

std::shared_ptr<Scene> GameEngine::currentScene() {
	return m_sceneMap.at(m_currentScene);
}

sf::RenderWindow& GameEngine::window() {
	return m_window;
}

void GameEngine::sUserInput() {
	while (auto event = m_window.pollEvent())
	{
		// pass the event to imgui to be parsed
		ImGui::SFML::ProcessEvent(m_window, *event);

		if (event->is<sf::Event::Closed>()) { quit(); }

		// this event is triggered when a key is pressed
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			auto it = currentScene()->getActionMap().find(keyPressed->scancode);
			if (it == currentScene()->getActionMap().end())
			{
				continue;
			}

			Action action(it->second, "START");
			currentScene()->sDoAction(action);
		}

		// this event is triggered when a key is released
		if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			auto it = currentScene()->getActionMap().find(keyReleased->scancode);
			if (it == currentScene()->getActionMap().end())
			{
				continue;
			}

			Action action(it->second, "END");
			currentScene()->sDoAction(action);
		}

		// this event is triggered when we click on window with mouse
		if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			Vec2f mPos(mousePressed->position);
			currentScene()->sClickHandler(mPos, mousePressed->button);
		}
	}
}

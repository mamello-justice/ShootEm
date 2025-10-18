#include "Scene_Menu.hpp"

#include <functional>
#include <memory>
#include <print>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Action.hpp"
#include "Assets.hpp"
#include "Button.hpp"
#include "Core.hpp"
#include "Flex.hpp"
#include "GameEngine.hpp"
#include "Scene.hpp"
#include "Scene_Play.hpp"

Scene_Menu::Scene_Menu(std::shared_ptr<GameEngine> gameEngine) : Scene(gameEngine) {
	init();
}

void Scene_Menu::init() {
	registerAction(sf::Keyboard::Scancode::W, "UP");
	registerAction(sf::Keyboard::Scancode::S, "DOWN");
	registerAction(sf::Keyboard::Scancode::D, "PLAY");
	registerAction(sf::Keyboard::Scancode::Escape, "QUIT");

	m_title = std::make_shared<sf::Text>(
		Assets::Instance().getFont("orbitron"), "Shoot Em!", 150);
	m_title->setFillColor(sf::Color::White);
	auto titleX = (m_gameEngine->window().getSize().x - m_title->getLocalBounds().size.x) / 2.f - 20.f;
	m_title->setPosition(Vec2f(titleX, 50.f));

	m_menuBox = std::make_shared<Layout::Flex>();
	m_menuBox->setPosition({
		(m_gameEngine->window().getSize().x - m_menuBox->getLocalBounds().size.x) / 2.f,
		(m_gameEngine->window().getSize().y - m_menuBox->getLocalBounds().size.y) / 2.f
		});
	m_menuBox->setGap(50);

	auto startButton = std::make_shared<Components::Button>(
		std::make_shared<sf::Text>(
			Assets::Instance().getFont("orbitron"),
			"Start",
			50)
	);
	auto startCallback = [=]() {
		std::print("Starting Game\n");
		sDoAction(Action("PLAY", "START")); };
	m_clickListener.registerListener(
		startButton,
		sf::Mouse::Button::Left,
		std::make_shared<std::function<void()>>(startCallback));
	m_menuBox->addChild(startButton);

	auto quitButton = std::make_shared<Components::Button>(std::make_shared<sf::Text>(
		Assets::Instance().getFont("orbitron"),
		"Quit",
		50)
	);
	auto quitCallback = [=]() {
		std::print("Quiting Game\n");
		sDoAction(Action("QUIT", "START")); };
	m_clickListener.registerListener(
		quitButton,
		sf::Mouse::Button::Left,
		std::make_shared<std::function<void()>>(quitCallback));
	m_menuBox->addChild(quitButton);
}

void Scene_Menu::update() {
	sRender();
}

void Scene_Menu::onEnd() {
	m_gameEngine->quit();
}

void Scene_Menu::sDoAction(const Action& action) {
	if (action.type() == "START")
	{
		if (action.name() == "UP")
		{
			if (m_selectedMenuIndex > 0)
			{
				m_selectedMenuIndex--;
			}
			else
			{
				m_selectedMenuIndex = m_menuStrings.size() - 1;
			}
		}
		else if (action.name() == "DOWN")
		{
			m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
		}
		else if (action.name() == "PLAY")
		{
			m_gameEngine->changeScene(
				"PLAY", std::make_shared<Scene_Play>(m_gameEngine));
		}
		else if (action.name() == "QUIT")
		{
			onEnd();
		}
	}
	else if (action.type() == "END")
	{
	}
}

void Scene_Menu::sRender() {
	m_gameEngine->window().clear(sf::Color(11, 16, 38));

	m_gameEngine->window().draw(*m_menuBox);
	m_gameEngine->window().draw(*m_title);
}

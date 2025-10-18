#pragma once

#include "Scene.hpp"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "Action.hpp"
#include "Core.hpp"
#include "GameEngine.hpp"

Scene::Scene(std::shared_ptr<GameEngine> gameEngine) : m_gameEngine(gameEngine) {}

void Scene::setPaused(const bool& paused) {
	m_paused = paused;
}

void Scene::registerAction(const sf::Keyboard::Scan& scancode, const std::string& action) {
	m_actionMap[scancode] = action;
}

const std::map<sf::Keyboard::Scan, std::string>& Scene::getActionMap() const {
	return m_actionMap;
}

void Scene::sClickHandler(const Vec2f& mPos, const sf::Mouse::Button& button) {
	m_clickListener.onClick(mPos, button);
}

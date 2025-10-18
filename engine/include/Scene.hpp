#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "Action.hpp"
#include "Core.hpp"
#include "EntityManager.hpp"
#include "GameEngine.hpp"

class Scene
{
protected:
	std::shared_ptr<GameEngine> m_gameEngine;
	EntityManager m_entityManager;
	int m_frame;
	std::map<sf::Keyboard::Scan, std::string> m_actionMap;
	bool m_paused;
	Listener::Click m_clickListener;

public:
	Scene(std::shared_ptr<GameEngine> gameEngine);

	virtual void update() = 0;

	void registerAction(const sf::Keyboard::Scan& scancode, const std::string& action);

	const std::map<sf::Keyboard::Scan, std::string>& getActionMap() const;

	void sClickHandler(const Vec2f& mPos, const sf::Mouse::Button& button);

	virtual void sDoAction(const Action& action) = 0;

	virtual void sRender() = 0;

	void setPaused(const bool& paused);

};

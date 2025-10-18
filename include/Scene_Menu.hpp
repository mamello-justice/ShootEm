#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "Action.hpp"
#include "Flex.hpp"
#include "GameEngine.hpp"
#include "Scene.hpp"

class Scene_Menu : public Scene {
	std::vector<std::string> m_levelPaths;
	std::vector<std::string> m_menuStrings;
	size_t m_selectedMenuIndex;

	std::shared_ptr<sf::Text> m_title;
	std::shared_ptr<Layout::Flex> m_menuBox;

protected:
	void init();
	void update() override;

	void onEnd();

	void sDoAction(const Action& action) override;
	void sRender() override;

public:
	Scene_Menu(std::shared_ptr<GameEngine> gameEngine);
};

template void GameEngine::changeScene<Scene_Menu>(
	const std::string&, std::shared_ptr<Scene_Menu>);

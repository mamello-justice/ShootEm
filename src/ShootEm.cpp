#include "ShootEm.hpp"

#include <memory>
#include <string>

#include "GameConfig.hpp"
#include "Scene_Menu.hpp"

ShootEm::ShootEm() : m_gameEngine(std::make_shared<GameEngine>()) {
    init();
}

void ShootEm::init() {
    std::srand((unsigned int)time(NULL));

    GameConfig::getInstance().loadFromFile(getConfigPath());

    m_gameEngine->window().setTitle("ShootEm");
    m_gameEngine->window().setSize(sf::Vector2u(
        GameConfig::getInstance().Window.Width,
        GameConfig::getInstance().Window.Height));
}

void ShootEm::run() {
    m_gameEngine->changeScene(
        "Scene_Menu", std::make_shared<Scene_Menu>(m_gameEngine));
    m_gameEngine->run();
}

#include "ShootEm.hpp"

#include <memory>
#include <string>

#include "GameConfig.hpp"
#include "Scene_Menu.hpp"

ShootEm::ShootEm() :
    m_gameEngine(std::make_shared<GameEngine>()) {
    init();
}

void ShootEm::init() {
    std::srand((unsigned int)time(NULL));

    // Initialize Window
    m_gameEngine->window().create(sf::VideoMode::getDesktopMode(), "TooDeeEditor", sf::State::Fullscreen);
    m_gameEngine->window().setFramerateLimit(60);
    m_gameEngine->window().setTitle("ShootEm");

    GameConfig::getInstance().loadFromFile(getConfigPath());
}

void ShootEm::run() {
    m_gameEngine->changeScene(
        "ShootEm_Menu", std::make_shared<Scene_Menu>(m_gameEngine));

    while (m_gameEngine->getIsRunning()) { update(); }
}

void ShootEm::update() {
    m_gameEngine->window().clear();
    m_gameEngine->update();
    m_gameEngine->window().display();
}

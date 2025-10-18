#include "Animation.hpp"

#include <string>
#include <SFML/Graphics.hpp>

#include "Assets.hpp"

Animation::Animation(const std::string& name, const std::string& textureName) : Animation(name, textureName, 1, 0) {}

Animation::Animation(const std::string& name, const std::string& textureName, size_t frameCount, size_t speed)
	: m_name(name), m_frameCount(frameCount), m_currentFrame(0), m_speed(speed), m_textureName(textureName) {
	const sf::Texture& t = Assets::Instance().getTexture(textureName);

	m_textureRect.size = { int(t.getSize().x / frameCount), int(t.getSize().y) };
}

// updates the animation to show the next frame, depending on its
// animation loops when it reaches the end
void Animation::update() {
	m_currentFrame++;

	// TODO: 1) calculate the correct frame of animation to play based on currentFrame
	//		 2) set the texture rectangle properly (see constructor for sample)
}

bool Animation::hasEnded() const {
	// TODO: detect when animation has ended (last frame was played) and return true
	return false;
}

const std::string& Animation::getName() const {
	return m_name;
}

const sf::IntRect& Animation::getRect() const {
	return m_textureRect;
}

const sf::Sprite Animation::getSprite() const {
	return sf::Sprite(Assets::Instance().getTexture(m_textureName), getRect());
}


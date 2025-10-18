#include "Button.hpp"

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

namespace Components
{
    Button::Button(
        std::shared_ptr<sf::Text> text)
        :
        Button(
            text,
            sf::Color::White,
            sf::Color::Transparent,
            sf::Color::Transparent) {}

    Button::Button(
        std::shared_ptr<sf::Text> text,
        const sf::Color& fgColor,
        const sf::Color& bgColor,
        const sf::Color& olColor)
        :
        m_text(text),
        m_bg(std::make_shared<sf::RectangleShape>(text->getGlobalBounds().size)),
        m_fgColor(fgColor),
        m_bgColor(bgColor),
        m_olColor(olColor) {

        auto textPos = text->getLocalBounds().position;
        auto textSize = text->getLocalBounds().size;
        text->setOrigin({
                textPos.x + textSize.x / 2.0f,
                textPos.y + textSize.y / 2.0f
            });
        m_text->setFillColor(fgColor);

        setSize(textSize);

        auto bgPos = m_bg->getPosition();
        auto bgSize = m_bg->getSize();
        m_bg->setOrigin({
                bgPos.x + bgSize.x / 2.0f,
                bgPos.y + bgSize.y / 2.0f
            });
        m_bg->setFillColor(bgColor);
        m_bg->setOutlineColor(olColor);
    }

    void Button::setSize(Vec2f size) {
        m_size = size;

        m_bg->setSize(size);

        update();
    }

    void Button::setText(std::string t) {
        m_text->setString(t);
    }

    void Button::setTextColor(const sf::Color& fgColor) {
        m_fgColor = fgColor;
        m_text->setFillColor(fgColor);
    }

    void Button::setBackgroundColor(const sf::Color& bgColor) {
        m_bgColor = bgColor;
        m_bg->setFillColor(bgColor);
    }

    void Button::setOutlineColor(const sf::Color& olColor) {
        m_olColor = olColor;
        m_bg->setOutlineColor(olColor);
    }

    std::size_t Button::getPointCount() const {
        return 4;
    }

    sf::Vector2f Button::getPoint(std::size_t index) const {
        switch (index)
        {
        default:
        case 0:
            return { 0, 0 };
        case 1:
            return { m_size.x, 0 };
        case 2:
            return { m_size.x, m_size.y };
        case 3:
            return { 0, m_size.y };
        }
    }

    sf::Vector2f Button::getGeometricCenter() const {
        return m_size / 2.f;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        auto pos = getPosition();

        // Update position
        m_text->setPosition(pos);
        m_bg->setPosition(pos);

        target.draw(*m_bg, states);
        target.draw(*m_text, states);
    }

} // namespace Component

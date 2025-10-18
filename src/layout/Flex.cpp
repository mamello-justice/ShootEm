#include "Flex.hpp"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Layout
{
    Flex::Flex()
        : Flex(sf::Color::Transparent, sf::Color::Transparent) {}

    Flex::Flex(
        const sf::Color& bgColor,
        const sf::Color& olColor)
        :
        m_bg(std::make_shared<sf::RectangleShape>()),
        m_bgColor(bgColor),
        m_olColor(olColor) {
        updateBackground();
        m_bg->setFillColor(bgColor);
        m_bg->setOutlineColor(olColor);
    }

    void Flex::updateBackground() {
        m_bg->setSize(m_size);
        m_bg->setPosition(getPosition());

        auto bgPos = m_bg->getPosition();
        m_bg->setOrigin({
                bgPos.x + m_size.x / 2.0f,
                bgPos.y + m_size.y / 2.0f
            });

        {
            auto size = m_bg->getSize();
            auto pos = m_bg->getPosition();
        }
    }

    void Flex::updateChildren() {
        auto pos = getPosition();
        std::shared_ptr<sf::Shape> prev = nullptr;
        for (auto child : m_children) {
            size_t offsetY = 0;

            if (prev) {
                offsetY += prev->getGlobalBounds().size.y + m_gap;
            }

            child->setPosition({ pos.x, pos.y + offsetY });
            prev = child;
        }
    }

    void Flex::updateSize() {
        float width = 0.f, height = 0.f;

        for (auto& child : m_children) {
            auto size = child->getGlobalBounds().size;
            if (size.x > width) {
                width = size.x;
            }
            height += size.y;
            height += m_gap;
        }
        // Remove last item gap
        if (m_children.size() > 1) {
            height -= m_gap;
        }
        setSize({ width, height });
    }

    void Flex::setGap(float gap) {
        m_gap = gap;

        updateSize();
        updateChildren();
    }

    void Flex::setSize(Vec2f size) {
        m_size = size;

        update();
        updateBackground();
    }

    void Flex::addChild(std::shared_ptr<sf::Shape> child) {
        m_children.push_back(child);
        updateSize();
        updateChildren();
    }

    void Flex::setBackgroundColor(const sf::Color& bgColor) {
        m_bgColor = bgColor;
        m_bg->setFillColor(bgColor);
    }

    void Flex::setOutlineColor(const sf::Color& olColor) {
        m_olColor = olColor;
        m_bg->setOutlineColor(olColor);
    }

    Vec2f Flex::getSize() const {
        return m_size;
    }

    std::size_t Flex::getPointCount() const {
        return m_bg->getPointCount();
    }

    sf::Vector2f Flex::getPoint(std::size_t index) const {
        return m_bg->getPoint(index);
    }

    sf::Vector2f Flex::getGeometricCenter() const {
        return m_bg->getGeometricCenter();
    }

    void Flex::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(*m_bg, states);

        for (auto child : m_children) {
            target.draw(*child, states);
        }
    }
} //namespace Layout

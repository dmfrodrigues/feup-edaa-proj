#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Line shape; an abstraction of an edge (dashed or full line).
 */
namespace sf {
    class LineShape: public sf::VertexArray {
    public:
        /**
         * @brief Construct a new LineShape.
         * 
         * @param u     Origin position
         * @param v     Destination position
         * @param w     Line width
         */
        explicit LineShape(const sf::Vector2f& u, const sf::Vector2f& v, float w);

        /**
         * @brief Set origin position.
         * 
         * @param u     Origin position.
         */
        virtual void setFrom(const sf::Vector2f& u);
        /**
         * @brief Get origin position.
         * 
         * @return const sf::Vector2f&  Origin position.
         */
        const sf::Vector2f& getFrom() const;

        /**
         * @brief Set destination position.
         * 
         * @param v     Destination position.
         */
        virtual void setTo(const sf::Vector2f& v);
        /**
         * @brief Get destination position.
         * 
         * @return const sf::Vector2f&  Destination position.
         */
        const sf::Vector2f& getTo() const;

        /**
         * @brief Set line width.
         * 
         * @param w     Line width, in pixels
         */
        virtual void setWidth(float w);
        /**
         * @brief Get line width.
         * 
         * @return float    Line width, in pixels 
         */
        float getWidth() const;

        /**
         * @brief Set edge fill color.
         * 
         * @param color     Fill color
         */
        void setFillColor(sf::Color color);

        void append(const sf::Vertex &v);
        void append(const sf::VertexArray &v);

    private :
        sf::Vector2f u;     ///< @brief Origin position.
        sf::Vector2f v;     ///< @brief Destination position.
        float w;            ///< @brief Line width, in pixels.
    };

    /**
     * @brief Full line shape.
     */
    class FullLineShape: public LineShape {
    public:
        /**
         * @brief Construct a new FullLineShape.
         * 
         * @param u     Origin position
         * @param v     Destination position
         * @param w     Line width
         */
        explicit FullLineShape(const sf::Vector2f& u, const sf::Vector2f& v, float w);

        void setFrom (const sf::Vector2f& u) override;
        void setTo   (const sf::Vector2f& v) override;
        void setWidth(             float  w) override;

        /**
         * @brief Process property changes.
         */
        void process();
    };

    /**
     * @brief Dashed line shape.
     */
    class DashedLineShape: public LineShape {
    private:
        float dashFill = 0.5;
    public:
        /**
         * @brief Construct a new DashedLineShape.
         * 
         * @param u     Origin position
         * @param v     Destination position
         * @param w     Line width
         */
        explicit DashedLineShape(const sf::Vector2f& u, const sf::Vector2f& v, float w);

        void setFrom (const sf::Vector2f& u) override;
        void setTo   (const sf::Vector2f& v) override;
        void setWidth(             float  w) override;

        /**
         * @brief Process property changes.
         */
        void process();
    };

    class ArrowHead: public LineShape {
    private:
        static const float widthFactor;
        static const float lengthFactor;
        static const float advanceFactor;
    public:
        explicit ArrowHead(const sf::Vector2f& u, const sf::Vector2f& v, float w);

        void setFrom (const sf::Vector2f& u) override;
        void setTo   (const sf::Vector2f& v) override;
        void setWidth(             float  w) override;

        /**
         * @brief Process property changes.
         */
        void process();

        sf::Vector2f getLineConnection() const;
    };
}

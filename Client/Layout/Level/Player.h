#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.h"

struct CollisionInfo {
    int collisionSide = 0;
    float availablePos = 0;
};

class Player {
   private:
    sf::FloatRect rect;

    sf::Vector2f plVelocity = {0.0f, 0.0f};
    const sf::Vector2f defVel = {1.0f, 2.3f};

    bool onGround = false;
    bool onStairs = false;
    bool stairsAvailable = false;
    bool jumped = false;

    sf::Texture plTexture;
    sf::Sprite* playerSprite;

   public:
    Player() = default;
    Player(const std::string& path);
    Player(Player&) = default;
    ~Player();

    void update(const Map& map, int time);

    CollisionInfo collisionX(const Map& map) const;
    CollisionInfo singleCollisionX(float top, float bottom, const Map& map,
                                   int x, const int& cageSize) const;
    CollisionInfo collisionY(const Map& map) const;
    CollisionInfo singleCollisionY(float left, float right, const Map& map,
                                   int y, const int& cageSize) const;

    CollisionInfo stairsCollisionY(const Map& map);
    CollisionInfo bottomStairsCollisionY(const Map& map) const;

    static bool isStairs(int curCage);
    static bool isTopOfStairs(int curCage);
    static bool isBlock(int curCage);

    void jump();

    void move(int direction);

    void grab(int direction);

    void setPos(sf::Vector2f pos);
    sf::Vector2i getPos() const;

    void setVel(sf::Vector2f vel);
    sf::Vector2f getVel() const;

    bool isOnGround() const;

    bool isOnStairs() const;
    bool isStairsAvailable() const;

    sf::Sprite* getSprite(sf::Vector2i offset) const;
    sf::RectangleShape dbgSprite(sf::Vector2i offset) const;
};
#pragma once

#include <SFML/Graphics.hpp>

class Component {};

class CTransform : public Component {
public:
	sf::Vector2f pos = { 0.0f, 0.0f };
	sf::Vector2f prevPos = { 0.0f, 0.0f };
	sf::Vector2f scale = { 1.0f, 1.0f };
	sf::Vector2f velocity{ 0.0f, 0.0f };
	float angle = 0;

	CTransform(const sf::Vector2f& p, const sf::Vector2f& v, float a)
		: pos(p), velocity(v), angle(a) {}
};

class CShape : public Component {
public:
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points) {
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}

	auto getFillColor() const { return circle.getFillColor(); }

	void setFillColor(const sf::Color& fill) { circle.setFillColor(fill); }

	void setOutlineColor(const sf::Color& outline) { circle.setOutlineColor(outline); }
};

class CBoundingBox : public Component {
public:
	sf::Vector2f size;
	sf::Vector2f halfSize;
	CBoundingBox(const sf::Vector2f& s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CCollision : public Component {
public:
	float radius = 0;
	CCollision(float r)
		: radius(r) {}
};

class CInput : public Component {
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput() {}
};

class CScore : public Component {
public:
	int score = 0;
	CScore(int s)
		: score(s) {}
};

class CLifeSpan : public Component {
public:
	int remaining = 0;	// amount of lifespan remaining on the entity
	int total = 0;		// the toal initial amount of lifespan
	CLifeSpan(int total)
		: remaining(total), total(total) {}
};

class CAnimation : public Component {
public:
	//Animation animation;
};
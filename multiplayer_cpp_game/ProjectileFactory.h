#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ObjectPool.h"

class baseProjectile;
class bullet;

class ProjectileFactory
{
public:
	ProjectileFactory();
	~ProjectileFactory();

	// Initialize resources and pools
	void initialize();

	//get projectile of type
	baseProjectile* createProjectile(
		const std::string& type,
		sf::Vector2f position,
		sf::Angle angle,
		sf::Vector2f velocity);

	void recycleProjectile(baseProjectile* projectile);

private:
	//suggested to include here, todo remove?
	sf::Texture bulletTexture;

	// Object pools for different projectile types
	ObjectPool<bullet>* bulletPool;

	// Factory methods for creating projectiles
	bullet* createBullet();

};


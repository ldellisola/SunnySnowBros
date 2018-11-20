#pragma once


#include "Projectile.h"
#include <stdint.h>

class FireProjectile
	:public Projectile
{
public:
	FireProjectile(uint16_t x, uint16_t y, HorizontalDirection dir, Score* score)
		:Projectile(x, y, dir, 3, 6, (Score*)score)
	{
	}

	~FireProjectile()
	{
	}


};

#include "SnowBall.h"

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*4)	// 200ms
#define FallTicks (ms50*6)	// 300ms

SnowBall::SnowBall(Monster * monster, Score * PlayerScore)
	:Slider(monster->getX(), WalkTicks),Jumper(monster->getY(), JumpTicks, FallTicks)
{

	this->state = SnowBallState::Rolling;
	this->setHorizontalDir(HorizontalDirection::Left);
	this->capturedMonster = monster;
	this->playerScore = PlayerScore;
	this->enemyHits = 0;
	this->wallHits = 0;
}

bool SnowBall::collision(Being * being)
{

	if (this->getX() == being->getX() && this->getY() == being->getY()) {

		if (dynamic_cast<Monster*>(being)) {
			this->enemyHits++;
			being->kill();
			for (int i = 1; i <= enemyHits; i++) {
				*playerScore += i * 1000;
			}


		}
		else if (dynamic_cast<Player *>(being)) {
			hijackedPlayers.push_back((Player*)being);
			being->setState(BeingState::Carried);
		}


		return true;
	}

	return false;
}

void SnowBall::update(void * ptr)
{

	World& world = *(World *) ptr;

	switch (getHorizontalDir())
	{
	case HorizontalDirection::Left:

		if (world.map[getY()][getX() - 1] == 'F') {
			wallHits++;
			this->setHorizontalDir(HorizontalDirection::Right);
		}

		break;
	case HorizontalDirection::Right:
		if (world.map[getY()][getX() + 1] == 'F') {
			wallHits++;
			this->setHorizontalDir(HorizontalDirection::Left);
		}
		break;

	}




	std::unique_ptr<char> row(new char[world.columna]);

	for (int i = 0; i < world.columna; i++) {
		row.get()[i] = world.map[getY()][i];
	}

	Slider::update(row.get());

	std::unique_ptr<char> column(new char[world.fila]);

	for (int i = 0; i < world.fila; i++) {
		column.get()[i] = world.map[i][getX()];
	}

	Jumper::update(column.get());

	for (Player* plyr : hijackedPlayers) {
		plyr->setX(getX());
		plyr->setY(getY());
	}




}

bool SnowBall::shouldDie()
{
	if (wallHits == maxHits)
		return true;
	else 
		return false;
}

SnowBall::~SnowBall ()
{
}

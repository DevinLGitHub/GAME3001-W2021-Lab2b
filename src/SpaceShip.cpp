#include "SpaceShip.h"


#include "Game.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", 
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f) );
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
}

void SpaceShip::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 SpaceShip::getOrientation() const
{
	return m_orientation;
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}

void SpaceShip::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float SpaceShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

void SpaceShip::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setRotation(float angle)
{
	// angle to degrees
	m_rotationAngle = angle;
	auto angle_in_radians = (angle - 90.0f) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);
	
	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float SpaceShip::getRotation() const
{
	return m_rotationAngle;
}

void SpaceShip::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	
	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	
	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	std::cout << "Target Rotation: " << target_rotation << std::endl;
		
	//getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	//getTransform()->position += getRigidBody()->velocity;
}

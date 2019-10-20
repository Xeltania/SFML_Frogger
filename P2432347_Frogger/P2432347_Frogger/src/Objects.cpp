#include "Objects.h"

using namespace std;

Objects::Objects()
{

	// Instantiation of lanes attribute values //
	m_fCarLane1 = 550;
	m_fCarLane2 = 680;
	m_fCarLane3 = 800;
	m_fLogLane1 = 140;
	m_fLogLane2 = 240;
	m_fLogLane3 = 350;
	m_iCarSpawnOffset = 850;
	m_iLogSpawnOffset = 700;

	// Instantiation of movement variables //
	m_fCarSpeed = 5.f;
	m_fLogSpeed = 1.5f;

	// Instantiation of object sizes //
	carSize.x = 1.f;
	carSize.y = 1.f;
	logSize.x = 2;
	logSize.y = 2;
	carScale.x = 100;
	carScale.y = 90;
	logScale.x = 75;
	logScale.y = 30;

	// Set the textures of the cars and logs //
	m_sCarTexPath = "..\\Assets\\Textures\\car.png";
	m_sLogTexPath = "..\\Assets\\Textures\\log.png";
	carTex.loadFromFile(m_sCarTexPath);
	logTex.loadFromFile(m_sLogTexPath);

	// Targeting each of the cars in the car spritesheet //
	carTexTarget1 = sf::IntRect(1, 0, (133 / 7), 20);
	carTexTarget2 = sf::IntRect((133 / 7), 0, (133 / 8 * 2), 20);
	carTexTarget3 = sf::IntRect((133 / 8 * 3), 0, (133 / 8 * 2.5), 20);

	const int m_iNumObjects = 9; // Defines how many objects there are of each type.
	// Using a loop, go through the arrays of objects and set their textures, sizes, and positions //
	for (int i = 0; i < m_iNumObjects; i++)
	{
		// Car Setup //
		m_aCarArr[i].setSize(carSize);
		m_aCarArr[i].setScale(carScale);
		m_aCarArr[i].setOrigin(carSize.x / 2, carSize.y / 2);
		m_aCarArr[i].setTexture(&carTex);

		// Chooses a random car texture for each car shape //
		m_iCarTexChoice = rand() % 3;
		cout << m_iCarTexChoice << endl;

		switch (m_iCarTexChoice)
		{
		case 0: m_aCarArr[i].setTextureRect(carTexTarget1);
			break;
		case 1: m_aCarArr[i].setTextureRect(carTexTarget2);
			break;
		case 2: m_aCarArr[i].setTextureRect(carTexTarget3);
			break;
		}
		// Log Setup //
		m_aLogArr[i].setSize(logSize);
		m_aLogArr[i].setScale(logScale);
		m_aLogArr[i].setOrigin(logSize.x / 2, logSize.y / 2);
		m_aLogArr[i].setTexture(&logTex);
	}
	for (int i = 0; i < (m_iNumObjects / 3); i++) // First lane of objects:
	{
		m_aCarArr[i].setPosition(m_iCarSpawnOffset, m_fCarLane1);
		m_aCarArr[i].setRotation(180); // flip the sprites to face the right way.
		m_iCarSpawnOffset -= 350;

		m_aLogArr[i].setPosition(m_iLogSpawnOffset, m_fLogLane1);
		m_iLogSpawnOffset -= 300;

	}

	// Reset the offsets.
	m_iCarSpawnOffset = 750;
	m_iLogSpawnOffset = 1050;
	for (int i = 3; i < (m_iNumObjects * 2 / 3); i++) // Second lane of objects: 
	{
		m_aCarArr[i].setPosition(m_iCarSpawnOffset, m_fCarLane2);
		m_iCarSpawnOffset -= 350;

		m_aLogArr[i].setPosition(m_iLogSpawnOffset, m_fLogLane2);
		m_iLogSpawnOffset -= 400;

	}

	// Reset offsets.
	m_iCarSpawnOffset = 650;
	m_iLogSpawnOffset = 750;
	for (int i = 6; i < m_iNumObjects; i++) // Third lane of objects:
	{
		m_aCarArr[i].setPosition(m_iCarSpawnOffset, m_fCarLane3);
		m_iCarSpawnOffset -= 300;

		m_aLogArr[i].setPosition(m_iLogSpawnOffset, m_fLogLane3);
		m_iLogSpawnOffset -= 350;

	}

}

void Objects::MoveObjects(float carSpeed, float logSpeed) // Method that sets the speeds of the objects:
{
	carSpeed = m_fCarSpeed;
	logSpeed = m_fLogSpeed;

	for (int i = 0; i < 9; i++)
	{
		if (i < 3) // First lane speeds:
		{
			carSpeed = 0.1f;
			logSpeed = 0.3f;
		}
		if (i > 2 && i < 6) // Second lane speeds:
		{
			carSpeed = -0.25f;
			logSpeed = -0.5f;
		}
		else if (i > 5 && i < 9) // Third lane speeds:
		{
			carSpeed = 0.05f;
			logSpeed = 0.25f;
		}
		// Make the objects move left/right at their speed:
		m_aCarArr[i].move(carSpeed, 0);
		m_aLogArr[i].move(logSpeed, 0);
	}
	CheckObjectPosition(1, 1, 1, 1, 1, 1);
}

void Objects::CheckObjectPosition(float carLane1, float carLane2, float carLane3, float logLane1, float logLane2, float logLane3) // Checks if the objecst move off screen:
{

	carLane1 = m_fCarLane1;
	carLane2 = m_fCarLane2;
	carLane3 = m_fCarLane3;
	logLane1 = m_fLogLane1;
	logLane2 = m_fLogLane2;
	logLane3 = m_fLogLane3;

	Game Window; // Object of game window used to define the width.

	for (int i = 0; i < 9; i++)
	{
		if (m_aCarArr[i].getPosition().x < (0 - (m_aCarArr[i].getScale().x))) // If the object is moving off screen to the left:
		{
			// Reset to the edge of the screen and into the right y position (the right lane).
			if (i < 6)
			{
				if (i < 3)
				{
					m_aCarArr[i].setPosition(Window.GetWindowW() + (m_aCarArr[i].getScale().x), carLane1);
				}
				else
				{
					m_aCarArr[i].setPosition(Window.GetWindowW() + (m_aCarArr[i].getScale().x), carLane2);
				}
			}
			else
			{
				m_aCarArr[i].setPosition(Window.GetWindowW() + (m_aCarArr[i].getScale().x), carLane3);
			}
		}
		if (m_aLogArr[i].getPosition().x < (0 - (m_aLogArr[i].getScale().x))) // If the object is moving off screen to the left:
		{
			// Reset to the edge of the screen and into the right y position (the right lane).
			if (i < 6)
			{
				if (i < 3)
				{
					m_aLogArr[i].setPosition(Window.GetWindowW() + (m_aLogArr[i].getScale().x / 2), logLane1);
				}
				else
				{
					m_aLogArr[i].setPosition(Window.GetWindowW() + (m_aLogArr[i].getScale().x / 2), logLane2);
				}
			}
			else
			{
				m_aLogArr[i].setPosition(Window.GetWindowW() + (m_aLogArr[i].getScale().x / 2), logLane3);
			}
		}
		else if (m_aCarArr[i].getPosition().x > (Window.GetWindowW() + (m_aCarArr[i].getScale().x))) // Otherwise if objects are moving off to the right: 
		{
			// Reset to the start of the screen and into the right y position (the right lane).
			if (i < 6)
			{
				if (i < 3)
				{
					m_aCarArr[i].setPosition(0 - (m_aCarArr[i].getScale().x), carLane1);
				}
				else
				{
					m_aCarArr[i].setPosition(0 - (m_aCarArr[i].getScale().x), carLane2);
				}
			}
			else
			{
				m_aCarArr[i].setPosition(0 - (m_aCarArr[i].getScale().x), carLane3);
			}
		}
		else if (m_aLogArr[i].getPosition().x > (Window.GetWindowW() + (m_aLogArr[i].getScale().x))) // Otherwise if objects are moving off to the right: 
		{
			// Reset to the start of the screen and into the right y position (the right lane).
			if (i < 6)
			{
				if (i < 3)
				{
					m_aLogArr[i].setPosition(0 - (m_aLogArr[i].getScale().x), logLane1);
				}
				else
				{
					m_aLogArr[i].setPosition(0 - (m_aLogArr[i].getScale().x), logLane2);
				}
			}
			else
			{
				m_aLogArr[i].setPosition(0 - (m_aLogArr[i].getScale().x), logLane3);
			}
		}
	}
}


void Objects::draw(sf::RenderTarget & target, sf::RenderStates states) const // Targets all of the objects so they may be drawn in main() .
{
	target.draw(carRect1);
	target.draw(carRect2);
	target.draw(carRect3);
	target.draw(carRect4);
	target.draw(carRect5);
	target.draw(carRect6);
	target.draw(carRect7);
	target.draw(carRect8);
	target.draw(carRect9);
	target.draw(logRect1);
	target.draw(logRect2);
	target.draw(logRect3);
	target.draw(logRect4);
	target.draw(logRect5);
	target.draw(logRect6);
	target.draw(logRect7);
	target.draw(logRect8);
	target.draw(logRect9);
}


Objects::~Objects()
{
}

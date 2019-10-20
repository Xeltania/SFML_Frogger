#pragma once
#include "Game.h"

using namespace std;

class Objects : public sf::Drawable
{
public:
	Objects();
	~Objects();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// Methods to animate the objects moving.
	void MoveObjects(float carSpeed, float logSpeed);
	void CheckObjectPosition(float carLane1, float carLane2, float carLane3, float logLane1, float logLane2, float logLane3); // Used to make sure the objects never diappear off screen when moving.
	sf::RectangleShape carRect1, carRect2, carRect3, carRect4, carRect5, carRect6, carRect7, carRect8, carRect9; // The definition of the car object shapes.
	sf::RectangleShape logRect1, logRect2, logRect3, logRect4, logRect5, logRect6, logRect7, logRect8, logRect9; // The definition of the log object shapes.

	// Arrays holding the individual Rectangles of the Objects so they may be referenced as a group elsewhere //
	sf::RectangleShape m_aCarArr[9]{ carRect1,carRect2,carRect3,carRect4,carRect5,carRect6,carRect7,carRect8,carRect9 };
	sf::RectangleShape m_aLogArr[9]{ logRect1,logRect2,logRect3,logRect4,logRect5,logRect6,logRect7,logRect8,logRect9 };

private:

	// Textures attributes //
	sf::Texture carTex, logTex; // The texture of the objects
	string m_sCarTexPath, m_sLogTexPath; // Defines the path to the texure of the objects.
	sf::IntRect carTexTarget1, carTexTarget2, carTexTarget3; // Used to target the car sprite from the spritesheet.
	int m_iCarTexChoice;
	sf::Texture lilypadTex;
	string m_sLilypadTexPath;

	// Size and Scale Vectors //
	sf::Vector2f carSize, logSize; // Used to define the size of each object.
	sf::Vector2f carScale, logScale; // Defines the scaling of each object.


		// Lanes Attributes //
	float m_fCarLane1, m_fCarLane2, m_fCarLane3; // Defines the Y position for the objects for car lanes.
	float m_fLogLane1, m_fLogLane2, m_fLogLane3; // Defines the Y position for the objects for log lanes.
	int m_iCarSpawnOffset, m_iLogSpawnOffset; // Used to spawn in cars and logs at different x positions.

		// Speeds attributes //
	float m_fCarSpeed, m_fLogSpeed; // Used to define the speed at which the objects shall be transformed at.

};


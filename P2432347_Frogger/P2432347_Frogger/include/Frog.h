#pragma once
#include "Game.h"
class Frog : public Game
{
public:
	Frog();
	~Frog();
	//void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	// Private attributes for the frog and its lives //
	sf::Sprite frogSprite;
	sf::Sprite livesUI[3], livesDeadUI[3];
	sf::Texture livesTexture, deadLivesTexture; // Textures for lives and when a life is lost.
	string uiPath, uiPath2;

	// Methods for Frog controls //
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ResetFrogPos();

	// Setters //
	void SetValues(bool leftDown, bool rightDown, bool upDown, bool downDown); // Updates the value of the bools depending on which key has been pressed.
	void SetLives(int lives);
	void SetDeadUIVisible();
	void ResetDeadUIVisible();


	// Getters //
	bool GetUp();
	bool GetDown();
	bool GetLeft();
	bool GetRight();
	int GetLives();
	sf::Vector2f GetPositionSprite();

	// Animation Method //
	void FrogAnimation();

private:
	// Variables used to define the frog sprite's attributes //
	string texturePath;
	sf::Texture frogTexture;
	sf::Vector2f frogSize;
	sf::IntRect defaultFrog; // Rectangles to target the sprites on the spritesheet.
	sf::Clock FrameClock;
	bool m_bRunAnimation;
	int m_iLives;
	int m_iFrogScalerX, m_iFrogScalerY; // Used to scale the frog sprite to be more visible.
	int m_iTextureFrameWidth, m_iTextureFrameHeight;

	// Value that is used to move the frog //
	int m_iOffsetX, m_iOffsetY;
	sf::Vector2f startPosition;

	// Bools defining whether a key is being pressed //
	bool m_bLeftKeyDown;
	bool m_bRightKeyDown;
	bool m_bUpKeyDown;
	bool m_bDownKeyDown;



};


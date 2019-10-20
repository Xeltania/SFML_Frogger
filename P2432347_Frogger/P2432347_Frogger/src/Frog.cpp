#include "Frog.h"

using namespace std;


Frog::Frog()
{
	m_iOffsetY = GetWindowW() / 10; // Sets the offset to 1/10th of the window width so the frog doesn't jump too fast.
	m_iOffsetX = GetWindowW() / 20;

	// Definition of the sprite size //
	frogSize.x = 60.f;
	frogSize.y = 60.f;
	m_iFrogScalerX = 3;
	m_iFrogScalerY = 1;
	m_iTextureFrameWidth = frogTexture.getSize().x / 5.5;
	m_iTextureFrameHeight = frogTexture.getSize().y;

	// Initialisation of the targeted sprites //
	defaultFrog = sf::IntRect(48, 0, 14, 18);
	m_bRunAnimation = false; // By default set the movement animation to false.

	// Sprite and Texture setting //
	texturePath = "..\\Assets\\Textures\\FrogSheet.png"; // Points to the Frog Spritesheet in Assets.
	frogTexture.loadFromFile(texturePath); // Sets the texture to the Frog Spritesheet.
	frogSprite.setScale((frogSize.x / frogTexture.getSize().x * m_iFrogScalerX), (frogSize.y / frogTexture.getSize().y * m_iFrogScalerY)); // Sets the scale of the sprite to a relative size.
	frogSprite.setOrigin(defaultFrog.width / 2, defaultFrog.height / 2); //Sets the origin of the sprite to the centre.
	frogSprite.setTexture(frogTexture); // Sets the sprite's texture to the above texture.
	frogSprite.setTextureRect(defaultFrog);

	//Set the sprite position relative to the window size //
	//frogSprite.setPosition(GetWindowW()/2,GetWindowH()-15); old method of setting the frog position using magic numbers. Created vector.
	startPosition.x = GetWindowW() / 2;
	startPosition.y = GetWindowH() - 15;
	frogSprite.setPosition(startPosition);
	SetLives(3); // Initial value for the lives.

	// Set the Lives UI Array //
	uiPath = "..\\Assets\\Textures\\LivesSprite.png";
	livesTexture.loadFromFile(uiPath);

	// Set the Dead Lives UI Array//
	uiPath2 = "..\\Assets\\Textures\\DeadSprite.png";
	deadLivesTexture.loadFromFile(uiPath2);
	for (int i = 0; i < 3; i++)  // For loop to set up the Lives UI:
	{
		livesUI[i].setTexture(livesTexture);
		livesUI[i].setScale(sf::Vector2f(2, 2));
		livesDeadUI[i].setTexture(deadLivesTexture);
		livesDeadUI[i].setScale(sf::Vector2f(2, 2));
		livesDeadUI[i].setColor(sf::Color(255, 255, 255, 0)); // Set the dead live sprite to invisible by default.

	// Set the positions for the sprites:
		if (i > 1)
		{
			livesUI[i].setPosition(100, 50);
			livesDeadUI[i].setPosition(100, 50);
		}
		else if (i < 1)
		{
			livesUI[i].setPosition(30, 50);
			livesDeadUI[i].setPosition(30, 50);
		}
		else
		{
			livesUI[i].setPosition(65, 50);
			livesDeadUI[i].setPosition(65, 50);
		}
	}
}
/*void Frog::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(frogSprite);
}*/

// Methods that make the frog move in its available directions //
void Frog::MoveUp()
{	// If the sprite is below the bases and between any of the bases widths:
	if ((frogSprite.getPosition().y >= 180) || ((frogSprite.getPosition().x >= 160) && (frogSprite.getPosition().x <= 240)) || ((frogSprite.getPosition().x >= 360) && (frogSprite.getPosition().x <= 440)) || ((frogSprite.getPosition().x >= 560) && (frogSprite.getPosition().x <= 640)) || ((frogSprite.getPosition().x >= 760) && (frogSprite.getPosition().x <= 840)))
	{

		if (frogSprite.getRotation() != 0) // If the sprite is not already facing the right way, rotate it to face the way it is moving.
		{
			frogSprite.setRotation(0);
		}
		m_bRunAnimation = true; // Run the movement animation.
		frogSprite.setPosition(frogSprite.getPosition() + sf::Vector2f(0, -m_iOffsetY)); // Move the frog up by the y offset.

	}
}
void Frog::MoveDown()
{
	if (frogSprite.getPosition().y <= (GetWindowH() - 25)) // While the frog sprite is above the bottom of the screen it can move down.
	{
		if (frogSprite.getRotation() != 180)
		{
			frogSprite.setRotation(180);
		}
		m_bRunAnimation = true;
		frogSprite.setPosition(frogSprite.getPosition() + sf::Vector2f(0, m_iOffsetY)); // Move the frog down by the y offset.
	}
}
void Frog::MoveLeft()
{
	if (frogSprite.getPosition().x >= 20)  // While the frog sprite is to the right of the left border of the window it may move left.
	{
		if (frogSprite.getRotation() != 270)
		{
			frogSprite.setRotation(270);
		}
		m_bRunAnimation = true;
		frogSprite.setPosition(frogSprite.getPosition() + sf::Vector2f(-m_iOffsetX, 0)); // Move the frog left by the x offset.
	}
}
void Frog::MoveRight()
{
	if (frogSprite.getPosition().x <= (GetWindowW() - 20)) // While the frog sprite is to the right of the right border of the window it may move right.
	{
		if (frogSprite.getRotation() != 90)
		{
			frogSprite.setRotation(90);
		}
		m_bRunAnimation = true;
		frogSprite.setPosition(frogSprite.getPosition() + sf::Vector2f(m_iOffsetX, 0)); // Move the frog right by the x offset.
		//frogSprite.setRotation(frogSprite.getRotation() + 20.f);
	}
}

void Frog::ResetFrogPos() // Move the frog back to its starting position in the window.
{
	frogSprite.setPosition(startPosition);
	frogSprite.setRotation(0); // Reset the frog to face up.
}

// Setters //
void Frog::SetValues(bool leftDown, bool rightDown, bool upDown, bool downDown)
{
	m_bLeftKeyDown = leftDown;
	m_bRightKeyDown = rightDown;
	m_bUpKeyDown = upDown;
	m_bDownKeyDown = downDown;
}
void Frog::SetLives(int lives)
{
	m_iLives = lives;
}
// Used to display/hide the dead lives sprites: 
void Frog::SetDeadUIVisible()
{
	livesDeadUI[GetLives()].setColor(sf::Color(255, 255, 255, 255));

}
void Frog::ResetDeadUIVisible()
{
	for (int i = 0; i < 3; i++)
	{
		livesDeadUI[i].setColor(sf::Color(255, 255, 255, 0));
	}

}
// Getters //
bool Frog::GetUp()
{
	return m_bUpKeyDown;
}
bool Frog::GetDown()
{
	return m_bDownKeyDown;
}
bool Frog::GetLeft()
{
	return m_bLeftKeyDown;
}
bool Frog::GetRight()
{
	return m_bRightKeyDown;
}
int Frog::GetLives()
{
	return m_iLives;
}
sf::Vector2f Frog::GetPositionSprite()
{
	return frogSprite.getPosition();
}

void Frog::FrogAnimation() // Runs through the spritesheet to animate the frog sprite when it moves:
{

	if (FrameClock.getElapsedTime().asSeconds() > (1.f / 15.f)) // Every 1/15th of a second:
	{
		if (m_bRunAnimation)  // If the animation bool is true:
		{
			// Check for the place in the spritesheet that is to be shown next and set it to the sprite's texture:
			if (defaultFrog.left <= 2)
			{
				defaultFrog.left = 48;
				m_bRunAnimation = false;
			}
			else
			{
				defaultFrog.left -= 23;
			}
			frogSprite.setTextureRect(defaultFrog); // Reset the texture to the stationary one at the end.

		}
		FrameClock.restart();
	}

}

// Destructor //
Frog::~Frog()
{
}

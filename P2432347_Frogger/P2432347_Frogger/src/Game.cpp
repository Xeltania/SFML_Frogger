#include "Game.h"

using namespace std;

// Constructor //
Game::Game()
{

	// Instantiation of private members // 
	m_bGameActive = true; // The game is default as active as the player has not finished/lost on start.
	m_iFrameLimit = 1000;
	// Set the current resolution to the width and height of the monitor.
	m_iScreenResW = sf::VideoMode::getDesktopMode().width;
	m_iScreenResH = sf::VideoMode::getDesktopMode().height;
	// Set the window width and height to relative sizes of the resolution. Values are inverted so the window is portrait.
	m_iWindowW = m_iScreenResH / 1.2;
	m_iWindowH = m_iScreenResW / 2;
	// Set the position of the window relative to the screen resolution ( Divided to give a central position).
	m_vWindowPos = sf::Vector2i(m_iScreenResW / 5, m_iScreenResH / 100);

	// Instantiation of UI members //
	// Timer Bar //
	m_TimerBarSize.x = 120;
	m_TimerBarSize.y = 20;
	sf::Vector2f vTimerOrigin(0, m_TimerBarSize.x / 2);
	uiTimerBar.setFillColor(sf::Color(255, 0, 0, 255));
	uiTimerBar.setSize(sf::Vector2f(m_TimerBarSize));
	uiTimerBar.setRotation(180); // Flips the bar so it decreases left to right.
	uiTimerBar.setOrigin(vTimerOrigin);
	uiTimerBar.setPosition((GetWindowW() - 50), (GetWindowH() - 50));

	// Timer Text //
	uiFont.loadFromFile("..\\Assets\\Fonts\\GameFont.ttf");
	uiTimerText.setFont(uiFont);
	uiTimerText.setCharacterSize(40);
	uiTimerText.setFillColor(sf::Color(0, 0, 0, 255));
	//uiTimerText.setString("Time: " + to_string(iTimerSize));
	uiTimerText.setPosition((GetWindowW() - 125), (GetWindowH() - 50));

	// Score Text //
	uiScore.setFont(uiFont);
	uiScore.setCharacterSize(50);
	uiScore.setFillColor(sf::Color(255, 255, 100, 255));

	// Lives UI //
	uiLives.setFont(uiFont);
	uiLives.setCharacterSize(35);
	uiLives.setFillColor(sf::Color(0, 0, 0, 255));
	uiLives.setString("Lives: ");
	uiLives.setPosition((1 / GetWindowW()) + 50, (1 / GetWindowH() + 5));


	// Instantiation for game over UI //

	// Text that says the game is over.
	uiGameOverText.setFont(uiFont);
	uiGameOverText.setCharacterSize(uiScore.getCharacterSize()); // Use the same size as the other UI text that will be displayed.
	uiGameOverText.setFillColor(sf::Color::Red);
	uiGameOverText.setString("G A M E   O V E R");
	uiGameOverText.setPosition(sf::Vector2f(GetWindowW() / 3, 1 / GetWindowH()));

	// Text that tells the player the button to retry.
	uiRetryText.setFont(uiFont);
	uiRetryText.setCharacterSize(uiScore.getCharacterSize());
	uiRetryText.setFillColor(sf::Color::White);
	uiRetryText.setString("To retry, press the  'R' button");
	uiRetryText.setPosition(sf::Vector2f(GetWindowW() / 10, GetWindowH() / 2));

	// Text that tells the player an alternative exit method.
	uiExitText.setFont(uiFont);
	uiExitText.setCharacterSize(uiScore.getCharacterSize());
	uiExitText.setFillColor(sf::Color::White);
	uiExitText.setString("To exit, press escape or close the window using the 'x' \n in the top right corner");
	uiExitText.setPosition(sf::Vector2f(GetWindowW() / 10, GetWindowH() - 200));

	// Text that tells the player whether they won or lost.
	uiEndStatusText.setFont(uiFont);
	uiEndStatusText.setCharacterSize(uiScore.getCharacterSize());
	uiEndStatusText.setFillColor(sf::Color::White);
	uiEndStatusText.setPosition(sf::Vector2f(GetWindowW() / 3, GetWindowH() / 6));

	// Instantiation of the background //
		// Water //
	waterColour.r = 0; waterColour.g = 0; waterColour.b = 255; waterColour.a = 255; // Initialise the red green blue values and the alpha of the water colour.
	bgWaterRect.setFillColor(waterColour);
	bgWaterRect.setPosition(0, 0);
	bgWaterRect.setSize(sf::Vector2f(1000, 400));
	// Road //
	roadColour.r = 50; roadColour.g = 50; roadColour.b = 50; roadColour.a = 255;
	bgRoadRect.setFillColor(roadColour);
	bgRoadRect.setPosition(0, 500);
	bgRoadRect.setSize(sf::Vector2f(1000, 400));
	// Safe Zone Background //
	safeZoneColour.r = 9; safeZoneColour.g = 153; safeZoneColour.b = 37; safeZoneColour.a = 255;
	bgSafeZoneRect.setFillColor(safeZoneColour);
	bgSafeZoneRect.setPosition(0, 0);
	bgSafeZoneRect.setSize(sf::Vector2f(1000, 100));

	// Lilypads and base water //
	lilypadTexPath = "..\\Assets\\Textures\\LilypadTex.png";
	lilypadTexture.loadFromFile(lilypadTexPath);
	lilypadSize.x = 80;
	lilypadSize.y = 80;
	for (int i = 0; i < 4; i++)  // Initialise the shared values for each of the lilypads and the water under them:
	{
		lilypadsWater[i].setFillColor(waterColour);
		lilypadsWater[i].setSize(lilypadSize);
		lilypadsWater[i].setOrigin(lilypadSize.x / 2, lilypadSize.y / 2);

		lilypadsUI[i].setTexture(&lilypadTexture);
		lilypadsUI[i].setSize(lilypadSize);
		lilypadsUI[i].setOrigin(lilypadSize.x / 2, lilypadSize.y / 2);
		lilypadsUI[i].setFillColor(sf::Color(255, 255, 255, 0)); // Initialise the lilypad sprite to be hidden until intersected with.
		//lilypadsUI[i].getFillColor().a;

	}
	// Initialise the positions //
	lilypadPos1.x = 200;
	lilypadPos1.y = 60;
	lilypadPos2.x = 400;
	lilypadPos2.y = lilypadPos1.y;
	lilypadPos3.x = 600;
	lilypadPos3.y = lilypadPos2.y;
	lilypadPos4.x = 800;
	lilypadPos4.y = lilypadPos3.y;
	// Set the water and lilypad to the correct position //
	lilypadsUI[0].setPosition(lilypadPos1);
	lilypadsUI[1].setPosition(lilypadPos2);
	lilypadsUI[2].setPosition(lilypadPos3);
	lilypadsUI[3].setPosition(lilypadPos4);
	lilypadsWater[0].setPosition(lilypadPos1);
	lilypadsWater[1].setPosition(lilypadPos2);
	lilypadsWater[2].setPosition(lilypadPos3);
	lilypadsWater[3].setPosition(lilypadPos4);



	// Middle Path //
	pathColour.r = 178; pathColour.g = 130; pathColour.b = 204; pathColour.a = 255;
	bgPathRect.setFillColor(pathColour);
	bgPathRect.setPosition(0, 400);
	bgPathRect.setSize(sf::Vector2f(1000, 100));

}
// Setters //
void Game::SetGameActive(bool gameActive)
{
	m_bGameActive = gameActive;
}
void Game::SetWindowPos(int xPosition, int yPosition)
{
	m_vWindowPos.x = xPosition;
	m_vWindowPos.y = yPosition;
}
void Game::SetScore(int score)
{
	score += m_iScore;
}
void Game::SetEndStatus()
{
	if (lilypadsVisited[0] && lilypadsVisited[1] && lilypadsVisited[2] && lilypadsVisited[3]) // If all of the lilypads were visited:
	{
		m_bVisited = true; // The player won
	}
	else
	{
		m_bVisited = false; // The player lost
	}
	if (m_bVisited)
	{
		uiEndStatusText.setString("You Win !");
	}
	else
	{
		uiEndStatusText.setString("You Lose");
	}
}


// Getters //
int Game::GetWindowW() // Get the width of the game window.
{
	return m_iWindowW;
}
int Game::GetWindowH() // Get the height of the game window.
{
	return m_iWindowH;
}
int Game::GetWindowPosX()
{
	return m_vWindowPos.x;
}
int Game::GetWindowPosY()
{
	return m_vWindowPos.y;
}
int Game::GetFrameRate()
{
	return m_iFrameLimit;
}
/*int Game::GetScore()
{
	return m_iScore;
}*/
bool Game::GetGameActive() // Used to check if the game is still active.
{
	return m_bGameActive;
}
float Game::GetClockTime() // Used to get the elapsed time in seconds.
{
	return m_GameClock.getElapsedTime().asSeconds();
}
sf::Time Game::GetTimerTime()
{
	return m_GameTimerMax;
}

void Game::UpdateTimer()
{
	float fDuration = m_GameTimerClock.getElapsedTime().asSeconds(); // Get the duration the timer has been ticking for in seconds.
	int iTimerSize = uiTimerBar.getSize().x / 4;
	if (fDuration > 1) // For every second passed:
	{
		uiTimerBar.setSize(sf::Vector2f(uiTimerBar.getSize().x - 4, 20)); // Decrease the size of the bar.
		m_GameTimerClock.restart();
	}
	uiTimerText.setString("Time: " + to_string(iTimerSize)); // Display the new remaining time.

}

void Game::UpdateScore()
{
	uiScore.setString("Score: " + to_string(m_iScore)); // Display the current score.
}
void Game::ResetClock() // Resets the clock to count down again.
{
	m_GameClock.restart();
	uiTimerBar.setSize(m_TimerBarSize);
}
void Game::ScoreTextPos()
{
	if (m_bGameActive) // If the game is active, put the score text out of the way of the game interface.
	{
		uiScore.setOutlineColor(sf::Color::Black);
		uiScore.setOutlineThickness(2);
		uiScore.setPosition(GetWindowW() / 8, GetWindowH() - 50);
	}
	else // Otherwise move it to the centre so it stands out.
	{
		uiScore.setPosition(GetWindowW() / 3, GetWindowH() / 8);
	}

}
void Game::ResetLilypads()
{
	for (int n = 0; n < 4; n++)
	{
		lilypadsVisited[n] = false; // Make the lilypads unvisited again.
		lilypadsUI[n].setFillColor(sf::Color(0, 0, 0, 0)); // Hide the lilypad sprite again.
	}
}

// Destructor //
Game::~Game()
{

}

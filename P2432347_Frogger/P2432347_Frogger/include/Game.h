#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Game // Used to set up the general base of the game: window, position on the screen, game over state.
{
public:
	Game(); // Constructor.
	~Game(); // Destructor.



	// Variables used to draw the background //
	sf::RectangleShape bgWaterRect, bgRoadRect, bgSafeZoneRect, bgPathRect;
	sf::Color waterColour, roadColour, safeZoneColour, pathColour;


	// Variables used to draw the Lilypad bases //
	sf::RectangleShape bgLilypad1, bgLilypad2, bgLilypad3, bgLilypad4;
	sf::RectangleShape bglilypadWater1, bglilypadWater2, bglilypadWater3, bglilypadWater4;;
	// Arrays of lilypad shapes //
	bool lilypadsVisited[4] = { false, false, false, false };
	bool m_bVisited; // Used to reference whether all of the lilypads were visited.
	sf::RectangleShape lilypadsUI[4] = { bgLilypad1, bgLilypad2, bgLilypad3, bgLilypad4 };
	sf::RectangleShape lilypadsWater[4] = { bglilypadWater1, bglilypadWater2, bglilypadWater3, bglilypadWater4 };
	// Lilypad Textures //
	sf::Texture lilypadTexture; // The texture used when the lilypad is reached.
	string lilypadTexPath; // The path to the lilypad image.
		// Vectors of lilypad base scales and positions //
	sf::Vector2f lilypadSize, lilypadScale; // Used to size and scale the lilypad water and lilypad.
	sf::Vector2f lilypadPos1, lilypadPos2, lilypadPos3, lilypadPos4; // Used to set the position for each lilypad and its water.


	// UI Variables //
	sf::RectangleShape uiTimerBar;
	sf::Font uiFont;
	sf::Text uiTimerText, uiScore, uiLives;
	sf::Text uiRetryText, uiExitText, uiGameOverText, uiEndStatusText;
	int m_iScore = 0;

	// Setters //
	void SetGameActive(bool gameActive); // Used to update the value where the game becomes over.
	void SetWindowPos(int xPosition, int yPosition); // Sets the position of the game window relative to the user's monitor.
	void SetScore(int score);
	void SetEndStatus(); // Sets the end status text.

	// Getters //
	int GetWindowW();
	int GetWindowH();
	int GetWindowPosX();
	int GetWindowPosY();
	int GetFrameRate();
	//int GetScore();
	float GetClockTime();
	sf::Time GetTimerTime();
	bool GetGameActive();

	// Other Methods //
	void UpdateTimer();
	void UpdateScore();
	void ResetClock();
	void ScoreTextPos();
	void ResetLilypads();


private:
	sf::Clock m_GameClock; // Used to measure the duration that the game has been active. 
	sf::Clock m_GameTimerClock; // This is how long the player has to reach the lilypad.
	sf::Time m_GameTimerMax = sf::seconds(30);
	bool m_bGameActive; // Defines whether the game is not over.
	unsigned int m_iWindowW, m_iWindowH; // Used to define the width and height of the game window.
	unsigned int m_iScreenResW, m_iScreenResH; // Used to fetch the screen resolution of the monitor being used.
	unsigned int m_iFrameLimit; // Defines the maximum frame rate of the game (per second).
	sf::Vector2i m_vWindowPos; // Vector to define the postion of the window in relation to the screen.
	sf::Vector2f m_TimerBarSize;

};


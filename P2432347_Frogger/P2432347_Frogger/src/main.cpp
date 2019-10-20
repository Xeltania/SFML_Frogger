#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Audio.h"
#include "Frog.h"
#include "Objects.h"

using namespace std;

int main()
{

	Game GameUI; // The object reference of the Game class (used to define the RenderWindow).
	Audio Sounds; // Object reference to the Audio class (used to play music and sound effects).
	Frog Frog; // Object reference to the Frog class, used to create the player in the window.
	Objects GameObjects; // Object reference to the Objects class, creates the cars and logs.
	bool bStopClock = false; // Initialisation of the timer handler. This prevents time from counting down while the game is not active.
	int iLilypadChecker = 0; // Used to check whether all of the lilypads have been sat on.

	// Set up the game window //
	sf::RenderWindow gameScreen(sf::VideoMode(GameUI.GetWindowW(), GameUI.GetWindowH()), "Frogger");
	gameScreen.setPosition(sf::Vector2i(GameUI.GetWindowPosX(), GameUI.GetWindowPosY()));
	gameScreen.setFramerateLimit(GameUI.GetFrameRate());

	// Score calculations for increasing by a relative amount //
	int iCalculatedScore; // The score is the basal value multiplied by how long it took to reach the lilypad.
	int iScoreValue; // The basal value used to create the score from.
	float fTimeTaken; // The time taken to reach a lilypad.
	
	Sounds.PlayIntroMusic(); // Plays the intro music when the window opens.
	while (gameScreen.isOpen())
	{
		if (Sounds.introMusic.getStatus() == sf::Music::Stopped && Sounds.bgMusic.getStatus() == sf::Music::Stopped) // When the intro music ends, continually play the end music.
		{
			Sounds.PlayBGMusic();
		}
		sf::Event event;
		while (gameScreen.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // If the window gets closed:
			{
				gameScreen.close();
			}
			if (event.type == sf::Event::KeyPressed)  // If the user presses a key: check it against the valid inputs
			{

				// Movement Keys //
				if (event.key.code == sf::Keyboard::Up && !(Frog.GetUp()))
				{

					Frog.MoveUp();
					Sounds.PlayHopSound();
					Frog.SetValues(false, false, true, false);
				}
				if (event.key.code == sf::Keyboard::Down && !(Frog.GetDown()))
				{

					Frog.MoveDown();
					Sounds.PlayHopSound();
					Frog.SetValues(false, false, false, true);
				}
				if (event.key.code == sf::Keyboard::Left && !(Frog.GetLeft()))
				{

					Frog.MoveLeft();
					Sounds.PlayHopSound();
					Frog.SetValues(true, false, false, false);
				}
				if (event.key.code == sf::Keyboard::Right && !(Frog.GetRight()))
				{

					Frog.MoveRight();
					Sounds.PlayHopSound();
					Frog.SetValues(false, true, false, false);
				}

				// Restart Or Close the Game when it is over //
				if (event.key.code == sf::Keyboard::R && !GameUI.GetGameActive())
				{
					// Reset game values //
					GameUI.ResetLilypads();
					GameUI.SetScore(GameUI.m_iScore -= GameUI.m_iScore);
					Frog.ResetDeadUIVisible();
					Frog.SetLives(3);
					Frog.ResetFrogPos();
					GameUI.SetGameActive(true);
					GameUI.ResetClock();
					bStopClock = false;
				}
				if (event.key.code == sf::Keyboard::Escape && !GameUI.GetGameActive()) // Used as an alternative to quit the game when it is over.
				{
					gameScreen.close();
				}
			}
			// When the player stops pressing the movement keys: reset the values //
			if (event.type == sf::Event::KeyReleased)
			{
				Frog.SetValues(false, false, false, false);
			}

		}
		// Score Handling //
		GameUI.UpdateScore();
		GameUI.ScoreTextPos(); // Defined outside the game loop so that it may change when the game is no longer active.

		// Controls the flow of the game. While the user has not lost: //
		if (GameUI.GetGameActive())
		{

			Frog.FrogAnimation(); // Animate the frog.
			// Timer Handling //
			if (GameUI.GetClockTime() > GameUI.GetTimerTime().asSeconds()) // If the timer runs out: 
			{
				// Remove a life, reset the frog position and the timer:
				Frog.SetLives(Frog.GetLives() - 1);
				Frog.SetDeadUIVisible();
				Frog.ResetFrogPos();
				GameUI.ResetClock();
			}
			if (!bStopClock) // While the clock is not set to stop, upadte the timer.
			{
				GameUI.UpdateTimer();
			}

			// Move Objects //
			GameObjects.MoveObjects(5, 1.5);


			// Checking for Frog intersection with logs //
			int intersectingLog = -1;
			if ((Frog.GetPositionSprite().y < GameUI.bgWaterRect.getSize().y) && (Frog.GetPositionSprite().y > GameUI.bgSafeZoneRect.getSize().y)) // If the Frog is in the water bounds.
			{
				for (int n = 0; n < 9; n++)
				{
					if (Frog.frogSprite.getGlobalBounds().intersects(GameObjects.m_aLogArr[n].getGlobalBounds())) // If the frog sprite intersects a log:
					{
						intersectingLog = n; // Set the value to the log being intersected.
						Frog.frogSprite.setPosition(GameObjects.m_aLogArr[n].getPosition()); // Make the frog move with the log by setting its position to the origin of the log. (cannot move sideways when on a log)
					}

				}
				if (intersectingLog == -1) // If no log is being intersected with and the frog is in the water bounds:
				{
					Frog.SetLives(Frog.GetLives() - 1); // Remove a life
					Frog.SetDeadUIVisible();
					Frog.ResetFrogPos(); // Send the frog sprite back to its start position.
					GameUI.ResetClock();
				}

			}

			// Check Frog intersecting Cars //
			for (int n = 0; n < 9; n++)
			{
				if (Frog.frogSprite.getGlobalBounds().intersects(GameObjects.m_aCarArr[n].getGlobalBounds())) // If the frog sprite intersects with a car: 
				{
					// Remove a life and reset the frog position //
					Frog.SetLives(Frog.GetLives() - 1);
					Frog.SetDeadUIVisible();
					Frog.ResetFrogPos();
					GameUI.ResetClock();
				}
			}

			if (Frog.GetLives() == 0) // If the player loses all of their lives :
			{
				GameUI.SetEndStatus();
				GameUI.SetGameActive(false); // Set the game to over.
				bStopClock = true; // Stop the clock continuing.
			}

			// Check Frog has reached a lilypad //
			for (int n = 0; n < 4; n++)
			{
				if ((Frog.frogSprite.getGlobalBounds().intersects(GameUI.lilypadsUI[n].getGlobalBounds())) && !(GameUI.lilypadsVisited[n])) // If the frog intersects and has not before: 
				{
					Sounds.PlayLilypadSound(); // Play the sound for entering a lilypad.
					iLilypadChecker++; // Increment the checker to say that anoter lilypad has been visited.
					GameUI.lilypadsVisited[n] = true; // Set the lilypad to visited in the array.
					// Calculate the score to add : 
					iScoreValue = 50;
					fTimeTaken = GameUI.GetClockTime();
					iCalculatedScore = iScoreValue * fTimeTaken;
					//int iCurrentScore = GameUI.GetScore();
					GameUI.SetScore(GameUI.m_iScore += iCalculatedScore);
					GameUI.UpdateScore();
					// Set the lilypad sprite to be visible and update the bool so it may not be interacted with again //
					GameUI.lilypadsUI[n].setFillColor(sf::Color(255, 255, 255, 255));
					Frog.ResetFrogPos();
					GameUI.ResetClock();

				}
			}
			// Check whether the game is won //
			if (iLilypadChecker == 4) // If all of the lilypads have been sat on:
			{
				GameUI.SetEndStatus(); // Set the status as the game is won.
				GameUI.SetGameActive(false); // The game is no longer active as it has been won.
				bStopClock = true;
				iLilypadChecker = 0; // Reset the checker.
			}

			// The background of the screen when it clears (set to white to be able to see non-alpha sprite borders).
			gameScreen.clear(sf::Color(255, 255, 255, 255));

			// Drawing: (The last drawn sprite will appear on top) //

			// Background //
			gameScreen.draw(GameUI.bgWaterRect);
			gameScreen.draw(GameUI.bgRoadRect);
			gameScreen.draw(GameUI.bgSafeZoneRect);
			gameScreen.draw(GameUI.bgPathRect);
			for (int i = 0; i < 4; i++)
			{
				gameScreen.draw(GameUI.lilypadsWater[i]);
				gameScreen.draw(GameUI.lilypadsUI[i]);
			}

			// UI //
			gameScreen.draw(GameUI.uiTimerText);
			gameScreen.draw(GameUI.uiTimerBar);
			gameScreen.draw(GameUI.uiScore);
			gameScreen.draw(GameUI.uiLives);

			// Objects //
			for (int i = 0; i < 9; i++)
			{

				gameScreen.draw(GameObjects.m_aCarArr[i]);
				gameScreen.draw(GameObjects.m_aLogArr[i]);
			}

			// Frog and Lives sprites //
			gameScreen.draw(Frog.frogSprite);
			for (int i = 0; i < 3; i++)
			{
				gameScreen.draw(Frog.livesDeadUI[i]);
			}

			for (int i = 0; i < Frog.GetLives(); i++)
			{
				gameScreen.draw(Frog.livesUI[i]);
			}

		}
		// The last thing to be drawn: Only draws when the game is over //
		if (!GameUI.GetGameActive())
		{
			Sounds.bgMusic.stop(); // Stop the game music.
			gameScreen.clear(sf::Color(0, 0, 0, 255)); // Hide the game screen by clearing to black.
			gameScreen.draw(GameUI.uiScore);
			gameScreen.draw(GameUI.uiGameOverText);
			gameScreen.draw(GameUI.uiEndStatusText);
			gameScreen.draw(GameUI.uiRetryText);
			gameScreen.draw(GameUI.uiExitText);

		}

		gameScreen.display();

	}
	return 0;
}
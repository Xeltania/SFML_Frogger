#pragma once
#include "Game.h"
#include <SFML/Audio.hpp>
class Audio : public Game
{
public:
	Audio();
	~Audio();

	// Public music attributes //
	sf::Music introMusic; // Loads the intro music.
	sf::Music bgMusic; // Loads the background music.

	// Methods for playing audio //
	void PlayLilypadSound();
	void PlayHopSound();
	void PlayIntroMusic();
	void PlayBGMusic();

private:
	sf::SoundBuffer audioBuffer; // Buffer for the background music.
	sf::Sound audioSound; // Sound effect.
	string introMusicPath, bgMusicPath; // used to locate the audio files.
};


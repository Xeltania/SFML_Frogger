#include "Audio.h"

using namespace std;

Audio::Audio()
{
	// Instantiate the path for the game musics //
	introMusicPath = "..\\Assets\\Audio\\Frogger_Intro_Song.wav";
	bgMusicPath = "..\\Assets\\Audio\\Frogger_Loop_Song.wav";
	bgMusic.setLoop(true); // Set the background music to be looped.
	// Locate the music using the paths //
	introMusic.openFromFile(introMusicPath);
	bgMusic.openFromFile(bgMusicPath);

}

// Sound playing methods //
void Audio::PlayLilypadSound() // Plays the sound for intersecting a lilypad by loading it into the buffer.
{
	audioBuffer.loadFromFile("..\\Assets\\Audio\\Frogger_Lilypad.wav");
	audioSound.setBuffer(audioBuffer);
	audioSound.play();
}
void Audio::PlayHopSound()// Plays the sound for moving by loading it into the buffer.
{
	audioBuffer.loadFromFile("..\\Assets\\Audio\\Frogger_Hop.wav");
	audioSound.setBuffer(audioBuffer);
	audioSound.play();
}
void Audio::PlayIntroMusic() // Plays the intro song.
{
	introMusic.play();
}
void Audio::PlayBGMusic() // Plays the background music.
{
	bgMusic.play();
}

Audio::~Audio()
{
}

/// <summary>
/// author Kacie Franklin
/// date July 07 2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include<string>

enum class ObjectPressed
{
	None,
	PlayButton,
	QuitButton,
	SettingsButton,
	SelectButton,
};

enum class SelectedSerum
{
	None,
	GreenSerum,
	YellowSerum,
	BlueSerum,
	DarkBlueSerum,
	RedBlood,
	BlueBlood,
	BlackBlood,
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();
	void fadeBlackTransition();
	void selectSerums();
	void checkSerumSelection();

	Player myplayer;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Font m_romanAntiqueFont;
	sf::Text m_message; // text used for message on screen

	bool m_exitGame; // control exiting game

	//gamemode
	int gamemode;
	int mainMenu = 1;
	int serumSelect = 2;
	int mixingSerums = 3;
	int cutHand = 4;
	int shakeVial = 5;
	int useSyringe = 6;

	//Background sprites & textures
	sf::Texture m_labBackgroundTexture; // texture for lab bg
	sf::Sprite m_labBackgroundSprite; // sprite for lab bg
	sf::Texture m_labBackgroundShadeTexture;//texture for lab bg shade
	sf::Sprite m_labBackgroundShadeSprite; //sprite for bg lab shade 

	//frame sprite and texture
	sf::Sprite m_frameSprite;
	sf::Texture m_frameTexture;

	//Potions sprites & textures
	sf::Texture m_serumGreenTexture;
	sf::Sprite m_serumGreenSprite;
	sf::Texture m_serumYellowTexture;
	sf::Sprite m_serumYellowSprite;
	sf::Texture m_serumDarkBlueTexture;
	sf::Sprite m_serumDarkBlueSprite;
	sf::Texture m_serumBlueTexture;
	sf::Sprite m_serumBlueSprite;
	sf::Texture m_redBloodTexture;
	sf::Sprite m_redBloodSprite;
	sf::Texture m_blueBloodTexture;
	sf::Sprite m_blueBloodSprite;
	sf::Texture m_blackBloodTexture;
	sf::Sprite m_blackBloodSprite;
	sf::Sprite m_vialSprite;
	sf::Texture m_vialTexture;

	//button sprites and textures
	sf::Sprite m_buttonSprite;
	sf::Texture m_buttonTexture;
	sf::Sprite m_continueSprite;
	sf::Texture m_continueTexture;
	sf::Sprite m_selectSprite;
	sf::Texture m_selectTexture;

	//mouse controls
	sf::Vector2f m_mouseEnd;
	bool m_mouseHeld = false; //bool to check if the mouse if held down
	ObjectPressed clicked = ObjectPressed::None;

	//Animations
	int m_transitionFrame = {-1};
	const int TRANSITION_FRAMES = 13;
	float m_transitionFrameCounter = 0.0f;
	float m_transitionFrameIncrement = 0.3f;
	sf::Sprite m_fadeBlackSprite;
	sf::Texture m_fadeBlackTexture;
	bool m_transitioning = false;

	//arrary
	bool serumSelected = false;
	SelectedSerum selected = SelectedSerum::None;
	int serum = 0;


};

#endif // !GAME_HPP


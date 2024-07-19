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
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	bool m_exitGame; // control exiting game

	//Background sprites & textures
	sf::Texture m_labBackgroundTexture; // texture for lab bg
	sf::Sprite m_labBackgroundSprite; // sprite for lab bg
	sf::Texture m_labBackgroundShadeTexture;//texture for lab bg shade
	sf::Sprite m_labBackgroundShadeSprite; //sprite for bg lab shade 

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

};

#endif // !GAME_HPP


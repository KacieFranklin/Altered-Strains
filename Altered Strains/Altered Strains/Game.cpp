/// <summary>
/// @author Kacie Franklin
/// @date July 07 2024
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	//sf::Style::Fullscreen;
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_labBackgroundSprite);
	m_window.draw(m_blackBloodSprite);
	m_window.draw(m_blueBloodSprite);
	m_window.draw(m_redBloodSprite);
	m_window.draw(m_serumBlueSprite);
	m_window.draw(m_serumDarkBlueSprite);
	m_window.draw(m_serumGreenSprite);
	m_window.draw(m_serumYellowSprite);
	m_window.draw(m_labBackgroundShadeSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the background
/// </summary>
void Game::setupSprite()
{
	if (!m_labBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\AS Lab BG.png"))//load texture
	{
		std::cout << "problem loading AS Lab BG.png" << std::endl;
	}
	m_labBackgroundSprite.setTexture(m_labBackgroundTexture);
	m_labBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	//m_labBackgroundSprite.setPosition(300.0f, 180.0f);
	m_labBackgroundSprite.scale(4.0f, 4.2f);//making it fit the window
	m_labBackgroundTexture.setSmooth(true);

	if (!m_labBackgroundShadeTexture.loadFromFile("ASSETS\\IMAGES\\AS Lab BG_Multi.png"))//load texture
	{
		std::cout << "problem loading AS Lab BG_Multi.png";
	}
	m_labBackgroundShadeSprite.setTexture(m_labBackgroundShadeTexture);
	m_labBackgroundShadeSprite.scale(4.0f, 4.2f);//making it fir the window
	m_labBackgroundShadeSprite.setColor(sf::Color::Black);
	//m_labBackgroundShadeSprite.setPosition(300.0f, 180.0f);
	m_labBackgroundShadeTexture.setSmooth(true);

	//potion sprites and load textures
	if (!m_blackBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS Black Serum.png"))//load texture
	{
		std::cout << "problem loading AS Black Serum.png";
	}
	m_blackBloodSprite.setTexture(m_blackBloodTexture);
	m_blackBloodSprite.scale(4.0f, 4.0f);
	m_blackBloodSprite.setPosition(282, 78);

	if (!m_blueBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS DarkBlue Blood.png"))//load texture
	{
		std::cout << "problem loading AS DarkBlue Blood.png";
	}
	m_blueBloodSprite.setTexture(m_blueBloodTexture);
	m_blueBloodSprite.scale(4.0f, 4.0f);
	m_blueBloodSprite.setPosition(515, 78);

	if (!m_redBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS Red Blood.png"))//load texture
	{
		std::cout << "problem loading AS Red Blood.png";
	}
	m_redBloodSprite.setTexture(m_redBloodTexture);
	m_redBloodSprite.scale(4.0f, 4.0f);
	m_redBloodSprite.setPosition(400, 78);

	if (!m_serumDarkBlueTexture.loadFromFile("ASSETS\\IMAGES\\AS DarkBlue Serum.png"))//load texture
	{
		std::cout << "problem loading AS DarkBlue Serum.png";
	}
	m_serumDarkBlueSprite.setTexture(m_serumDarkBlueTexture);
	m_serumDarkBlueSprite.scale(4.0f, 4.0f);
	m_serumDarkBlueSprite.setPosition(50, 305);

	if (!m_serumBlueTexture.loadFromFile("ASSETS\\IMAGES\\AS Blue Serum.png"))//load texture
	{
		std::cout << "problem loading AS Blue Serum.png";
	}
	m_serumBlueSprite.setTexture(m_serumBlueTexture);
	m_serumBlueSprite.scale(4.0f, 4.0f);
	m_serumBlueSprite.setPosition(405, 385);

	if (!m_serumYellowTexture.loadFromFile("ASSETS\\IMAGES\\AS Yellow Serum.png"))//load texture
	{
		std::cout << "problem loading AS Yellow Serum.png";
	}
	m_serumYellowSprite.setTexture(m_serumYellowTexture);
	m_serumYellowSprite.scale(4.0f, 4.0f);
	m_serumYellowSprite.setPosition(210, 320);

	if (!m_serumGreenTexture.loadFromFile("ASSETS\\IMAGES\\AS Green Serum.png"))//load texture
	{
		std::cout << "problem loading AS Green Serum.png";
	}
	m_serumGreenSprite.setTexture(m_serumGreenTexture);
	m_serumGreenSprite.scale(4.0f, 4.0f);
	m_serumGreenSprite.setPosition(50, 25);
}

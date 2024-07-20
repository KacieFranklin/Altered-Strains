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
	m_exitGame{ false } //when true game will exit
{
	
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	gamemode = mainMenu;
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
		//gamemode = mainMenu;
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
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed a mouse button
		{
			processMouseDown(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type) //user released mouse button 
		{
			processMouseUp(newEvent);
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

void Game::processMouseDown(sf::Event t_event)
{
	m_mouseHeld = true;
	m_mouseEnd.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseEnd.y = static_cast<float>(t_event.mouseButton.y);
	if (m_buttonSprite.getGlobalBounds().contains(m_mouseEnd))//checks if the mouse is in the same position as the play button
	{

		clicked = ObjectPressed::PlayButton;
	}
	else if (m_continueSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		clicked = ObjectPressed::SelectButton;
	}

	if (m_serumGreenSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::GreenSerum;
	}
	else if (m_serumYellowSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::YellowSerum;
	}
	else if (m_serumBlueSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::BlueSerum;
	}
	else if (m_serumDarkBlueSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::DarkBlueSerum;
	}
	else if (m_redBloodSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::RedBlood;
	}
	else if (m_blueBloodSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::BlueBlood;
	}
	else if (m_blackBloodSprite.getGlobalBounds().contains(m_mouseEnd))
	{
		selected = SelectedSerum::BlackBlood;
	}
}

void Game::processMouseUp(sf::Event t_event)
{
	m_mouseHeld = false;
	if (clicked == ObjectPressed::PlayButton)
	{
		m_transitioning = true;
		fadeBlackTransition();
		gamemode = serumSelect;
	}
	else if (clicked == ObjectPressed::SelectButton)
	{
		gamemode = mixingSerums;
	}

	if (selected == SelectedSerum::GreenSerum)
	{
		serum = 1;
		selectSerums();
	}
	else if (selected == SelectedSerum::YellowSerum)
	{
		serum = 2;
		selectSerums();
	}
	else if (selected == SelectedSerum::BlueSerum)
	{
		serum = 3;
		selectSerums();
	}
	else if (selected == SelectedSerum::DarkBlueSerum)
	{
		serum = 4;
		selectSerums();
	}
	else if (selected == SelectedSerum::RedBlood)
	{
		serum = 5;
		selectSerums();
	}
	else if (selected == SelectedSerum::BlueBlood)
	{
		serum = 6;
		selectSerums();
	}
	else if(selected == SelectedSerum::BlackBlood)
	{
		serum = 7;
		selectSerums();
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
	m_window.clear(sf::Color::Black);
	if (gamemode == mainMenu)
	{
		m_window.draw(m_message);
		m_window.draw(m_buttonSprite);

	}
	else if (gamemode == serumSelect)
	{
		m_window.draw(m_labBackgroundSprite);
		m_window.draw(m_blackBloodSprite);
		m_window.draw(m_blueBloodSprite);
		m_window.draw(m_redBloodSprite);
		m_window.draw(m_serumBlueSprite);
		m_window.draw(m_serumDarkBlueSprite);
		m_window.draw(m_serumGreenSprite);
		m_window.draw(m_serumYellowSprite);
		m_window.draw(m_labBackgroundShadeSprite);
		m_window.draw(m_frameSprite);
		m_window.draw(m_continueSprite);
		
		if (m_transitioning == true)
		{
			//m_window.draw(m_fadeBlackSprite);
		}
	}
	else if (gamemode == mixingSerums)
	{
		m_window.draw(m_vialSprite);
		m_window.draw(m_frameSprite);
	}
	
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_romanAntiqueFont.loadFromFile("ASSETS\\FONTS\\RomanAntique.ttf"))
	{
		std::cout << "problem loading roman antique font" << std::endl;
	}
	m_message.setFont(m_romanAntiqueFont);
	m_message.setString("Altered Strains");
	m_message.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_message.setPosition(180.0f, 40.0f);
	m_message.setCharacterSize(80U);
	m_message.setOutlineColor(sf::Color::Red);
	m_message.setFillColor(sf::Color::White);
	m_message.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the background, serums, etc
/// </summary>
void Game::setupSprite()
{
	if (!m_fadeBlackTexture.loadFromFile("ASSETS\\IMAGES\\AS TransitionBlack.png"))
	{
		std::cout << "problem loading AS TransitionBlack.png";
	}
	m_fadeBlackSprite.setTexture(m_fadeBlackTexture);
	m_fadeBlackSprite.setTextureRect(sf::IntRect{ 0,0,144,144 });
	//m_fadeBlackSprite.scale(5.0f, 5.0f);
	//m_fadeBlackSprite.setPosition(800, 600);
	m_fadeBlackSprite.setColor(sf::Color::Cyan);


	if (!m_frameTexture.loadFromFile("ASSETS\\IMAGES\\AS Frame.png"))
	{
		std::cout << "problem loading AS Frame.png";
	}
	m_frameSprite.setTexture(m_frameTexture);
	m_frameSprite.scale(4.0f, 3.0f);
	m_frameSprite.setColor(sf::Color::Black);

	if (!m_labBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\AS Lab BG.png"))//load texture
	{
		std::cout << "problem loading AS Lab BG.png" << std::endl;
	}
	m_labBackgroundSprite.setTexture(m_labBackgroundTexture);
	//m_labBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	m_labBackgroundSprite.setPosition(50, 50);
	m_labBackgroundSprite.scale(3.5f, 3.5f);//making it fit the window
	//m_labBackgroundTexture.setSmooth(true);

	if (!m_labBackgroundShadeTexture.loadFromFile("ASSETS\\IMAGES\\AS Lab BG_Multi.png"))//load texture
	{
		std::cout << "problem loading AS Lab BG_Multi.png";
	}
	m_labBackgroundShadeSprite.setTexture(m_labBackgroundShadeTexture);
	m_labBackgroundShadeSprite.scale(3.5f, 3.5f);//making it fir the window
	m_labBackgroundShadeSprite.setColor(sf::Color::Black);
	m_labBackgroundShadeSprite.setPosition(50, 50);
	m_labBackgroundShadeTexture.setSmooth(true);

	//potion sprites and load textures
	if (!m_blackBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS Black Serum.png"))//load texture
	{
		std::cout << "problem loading AS Black Serum.png";
	}
	m_blackBloodSprite.setTexture(m_blackBloodTexture);
	m_blackBloodSprite.scale(3.0f, 3.0f);
	m_blackBloodSprite.setPosition(310, 125);

	if (!m_blueBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS DarkBlue Blood.png"))//load texture
	{
		std::cout << "problem loading AS DarkBlue Blood.png";
	}
	m_blueBloodSprite.setTexture(m_blueBloodTexture);
	m_blueBloodSprite.scale(3.0f, 3.0f);
	m_blueBloodSprite.setPosition(515, 125);

	if (!m_redBloodTexture.loadFromFile("ASSETS\\IMAGES\\AS Red Blood.png"))//load texture
	{
		std::cout << "problem loading AS Red Blood.png";
	}
	m_redBloodSprite.setTexture(m_redBloodTexture);
	m_redBloodSprite.scale(3.0f, 3.0f);
	m_redBloodSprite.setPosition(415, 125);

	if (!m_serumDarkBlueTexture.loadFromFile("ASSETS\\IMAGES\\AS DarkBlue Serum.png"))//load texture
	{
		std::cout << "problem loading AS DarkBlue Serum.png";
	}
	m_serumDarkBlueSprite.setTexture(m_serumDarkBlueTexture);
	m_serumDarkBlueSprite.scale(3.0f, 3.0f);
	m_serumDarkBlueSprite.setPosition(100, 320);

	if (!m_serumBlueTexture.loadFromFile("ASSETS\\IMAGES\\AS Blue Serum.png"))//load texture
	{
		std::cout << "problem loading AS Blue Serum.png";
	}
	m_serumBlueSprite.setTexture(m_serumBlueTexture);
	m_serumBlueSprite.scale(3.0f, 3.0f);
	m_serumBlueSprite.setPosition(405, 380);

	if (!m_serumYellowTexture.loadFromFile("ASSETS\\IMAGES\\AS Yellow Serum.png"))//load texture
	{
		std::cout << "problem loading AS Yellow Serum.png";
	}
	m_serumYellowSprite.setTexture(m_serumYellowTexture);
	m_serumYellowSprite.scale(3.0f, 3.0f);
	m_serumYellowSprite.setPosition(250, 330);

	if (!m_serumGreenTexture.loadFromFile("ASSETS\\IMAGES\\AS Green Serum.png"))//load texture
	{
		std::cout << "problem loading AS Green Serum.png";
	}
	m_serumGreenSprite.setTexture(m_serumGreenTexture);
	m_serumGreenSprite.scale(3.0f, 3.0f);
	m_serumGreenSprite.setPosition(100, 85);

	if (!m_vialTexture.loadFromFile("ASSETS\\IMAGES\\AS Beaker.png"))
	{
		std::cout << "problem loading AS Beaker.png";
	}
	m_vialSprite.setTexture(m_vialTexture);
	m_vialSprite.setScale(5.0f, 5.0f);
	m_vialSprite.setPosition(350, 120);

	//buttom sprites and textures
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\AS ButtonOne.png"))
	{
		std::cout << "problem loading AS ButtonOne.png";
	}
	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.scale(3.0f, 3.0f);
	m_buttonSprite.setPosition(200, 280);

	if (!m_continueTexture.loadFromFile("ASSETS\\IMAGES\\AS ButtonOne.png"))
	{
		std::cout << "problem loading AS ButtonOne.png";
	}
	m_continueSprite.setTexture(m_continueTexture);
	m_continueSprite.setScale(2.0f, 2.0f);
	m_continueSprite.setPosition(80, 500);
}

/// <summary>
/// Animates a fade to black transition
/// </summary>
void Game::fadeBlackTransition()
{
	int frame = 0;
	const int FRAME_WIDTH = 144;
	const int FRAME_HEIGHT = 144;

	m_transitionFrameCounter += m_transitionFrameIncrement;
	frame = static_cast<int>(m_transitionFrameCounter);
	if (frame >= TRANSITION_FRAMES)
	{
		frame = 0;
		m_transitionFrameCounter = 0.0f;
	}
	if (frame != m_transitionFrame)
	{
		m_transitionFrame = frame;
		m_fadeBlackSprite.setTextureRect(sf::IntRect{ frame * FRAME_WIDTH,0,FRAME_WIDTH, FRAME_HEIGHT });
	}
}

void Game::selectSerums()
{
	switch(serum)
	{
		case 1:
			m_serumGreenSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		case 2:
			m_serumYellowSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		case 3:
			m_serumBlueSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		case 4:
			m_serumDarkBlueSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		case 5:
			m_redBloodSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		case 6:
			m_blueBloodSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();

		default:
			m_blackBloodSprite.setColor(sf::Color::Black);
			serumSelected = true;
			checkSerumSelection();
	}
}

void Game::checkSerumSelection()
{
	if (serumSelected == true)
	{
		std::cout << serum << "";
	}
}

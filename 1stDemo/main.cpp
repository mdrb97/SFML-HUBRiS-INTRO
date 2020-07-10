#include <iostream>
#include <string>
#include <cmath> 
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <TlHelp32.h> 

std::string getFrameText(int min, int max, char symbol) {
	std::string str = "";
	for (int i = min; i < max; i++)
		str += symbol;
	return str;
}

bool DialogDisplayFullsceen() {
	return MessageBox(NULL, "Fullscreen?", "HUBRiS in 2020!", MB_YESNO) == IDYES;
}

int main()
{
	int rightTextLoopCtr = 0;
	int frameRate = 60;
	int windowWidth = 800;
	int windowHeight = 600;
	sf::RenderWindow window;
	if (DialogDisplayFullsceen())
		window.create(sf::VideoMode(windowWidth, windowHeight), "HUBRiS!", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(windowWidth, windowHeight), "HUBRiS!");

	window.setFramerateLimit(frameRate);

	std::cout << "Initializing Demo..." << std::endl;

	int textFrameWidthOffset = 50;
	int textFrameHeightOffset = 50;

	sf::Font font;
	sf::Text sinText;
	sf::Text frameTextTop;
	sf::Text frameTextBottom;
	sf::Text frameTextVertical;
	sf::Text title;
	sf::Text releaseDate;
	sf::Text leftMessage;
	sf::Text rightMessage;
	sf::Text bottomBanner;
	sf::Clock textClock;
	sf::Clock bottomBannerClock;
	sf::Clock bottomBannerColorClock;
	sf::ConvexShape star1;
	sf::Texture hubrisTexture;
	sf::Sprite hubrisSprite;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	bool switchBottomBannerDirection = false;

	if (!hubrisTexture.loadFromFile("hubris.png"))
		return -1;


	if (!font.loadFromFile("Cute Jellyfish.ttf"))
		return -1;


	std::cout << "Font Loaded!" << std::endl;

	star1.setPointCount(10);
	// creating star
	star1.setPoint(0, sf::Vector2f(0, 150));
	star1.setPoint(1, sf::Vector2f(95, 150));
	star1.setPoint(2, sf::Vector2f(124, 240));
	star1.setPoint(3, sf::Vector2f(155, 150));
	star1.setPoint(4, sf::Vector2f(250, 150));
	star1.setPoint(5, sf::Vector2f(173, 95));
	star1.setPoint(6, sf::Vector2f(200, 0));
	star1.setPoint(7, sf::Vector2f(124, 58));
	star1.setPoint(8, sf::Vector2f(50, 0));
	star1.setPoint(9, sf::Vector2f(78, 95));
	//setting it's position
	star1.setPosition(100, 600 / 2);
	star1.setFillColor(sf::Color::Color(25, 25, 112));
	star1.setOutlineColor(sf::Color::Color(0, 0, 128));
	star1.setOutlineThickness(2);

	frameTextTop.setFont(font);
	frameTextTop.setString(getFrameText(0, windowWidth, '*'));
	frameTextTop.setCharacterSize(48);
	frameTextTop.setFillColor(sf::Color::Color(211, 211, 211));
	frameTextTop.setPosition(0, 0 + textFrameHeightOffset / 2);
	frameTextBottom.setFont(font);
	frameTextBottom.setString(getFrameText(0, windowWidth, '*'));
	frameTextBottom.setCharacterSize(48);
	frameTextBottom.setFillColor(sf::Color::Color(211, 211, 211));
	frameTextBottom.setPosition(0, windowHeight - textFrameHeightOffset * 2);
	frameTextVertical.setFont(font);
	frameTextVertical.setString(getFrameText(0, 26, '*'));
	frameTextVertical.setPosition(windowWidth / 2 - 100, windowHeight / 10);
	frameTextVertical.setRotation(90);
	frameTextVertical.setCharacterSize(48);
	frameTextVertical.setFillColor(sf::Color::Color(211, 211, 211));

	int titleWidth = 20;
	int titleHeight = 60;
	int releaseDateWidth = titleWidth;
	int releaseDateHeight = titleHeight + 100;
	int leftMessageWidth = titleWidth;
	int leftMessageHeight = releaseDateHeight + 100;

	title.setFont(font);
	title.setString("--HUBRiS PRESENTS:\n\t\tSFML DEMO 1");
	title.setPosition(titleWidth, titleHeight);
	title.setCharacterSize(24);
	title.setFillColor(sf::Color::White);

	releaseDate.setFont(font);
	releaseDate.setString("--RELEASED ON:\n\t\tO1/O6/2O2O");
	releaseDate.setPosition(releaseDateWidth, releaseDateHeight);
	releaseDate.setCharacterSize(24);
	releaseDate.setFillColor(sf::Color::White);

	leftMessage.setFont(font);
	leftMessage.setString("\n\n\n\nRELEASED FOR YOUR \nPLEASURE!");
	leftMessage.setPosition(leftMessageWidth, leftMessageHeight);
	leftMessage.setCharacterSize(24);
	leftMessage.setFillColor(sf::Color::White);

	rightMessage.setFont(font);
	rightMessage.setString("lets hopefully get rid of this pandemic <3 ");
	rightMessage.setPosition(windowWidth / 2 - 100, windowHeight / 10);
	rightMessage.setCharacterSize(24);
	rightMessage.setFillColor(sf::Color::White);

	sinText.setFont(font);
	sinText.setString("HUBRiS in 2O2O!");
	sinText.setCharacterSize(80);
	sinText.setFillColor(sf::Color::Color(46, 139, 87));
	sinText.setLetterSpacing(2);
	sinText.setOutlineColor(sf::Color::Color(0, 0, 128));
	sinText.setOutlineThickness(2);
	sinText.setPosition(-1 * windowWidth, windowHeight / 2);

	bottomBanner.setFont(font);
	bottomBanner.setString("sV / CaKE / MrK - HUBRiS 2O2O");
	bottomBanner.setCharacterSize(24);
	bottomBanner.setPosition(windowWidth, windowHeight - 30);
	bottomBanner.setStyle(sf::Text::Style::Italic);

	std::cout << "Text is ready. Lets go!" << std::endl;

	float currentTextPosition = 0.0f;
	float baseline = 325;
	float starBaseline = 350;
	float y = 0;
	float starY = 0;
	float x = -1 * windowWidth;
	float frequency = 200;
	float starFrequency = 10;
	float sign = 1;
	float textRotationSign = 1;

	if (!soundBuffer.loadFromFile("pleasure to paso.ogg"))
		return -1;

	sound.setBuffer(soundBuffer);

	hubrisTexture.setSmooth(true);
	hubrisSprite.setTexture(hubrisTexture);
	hubrisSprite.setPosition(windowWidth / 2 - 50, windowHeight / 2);

	int bottomBannerR = 0;
	int bottomBannerG = 0;
	int bottomBannerB = 0;

	sf::Color rgbColors[21] = {
		sf::Color(255, 0, 0, 44),
		sf::Color(255, 0, 0, 87),
		sf::Color(255, 0, 0, 127),
		sf::Color(255, 127, 0, 44),
		sf::Color(255, 127, 0, 87),
		sf::Color(255, 127, 0, 127),
		sf::Color(255, 255, 0, 44),
		sf::Color(255, 255, 0, 87),
		sf::Color(255, 255, 0, 127),
		sf::Color(0, 255, 0, 44),
		sf::Color(0, 255, 0, 87),
		sf::Color(0, 255, 0, 127),
		sf::Color(0, 0, 255, 44),
		sf::Color(0, 0, 255, 87),
		sf::Color(0, 0, 255, 127),
		sf::Color(75, 0, 130, 44),
		sf::Color(75, 0, 130, 87),
		sf::Color(75, 0, 130, 127),
		sf::Color(143, 0, 255, 44),
		sf::Color(143, 0, 255, 87),
		sf::Color(143, 0, 255, 127)
	};
	short rgbColorIdx = 0;

	while (window.isOpen())
	{
		sf::Event event;
		if (sound.getStatus() == sf::SoundSource::Status::Stopped)
			sound.play();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		window.clear();

		window.draw(bottomBanner);
		window.draw(hubrisSprite);
		window.draw(star1);
		window.draw(frameTextTop);
		window.draw(frameTextBottom);
		window.draw(frameTextVertical);
		window.draw(sinText);
		window.draw(title);
		window.draw(releaseDate);
		window.draw(leftMessage);
		window.draw(rightMessage);

		window.display();

		y = baseline + ((sin(x * 0.02) * frequency));
		starY = (starBaseline - (x)) + (starFrequency);
		if (starY < 0)
			starY *= -1;
		sinText.setPosition(x, y - 100);
		star1.setPosition(x + 500, 600 / 2);
		star1.setRotation(starY);

		if (x >= 1000 && sign != -1) {
			sign = -1;
		}
		else if (x <= -1000 && sign == -1)
			sign = 1;
		x += (sign);

		if (textClock.getElapsedTime().asSeconds() > 10) {
			switch (rightTextLoopCtr) {
			case -1:
				rightTextLoopCtr++;
				rightMessage.setString("lets hopefully get rid of this pandemic <3 ");
				break;
			case 0:
				rightTextLoopCtr++;
				rightMessage.setString("Fuck CoronaVirus!");
				break;
			case 1:
				rightTextLoopCtr++;
				rightMessage.setString("Power to the Hong Kong fighters!");
				break;
			case 2:
				rightTextLoopCtr++;
				rightMessage.setString("<3 each other");
				break;
			case 3:
				rightTextLoopCtr++;
				rightMessage.setString("Keep an eye on HUBRiS for another \nquality release!");
				break;
			case 4:
				rightTextLoopCtr++;
				rightMessage.setString("Greetingz to sV for helping \nwith the star!");
				break;
			default:
				rightTextLoopCtr = -1;
				rightMessage.setString("Oh! You're still here? Let it loop again :-D");
				break;
			}
			
			textClock.restart();
		}

		if (bottomBannerClock.getElapsedTime().asSeconds() > 15) {
			if (switchBottomBannerDirection) 
				bottomBanner.setPosition(windowWidth, windowHeight - 30);
			switchBottomBannerDirection = !switchBottomBannerDirection;
			bottomBannerClock.restart();
		}

		hubrisSprite.setPosition(windowWidth / 2 - 50, windowHeight / 2 - (y / 10));

		if(bottomBanner.getPosition().x != 0)
			bottomBanner.move(-10, 0);
		else if(switchBottomBannerDirection)
			bottomBanner.move(-10, 0);

		if (bottomBannerColorClock.getElapsedTime().asMilliseconds() > 100) {
			if (!switchBottomBannerDirection)
				bottomBanner.setFillColor(rgbColors[rgbColorIdx]);
			else
				bottomBanner.setFillColor(rgbColors[rgbColorIdx]);

			bottomBannerColorClock.restart();

			rgbColorIdx += 1;
			if (rgbColorIdx == 21 - 1)
				rgbColorIdx = 0;
		}
	}

	return 0;
}


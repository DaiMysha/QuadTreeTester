#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/gl.h>

#define WIDTH   640
#define HEIGHT  480

void drawCross(sf::RenderTarget& window, const sf::Vector2f& p, const sf::Color& c = sf::Color::Green, float size = 5.0f) {

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(p.x-size,p.y), c),
        sf::Vertex(sf::Vector2f(p.x+size,p.y), c),
        sf::Vertex(sf::Vector2f(p.x,p.y-size), c),
        sf::Vertex(sf::Vector2f(p.x,p.y+size), c)
    };

    window.draw(line, 4, sf::Lines);
}

//font taken from http://www.fontspace.com/melifonts/sweet-cheeks
int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "QuadTree tester");

    int fps = 0;
    int elapsedFrames = 0;
    sf::Clock clock, pclock;

    sf::Font font;

    if(!font.loadFromFile("data/Sweet Cheeks.ttf")) exit(-1); //because yes

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(580,10);
    text.setString("0");
    text.setColor(sf::Color::White);

    sf::View view;
    view.setSize(sf::Vector2f(WIDTH,HEIGHT));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code) {
                    case sf::Keyboard::Escape:
                    {
                        window.close();
                    } break;
                    default: break;
                }
            }
        }
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        window.clear();

        drawCross(window,sf::Vector2f(mouse.x,mouse.y));

        window.draw(text);
        window.display();

        //sf::sleep(sf::milliseconds(16));
        ++elapsedFrames;
        if(clock.getElapsedTime().asMilliseconds() > 500) {
            fps = elapsedFrames;
            elapsedFrames = 0;
            clock.restart();
            //for some reason my compiler doesn't find to_string so..
            std::ostringstream str;
            str << (fps*2) << "\n";
            str << "n : " << 0;
            text.setString(str.str());
        }
    }

    return 0;
}

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <list>

#include <time.h>

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

void addRandoms(std::list<sf::Vector2f>& l, int count) {
    float x,y;
    for(int i=0;i<count;++i) {
        x = rand() % WIDTH;
        y = rand() % WIDTH;
        l.push_back(sf::Vector2f(x,y));
    }
}

//font taken from http://www.fontspace.com/melifonts/sweet-cheeks
int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "QuadTree tester");
    srand(time(0));
    int fps = 0;
    int elapsedFrames = 0;
    sf::Clock clock, pclock;

    sf::Font font;

    if(!font.loadFromFile("data/Sweet Cheeks.ttf")) exit(-1); //because yes

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(550,10);
    text.setString("0");
    text.setColor(sf::Color::White);

    sf::View view;
    view.setSize(sf::Vector2f(WIDTH,HEIGHT));

    std::list<sf::Vector2f> points;

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
                    case sf::Keyboard::F1:
                    {
                        addRandoms(points,1);
                    } break;
                    case sf::Keyboard::F2:
                    {
                        addRandoms(points,10);
                    } break;
                    case sf::Keyboard::F3:
                    {
                        addRandoms(points,100);
                    } break;
                    case sf::Keyboard::F4:
                    {
                        addRandoms(points,1000);
                    } break;
                    default: break;
                }
            } else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Right) {
                    points.clear();
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            points.push_back(sf::Vector2f(mouse.x,mouse.y));
        }

        window.clear();

        for(sf::Vector2f p : points)
            drawCross(window,p);

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
            str << "n : " << points.size();
            text.setString(str.str());
        }
    }

    return 0;
}

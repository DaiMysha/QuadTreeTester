#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <list>

#include <time.h>

#include <DMUtils\QuadTree.hpp>

#define WIDTH   640
#define HEIGHT  480

int n=0;

std::list<typename DMUtils::physics::AABB<float>> aabb_list;

void drawCross(sf::RenderTarget& window, const sf::Vector2f& p, const sf::Color& c = sf::Color::Green, float size = 5.0f) {

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(p.x-size,p.y), c),
        sf::Vertex(sf::Vector2f(p.x+size,p.y), c),
        sf::Vertex(sf::Vector2f(p.x,p.y-size), c),
        sf::Vertex(sf::Vector2f(p.x,p.y+size), c)
    };

    window.draw(line, 4, sf::Lines);
}

void drawBox(sf::RenderTarget& window, sf::Vector2i a, sf::Vector2i b, sf::Color c) {

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(a.x,a.y), c),
        sf::Vertex(sf::Vector2f(b.x,a.y), c),
        sf::Vertex(sf::Vector2f(b.x,b.y), c),
        sf::Vertex(sf::Vector2f(a.x,b.y), c),
        line[0]
    };

    window.draw(line, 5, sf::LinesStrip);
}

template <typename T>
void drawBox(sf::RenderTarget& window, const DMUtils::physics::AABB<T>& a, const sf::Color& c = sf::Color::Green) {

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(a.left,a.top), c),
        sf::Vertex(sf::Vector2f(a.left + a.width,a.top), c),
        sf::Vertex(sf::Vector2f(a.left + a.width,a.top + a.height), c),
        sf::Vertex(sf::Vector2f(a.left,a.top + a.height), c),
        line[0]
    };

    window.draw(line, 5, sf::LinesStrip);
}

void addPoint(DMUtils::QuadTree<DMUtils::physics::AABB<float>>& l, float x, float y, float w, float h) {
    DMUtils::physics::AABB<float> box = DMUtils::physics::AABB<float>(x,y,w,h);
    aabb_list.push_front(box);

    l.insert(*aabb_list.begin(),&*aabb_list.begin());
    ++n;
}

void addRandoms(DMUtils::QuadTree<DMUtils::physics::AABB<float>>& l, int count) {
    float x,y,w,h;
    for(int i=0;i<count;++i) {
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        w = rand() % ((int)x - WIDTH);
        h = rand() % ((int)y - HEIGHT);

        addPoint(l,x,y,w,h);
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

    sf::Vector2i click1;
    sf::Vector2i click2;
    bool pressed = false;
    bool collision = false;
    int col_size = 0;

    DMUtils::QuadTree<DMUtils::physics::AABB<float>> points(WIDTH,HEIGHT);

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
                    case sf::Keyboard::BackSpace:
                    {
                        n = 0;
                        points.clear();
                    } break;
                    case sf::Keyboard::Delete:
                    {
                        n -= points.remove(DMUtils::physics::AABB<float>(click1.x,click1.y,click2.x - click1.x,click2.y - click1.y));
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
                    case sf::Keyboard::F5:
                    {
                        addRandoms(points,100000);
                    } break;
                    default: break;
                }
            } else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Middle) {
                    collision = !collision;
                }
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    addPoint(points,mouse.x,mouse.y,rand()%50,rand()%50);

                }
                if(event.mouseButton.button == sf::Mouse::Right) {
                    pressed = true;
                    click1 = sf::Mouse::getPosition(window);
                }
            } else if(event.type == sf::Event::MouseMoved) {
                if(pressed) click2 = sf::Mouse::getPosition(window);
            } else if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Right) {
                    pressed = false;
                    if(click1.x > click2.x) {
                        auto i = click2.x;
                        click2.x = click1.x;
                        click1.x = i;
                    }
                    if(click1.y > click2.y) {
                        auto i = click2.y;
                        click2.y = click1.y;
                        click1.y = i;
                    }
                }
            }
        }

        window.clear();

        for(auto& p : points.data())
            drawBox(window,*p);
        if(collision) {
            auto col = points.query(DMUtils::physics::AABB<float>(click1.x,click1.y,click2.x - click1.x,click2.y - click1.y));
            for(auto& n : col) {
                drawBox(window,*n.data,sf::Color::Blue);
            }
            col_size = col.size();
        }

        drawBox(window,click1,click2,sf::Color::Red);

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
            str << "\nd : " << points.depth();
            if(collision) str << "\ncol : " << col_size;
            text.setString(str.str());
        }
    }

    return 0;
}

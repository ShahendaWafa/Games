#include <SFML/Graphics.hpp>
#include <iostream>

int pressed = 0;

int maze[10][10]{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    1, 1, 0, 0, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 0, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void drawMaze(sf::RenderWindow* window, sf::Sprite block) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (maze[j][i] == 1) {
                block.setPosition(sf::Vector2f(i * 50, j * 50));
                window->draw(block);
            }
        }
    }
}

sf::Vector2f move(sf::Vector2f pos, int key) {
    if (key == 1) {
        if (!(maze[(int)pos.y / 50][(int)pos.x / 50])) {
            pos.x -= 1;
        }
        else {
            pressed = 0;
            pos.x += 1;
        }
    }
    if (key == 2) {
        if (!(maze[(int)pos.y / 50][((int)(pos.x) + 50) / 50])) {
            pos.x += 1;
        }
        else {
            pressed = 0;
        }
    }
    if (key == 3) {
        if (!(maze[(int)pos.y / 50][((int)(pos.x)) / 50])) {
            pos.y -= 1;
        }
        else {
            pressed = 0;
            pos.y += 1;
        }
    }
    if (key == 4) {
        if (!(maze[((int)pos.y + 50) / 50][(int)(pos.x) / 50])) {
            pos.y += 1;
        }
        else {
            pressed = 0;
        }
    }
    return pos;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

    sf::Texture grass, bugu, bugd, bugl, bugr;
    bugu.loadFromFile("bugU.png");
    bugd.loadFromFile("bugD.png");
    bugl.loadFromFile("bugL.png");
    bugr.loadFromFile("bugR.png");
    grass.loadFromFile("grass.png");

    sf::Sprite block(grass);
    block.setScale(50 / block.getLocalBounds().width, 50 / block.getLocalBounds().height);
    sf::Sprite bug(bugu);
    bug.setScale(50 / bug.getLocalBounds().width, 50 / bug.getLocalBounds().height);
    bug.setPosition(4 * 50, 8 * 50);

    sf::RectangleShape endPoint(sf::Vector2f(5, 50));
    endPoint.setFillColor(sf::Color::Green);
    endPoint.setPosition(10 * 50 - 5, 3 * 50);

    sf::Vector2f won(450, 150);
    sf::Texture text;
    text.loadFromFile("congrats.png");
    sf::Sprite sp(text);
    sp.setScale(400 / sp.getLocalBounds().width, 50 / sp.getLocalBounds().height);
    sp.setPosition(50, 225);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (pressed == 0) {
                switch (event.type) {
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                    case sf::Keyboard::Left:
                        pressed = 1;
                        bug.setTexture(bugl);
                        break;
                    case sf::Keyboard::Right:
                        pressed = 2;
                        bug.setTexture(bugr);
                        break;
                    case sf::Keyboard::Up:
                        bug.setTexture(bugu);
                        pressed = 3;
                        break;
                    case sf::Keyboard::Down:
                        bug.setTexture(bugd);
                        pressed = 4;
                        break;
                    }
                default:
                    break;
                }
            }

        }
        if (pressed) {
            sf::Vector2f pos = move(bug.getPosition(), pressed);
            bug.setPosition(pos);
        }

        if (bug.getPosition() == won) {
            pressed = -1;
        }

        drawMaze(&window, block);
        window.draw(bug);
        window.draw(endPoint);
        if (pressed == -1) {
            window.draw(sp);
        }
        window.display();
        window.clear(sf::Color::White);

    }

    return 0;
}
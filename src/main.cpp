#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 720;
const int RESOLUTION = 8;

const int rows = WIDTH/RESOLUTION;
const int cols = HEIGHT/RESOLUTION;

int dir = 0;

int pos_rows = rows/2;
int pos_cols = cols/2;

void moveAnt(int d)
{
    switch(d)
    {
        case 0: //up
            if(pos_rows == 0)
                pos_rows++;
            else
                pos_rows--;
        break;

        case 1: //right
            if(pos_cols == cols-1)
                pos_cols--;
            else
                pos_cols++;
        break;

        case 2: //down
            if(pos_rows == rows-1)
                pos_rows--;
            else
                pos_rows++;
        break;

        case 3: //left
            if(pos_cols == 0)
                pos_cols++;
            else
                pos_cols--;
        break;

        default:
            cout << "This should never trigger." << endl;
    }
}

int main()
{
    int grid[rows][cols];

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            grid[i][j] = 0;
        }
    }

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(RESOLUTION, RESOLUTION));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Langton's Ant");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(grid[pos_rows][pos_cols] == 1) //white
        {
            dir++; //turn right
            if(dir>3)
                {dir=0;}
            grid[pos_rows][pos_cols] = 0; //flip colour
            moveAnt(dir); //move one unit
        }
        else if(grid[pos_rows][pos_cols] == 0) //black
        {
            dir--; //turn left
            if(dir<0)
                {dir=3;}
            grid[pos_rows][pos_cols] = 1; //flip colour
            moveAnt(dir); //move one unit
        }
        window.clear();

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                if(grid[i][j] == 1)
                    rectangle.setFillColor(sf::Color::White);
                else
                    rectangle.setFillColor(sf::Color::Black);

                rectangle.setPosition(i*RESOLUTION, j*RESOLUTION);
                window.draw(rectangle);
            }
        }

        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(pos_rows*RESOLUTION, pos_cols*RESOLUTION);
        window.draw(rectangle);

        window.display();
    }

    return 0;
}

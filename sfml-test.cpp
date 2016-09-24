/** 
Minigame using SFML library
Copyright (C) 2016 Stefan Ivanovic 

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
**/


#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
using namespace sf;





int main()
{
   srand (time(NULL));
   RenderWindow window(VideoMode(1400, 800), "Space Bunny");
   window.setFramerateLimit(60);
   Font font;
   font.loadFromFile("Elektra.ttf");
   Text title("Space  Bunny", font, 120);
   title.setPosition(80,50);
   int start_menu = 0;
   Text start("Press enter to start", font, 30);
   start.setPosition(490, 600);
   Texture bunnypic;
   std::vector<float> bunny_pos;
   bunny_pos.push_back(10);
   bunny_pos.push_back(400);
   bunnypic.loadFromFile("Bunny.png");
   Sprite bunny;
   bunny.setTexture(bunnypic);
   bunny.setPosition(bunny_pos[0],bunny_pos[1]);
   std::vector<float> view_pos;

   int score = 0;
   float speed = 1;

   std::vector<float> carrot_pos;
   Texture carrot_pic;
   Sprite carrot;
   carrot_pic.loadFromFile("Carrot.png");
   carrot_pos.push_back(1300);
   carrot_pos.push_back(280);
   carrot.setTexture(carrot_pic);
   carrot.setPosition(carrot_pos[0],carrot_pos[1]);


   std::string sscore;

   std::ostringstream convert;

   convert << score;
   sscore = convert.str();
   Font font2;
   font2.loadFromFile("FlashRoger.ttf");
   Text scoretxt(sscore, font2, 100);
   scoretxt.setPosition(650,650);
   Text game_over("GAME  OVER",font,100);
   game_over.setPosition(130,300);

   Texture backtexture;
   backtexture.loadFromFile("space.jpg");
   Sprite background;
   background.setPosition(0,0);
   background.setTexture(backtexture);



    // run the program as long as the window is open
    while (window.isOpen())
    {
        bunny.setPosition(bunny_pos[0],bunny_pos[1]);
        // check all the window's evencarrot.setPosition(carrot_pos[0],carrot_pos[1]);ts that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            if(Keyboard::isKeyPressed(Keyboard::Return))
            {
                switch (start_menu)
                {
                case 0:
                    start_menu = 1;
                    break;
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (bunny_pos[1] != 0)
                {
                    bunny_pos[1] -= 100;
                }

            }
            if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (bunny_pos[1] != 600)
                {
                    bunny_pos[1] += 100;
                }
            }

            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        if (start_menu == 0)
        {
            window.clear(Color::Black);
            window.draw(background);
            window.draw(title);
            window.draw(start);
            window.display();
        }
        else if (start_menu == 1)
        {

            int random = rand()%400+1;
            window.clear(Color::Black);
            if (carrot_pos[0] < 200 && carrot_pos[1] == bunny_pos[1]+80 )
            {
                carrot_pos[0] = 1300;
                if (random < 100)
                {
                    carrot_pos[1] = 80;
                }
                else if (random >= 100 && random < 200)
                {
                    carrot_pos[1] = 280;
                }
                else if (random >= 200 && random < 300)
                {
                    carrot_pos[1] = 480;
                }
                else if (random >= 300 && random < 400)
                {
                    carrot_pos[1] = 580;
                }
                score++;
                std::ostringstream convert;
                convert << score;
                sscore = convert.str();
                scoretxt.setString(sscore);
                if(score % 10 == 0 && score > 2)
                {
                    speed += 0.5;
                }
            }

            carrot.setPosition(carrot_pos[0],carrot_pos[1]);
            carrot_pos[0] -= 10*speed;

            window.draw(background);
            window.draw(carrot);
            window.draw(bunny);
            window.draw(scoretxt);


            window.display();
            if(carrot_pos[0] < 0)
            {
                start_menu = 2;
            }
        }
        else
        {
            window.clear(Color::Black);
            window.draw(background);
            window.draw(game_over);
            window.draw(scoretxt);
            window.display();
        }

    }

    return 0;
}


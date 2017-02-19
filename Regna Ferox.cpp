#include <iostream>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include<cctype>
#include <SFML/Audio.hpp>

int main ()
{
    std::string gender;

    std::cout<<"Welcome to the land of Regna Ferox." <<std::endl <<std::endl;
    std::cout <<"Are you a boy or a girl?" <<std::endl;
    std::cin >> gender;



    while(gender!="boy" && gender!="girl")
    {
        std::cout <<"Stop entering invalid stuff, mongrel." <<std::endl;
        std::cout <<"Are you a boy or a girl?" <<std::endl;
        std::cin >> gender;

    }





    sf::RenderWindow window(sf::VideoMode(800,600),"Adventures of Ashton");
    //this opens the window

    std::ifstream openfile("map1.txt");
    sf::Texture tileTexture;
    sf::Sprite tiles;



    sf::Vector2i gamemap[100][100];
    sf::Vector2i loadCounter = sf::Vector2i(0,0);

    if(openfile.is_open())
    {
        std::string tileLocation;
        openfile >> tileLocation;
        tileTexture.loadFromFile(tileLocation);
        tiles.setTexture(tileTexture);
        while(!openfile.eof())
        {
            std::string str;
            openfile >> str;
            char x = str[0], y = str[2];
            if(!isdigit(x) || !isdigit(y))
               gamemap[loadCounter.x][loadCounter.y] = sf::Vector2i(-1,-1);
            else
               gamemap[loadCounter.x][loadCounter.y] = sf::Vector2i(x-'0',y-'0');
            if(openfile.peek() == '\n')
            {
                loadCounter.x = 0;
		loadCounter.y++;
            }
	else
		loadCounter.x++;

        }
	loadCounter.y++;

    }



    enum player{Down,Left,Right,Up,animationDown,animationLeft,animationRight,animationUp};
    sf::Vector2i source(1, Down);

    sf::Texture playertex;
    sf::Sprite fireemblem;









    sf::Music music; //this works similarly to the sprite and texture function
    if(!music.openFromFile("conquest.wav"))
       std::cout <<"File is not working. Try again." <<std::endl;

       music.play();
       music.setLoop(true);



    //we need to load the image
    if(!playertex.loadFromFile("friend.png")|| !playertex.loadFromFile("girl.png"))
        std::cout <<"File is in the wrong location" << std::endl;

    if (gender == "boy") //Loads a boy character
        playertex.loadFromFile("friend.png");

    if (gender == "girl") //Loads a girl character
        playertex.loadFromFile("girl.png");


    //need to set the texture
    fireemblem.setTexture(playertex);


    //starting player in a different location

    fireemblem.setPosition(375.f,300.f);

    sf::Clock clock;
    float frameSpeed=500, frameCounter=0, frameSwitch=100;



    //start game loop
    while(window.isOpen())
    {
        sf::Event event;
        //check for events
        while(window.pollEvent(event))
            //need to set loop to check to close window

            if(event.type==sf::Event::Closed)
                window.close();

        for (int i = 0; i < loadCounter.x; i++)
    {
        for (int j = 0; j < loadCounter.y; j++)
        {
            if(gamemap[i][j].x != -1 && gamemap[i][j].y != -1)
            {
                tiles.setPosition(i*32, j*32);
                tiles.setTextureRect(sf::IntRect(gamemap[i][j].x * 32, gamemap[i][j].y * 32, 32, 32));
                window.draw(tiles);
            }
        }
    }


    frameCounter += frameSpeed * clock.restart().asSeconds();

        if(frameCounter >= frameSwitch)
    {

            frameCounter = 0;


        source.x++; //sets source.x = 2
        if(source.x * 42>= playertex.getSize().x)
            source.x=0; //cycling images





    }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();


        //movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
           {
               source.y = Down;
               fireemblem.move(0,0.1);
           }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            source.y = Left;
            fireemblem.move(-0.1,0);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            source.y = Right;
            fireemblem.move(0.1,0);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            source.y = Up;
            fireemblem.move (0,-0.1);
        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (source.y == Down) )
        {

            source.y = animationDown;


        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (source.y == Left) )
        {
            source.y = animationLeft;

        }


        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (source.y == Right) )
        {
            source.y = animationRight;

        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (source.y == Up) )
        {
            source.y = animationUp;

        }





        fireemblem.setTextureRect(sf::IntRect(source.x*42,source.y*42,42,42)); //cuts the image
         //clears display so the images dont remain



        window.draw(fireemblem);
        window.display();
        window.clear();





    }



return 0;


}




/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
//---------22i-0943---------//
//-------Ahmed Hannan------//
//PF Final Project//

#include<iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4 ,obj5;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/gameover.png");
    obj5.loadFromFile("img/bomb.png");
    
    
    Sprite sprite(obj1), background(obj2), frame(obj3), over(obj4), bomb(obj5), block1(obj1), block2(obj1),block3(obj1); 
    int delta_x=0, colorNum=1;
    float timer=0, delay=0.3,total_time=0.0, delay2 =0,bombtimer =0, bomb_time=0,temp;
    bool rotate=0;
    int current_block=rand()%7,  bomb_loc[2] ={}, bomb_color = rand()%7+1,level=1, bloclist[3] ={};
    int blockrotated=0;
    bool doesCollide=0;
    bool spacekey = 0, isbomb;
    int point_3[4][2] ={};
    int score=0;
    
    bloclist[0] = current_block;
    bloclist[1] = rand()%7;
    bloclist[2] = rand()%7;
    Clock clock;
    
    bomb_loc[0] = rand()%9+1; //setting ramdon x value for bomb throughout the game
    bomb_loc[1]=0;

    sf::Music music;
	if (!music.openFromFile("GameMusic.ogg")) //playing Toby Fox's Knock You Down in the background of the game
	{
		std::cout<<"File not found"<<std::endl;
	}
	
	music.play();
	music.setVolume(40.f); //Reducing sound to make sound effects audible
	
	sf::SoundBuffer buffer1;
	if(!buffer1.loadFromFile("zoom2.wav")) //Sound effect swoosh
	{
		std::cout<<"Error!"<<std::endl;
	}
	
	
	sf::Sound sound_1;
	sound_1.setBuffer(buffer1); //sound effect from buffer loaded into sound_1 
	
	sf::SoundBuffer buffer2;
	if(!buffer2.loadFromFile("drop.wav")) //Sound effect for spacebar
	{
		std::cout<<"error"<<std::endl; 
	}
	
	
	sf::Sound sound_2;
	sound_2.setBuffer(buffer2); //sound effect from buffer loaded into sound_2
	
	sf::SoundBuffer buffer3;
	if(!buffer3.loadFromFile("clear.wav")) //sound effect for row clearing added into buffer
	{
		std::cout<<"error"<<std::endl;
	}
	
	
	sf::Sound sound_3;
	sound_3.setBuffer(buffer3); 

    sf::SoundBuffer buffer4;
	if(!buffer4.loadFromFile("crash.wav")) //loading horizontal movemental failure sound effects into buffer
	{
		std::cout<<"error"<<std::endl;
	}
	
	
	sf::Sound sound_4;
	sound_4.setBuffer(buffer4); //sound effect from buffer loaded into sound_4
    
    sf::Font font; 
    
    if (!font.loadFromFile("ROCK.TTF"))    //loading font
    {
        std::cout<<"Font cant be loaded!"<<std::endl;
    }
    
	sf::Text text;

    
    text.setFont(font); // setting font for text

    text.setCharacterSize(32); //setting text size
    text.setFillColor(sf::Color::Black); //setting text color
    text.setStyle(sf::Text::Bold | sf::Text::Underlined); //formatting
    
    text.setPosition(30,400);
    

    bombtimer = 6 * (rand()%5+1); //setting timer for bomb
    
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        total_time += time;
        bomb_time += time;
        clock.restart();
        timer+=time;
        

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
            	else if (e.key.code == Keyboard::X)
            		return 0;
            	else if (e.key.code == Keyboard::Space)
            		spacekey = 1;			
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        
        if(bomb_time>bombtimer) 
        {
            isbomb =1;  //setting check to see if time has come for bomb.

        }
        
       
        


        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
                       //Example: fallingPiece() function is called here
		
        
        
        if(!isbomb){ 
            window.draw(text);
            temp = point_1[1][1];       
            if(spacekey)
            {
                instantdrop(spacekey);
                

            }
            if(point_1[1][1] != temp) //checking if the spacebar did cause a change
            {
                sound_2.play();
            }
            
            temp = point_1[0][0]; //resetting temp to see if delta_x caused a change and playing collision sound if it didnt
            if(delta_x !=0)
            {
                horizontalMovement(delta_x);
                if(point_1[0][0] == temp)
                {
                sound_4.play();
                }
                
            }					   
            

            fallingPiece(timer, delay,colorNum,current_block,blockrotated, bloclist);
            
            temp = score;
            score += RowIsFull(); //checking if row deleted
            if (score != temp) //seeing if score even got updated
            {
                sound_3.play();
            }
        
            

            temp = blockrotated;
            if(rotate)
            {
                rotateCollision(doesCollide,current_block,blockrotated); //function to see if blocks collide while rotating
                rotation(rotate, current_block,blockrotated,doesCollide); //function to rotate block
            }
            if(temp != blockrotated) //seeing if rotation of a block changed
            {
                sound_1.play(); //playing a sound if rotation occured
            }
            
            shadow(point_3); //a function to display the shadow of the falling object, only uses a seperate array as an input.

            if(gameOver())
            {
                window.clear(Color::Black);
                window.draw(over);
                window.display();
                music.stop();
                clock.restart();
                time = clock.getElapsedTime().asSeconds();
                delay2 =3.0;
                while(time < delay2)
                {
                    time = clock.getElapsedTime().asSeconds();
                }
                restartGame();
                score =0;
                music.play();
                total_time =0;
            }

            difficultyLevel(total_time,level);
            std::cout<<bloclist[0]<< " " << bloclist[1] <<std::endl;
            

            
            

            ///*** YOUR CALLING STATEMENTS END HERE ***///
            //////////////////////////////////////////////

            
            

            window.clear(Color::Black);
            text.setString("score = " + std::to_string(score));
            window.draw(background);
            window.draw(text);

            if (level == 1)//displaying 3 block suggestions
            {
                delay =0.3;
                for (int i=0; i<4; i++){
                    block1.setTextureRect(IntRect(1*18,0,18,18));
                    block1.setPosition(250 + (BLOCKS[bloclist[0]][i]%2)*18,100 + (BLOCKS[bloclist[0]][i]/2)*18);
                    
                    window.draw(block1);
                    
                }

                for (int i=0; i<4; i++){
                    block2.setTextureRect(IntRect(2*18,0,18,18));
                    block2.setPosition(250 + (BLOCKS[bloclist[1]][i]%2)*18,200 + (BLOCKS[bloclist[1]][i]/2)*18);
                    
                    window.draw(block2);
                    
                }

                for (int i=0; i<4; i++){
                    block3.setTextureRect(IntRect(3*18,0,18,18));
                    block3.setPosition(250 + (BLOCKS[bloclist[2]][i]%2)*18,300 + (BLOCKS[bloclist[2]][i]/2)*18);
                    
                    window.draw(block3);
                    
                }

            }
            else if (level ==2) //displaying two block sugestions
            {
                delay =0.15;
                for (int i=0; i<4; i++){
                    block1.setTextureRect(IntRect(1*18,0,18,18));
                    block1.setPosition(250 + (BLOCKS[bloclist[0]][i]%2)*18,100 + (BLOCKS[bloclist[0]][i]/2)*18);
                    
                    window.draw(block1);
                    
                }

                for (int i=0; i<4; i++){
                    block2.setTextureRect(IntRect(2*18,0,18,18));
                    block2.setPosition(250 + (BLOCKS[bloclist[1]][i]%2)*18,200 + (BLOCKS[bloclist[1]][i]/2)*18);
                    
                    window.draw(block2);
                    
                }

            }
            else //displaying just one block suggestion
            {
                delay =0.1;
                for (int i=0; i<4; i++){
                    block1.setTextureRect(IntRect(1*18,0,18,18));
                    block1.setPosition(250 + (BLOCKS[bloclist[0]][i]%2)*18,100 + (BLOCKS[bloclist[0]][i]/2)*18);
                
                    window.draw(block1);
                    
                }
            }

            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (gameGrid[i][j] == 0)
                    {
                    
                        continue;
                    
                    }
                    else
                    {
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        
                            sprite.setPosition(j * 18, i * 18);

                            sprite.move(28, 31);

                            window.draw(sprite);
                        
                    }
                
                }
            }
            for (int i=0; i<4; i++){
                sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
                sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
                sprite.move(28,31);
                window.draw(sprite);
            }

            for (int i=0; i<4; i++){
                sprite.setTextureRect(IntRect((colorNum+7)*18,0,18,18));
                sprite.setPosition(point_3[i][0]*18,point_3[i][1]*18);
                sprite.move(28,31);
                window.draw(sprite);
            }
        }
        else
        {
            
            window.clear();
            window.draw(background);

            for(int i=0;i<4;i++)
            {
                point_1[i][0] =0;
                point_1[i][1] =0;
                point_3[i][0] =0;
                point_3[i][1] =0;
            }
            
            time = clock.getElapsedTime().asSeconds();
            delay2 =0.3;
            
            while(time < delay2)
            {
                time = clock.getElapsedTime().asSeconds();
            }

            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (gameGrid[i][j] == 0)
                    {
                    
                        continue;
                    
                    }
                    else
                    {
                        sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                        
                            sprite.setPosition(j * 18, i * 18);

                            sprite.move(28, 31);

                            window.draw(sprite);
                        
                    }
                
                }
            }

            bomb.setTextureRect(IntRect(bomb_color * 18, 0, 18, 18));
            bomb.setPosition(bomb_loc[0] * 18, bomb_loc[1] * 18);
            bomb.move(28, 31);
            window.draw(bomb);
            
            if(gameGrid[bomb_loc[1]+1][bomb_loc[0]] == 0  & bomb_loc[1] < 20)
            {
                bomb_loc[1]+=1;
            } 
            else if(bomb_loc[1]==20)
            {
                isbomb =0;
                bomb_time=0;
                timer=0;
                bomb_loc[1]=0;
                bomb_color = rand()%7+1;
            }
            else
            {
                if(bomb_color == gameGrid[bomb_loc[1]+1][bomb_loc[0]])
                {   
                    restartGame();
                    
                }
                else
                {
                    int val =0;

                    for(int i =0; i<10 ; i++)
                    {
                        if(gameGrid[20][i])
                        {
                            gameGrid[20][i] =0;
                            val++;
                        }
                        if(val==4)
                        {
                            break;
                        }
                    }        
                

                    isbomb=0;
                    bomb_time=0;
                    timer=0;
                    bomb_loc[1]=0;
                    bomb_color = rand()%7+1;


                }
            }
            

        }
            //---The Final on Which Everything is Drawn Over is Loaded---//
            window.draw(frame);
            //---The Window that now Contains the Frame is Displayed---//
            window.display();
        
        
    }
    
    
    return 0;
}

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)'
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
//---------22i-0943---------//
//-------Ahmed Hannan------//
//PF Final Project//

void fallingPiece(float& timer, float& delay, int& colorNum, int& n,int& blockrotated, int blocklist[]){
     //takes timer and delay to compare, takes color of block, takes block number and block rotation orientation
	 // creates block when new block is needed and makes originally placed blocks fall by one
    if (timer>delay){
        
        
            
        if((point_2[0][0] == point_2[3][0]) && (point_2[0][1] == point_2[3][1])){ //removing the single block at the start of the game and replacing it with a shape
        	for (int i=0;i<4;i++){
        		point_1[i][0] = BLOCKS[n][i] % 2;
        	    point_1[i][1] = BLOCKS[n][i] / 2;
				blockrotated=0;
        	}
        }
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        	
        }
        	
      	
       	
        if (!anamoly()){
        
        	for (int i = 0; i < 4; i++)
            {
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum; //storing blocks in gameGrid

            }

            
            //setting a random block for the next time.
            n = blocklist[0];
			blocklist[0] = blocklist[1];
			blocklist[1] =blocklist[2];
			blocklist[2] = rand()%7;
            blockrotated=0; //resetting rotation value
            colorNum = rand()%7 +1; //numbers 1-7
            //--- Un-Comment this Part When You Make BLOCKS array---//
            
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            
        }
        
        timer=0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
void horizontalMovement(int& delta_x){ //only takes delta x, no return
		
		
		bool lborder=1,rborder=1;
		bool collide=0;
		
		if(delta_x == -1)
		{
			for(int i =0;i<4;i++){
				if(gameGrid[point_1[i][1]][point_1[i][0]-1] !=0 ) // checking if  block will collide moving left
				{
					collide =1;
				}
			}
		}
		else if (delta_x ==1){
			for(int i =0; i<4;i++){
				if(gameGrid[point_1[i][1]][point_1[i][0]+1] !=0 ) // checking if  block will collide moving right
				{
					collide =1;
				}
			}
		}
		
		if((point_1[0][0]>0 && point_1[1][0]>0) && (point_1[3][0] >0   &&  point_1[2][0]>0)) 
		{
			lborder=0; //checking if block is at border
			
		}
		if((point_1[0][0]<9 && point_1[1][0]<9)&&(point_1[2][0]<9 && point_1[3][0]<9))
		{
			rborder =0; //checking if block is at border
		}
		
		
		if ((delta_x ==-1 && !lborder) && !collide){ //seeing if keyboard pressed and if block is NOT at border
			for(int i =0 ; i<4;i++)
			{
				point_1[i][0] -=1;
    	    	point_2[i][0] -=1; //horizontal movement by 1 block left for negative input
			}		
		
		}
		else if((delta_x ==1 && !rborder)&& !collide){
			for(int i =0 ; i<4;i++)
			{
				point_1[i][0] +=1; //horizontal movement by 1 block right for positive input
    	    	point_2[i][0] +=1;
			}	
		}
		
		delta_x =0;
		
		
}

void rotateCollision(bool& doesCollide, int& n, int blockrotated) //takes boolean to store if collision will occur, block number and block rotation orientation
{
	//int temp[4][2]={0};
	doesCollide =0;
	switch(n)
	{
		case 0:
			if(blockrotated)
			{
				for(int i =0;i<4;i++)
				{
					if(0 < gameGrid[point_1[i][1]+i][point_1[1][0]]!= 0) //if block 0 is already rotated then will it cause collision on further rotation checked here
					{
						doesCollide =1;
					}
				}
				
			}
			else //if block 0 isn't already rotated, will it collide with other blocks if we attempt to rotate seen here
			{
				doesCollide =0;
				for(int i =0;i<4;i++)
				{
					if(gameGrid[point_1[0][1]][point_1[i][0]+(i-1)] !=0 )
					{
						doesCollide =1;
					}	
				}
			}
			break;
		case 1:
			if(!blockrotated) //checking for block 1 if itll collide upon rotating
			{
				if(gameGrid[point_1[1][1]][point_1[1][0]-1]!=0 || gameGrid[point_1[0][1]][point_1[2][0]] != 0)
				{
					doesCollide =1;
				}
			}
			else //checking if block 1 will collide when rotated back to original shape
			{
				if(gameGrid[point_1[3][1]+1][point_1[3][0]] !=0 || gameGrid[point_1[3][1]+2][point_1[3][0]])
				{
					doesCollide=1;
				}
			}
		case 2: //checking if block 2 will collide 
				if(!blockrotated)
				{
					if(gameGrid[point_1[1][1]][point_1[1][0]+1] !=0 || gameGrid[point_1[0][1]][point_1[2][0]] != 0 )
					{
						doesCollide=1;
					}
				}
				else
				{
					if(gameGrid[point_1[1][1]][point_1[3][0]] !=0 || gameGrid[point_1[1][1]+1][point_1[3][0]] != 0)
					{
						doesCollide=1;
					}
				}
			break;
	
		case 3: //checking for block 3 based on current rotation orientation
			if(!blockrotated)
			{
				if(gameGrid[point_1[1][1]][point_1[1][0]+1] != 0)
				{
					doesCollide =1;
				}
			}
			else if(blockrotated ==1)
			{
				if(gameGrid[point_1[1][1]-1][point_1[1][0]] != 0)
				{
					doesCollide=1;
				}
			}
			else if(blockrotated ==2)
			{	
				if(gameGrid[point_1[1][1]][point_1[1][0]-1] != 0)
				{
					doesCollide=1;
				}	
			}
			else if(blockrotated ==3)
			{
				if(gameGrid[point_1[1][1]+1][point_1[1][0]] != 0)
				{
					doesCollide =1;
				}
			}
			break;
			
		case 4: //checking for block 4 based on current rotation orientation
			if(!blockrotated && point_1[1][1]>0)
			{
				if(gameGrid[point_1[1][1]-1][point_1[1][0]] !=0 || gameGrid[point_1[0][1]][point_1[0][0]-1] != 0)
				{
					doesCollide =1;
				}
			}
			else if(blockrotated ==1)
			{
				if(gameGrid[point_1[0][1]-1][point_1[1][0]] != 0 || gameGrid[point_1[1][1]][point_1[1][0]+1] !=0)
				{
					doesCollide =1;
				}
			}
			else if(blockrotated ==2)
			{
				if(gameGrid[point_1[0][1]][point_1[0][0]+1] != 0 || gameGrid[point_1[1][1]+1][point_1[1][0]] != 0)
				{
					doesCollide =1;
				}
					
			}
			else if(blockrotated ==3)
			{
				if(gameGrid[point_1[1][1]][point_1[1][0]-1] != 0|| gameGrid[point_1[0][1]+1][point_1[0][0]] != 0)
				{
					doesCollide =1;
				}
			}
			break;
		case 5: //checking for block 5 based on current rotation orientation
			if(!blockrotated)
			{
				if(gameGrid[point_1[2][1]][point_1[2][0]+1] !=0 || gameGrid[point_1[2][1]][point_1[2][0]+2] !=0 )
				{
					doesCollide =1;
				}
			}
			else if(blockrotated ==1)
			{
				if(gameGrid[point_1[2][1]+1][point_1[2][0]] !=0 || gameGrid[point_1[2][1]+2][point_1[2][0]] !=0)
				{
					doesCollide =1;
				}
				
			}
			else if(blockrotated==2)
			{
				if(gameGrid[point_1[2][1]][point_1[2][0]-1] !=0 || gameGrid[point_1[2][1]][point_1[2][0]-2] !=0)
				{
					doesCollide =1;
				}
			}
			else if(blockrotated==3)
			{
				if(gameGrid[point_1[2][1]-1][point_1[2][0]] !=0 || gameGrid[point_1[2][1]-2][point_1[2][0]] !=0)
				{
					doesCollide =1;
				}
			}
			break;


	}
	
	
	
	return;
}


void rotation(bool& rotate, int n, int& blockrotated, bool& doesCollide) //takes bool rotate bool will gets turned off by the end of it, takes block number n, block rotation orientation 
// and takes final bool too see if collision will occur upon rotation
{
		
		
		if(n==0){ // for block 0
			if((!blockrotated && (point_1[0][1] > 3)) && !doesCollide ) //border and collision check if not already rotated
			{
			
				if(((point_1[0][0] > 0) && (point_1[0][0]<8)) && (point_1[0][1] != point_1[3][1]))
				{
					point_1[0][0] = point_1[0][0]-1;
					point_1[2][0] = point_1[2][0]+1;
					point_1[3][0] = point_1[3][0]+2;
					for(int i =0; i<4;i++)
					{
						point_1[i][1] = point_1[0][1];
					}
				
					for (int i =0;i<4;i++){
						point_2[i][0] = point_1[i][0];
						point_2[i][1] = point_1[i][1];
					}
					blockrotated=1;
					
				}
					
			}
			else if(blockrotated && !doesCollide) //border and collision checks if its alrady rotated and is going back to original orientation
			{
				if(((point_1[0][0] > -1) && (point_1[0][0]<8)) && (point_1[0][0]<18) )
				{
					point_1[0][0] = point_1[0][0]+1;
					point_1[2][0] = point_1[2][0]-1;
					point_1[3][0] = point_1[3][0]-2;
					for(int i =0; i<4;i++)
					{
						point_1[i][1] = point_1[0][1]+i;
					}
				
					for (int i =0;i<4;i++){
						point_2[i][0] = point_1[i][0];
						point_2[i][1] = point_1[i][1];
					}
					blockrotated=0;
				}
					
			}
		}
		else if(n==1){			
				if((!blockrotated && (point_1[1][0]>0)&& (point_1[1][1]<18)) && !doesCollide) //border and block collision check for block 1 if not rotated
				{
						point_1[0][0] -=1;
						point_1[0][1] +=1;
						point_1[2][1] -=1;
						point_1[2][0] -=1;
						point_1[3][1] -=2;
						blockrotated =1;	
					
					
				}
				else if((blockrotated && (point_1[2][1]<14)) && !doesCollide)	// border and collision check for block 1 if already rotated
				{
					
					point_1[0][0] +=1;
					point_1[0][1] -=1;
					point_1[2][1] +=1;
					point_1[2][0] +=1;
					point_1[3][1] +=2;
					blockrotated =0;
				}
				
					
			}		
	
		else if (n==2){ //border and collision check of block 2 based on rotation
			if(((!blockrotated && point_1[1][0]<8) && (point_1[1][0]>0 && point_1[1][1]<18)) && !doesCollide)
			{
				point_1[0][0] += 1;
				point_1[0][1] += 1;
				point_1[2][1] -= 1;
				point_1[2][0] += 1;
				point_1[3][1] -= 2;
				blockrotated=1;
			}
			else if((blockrotated && (point_1[2][1]<14)) && !doesCollide ) 
			{
				point_1[0][0] -= 1;
				point_1[0][1] -= 1;
				point_1[2][1] += 1;
				point_1[2][0] -= 1;
				point_1[3][1] += 2;
				blockrotated=0;
			
			
			}
		}
		else if (n==3 && point_2[3][1]>3) //border and collision check of block 3 based on rotation, keeping point_1[1] as center of rotation
		{
			if((!blockrotated && point_2[2][0]<8) && !doesCollide)
			{
				point_1[0][1] += 1;
				point_1[0][0] -= 1;
				point_1[3][1] -= 1;
				point_1[3][0] += 1;
				point_1[2][1] += 1;
				point_1[2][0] += 1;
				blockrotated =1;
			}	
			else if(blockrotated ==1 && (point_2[3][0]<9 && !doesCollide))
			 {
			 	point_1[0][1] += 1;
				point_1[0][0] += 1;
				point_1[3][1] -= 1;
				point_1[3][0] -= 1;
				point_1[2][1] -= 1;
				point_1[2][0] += 1;
				blockrotated =2;
			 }
			else if(blockrotated ==2 && (point_2[1][0] > 0 && !doesCollide)) 
			{
				point_1[0][1] -= 1;
				point_1[0][0] += 1;
				point_1[3][1] += 1;
				point_1[3][0] -= 1;
				point_1[2][1] -= 1;
				point_1[2][0] -= 1;
				blockrotated =3;
			}
			else if(blockrotated ==3 &&(point_1[1][1]<18 && !doesCollide))
			{
				point_1[0][1] -= 1;
				point_1[0][0] -= 1;
				point_1[3][1] += 1;
				point_1[3][0] += 1;
				point_1[2][1] += 1;
				point_1[2][0] -= 1;
				blockrotated =0;
			}
			
		}	
		else if(n ==4) //border and collision check of block 4 based on rotation, keeping point_1[1] as center of rotation
		{
			if(blockrotated ==0 && (point_1[0][0]>0 && !doesCollide))
			{	
				point_1[0][1] -=1;
				point_1[0][0] +=1;
				point_1[2][0] -=1;
				point_1[2][1] -=1;
				point_1[3][0] -=2;
				point_1[3][1] -=2;
				blockrotated =1;
			}
			else if(blockrotated ==1 && (point_1[1][0]<9&& !doesCollide))	
			{
				point_1[0][1] +=1;
				point_1[0][0] +=1;
				point_1[2][0] +=1;
				point_1[2][1] -=1;
				point_1[3][0] +=2;
				point_1[3][1] -=2;
				blockrotated =2;
			
			}
			else if((blockrotated ==2 && !doesCollide) && (point_1[0][0]<9 && point_1[1][1]<18))
			{
				point_1[0][1] +=1;
				point_1[0][0] -=1;
				point_1[2][0] +=1;
				point_1[2][1] +=1;
				point_1[3][0] +=2;
				point_1[3][1] +=2;
				blockrotated =3;
			}
			else if((blockrotated ==3 && !doesCollide) && (point_1[1][0]>0 && point_1[0][1]<18))
			{
				point_1[0][1] -=1;
				point_1[0][0] -=1;
				point_1[2][0] -=1;
				point_1[2][1] +=1;
				point_1[3][0] -=2;
				point_1[3][1] +=2;
				blockrotated =0;
			
			}
		
		}
		else if(n==5) //border and collision check of block 5 based on rotation, keeping point_1[2] as center of rotation
		{
			if((!blockrotated && !doesCollide) && point_1[2][0]< 8 )	
			{
				point_1[0][1] +=2;
				point_1[0][0] +=2;
				point_1[1][0] +=1;
				point_1[1][1] +=1;
				point_1[3][0] +=1;
				point_1[3][1] -=1;
				blockrotated =1;
			}	
			else if ((blockrotated ==1 && !doesCollide) && point_1[2][1] < 17)
			{
				point_1[0][1] +=2;
				point_1[0][0] -=2;
				point_1[1][0] -=1;
				point_1[1][1] +=1;
				point_1[3][0] +=1;
				point_1[3][1] +=1;
				blockrotated =2;
			}	
			else if((blockrotated == 2 && !doesCollide) && point_1[2][0]>1)
			{
				point_1[0][1] -=2;
				point_1[0][0] -=2;
				point_1[1][0] -=1;
				point_1[1][1] -=1;
				point_1[3][0] -=1;
				point_1[3][1] +=1;
				blockrotated =3;
			}
			else if ((blockrotated==3 && !doesCollide) && point_1[2][1] > 2)
			{
				point_1[0][1] -=2;
				point_1[0][0] +=2;
				point_1[1][0] +=1;
				point_1[1][1] -=1;
				point_1[3][0] -=1;
				point_1[3][1] -=1;
				blockrotated =0;
			}

		
		}	
		
		//block 6 due to its shape cannot be rotated
		
		
			
		
		
		
		
		
	rotate =0;
	return;
}

int RowIsFull() //checks if row is full and removes it, generates score as it does
{
    bool rowIsFull;
	int rowscleared=0, score =0; 

    for (int i = 0; i < M; i++)
    {
        rowIsFull = 1;

        for (int j = 0; j < N; j++)
        {
            if (gameGrid[i][j] == 0)
            {
                rowIsFull = 0;      // reset the bool variable if any one block is zero i.e unoccupied
                
				break;
            }

        }

        int temp = i; // variable to store the index of row being removed

        if (rowIsFull == 1)
        {
			rowscleared += 1;
            for (int j = 0; j < N; j++)
            {
                gameGrid[temp][j] = 0;   //reset the full row to 0 in gameGrid array 


            }
            for (int k = temp; k > 0; k--)
            {
                for (int w = 0; w < N; w++)
                {
                    gameGrid[k][w] = gameGrid[k - 1][w]; //copy all the blocks above the newly emplied row 
                }
            }
        }

    }
	if(rowscleared ==1)
	{
		score += 10; //if one row cleared at a time then score gets incremented by 10
	
	}
	else if(rowscleared ==2)
	{
		score += 30; //if two rows cleared at one time score incremented by 30
	}
	else if(rowscleared ==3)
	{
		score += 60; //if three rows cleared at once score incremented by 60
	}
	else if(rowscleared > 3)
	{
		score += 100; //if more than three rows cleared, score increased by 100
	}

	
	return score;
}
void instantdrop(bool& spacekey) //takes spacekey being pressed as an input and instantly drops shape to its max fallable value
{
	int dropBlocks[4]; //array to store how many blocks every block can fall before anomaly
	int min=0, height, drop=0;
	bool partOfShape=0;
	
	if(point_1[0][1] >1){
		for(int j=0;j<4;j++)
		{
			height = point_1[j][1]+1;
			drop =0;
			while((gameGrid[height][point_1[j][0]] ==0) && (height <20))
			{
				height +=1;
				drop +=1;
			}
			partOfShape =0;
			for(int i =0; i<4; i++)
			{	
				if(point_1[i][0] == point_1[j][0]) //same x values
				{
				
					if(i ==0)
					{
						continue;
					}
					else if(point_1[i][1] == height)
					{
						partOfShape =1;
					}
				}
			}
			if(partOfShape)
			{
				height +=1;
				drop+=1;
			}
			else
			{
			
				dropBlocks[j] = drop;
			}
		}
	
		min=99; //choosing a huge value for min to find minimum lower than it
		for(int l =0; l<4; l++)
		{
			if(dropBlocks[l]<min)
			{
				min = dropBlocks[l];
			}
		
		}
	
		for(int m=0;m<4;m++)
		{
			point_1[m][1]+= min;
			point_2[m][1]+= min; 
		}
	}
	spacekey=0;
	
	
	
	
}

void shadow(int point_3[4][2]) //generates shadow, takes its postion array as an argument 
{
	int dropBlocks[4]; //array to store how many blocks every block can fall before anomaly
		int min=0, height, drop=0;
		bool partOfShape=0;
	
	if(point_1[0][1] >1){
		for(int j=0;j<4;j++)
		{
			height = point_1[j][1]+1;
			drop =0;
			while((gameGrid[height][point_1[j][0]] ==0) && (height < 20)) //seeing if grid empty at that point and is height isnt exceeding limit
			{
				height +=1;
				drop +=1;
			}
			partOfShape =0;
			for(int i =0; i<4; i++) //checking if the game grid value is just part of the shape
			{	
				if(point_1[i][0] == point_1[j][0]) //same x values
				{
				
					if(i ==0)
					{
						continue;
					}
					else if(point_1[i][1] == height)
					{
						partOfShape =1;
					}
				}
			}
			if(partOfShape)
			{
				drop+=1;
				height +=1;
			}
			else
			{
			
				dropBlocks[j] = drop;
			}
		}
	
		min=99; //choosing a huge value for min to find minimum lower than it
		for(int l =0; l<4; l++)
		{
			if(dropBlocks[l]<min)
			{
				min = dropBlocks[l];
			}
		
		}
	
		for(int m=0;m<4;m++) //assiging the minimum fall value + original value to every block in shadow
		{
			point_3[m][1] = point_1[m][1]+min;
			point_3[m][0] = point_1[m][0];
			
		}
	}

}

//meun

bool gameOver() //checking if game is over 
{
	bool top=0;
	for (int i =0; i<10;i++)
	{
		if(gameGrid[1][i] != 0)
		{
			top =1;
		}
	}

	return top;

}

void restartGame() //renews the entire game grid
{
	for (int i =0 ; i<20; i++)
	{
		for(int j =0; j<10; j++)
		{
			gameGrid[i][j] =0;
		}
	}
	for(int i=0;i<4;i++)
	{
		point_1[i][0] =0;
		point_1[i][1] =0;
		
 	}
	
	

}




void difficultyLevel(int time, int& level) //takes total time and difficulty level variable and changes difficulty level depending on time
{
	if (time < 30)
		level =1;
	else if (time < 45)
		level =2;
	else if (time >= 45)
		level = 3;

}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////























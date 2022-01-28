/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
										      "SEMESTER FINAL PROJECT"
											NAME : AMNA SAHFIQ
											ROLLL NO. : 19I-1978
											SECTION : ' E '
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
void start();    // start function prototype
int file_reading(int [][2],int &);      // file_reading function prototype
void alivecell_initializer(int [][2],int &, int[][20]);    // alivecell_initializer function prototype
void Grid_display(int [][20]);     // Grid_display function prototype
void menu_display();     // menu function prototype
int adding_neighbors(int [][20], int , int, int[][2], int &);      // adding_neighbors function prototype
int counting_live_neighbors(int [][20], int, int );     // counting_live_neighbors function prototype
void next_generation(int[][2], int[][20], int, int & ,int &, int[][2]);    // next_generation function prototype
void display_secondaryarray(int [][2], int &);    // display_secondaryarray function prototype
void display_neiarray(int [][2], int &);     // display_neiarray function prototype
void file_writing(int [][2], int, int&);   // file_writing function prototype
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int main()
{
	start();  // start function call
	return 0;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void start() //start function : initializes main arrays and calls the rest of the functions instead of main
{
	const int secarr_size=100, neiarr_size=300, grid_size=20, coordinates_num=2;  
	int grid[grid_size][grid_size]={0};
	int sec_array[secarr_size][coordinates_num]={0};
	int nei_array[neiarr_size][coordinates_num]={0};
	int lastindex_sec=-1;
	int lastindex_nei=-1;
	int generations=0;
	menu_display();     //menu function call
	generations= file_reading(sec_array,lastindex_sec);  //file reading function call which returns an integer for number of generations
	alivecell_initializer(sec_array,lastindex_sec, grid);  // alive_cell initializer function call
        cout <<setw(38) <<"GENERATION: 0th"<<endl;
	Grid_display(grid);   // function call to display the initial grid after file reading
	cout << "Enter '1' to start the Generations or '0' to terminate the game : ";
	int option;
        do
        {
        	cin >> option;
        	if (option!=1 && option!=0)
        	{
        		cout << "PLease choose from '1' or '0' only."<<endl;  // error message in case of invalid input
        		cout << "OPTION : ";
        	}
        }
        while(option!=1 && option!=0);
        if(option==0)
        {
        	cout << "You chose to end the game"<<endl;
        	exit(0);
        }
        cout << endl<<endl;
	next_generation(sec_array, grid, generations, lastindex_sec, lastindex_nei, nei_array);  //next_generation function call to apply game rules
	file_writing(sec_array, generations,lastindex_sec);  // file writing function call to display output coordinates in a text file
	cout << "Thanks for Playing! Hope that you enjoyed it :)"<<endl;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int file_reading(int secondary_arr[100][2], int &lastindex_secondary)  //file reading function call to read the coordinates from input file
{
	int gen_num=0, cells_num=0;  // initialization
	string filename;
	cout << "Enter the name of the file you want to read in for the 0th Generation : "; //prompt for user
	cin  >> filename;
	ifstream readfile(filename); //object creation and input text file opening
	if(readfile)
	{
		readfile >> gen_num;        
		cout << "Number of total generations required : " << gen_num << endl; //input file reading
		readfile >> cells_num;          
		cout << "Number of alive cells at 0th Generation : " << cells_num << endl; //input file reading
		
		for(int count=0, check=0; check<cells_num; count++,check++)    //check is for checking if all the coordinates are stored in respective variables	
		{
			for(int j=0;j<2;j++)
			{
				readfile >> secondary_arr[count][j];   //reading coordinates from file
			}
			lastindex_secondary++;  // stores the last coloumn index of secondary array
		}
		cout << endl<<endl;
	}
	else
	{
		cout << "The desired file cannot be opened."<<endl;  //prompt for user in case the file cannot be opened
		exit(0);
	}
	readfile.close();  //input file closes
	return gen_num;    //returns the number of generaions of grid to start function
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void alivecell_initializer(int secondary_arr[100][2], int &lastindex_secondary, int grid_arr[20][20]) //alive cell initializer function to store the coordinates of alive cells in the secondary array.
{
	for(int i=0;i<=lastindex_secondary;i++) // loop to control the indexes of rows
	{
			int x=0, y=0;
			for(int j=0;j<2;j++)  // loop to control the indexes of coloumns
			{
				if(j==0)
				x=secondary_arr[i][j];  //stores x-coordinate
				if(j==1)                
				y=secondary_arr[i][j];  //stores y-coordinates
			}
			grid_arr[x][y]=1;  
	}             
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void Grid_display(int grid_arr[20][20])  // grid function to display the grid upon calling
{
	int alive=1;  //initializer for alive cell
	char dead='.';  //initializer for dead cells
	for(int i=0;i<20;i++)
	{                                       
		for(int j=0;j<20;j++)
		{
		
			if(grid_arr[i][j]==1)               
			{
				cout<<setw(3)<<alive;            //1 is for alive cell  
			}
			else
			{
				cout<<setw(3)<<dead;            //'.' is for dead cell
			}
			
		}
		cout<<endl;
	}
	cout << endl;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void menu_display()   //menu function to display menu for the game
{
	cout << "WELCOME TO THE GAME OF LIFE :) "<<endl;      //instructions for the user
	cout << "The Game of Life is not your typical computer game but it is a cellular automaton."<<endl;  //instructions for the user
	cout << "The rules of the \"GAME OF LIFE\" are as follows: "<<endl;  //instructions for the user
	cout << "-> For a space that is populated : "<<endl;  //instructions for the user
    	cout << "        1) Each cell with one or no neighbors dies, as if by solitude."<<endl ;  //instructions for the user
    	cout << "	 2) Each cell with four or more neighbors dies, as if by overpopulation."<<endl ;   //instructions for the user
    	cout << "	 3) Each cell with two or three neighbors survives."<<endl ;   //instructions for the user
	cout << "-> For a space that is empty or unpopulated : "<<endl;   //instructions for the user
        cout << "        1) Each cell with three neighbors becomes populated. "<<endl;   //instructions for the user
        cout <<"CONTROLS : Enter the name of file for your 0th Generation when demanded and a new generation of cells"<<endl;   //instructions for the user
        cout <<"           (corresponding to the iteration of the rules) is produced."<<endl;  //instructions for the user
        cout << "Enter '1' to advance or '0' to terminate : ";  //prompt for the user
        int option;
        do
        {
        	cin >> option;
        	if (option!=1 && option!=0)
        	{
        		cout << "PLease choose from '1' or '0' only."<<endl;   //error message upon wrong input
        		cout << "OPTION : ";
        	}
        }
        while(option!=1 && option!=0);
        if(option==0)
        {
        	cout << "*** You chose to end the game ***"<<endl;  //prompt for user
        	exit(0);
        }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int adding_neighbors(int grid_arr[20][20], int x, int y, int nei_arr[300][2], int & lastindex_nei) //function to store all neighbors of alive cells without repitition check
{
	//a single live cell (x,y) can only have eight neighbours i.e. (x-1,y-1), (x, y-1),(x+1,y-1), (x-1,y), (x+1,y), (x-1,y+1), (x, y+1), (x+1,y+1)
	int repitition_check;  //variable for duplication check
	if (grid_arr[x - 1][y - 1] == 0)  //storing coordinates of 1st neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x - 1 && nei_arr[i][1] == y - 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x - 1 ;   //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y - 1;    //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x - 1][y] == 0)   //storing coordinates of 2nd neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x - 1 && nei_arr[i][1] == y)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x - 1;    //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y;        //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x - 1][y + 1] == 0)   //storing coordinates of 3rd neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x - 1 && nei_arr[i][1] == y + 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x - 1;      //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y + 1;      //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x][y - 1] == 0)    //storing coordinates of 4th neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x && nei_arr[i][1] == y - 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x;      //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y - 1;    //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x][y + 1] == 0)    //storing coordinates of 5th neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x && nei_arr[i][1] == y + 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x;   //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y + 1;   //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x + 1][y - 1] == 0)    //storing coordinates of 6th neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x + 1 && nei_arr[i][1] == y - 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x + 1;     //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y - 1;     //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x + 1][y] == 0)    //storing coordinates of 7th neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x + 1 && nei_arr[i][1] == y)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x + 1;     //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y;        //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	if (grid_arr[x + 1][y + 1] == 0)    //storing coordinates of 8th neighbor
	{
		repitition_check = 0;
		for (int i = 0; i <= 299; i++)
		{
			if (nei_arr[i][0] == x + 1 && nei_arr[i][1] == y + 1)
			{
				repitition_check+=1;
			}
		}

		if (repitition_check < 1)
		{
			for(int j=0;j<2;j++)
			{
				if(j==0)
				nei_arr[lastindex_nei][j] = x + 1;    //stores x coordinate of neighbor
				if(j==1)                
				nei_arr[lastindex_nei][j] = y + 1;    //stores y coordinate of neighbor
			}
			lastindex_nei+=1;
		}
	}

	return lastindex_nei;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int counting_live_neighbors(int grid_arr[20][20], int x_coord, int y_coord)  //function for counting alive neighbors in the grid
{
	int alive = 0;                              	
	if (grid_arr[x_coord - 1][y_coord - 1] == 1) 
	{
		alive+=1;
	}	
	if (grid_arr[x_coord][y_coord - 1] == 1) 
	{
		alive+=1;
	}		
	if (grid_arr[x_coord + 1][y_coord - 1] == 1) 
	{
		alive+=1;
	}		
	if (grid_arr[x_coord - 1][y_coord] == 1) 
	{
		alive+=1;
	}	
	if (grid_arr[x_coord + 1][y_coord] == 1) 
	{
		alive+=1;
	}			
	if (grid_arr[x_coord - 1][y_coord + 1] == 1) 
	{
		alive+=1;
	}	
	if (grid_arr[x_coord][y_coord + 1] == 1) 
	{
		alive+=1;
	}		
	if (grid_arr[x_coord + 1][y_coord + 1] == 1) 
	{
		alive+=1;
	}	
	return alive;    //returns number of alive neighbors of certain cell
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void next_generation(int secondary_array[100][2], int grid_arr[20][20], int gen_num, int &lastindex_sec, int & lastindex_nei, int nei_arr[300][2])   //function for implemnting game rules
{
	int alive_neighbors, upgraded_Grid[20][20] = {0};
	for (int i = 0; i < gen_num; i++)   //external most loop for controling number of generations
	{
		if(i==0)
		cout << setw(36)<<"GENERATION : " << i + 1 << "st " << endl;    //naming for each generation
		else if(i==1)
		cout << setw(36)<<"GENERATION : " << i + 1 << "nd " << endl;    //naming for each generation
		else if(i==2)                                               
		cout << setw(36)<<"GENERATION : " << i + 1 << "rd " << endl;    //naming for each generation
		else
		cout << setw(36)<<"GENERATION : " << i + 1 << "th " << endl;    //naming for each generation
		
			for (int i = 0 ; i <= 19; i++)    //loop to control y axis of grid
			{
				for (int j = 0; j <= 19; j++) //loop to control x axis of grid
				{
					
					if (grid_arr[i][j] != 0)
					{
						alive_neighbors = counting_live_neighbors(grid_arr, i, j);  // function call for counting alive neighbors of current coordinates

						if (alive_neighbors != 3 && alive_neighbors != 2 )   //condition to check cell future life
						{
							lastindex_sec-=1;    //index update
							upgraded_Grid[i][j] = 0;     //cell initilization with 0 if it fails to survives according to rules of lonliness or over crowding
							
							for (int k = 0; k <= 99; k++)    
							{
								if (i == secondary_array[k][0] && j == secondary_array[k][1])
								{
									for (int l = k; l <= 99; l++)
									{
										for(int m=0; m<2;m++)
										{
											if(m==0)
											secondary_array[l][m] = secondary_array[l + 1][m];   //secondary array update x coordinate
											if(m==1)
											secondary_array[l][m] = secondary_array[l + 1][m];   //secondary array update y coordinate
										}
				
									}
								}
							}
						}	
					}
				}
			}
			
			
			
			
		for (int i = 0; i <= 19; i++)   //loop to control grid y axis
		{
			for (int j = 0; j <= 19; j++)  // loop to control grid x axis
			{
				if (grid_arr[i][j] != 0)  // condition to check cell aliveness
				{
					alive_neighbors = counting_live_neighbors(grid_arr, i, j);    //function call to count alive neighbors

					if (alive_neighbors == 2 || alive_neighbors == 3) 
					{
						upgraded_Grid[i][j] = 1;    //cell sustaination if it survives
					}
				}
			}
		}

		for (int i = 0; i <= 19; i++)   //loop to control grid y axis
		{
			for (int j = 0; j <= 19; j++)   //loop to control grid x axis
			{
				if (grid_arr[i][j] != 1 )  //condition to check if cell is dead
				{
					alive_neighbors = counting_live_neighbors(grid_arr, i, j);

					if (alive_neighbors == 3)
					{
						upgraded_Grid[i][j] = 1;   //cell addition id it fullfills conditions
						lastindex_sec+=1;     //index upgrade

						for(int k=0; k<2;k++)
						{
							if(k==0)
							secondary_array[lastindex_sec][k] = i;   //update x coordinate
							if(k==1)
							secondary_array[lastindex_sec][k] = j;    //update y coordinate
						}
					}
				}
			}
		}

		
		Grid_display(upgraded_Grid);  //function call to dispaly grid

		display_secondaryarray(secondary_array, lastindex_sec);  // function call to display secondary array

		for (int i = 0; i < 300; i++) //loop to udate neighbor array
		{
			for(int j=0; j<2;j++)
			{
				if (j==0)
				nei_arr[i][j] = 0;    //update x coordinate
				if (j==1)
				nei_arr[i][j] = 0;    //update y coordinate
			}
		}

		int temp_storage;
		int lastindexnei_updated = -1;

		for (int i = 0; i <= lastindex_sec; i++)
		{
			temp_storage = adding_neighbors(upgraded_Grid, secondary_array[i][0], secondary_array[i][1], nei_arr, lastindexnei_updated );  //function call to counting neighbors
			lastindexnei_updated = temp_storage;    //updated last index of neighbor array

		}

		display_neiarray(nei_arr, lastindexnei_updated);  // function call to display neighbor array
			
			for (int i = 0; i <= 19; i++)  
			{
				for (int j = 0; j <= 219; j++)
				{
					grid_arr[i][j] = upgraded_Grid[i][j];
				}
			}
		}
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void display_secondaryarray(int secondary_array[100][2], int &lastindex_secondary) //function to display secondary array after each grid display of generation
{
	cout << "Secondary Array : [   ";
	for (int i = 0; i <= lastindex_secondary; i++) 
	{ 
		for(int j=0; j<2;j++)
		{
			if(j==0)
			cout <<"("<<secondary_array[i][j] << ",";   //displays x coordinate
			if(j==1)
			cout << secondary_array[i][j] << ")    ";   //displays y coordinate
		}
	} 
	cout<< "]"<<endl;
	cout<<"Last index of secondary array : " << lastindex_secondary<<endl;    //displays last index of the secondary array
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void display_neiarray(int nei_arr[][2], int& lastindex_nei)    //function to display neighbor array array after each grid display of generation
{
	cout << "Neighbour array : [   ";

	for (int i = 0; i < lastindex_nei; i++)
	{
		for(int j=0; j<2;j++)
		{
			if(j==0)
			cout <<"("<<nei_arr[i][j] << ",";    //displays x coordinate
			if(j==1)
			cout << nei_arr[i][j] << ")    ";    //displays y coordinate
		}
	}
	cout<< "]"<<endl;
	cout << "Last index of Neighbor array : " << lastindex_nei - 1 << endl;   //displays last index of the neighboring array
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void file_writing(int secondary_array[100][2], int gen_num, int &lastindex_sec)  // function to display output of alive cell coordinates in a file 
{
	ofstream writefile("Output.txt");   //obh=ject creation and opening the output text file     
	writefile << gen_num << endl;    //displays the total number of generations
	writefile << lastindex_sec+1<<endl;   //displays the number of alive cells in the output text file
	for (int i = 0; i<=lastindex_sec; i++) 
	{
		for(int j=0; j<2;j++)
		{
			if(j==0)
			writefile << secondary_array[i][j] << "  ";    // displays x coordinate of each alive cell
			if(j==1)
			writefile << secondary_array[i][j] <<endl;    //displays y coordinate of each alive cell
		}
	}
	writefile.close();   // closes output text file
}

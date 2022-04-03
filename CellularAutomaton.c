#include <stdio.h>
#define MAX_STATE 8
//Setting the console's font size as 10 was enough to see the shapes and sentences in my screen. I may recommend it also for your screen.
void initialize_array(int cell_array[], int size);
void create_rule_table(int rule_number,int rule_table[][2]);
void print_rule_table(int rule_table[][2]);
void print_state(int state_to_print[], int size);
int  calculate_next_state(int left_cell,int middle_cell,int right_cell,int rule_table[][2]);
void swap_arrays(int current_state[],int next_state[],int size);

int main(void)
{
	int array_size,rule_number,generation_num;  //they will be typed by a user.
	do{
		printf("Type a number for the number of cells(min 25-max 120): ");
		scanf("%d",&array_size);
	}while(array_size<25 || array_size>120);   //you may change this interval if you desire. It is just for a better shape in this console font size.

	int current_state[array_size],next_state[array_size];   // Arrays to hold the current and the next state of all cells was declarated.
 	initialize_array(current_state,array_size);				//Current_state array is initialiazed by this function.

 	do{
 		printf("Type a rule number(between 0 and 255): ");
		scanf("%d",&rule_number);
	}while(rule_number<0 || rule_number>255);
	int rule_table[MAX_STATE][2];  //this is a necessary 2D array to create a rule table which is for calculating next state.
	create_rule_table(rule_number,rule_table);  //The necessary rule table is created by this function.

 	do{
 		printf("Type how many generation you want to see (min 1-max 100): ");
 		scanf("%d",&generation_num);
 	}while(generation_num <= 0 || generation_num > 100); //Again, you may change it if you want.

 	print_rule_table(rule_table);    		//it will show the rule to user after the inputs are taken.
 	print_state(current_state,array_size); //Initial state of the cells will be printed after the rule table is printed.

 	int generation_count=0,cell_n,left,right,middle;
 	while(generation_count < generation_num)
 	{
 		printf("\n");
 		for(cell_n=0;cell_n<array_size;cell_n++)	//it will start from the first cell and end when it is the last cell.
 		{
 			if(cell_n==0)   //Therefore, if it is the first cell, it will take the last cell as the left cell.
 			{
 				left= current_state[array_size-1];
 				middle= current_state[cell_n];
 				right= current_state[cell_n+1];
 				next_state[cell_n]= calculate_next_state(left,middle,right,rule_table);
			}
 			else if(cell_n==array_size-1)   //Same, if it is the last cell, it will take the first cell as the right cell.
			{
				left= current_state[cell_n-1];
 				middle= current_state[cell_n];
 				right= current_state[0];
 				next_state[cell_n]= calculate_next_state(left,middle,right,rule_table);
			}
			else  //And, this part will be applied for the other cells.
			{
 				left= current_state[cell_n-1];
 				middle= current_state[cell_n];
 				right= current_state[cell_n+1];
 				next_state[cell_n]= calculate_next_state(left,middle,right,rule_table);
 			}
		}
		print_state(next_state,array_size); //Here, the generation is printed.
		swap_arrays(current_state,next_state,array_size);   //Here,current state of all cells is changed with their next state for the next repetition.
		generation_count++;
	}
	return 0;
}
void initialize_array(int cell_array[], int size)
{
	int cell_n,middle_point;	 //cell value in the middle point will be assigned to 1, and rest of them will be 0.
	if(size%2== 1)
		middle_point= size/2;    //cell in the middle point can be found like this if size is an odd number.
	else
		middle_point= size/2-1;  //cell in the middle pooint can be found like this if size is an even number.
	for(cell_n=0;cell_n<size;cell_n++)
	{
		if(cell_n == middle_point)
			cell_array[cell_n]= 1;
		else
			cell_array[cell_n]= 0;
	}
}
void create_rule_table(int rule_number,int rule_table[][2])
{
	int next_state=rule_number;  //this is for generating a rule without playing user's input.
	int row,column;
	/*
		First column will hold the states of 3 cells but it will be in decimal system(111=7,110=6.....000=0).
		Second column will hold the next state of the cell in the middle according to rule number.
	*/
	for(row=0;row<MAX_STATE;row++)
		for(column=0;column<2;column++)
				if(column==0)
					rule_table[row][column]= row;
				else
				{
					rule_table[row][column] = next_state % 2;   //this statement assigns the next state of the cell in the middle to second column.
					next_state = next_state/2;  	//this statement update the next_state value to calculate the binary equivalent of the rule number correctly.
				}
	//this will create the rule table of any rules.
}
void print_rule_table(int rule_table[][2])
{
	int row,column;
	printf(" Current State(decimal)	   Next State\n");
	printf("-------------------------------------\n");
	for(row=0;row<MAX_STATE;row++)
	{
		for(column=0;column<2;column++)
			printf("\t%d\t\t",rule_table[row][column]);

		printf("\n");
	}
}
void print_state(int array[],int size)
{
	int cell_n;
	for(cell_n=0;cell_n<size;cell_n++)
	{
		if(array[cell_n]==1)
			printf("# ");   //for 1, print this shape.
		else
			printf("  ");	//for 0, print this.
	}
}
int calculate_next_state(int left_cell,int middle_cell,int right_cell,int rule_table[][2])
{
	int state,new_state,state_iterator;
	state= left_cell*4 + middle_cell*2 + right_cell*1;   //4 comes from 2^2, 2 from 2^1, 1 from 2^0.
	/*
		Here, the state of the middle cell value is converted to decimal system.
		Now, I will use the rule_table that I have created above.
		It holds the all possible states of each 3 cells in decimal system in the first column
		and the second column holds the next state of the middle cell according to rule number.
	*/
	for(state_iterator=0;state_iterator<MAX_STATE;state_iterator++)
		if(state == rule_table[state_iterator][0])
		{
			new_state= rule_table[state_iterator][1];  //new state of the middle cell is found when the state is matched.
			break;
		}

	return new_state;
}
void swap_arrays(int current_state[],int next_state[],int size)
{
	int cell_n;
	for(cell_n=0;cell_n<size;cell_n++)
		current_state[cell_n]= next_state[cell_n];
		//it is just changing each cell state value in the old state array with each cell state value in the new state array.
}


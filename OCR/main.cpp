#include <iostream>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <windows.h>

#include "../BackPropagation/network.h"

using namespace std;

int letters[26][7][5]={
				   {{0,1,1,1,0},
				  	{1,0,0,0,1},
				  	{1,0,0,0,1},
				  	{1,1,1,1,1},
				  	{1,0,0,0,1},
				  	{1,0,0,0,1},
				  	{1,0,0,0,1}},
				  	
				   {{1,1,1,1,0},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,1,1,1,0},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,1,1,1,0}},
					
				   {{0,1,1,1,0},
					{1,0,0,0,1},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,0,0,0,1},
					{0,1,1,1,0}},
					
				   {{1,1,1,1,0},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,1,1,1,0}},
				   
				   {{1,1,1,1,1},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,1,1,1,0},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,1,1,1,1}},
					
				   {{1,1,1,1,1},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,1,1,1,0},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,0,0,0,0}},
					
				   {{0,1,1,1,0},
					{1,0,0,0,1},
					{1,0,0,0,0},
					{1,0,0,0,0},
					{1,0,0,1,1},
					{1,0,0,0,1},
					{0,1,1,1,0}},
					
				   {{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,1,1,1,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1}},
					
				   {{0,1,1,1,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,1,1,1,0}},
					
				   {{0,0,1,1,1},
					{0,0,0,1,0},
					{0,0,0,1,0},
					{0,0,0,1,0},
					{0,0,0,1,0},
					{1,0,0,1,0},
					{0,1,1,0,0}},
					
				   {{1,0,0,0,1},
					{1,0,0,1,0},
					{1,0,1,0,0},
					{1,1,0,0,0},
					{1,0,1,0,0},
					{1,0,0,1,0},
					{1,0,0,0,1}},
					
				   {{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,1,1,1,1}},
				   	
				   {{1,0,0,0,1},
					{1,1,0,1,1},
					{1,0,1,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1},
					{1,0,0,0,1}},
					
				   {{1,0,0,0,1},
					{1,0,0,0,1},
					{1,1,0,0,1},
					{1,0,1,0,1},
					{1,0,0,1,1},
					{1,0,0,0,1},
					{1,0,0,0,1}},
					
				   {{0,1,1,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,1,1,0}},
				   	
				   {{1,1,1,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,1,1,1,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0},
				   	{1,0,0,0,0}},
				   	
				   {{0,1,1,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,1,0,1},
				   	{1,0,0,1,0},
				   	{0,1,1,0,1}},
				   	
				   {{1,1,1,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,1,1,1,0},
				   	{1,0,1,0,0},
				   	{1,0,0,1,0},
				   	{1,0,0,0,1}},
				   	
				   {{0,1,1,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,0},
				   	{0,1,1,1,0},
				   	{0,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,1,1,0}},
				   	
				   {{1,1,1,1,1},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0}},
					
				   {{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,1,1,0}},
				   	
				   {{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,0,1,0},
				   	{0,1,0,1,0},
				   	{0,0,1,0,0}},
				   	
				   {{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{1,0,1,0,1},
				   	{1,0,1,0,1},
				   	{1,0,1,0,1},
				   	{0,1,0,1,0}},
				   	
				   {{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,0,1,0},
				   	{0,0,1,0,0},
				   	{0,1,0,1,0},
				   	{1,0,0,0,1},
				   	{1,0,0,0,1}},
				   	
				   {{1,0,0,0,1},
				   	{1,0,0,0,1},
				   	{0,1,0,1,0},
				   	{0,0,1,0,0},
				   	{0,0,1,0,0},
				   	{0,0,1,0,0},
				   	{0,0,1,0,0}},
				   	
				   {{1,1,1,1,1},
				   	{0,0,0,0,1},
				   	{0,0,0,1,0},
				   	{0,0,1,0,0},
				   	{0,1,0,0,0},
				   	{1,0,0,0,0},
				   	{1,1,1,1,1}}};
					
void cls()
{
	COORD coor;
	coor.X=0;
	coor.Y=0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coor);
}

int main()
{
	srand(time(NULL));
	
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
	
	const int NUM_INPUTS = 35;
	const int NUM_HIDDEN_LAYERS = 2;
	const int NUM_HIDDENS[] = {20, 20};
	const int NUM_OUTPUTS = 26;
	const double LEARNING_RATE = 0.1;
	
	Network train(NUM_INPUTS,NUM_HIDDEN_LAYERS,NUM_HIDDENS,NUM_OUTPUTS,LEARNING_RATE);	//inputs, hidden, outputs, rate
	
	double inputs[NUM_INPUTS],target[NUM_OUTPUTS];
	double hidden_outputs[NUM_HIDDENS[NUM_HIDDEN_LAYERS-1]],outputs[NUM_OUTPUTS];
	double hidden_errors[NUM_HIDDENS[NUM_HIDDEN_LAYERS-1]],output_errors[NUM_OUTPUTS];
	double prev_error;
	
	getch();
	system("cls");
	
	bool state=true;
	long turn=0;
	unsigned int start=clock();
	unsigned int current = 0;
	float speed = 2.0f;
	
	int target_index=0, output_index=0, count=0, actual_count=0, round=0;
	
	while(true)
	{
		
		if(kbhit())
		{
			int input = getch();
			if(input==27)
				break;
			else if(input=='d')
				speed*=2.0f;
			else if(input=='a')
				speed/=2.0f;
			else if(input=='p')
			{
				cout << endl;
				train.print_weights();
				input=getch();
				if(input==27)
					break;
				system("cls");
				state = true;
				continue;
			}
			else if(input!=13)
				state = !state;
			else
			{
				cout << "\nEnter your condition:" << endl;
				for(int i=0;i<NUM_INPUTS;i++)
					cin >> inputs[i];
				
				train.feedforward(inputs);
				train.get_outputs(outputs);
				
				output_index=0;
				for(int i=1;i<26;i++)
					if(outputs[i]>outputs[output_index])
						output_index=i;
				
				cout << endl;
				for(int i=0;i<7;i++)
				{
					for(int j=0;j<5;j++)
						cout << (inputs[i*5+j]?" x":"  ");
					cout << endl;
				}
				
				cout << "\nNeural output -- " << endl;
				cout << "Answer: ";
				for(int i=0;i<5;i++)
				{
					output_index=0;
					for(int j=0;j<26;j++)
						if(outputs[j]>outputs[output_index])
							output_index=j;
					cout << static_cast<char>(output_index + 'A') << "   " << outputs[output_index] << "   ";
					outputs[output_index]=0;
				}
				cout << endl;
						
				input=getch();
				if(input==27)
					break;
				system("cls");
				state = true;
				continue;
			}
		}

		for(int i=0;i<7;i++)
			for(int j=0;j<5;j++)
				inputs[i*5+j]=letters[turn%26][i][j];
		
		for(int i=0;i<26;i++)
			target[i]=(turn%26==i);
			
		train.feedforward(inputs);
		train.feedback(target);
		train.get_outputs(outputs);
		train.get_output_errors(output_errors);
		train.get_hidden_outputs(NUM_HIDDEN_LAYERS-1,hidden_outputs);
		train.get_hidden_errors(NUM_HIDDEN_LAYERS-1,hidden_errors);
		
		output_index=0;
		for(int i=1;i<26;i++)
			if(outputs[i]>outputs[output_index])
				output_index=i;
		if(outputs[output_index] < 0.9)
			actual_count++;
		if((turn%26) != output_index)
			count++;
	
		if(clock()-current>(1000/speed) && state)
		{
			current=clock();
			cls();
			cout <<  "Speed: " << speed << "x   Time: " << (clock()-start)/1000 << "s   Turns: " << turn << "\n" << endl;
			cout << "Number of inputs: " << NUM_INPUTS << "   Number of outputs: " << NUM_OUTPUTS << "   Learning rate: " << LEARNING_RATE << endl;
			cout << "Number of hidden layers: " << NUM_HIDDEN_LAYERS << endl;
			for(int i=0;i<NUM_HIDDEN_LAYERS;i++)
				cout << "[" << i << "]: " << NUM_HIDDENS[i] << "   ";
			cout << "\n" << endl;
			
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<5;j++)
					cout << (inputs[i*5+j]?" x":"  ");
				cout << endl;
			}
			cout << endl;
			
			cout << "Target: ";
			cout << static_cast<char>(turn%26 + 'A') << endl;
			
			cout << "Output: ";
			
			for(int i=0;i<5;i++)
			{
				output_index=0;
				for(int j=0;j<26;j++)
					if(outputs[j]>outputs[output_index])
						output_index=j;
				cout << static_cast<char>(output_index + 'A') << "   " << outputs[output_index] << "   ";
				outputs[output_index]=0;
			}
			cout << "\n" << endl;

			cout << "Error count: " << setw(10) << count << "       Rounds: " << round << "          " << endl;
			cout << "Error rates: " << setw(10) << 100.0*count/round << " %              \n" << endl;
			cout << "Actual error count: " << setw(10) << actual_count << endl;
			cout << "Actual error rates: " << setw(10) << 100.0*actual_count/round << " %          " << endl;
			
			count=round=actual_count=0;
			//train.print_weights();
		}
		prev_error = output_errors[0];
		turn++;
		round++;
	}
	
	cout << "\n\nErrors[0]: " << setw(10) << output_errors[0] << "   Errors[1]: " << setw(10) << output_errors[1] << "\n" << endl;
	return 0;
}

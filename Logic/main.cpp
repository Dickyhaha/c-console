#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>


using namespace std;

int main()
{
	srand(time(NULL));
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
	
	int layers[] = {1};
	double inputs[2];
	double target[1];
	double output[1];
	int count=0,round=0;
	
	/*Network train(2,1,layers,1,0.1);
	getch();
	system("cls");
	
	unsigned int time = 0;
	
	while(!kbhit())
	{
		inputs[0]=rand()%2;
		inputs[1]=rand()%2;
		target[0]=inputs[0]&&inputs[1];//(inputs[0]&&!inputs[1])||(!inputs[0]&&inputs[1]);
		train.feedforward(inputs);
		train.feedback(target);
		if(target[0] != (output[0]>0.5))
			count ++;
		round++;
		if(clock()-time>500)
		{
			system("cls");
			time = clock();
			train.get_outputs(output);
			cout << inputs[0] << " " << inputs[1] << endl;
			cout << (output[0] > 0.5) << " " << target[0] << endl;
			cout << count << "/" << round << endl;
			count = round = 0;
		}
	}
	*/
	return 0;
}

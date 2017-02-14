#include <cstdlib>
#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
    char input=0;
    char words[20];
    FILE * file;
    file = fopen("ignoreme.bday","w+");
	printf("<R>ead file / <W>rite file");
	while(1)
	{
	    input=getch();
	    if(input=='r')
	    {
	        fscanf(file,"%s",words);
	        cout<<"\n"<<words<<"\n";
	        break;
	    }
	    else if(input=='w')
	    {
	        cout<<"\n\nWrite below: \n\n";
	        cin.getline(words,20*sizeof(char));
	        fprintf(file,"%s",words);
	        break;
	    }
	}
    printf("\nDone");
    getch();
    fclose(file);
    return EXIT_SUCCESS;
}

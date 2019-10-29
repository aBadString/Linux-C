#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "menu.h"
#include "perm.h"

int main(int argc, char *argv[])
{
	int id = 0;
	
	do
	{
		id = Menu();
		switch(id)
		{
		case 0:
			break;
		case 1:
			CreateFile();
			break;
		case 2:
			WriteFile();
			break;
		case 3:
			ReadFile();
			break;
		case 4:
			Change();
			break;
		case 5:
			Look();
			break;
		case 6:
			About();
			break;
		default:
			printf("error");
		}
		ToContinue();
	}while(id != 0);

	return 0;
}

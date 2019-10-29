#include "menu.h"

void ToContinue()
{
	printf("按回车继续");
	while (getchar() != '\n')
	{
		continue;
	}
}

int Menu()
{
	int id = 0;

	system("clear");
	printf("*****************************\n");
	printf("    0. 退出\n");
	printf("    1. 创建新文件\n");
	printf("    2. 写文件\n");
	printf("    3. 读文件\n");
	printf("    4. 修改文件权限\n");
	printf("    5. 查看当前文件的权限\n");
	printf("    6. 关于\n");
	printf("*****************************\n");
	
	printf("Please input your choice(0-6): ");
	id = getchar() - 48;
	
	while (getchar() != '\n')
	{
		continue;
	}
	
	return id;
}

int About()
{
	printf("姓名：冷劲松\n");
	printf("学号：8002117172\n");
	printf("班级：软工1705\n");
	printf("版本：0.0.0\n");
	printf("功能：创建和读写文件，查看和修改文件权限\n");
	return 0;
}

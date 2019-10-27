#include "file_in.h"

/* 创建文件 */
int CreateFile()
{
	FILE *fp;
	char filename[STR_SIZE];
	
	printf("文件名: ");
	gets(filename);
	
	if((fp = fopen(filename, "r")) == NULL)
	{
		if((fp = fopen(filename, "w+")) == NULL)
		{
			printf("文件创建失败\n");
			return -1;
		}
		else
		{
			printf("文件创建成功\n");
			fclose(fp);
			return 0;
		}
	}
	else
	{
		printf("文件已存在\n");
		fclose(fp);
		return -1;
	}
}

/* 写文件 */
int WriteFile()
{
	FILE *fp;
	char filename[STR_SIZE];
	char buffer[BUFFER_SIZE];
	char ch;
	int i;
	
	printf("文件名: ");
	gets(filename);
	
	if((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	else
	{
		for(i = 0; (ch = getchar()) != EOF; )
		{
			if(i < BUFFER_SIZE-1)
			{
				buffer[i] = ch;
				i++;
			}
			else
			{
				buffer[i] = '\0'; // i == BUFFER_SIZE-1
				i = 0;
				if(fputs(buffer,fp) == -1)
				{
					printf("写入失败\n");
					fclose(fp);
					return -1;
				}
			}
		}
		buffer[i] = '\0';
		if(fputs(buffer,fp) == -1)
		{
			printf("写入失败\n");
			fclose(fp);
			return -1;
		}
		else
		{
			printf("写入成功\n");
			fclose(fp);
			return 0;
		}
	}
}

/* 读文件 */
int ReadFile()
{
	FILE *fp;
	char filename[STR_SIZE];
	char ch;
	
	printf("文件名: ");
	gets(filename);
	
	if((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	else
	{
		while((ch = fgetc(fp)) != EOF)
		{
			putchar(ch);
		}
		fclose(fp);
		return 0;
	}
}

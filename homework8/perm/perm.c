#include "perm_in.h"

/* 修改文件权限 */
int Change()
{
	char filename[STR_SIZE];
	int mode;
	
	printf("文件名: ");
	gets(filename);
	printf("权限: ");
	scanf("%d", &mode);
	while (getchar() != '\n'){continue;}
	
	if(mode > 777 || mode < 0) // 验证要设置的权限是否合法
	{
        printf("权限不正确\n"); 
        return -1;
    }
    else
    {
    	mode = (mode/100)*8*8 + (mode/10%10)*8 + (mode%10); // 转换为八进制
    	if(chmod(filename, mode) == -1)
    	{
        	printf("权限设置失败\n");
        	return -1;
    	}
    	else
    	{
    		return 0;
    	}
    }
}

/* 查看文件权限 */
int Look()
{
	char filename[STR_SIZE];
	char strPerm[STR_SIZE];
	struct stat sta;
	
	printf("文件名: ");
	gets(filename);
	
	if(lstat(filename, &sta) == -1)
	{
		printf("读取权限失败\n");
		return -1;
	}
	else
	{
		getPermission(sta.st_mode, strPerm);
		printf("%s\n", strPerm);
		return 0;
	}
}

static int getPermission(mode_t mode,char strPerm[])
{
	mode_t perm = 256; // 256 == 100 000 000
	char temp[10] = {
		'-','-','-',
		'-','-','-',
		'-','-','-',
		'\0'
		};
	char RWX[4] = {'-','r','w','x'};
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 1; j <= 3; j++)
		{
			if ((perm & mode) != 0)
			{
				temp[(i*3)+j-1] = RWX[j];
			}
			perm = perm >> 1;
		}
	}
	strcpy(strPerm, temp);
	
	return 0;
}

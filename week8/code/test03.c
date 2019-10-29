#include <stdio.h>
#include <malloc.h>

void print(char*, int);

int main()
{
	char *s1 = "abcde";
	char *s2 = "abcde";
	char s3[] = "abcd";
	long int *s4[100];
	char *s5 = "abcde";
	int a = 5;
	int b = 6;
	
	printf("variables address in main function: s1=%p  s2=%p s3=%p s4=%p s5=%p a=%p b=%p \n\n", s1,s2,s3,s4,s5,&a,&b);   
	printf("variables address in processcall:\n");    
	print("ddddddddd",5);//参数入栈从右至左进行,p先进栈,str后进 &p>&str    
	printf("main=%p print=%p \n",main,print);  
}

void print(char *str, int p)
{
	char *s1 = "abcde";
	char *s2 = "abcde";
	char s3[] = "abcdeee";
	long int *s4[100];
	char *s5 = "abcde";
	int a = 5;
	int b = 6;
	int c;
	int d;
	char *q = str;
	int m = p;
	char *r = (char*)malloc(1);
	char *w = (char*)malloc(1);
	
	printf("s1=%p s2=%p s3=%p s4=%p s5=%p a=%p b=%p c=%p d=%p str=%p q=%p p=%p m=%p r=%p w=%p \n\n", s1,s2,s3,s4,s5,&a,&b,&c,&d,&str,q,&p,&m,r,w);   
	/* 栈和堆是在程序运行时候动态分配的，局部变量均在栈上分配。 
	栈是反向增长的，地址递减；malloc等分配的内存空间在堆空间。堆是正向增长的，地址递增。   
	r,w变量在栈上(则&r>&w)，r,w所指内容在堆中(即r<w)。*/ 
}

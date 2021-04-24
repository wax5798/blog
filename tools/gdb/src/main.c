/*************************************************************************
	> File Name: main.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月18日 星期日 18时06分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int addFunc(int a, int b);

static void localFunc()
{
	printf("[%s, %d] debug here\n", __func__, __LINE__);
}

int main(int argc, char *argv[])
{
	int a = 1, b = 2, c = 0;
	int *p = &a;

	localFunc();
	c = addFunc(a, b);

	printf("a = %d, b = %d, c = %d, *p = %d\n", a, b, c, *p);
	return 0;
}

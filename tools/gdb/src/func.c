/*************************************************************************
	> File Name: func.c
	> Author: Wan Xiangjun
	> Mail: 
	> Created Time: 2021年04月18日 星期日 18时08分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void localFunc()
{
	printf("[%s, %d] debug here\n", __func__, __LINE__);
}

int addFunc(int a, int b)
{
	localFunc();
	return a + b;
}

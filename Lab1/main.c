#include <stdio.h>
#include "add.h"

int main(void)
{
    int i = add(1, 2);

    /* %d == ����, %s == ���ڿ� */
    printf("Hello world + %d \n", i);

    return i;
}

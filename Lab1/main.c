#include <stdio.h>
#include "add.h"

int main(void)
{
    int i = add(1, 2);

    /* %d == 정수, %s == 문자열 */
    printf("Hello world + %d \n", i);

    return i;
}

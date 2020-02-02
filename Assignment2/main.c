#include <stdio.h>
#include "translate.h"

int main(int argc, const char* argv[])
{
    int result;

    result = translate(argc, argv);
    fprintf(stderr, "Error Code: %d \n", result);

    return result;
}

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "my_string.h"

int main(void)
{
    const char* str = "We all live in a yellow submarine";
    char str_cpy[34];
    char* token;
    char test[1];


    strncpy(str_cpy, str, 33);
    str_cpy[33] = '\0';

    test[0] = '\0';
    reverse(test);
    reverse(str_cpy);
    assert(strcmp("enirambus wolley a ni evil lla eW", str_cpy) == 0);
    printf("%d\n", index_of(str, "all "));

    assert(index_of(str, "all ") == 3);

    assert(index_of(str, "marine") == 27);
    assert(index_of(str, "all good") == -1);
    assert(index_of(str, "marinett") == -1);
    assert(index_of(str, "a") == 3);
    assert(index_of(str, "sub") == 24);
    assert(index_of(str, "live") == 7);
    printf("%d\n", index_of(NULL, NULL));
    assert(index_of(str, "") == 0);
    assert(index_of(test, "live") == -1);

    reverse(str_cpy);

    assert(strcmp(str_cpy, str) == 0);

    reverse_by_words(str_cpy);
    printf("rbw: %s \n", str_cpy);
    assert(strcmp("eW lla evil ni a wolley enirambus", str_cpy) == 0);
    reverse_by_words(str_cpy);

    reverse_by_words(test);
    printf("test pass;\n");

    assert(strcmp(str_cpy, str) == 0);

    assert(tokenize(NULL, " ") == NULL);

    token = tokenize(test, " ");
    printf("test pass;\n");

    token = tokenize(str_cpy, " ");
    assert(token == str_cpy);
    assert(strcmp(token, "We") == 0);

    token = tokenize(NULL, " ");
    assert(token == str_cpy + 3);
    assert(strcmp(token, "all") == 0);

    token = tokenize(NULL, " ");
    assert(token == str_cpy + 7);
    assert(strcmp(token, "live") == 0);

    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 12);
    assert(strcmp(token, "ni") == 0);

    token = reverse_tokenize(NULL, " ");
    token = reverse_tokenize(NULL, " ");
    assert(token == str_cpy + 17);
    assert(strcmp(token, "wolley") == 0);

    token = reverse_tokenize(NULL, " ");
    printf("last: %s \n", token);
    assert(strcmp(token, "enirambus") == 0);

    {
        const char* str1 = "asdf,.. jfdsf";
        char str1_cpy[14];
        char* token1;
        size_t i;
        strncpy(str1_cpy, str1, 14);

        token1 = tokenize(str1_cpy, ",.");
        printf("tkn: %s, %s\n", token1, str1_cpy);

        token1 = tokenize(NULL, ",.");
        printf("tkn: %s, %s\n", token1, str1_cpy);

        token1 = tokenize(NULL, ",.");
        printf("tkn: %s, %s\n", token1, str1_cpy);

        token1 = tokenize(NULL, ",.");
        printf("tkn: %s, %s\n", token1, str1_cpy);

        for (i = 0; i < 14; ++i) {
            printf("char:%c, int:%d\n", str1_cpy[i], (int)str1_cpy[i]);
        }
    }

    printf("Complete");

	return 0;
}

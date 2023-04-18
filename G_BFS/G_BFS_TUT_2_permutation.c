#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFER = 1000;

void permutation(char *pre, char *s);

int main()
{
    char input[BUFFER];
    scanf("%s", input);

    permutation("", input);
    return 0;
}

void permutation(char *pre, char *s)
{
    int len = strlen(s);
    if (len < 2) {
        char result[BUFFER];
        strcpy(result, pre);
        strcat(result, s);
        puts(result);
        return;
    }
    for (int i = 0; i < len; ++i) {
        char new_pre[BUFFER], new_s[BUFFER];
        strcpy(new_pre, pre);
        strncat(new_pre, s+i, 1);

        strncpy(new_s, s, i);
        new_s[i] = '\0';
        if (i+1 < len) {
            strcat(new_s, s+i+1);
        }
        permutation(new_pre, new_s);
    }
}
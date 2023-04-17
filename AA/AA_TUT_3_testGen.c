#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    
    FILE *f;
    if ((f = fopen("AA_TUT_3_input_100000000.txt", "w")) == NULL) {
        printf("Error opening file!");
        return 1;
    }

    size_t sz;
    printf("Enter size: ");
    scanf("%llu", &sz);
    fprintf(f, "%llu ", sz);
    
    for (size_t i = 0; i < sz - 1; ++i) {
        fprintf(f, "%llu ", i+1);
    }
    fprintf(f, "0");
    fclose(f);
    return 0;
}

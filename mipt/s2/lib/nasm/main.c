#include "library.h"
#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    printf("%d", subroutine(a, b));

    return(0);
}

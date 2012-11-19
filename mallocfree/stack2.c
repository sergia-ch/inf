//#define DEBUG
#undef DEBUG

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node
{
    struct Node * next;
    Data data;
};

struct Node * top = NULL;

void stack_print(struct Node * s);
struct Node * stack_push(struct Node * s, Data x);
void stack_destroy(struct Node * s);

#endif

void stack_print(struct Node * s)
{
    if(!s)
    {
        printf("Empty stack\n");
        return;
    }

    struct Node * now;
    for(now = s; now != NULL; now = now->next)
        printf("%d ", now->data);

    printf("\n");
}

struct Node * stack_push(struct Node * s, Data x)
{
    struct Node * nitem = malloc(sizeof(struct Node));
    nitem->next = s;
    nitem->data = x;
    return(nitem);
}

void stack_destroy(struct Node * s)
{
    if(s != NULL)
    {
        if(s->next != NULL)
            stack_destroy(s->next);
        free(s);
    }
}

#ifdef DEBUG
int main()
{
    struct Node * sp = NULL;

    long long int i;

    for(;;)
    {
        sp = stack_push(sp, 5);
        sp = stack_push(sp, 19);
//        stack_print(sp);
        // 19 5
        sp = stack_push(sp, -2);
//        stack_print(sp);
        // -2 19 5

        stack_destroy(sp);

        sp = NULL;
    }

    return 0;
}
#endif

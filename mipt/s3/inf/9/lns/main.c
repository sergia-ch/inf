#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s source destination\n", argv[0]);
        return(-1);
    }

    if(symlink(argv[1], argv[2]) < 0)
    {
        printf("symlink failed [%s] -> [%s]\n", argv[1], argv[2]);
        return(-1);
    }

    return(0);
}

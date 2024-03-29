#include "common.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"
#include "multicast.h"
#include "myaes.h"
#include "myauth.h"
#include <string.h>

#define CMDERROR "Command is TOO long (ignored)!\n"

char name[MNAME], password[MPASSWORD];

int sd;

int main(int argc, char* argv[])
{   
    MD5_CTX md5handler;
    AESInit();
    authInfoReadFile();

    if(argc < 2)
    {
        printf("Usage: %s REAL_IFACE_IP\n", argv[0]);
        return(1);
    }

    broadcastMessage bm;

    printf("User: ");
    scanf("%s", bm.name);
    strcpy(bm.password, getpass("Password: "));

    //printf("[%s]", password);
    if(!authenticate(bm.name, bm.password))
    {
        fprintf(stderr, "Wrong username/password!\n");
        return(1);
    }

    printf("Welcome!\n");

    multicastInit(argv[1]);

    size_t size;

    int error = 0;

    void* cipher;
    int len;

    char buf[RXMAX];

    if(!fork())
    {
        for(;;)
            if((size = multicastRx(buf, RXMAX)) > 0)
            {
                len = size;
                void* plain = decryptMessageCheckHash(buf, &len);
                if(plain != NULL)
                {
                    if(len == sizeof(responseMessage) && *((char*) (plain + MD5_DIGEST_LENGTH)) == RESPONSE)
                    {
                        responseMessage resp = *(responseMessage*) plain;
                        printf("%s: %s", resp.hostname, resp.response);
                    }
                }
                else
                    fprintf(stderr, "not a response!\n");
            }
        return(0);
    }

    for(;;)
    {
        //fprintf(stderr, "$ ");
        if((size = read(STDIN_FILENO, bm.command, MCOMMAND - 1)) > 0)
        {
            if(bm.command[size - 1] != '\n')
            {
                write(STDOUT_FILENO, CMDERROR, sizeof(CMDERROR) - 1);
                error = 2;
            }
            else if(error > 0) error--;
            if(error == 0)
            {
                //bm.password[0] = 1;
                bm.command[size - 1] = 0;
                bm.type = COMMAND;
                //fprintf(stderr, "[%s]\n", bm.command);
                len = sizeof(bm);

                MD5(((void*) &bm) + MD5_DIGEST_LENGTH, sizeof(bm) - MD5_DIGEST_LENGTH, bm.md5digest);

                cipher = AESEncrypt((void*) &bm, &len);
                //printf("sending len=%d\n", len);

                multicastTx(cipher, len);
                //multicastTx(bm.command, size);
            }
        }
    }
}

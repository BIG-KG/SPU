#include "C:\MIPT\SPU\stack\stack_funk.h"

#include "C:\MIPT\SPU\stack\errors.h"

#include "C:\MIPT\SPU\stack\const.h"

#include <string.h>

void main_runner(FILE *openingFile)
{
        int command = -2;
        int64_t stc = stack_ctor();

        printf("2\n");

        int ip = 0;
        int commands[256] = {};

        printf("3\n");


        while (fscanf(openingFile ,"%d", &commands[ip]) != EOF){
            ip++;
        }

        int numOFComm = ip;
        ip = 0;

        while(ip < numOFComm){

            command = commands[ip];

            if      (command ==  1){
                ip++;
                push (stc, commands[ip]);
            }

            else if (command ==  2){
                push (stc, pop (stc) + pop (stc));

            }

            else if (command ==  3){
                push (stc, pop (stc) * pop (stc));
            }

            else if (command ==  4){
                int a = pop (stc);
                int b = pop (stc);
                push (stc, b - a);
            }

            else if (command ==  5){
                int a = pop (stc);
                int b = pop (stc);
                push (stc, b / a);
            }

            else if (command ==  0){
                printf ("%d", pop (stc));
            }

            else if (command == -1){
                break;
            }

            else{
                printf ("Syntax error _%d_", command);
                return;
            }

            ip++;
        }

        stack_dtor(stc);


}

int main(int argc, char *argv[])
{
    printf("0\n");

    FILE *readingFile = fopen (argv[1] , "r");

    printf("1\n");

    main_runner (readingFile);


    fclose(readingFile);

    return 0;
}

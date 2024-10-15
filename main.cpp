#include "C:\MIPT\SPU\stack\stack_funk.h"

#include "C:\MIPT\SPU\stack\errors.h"

#include "C:\MIPT\SPU\stack\const.h"

#include <string.h>

void main_runner(FILE *openingFile)
{
        int command = -2;
        int64_t stc = stack_ctor();

        while(1){

            if(fscanf (openingFile, "%d", &command) == EOF){
                return;
            }

            if      (command ==  1){
                int a = 0;
                fscanf (openingFile, "%d", &a);
                push (stc, a);
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
        }

        stack_dtor(stc);


}

int main(int argc, char *argv[])
{
    FILE *readingFile = fopen (argv[1] , "r");

    main_runner (readingFile);

    fclose(readingFile);

    return 0;
}

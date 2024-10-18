#include "C:\MIPT\SPU\stack\stack_funk.h"
#include "C:\MIPT\SPU\stack\errors.h"
#include "C:\MIPT\SPU\stack\const.h"

#include "C:\MIPT\SPU\onegin\onegin.h"

#include <string.h>

int file_to_array(int **commandsArray, int file);

enum SPU_commands{
    RET = -1,
    POP = 0,
    PSH = 1,
    ADD = 2,
    MUL = 3,
    SUB = 4,
    DIV = 5,
    LUK = 6,
    JMP = 7,
    JMPM,
    JMPL,
    JMPE,
    JMPME,
    JMPLE

};


void main_runner(int commandsFile)
{
        int64_t stc       = stack_ctor();
        int ip            = 0 ;
        int *commands     = NULL;
        int numOfCommands = 0 ;
        int registers[5]  = {};
        int a             = 0;
        int b             = 0;

        numOfCommands = file_to_array(&commands, commandsFile);

        for(int i = 0; i < numOfCommands; i ++){
            printf("_%d_\n", commands[i]);
        }

        printf("\n\n\n");

        while(ip < numOfCommands){

            commands[ip];

            switch (commands[ip]){
                case PSH:
                    ip++;
                    push (stc, commands[ip]);
                    break;

                case ADD:
                    push (stc, pop (stc) + pop (stc));
                    break;

                case MUL:
                    push (stc, pop (stc) * pop (stc));
                    break;

                case SUB:
                    a = pop (stc);
                    b = pop (stc);
                    push (stc, b - a);
                    break;

                case DIV:
                    a = pop (stc);
                    b = pop (stc);
                    push (stc, b / a);
                    break;

                case POP:
                    printf ("%d", pop (stc) );
                    break;

                case RET:
                    ip = numOfCommands + 1;  //easy break cycle, using while condition
                    break;

                case LUK:
                    printf ("%d", look (stc, 0));
                    break;

                case JMP:
                    ip = commands[ip + 1];
                    break;

                case JMPM:
                    a = pop (stc);
                    b = pop (stc);
                    if (a > b) ip = commands[ip + 1];
                    break;

                case JMPL:
                    a = pop (stc);
                    b = pop (stc);
                    if (a < b) ip = commands[ip + 1];
                    break;

                case JMPE:
                    a = pop (stc);
                    b = pop (stc);
                    if (a == b) ip = commands[ip + 1];
                    break;

                case JMPME:
                    a = pop (stc);
                    b = pop (stc);
                    if (a >= b) ip = commands[ip + 1];
                    break;

                case JMPLE:
                    a = pop (stc);
                    b = pop (stc);
                    if (a <= b) ip = commands[ip + 1];
                    break;

                default:
                    printf ("Syntax error _%d_", commands[ip]);
            }

            ip++;
        }

        stack_dtor(stc);


}

int main(int argc, char *argv[])
{
    int *commandsArray = NULL;

    int commandsFile = open(argv[1], _O_BINARY | O_RDONLY );

    //int num = file_to_array(&commandsArray, commandsFile);
    main_runner (commandsFile);

    close(commandsFile);

    return 0;
}

int file_to_array(int **commandsArray, int inputFile){

    static int commands[512] = {};
    *commandsArray = commands;

    char *allStr                   = NULL;
    string_start_end *stringsArray = NULL;
    int numStrings                 = enter_text_struct(&stringsArray, inputFile, &allStr);

    for(int i = 0; i < numStrings; i ++){
        commands[i] = atoi (  (stringsArray[i]).startl  );
    }

    close(inputFile);

    return numStrings;
}

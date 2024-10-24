#include "C:\MIPT\SPU\stack\stack_funk.h"
#include "C:\MIPT\SPU\stack\errors.h"
#include "C:\MIPT\SPU\stack\const.h"

#include "C:\MIPT\SPU\onegin\onegin.h"

#include <string.h>

int file_to_array(int **commandsArray, int file);


enum SPU_math_commands{
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
    JMPLE,
    JMPREG,
    CALL,
    RETURN

};

struct SPU_type{
    int64_t stc       = 0;
    int64_t returns   = 0;
    int ip            = 0;
    int *commands     = NULL;
    int numOfCommands = 0;
    int registers[5]  = {};
    int RAM[100]      = {};
};

int *get_arg(SPU_type* SPU);

void main_runner(int commandsFile)
{
    SPU_type SPU      = {};
    SPU.stc           = stack_ctor();
    SPU.returns       = stack_ctor();
    int a             = 0;
    int b             = 0;

    SPU.numOfCommands = file_to_array(&SPU.commands, commandsFile);

    for(int i = 0; i < SPU.numOfCommands; i ++){
        printf("_%d_\n", SPU.commands[i]);
    }

    printf("\n\n\n");
    int *argument = NULL;

    while(SPU.ip < SPU.numOfCommands){

        switch (SPU.commands[SPU.ip]){
            case PSH:
                argument = get_arg(&SPU);
                printf("333\n");
                push (SPU.stc, *argument);
                printf("444\n");
                break;

            case ADD:
                printf("t11\n");
                push (SPU.stc, pop (SPU.stc) + pop (SPU.stc));
                break;

            case MUL:
                printf("t10");
                push (SPU.stc, pop (SPU.stc) * pop (SPU.stc));
                break;

            case SUB:
                printf("t1");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                push (SPU.stc, b - a);
                break;

            case DIV:
                printf("t2");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                push (SPU.stc, b / a);
                //printf("div = %d\n", b / a);
                break;

            case POP:
                argument = get_arg(&SPU);
                printf("111\n");
                *argument = pop(SPU.stc);
                printf("222\n");
                break;

            case RET:
                SPU.ip = SPU.numOfCommands + 1;  //easy break cycle, using while condition
                break;

            case LUK:
                printf("t9");
                printf ("\n\nreturn = %d\n", pop (SPU.stc));
                break;

            case JMP:
                SPU.ip = SPU.commands[SPU.ip + 1] - 1;
                //printf("     new SPU.ip = %d     ", SPU.ip);
                break;

            case JMPM:
                printf("t3");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                SPU.ip ++;
                if (a > b) SPU.ip = SPU.commands[SPU.ip];
                break;

            case JMPL:
                printf("t4");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                SPU.ip ++;
                if (a < b) SPU.ip = SPU.commands[SPU.ip];
                break;

            case JMPE:
                printf("t5");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                SPU.ip ++;
                if (a == b) SPU.ip = SPU.commands[SPU.ip];
                break;

            case JMPME:
                printf("t6");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                SPU.ip ++;
                if (a >= b) SPU.ip = SPU.commands[SPU.ip];
                break;

            case JMPLE:
                printf("t7");
                a = pop (SPU.stc);
                b = pop (SPU.stc);
                SPU.ip ++;
                if (a <= b) SPU.ip = SPU.commands[SPU.ip];
                break;

            case JMPREG:
                SPU.ip ++;
                a = SPU.commands[SPU.ip];
                SPU.ip = SPU.registers[a];
                break;

            case CALL:
                push(SPU.returns, SPU.ip + 1);
                SPU.ip = SPU.commands[SPU.ip + 1] - 1;
                break;

            case RETURN:
                SPU.ip = pop(SPU.returns);
                break;

            default:
                printf ("\nSyntax error -%d-         ip = %d\n", SPU.commands[SPU.ip], SPU.ip);
        }

        SPU.ip++;
    }

    stack_dtor(SPU.stc);


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

int file_to_array(int **commandsArray, int inputFile)
{

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

int *get_arg(SPU_type* SPU)
{
    SPU->ip ++;
    int mode      = (SPU->commands)[SPU->ip];
    int *argument = NULL;
    static int containedEl = 0;

    if (  (mode & 2) != 0)
    {
        SPU->ip ++;
        argument = &(SPU->registers)[(SPU->commands)[SPU->ip]];
        printf("case1\n");
    }

    if (  (mode & 1) != 0)
    {
        SPU->ip++;
        containedEl = (SPU->commands)[SPU->ip];
        printf("case2  %d\n", mode);
        if ((mode & 2) == 0) argument = &containedEl;
    }

    if (  (mode & 1) != 0 && (mode & 2) != 0  )
    {
        containedEl += *argument;
        argument = &containedEl;
    }


    if( (mode & 4)  != 0)
    {
        printf("case3 %d\n", mode);
        argument = &(SPU->RAM)[*argument];
    }
    printf("\n\n");

    return argument;
}

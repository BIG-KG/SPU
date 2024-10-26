
#include "C:\MIPT\SPU\stack\stack_funk.h"
#include "C:\MIPT\SPU\stack\errors.h"
#include "C:\MIPT\SPU\stack\const.h"
#include "C:\MIPT\SPU\onegin\onegin.h"

#include <string.h>
#include <math.h>

#include "enums.cpp"


const int SCALING_FACTOR = 1000;

int file_to_array(int **commandsArray, int file);


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
    int64_t a             = 0;
    int64_t b             = 0;

    SPU.numOfCommands = file_to_array(&SPU.commands, commandsFile);

    for(int i = 0; i < SPU.numOfCommands; i ++){
        printf("%d   _%d_\n", i, SPU.commands[i]);
    }

    printf("\n\n\n");
    int *argument = NULL;
    int run = 1;

    while(SPU.ip < SPU.numOfCommands && run == 1){

    #define DEF_CMD(name, CODE, argType, codet)     \
        case (CODE):                                \
            codet                                   \
            break;                                  \
                                                    \
                                                    \

        switch (SPU.commands[SPU.ip])
        {
            #include "commands.cpp"

            default:
                printf ("\nSyntax error -%d-         ip = %d\n", SPU.commands[SPU.ip], SPU.ip);
        }
        #undef  DEF_CMD
        SPU.ip++;
    }
    printf("cycle_out\n");
    stack_dtor(SPU.stc);
    stack_dtor(SPU.returns);
    printf("stacks_dtr\n");
}

int main(int argc, char *argv[])
{
    int *commandsArray = NULL;

    int commandsFile = open(argv[1], _O_BINARY | O_RDONLY );

    //int num = file_to_array(&commandsArray, commandsFile);
    main_runner (commandsFile);

    printf("end_main_runner\n");
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
    }

    if (  (mode & 1) != 0)
    {
        SPU->ip++;
        containedEl = (SPU->commands)[SPU->ip];

        containedEl *= SCALING_FACTOR;

        if ((mode & 2) == 0) argument = &containedEl;
    }

    if (  (mode & 1) != 0 && (mode & 2) != 0  )
    {
        containedEl += *argument;
        argument = &containedEl;
    }


    if( (mode & 4)  != 0)
    {
        argument = &(SPU->RAM)[*argument];
    }
    printf("\n\n");

    return argument;
}

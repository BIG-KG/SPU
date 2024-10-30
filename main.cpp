
#include "C:\MIPT\SPU\stack\stack_funk.h"
#include "C:\MIPT\SPU\stack\errors.h"
#include "C:\MIPT\SPU\stack\const.h"
#include "C:\MIPT\SPU\onegin\onegin.h"

#include <string.h>
#include <math.h>

#include "common_info.cpp"
#include "processro_const&t.h"
#include "processor_funks.h"

void main_runner(int commandsFile)
{
    SPU_type SPU      = {};
    SPU.stc           = stack_ctor();
    SPU.returns       = stack_ctor();
    int64_t a             = 0;
    int64_t b             = 0;

    SPU.numOfCommands = file_to_array(&SPU.commands, commandsFile);

    // for(int i = 0; i < SPU.numOfCommands; i ++){
    //     printf("%d   _%d_\n", i, SPU.commands[i]);
    // }
    // printf("\n\n\n");
    command_t *command = NULL;
    int *argument         = NULL;
    int run               = 1;

    while(SPU.ip < SPU.numOfCommands && run == 1){

    command = (command_t *)(&SPU.commands[SPU.ip]);
    //printf("command = %d      ->      %d\n", SPU.ip, SPU.commands[SPU.ip]);

    #define DEF_CMD(name, CODE, argType, codetxt)   \
        case (CODE):                                \
            codetxt                                 \
            break;                                  \
                                                    \
                                                    \

        switch (command->commandNum)
        {
            #include "commands.cpp"

            default:
                printf ("\nSyntax error -%d-         ip = %d\n", command->commandNum, SPU.ip);
        }
    #undef  DEF_CMD
        SPU.ip++;
    }
    //printf("cycle_out\n");
    stack_dtor(SPU.stc);
    stack_dtor(SPU.returns);
    //printf("stacks_dtr\n");
}

int main(int argc, char *argv[])
{
    int *commandsArray = NULL;

    int commandsFile = open(argv[1], _O_BINARY | O_RDONLY );

    //int num = file_to_array(&commandsArray, commandsFile);
    main_runner (commandsFile);

     //printf("end_main_runner\n");
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

    for (int i = 0; i < numStrings; i ++)
    {
        commands[i] = atoi (  (stringsArray[i]).startl  );
    }

    close  (inputFile);

    return numStrings;
}

int *get_arg(command_t* command, SPU_type* SPU)
{
    int mode      = command->memoryType;
    int *argument = NULL;
    static int containedEl = 0;

    if (  (mode & 2) != 0)
    {
        argument = &(SPU->registers)[command->registerNum];
       // printf()
    }


    if (  (mode & 1) != 0)
    {

        //printf("contained EL\n");
        SPU->ip++;
        containedEl  = SPU->commands[SPU->ip];

        if ((mode & 2) == 0) argument = &containedEl;
    }

    if (  (mode & 1) != 0 && (mode & 2) != 0  )
    {
        containedEl += *argument;
        argument     = &containedEl;
    }


    if( (mode & 4)  != 0)
    {
        argument = &(SPU->RAM)[*argument / SCALING_FACTOR];
    }

    return argument;
}

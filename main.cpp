
#include "C:\MIPT\SPU\stack\stack_funk.h"
#include "C:\MIPT\SPU\stack\errors.h"
#include "C:\MIPT\SPU\stack\const.h"
#include "C:\MIPT\SPU\onegin\onegin.h"

#include <string.h>
#include <math.h>

#include "common_info.cpp"
#include "processro_const&t.h"
#include "processor_funks.h"

#define DEF_CMD(name, CODE, argType, codetxt)             \
    void funk_##CODE(SPU_type *SPU, command_t *command){   \
        codetxt                                           \
    }                                                     \

#include "commands.cpp"
#undef DEF_CMD

struct command_to_funk{
    int commandNUM = 0;
    void (*message) (SPU_type *SPU, command_t *command);
};

command_to_funk code_to_funk[32] = {};



void main_runner(int commandsFile)
{
    int lastNum = 0;
    #define DEF_CMD(name, CODE, argType, codetxt)                \
        code_to_funk[ CODE ].commandNUM = CODE       ;           \
        code_to_funk[ CODE ].message    = funk_##CODE;           \
        lastNum ++;                                              \

    #include "commands.cpp"
    #undef DEF_CMD

    SPU_type SPU      = {};
    SPU.stc           = stack_ctor();
    SPU.returns       = stack_ctor();
    SPU.run           = 1;
    int64_t a         = 0;
    int64_t b         = 0;


    SPU.numOfCommands = file_to_array(&SPU.commands, commandsFile);

    // for(int i = 0; i < SPU.numOfCommands; i ++){
    //     printf("%d   _%d_\n", i, SPU.commands[i]);
    // }
    // printf("\n\n\n");
    command_t *command = NULL;


    while(SPU.ip < SPU.numOfCommands && SPU.run == 1){

        command = (command_t *)(&SPU.commands[SPU.ip]);
        //printf("command = %d      ->      %d\n", SPU.ip, SPU.commands[SPU.ip]);

        if (  command->commandNUM >= 0 && command->commandNUM <= lastNum  )
        {
            code_to_funk[command->commandNUM].message(&SPU, command);
        }
        else
        {
            printf ("\nSyntax error -%d-         ip = %d\n", command->commandNUM, SPU.ip);
            assert(0);
        }

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

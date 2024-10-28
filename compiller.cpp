
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cpmp_types.h"

#include "enums.cpp"
#include "compiller_func.h"
#include "cmpiller_types.h"

const int SCALING_FACTOR = 1000;

enum returnings_types{
    REED  = 0,
    WRITE = 1
};

struct command
{
    int     commandNUM  : 5;
    int     memoryType  : 3;
    int     registerNum : 3;
    int     constValue  : 20;
};


int main(int argc, char *argv[])
{`
	FILE *inputFile     = fopen (argv[1] ,         "r");
	FILE *outputFile    = fopen ("compilled.txt" , "w");
	char command[30]    = "";
	tag tagsArray[30]   = {0};

    int commentary_mode = 0;
	int a = 0;
	int b = 0;

	find_tags(inputFile, tagsArray);

    struct output_commands outputArray;

    while (  fscanf (inputFile, "%s", &command) != EOF  )
    {
        printf("%s\n", command);

        if (commentary_mode == 1)
        {
            if (  command [strlen(command) - 1] == '#'  )
            {
                commentary_mode = 0;
                continue;
            }
            else
            {
                continue;
            }
        }



        if      (strcmp (command, "push") == 0)
        {
            compile_args(inputFile, REED, &outputArray, PSH);

        }

        else if (strcmp (command, "add") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = ADD;
        }


        else if (strcmp (command, "mul") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = MUL;
        }


        else if (strcmp (command, "sub") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = SUB;
        }


        else if (strcmp (command, "div") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = DIV;
        }


        else if (strcmp (command, "look") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = LUK;
        }


        else if (strcmp (command, "pop") == 0)
        {
            compile_args(inputFile, WRITE, &outputArray, POP);
        }


        else if (strcmp (command, "end") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = END;
        }


        else if (strcmp (command, "jmp") == 0)
        {
            jump_argument(tagsArray, inputFile, &outputArray, JMP);
        }


        else if (strcmp (command, "jmpm")   == 0)
        {
            jump_argument(tagsArray, inputFile, &outputArray, JMPM);
        }


        else if (strcmp (command, "jmpl")   == 0)
        {
            jump_argument(tagsArray, inputFile, &outputArray, JMPL);
        }


        else if (strcmp (command, "jmpe")   == 0)
        {
            jump_argument(tagsArray, inputFile, &outputArray, JMPE);
        }

        else if (strcmp (command, "call") == 0)
        {
            jump_argument(tagsArray, inputFile, &outputArray, CALL);
        }


        else if (strcmp (command, "ret") == 0)
        {
			outputArray.commands[outputArray.currentCommand] = RETURN;
        }

        else if (strcmp (command, "sqrt") == 0)
        {
            outputArray.commands[outputArray.currentCommand] = SQRT;
        }

        else if ( command[0] == '^')
        {
            continue;
        }

        else if ( command[0] == '#'){
            commentary_mode = 1;
        }

        else
        {
            printf ("Syntax error _%s_\n", command);
			assert(0);
        }

       outputArray.currentCommand ++;
    }

    outputCommandFile(outputFile, &outputArray);

    printf("end\n");

	fclose(inputFile );
	fclose(outputFile);

	return 0;
}

int find_tags(FILE *inputFile, tag *tagsArray)
{
    char command[30] = {};
    int commandlen   = 0;
    char lastEl      = 0;
    int i  = 0;
    int ip = 0;

    while (  fscanf (inputFile, "%s", &command) != EOF  )
    {
        commandlen = strlen(command);
        lastEl = command[commandlen - 1];
        printf("\n");

        printf("current command data    string = _%s_    lastel = _%c_        curr ip = %lld\n", command, lastEl, ip);

        if (command[0] == '^')
        {
            sscanf ( &command[1], "%s", (tagsArray[i]).name );
            if (  strlen((tagsArray[i]).name) == 0  ){
                printf("MILORD, NAZVANIE POINTERA NE MOZHET BIT PUSTIM\n");
                assert(0);
            }
                (tagsArray[i]).contain = ip;
                i++;
            continue;
        }

        else if (!( lastEl == ']' || lastEl == 'X' || isdigit(lastEl) || command[0] == ':'))
        {
            ip++;
        }
    }

    fseek(inputFile, 0, SEEK_SET);

    return i;
}

int get_tag(char* a, tag *tagsArray){
    for(int i = 0; i < 30; i ++){
        if (  strcmp((tagsArray[i]).name, a) == 0  )
            return (tagsArray[i]).contain;
    }
    return -1;
}

void compile_args(FILE *inputFile, char returningMode, struct output_commands *outputArray, int commandNUM )
{
    int typeOfMemory  = 0;
    int returningReg  = 0;
    int returningConst = 0;
    int current = 0;

    char command[32] = {};
    fscanf(inputFile, "%s", command);


    if      (command[current] == '[' && command[strlen(command) - 1] == ']')
    {
        typeOfMemory += 4;
        current ++;
    }

    else if (!command[current] == '[' || !command[strlen(command) - 1] == ']')
    {
        printf("ERROR IN APPEL TO RAM\n");
        assert(0);
    }



    if      (  isalpha(command[current]) && isalpha(command[current + 1])  )
    {
        typeOfMemory += 2;
        returningReg = command[current] - 'A' + 1;

        if (returningReg < 1 || returningReg > 4)
        {
            printf("ERROR, REFERENSE TO UNEXISEBLE REGISTER\n");
            assert(0);

        }

        current += 3;
    }

    else if (  isalpha(command[current])    ||   isalpha(command[current + 1])           &
                       !(command[current + 2] == '+' || command[current + 2] == ']' || typeOfMemory & 4 == 0)             )
    {
        printf("ERROR, WRONG REFERENSE TO REGISTER _%s_\n", &command[current]);
        assert(0);
    }


    if      (   isdigit(command[current])   ||   ( command[current] == '-'  &&  isdigit(command[current + 1] ) )   )
    {
        if(  (typeOfMemory & 2) != 0  && command[current - 1] != '+')
        {
            printf("ERROR, WRONG REFERENSE TO REGISTER _%s_\n", &command[current]);
            assert(0);
        }

        typeOfMemory += 1;
        returningConst = atoi (&command[current]);
    }



    if ( check_input_value(returningMode, typeOfMemory) != 0 )
    {
        return;
        assert(0);
    }

    struct command tmprCmd = {};
    tmprCmd.commandNUM  = commandNUM;
    tmprCmd.constValue  = returningConst * SCALING_FACTOR;
    tmprCmd.registerNum = returningReg;
    tmprCmd.memoryType  = typeOfMemory;

    outputArray->commands[outputArray->currentCommand] = *((int64_t*)&tmprCmd);

    // printf("%lld", typeOfMemory);
    // if ((typeOfMemory & 2) != 0) printf(" %lld", returningReg   );
    // if ((typeOfMemory & 1) != 0) printf(" %lld", returningConst);
    // fprintf("\n");

    return;
}

int check_input_value(int returningMode, int typeOfMemory)
{

    if (returningMode == WRITE && (typeOfMemory & 1) != 0 && (typeOfMemory & 4) == 0)
    {
        printf("ERROR, TRYING TO WRIGHT IN CONST VALUE\n");
        return 1;
    }

    if (typeOfMemory == 0)
    {
        printf("ERROR, NO INPUT VALUE\n");
        return 1;
    }

    return 0;
}

int jump_argument(tag *tagsArray, FILE *inputFile, struct output_commands *outputArray, int jumpType)
    {
        int a = 0;
        char command[30] = {};

        if (  fscanf (inputFile, "%d", &a) == 0  )
        {
            fscanf(inputFile, "%s", command);


            if(  (command[0] != ':') || (command[1]) == '\0' )
            {
                printf("MILORD, WRONG JUMP VALUE, command  = %s", command);
                assert(0);
            }
            a = get_tag (command + 1, tagsArray);

            if (a < 0)
            {
                printf("MILORD, WRONG JUMP VALUE, command  = %s", command);
            }
        }

        struct command tmprCmd = {};
        tmprCmd.commandNUM     = jumpType;
        tmprCmd.memoryType     = 1;
        tmprCmd.constValue     = a * SCALING_FACTOR;

    //_______________________________________________________________________________

    //_______________________________________________________________________________

        printf("cons value  =  %d              aodicadc = %d\n", tmprCmd.constValue, *((int*)&tmprCmd));

        printf("value = %d\n", *(int *)&tmprCmd);

        outputArray->commands[outputArray->currentCommand] = *((int*)&tmprCmd);

        return 0;
    }

void outputCommandFile(FILE *outputFile ,struct output_commands *outputArray)
{
    printf("cuur comm = %d\n", outputArray->currentCommand);
    for(int i = 0; i < outputArray->currentCommand; i++)
    {
        printf("%d = %lld\n", i, (int)(outputArray->commands[i]));
        fprintf(outputFile, "%lld\n", (int)(outputArray->commands[i]));
    }
}

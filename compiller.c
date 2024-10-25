#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cpmp_types.h"

#include "enums.cpp"
#include "compiller_func.h"


enum returnings_types{
    REED  = 0,
    WRITE = 1
};


int main(int argc, char *argv[])
{
	FILE *inputFile   = fopen (argv[1] ,         "r");
	FILE *outputFile  = fopen ("compilled.txt" , "w");
	char command[30]  = "";
	tag tagsArray[30] = {0};
	int a = 0;
	int b = 0;

	find_tags(inputFile, tagsArray);

    while(  fscanf (inputFile, "%s", &command) != EOF  )
    {
        printf("%s\n", command);


        if      (strcmp (command, "push") == 0)
        {
            fprintf (outputFile, "%d ", PSH);
            compile_args(inputFile, outputFile, REED);

        }


        else if (strcmp (command, "add") == 0)
        {
			fprintf (outputFile, "%d\n", ADD);
        }


        else if (strcmp (command, "mul") == 0)
        {
            fprintf (outputFile, "%d\n", MUL);
        }


        else if (strcmp (command, "sub") == 0)
        {
            fprintf (outputFile, "%d\n", SUB);
        }


        else if (strcmp (command, "div") == 0)
        {
            fprintf (outputFile, "%d\n", DIV);
        }


        else if (strcmp (command, "look") == 0)
        {
            fprintf (outputFile, "%d\n", LUK);
        }


        else if (strcmp (command, "pop") == 0)
        {
            fprintf (outputFile, "%d ", POP);
            compile_args(inputFile, outputFile, WRITE);
        }


        else if (strcmp (command, "end") == 0)
        {
            fprintf (outputFile, "%d\n", END);
        }


        else if (strcmp (command, "jmp") == 0)
        {
            jump_argument(tagsArray, inputFile, outputFile, JMP);
        }


        else if (strcmp (command, "jmpm")   == 0)
        {
            jump_argument(tagsArray, inputFile, outputFile, JMPM);
        }


        else if (strcmp (command, "jmpl")   == 0)
        {
            jump_argument(tagsArray, inputFile, outputFile, JMPL);
        }


        else if (strcmp (command, "jmpe")   == 0)
        {
            jump_argument(tagsArray, inputFile, outputFile, JMPE);
        }

        else if (strcmp (command, "call") == 0)
        {
            jump_argument(tagsArray, inputFile, outputFile, CALL);
        }


        else if (strcmp (command, "ret") == 0)
        {
			fprintf (outputFile, "%d\n",  RETURN);
        }

        else if (strcmp (command, "sqrt") == 0)
        {
            fprintf (outputFile, "%d\n", SQRT);
        }

        else if ( command[0] == '^') ;

        else
        {
            printf ("Syntax error _%s_\n", command);
            printf("firs sim ~%c~\n", command[0]);
			return 1;
        }

    }

    printf("end\n");

	fclose(inputFile );
	fclose(outputFile);

	return 0;
}

int find_tags(FILE *inputFile, tag *tagsArray){

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

        printf("current command data    string = _%s_    lastel = _%c_        curr ip = %d\n", command, lastEl, ip);

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

        else{
            ip++;
        }

        if ( lastEl == ']' || lastEl == 'X' || isdigit(lastEl) )
        {
            ip ++;

            printf("argument\n");

            for (int i = 0; i < commandlen; i ++)
            {
                if(command[i] == '+') ip ++;
            }
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

void compile_args(FILE *inputFile, FILE *outputFile, char returningMode)
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


    if      (  isdigit(command[current])  )
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
    }

    fprintf(outputFile, "%d", typeOfMemory);
    if ((typeOfMemory & 2) != 0) fprintf(outputFile, " %d", returningReg   );
    if ((typeOfMemory & 1) != 0) fprintf(outputFile, " %d", returningConst);
    fprintf(outputFile, "\n");
}


int check_input_value(int returningMode, int typeOfMemory)
{

    if (returningMode == WRITE && (typeOfMemory & 1) != 0 && (typeOfMemory & 4) == 0)
    {
        printf("ERROR, TRYING TO WRIGHT IN CONST VALUE\n");
        return 1;
    }

    return 0;
}

int jump_argument(tag *tagsArray, FILE *inputFile, FILE *outputFile, int jumpType)
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

        fprintf (outputFile, "%d %d\n", jumpType, a);

        return 0;
    }

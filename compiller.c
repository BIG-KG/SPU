#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

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

struct tag{
    char name[32] = {};
    int contain   = -1;
};

enum returnings_types{
    REED  = 0,
    WRITE = 1
};

int find_tags(FILE *inputFile, tag *tagsArray);
int get_tag(char* a, tag *tagsArray);
void compile_args(FILE *inputFile, FILE *outputFile, char returningMode);
int check_input_value(int returningMode, int typeOfMemory);



int main(int argc, char *argv[]){

	FILE *inputFile   = fopen (argv[1] ,         "r");
	FILE *outputFile  = fopen ("compilled.txt" , "w");
	char command[30]  = "";
	tag tagsArray[30] = {0};
	int a = 0;
	int b = 0;

	find_tags(inputFile, tagsArray);

    while(  fscanf (inputFile, "%s", &command) != EOF  ){

        printf("%s\n", command);


        if      (strcmp (command, "push") == 0){

            fprintf (outputFile, "%d ", PSH);
            compile_args(inputFile, outputFile, REED);

        }

        else if (strcmp (command, "add") == 0){
			fprintf (outputFile, "%d\n", ADD);
        }

        else if (strcmp (command, "mul") == 0){
            fprintf (outputFile, "%d\n", MUL);
        }

        else if (strcmp (command, "sub") == 0){
            fprintf (outputFile, "%d\n", SUB);
        }

        else if (strcmp (command, "div") == 0){
            fprintf (outputFile, "%d\n", DIV);
        }

        else if (strcmp (command, "look") == 0){
            fprintf (outputFile, "%d\n", LUK);
        }

        else if (strcmp (command, "pop") == 0){
            printf("current");
            fprintf (outputFile, "%d ", POP);
            compile_args(inputFile, outputFile, WRITE);
        }

        else if (strcmp (command, "end") == 0){
            fprintf (outputFile, "%d\n", RET);
        }

        else if (strcmp (command, "jmp") == 0){
            int a = 0;
            printf("start obr\n");
            if (  fscanf (inputFile, "%d", &a) == 0  ){
                fscanf(inputFile, "%s", command);
                if(  (command[0] != ':') || (command[1]) == '\0' ){
                    printf("MILORD, WRONG JUMP VALUE");
                }
                a = get_tag (command + 1, tagsArray);
            }

            fprintf (outputFile, "%d %d\n", JMP, a);
        }

        else if (strcmp (command, "jmpm")   == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPM, a);
        }

        else if (strcmp (command, "jmpl")   == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPL, a);
        }

        else if (strcmp (command, "jmpe")   == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPE, a);
        }

        else if (strcmp (command, "jmpme")  == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPME, a);
        }

        else if (strcmp (command, "jmple")  == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPLE, a);
        }

        else if (strcmp (command, "call") == 0){
            int a = 0;
            if (  fscanf (inputFile, "%d", &a) == 0  )
            {
                fscanf(inputFile, "%s", command);
                if (  (command[0] != ':') || (command[1]) == '\0' )
                {
                    printf("MILORD, WRONG JUMP VALUE");
                }
                a = get_tag (command + 1, tagsArray);
            }
            fprintf (outputFile, "%d %d\n", CALL, a);
        }

        else if (strcmp (command, "ret") == 0){
			fprintf (outputFile, "%d\n",  RETURN);
        }

        else if ( command[0] == '^'){
            ;
        }

        else{
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
        printf("qwer\n");

        if (command[0] == '^')
        {
            sscanf ( &command[1], "%s", (tagsArray[i]).name );
            if (  strlen((tagsArray[i]).name) == 0  ){
                printf("MILORD, NAZVANIE POINTERA NE MOZHET BIT PUSTIM\n");
                assert(0);
            }
                (tagsArray[i]).contain = ip;
                i++;
        }

        printf("popppppppp    string = _%s_    lastel = _%c_\n", command, lastEl);

        if ( lastEl == ']' || lastEl == 'X' || isdigit(lastEl) )
        {
            ip ++;

            printf("popppppppp\n");

            for (int i = 0; i < commandlen; i ++)
            {
                if(command[i] == '+') ip ++;
            }
        }
        ip ++;
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

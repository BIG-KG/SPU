#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
    JMPLE

};

int main(int argc, char *argv[]){

	FILE *inputFile  = fopen (argv[1] ,         "r");
	FILE *outputFile = fopen ("compilled.txt" , "w");
	char command[30] = "";

    while(  fscanf (inputFile, "%s", &command) != EOF  ){

        if      (strcmp (command, "psh") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", PSH, a);
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

        else if (strcmp (command, "res") == 0){
            fprintf (outputFile, "%d\n", POP);
        }

        else if (strcmp (command, "end") == 0){
            fprintf (outputFile, "%d\n", RET);
        }


        else if (strcmp (command, "jmp") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMP, a);
        }

        else if (strcmp (command, "jmpm") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPM, a);
        }

        else if (strcmp (command, "jmpl") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPL, a);
        }

        else if (strcmp (command, "jmpe") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPE, a);
        }

        else if (strcmp (command, "jmpme") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPME, a);
        }

        else if (strcmp (command, "jmple") == 0){
            int a = 0;
            fscanf  (inputFile, "%d", &a);
            fprintf (outputFile, "%d %d\n", JMPLE, a);
        }

        else{
            printf ("Syntax error _%s_\n", command);
			return 1;
        }
    }

	fclose(inputFile );
	fclose(outputFile);

	return 0;
}

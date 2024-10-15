#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	FILE *inputFile  = fopen (argv[1] ,         "r");
	FILE *outputFile = fopen ("compilled.txt" , "w");	
	char command[30] = "";
	
    while(  fscanf (inputFile, "%s", &command) != EOF  ){

        if      (strcmp (command, "psh") == 0){
            int a = 0;
            fscanf (inputFile, "%d", &a);
            fprintf (outputFile,  "1 %d\n", a);
        }

        else if (strcmp (command, "add") == 0){
			fprintf (outputFile,  "2\n");
        }

        else if (strcmp (command, "mul") == 0){
            fprintf (outputFile,  "3\n");
        }

        else if (strcmp (command, "sub") == 0){
            fprintf (outputFile,  "4\n");
        }

        else if (strcmp (command, "div") == 0){
            fprintf (outputFile,  "5\n");
        }

        else if (strcmp (command, "res") == 0){
            fprintf (outputFile,  "0\n");
        }

        else if (strcmp (command, "end") == 0){
            fprintf (outputFile, "-1\n");
        }

        else{
			
            printf ("Syntax error _%s_\n", command);
			return 1;
        }
    }
	
	fclose(inputFile);
	fclose(outputFile);
	
	return 0;
}
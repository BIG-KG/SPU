#include "onegin.h"


int enter_text_struct(string_start_end ** pointToStringArr, int inputfile, char ** start){

    assert(pointToStringArr);

    int maxNumbStrings = MAX_LEN_OF_STRING;
    int numstring      = 0;
	int inputFileSize  = 0;
    int currElement    = 1;

    string_start_end *stringsArray = NULL;
	stringsArray = (string_start_end *)calloc(sizeof(string_start_end), maxNumbStrings);

    inputFileSize = file_size(inputfile);

    char *bufferString = (char *)calloc(inputFileSize + 2, sizeof(char));
    int reatedElements = read(inputfile, bufferString + 1, inputFileSize); // very rarely, read reads less
    //в два прохода по колву \n а не realloc
    while ( currElement <= inputFileSize){

        while (  (isspace(bufferString[currElement]))  &&  (currElement <= inputFileSize)  ){

            currElement++;
        }

        if (currElement > inputFileSize){
            break;
        }

        bufferString[currElement - 1]  = '\0';
        stringsArray[numstring].startl = &bufferString[currElement];

        while (  !isspace(bufferString[currElement])  &&  (currElement <= inputFileSize)  &&
                (bufferString[currElement] != '\r')  ){

            currElement++;
        }

        bufferString[currElement]    = '\0';
        stringsArray[numstring].endline = &bufferString[currElement - 1];
        currElement ++;


        numstring ++;

        if (numstring + 2 > maxNumbStrings){
            stringsArray = (string_start_end *)realloc(stringsArray,
                                                         sizeof(string_start_end) * maxNumbStrings * STEP_ADDING_STRING);

            maxNumbStrings *= STEP_ADDING_STRING;
        }
    }

    *start = bufferString;
    *pointToStringArr = stringsArray;

    return numstring;

}

int file_size(int targetFile){

    lseek(targetFile, 0, SEEK_END);
    int file_size = tell(targetFile);
	lseek(targetFile, 0, 0       );

	return file_size;

}


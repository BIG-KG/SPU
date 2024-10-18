#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

const int MAX_LEN_OF_STRING = 60;
const int MAX_NUM_OF_STRINGS = 3;
const int STEP_ADDING_STRING = 5;

struct string_start_end{
    char *startl = NULL;
    char *endline = NULL;
};

struct start_end_arr{
    void *startch = NULL;
    void *endch = NULL;
};

int file_size(int targetFile);

int enter_text_struct(string_start_end ** pointToStringArr, int inputfile, char ** start);

#endif // HEADER_H_INCLUDED

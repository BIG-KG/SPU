#ifndef CPMP_TYPES_H_INCLUDED
#define CPMP_TYPES_H_INCLUDED

struct tag
{
    char name[32] = {};
    int contain   = -1;
};

const int START_COMMAND_ARR_SIZE = 1000;

typedef long long int int64_t;

struct output_commands
{
        int64_t *commands      = (int64_t *)calloc(START_COMMAND_ARR_SIZE, sizeof(int64_t));
        int currentCommand = 0;
        int maxCommands    = START_COMMAND_ARR_SIZE;
};

enum returnings_types
{
    REED  = 0,
    WRITE = 1
};



#endif // CPMP_TYPES_H_INCLUDED

const int START_COMMAND_ARR_SIZE = 512;

typedef long long int int64_t;

struct output_commands{
        int64_t *commands      = (int64_t *)calloc(START_COMMAND_ARR_SIZE, sizeof(int64_t));
        int currentCommand = 0;
        int maxCommands    = START_COMMAND_ARR_SIZE;
};

const int START_COMMAND_ARR_SIZE = 512;
struct output_commands{
        int *commands      = (int *)calloc(START_COMMAND_ARR_SIZE, sizeof(int));
        int currentCommand = 0;
        int maxCommands    = START_COMMAND_ARR_SIZE;
};

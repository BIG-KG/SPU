const int SCALING_FACTOR   = 100;
const int DRAWING_RAM_SIZE = 1600;
const int LINE_SIZE        = 40 ;
const int FULL_RAM_SIZE    = 1620;

struct SPU_type
{
    int64_t stc       = 0;
    int64_t returns   = 0;
    int ip            = 0;
    int *commands     = NULL;
    int numOfCommands = 0;
    int registers[5]  = {};
    int RAM[FULL_RAM_SIZE]      = {};
};

int file_to_array(int **commandsArray, int file);

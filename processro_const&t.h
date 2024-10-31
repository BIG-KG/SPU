const int SCALING_FACTOR   = 100;
const int DRAWING_RAM_SIZE = 2500;
const int LINE_SIZE        = 50 ;
const int FULL_RAM_SIZE    = 2520;

struct SPU_type
{
    int64_t stc       = 0;
    int64_t returns   = 0;
    int ip            = 0;
    int *commands     = NULL;
    int numOfCommands = 0;
    int registers[5]  = {};
    int RAM[FULL_RAM_SIZE]      = {};
    int run           = 1;
};

int file_to_array(int **commandsArray, int file);

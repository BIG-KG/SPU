const int SCALING_FACTOR   = 1000;
const int DRAWING_RAM_SIZE = 62500;
const int LINE_SIZE        = 250 ;
const int FULL_RAM_SIZE    = 63000;
const int NOT_VID_RAM      = 50;

struct SPU_type
{
    int64_t stc                = 0;
    int64_t returns            = 0;
    int ip                     = 0;
    int *commands              = NULL;
    int numOfCommands          = 0;
    int64_t registers[5]       = {};
    int64_t RAM[FULL_RAM_SIZE] = {};
    int run                    = 1;
};

int file_to_array(int **commandsArray, int file);

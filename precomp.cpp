# 1 "main.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.cpp"
# 10 "main.cpp"
# 1 "common_info.cpp" 1
enum SPU_math_commands{
    END = 0,
    POP = 1,
    PSH = 2,
    ADD = 3,
    MUL = 4,
    SUB = 5,
    LUK = 6,
    DIV = 7,
    JMP,
    JMPM,
    JMPL,
    JMPE,
    CALL,
    RETURN,
    SQRT,
    DRAW,
    PTCH
};

struct command_t
{
    int commandNUM : 7;
    int memoryType : 3;
    int registerNum : 3;
};
# 11 "main.cpp" 2
# 1 "processro_const&t.h" 1
const int SCALING_FACTOR = 100;
const int DRAWING_RAM_SIZE = 1600;
const int LINE_SIZE = 40 ;
const int FULL_RAM_SIZE = 1620;

struct SPU_type
{
    int64_t stc = 0;
    int64_t returns = 0;
    int ip = 0;
    int *commands = NULL;
    int numOfCommands = 0;
    int registers[5] = {};
    int RAM[FULL_RAM_SIZE] = {};
    int run = 1;
};

int file_to_array(int **commandsArray, int file);
# 12 "main.cpp" 2
# 1 "processor_funks.h" 1
int *get_arg(command_t* command, SPU_type* SPU);
# 13 "main.cpp" 2






# 1 "commands.cpp" 1
# 9 "commands.cpp"
void funk_END(SPU_type SPU, command_t *command){ { SPU->ip = SPU->numOfCommands + 1; run = 0; } }







void funk_POP(SPU_type SPU, command_t *command){ { int argument = get_arg(command, SPU); *argument = pop(SPU->stc); } }






void funk_PSH(SPU_type SPU, command_t *command){ { int argument = get_arg(command, SPU); push (SPU->stc, (*argument) ); } }
# 34 "commands.cpp"
void funk_ADD(SPU_type SPU, command_t *command){ { push (SPU->stc, pop (SPU->stc) + pop (SPU->stc)); } }





void funk_MUL(SPU_type SPU, command_t *command){ { int a = pop (SPU->stc); int b = pop (SPU->stc); push (SPU->stc, (a * b) / SCALING_FACTOR); } }







void funk_SUB(SPU_type SPU, command_t *command){ { int a = pop (SPU->stc); int b = pop (SPU->stc); push (SPU->stc, b - a); } }







void funk_LUK(SPU_type SPU, command_t *command){ { printf ("return look = %f\n", ((float)pop(SPU->stc) / SCALING_FACTOR)); } }





void funk_DIV(SPU_type SPU, command_t *command){ { int a = pop (SPU->stc); int b = pop (SPU->stc); push (SPU->stc, ((float)b / (float)a) * SCALING_FACTOR); } }
# 71 "commands.cpp"
void funk_JMP(SPU_type SPU, command_t *command){ { SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR -1 ; } }




void funk_JMPM(SPU_type SPU, command_t *command){ { int a = pop (SPU->stc); int b = pop (SPU->stc); if (a > b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1 ; else SPU->ip++; } }







void funk_JMPL(SPU_type SPU, command_t *command){ { a = pop (SPU->stc); b = pop (SPU->stc); if (a < b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1 ; else SPU->ip++; } }
# 93 "commands.cpp"
void funk_JMPE(SPU_type SPU, command_t *command){ { a = pop (SPU->stc); b = pop (SPU->stc); if (a == b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1 ; else SPU->ip++; } }
# 102 "commands.cpp"
void funk_CALL(SPU_type SPU, command_t *command){ { push(SPU->returns, SPU->ip + 2); SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1 ; } }







void funk_RETURN(SPU_type SPU, command_t *command){ { SPU->ip = pop(SPU->returns) - 1; } }






void funk_SQRT(SPU_type SPU, command_t *command){ { push(SPU->stc, sqrt (pop(SPU->stc)) * sqrt (SCALING_FACTOR) ); } }




void funk_DRAW(SPU_type SPU, command_t *command){ { for (int i = 0; i < DRAWING_RAM_SIZE; i ++) { if((SPU->RAM)[i] != 0) { printf("@"); } else { printf(" ", (SPU->RAM)[i]); } if( (i + 1) % LINE_SIZE == 0 ) printf("\n"); } } }
# 140 "commands.cpp"
void funk_PTCH(SPU_type SPU, command_t *command){ { printf ("return ptch = _%c_\n", ((int)pop(SPU->stc) / SCALING_FACTOR) ); } }
# 20 "main.cpp" 2


struct command_to_funk{
    int commandNUM = 0;
    void (*message) (SPU_type SPU, command_t *command);
};

command_to_funk code_to_funk[32] = {};



void main_runner(int commandsFile)
{





# 1 "commands.cpp" 1
# 9 "commands.cpp"
code_to_funk[ END ].commandNUM = END ; code_to_funk[ END ].message = funk_END;







code_to_funk[ POP ].commandNUM = POP ; code_to_funk[ POP ].message = funk_POP;






code_to_funk[ PSH ].commandNUM = PSH ; code_to_funk[ PSH ].message = funk_PSH;
# 34 "commands.cpp"
code_to_funk[ ADD ].commandNUM = ADD ; code_to_funk[ ADD ].message = funk_ADD;





code_to_funk[ MUL ].commandNUM = MUL ; code_to_funk[ MUL ].message = funk_MUL;







code_to_funk[ SUB ].commandNUM = SUB ; code_to_funk[ SUB ].message = funk_SUB;







code_to_funk[ LUK ].commandNUM = LUK ; code_to_funk[ LUK ].message = funk_LUK;





code_to_funk[ DIV ].commandNUM = DIV ; code_to_funk[ DIV ].message = funk_DIV;
# 71 "commands.cpp"
code_to_funk[ JMP ].commandNUM = JMP ; code_to_funk[ JMP ].message = funk_JMP;




code_to_funk[ JMPM ].commandNUM = JMPM ; code_to_funk[ JMPM ].message = funk_JMPM;







code_to_funk[ JMPL ].commandNUM = JMPL ; code_to_funk[ JMPL ].message = funk_JMPL;
# 93 "commands.cpp"
code_to_funk[ JMPE ].commandNUM = JMPE ; code_to_funk[ JMPE ].message = funk_JMPE;
# 102 "commands.cpp"
code_to_funk[ CALL ].commandNUM = CALL ; code_to_funk[ CALL ].message = funk_CALL;







code_to_funk[ RETURN ].commandNUM = RETURN ; code_to_funk[ RETURN ].message = funk_RETURN;






code_to_funk[ SQRT ].commandNUM = SQRT ; code_to_funk[ SQRT ].message = funk_SQRT;




code_to_funk[ DRAW ].commandNUM = DRAW ; code_to_funk[ DRAW ].message = funk_DRAW;
# 140 "commands.cpp"
code_to_funk[ PTCH ].commandNUM = PTCH ; code_to_funk[ PTCH ].message = funk_PTCH;
# 39 "main.cpp" 2


    SPU_type SPU = {};
    SPU.stc = stack_ctor();
    SPU.returns = stack_ctor();
    SPU.run = 1;
    int64_t a = 0;
    int64_t b = 0;


    SPU.numOfCommands = file_to_array(&SPU.commands, commandsFile);





    command_t *command = NULL;


    while(SPU.ip < SPU.numOfCommands && run == 1){

        command = (command_t *)(&SPU.commands[SPU.ip]);


        if ( command->commandNum >= 0 && command->commandNum < 17 )
        {
            code_to_funk[command->commandNum].message(&SPU, command);
        }
        else
        {
            printf ("\nSyntax error -%d-         ip = %d\n", command->commandNum, SPU.ip);
            assert(0);
        }

        SPU.ip++;
    }

    stack_dtor(SPU.stc);
    stack_dtor(SPU.returns);

}

int main(int argc, char *argv[])
{
    int *commandsArray = NULL;

    int commandsFile = open(argv[1], _O_BINARY | O_RDONLY );


    main_runner (commandsFile);


    close(commandsFile);

    return 0;
}

int file_to_array(int **commandsArray, int inputFile)
{

    static int commands[512] = {};
    *commandsArray = commands;

    char *allStr = NULL;
    string_start_end *stringsArray = NULL;
    int numStrings = enter_text_struct(&stringsArray, inputFile, &allStr);

    for (int i = 0; i < numStrings; i ++)
    {
        commands[i] = atoi ( (stringsArray[i]).startl );
    }

    close (inputFile);

    return numStrings;
}

int *get_arg(command_t* command, SPU_type* SPU)
{
    int mode = command->memoryType;
    int *argument = NULL;
    static int containedEl = 0;

    if ( (mode & 2) != 0)
    {
        argument = &(SPU->registers)[command->registerNum];

    }


    if ( (mode & 1) != 0)
    {


        SPU->ip++;
        containedEl = SPU->commands[SPU->ip];

        if ((mode & 2) == 0) argument = &containedEl;
    }

    if ( (mode & 1) != 0 && (mode & 2) != 0 )
    {
        containedEl += *argument;
        argument = &containedEl;
    }


    if( (mode & 4) != 0)
    {
        argument = &(SPU->RAM)[*argument / SCALING_FACTOR];
    }

    return argument;
}

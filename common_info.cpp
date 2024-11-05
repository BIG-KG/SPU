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
    PTCH_MY,
    INPT,
    SIN,
    COS,
    ACOS,
    POPV,
    PSHV

};

struct command_t
{
    int     commandNUM  : 7;
    int     memoryType  : 3;
    int     registerNum : 5;
};

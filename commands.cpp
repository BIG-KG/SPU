//          order of arguments for DEF_CMD(..........)
//__________________________________________________________________________________
// 1. "name",
// 2.  CODE,
// 3.  type of argument: 0 = no argumenРµ, 1 = push-type argument, 2 = jump-type argument,
// 4.  code in main;,
//__________________________________________________________________________________

DEF_CMD("end", END, 0,
{
   // printf("000\n");
    SPU.ip = SPU.numOfCommands + 1;
    run = 0;  //easy break cycle, using while condition

})

DEF_CMD("pop", POP, 1,
{
//    printf("111\n");
    argument = get_arg(command, &SPU);
    *argument = pop(SPU.stc);

})

DEF_CMD("push", PSH, 1,
{
  //  printf("222\n");
    argument = get_arg(command, &SPU);
    push (SPU.stc, (*argument) );

})

DEF_CMD("add", ADD, 0,
{
    //printf("333\n");
    push (SPU.stc, pop (SPU.stc) + pop (SPU.stc));
})

DEF_CMD("mul", MUL, 0,
{
//    printf("444\n");
    push (SPU.stc, (pop (SPU.stc) * pop (SPU.stc)) / SCALING_FACTOR);
})

DEF_CMD("sub", SUB, 0,
{
  //  printf("555\n");
    a = pop (SPU.stc);
    b = pop (SPU.stc);
    push (SPU.stc, b - a);
})

DEF_CMD("look", LUK, 0,
{
    //printf("666\n");
    printf ("\nreturn = %f\n", ((float)pop(SPU.stc) / SCALING_FACTOR));
})

DEF_CMD("div",  DIV, 0,
{
//    printf("777\n");
    a = pop (SPU.stc);
    b = pop (SPU.stc);
    push (SPU.stc, ((float)b / (float)a) * SCALING_FACTOR);
    //printf("div = %d\n", b / a);
})

DEF_CMD("jmp",  JMP,  2,
{
    SPU.ip             = (*get_arg(command, &SPU)) / SCALING_FACTOR  ;
})

DEF_CMD("jmpm", JMPM, 2,
{
    a = pop (SPU.stc);
    b = pop (SPU.stc);
    if (a >  b) SPU.ip = (*get_arg(command, &SPU)) / SCALING_FACTOR  ;
    else SPU.ip++;
})

DEF_CMD("jmpl", JMPL, 2,
{
    a = pop (SPU.stc);
    b = pop (SPU.stc);
    //printf("a = %d")
    if (a <  b) SPU.ip = (*get_arg(command, &SPU)) / SCALING_FACTOR  ;
    else SPU.ip++;
})

DEF_CMD("jmpe", JMPE, 2,
{
    a = pop (SPU.stc);
    b = pop (SPU.stc);
    //sprintf("com = 11          a = %d b = %d\n", a, b);
    if (a == b) SPU.ip = (*get_arg(command, &SPU)) / SCALING_FACTOR  ;
    else SPU.ip++;
})

DEF_CMD("call", CALL, 2,
{
    //printf("com = 12\n");
    push(SPU.returns, SPU.ip + 1);
    SPU.ip             = (*get_arg(command, &SPU)) / SCALING_FACTOR  ;
})

DEF_CMD("ret", RETURN, 0,
{
//    printf("com = 13\n");
    SPU.ip = pop(SPU.returns);
})

DEF_CMD("sqrt", SQRT, 0,
{
    push(SPU.stc, sqrt (pop(SPU.stc)) * sqrt (SCALING_FACTOR) );
})

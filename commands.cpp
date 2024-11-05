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
    SPU->ip = SPU->numOfCommands + 1;
    SPU->run = 0;  //easy break cycle, using while condition

})

DEF_CMD("pop", POP, 1,
{
    int64_t* argument = get_arg(command, SPU);
    *argument = pop(SPU->stc);
    //printf("uid = %d\n", argument - SPU->registers);
    //printf("pop\n");

})

DEF_CMD("push", PSH, 1,
{
    int64_t* argument = get_arg(command, SPU);
    push (SPU->stc, (*argument) );

})

DEF_CMD("add", ADD, 0,
{
    //printf("333\n");
    push (SPU->stc, pop (SPU->stc) + pop (SPU->stc));
})

DEF_CMD("mul", MUL, 0,
{
//    printf("444\n");
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    push (SPU->stc, (a * b) / SCALING_FACTOR);
})

DEF_CMD("sub", SUB, 0,
{
  //  printf("555\n");
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    push (SPU->stc, b - a);
})

DEF_CMD("look", LUK, 0,
{
    //printf("look");
    double a = (double)pop(SPU->stc) / SCALING_FACTOR;
    printf ("return look = %f\n", (a));
})

DEF_CMD("div",  DIV, 0,
{
//    printf("777\n");
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    push (SPU->stc, ((double)b / (double)a) * SCALING_FACTOR);
    //printf("div = %d\n", b / a);
})

DEF_CMD("jmp",  JMP,  2,
{
    SPU->ip             = (*get_arg(command, SPU)) / SCALING_FACTOR -1  ;
})

DEF_CMD("jmpm", JMPM, 2,
{
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    if (a >  b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1  ;
    else SPU->ip++;
})

DEF_CMD("jmpl", JMPL, 2,
{
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    //printf("a = %d     b = %d\n", a, b);
    if (a <  b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1  ;
    else SPU->ip++;
    //printf("%d\n", SPU->ip);
})

DEF_CMD("jmpe", JMPE, 2,
{
    int64_t a = pop (SPU->stc);
    int64_t b = pop (SPU->stc);
    if (a == b) SPU->ip = (*get_arg(command, SPU)) / SCALING_FACTOR - 1  ;
    else SPU->ip++;
})

DEF_CMD("call", CALL, 2,
{
    //printf("com = 12\n");
    push(SPU->returns, SPU->ip + 2);
    int a = (*get_arg(command, SPU)) / SCALING_FACTOR - 1;
    SPU->ip             =  a;
    //printf("new ip  = %d\n", SPU.ip);
})

DEF_CMD("ret", RETURN, 0,
{
//    printf("com = 13\n");
    SPU->ip = pop(SPU->returns) - 1;
    //printf("newest ip  = %d\n", SPU.ip);
})

DEF_CMD("sqrt", SQRT, 0,
{
    push(SPU->stc, sqrt (pop(SPU->stc)) * sqrt (SCALING_FACTOR) );
})

DEF_CMD("draw", DRAW, 0,
{
    double x = 0;
    double y = 0;

    for (int64_t i = 0; i < 20 * 20; i ++)
    {
        //printf(" %d ", (i * 3) + 50);
        x = (double)(i % 20) * 20;
        y = (double)(i / 20) * 20;
        //printf("x, y = %lf %lf\n", x, y);
        txSetFillColor(         RGB ( (int)(SPU->RAM)[i * 3 + 50]/1000,   (int)(SPU->RAM)[i * 3 + 51]/1000,      (int)(SPU->RAM)[i * 3 + 52]/1000) );
        txRectangle	(x, y, x + 20, y + 20);
       // printf(" %3d ", (SPU->RAM)[i * 3 + 52]/1000);
        //if( (i + 1) % 20 == 0 ) printf("\n");


    }


           // printf(" %d ", (i * 3) + 50);

})

DEF_CMD("ptch", PTCH_MY, 0,
{
    printf ("return ptch = _%c_\n", ((int64_t)pop(SPU->stc) / SCALING_FACTOR) );
})

DEF_CMD("input", INPT, 0,
{
    double a = 0;
    scanf("%f", &a);
    push (SPU->stc, (int64_t)(a * SCALING_FACTOR));
})

DEF_CMD("sin", SIN, 0,
{
    double a = ((double)pop(SPU->stc) / SCALING_FACTOR);
    a = (sin( a ) * SCALING_FACTOR);
    push (SPU->stc, (int64_t)a );
})

DEF_CMD("cos", COS, 0,
{
    double a = ((double)pop(SPU->stc) / SCALING_FACTOR);
    a = (cos( a ) * SCALING_FACTOR);
    push (SPU->stc, (int64_t)a );
})

DEF_CMD("acos", ACOS, 0,
{
    double a = ((double)pop(SPU->stc) / SCALING_FACTOR);
    a = (acos( a ) * SCALING_FACTOR);
    push (SPU->stc, (int64_t)a );
})

DEF_CMD("popv", POPV, 1,
{
    int64_t* argument = get_arg(command, SPU);
    *argument = pop(SPU->stc);

})

DEF_CMD("pushv", PSHV, 1,
{
      //printf("222\n");
    int64_t* argument = get_arg(command, SPU);
    //printf("pushing arg = %d\n",  (*argument));
    push (SPU->stc, (*argument) );
    //printf("endpush\n");

})


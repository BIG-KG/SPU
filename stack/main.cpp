#include "stack_funk.h"

#include "errors.h"

#include "const.h"




int main()
{
    int64_t stk  = stack_ctor();
    int64_t stk2 = stack_ctor();

    push(stk,  10);
    push(stk2, 20);
    push(stk,  30);
    push(stk2, 40);

    printf("name1 = %d, name2 = %d\n\n", stk, stk2);

    printf("%d\n", pop(stk));
    printf("%d\n", pop(stk));
    printf("%d\n", pop(stk2));
    printf("%d\n", pop(stk2));

    return 0;
}

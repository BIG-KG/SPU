#ifndef INNER_STACK_METODS_H_INCLUDED
#define INNER_STACK_METODS_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct chain_element{

    int64_t name           = 0;
    int32_t hashStack      = 0;
    chain_element *next    = NULL;
    chain_element *prev    = NULL;
    void *storegingElement = NULL;

};

void *stack_pointer(int64_t nameOfStack, int returnOnlyStack);

int64_t right_random_64();

#endif // INNER_STACK_METODS_H_INCLUDED

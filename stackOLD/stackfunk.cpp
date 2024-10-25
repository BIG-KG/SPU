#include "stack_types.h"
#include "stack_funk.h"
#include "errors.h"
#include "const.h"
#include "canary.h"
#include "inner_stack_metods.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int stack_ok(int64_t name){

    void *vptrTargetStack = stack_pointer (name, 1);

    if (!vptrTargetStack){
        Stack_error_global = NULL_STACK_PTR;
        printf("case1\n");
        return NULL_STACK_PTR;
    }

    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if (!(ptrTargetStack->dataPtr)){
        printf("case2\n");
        Stack_error_global = NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }


    int64_t endcannary = *(    (int64_t *)(  (char *)ptrTargetStack->dataPtr + (((sizeof(stackEl) * ptrTargetStack->maxSize / 8)  + 1) * 8)  )   );

    if(  *((int64_t *)( ptrTargetStack->dataPtr) - 1) != canary()
    ||   endcannary != canary()  ) {
        printf("case3\n");
        printf("real canry = %ld, given canry = %ld, lastcanr = %ld\n", canary(), *((int64_t *)(ptrTargetStack->dataPtr) - 1),   endcannary   );
        Stack_error_global = BROKEN_CANNARY;
    }

    if ( (ptrTargetStack->currSize) > (ptrTargetStack->maxSize) ){
        printf("case4\n");
        Stack_error_global = STACK_OVERFLOW;
        return STACK_OVERFLOW;
    }

    if ( (ptrTargetStack->currSize) < 0 ){
        printf("case5\n");
        Stack_error_global = STACK_UNDERFLOW;
        return STACK_UNDERFLOW;
    }

    int tmpErorror = hasher(name, 1);
    if(tmpErorror != 0){
        Stack_error_global = tmpErorror;
        return tmpErorror;
    }

    return 0;

}

void* stack_dump(int64_t name, int checkNeed){

    void *vptrTargetStack = stack_pointer (name, 1);                                       //.ûהגמûלג

    if (1){


        if(Stack_error_global == NULL_STACK_PTR || vptrTargetStack == NULL){
            printf("ERROR pointer tustruct is NULL.\n returning lastEl");
            return stack_pointer (-1, 1);
        }



        stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;
        printf("currSize = %d, maxsize = %d\n ", ptrTargetStack->currSize, ptrTargetStack->maxSize);


        if(Stack_error_global == NULL_DATA_PTR || ptrTargetStack->dataPtr == NULL){
            printf("ERROR pointer tustruct is NULL");
            return NULL;
        }

        for(int i = 0; i < ptrTargetStack->currSize; i++){
            printf("\n%d", look(name, i));
        }
        printf("\n");

        return NULL;

    }

    return NULL;
}

int stack_size_chk(int64_t name, int addingSize){

    IF_ERR_GO_OUT(name);

    void *vptrTargetStack = stack_pointer (name, 1);
    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;
    int sizeAfterAdd = ptrTargetStack->currSize + addingSize;

    if(  (sizeAfterAdd)  >=  (ptrTargetStack->maxSize)  ){

        int newSize      = (ptrTargetStack->maxSize) * SIZE_STEP_UP;
        void *tmpDataPtr = realloc (  ((char *)ptrTargetStack->dataPtr - 8) , ((sizeof(stackEl) * newSize / 8)  + 3) * 8  );

        if(tmpDataPtr == NULL){
            printf("ERROR cant expend stack.");
            return OUT_MY_OF_MEMORY;
        }

        plant_canary(tmpDataPtr, newSize, sizeof(stackEl));
        ptrTargetStack->dataPtr  = (char *)tmpDataPtr + 8;
        ptrTargetStack->maxSize *= SIZE_STEP_UP;

        return 0;

    }
    else if(  ((sizeAfterAdd)  <  (ptrTargetStack->maxSize/SIZE_STEP_DOWN))  &&
              ((ptrTargetStack->maxSize) > START_STACK_SIZE)  ){

        ptrTargetStack->maxSize /= SIZE_STEP_DOWN;

        void *tmpDataPtr = realloc(  ((char *)ptrTargetStack->dataPtr - 8) , ((sizeof(stackEl) * ptrTargetStack->maxSize / 8)  + 3) * 8  );

        if(tmpDataPtr == NULL){
            printf("ERROR cant narrow down stack.");
            return OUT_MY_OF_MEMORY;
        }

        plant_canary(tmpDataPtr, ptrTargetStack->maxSize, sizeof(stackEl));
        ptrTargetStack->dataPtr = (char *)tmpDataPtr + 8;

        return 0;

    }


    IF_ERR_GO_OUT(name);

    return 0;

}

int64_t stack_ctor(void){

    chain_element *lstLink = (chain_element *)stack_pointer(-1, 0);
    chain_element *newLink = (chain_element *)calloc(sizeof(chain_element), 1);
    if(!newLink){
    #ifndef NOT_RETURN_ERRORS
        printf("Error out of memory");
    #endif
        Stack_error_global = OUT_MY_OF_MEMORY;
        return OUT_MY_OF_MEMORY;
    }

    lstLink->next = newLink;
    newLink->prev = lstLink;
    int64_t name  = right_random_64();
    newLink->name = name;
    void **VptrTargetStack = &(newLink->storegingElement);

    if(!VptrTargetStack){

    #ifndef NOT_RETURN_ERRORS
        printf("Error, can't make stack, inner stack system is broke");
    #endif

        Stack_error_global = NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }

    stack_t *ptrTargetStack  = (stack_t *)calloc (sizeof(stack_t), 1); // u r wasting WAM
    ptrTargetStack->strCanry = canary(); /* do not make your vars functions*/
    ptrTargetStack->endCamry = canary();
    *VptrTargetStack = ptrTargetStack;

    int realSize        = (  (sizeof(stackEl) * START_STACK_SIZE / 8)  + 3) * 8;
    void *tmpPointer    = (void *)calloc(realSize, 1);

    if(!tmpPointer){
    #ifndef NOT_RETURN_ERRORS
        printf("Error out of memory");
    #endif
        Stack_error_global = OUT_MY_OF_MEMORY;
        return OUT_MY_OF_MEMORY;
    }

    plant_canary(tmpPointer, START_STACK_SIZE, sizeof(stackEl));

    ptrTargetStack->dataPtr  = (char *)tmpPointer + 8;
    ptrTargetStack->currSize = 0;
    ptrTargetStack->maxSize  = START_STACK_SIZE;

    hasher(name, 1);
    IF_ERR_GO_OUT(name);

    return name;
}

int pop(int64_t name){

    IF_ERR_GO_OUT(name);

    void *vptrTargetStack = stack_pointer (name, 1);
    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    if(ptrTargetStack->currSize < 1){
        printf("Error stack is empty");
        Stack_error_global = STACK_UNDERFLOW;
        return STACK_UNDERFLOW;
    }

    int returningEl = *((int*)(ptrTargetStack->dataPtr) + (ptrTargetStack->currSize-1));

    Stack_error_global = stack_size_chk(name, -1);
    if(Stack_error_global != 0){
        printf("sorry, can't pop element.");
        return OUT_MY_OF_MEMORY;
    }
    ptrTargetStack->currSize--;

    hasher(name, 1);
    IF_ERR_GO_OUT(name);

    return returningEl;
}

int push(int64_t name, int pushingEl){
    IF_ERR_GO_OUT(name);


    void *vptrTargetStack = stack_pointer (name, 1);
    stack_t * ptrTargetStack = (stack_t *)vptrTargetStack;

    Stack_error_global = stack_size_chk(name, 1);
    if(Stack_error_global != 0){
        printf("sorry, can't pop element.");
        return OUT_MY_OF_MEMORY;
    }
    ptrTargetStack->currSize++;
    *((int*)(ptrTargetStack->dataPtr) + (ptrTargetStack->currSize - 1)) = pushingEl;

    hasher(name, 1);
    IF_ERR_GO_OUT(name);

    return stack_ok(name);

}

int look(int64_t name, int ElNum){   // add stack to all names

    IF_ERR_GO_OUT(name);

    void *vptrTargetStack = stack_pointer (name, 1);

    stack_t * ptrTtargetStack = (stack_t *)vptrTargetStack;


    IF_ERR_GO_OUT(name);

    return *((int*)(ptrTtargetStack->dataPtr) + (ElNum));

}

int stack_dtor(int64_t name){

    chain_element *targetLink = (chain_element *)stack_pointer(name, 0);

    void *vptrTargetStack = stack_pointer(name, 1);

    if(vptrTargetStack != NULL){

        if(  (Stack_error_global != NULL_STACK_PTR)){

            stack_t * ptrTtargetStack = (stack_t *)(vptrTargetStack);

            if(  (Stack_error_global != NULL_DATA_PTR) ){
                free((char *)ptrTtargetStack->dataPtr - 8);
            }
            free(ptrTtargetStack);   // POISON (if debug)
        }
    }


    if(targetLink != NULL){
        targetLink->prev->next = targetLink->next;
        if(targetLink->next != NULL){
            targetLink->next->prev = targetLink->prev;
        }
        free(targetLink);

    }
    else{
        printf("\nStack alredy has been deleated");
    }
    return 0;
}

static int hasher(int64_t name, int changeHash){

    // make a function which takes memory and returns hash
    chain_element *targetLink = (chain_element *)stack_pointer(name, 0);
    stackEl *targetData = (stackEl *)((stack_t *)targetLink->storegingElement)->dataPtr ;
    int num_ofElements  =            ((stack_t *)targetLink->storegingElement)->currSize;
    int32_t tmpHash     = 0;

    for(int i = 0; i < num_ofElements; i ++){
        tmpHash += targetData[i];
        tmpHash += (tmpHash << 10);
        tmpHash ^= (tmpHash >> 6 );
    }
    tmpHash += (tmpHash << 3);
    tmpHash ^= (tmpHash >> 11);
    tmpHash += (tmpHash << 15);

    if(changeHash == 1){

        targetLink->hashStack = tmpHash;

    }

    else{

        if(targetLink->hashStack != tmpHash){

            printf("\n\n\n\n\nStack broked :'( \n");
            Stack_error_global = WRONG_MY_HASH;
            return WRONG_MY_HASH;
        }

    }

    return(0);
}

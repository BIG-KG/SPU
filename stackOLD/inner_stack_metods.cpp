#include "inner_stack_metods.h"
#include "stdio.h"

void *stack_pointer(int64_t nameOfStack, int returnOnlyStack){

    static chain_element stackChainArray = {};

    chain_element *currentChain = &stackChainArray;

    if (nameOfStack != -1 && nameOfStack != 0){
        while (currentChain->name != nameOfStack){
            if (currentChain->next == NULL){
                return NULL;
            }
            currentChain = currentChain->next;
        }
    }

    else if(nameOfStack == 0){
        return currentChain;
    }

    else{
        while (currentChain->next != NULL){
            currentChain = currentChain->next;
        }
    }

    if(returnOnlyStack == 1){
        return currentChain->storegingElement;
    }
    return currentChain;


}

int64_t right_random_64(){                          //ÃÅÍÅĞÈĞÓÅÒ ÏĞÀÂÈËÜÍÛÉ, Ñ ÒÎ×ÊÈ ÇĞÅÍÈß ÏĞÎÃÈ ĞÀÍÄÎÌ

    int64_t result = 0;
    static int random_cay = 0;

    random_cay++;
    while(result == 0 || result == -1){
        result = ((int64_t)rand())<<32;             // FULL COVERAGE INT_64
        result = result | (int64_t)rand();
        result = result * random_cay;               //ADD RANDOM, AND EL-TS DONT REAPEAT
        result = result % 512;                      //ÄËß ÓÄÎÁÍÎÉ ĞÀÁÎÒÛ Ñ İË-ÌÈ
    }

    return result;
}





 #include <stdio.h>
#include "demo.h"

void demo() {
    int class = 0;  //This will be an error in C++
    #ifdef NDEBUG
        printf("demo/1.0-(pure C): Hello World Release!\n");
    #else
        printf("demo/1.0-(pure C): Hello World Debug!\n");
    #endif
}

#ifndef MY_STACK_STACK_H
#define MY_STACK_STACK_H

#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <unistd.h>

#include "print_log.h"

typedef int data_t;


static data_t  CAN1 = (data_t)random();
static data_t  CAN2 = (data_t)random();


class Stack
{
    data_t canary1;

    data_t* data;
    size_t capacity = 0;
    size_t size = 0;

    data_t hash_ref;
    data_t hash_new;
    data_t canary2;

    error_stack StackOK();
    error_stack Realloc();
    data_t Hash_Refresh();

public:

    Verificator verificator;

    error_stack Test(error_stack error);
    Stack();
    explicit Stack(size_t capacity_);
    error_stack Push(data_t value);
    data_t Pop();
    error_stack Clean();
    size_t Size();
    size_t Capacity();
    bool IsEmpty();
    bool IsFull();
    error_stack Dump();
    Stack* Copy();
    ~Stack();

    Stack& operator=(const Stack&) = delete;
    Stack(const Stack&) = delete;
};

#define assert_( what, ref, format )                                    \
          do                                                            \
          {                                                             \
            if((what) != ref)                                           \
            {                                                           \
                stk->verificator.print_file("Failed:"                   \
                       " while acting in  "                             \
                       "function: "                                     \
                       "%s,\n expected : %"#format"\n",                 \
                       #what ,  ref);                                   \
            }                                                           \
            else                                                        \
            {                                                           \
                stk->verificator.print_file("\n\tFrom unittest:\t"      \
                                #what"....Passed....\n\n");             \
            }                                                           \
                                                                        \
                                                                        \
          } while(0)


#endif //MY_STACK_STACK_H

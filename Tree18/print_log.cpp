#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "print_log.h"

#define EXIT
#ifdef EXIT
#define exit( num ) if(1) exit( num )
#else
#define exit( num ) if(0) exit( num )
#endif

//FILE* file_name = fopen("print_log_tree.txt", "w+" );


Verificator::Verificator(const char* file_name)
{
    if(file_name == nullptr)
    {
        last_error = BAD_PTR;
    }
    assert(file_name);

    //printf("Verificator(file_name) constructor\n");
    this->log_file = fopen(file_name, "w+" );
    if(this->log_file == nullptr)
    {
        last_error = FILE_ERR;
    }
}

Verificator::~Verificator()
{
    //printf("Verificator() DESstructor\n");
    if(fclose(this->log_file) != 0)
    {
        assert(0);
        last_error = CLOSE_ERR;
    }
    this->log_file = nullptr;
}

error_tree Verificator::PrintLog()
{
    switch (this->last_error)
    {
        case  BAD_DATA_PTR:
            this->print_file("ERROR: the pointer on this->data is nullptr: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_DATA_PTR);
            return BAD_DATA_PTR;
        case  LEFT_CAN_KILLED:
            this->print_file("ERROR: the canary1 was killed: YOU CAN'T USE STACK ANYMORE\n");
            exit(LEFT_CAN_KILLED);
            return LEFT_CAN_KILLED;
        case  RIGHT_CAN_KILLED:
            this->print_file("ERROR: the canary2 was killed: YOU CAN'T USE STACK ANYMORE\n");
            exit(RIGHT_CAN_KILLED);
            return RIGHT_CAN_KILLED;
        case  BAD_SIZE:
            this->print_file("ERROR: this->size is less than zero: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_SIZE);
            return BAD_SIZE;
        case  BAD_CAPACITY:
            this->print_file("ERROR: this->capacity is less than zero: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_CAPACITY);
            return BAD_CAPACITY;
        case  SIZ_BIGGER_CAP:
            this->print_file("ERROR: this->size is bigger than this->capacity: YOU CAN'T USE STACK ANYMORE\n");
            exit(SIZ_BIGGER_CAP);
            return SIZ_BIGGER_CAP;
        case  FILE_ERR:
            this->print_file("ERROR: file was not opened: YOU CAN'T USE STACK ANYMORE\n");
            exit(FILE_ERR);
            return FILE_ERR;
        case  CLOSE_ERR:
            this->print_file("ERROR: file was not correctly closed: YOU CAN'T USE STACK ANYMORE\n");
            exit(CLOSE_ERR);
            return CLOSE_ERR;
        case  BAD_PTR:
            this->print_file("ERROR: the pointer is nullptr: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_PTR);
            return BAD_PTR;
        case  BAD_CONNECTION:
            this->print_file("ERROR: the pointer on the root and child is incorrect!\n");
            exit(BAD_CONNECTION);
            return BAD_CONNECTION;
        case  INVALID_ADD:
            this->print_file("ERROR: the add-function is trying to add to a non_null child!\n");
            exit(INVALID_ADD);
            return INVALID_ADD;
        case  BAD_HASH:
            this->print_file("ERROR: the hash was spoilt: YOU CAN'T USE STACK ANYMORE\n");
            exit(BAD_HASH);
            return  BAD_HASH;
        case  STACKOVERFLOW:
            this->print_file("ERROR: stack is overflow: YOU CAN'T USE STACK ANYMORE\n");
            exit(STACKOVERFLOW);
            return STACKOVERFLOW;
        case  STACKUNDERFLOW:
            this->print_file("ERROR: stack is underflow: YOU CAN'T USE STACK ANYMORE\n");
            exit(STACKUNDERFLOW);
            return STACKUNDERFLOW;
        default:
            return NO_ERR;
    }


}

error_tree Verificator::print_file(const char *fmt, ... )
{
    if(fmt == nullptr)
    {
        this->last_error = BAD_PTR;
    }
    if(this == nullptr)
    {
        this->last_error = BAD_PTR;
    }

    va_list args;
    va_start( args, fmt );
    vfprintf(this->log_file, fmt, args );
    va_end( args );

    return this->last_error;
}

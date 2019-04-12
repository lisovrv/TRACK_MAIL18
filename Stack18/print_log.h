#ifndef TEST_OK_TEST_OK_H
#define TEST_OK_TEST_OK_H
#include <stdio.h>
#include <stdlib.h>

#include "enum.h"

/**
 *
 *
 * Class TestOK is for checking errors
 */

class Verificator
{
    FILE* verificator; /// Output file for printing errors

public:

    error_stack last_error;
    Verificator();
    explicit Verificator(const char* file_name);
    error_stack print_file(const  char *fmt, ... );       /// print in file
    error_stack PrintLog();
    ~Verificator();
};




#endif //TEST_OK_TEST_OK_H

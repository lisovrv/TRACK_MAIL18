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
    FILE* log_file; /// Output file for printing errors

public:

    error_tree last_error;
    explicit Verificator(const char* file_name);
    error_tree print_file(const  char *fmt, ... );        /// print in file
    error_tree PrintLog();
    ~Verificator();

    Verificator& operator = (const Verificator&) = delete;
    Verificator(const Verificator&) = delete;
};




#endif //TEST_OK_TEST_OK_H

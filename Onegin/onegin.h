//
// Created by lisovrv on 11/2/18.
//

#ifndef MS_ONEGIN_ONEGIN_H
#define MS_ONEGIN_ONEGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

/*
 * TODO:
 * stat вместо fseak
 * strchr
 * убрать exit
 * comaprator свой
 * fread возвр значение.
 * большой кусок в функцию
 */

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------DEFINES---------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

enum Sort_kind
{
    VICEVERSA =  20,
    STRAIGHT  =  10,
    NONE      =  0
};



///Structure Strings

typedef struct String_view
{
    char* string; ///< String with data
    int length;   ///< It's length
}String_view;

///Error codes
enum errors {
    OK              = 0,    ///< if everything is Ok
    FOUT_ERR        = -10,  ///< if file was not opened
    FIN_ERR         = -11,  ///< if file was not opened
    FILE_SIZE       = -3,   ///< if unit test shows that root_num is different
    PTR_BAD         = -12,   ///< if in the case of single root unit test shows error
    COUNT_LINE      = -5,    ///< if answer of root1 is not equal to unit answer
    FREAD_ERR       = -7,
    POISON          = -10000,
    POISON_PTR      = 101010

};


//----------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------FUNCTIONS-----------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

String_view*    Sort_str        (int sort_kind, String_view* strings, int count_real_lines);
//String_view*    Vice_versa_str  (String_view* strings, int count_real_lines);
int             Onegin          (int sort_kind, FILE* fout, FILE* fin);
long            Sizeof_file     (FILE *fin);
int             Count_line      (char *buff, long file_size);
String_view*    Make_buffstr    (char* buff, int count_line, long file_size, int* count_empty);
int             File_OK         (FILE* fin);
int             Comparator      (const void* const_str1, const void* const_str2);
int             Test_OK         (int err);
void            Free_mem        (char* buff, char* buff_copy, String_view* strings_copy, String_view* strings);


#endif //MS_ONEGIN_ONEGIN_H

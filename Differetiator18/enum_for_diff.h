enum type
{
    Func        = 22,
    Var         = 33,
    Const       = 44
};

enum functions
{
#define DEFCMD( func, num , name ) func = (num),

#include "commands.h"

#undef DEFCMD

};

enum vars
{
    Var_x           = 200,
    Var_y           = 201
};



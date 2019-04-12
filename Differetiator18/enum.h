#ifndef TREE18_ENUM_H
#define TREE18_ENUM_H

enum error_tree
{
//---------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONTAINER_ENUM------------------------------------------
//---------------------------------------------------------------------------------------------------------
    BAD_DATA_PTR         = 50,
    LEFT_CAN_KILLED      = 51,
    RIGHT_CAN_KILLED     = 52,
    BAD_SIZE             = 53,
    BAD_CAPACITY         = 54,
    SIZ_BIGGER_CAP       = 55,
    STACKOVERFLOW        = 56,
    STACKUNDERFLOW       = 57,
    BAD_HASH             = 58,
    BAD_CONNECTION       = 59,
    INVALID_ADD          = 60,
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------TESTOK_ENUM-------------------------------------------
//---------------------------------------------------------------------------------------------------------
            NO_ERR               = 777,
    FILE_ERR             = 101,
    FILE_SIZE            = 110,
    CLOSE_ERR            = 102,
    BAD_PTR              = 103
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
};

#endif //TREE18_ENUM_H

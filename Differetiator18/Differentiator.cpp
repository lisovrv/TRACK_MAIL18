#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "Differentiator.h"


Node* Dif::Differentiator(Node *root)
{
    FILE* fin = fopen("Document777.tex", "aw");
    assert(root);
    switch((int)root->type)
    {
        case Func:
            switch((int)root->value)
            {
                            #define DEFCMD(func, num, name )        \
                            case func:                              \
                            func##_tex(fin, root);                  \
                            root = func##_diff(root);               \
                            break;

                            #include "commands.h"
                            #undef DEFCMD
                default:
                    break;
            }
            break;
        case Var:
            switch((int)root->value)
            {
                case Var_x:
                    Var_x_tex(fin, root);
                    root = Var_x_diff();
                    break;
                case Var_y:
                    Var_y_tex(fin, root);
                    root = Var_y_diff();
                    break;
                default:
                    break;
            }
            break;
        case Const:
            Const_tex(fin, root);
            root = Const_diff();
            break;
        default:
            break;
    }
    fclose(fin);
    return root;
}

Node* Dif::Sqrt_diff(Node *root)
{
    return DIVIDE(MULTY(CONST(2), SQRT), dR);
}

Node* Dif::Log_diff(Node *root)
{
    return DIVIDE(dR, cR);
}


Node* Dif::Exp_diff(Node *root)
{
    return MULTY(EXP, dR);
}

Node* Dif::Tan_diff(Node *root)
{
    return MULTY(DIVIDE(CONST(1),MULTY(COS, COS)), dR);
}

Node* Dif::Cotan_diff(Node *root)
{
    return MULTY(DIVIDE(CONST(-1),MULTY(SIN, SIN)), dR);
}


Node* Dif::Cos_diff(Node *root)
{
    return MULTY(MINUS( CONST(0), SIN), dR);
}

Node* Dif::Sin_diff(Node *root)
{
    return MULTY(COS, dR);
}

Node* Dif::Plus_diff(Node *root)
{
    return PLUS(dL, dR);
}

Node* Dif::Minus_diff(Node *root)
{
    return MINUS(dL, dR);
}

Node* Dif::Const_diff()
{
    return CONST(0);
}


Node* Dif::Var_x_diff()
{
    return CONST(1);
}

Node* Dif::Var_y_diff()
{
    return CONST(0);
}


Node* Dif::Divide_diff(Node *root)
{
    return DIVIDE(MINUS(MULTY(dL, cR), MULTY(dR, cL)), MULTY(cR, cR));
}

Node* Dif::Multy_diff(Node* root)
{
    return PLUS(MULTY(dL, cR),MULTY(dR, cL));
}







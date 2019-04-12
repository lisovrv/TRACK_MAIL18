#ifndef RDP
#define RDP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#define LENGTH_OF_FORMULA 150


class Rdp
{
    char* formula_str;
    int position;

    Node* GetN(Tree* tree);
    Node* GetE(Tree* tree);
    Node* GetT(Tree* tree);
    Node* GetP(Tree* tree);
    Node* Get_sin(Tree* tree);
    Node* Get_cos(Tree* tree);
    Node* Get_tg(Tree* tree);
    Node* Get_ctg(Tree* tree);
    Node* Get_x(Tree* tree);
    Node* Get_y(Tree* tree);
    Node* Get_ln(Tree* tree);
    Node* Get_sqrt(Tree* tree);
    Node* Get_exp(Tree* tree);


public:
    Rdp();
    Tree* GetTree(const char* sting_);
    ~Rdp();

};


#endif

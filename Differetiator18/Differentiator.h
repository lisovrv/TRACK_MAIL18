#ifndef DIFFER
#define DIFFER

#include <stdlib.h>
#include <stdio.h>

#include "RDP_diff.h"
#include "DSL.h"


class Dif: public Tree
{
private:
    Node* Plus_diff(Node *root);
    Node* Minus_diff(Node *root);
    Node* Multy_diff(Node *root);
    Node* Sin_diff(Node *root);
    Node* Divide_diff(Node *root);
    Node* Var_x_diff();
    Node* Var_y_diff();
    Node* Const_diff();
    Node* Cos_diff(Node *root);
    Node* Tan_diff(Node *root);
    Node* Cotan_diff(Node *root);
    Node* Exp_diff(Node *root);
    Node* Sqrt_diff(Node *root);
    Node* Log_diff(Node *root);
//---------------------------------------------------------------------------------------------------------
//----------------------------------------------OPTIMISATION-----------------------------------------------
//---------------------------------------------------------------------------------------------------------
    double OptConst(Node *root);
    void One_Nul_Opt(Node * root);
//---------------------------------------------------------------------------------------------------------
//-----------------------------------------------PRINTTEX---------------------------------------------------
//---------------------------------------------------------------------------------------------------------

    void Print_only_formula(FILE *fin, Node *root);

    void Sqrt_tex(FILE* fin, Node * root);
    void Exp_tex(FILE* fin, Node * root);
    void Log_tex(FILE* fin, Node * root);
    void Tan_tex(FILE* fin, Node * root);
    void Cos_tex(FILE* fin, Node * root);
    void Sin_tex(FILE* fin, Node * root);
    void Cotan_tex(FILE* fin, Node * root);
    void Plus_tex(FILE* fin, Node * root);
    void Minus_tex(FILE* fin, Node * root);
    void Multy_tex(FILE* fin, Node * root);
    void Divide_tex(FILE* fin, Node * root);
    void Var_y_tex(FILE *fin, Node *root);
    void Var_x_tex(FILE *fin, Node *root);
    void Const_tex(FILE *fin, Node *root);

    void Minus_opt_tex(Node* root);
    void Plus_opt_tex(Node* root);
    void Multy_opt_tex(Node* root);
    void Divide_opt_tex(Node* root);

    void Null_right_multy_tex(Node* root);
    void Null_left_multy_tex(Node* root);
    void One_right_multy_tex(Node* root);
    void One_left_multy_tex(Node* root);
    void Null_right_plus_tex(Node* root);
    void Null_left_plus_tex(Node* root);
    void Null_right_minus_tex(Node* root);




public:
    Node* Differentiator(Node* root);
    void Optimisation(Node * root);
    void PrintTEX(Node * tree);
};

#endif

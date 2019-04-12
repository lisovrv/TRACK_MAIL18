#ifndef DIFFERENTIATOR18_DSL_H
#define DIFFERENTIATOR18_DSL_H

#define CREATE_SUBTREE( type, value, left, right)   Create_Sub_Tree( type, value,       \
                                                    left, right)

#define CONST( num )    CREATE_SUBTREE(Const, num , nullptr, nullptr)
#define SIN             CREATE_SUBTREE(Func, Sin, nullptr, cR)
#define COS             CREATE_SUBTREE(Func, Cos, nullptr, cR)
#define EXP             CREATE_SUBTREE(Func, Exp, nullptr, cR)
#define SQRT             CREATE_SUBTREE(Func, Sqrt, nullptr, cR)
#define MINUS( left, right ) CREATE_SUBTREE(Func, Minus, left, right)
#define PLUS( left, right ) CREATE_SUBTREE(Func, Plus, left, right)
#define MULTY( left, right ) CREATE_SUBTREE(Func, Multy, left, right)
#define DIVIDE( left, right ) CREATE_SUBTREE(Func, Divide, left, right)


#define dL Differentiator(root->left)
#define dR Differentiator(root->right)

#define cL Copy( root->left )
#define cR Copy( root->right)

#endif //DIFFERENTIATOR18_DSL_H

#ifndef TREELIB
#define TREELIB

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "print_log.h"

#define HASH
#ifdef  HASH
#define _hash_( hash_kind ) if(1) (this->hash_kind) = Hash_Refresh_Tree()
#else
#define _hash_( hash_kind ) if(0) (this->hash_kind) = Hash_Refresh_Tree()
#endif

static long  CAN1 = random();
static long  CAN2 =  random();

typedef const char* data_t;

class Node
{
private:
    long canary1;

public:
    data_t value;
    Node* parent;
    Node* left;
    Node* right;

    explicit Node(data_t value_);
    error_tree PrintDot(const char* filename_for_dot);
    error_tree PrintTree_for_dot(FILE* fin);
    ~Node();

    long Hash_Refresh();
    error_tree NodeOK(Node* node, Verificator& verificator);
    error_tree RecPrint_for_Dump(Node* root, Verificator& verificator);

    Node& operator=(const Node&) = delete;
    Node(const Node&) = delete;

private:
    long canary2;
};

class Tree
{
    long hash_ref;
    long hash_new;
    size_t size;

    error_tree TreeOK();
    long Hash_Refresh_Tree();


public:
    Verificator verificator;
    Node* root;

    explicit Tree(data_t value_);
    error_tree Test(error_tree error_);
    error_tree Dump();

    Tree* Add_Left_Tree(data_t value_, Node* node_);
    Tree* Add_Right_Tree(data_t value_, Node* node_);

    ~Tree();
};



#endif

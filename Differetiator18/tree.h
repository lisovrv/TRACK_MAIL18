#ifndef TREELIB
#define TREELIB

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "print_log.h"
#include "enum_for_diff.h"
#include "DSL.h"


#define HASH
#ifdef  HASH
#define _hash_( hash_kind ) if(1) (this->hash_kind) = Hash_Refresh_Tree()
#else
#define _hash_( hash_kind ) if(0) (this->hash_kind) = Hash_Refresh_Tree()
#endif

#define POISON FLT_MAX

static long  CAN1 = random();
static long  CAN2 =  random();

typedef double data_t;

class Node
{
private:
    long canary1;

public:
    data_t type;
    data_t value;

    Node* parent;
    Node* left;
    Node* right;

    explicit Node(data_t  type, data_t value_);
    error_tree PrintDot(const char* filename_for_dot);
    error_tree PrintTree_for_dot(FILE* fin);
    const char* Label(const char* label_);
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

    Tree();
    explicit Tree(data_t type_, data_t value_);
    error_tree Test(error_tree error_);
    error_tree Dump();

    Node* Copy(Node* root);
    Node* Create_node(data_t type_, data_t value_);
    Node* Create_Sub_Tree(data_t type_, data_t value_, Node* left_, Node* right_);
    Node* Add_Left_Tree(data_t type_, data_t value_, Node* node_);
    Node* Add_Right_Tree(data_t type_, data_t value_, Node* node_);

    ~Tree();
};


//static Node* poison = new Node(POISON, POISON); //instead of nullptr: the leaves of the tree will have left and right prt on "poison"

#endif

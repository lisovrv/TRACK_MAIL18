#include "tree.h"
#include <assert.h>
#include <string.h>

#define POISON INT_MAX

#define LENGTH 50

/**
 * TODO:
 * root or node ?
 *
 *
 * @param value_
 */

Node::Node(data_t value_):
        canary1(CAN1),
        canary2(CAN2),
        value(value_),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
{
    //printf("Node(data_t value_) constructor!\n");
}

Node::~Node()
{
    this->canary1 = POISON;
    this->canary2 = POISON;
    delete this->left;
    delete this->right;
    //printf("Node() DEStructor!\n");
}

Tree::Tree(data_t value_):
        size(1),
        verificator("print_log_tree.txt")
{
    this->root = new Node(value_);
    _hash_(hash_ref);
    _hash_(hash_new);
    //printf("Tree(data_t value) constructor!\n");
}


Tree::~Tree()
{
    this->verificator.last_error = NO_ERR;
    this->Test(this->TreeOK());
    delete this->root;
    this->size = POISON;
    //printf("Tree() DESstructor!\n");
}

error_tree Node::NodeOK(Node* root, Verificator& verificator)
{
    assert(this);
    if(root == nullptr)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(root);

    if(root->canary1 != CAN1)
    {
        verificator.last_error = LEFT_CAN_KILLED;
    }
    if(root->canary2 != CAN2)
    {
        verificator.last_error = RIGHT_CAN_KILLED;
    }
    if(root->parent != nullptr)
    {
        if(root->left != nullptr)
        {
            root->NodeOK(root->left, verificator);
        }
        if(root->parent->left != root && root->parent->right != root)
        {
            verificator.last_error = BAD_CONNECTION;
        }
        if(root->right != nullptr)
        {
            root->NodeOK(root->left, verificator);
        }
    }
    return verificator.last_error;
}

error_tree Tree::TreeOK()
{
    assert(this);
    verificator.last_error = root->NodeOK(root, verificator);
    if(this->root == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
    }
    if(this->size < 0)
    {
        this->verificator.last_error = BAD_SIZE;
    }
    _hash_(hash_new);
    if(this->hash_new != this->hash_ref)
    {
        this->verificator.last_error = BAD_HASH;
    }

    return  this->verificator.last_error;
}


error_tree Tree::Test(error_tree error_)
{
    assert(this);
    verificator.last_error = error_;

    if(verificator.last_error != NO_ERR)
    {
        verificator.PrintLog();
    }
    return verificator.last_error;
}

long Tree::Hash_Refresh_Tree()
{
    assert(this);
    return this->root->Hash_Refresh();
}

long Node::Hash_Refresh()
{
    assert(this);
    long hash = canary1 / canary2 + 777;
    if(this->left != nullptr)
    {
        hash += this->left->Hash_Refresh();
    }

    hash += *(int*) this->value;
    size_t length = strlen(this->value);
    for(int i = 0; i < length; i++)
    {
        hash += (int)(this->value)[i] * i;
    }

    if(this->right != nullptr)
    {
        hash +=  this->right->Hash_Refresh();
    }
    return hash;
}

error_tree Tree::Dump()
{
    assert(this);
    this->verificator.last_error = NO_ERR;
    this->verificator.print_file("\n\n--------------------------------------------------------------------\n");
    this->verificator.print_file("Tree : [%p]\n", this);
    this->verificator.print_file("tree->root [%p] = %s\n", this->root, this->root->value);
    this->verificator.print_file("size = %zu\n", this->size);
    this->verificator.print_file("hash_new = %d\nhash_ref = %d\n", this->hash_new, this->hash_ref);
    this->root->RecPrint_for_Dump(this->root, this->verificator);

    this->verificator.print_file("--------------------------------------------------------------------\n");
    Test(this->TreeOK());
    return this->verificator.last_error;
}

error_tree Node::RecPrint_for_Dump(Node* root, Verificator& verificator)
{
    verificator.last_error = NO_ERR;
    assert(this);
    if(root == nullptr)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(root);

    if(root->left != nullptr)
    {
        root->left->RecPrint_for_Dump(root->left, verificator);
    }
    verificator.print_file("\t\tnode[%p] = %s\t\t\t\t", root, root->value);
    if(root->parent  != nullptr)
    {
        verificator.print_file("node->parent[%p] = %s\n", root->parent, root->parent->value);
    }
    else
    {
        verificator.print_file("parent is nullptr :(\n");
    }
    if(root->right != nullptr)
    {
        root->right->RecPrint_for_Dump(root->right, verificator);
    }
    return verificator.last_error;
}

Tree* Tree::Add_Left_Tree(data_t value_, Node* node_)
{
    assert(this);
    if(node_ == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
    }
    assert(node_);
    this->verificator.last_error = NO_ERR;
    this->Test(this->TreeOK());

    node_->left = new Node(value_);
    node_->left->parent = node_;
    this->size++;

    _hash_(hash_ref);
    _hash_(hash_new);
    return this;
}

Tree* Tree::Add_Right_Tree(data_t value_, Node* node_)
{
    assert(this);
    if(node_ == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
    }
    assert(node_);
    this->verificator.last_error = NO_ERR;
    this->Test(this->TreeOK());

    node_->right = new Node(value_);
    node_->right->parent = node_;
    this->size++;

    _hash_(hash_ref);
    _hash_(hash_new);
    return this;
}



error_tree Node::PrintDot(const char* filename_for_dot)
{
    assert(this);
    error_tree errorTree = NO_ERR;
    FILE * fin = fopen(filename_for_dot, "w");
    if(fin == nullptr)
    {
        errorTree = FILE_ERR;
    }

    fprintf(fin, "digraph graphname {\n");
    fprintf(fin, "\tnode [shape=box]\n");
    this->PrintTree_for_dot(fin);
    fprintf(fin, "}");
    fclose(fin);

    const char* esp = "dot ";
    char* res = (char*) calloc (LENGTH, sizeof(char));
    const char* val = filename_for_dot;
    res = strcat(strcat(res, esp), val);
    const char* jpg = " -Tjpg -O";
    res = strcat(res, jpg);
    system(res);
    free(res);

    //system ("dot tree.dot -Tjpg -O");

    const char* esp2 = "eog ";
    char* res2 = (char*) calloc (LENGTH , sizeof(char));
    const char* val2 = filename_for_dot;
    res2 = strcat(strcat(res2, esp2), val2);
    const char* jpg2 = ".jpg";
    res2 = strcat(res2, jpg2);
    system(res2);
    free(res2);

    //system("xdg-open tree.dot.jpg");  feh - analogy, eog

    return errorTree ;
}

error_tree Node::PrintTree_for_dot(FILE *fin)
{
    error_tree errorTree = NO_ERR;
    if(fin == nullptr)
    {
        errorTree = FILE_ERR;
    }
    assert(fin);
    assert(this);

    fprintf(fin, "\telem_%p [label=\"%s\"];\n", this, this->value);
    if(this->left)
    {
        this->left->PrintTree_for_dot(fin);
        fprintf(fin, "\telem_%p -> elem_%p [label=\"yes\", color=blue];\n", this, this->left);
    }
    if(this->right)
    {
        this->right->PrintTree_for_dot(fin);
        fprintf(fin, "\telem_%p -> elem_%p [label=\"no\", color=blue];\n", this, this->right);
    }
    return errorTree;
}












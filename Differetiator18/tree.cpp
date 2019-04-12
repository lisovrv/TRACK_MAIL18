#include "tree.h"
#include <assert.h>
#include <string.h>

#define LENGTH 50


/**
 * TODO:
 * root or node ?
 *
 */

//-----------------------------------------------------------------------------------------------------------
//----------------------------------CONSTRUCTORS_AND_DESTRUCTORS-------------------------------------------
//-------------------------------------------------------------------------------------------------------------

Node::Node(data_t type_, data_t value_):
        canary1(CAN1),
        canary2(CAN2),
        value(value_),
        type(type_),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
{
    //printf("Node(data_t value_, data_t type) constructor!\n");
}

Node::~Node()
{
    this->value= POISON;
    this->type = POISON;
    this->canary1 = (long)POISON;
    this->canary2 = (long)POISON;
    delete this->left;
    delete this->right;
    //printf("Node() DEStructor!\n");
}

Tree::Tree(data_t type_, data_t value_):
        size(1),
        verificator("print_log_tree.txt")
{
    this->root = new Node(type_, value_);
    _hash_(hash_ref);
    _hash_(hash_new);
    printf("Tree(data_t value, data_t type) constructor!\n");
}

Tree::Tree():
        size(),
        verificator("print_log_tree.txt")
{
    printf("Tree() constructor!\n");
}

Tree::~Tree()
{
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    this->verificator.last_error = NO_ERR;
    //this->Test(this->TreeOK()); ////PROBLEM
    delete this->root;
    this->size = (size_t) POISON;
    printf("Tree() DESstructor!\n");
}

//-----------------------------------------------------------------------------------------------------------
//---------------------------------------CREATING_AND_COPYING-----------------------------------------------
//---------------------------------------------------------------------------------------------------------

Node* Tree::Create_node(data_t type_, data_t value_)
{
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    this->verificator.last_error = NO_ERR;
    if(this->root != nullptr)
    {
        this->Test(this->TreeOK());
    }

    Node* newnode = new Node(type_, value_);
    this->size++;

    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    return newnode;
}

/**
 *
 * Do not use it in the beginnig of creating a tree
 * Useful further, when you need to reconstruct a tree
 *
 *
 *
 */

Node* Tree::Create_Sub_Tree(data_t type_, data_t value_, Node* left_, Node* right_)
{
    //printf("SSSSSSSSSSSSSSSSSS\n");
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    this->verificator.last_error = NO_ERR;
    if(this->root != nullptr)
    {
        this->Test(this->TreeOK());
    }

    Node* root_ = new Node(type_, value_);
    assert(root_);

    this->size++;
    //printf("this->size = %zu  value = %lg  type = %lg  this = %p\n",
    //        this->size, root_->value, root_->type, root_);
    root_->left = left_;
    if(root_->left != nullptr)
    {
        root_->left->parent = root_;
    }
    root_->right = right_;
    if(root_->right != nullptr)
    {
        root_->right->parent = root_;
    }

    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    return root_;
}



Node* Tree::Copy(Node* root)
{
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    Node* newroot = new Node(root->type, root->value);
    this->size++;
    //printf("this->size = %zu  value = %lg  type = %lg  this = %p\n",
     //       this->size, newroot->value, newroot->type, newroot);

    newroot->parent = root->parent;

    if(root->left)
    {
        Node* newnode = Copy(root->left);
        newroot->left = newnode;
    }
    if(root->right)
    {
        Node* newnode = Copy(root->right);
        newroot->right = newnode;
    }
    return newroot;
}

Node* Tree::Add_Left_Tree(data_t type_, data_t value_, Node* node_)
{
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    if(node_ == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
    }
    assert(node_);
    this->verificator.last_error = NO_ERR;
    this->Test(this->TreeOK());

    node_->left = new Node(type_, value_);
    node_->left->parent = node_;
    this->size++;

    _hash_(hash_ref);
    _hash_(hash_new);
    return node_->left;
}

Node* Tree::Add_Right_Tree(data_t type_, data_t value_, Node* node_)
{
    if(this->root != nullptr)
    {
        _hash_(hash_ref);
        _hash_(hash_new);
    }
    if(node_ == nullptr)
    {
        this->verificator.last_error = BAD_PTR;
    }
    assert(node_);
    this->verificator.last_error = NO_ERR;
    this->Test(this->TreeOK());

    node_->right = new Node(type_, value_);
    node_->right->parent = node_;
    this->size++;

    _hash_(hash_ref);
    _hash_(hash_new);
    return node_->right;
}

//-----------------------------------------------------------------------------------------------------------
//---------------------------------------VERIFICATORS-----------------------------------------------
//---------------------------------------------------------------------------------------------------------

error_tree Node::NodeOK(Node* root, Verificator& verificator)
{
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
    verificator.last_error = error_;

    if(verificator.last_error != NO_ERR)
    {
        verificator.PrintLog();
    }
    return verificator.last_error;
}

long Tree::Hash_Refresh_Tree()
{
    return this->root->Hash_Refresh();
}

long Node::Hash_Refresh()
{
    long hash = canary1 / (canary2);
    if(this->left != nullptr)
    {
        hash += this->left->Hash_Refresh();
    }

    hash += (long) this->value;

    if(this->right != nullptr)
    {
        hash +=  this->right->Hash_Refresh();
    }
    return hash;
}

error_tree Tree::Dump()
{
    _hash_(hash_ref);
    _hash_(hash_new);
    this->verificator.last_error = NO_ERR;
    this->verificator.print_file("\n\n--------------------------------------------------------------------\n");
    this->verificator.print_file("Tree : [%p]\n", this);
    this->verificator.print_file("tree->root [%p] = %lg\n", this->root, this->root->value);
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
    if(root == nullptr)
    {
        verificator.last_error = BAD_PTR;
    }
    assert(root);

    if(root->left != nullptr)
    {
        root->left->RecPrint_for_Dump(root->left, verificator);
    }
    verificator.print_file("\t\tnode[%p] = %lg\t\t\t\t", root, root->value);
    if(root->parent  != nullptr)
    {
        verificator.print_file("node->parent[%p] = %lg\n", root->parent, root->parent->value);
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

error_tree Node::PrintDot(const char* filename_for_dot)
{
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

    const char* esp2 = "xdg-open ";
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


    if(this->type == Const)
    {
        fprintf(fin, "\telem_%p [label=\"%lg\"];\n", this, this->value);
    }
    else
    {
        const char* label = new char[LENGTH];
        label = this->Label(label);
        fprintf(fin, "  elem_%p [label=\"%s\"];\n", this, label);
    }

    if(this->left)
    {
        this->left->PrintTree_for_dot(fin);
        fprintf(fin, "\telem_%p -> elem_%p [label=\"left\", color=blue];\n", this, this->left);
    }
    if(this->right)
    {
        this->right->PrintTree_for_dot(fin);
        fprintf(fin, "\telem_%p -> elem_%p [label=\"right\", color=blue];\n", this, this->right);
    }
    return errorTree;
}

const char* Node::Label(const char* label_)
{
    switch((int)this->type)
    {
        case Func:
            switch((int)this->value)
            {
                #define DEFCMD( func, num, name)        \
                                case func:              \
                                label_ = name;          \
                                break;

                #include "commands.h"
                default:
                    break;
            }
            break;
        case Var:
            switch((int)this->value)
            {
                case Var_x:
                    label_ = "x";
                    break;
                case Var_y:
                    label_ = "y";
                    break;
                default:
                    break;
            }
            break;
        #undef DEFCMD
        default:
            break;
    }
    return label_;
}
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "stack.h"

void Unittest(Stack* stk)
{

    int total = 9;
    int passed = 0;

    for(int i = 0; i < total + 1; i++)
    {
        if(stk->Push(i) == NO_ERR)
        {
            printf("\r[%.*s#%.*s]\t", passed, "---------", total - passed, "---------");
            printf("..PASSED..%d\t", i + 1);
            passed++;
            fflush(stdout);
            sleep(1);
        }
    }
}


int main()
{
    auto stk = new Stack(10);

    assert_(stk->Dump(),  NO_ERR , d);
    for(int i = 0; i < 20; i++)
    {
        assert_(stk->Push(i), NO_ERR , d);
    }
    for(int i = 0; i < 10; i++)
    {
        assert_(stk->Pop(), 19 - i , d);
    }
    {auto cp = stk;}
    assert_(stk->Dump(),  NO_ERR , d);

    assert_(stk->Clean(),  NO_ERR , d);
    assert_(stk->Clean(),  NO_ERR , d);
    assert_(stk->Dump(),  NO_ERR , d);
    Stack* stk_new = stk->Copy();
    assert_(stk_new->Dump(),  NO_ERR , d);
    for(int i = 0; i < 20; i++)
    {
        assert_(stk_new->Push(i), NO_ERR , d);
    }
    assert_(stk_new->Dump(),  NO_ERR , d);
    assert_(stk->Dump(),  NO_ERR , d);

    assert_(stk->Size(),  0 , d);
    assert_(stk->Size(),  0 , d);
    assert_(stk->Capacity(),  20 , d);
    assert_(stk->IsFull(),  false , d);
    assert_(stk->IsEmpty(),  true , d);

    Unittest(stk);

    delete stk;
    //delete stk_new;

    return 0;

}



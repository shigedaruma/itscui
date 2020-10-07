//
// 単体テストのテストコード
//
//  伊藤茂行
//  20-06-18

#include "itsut.h"

#if UNIT_TESTING
int main()
{
    try
    {
        printf("hello unit_test world!!\n");
        int v1 = 4;
        int v2 = 5;
        ITS_UT_NEi(v1, v2);
        ITS_UT_LTi(v1, v2);
        ITS_UT_LEi(v1, v2);
        ITS_UT_GTi(v2, v1);
        ITS_UT_GEi(v2, v1);
        //ITS_UT_EQi(v1, v2);
        char const* s1 = "hello";
        char const* s2 = "world";
        char const* s3 = "hello";
        //char const* s4 = nullptr;
        ITS_UT_EQs(s1, s3);
        ITS_UT_NEs(s1, s2);
        //ITS_UT_EQs(s1, s2);
        //ITS_UT_EQs(s1, s4);
        return 0;
    }
    catch(its::ut::FailureException& e)
    {
        e();
        return 1;
    }
}
#else
int main()
{
    return 0;
}
#endif

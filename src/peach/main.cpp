#include <peach/peach.h>

namespace peach
{
    namespace ttt
    {
        struct TTTTT
        {};
    } // namespace ttt
} // namespace peach

struct A123
{
    int a;
    int b;
    int c;
};

class XCCC : public A123
{
    XCCC() : tt(11), cs(11)
    {
        tt    = 123;
        int c = 5;
    }
    int tt;
    int cs;
};

int main()
{
    int ab = 0;
    ab++;
    printf("%d", ab);
    return 0;
}
#define USING_PRINT 1
#include <ZipsLib.h>

int main()
{
    init_libs();
    BEGIN_SETUP();

    while (1)
    {
        sleep_ms(1000);
        LOG("Hello Akron!");
    }

    return 0;
}

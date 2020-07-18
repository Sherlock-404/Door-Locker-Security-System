#include "HMI.h"

int main()
{

    mcu_init();
    while (1)
    {
        idle_mode();
    }
}
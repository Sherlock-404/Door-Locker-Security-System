#include "HMI.h"
int main()
{
    mcu_init();
    initialize_password();
    while (1)
    {
        idle_mode();
    }
}
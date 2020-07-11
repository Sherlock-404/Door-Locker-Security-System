#include "HMI.h"

int main()
{
    mcu_init();
    while (1)
    {
        switch (UART_recieveByte())
        {
        case new_password:
            save_password();
            break;
        case compare_passwords:
            get_password();
            authenticate_password();
            break;
        case open_gate:
            open();
            break;
        case theif:
            alarm_on();
            break;
        }
    }
}
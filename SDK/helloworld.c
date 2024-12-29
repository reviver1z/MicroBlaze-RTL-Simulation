#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"

int main()
{
    init_platform();
    char buff[11];

    static float arr[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    union {
        unsigned int a;
        float b;
    } itof;

    float sum = 0.0;

    // Writing array values to BRAM:
    for (int i = 0; i < 9; i++) {
        itof.b = arr[i];
        Xil_Out32(XPAR_AXI_BRAM_0_BASEADDRESS + (4 * i), itof.a); // Writing to BRAM.
        sum += arr[i]; //Calculates Sum.
    }

    itof.b = sum; //Saving The Result

    // Printing the result
    sprintf(buff, "%f", itof.b);
    xil_printf("Sum = %s\n\r", buff);

    cleanup_platform();
    return 0;
}
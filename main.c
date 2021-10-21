#include <stdio.h>


int main(void) {

    int pin;
    
    for (int i = 1; ; i++) {
        printf("Insert PIN: ");
        scanf("%d", &pin);

        if (pin == 0000) {
            break;
        }
        else if (i == 3) {
            printf("Wrong pin. Exiting program...");
            return 0;
        }
    }
    int function;
    while (1) {
        
        printf("\nFunctions:\nExit (0)\nWithdraw (1)\nBalance (2)\nTransactions (3)\nPrepaid top-up (4)\n");
        printf("Select function: ");
        scanf("%d", &function);
        printf("\n");

        switch (function) {
            case 0:
                printf("Exiting program...");
                return 0;
            
            case 1:
                printf("Withdraw completed. Take the money.\n");
                break;
            
            case 2:
                printf("Your balance is: 2000e\n");
                break;
            
            case 3:
                printf("10.06.2021    -200e\n");
                printf("16.03.2021    -50e\n");
                printf("26.10.2020    +1000e\n");
                printf("05.07.2019    +10e\n");
                break;
            
            case 4: 
                printf("Top-up completed.\n");
                break;

            default: 
                printf("Function not available. Try again.\n");

        }




    }
    return 0;
}
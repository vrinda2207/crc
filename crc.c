#include <stdio.h>
#include <string.h>
/* CRC-CCITT polynomial Assumed 1011 */
char poly[] = "1011";
/* Function to perform CRC calculation and append/check the remainder */
void calculateCrc(char *input, char *output, int mode) {
    strcpy(output, input);  // Copy input to output
    // If mode is 1 (transmission), append zeros to the message for CRC calculation
    if (mode) {
        for (int i = 1; i < strlen(poly); i++) {
            strcat(output, "0");
        }
    }
    // Perform XOR with the generator polynomial
    for (int i = 0; i < strlen(input); i++) {
        if (output[i] == '1') {  // If the bit is '1', perform XOR
            for (int j = 0; j < strlen(poly); j++) {
                output[i + j] = (output[i + j] == poly[j]) ? '0' : '1';  // XOR operation
            }
        }
    }
}
/* Main function */
int main() {
    char data[100], received[100];
    char crcCode[100];
   
    // Sender side
    printf("Enter the input message in binary: ");
    scanf("%s",data);
    // Calculate and append CRC to the data
    calculateCrc(data, crcCode, 1);
    printf("The transmitted message with CRC is: %s%s\n", data, crcCode+ strlen(data));
    // Receiver side
    printf("Enter the received message in binary: ");
    scanf("%s", received);
    // Check if there are any errors in the received message
    calculateCrc(received, crcCode, 0);
    // Check for any non-zero remainder (which indicates an error)
    int errorFound = 0;
    for (int i = strlen(received); i < strlen(received) + strlen(poly) - 1; i++) {
        if (crcCode[i] == '1') {
            errorFound = 1;
            break;
        }
    }
    if (errorFound) {
        printf("Error in data transmission has occurred.\n");
    } else {
        printf("No error in data.\n");
    }
    return 0;
}     

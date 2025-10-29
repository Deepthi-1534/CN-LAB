#include <stdio.h>
#include <string.h>

void xorDivision(char dividend[], char divisor[], char remainder[]) {
    int i, j;
    int divLen = strlen(divisor);
    int msgLen = strlen(dividend);
    for (i = 0; i < msgLen; i++)
        remainder[i] = dividend[i];
    for (i = 0; i <= msgLen - divLen; i++) {
        if (remainder[i] == '1') {
            for (j = 0; j < divLen; j++) {
                remainder[i + j] = (remainder[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }
}

int main() {
    char message[100], generator[50], appended[150], remainder[150], transmitted[150], received[150];
    int msgLen, genLen, i;
    printf("Enter the generator polynomial: ");
    scanf("%s", generator);
    printf("Enter the message: ");
    scanf("%s", message);
    msgLen = strlen(message);
    genLen = strlen(generator);
    strcpy(appended, message);
    for (i = 0; i < genLen - 1; i++)
        appended[msgLen + i] = '0';
    appended[msgLen + genLen - 1] = '\0';
    printf("\nMessage after appending zeros: %s\n", appended);
    xorDivision(appended, generator, remainder);
    char checksum[50];
    for (i = 0; i < genLen - 1; i++)
        checksum[i] = remainder[msgLen + i];
    checksum[genLen - 1] = '\0';
    printf("Checksum (Remainder): %s\n", checksum);
    strcpy(transmitted, message);
    strcat(transmitted, checksum);
    printf("\nTransmitted message (with checksum): %s\n", transmitted);
    printf("\nEnter the received message: ");
    scanf("%s", received);
    xorDivision(received, generator, remainder);
    int error = 0;
    for (i = 0; i < genLen - 1; i++) {
        if (remainder[strlen(received) - genLen + 1 + i] == '1') {
            error = 1;
            break;
        }
    }
    if (error == 0)
        printf("\nReceived message is error-free ✅\n");
    else
        printf("\nError detected in received message ❌\n");
    return 0;
}

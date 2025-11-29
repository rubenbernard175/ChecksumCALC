(298 characters — safe & clean)

---

# 📌 Full Raw Source Code (PASTE STRAIGHT INTO pa02.c)

```c
//RUBEN BERNARD 5583850
/*I Ruben Bernard (5583850) affirm that 
this program is entirely my own work and that I have neither developed my 
code with any 
another person, nor copied any code from any other person, nor permitted 
my code to be copied 
or otherwise used by any other person, nor have I copied, modified, or 
otherwise used programs 
created by others. I acknowledge that any violation of the above terms will 
be treated as 
academic dishonesty.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void print_error_and_exit() { 
    fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
    exit(1); 
} 

unsigned char calculate_8bit_checksum(const char *data, int length) { 
    unsigned char checksum = 0; 
    for (int i = 0; i < length; i++) checksum += data[i];
    return checksum; 
} 

unsigned short calculate_16bit_checksum(const char *data, int length) { 
    unsigned short checksum = 0; 
    for (int i = 0; i < length; i += 2) {
        unsigned short pair = (data[i] << 8) + (i + 1 < length ? data[i + 1] : 'X');
        checksum += pair; 
    }
    return checksum; 
} 

unsigned int calculate_32bit_checksum(const char *data, int length) { 
    unsigned int checksum = 0; 
    for (int i = 0; i < length; i += 4) {
        unsigned int group = (data[i] << 24) |
                             ((i + 1 < length ? data[i + 1] : 'X') << 16) |
                             ((i + 2 < length ? data[i + 2] : 'X') << 8) |
                             (i + 3 < length ? data[i + 3] : 'X');
        checksum += group; 
    }
    return checksum; 
} 

int main(int argc, char *argv[]) { 
    if (argc != 3) print_error_and_exit(); 

    FILE *file = fopen(argv[1],"r");
    if (!file) return perror("File error"), 1;

    int checksum_size = atoi(argv[2]);
    if (checksum_size != 8 && checksum_size != 16 && checksum_size != 32) {
        fclose(file);
        print_error_and_exit();
    }

    char buffer[10000];
    int length=fread(buffer,1,sizeof(buffer)-1,file);
    fclose(file);
    buffer[length]='\0';

    int padded_length=length;
    if(checksum_size==16 && length%2!=0) buffer[padded_length++]='X';
    else if(checksum_size==32 && length%4!=0){
        int pad=4-(length%4);
        for(int i=0;i<pad;i++) buffer[padded_length++]='X';
    }
    buffer[padded_length]='\0';

    printf("\n");
    for(int i=0;i<padded_length;i++){
        putchar(buffer[i]);
        if((i+1)%80==0||i==padded_length-1) putchar('\n');
    }

    unsigned long checksum=0;
    if(checksum_size==8) checksum=calculate_8bit_checksum(buffer,padded_length);
    else if(checksum_size==16) checksum=calculate_16bit_checksum(buffer,padded_length);
    else checksum=calculate_32bit_checksum(buffer,padded_length);

    printf("%2d bit checksum is %8lx for all %4d chars\n",
           checksum_size,checksum&((1UL<<checksum_size)-1),padded_length);

    return 0;
}
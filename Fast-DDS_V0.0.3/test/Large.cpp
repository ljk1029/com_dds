/**
 * 大小端判断
*/
#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t num = 0x12345678;
    uint8_t *ptr = (uint8_t *)&num;
    printf("%x %x %x %x\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    return 0;
}
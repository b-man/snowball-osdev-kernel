/* simple string library */

#include <string.h>
#include <types.h>

char *strcpy(char *restrict str1, const char *restrict str2)
{
        char *ret = str1;

        while ((*str1++ = *str2++) != '\0')
                ;

        *str1 = '\0';

        return ret;
}

int strcmp(const char *str1, const char *str2)
{
        while (*str1 && (*str1 == *str2))
                ++str1, ++str2;

        return (*(const unsigned char*)str1 - *(const unsigned char*)str2);
}

unsigned int strlen(const char *str)
{
        size_t len = 0;

        while (*str++ != '\0')
                ++len;

        return len;
}

int atoi(const char *str)
{
        int val = 0;
        int neg = 0;

        if (*str == '-') {
            neg = 1;
            *str++;
        }

        while (*str != '\0') {
                if ( *str >= '0' || *str <= '9' ) {
                    val *= 10;
                    val += (int)(*str - '0');
                }
                *str++;
        }

        if (neg == 1)
            val = 0 - val;

        return val;
}

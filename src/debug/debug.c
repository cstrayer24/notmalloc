#include "./debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
void printErr(const char *message, ...)
{

    printf("[x] %s\n", message);
}

void printInfo(const char *msgFormat, ...)
{
    va_list args;
    va_start(args, msgFormat);

    char buff[1024];
    vsnprintf(buff, sizeof(buff), msgFormat, args);
    printf("[+] %s\n", buff);
    va_end(args);
}
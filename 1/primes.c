#include "kernel/types.h"
#include "user/user.h"

/** pseudo code:
 * p = get a number from left neighbor
 * print p
 * loop:
 *  n = get a number from left neighbor
 *  if (p does not divide n)
 *      send n to right neighbor
 */ 
int main(int argc, char *argv[]) 
{
    int numbers[100], cnt = 0, i;
    int fd[2];
    for(i=2; i <= 35; i++) {
        numbers[cnt++] = i;
    }
    while(cnt > 0) {
        pipe(fd);
    }
    exit();
}
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int time;
    // int uptime(void);
    time = uptime();
    printf("uptime: %d\n", time);
    
    exit();
}
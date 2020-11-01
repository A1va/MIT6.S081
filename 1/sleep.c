#include "kernel/types.h"
#include "user/user.h"
// 必须先包含types.h文件，否则uint类型报错

int main(int argc, char* argv[]) {

    // 1.传参错误(参考user/mkdir.c的处理方式)
    if(argc != 2) {
        // void fprintf(int, const char*, ...);
        fprintf(2, "usage: sleep <non-negative integer>\n");
        exit();
    }
    // 2.将命令行(字符串)转换为整数
    // int atoi(const char*);
    // while('0' <= *s && *s <= '9')
    //      n = n*10 + *s++ - '0';
    // 通过将整数字符串，逐个整数字符-'0'，转换为整数
    // 不能处理非数字的其他字符
    int integer = atoi(argv[1]);
    
    // user/: int sleep(int);
    sleep(integer);

    exit();
}
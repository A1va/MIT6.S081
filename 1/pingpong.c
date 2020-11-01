#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pid;
    int parent_fd[2] // parent2child pipe
        ,
        child_fd[2]; // child2parent pipe

    // pipe()和fork()的错误处理，参考user/alloctest.c的处理
    // int pipe(int*);
    if (pipe(parent_fd) != 0)
    {
        printf("pipe(parent_fd) failed\n");
        exit();
    }

    if (pipe(child_fd) != 0)
    {
        printf("pipe(child_fd) failed\n");
        exit();
    }

    // int fork(void);
    pid = fork();
    if (pid < 0)
    {
        printf("fork failed");
        exit();
    }

    /**
     * Write a program that uses UNIX system calls to "ping-pong" a byte between two processes over a pair of pipes 
     * , one for each direction. 
     * The parent sends by writing a byte to parent_fd[1] and the child receives it by reading from parent_fd[0].
     * After receiving a byte from parent, the child responds with its own byte by writing to child_fd[1]
     * , which the parent then reads.
     * tips: char--1 byte
     */

    if (pid == 0)
    {
        // child process
        char buffer[2];
        // 在子进程中，只需要child_fd的写入端和parent_fd的读取端，即可发送1字节"o"到父进程
        // 关闭不需要的管道端口
        close(parent_fd[1]);
        close(child_fd[0]);
        // 持续监听并读取parent_fd读取端的数据
        read(parent_fd[0], buffer, 1);
        if (buffer[0] == 'i')
        {
            printf("%d: received ping\n", getpid());
        }
        // 通过child_fd写入端发送1字节"o"到父进程
        write(child_fd[1], "o", 1);
        // close pipe
        close(child_fd[1]);
        close(parent_fd[0]);
    }
    else
    {
        // parent process
        char buffer[2];
        // 在父进程中，只需要parent_fd的写入端和child_fd的读取端，即可发送1字节"i"到子进程
        close(parent_fd[0]);
        close(child_fd[1]);
        // 通过parent_fd写入端发送1字节"i"到子进程
        write(parent_fd[1], "i", 1);
        // 持续监听子进程读取端
        read(child_fd[0], buffer, 1);
        if (buffer[0] == 'o')
        {
            printf("%d: received pong\n", getpid());
        }
        // close pipe
        close(child_fd[0]);
        close(parent_fd[1]);
    }
    exit();
}
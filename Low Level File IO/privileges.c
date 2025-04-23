#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void){
    // Check if the file exists. If it exists, remove it

    unlink("./doc3.txt");

    int fd1 = open("./doc3.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd1 == -1){
        perror("./doc3.txt");
        printf("Error while opening the file doc3 %d", errno);
        exit(0);
    } else {
        printf("File created successfully\n");
        close(fd1);
    }

    // Display current permissions
    system("ls -la ./doc3.txt");

    int chmod_return = chmod("./doc3.txt", S_IRWXU);
    if (chmod_return == -1)
    {
        perror("./doc3.txt");
        printf("Error while changing the permissions of the file doc3 fd1%d", errno);
        exit(0);
    }else{
        printf("Permissions changed successfully fd1\n");
    }

    int fd2 = open("./doc3.txt", O_RDWR, S_IRWXU);
    if (fd2 == -1){
        perror("./doc3.txt");
        printf("Error while opening the file doc3  fd2 %d", errno);
        exit(0);
    }
    else
    {
        char data[5] = "hello";
        int bytes_written = write(fd1, data, 5);

        if (bytes_written == -1)
        {
            perror("./doc3.txt");
            printf("Error while writing the file doc3 fd2 %d", errno);
            exit(0);
        }
        else
        {
            close(fd2);
        }
    }
}
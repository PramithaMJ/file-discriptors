/**
 * @file privileges.c
 * @brief This program demonstrates file permissions and error handling in C.
 * It creates a file named doc3.txt with read, write, and execute privileges,
 * then changes its permissions to read-only.
 * Finally, it attempts to write to the file with error handling.
 * 
 * @details
 * 1. The program starts by including necessary header files for file I/O and error handling.
 * 2. It checks if the file doc3.txt exists and removes it if it does.
 * 3. It creates a new file doc3.txt with read, write, and execute privileges for user, group, and others.
 * 4. It checks for errors during file creation and handles them appropriately.
 * 5. It displays the current permissions of the file.
 * 6. It changes the file permissions to read-only for the user.
 * 7. It checks for errors during permission change and handles them appropriately.
 * 8. It attempts to open the file in read-only mode.
 * 9. It checks for errors during file opening and handles them appropriately.
 * 10. It attempts to write a string to the file and checks for errors during writing.
 * 11. It closes the file and checks for errors during closing.
 * 12. It prints a success message if all operations are successful.
 * 
 * @note This program uses low-level file I/O functions from the POSIX API.
 * @warning Ensure that the file permissions allow writing to doc3.txt.
 * @bug No known bugs.
 * @todo Add error handling for user input (e.g., invalid size).
 * @author PramithaMJ
 * @date 2025-04-23
 * * @section description
 * This program demonstrates file permissions and error handling in C.
 * It creates a file named doc3.txt with read, write, and execute privileges,
 * then changes its permissions to read-only.
 * Finally, it attempts to write to the file with error handling.
 * 
 * 
 * Create and open a file doc3.txt with read,write,execute privileges and close it.
 * Then, change the mode to read only privileges without opening it.
 * Open doc3.txt as read only and Write a program with error handling to write a sentence to it
 */

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
/**
 * @file lseek.c
 * @brief This program demonstrates low-level file I/O in C.
 * It reads specific byte ranges from a source file (doc1.txt) and writes them to a destination file (doc2.txt).
 * 
 * @details
 * 1. The program starts by including necessary header files for file I/O and error handling.
 * 2. It opens the source file (doc1.txt) in read-only mode.
 * 3. It checks for errors during file opening and handles them appropriately.
 * 4. It opens the destination file (doc2.txt) in write-only mode, creating it if it doesn't exist.
 * 5. It checks for errors during file opening and handles them appropriately.
 * 6. It uses lseek to move the file pointer to specific byte positions in the source file.
 * 7. It reads the contents of the source file from the specified byte positions and writes them to the destination file.
 * 8. It checks for errors during reading and writing operations.
 * 9. It closes both files and checks for errors during closing.
 * 10. It prints a success message if all operations are successful.
 * @note This program uses low-level file I/O functions from the POSIX API.
 * 
 * Write a program to read from 15th byte to 30th byte and 40th byte to 50th byte
 * from a doc1.txt and write to doc2.txt
 */
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
    int fd1 = open("./doc1.txt", O_RDONLY | O_CREAT | O_APPEND, S_IRUSR);
    printf("File opened succesfully for reading");
    if (fd1 == -1){
        perror("./doc1.txt");
        printf("Error occured while opening the file %d", errno);
        exit(0);
    } else{
        char data_read1[16];
        lseek(fd1, 14, SEEK_SET); // move the file offset to 15th byte
        int bytes_read1 = read(fd1, data_read1, 16); // now the file offset is 30 so next byte is 31

        char data_read2[11];
        lseek(fd1, 9, SEEK_CUR); // move the file offset to 40th byte
        // SEEK_CUR means current position of the file offset
        // so 40th byte is 9 bytes ahead of the current position
        // so the file offset is 50th byte
        // so the next byte is 51st byte
        // so we read 11 bytes from the file

        int bytes_read2 = read(fd1, data_read2, 11);

        if (bytes_read1 == -1 || bytes_read2 == -1){
            perror("./doc1.txt");
            printf("Error occured while reading from the file %d", errno);
            exit(0);
        }else{
            printf("Read from the file successfully");
            close(fd1);
        }

        int fd2 = open("./doc2.txt", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR);
        if (fd2 == -1){
            perror("./doc2.txt");
            printf("Error while opening the file %d", errno);
            exit(0);
        }

        printf("File opened for writting successfully");

        int bytes_written1 = write(fd2, (void *)data_read1, 16);
        int bytes_written2 = write(fd2, (void *)data_read2, 11);

        if (bytes_written1 == -1 || bytes_written2 == -1){
            perror("./doc2.txt");
            printf("Error occured when writing to the file %d", errno);
            exit(0);
        }

        close(fd2);
        printf("Bytes were written successfully to file");
    }
    return 0;
}
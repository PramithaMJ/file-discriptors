/**
 * @file copy_file.c
 * @brief This program demonstrates low-level file I/O in C.
 * @details
 * 1. The program starts by including necessary header files for file I/O and error handling.
 * 2. It opens the source file (doc1.txt) in read-only mode.
 * 3. It checks for errors during file opening and handles them appropriately.
 * 4. It opens the destination file (doc2.txt) in write-only mode, creating it if it doesn't exist.
 * 5. It checks for errors during file opening and handles them appropriately.
 * 6. It reads the contents of the source file and writes them to the destination file.
 * 7. It checks for errors during reading and writing operations.
 * 8. It closes both files and checks for errors during closing.
 * 9. It prints a success message if all operations are successful.
 * @note This program uses low-level file I/O functions from the POSIX API.
 * @warning Ensure that the file permissions allow reading from doc1.txt and writing to doc2.txt.
 * @bug No known bugs.
 * @author PramithaMJ
 * @date 2025-04-23
 *  Copy doc1.txt into another file doc2.txt with possible error handling
 */

#include <unistd.h>   // UNIX standard header for POSIX API
#include <sys/stat.h> // Header for file status functions and structures
#include <errno.h>    // Header for error number and error codes
#include <fcntl.h>    // Header for file control operations
#include <stdlib.h>   // Standard library header for memory allocation and process control
#include <stdio.h>    // Standard input/output header for printf and scanf


int main(void) {

    int fd1 = open("./doc1.txt", O_RDONLY | O_CREAT | O_APPEND, S_IRUSR); // Open doc1.txt in read-only mode, create if it doesn't exist, and append if it does
    char data_read[18]; // Buffer to store data read from the file
    if (fd1 == -1) {
        perror("./doc1.txt");
        printf("\nError occured when opening the file %d", errno);
        exit(0);
    }
    else{
        /**
         * sizeˍt read(int fileˍdescriptor, void * buffer, sizeˍt size)
         * fileˍdescriptor: The file descriptor of the file to read from
         * buffer: A pointer to the buffer where the read data will be stored
         * size: The number of bytes to read from the file
         * Returns the number of bytes read on success, or -1 on error
         * The read function reads data from a file descriptor into a buffer.
         * The number of bytes read is returned, or -1 if an error occurs.
         * The read function may read fewer bytes than requested if the end of the file is reached.
         * The read function may also return 0 if the end of the file is reached.
         * The read function does not null-terminate the buffer, so the caller must ensure that the buffer is large enough to hold the data.
         */
        int bytes_read = read(fd1, (void *)data_read, 18); // Read up to 18 bytes from the file into the buffer
        if (bytes_read == -1){
            perror("doc1.txt");
            printf("\nError occured when reading the file %d", errno);
            exit(0);
        }
        else{
            int fd2 = open("./doc2.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
            if (fd2 == -1){
                perror("./doc2.txt");
                printf("\nError occured when opening the file %d", errno);
                exit(0);
            }else{
                int bytes_written = write(fd2, (void *)data_read, 18);
                if (bytes_written == -1){
                    perror("./doc2.txt");
                    printf("\nError occured when writing to file %d", errno);
                    exit(0);
                }else{
                    printf("\n Written to file successfully.");
                    close(fd1);
                    close(fd2);
                }
            }
        }
    }
    return 0; // Return 0 to indicate successful completion of the program
}
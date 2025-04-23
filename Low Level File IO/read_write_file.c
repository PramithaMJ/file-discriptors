/**
 * @file read_write_file.c
 * @brief This program demonstrates low-level file I/O in C.
 * It prompts the user for their name and age, then writes this information to a file named doc1.txt.
 * If doc1.txt already exists, it truncates the file and rewrites it.
 * The program includes error handling for file operations.
 * @details
 * 1. The program starts by including necessary header files for file I/O and error handling.
 * 2. It prompts the user to enter the size of their name and reads it.
 * 3. It allocates a character array of the specified size to store the name.
 * 4. It prompts the user to enter their name and reads it into the array.
 * 5. It prompts the user to enter their age and reads it.
 * 6. It opens a file named doc1.txt in write-only mode, truncating it if it already exists.
 * 7. It checks for errors during file opening and handles them appropriately.
 * 8. It writes the name and age to the file, checking for errors during writing.
 * 9. It closes the file and checks for errors during closing.
 * 10. It prints a success message if all operations are successful.
 * @note This program uses low-level file I/O functions from the POSIX API.
 * @warning Ensure that the file permissions allow writing to doc1.txt.
 * @todo Add error handling for user input (e.g., invalid size).
 * @bug No known bugs.
 * @author PramithaMJ
 * @date 2025-04-23
Create a text file named as doc1.txt and write name and age the user input using
standard input to doc1.txt with possible error handling.If doc1.txt exists;
the program should truncate it and rewrite.
 */

#include <unistd.h>   // Provides access to the POSIX operating system API including read(), write(), close() system calls
#include <sys/stat.h> // Defines functions and structures for getting file status (stat, fstat), and file permissions
#include <errno.h>    // Defines errno variable and error codes to identify system call errors
#include <fcntl.h>    // Provides file control operations like open(), and file status flags like O_RDONLY, O_WRONLY
#include <stdlib.h>   // Standard library functions for memory allocation, process control, conversions, etc.
#include <stdio.h>    // Standard input/output library for printf(), scanf(), etc.

int main(void){

    int size; // Variable to store the size of the name
    printf("Enter size of the name: "); // Prompt user for size
    scanf("%d", &size); // Read size from user input
    char name[size]; // Declare a character array to store the name
    printf("\n Enter your name: "); // Prompt user for name
    scanf("%s",name); // Read name from user input
    char age[2]; // Declare an array to store the age
    printf("\n Enter your age: "); // Prompt user for age
    scanf("%s", age); // Read age from user input

    int fd1; // File descriptor for the file
   /**
     * O_WRONLY - Write Only mode (not read-write as incorrectly noted)
     * O_CREAT - Create the file if it doesn't exist
     * O_TRUNC - Truncate the file to 0 bytes if it exists
     * S_IRWXU - Read, write, and execute permissions for the file owner (User)
     * S_IRWXG - Read, write, and execute permissions for the group
     * S_IRWXO - Read, write, and execute permissions for others
     */
    fd1 = open("doc1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO); // Open file in write-only mode, create if it doesn't exist, truncate if it does
    if (fd1 == -1){
        perror("doc1.txt");
        printf("File could not be opened or created proerly. Error number is %d \n", errno); // Print error message if file opening fails
        exit(0); // Exit the program with an error code
    }else{
        printf("File opened successfully \n"); // Print success message if file opens successfully
        printf("Writing to file \n"); // Print message indicating writing to file
        /**
         * size t write(int fileˍdescriptor, void * buffer, size t size);
         * fileˍdescriptor - The file descriptor of the file to write to
         * buffer - A pointer to the data to be written
         * size - The number of bytes to write
         * Returns the number of bytes written on success, or -1 on error
         * The write() function writes data from a buffer to a file descriptor.
         * The size parameter specifies the number of bytes to write.
         * The function returns the number of bytes written, or -1 on error.
         * The buffer parameter is a pointer to the data to be written.
         */
        int byte_written = write(fd1, (void *)name, size); // Write name to file
        if (byte_written == -1){
            perror("doc1.txt");
            printf("File could not be written properly. Error number is %d \n", errno); // Print error message if writing fails
            exit(0); // Exit the program with an error code
        }
        char buffer1[8] = " age is ";
        
        int byte_written1 = write(fd1, (void *) buffer1, 8); // Write "age is" to file
        int byte_written2 = write(fd1, (void *) age, 2); // Write age to file

        if (byte_written2 | byte_written1 == -1){
            perror("doc1.txt"); // Print error message if writing fails
            printf("File could not be written properly. Error number is %d \n", errno); // Print error message if writing fails
            exit(0); // Exit the program with an error code
        }
        printf("File written successfully \n"); // Print success message if writing is successful
        /**
         * int close(int fileˍdescriptor);
         * fileˍdescriptor - The file descriptor of the file to close
         * Returns 0 on success, or -1 on error
         * The close() function closes a file descriptor, releasing any resources associated with it.
         */
        int close_status = close(fd1); // Close the file
        if (close_status == -1){
            perror("doc1.txt");
            printf("File could not be closed properly. Error number is %d \n", errno); // Print error message if closing fails
            exit(0); // Exit the program with an error code
        }
        printf("File closed successfully \n"); // Print success message if file closes successfully
        printf("File doc1.txt created successfully \n"); // Print success message if file is created successfully
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define REQ_PIPE_NAME  "REQ_PIPE_99263"
#define RESP_PIPE_NAME "RESP_PIPE_99263"
#define SHM_NAME "/8G32lC"
#define MAP_FILE_MESSAGE "MAP_FILE"

#define HELLO_MESSAGE "HELLO"
#define PING_MESSAGE "PING"
#define EXIT_MESSAGE "EXIT"
#define PONG_MESSAGE "PONG"
#define CREATE_SHM_MESSAGE "CREATE_SHM"
#define WRITE_TO_SHM_MESSAGE "WRITE_TO_SHM"
#define SUCCESS_MESSAGE "SUCCESS"
#define ERROR_MESSAGE "ERROR"

void write_message(int fd, const char* msg) {
    unsigned char size = strlen(msg);
    write(fd, &size, 1);
    write(fd, msg, size);
}

char* read_message(int fd) {
    unsigned char size;
    read(fd, &size, 1);
    char* msg = (char*)calloc(size + 1, sizeof(char));
    read(fd, msg, size);
    return msg;
}

int main(void) {

    unsigned int shm_size = 0;
    void* shm_addr = NULL;
    
    if(mkfifo(RESP_PIPE_NAME, 0600) != 0) {
        perror("ERROR\ncannot create the response pipe");
        return 1;
    }

    int req_fd = open(REQ_PIPE_NAME, O_RDONLY);
    if(req_fd == -1) {
        perror("ERROR\ncannot open the request pipe");
        return 1;
    }

    int resp_fd = open(RESP_PIPE_NAME, O_WRONLY);
    if(resp_fd == -1) {
        perror("ERROR\ncannot open the response pipe");
        return 1;
    }

    write_message(resp_fd, HELLO_MESSAGE);
    printf("SUCCESS\n");

    while(1) {
        char* msg = read_message(req_fd);

        if(strcmp(msg, PING_MESSAGE) == 0) {
            write_message(resp_fd, PING_MESSAGE);
            write(resp_fd, (unsigned int[]){99263}, sizeof(unsigned int));
            write_message(resp_fd, PONG_MESSAGE);
        } else if(strcmp(msg, EXIT_MESSAGE) == 0) {
            free(msg);
            close(req_fd);
            close(resp_fd);
            unlink(RESP_PIPE_NAME);
            exit(0);
        } else if(strcmp(msg, CREATE_SHM_MESSAGE) == 0) {
            free(msg);
            unsigned int size;
            read(req_fd, &size, sizeof(unsigned int));
            int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0664);
            if(shm_fd == -1) {
                perror("ERROR\nCould not create shared memory");
                write_message(resp_fd, CREATE_SHM_MESSAGE);
                write_message(resp_fd, ERROR_MESSAGE);
            } else {
                ftruncate(shm_fd, size);
                void* addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
                if(addr == MAP_FAILED) {
                    perror("ERROR\nCould not map shared memory");
                    write_message(resp_fd, CREATE_SHM_MESSAGE);
                    write_message(resp_fd, ERROR_MESSAGE);
                } else {
                    write_message(resp_fd, CREATE_SHM_MESSAGE);
                    write_message(resp_fd, SUCCESS_MESSAGE);
                }
                close(shm_fd);
            }
        } else if(strcmp(msg, WRITE_TO_SHM_MESSAGE) == 0) {
        	free(msg);
        	unsigned int offset;
        	unsigned int value;
        	read(req_fd, &offset, sizeof(unsigned int));
        	read(req_fd, &value, sizeof(unsigned int));
        	if (offset + sizeof(unsigned int) <= shm_size) {
            		memcpy(shm_addr + offset, &value, sizeof(unsigned int));
            		write_message(resp_fd, WRITE_TO_SHM_MESSAGE);
            		write_message(resp_fd, SUCCESS_MESSAGE);
        } else {
            write_message(resp_fd, WRITE_TO_SHM_MESSAGE);
            write_message(resp_fd, ERROR_MESSAGE);
        }
      } else if(strcmp(msg, MAP_FILE_MESSAGE) == 0) {
    free(msg);
    char* file_name = read_message(req_fd);

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("ERROR\nCould not open the file");
        write_message(resp_fd, MAP_FILE_MESSAGE);
        write_message(resp_fd, ERROR_MESSAGE);
    } else {
        struct stat sb;
        if (fstat(fd, &sb) == -1) {
            perror("ERROR\nCould not get the file size");
            write_message(resp_fd, MAP_FILE_MESSAGE);
            write_message(resp_fd, ERROR_MESSAGE);
        } else {
            void* addr = mmap(0, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            if (addr == MAP_FAILED) {
                perror("ERROR\nCould not map the file");
                write_message(resp_fd, MAP_FILE_MESSAGE);
                write_message(resp_fd, ERROR_MESSAGE);
            } else {
                write_message(resp_fd, MAP_FILE_MESSAGE);
                write_message(resp_fd, SUCCESS_MESSAGE);
            }
        }
        close(fd);
      }
     free(file_name);
    }

  }
    return 0;
}

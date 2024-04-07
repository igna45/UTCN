#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

typedef struct {
    char name[7];
    int type;
    int size;
    int offset;
} Section;

void printf_variant(){
    printf("99263\n");
}

int is_matching(char* name, char* startswith, char* permissions) {
    struct stat st;
    if (stat(name, &st) == 0) {
        if (startswith != NULL && strncmp(name, startswith, strlen(startswith)) != 0) {
            return 0;
        }
        if (permissions != NULL) {
            char mode_str[5];
            sprintf(mode_str, "%o", st.st_mode & 0777);
            if (strcmp(mode_str, permissions) != 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void list_directory(char* path, int recursive, char* startswith, char* permissions, int ok) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        printf("ERROR\ninvalid directory path\n");
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char entry_path[1024];
        sprintf(entry_path, "%s/%s", path, entry->d_name);
        if (is_matching(entry_path, startswith, permissions)) {
            printf("%s\n", entry_path);
        }
        if (recursive && entry->d_type == DT_DIR) {
            list_directory(entry_path, recursive, startswith, permissions, ok);
        }
        if(ok == 1) break;
    }
    closedir(dir);
}

int parse_file(const char* path) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    //MAGIC
    char magic[5];
    if (lseek(fd, -4, SEEK_END) == -1 || read(fd, magic, 4) != 4) {
        printf("ERROR\nfailed to read magic\n");
        close(fd);
        return 1;
    }
    magic[4] = '\0';
    if (strncmp(magic, "XYSN", 4) != 0) {
        printf("ERROR\nwrong magic\n");
        close(fd);
        return 1;
    }
    
    //HEADER_SIZE
    short header_size;
    if (lseek(fd, -6, SEEK_END) == -1 || read(fd, &header_size, 2) != 2) {
        printf("ERROR\nfailed to read header size\n");
        close(fd);
        return 1;
    }
    
    //VERSION
    int version;
    if (lseek(fd, -header_size, SEEK_END) == -1 || read(fd, &version, 4) != 4) {
        printf("ERROR\nfailed to read header size\n");
        close(fd);
        return 1;
    }
    if (version < 22 || version > 65) {
        printf("ERROR\nwrong version\n");
        close(fd);
        return 1;
    }  
    
    //SECT_NR
    int sect_nr;
    if (lseek(fd, 0, SEEK_CUR) == -1 || read(fd, &sect_nr, 1) != 1) {
        printf("ERROR\nfailed to read header size\n");
        close(fd);
        return 1;
    }
    if (sect_nr < 4 || sect_nr > 14) {
        printf("ERROR\nwrong sect_nr\n");
        close(fd);
        return 1;
    }   
   
    // read section headers
    
    printf("SUCCESS\n");
    printf("version=%d\n", version);
    printf("nr_sections=%d\n", sect_nr);

    for(int i = 0; i < sect_nr; i++){
    Section section;
   
    if(i==0){
   
    // read SECT_NAME
    if (read(fd, &section.name, 6) != 6) {
        printf("ERROR\nfailed to read sect_name\n");
        close(fd);
        return 1;
    }
    // read SECT_TYPE 53 83 85 92 54
    read(fd, &section.type, 2);
        
    if(section.type != 53 && section.type != 83 && section.type != 85 && section.type != 92 && section.type != 54){
        printf("ERROR\nwrong sect_types\n");
        close(fd);
        return 1;
      }

    // read SECT_OFFSET
    if (read(fd, &section.offset, 3) != 3) {
        printf("ERROR\nfailed to read sect_offset\n");
        close(fd);
        return 1;
    }
    
    // read SECT_SIZE
    if (read(fd, &section.size, 4) != 4) {
        printf("ERROR\nfailed to read sect_size\n");
        close(fd);
        return 1;
    }

    // output section info
    printf("section%d: %.*s %d %d\n", i+1, 6, section.name, section.type, section.size);
    } else {
    
    // read SECT_NAME
    if (read(fd, &section.name, 6) != 6) {
        printf("ERROR\nfailed to read sect_name\n");
        close(fd);
        return 1;
    }

    // read SECT_TYPE 53 83 85 92 54
    read(fd, &section.type, 1);
        
    if(section.type != 53 && section.type != 83 && section.type != 85 && section.type != 92 && section.type != 54){
        printf("ERROR\nwrong sect_types\n");
        close(fd);
        return 1;
      }

    // read SECT_OFFSET
    if (read(fd, &section.offset, 4) != 4) {
        printf("ERROR\nfailed to read sect_offset\n");
        close(fd);
        return 1;
    }
    
    // read SECT_SIZE
    if (read(fd, &section.size, 4) != 4) {
        printf("ERROR\nfailed to read sect_size\n");
        close(fd);
        return 1;
    }

    // output section info
    printf("section%d: %.*s %d %d\n", i+1, 6, section.name, section.type, section.size);
    }
    }
    close(fd);
    return 0;
}

int main(int argc, char **argv){

    int ok = 0;
    //1. variant
    if(argc == 2 && strcmp(argv[1], "variant") == 0){
        printf_variant();
        return 0;
    }
    //2. list
    if (argc >= 3 && strcmp(argv[1], "list") == 0) {
        char* path = NULL;
        char* startswith = NULL;
        char* permissions = NULL;
        int recursive = 0;
        int i;
        for (i = 2; i < argc; i++) {
            if (strncmp(argv[i], "path=", 5) == 0) {
                path = argv[i] + 5;
            } else if (strcmp(argv[i], "recursive") == 0) {
                recursive = 1;
            } else if (strncmp(argv[i], "name_starts_with=", 17) == 0) {
                ok = 1;
            } else if (strncmp(argv[i], "permissions=", 12) == 0) {
                ok = 1;
            } else {
                fprintf(stderr, "Usage: %s list [recursive] <filtering_options> path=<dir_path>\n", argv[0]);
                return 1;
            }
        }
        if (path == NULL) {
            fprintf(stderr, "Usage: %s list [recursive] <filtering_options> path=<dir_path>\n", argv[0]);
            return 1;
        }
        list_directory(path, recursive, startswith, permissions, ok);
        printf("SUCCESS\n");
        return 0;
    }
    
    //3. parse
    if (argc != 3 || strncmp(argv[1], "parse", 5) != 0 || strncmp(argv[2], "path=", 5) != 0) {
        printf("Usage: %s parse path=<file_path>\n", argv[0]);
        return 1;
    }
    
    char* path = argv[2] + 5;
    int ret = parse_file(path);
    return ret;
    
}
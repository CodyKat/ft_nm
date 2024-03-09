#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <elf.h>
// void *  mmap(void *, size_t, int, int, int, off_t) __DARWIN_ALIAS(mmap);
// int     munmap(void *, size_t) __DARWIN_ALIAS(munmap);

// struct stat
// {
//     dev_t st_dev;     /* [XSI] ID of device containing file */
//     ino_t st_ino;     /* [XSI] File serial number */
//     mode_t st_mode;   /* [XSI] Mode of file (see below) */
//     nlink_t st_nlink; /* [XSI] Number of hard links */
//     uid_t st_uid;     /* [XSI] User ID of the file */
//     gid_t st_gid;     /* [XSI] Group ID of the file */
//     dev_t st_rdev;    /* [XSI] Device ID */
// #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
//     struct timespec st_atimespec; /* time of last access */
//     struct timespec st_mtimespec; /* time of last data modification */
//     struct timespec st_ctimespec; /* time of last status change */
// #else
//     time_t st_atime;   /* [XSI] Time of last access */
//     long st_atimensec; /* nsec of last access */
//     time_t st_mtime;   /* [XSI] Last data modification time */
//     time_t st_ctime;   /* [XSI] Time of last status change */
//     long st_ctimensec; /* nsec of last status change */
// #endif
//     off_t st_size;          /* [XSI] file size, in bytes */
//     blkcnt_t st_blocks;     /* [XSI] blocks allocated for file */
//     blksize_t st_blksize;   /* [XSI] optimal blocksize for I/O */
//     __uint32_t st_flags;    /* user defined flags for file */
//     __uint32_t st_gen;      /* file generation number */
//     __int32_t st_lspare;    /* RESERVED: DO NOT USE! */
//     __int64_t st_qspare[2]; /* RESERVED: DO NOT USE! */
// };

// using namespace std;
int g_;

#define FILE_SIZE 40

int main(int argc, char *argv[])
{
    int fd;
    struct stat fs;
    char *file;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &fs);
    // cout << "dev_t st_dev : " << fs.st_dev << endl;
    // cout << "ino_t st_ino : " << fs.st_ino << endl;
    // cout << "mode_t st_mode : " << fs.st_mode << endl;
    // cout << "mode_t st_nlink : " << fs.st_nlink << endl;
    // cout << "nlink_t st_nlink : " << fs.st_nlink << endl;
    // cout << "uid_t st_uid : " << fs.st_uid << endl;
    // cout << "gid_t st_gid : " << fs.st_gid << endl;
    // cout << "dev_t st_rdev : " << fs.st_rdev << endl;
    // cout << "off_t st_size : " << fs.st_size << endl;
    // cout << "blkcnt_t st_blocks : " << fs.st_blocks << endl;
    // cout << "blksize_t st_blksize : " << fs.st_blksize << endl;
    // cout << "__uint32_t st_flags : " << fs.st_flags << endl;
    // cout << "__uint32_t st_gen : " << fs.st_gen << endl;

    // file = (char *)malloc(fs.st_size);
    // cout << "fd : " << fd << endl;
    file = (char *)mmap(NULL, fs.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (file == MAP_FAILED)
    { // 매핑에 실패하여 에러메세지가 담긴 경우
        close(fd);
        // perror("Error mmaping the file");
        exit(EXIT_FAILURE);
    }
    Elf64_Ehdr *elf_file = (Elf64_Ehdr *)file;
    printf("%ul", elf_file->e_shoff);
    return 0;
}
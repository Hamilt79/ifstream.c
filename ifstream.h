#ifndef IFSTREAM_H
#define IFSTREAM_H

#include <stddef.h>
#include <stdio.h>

#define IFS_BUFSZ 4096

typedef struct {
    FILE *fp;
    unsigned char buf[IFS_BUFSZ];
    size_t pos;
    size_t len;
    int eof;
    int err;
} ifstream;

int ifs_open(ifstream *s, const char *path);
int ifs_getc(ifstream *s);
int ifs_eof(const ifstream *s);
int ifs_error(const ifstream *s);
void ifs_close(ifstream *s);

#endif

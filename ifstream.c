#include "ifstream.h"

#include <string.h>

static size_t ifs_fill(ifstream *s)
{
    if (s->eof || s->err)
        return 0;
    s->pos = 0;
    s->len = fread(s->buf, 1, IFS_BUFSZ, s->fp);
    if (s->len == 0) {
        if (ferror(s->fp))
            s->err = 1;
        else
            s->eof = 1;
    }
    return s->len;
}

int ifs_open(ifstream *s, const char *path)
{
    memset(s, 0, sizeof *s);
    s->fp = fopen(path, "rb");
    return s->fp ? 0 : -1;
}

int ifs_getc(ifstream *s)
{
    if (s->pos >= s->len && ifs_fill(s) == 0)
        return -1;
    return s->buf[s->pos++];
}

size_t ifs_read(ifstream *s, void *dst, size_t n)
{
    unsigned char *p = dst;
    size_t got = 0;

    while (got < n) {
        size_t take;

        if (s->pos >= s->len && ifs_fill(s) == 0)
            break;
        take = s->len - s->pos;
        if (take > n - got)
            take = n - got;
        memcpy(p + got, s->buf + s->pos, take);
        s->pos += take;
        got += take;
    }
    return got;
}

long ifs_getline(ifstream *s, char *dst, size_t cap)
{
    size_t n = 0;
    int c = -1;

    if (cap == 0)
        return -1;
    while (n + 1 < cap && (c = ifs_getc(s)) != -1 && c != '\n')
        dst[n++] = (char)c;
    dst[n] = '\0';
    if (n == 0 && c == -1)
        return -1;
    return (long)n;
}

int ifs_eof(const ifstream *s)
{
    return s->eof && s->pos >= s->len;
}

int ifs_error(const ifstream *s)
{
    return s->err;
}

void ifs_close(ifstream *s)
{
    if (s->fp)
        fclose(s->fp);
    s->fp = NULL;
}

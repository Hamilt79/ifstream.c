#include "ifstream.h"

#include <string.h>

static size_t ifs_fill(ifstream *s)
{
    if (s->eof || s->err)
        return 0;
    s->pos = 0;
    s->len = fread(s->buf, 1, IFS_BUFSZ, s->fp);
    if (s->len == 0)
        s->eof = 1;
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

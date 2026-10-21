#include "ifstream.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    ifstream s;
    char line[64];
    char buf[8];
    FILE *f;

    f = fopen("t.txt", "wb");
    assert(f);
    fputs("one\ntwo\nthree", f);
    fclose(f);

    assert(ifs_open(&s, "t.txt") == 0);
    assert(ifs_getline(&s, line, sizeof line) == 3);
    assert(strcmp(line, "one") == 0);
    assert(ifs_getline(&s, line, sizeof line) == 3);
    assert(strcmp(line, "two") == 0);
    assert(ifs_getline(&s, line, sizeof line) == 5);
    assert(strcmp(line, "three") == 0);
    assert(ifs_getline(&s, line, sizeof line) == -1);
    assert(ifs_eof(&s));
    ifs_close(&s);

    assert(ifs_open(&s, "t.txt") == 0);
    assert(ifs_read(&s, buf, 8) == 8);
    assert(memcmp(buf, "one\ntwo\n", 8) == 0);
    assert(ifs_getc(&s) == 't');
    ifs_close(&s);

    assert(ifs_open(&s, "nope.txt") == -1);

    remove("t.txt");
    puts("ok");
    return 0;
}

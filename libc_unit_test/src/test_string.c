#ifndef __TEST_STRING_H__
#define __TEST_STRING_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>

#include <stdio.h>
#include <string.h>

#include "test.h"

static void test_memchr(void)
{
    mz_cunit_assert_string(MZ_TRUE, "DEFG", memchr("ABCDEFG", 'D', 70));
    mz_cunit_assert_string(MZ_TRUE, "DEFG", memchr("ABCDEFG", 'D', 7));
    mz_cunit_assert_string(MZ_TRUE, NULL, memchr("ABCDEFG", 'D', 3));

    mz_cunit_assert_string(MZ_TRUE, NULL, memchr("ABCDEFG", 'X', 70));
    mz_cunit_assert_string(MZ_TRUE, NULL, memchr("ABCDEFG", 'X', 7));
    mz_cunit_assert_string(MZ_TRUE, NULL, memchr("ABCDEFG", 'X', 3));

    mz_cunit_assert_string(MZ_TRUE, "\0", memchr("ABCDEFG", '\0', 70));
}

static void test_memcmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0, memcmp("ABCDEFG", "ABCD", 4));
    mz_cunit_assert_int(MZ_TRUE, 0, memcmp("ABCDEFG", "ABCD", 3));
    mz_cunit_assert_int(MZ_TRUE, 1, memcmp("ABCDEFG", "ABCD", 5));

    mz_cunit_assert_int(MZ_TRUE,  0, memcmp("ABCD", "ABCDEFG", 4));
    mz_cunit_assert_int(MZ_TRUE,  0, memcmp("ABCD", "ABCDEFG", 3));
    mz_cunit_assert_int(MZ_TRUE, -1, memcmp("ABCD", "ABCDEFG", 5));
}

static void test_memcpy(void)
{
    char buf[64];
    char *dest;

    dest = memcpy(buf, "ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    memset(buf, 0, sizeof(buf));
    memcpy(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memcpy(buf, "ABCDEFG", 8);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memcpy(buf, "ABCDEFG", 20);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memcpy(buf, "ABCDEFG", 3);
    mz_cunit_assert_string(MZ_TRUE, "ABC", buf);

    memset(buf, 0, sizeof(buf));
    memcpy(buf, "ABCDEFG", 3);
    memcpy(buf + 3, "ABCDEFG", 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCABCD", buf);
}

static void test_memmove(void)
{
    char buf[64];
    char *dest;

    dest = memmove(buf, "ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 8);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 3);
    mz_cunit_assert_string(MZ_TRUE, "ABC", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 3);
    memmove(buf + 3, "ABCDEFG", 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCABCD", buf);
 
    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 8);
    memmove(buf + 3, buf, 3);
    mz_cunit_assert_string(MZ_TRUE, "ABCABCG", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 8);
    memmove(buf + 7, buf, 3);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGABC", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 8);
    memmove(buf + 7, buf, 20);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    memmove(buf, "ABCDEFG", 8);
    memmove(buf + 8, buf, 20);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);
}

static void test_memset(void)
{
    char buf[64];
    char *dest;
    int i;
    
    dest = memset(buf, 10, sizeof(buf));
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    memset(buf, 5, sizeof(buf));
    for (i = 0; i < sizeof(buf); i++)
        mz_cunit_assert_int(MZ_TRUE, 5, buf[i]);

    memset(buf, 0x1234, sizeof(buf));
    for (i = 0; i < sizeof(buf); i++)
        mz_cunit_assert_int(MZ_TRUE, 0x34, buf[i]);
}

static void test_strcat(void)
{
    char buf[64];
    char *dest;

    memset(buf, 0, sizeof(buf));
    dest = strcat(buf, "ABCD");
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);
    
    memset(buf, 0, sizeof(buf));
    strcat(buf, "ABCD");
    strcat(buf, "EFG");
    strcat(buf, "HIJK");
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    memset(buf, 0, sizeof(buf));
    strcat(buf, "ABCD");
    strcat(buf + 2, "EFG");
    strcat(buf + 4, "HIJK");
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    dest = "XYZ";
    memset(buf, 0, sizeof(buf));
    strcat(buf, "ABCD");
    strcat(buf, dest);
    mz_cunit_assert_string(MZ_TRUE, "ABCDXYZ", buf);
}

static void test_strchr(void)
{
    mz_cunit_assert_string(MZ_TRUE, "DEFG", strchr("ABCDEFG", 'D'));
    mz_cunit_assert_string(MZ_TRUE, NULL, strchr("ABCDEFG", 'd'));
    mz_cunit_assert_string(MZ_TRUE, NULL, strchr("ABCDEFG", 'X'));
    mz_cunit_assert_string(MZ_TRUE, "\0", strchr("ABCDEFG", '\0'));

    mz_cunit_assert_string(MZ_TRUE, "CABCABC", strchr("ABCABCABC", 'C'));
}

static void test_strcmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 1, strcmp("ABCDEFG", "ABCD"));
    mz_cunit_assert_int(MZ_TRUE, -1, strcmp("ABCD", "ABCDEFG"));
    mz_cunit_assert_int(MZ_TRUE, 0, strcmp("ABCDEFG", "ABCDEFG"));

    mz_cunit_assert_int(MZ_TRUE, 1, strcmp("ABCDEFG", "\0"));
    mz_cunit_assert_int(MZ_TRUE, 1, strcmp("ABCDEFG", "ABCDABC"));
    mz_cunit_assert_int(MZ_TRUE, -1, strcmp("ABCDABC", "ABCDEFG"));
}

static void test_strcpy(void)
{
    char buf[64];
    char *dest;

    memset(buf, 0, sizeof(buf));
    dest = strcpy(buf, "ABCDEFG");
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "ABCDEFG");
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "ABCDEFG");
    strcpy(buf + 3, "ABCDEFG");
    mz_cunit_assert_string(MZ_TRUE, "ABCABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "ABCDEFG");
    strcpy(buf + 10, "ABCDEFG");
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    dest = "ABCDEFG";
    strcpy(buf, dest);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    dest = "ABCDEFG";
    strcpy(buf, dest + 3);
    mz_cunit_assert_string(MZ_TRUE, "DEFG", buf);
}

static void test_strcspn(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0,  strcspn("ABCDEFGHIJK", "A"));
    mz_cunit_assert_int(MZ_TRUE, 7,  strcspn("ABCDEFGHIJK", "H"));
    mz_cunit_assert_int(MZ_TRUE, 10, strcspn("ABCDEFGHIJK", "K"));

    mz_cunit_assert_int(MZ_TRUE, 3,  strcspn("ABCDEFGHIJK", "DHK"));
    mz_cunit_assert_int(MZ_TRUE, 0,  strcspn("ABCDEFGHIJK", "AK"));
    mz_cunit_assert_int(MZ_TRUE, 3,  strcspn("ABCDEFGHIJK", "KD"));

    mz_cunit_assert_int(MZ_TRUE, 11, strcspn("ABCDEFGHIJK", "X"));
    mz_cunit_assert_int(MZ_TRUE, 11, strcspn("ABCDEFGHIJK", "XY"));
    mz_cunit_assert_int(MZ_TRUE, 3,  strcspn("ABCDEFGHIJK", "XD"));
}

static void test_strdup(void)
{
    char *src = "ABCD";
    char *dest = strdup(src);

    mz_cunit_assert_string(MZ_TRUE, dest, src);
    mz_cunit_assert_int(MZ_FALSE, (int)dest, (int)src);
}

static void test_strerror(void)
{
    //TODO: Unit-Test
}

size_t strlcat(char *  dst, const char *  src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end */
    while (n-- != 0 && *d != '\0')
        d++;
    dlen = d - dst;
    n = siz - dlen;

    if (n == 0)
        return(dlen + strlen(s));
    while (*s != '\0') {
        if (n != 1) {
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';

    return(dlen + (s - src));   /* count does not include NUL */
}

size_t strlcpy(char *  dst, const char *  src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0) {
        while (--n != 0) {
            if ((*d++ = *s++) == '\0')
                break;
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0) {
        if (siz != 0)
            *d = '\0';      /* NUL-terminate dst */
        while (*s++)
            ;
    }

    return(s - src - 1);    /* count does not include NUL */
}

static void test_strlcat(void)
{
    char buf[64];
    char small_buf[4];
    char *dest;
    int count;

    memset(buf, 0, sizeof(buf));
    count = strlcat(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    memset(small_buf, 0, sizeof(small_buf));
    count = strlcat(small_buf, "ABCDEFG", sizeof(small_buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);
    mz_cunit_assert_string(MZ_TRUE, "ABC", small_buf);

    memset(buf, 0, sizeof(buf));
    strlcat(buf, "ABCD", sizeof(buf));
    strlcat(buf, "EFG", sizeof(buf));
    strlcat(buf, "HIJK", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    memset(buf, 0, sizeof(buf));
    strlcat(buf, "ABCD", sizeof(buf));
    strlcat(buf + 2, "EFG", sizeof(buf));
    strlcat(buf + 4, "HIJK", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    dest = "XYZ";
    memset(buf, 0, sizeof(buf));
    strlcat(buf, "ABCD", sizeof(buf));
    strlcat(buf, dest, sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDXYZ", buf);
}

static void test_strlcpy(void)
{
    char buf[64];
    char small_buf[4];
    int count;
    char *dest;

    memset(buf, 0, sizeof(buf));
    count = strlcpy(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    memset(small_buf, 0, sizeof(small_buf));
    count = strlcpy(small_buf, "ABCDEFG", sizeof(small_buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    memset(buf, 0, sizeof(buf));
    strlcpy(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strlcpy(buf, "ABCDEFG", sizeof(buf));
    strlcpy(buf + 3, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strlcpy(buf, "ABCDEFG", sizeof(buf));
    strlcpy(buf + 10, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    dest = "ABCDEFG";
    strlcpy(buf, dest, sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    dest = "ABCDEFG";
    strlcpy(buf, dest + 3, sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "DEFG", buf);

    memset(small_buf, 0, sizeof(small_buf));
    strlcpy(small_buf, "ABCDEFG", sizeof(small_buf));
    mz_cunit_assert_string(MZ_TRUE, "ABC", small_buf);
}

static void test_strlen(void)
{
    mz_cunit_assert_int(MZ_TRUE, 7, strlen("ABCDEFG"));
    mz_cunit_assert_int(MZ_TRUE, 0, strlen("\0"));
}

static void test_strncat(void)
{
    char buf[64];
    char *dest;

    memset(buf, 0, sizeof(buf));
    dest = strncat(buf, "ABCD", 4);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);
    
    memset(buf, 0, sizeof(buf));
    strncat(buf, "ABCD", 4);
    strncat(buf, "EFG", 3);
    strncat(buf, "HIJK", 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    memset(buf, 0, sizeof(buf));
    strncat(buf, "ABCD", 4);
    strncat(buf + 2, "EFG", 3);
    strncat(buf + 4, "HIJK", 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFGHIJK", buf);

    dest = "XYZ";
    memset(buf, 0, sizeof(buf));
    strncat(buf, "ABCD", 4);
    strncat(buf, dest, 3);
    mz_cunit_assert_string(MZ_TRUE, "ABCDXYZ", buf);

    memset(buf, 0, sizeof(buf));
    strncat(buf, "ABCDEFGHIJK", 6);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEF", buf);
 
}

static void test_strncmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0, strncmp("ABCDEFG", "ABCD", 4));
    mz_cunit_assert_int(MZ_TRUE, 0, strncmp("ABCDEFG", "ABCD", 3));
    mz_cunit_assert_int(MZ_TRUE, 1, strncmp("ABCDEFG", "ABCD", 5));

    mz_cunit_assert_int(MZ_TRUE,  0, strncmp("ABCD", "ABCDEFG", 4));
    mz_cunit_assert_int(MZ_TRUE,  0, strncmp("ABCD", "ABCDEFG", 3));
    mz_cunit_assert_int(MZ_TRUE, -1, strncmp("ABCD", "ABCDEFG", 5));
}

static void test_strncpy(void)
{
    char buf[64];
    char *dest;

    dest = strncpy(buf, "ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    memset(buf, 0, sizeof(buf));
    strncpy(buf, "ABCDEFG", sizeof(buf));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strncpy(buf, "ABCDEFG", 8);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strncpy(buf, "ABCDEFG", 20);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", buf);

    memset(buf, 0, sizeof(buf));
    strncpy(buf, "ABCDEFG", 3);
    mz_cunit_assert_string(MZ_TRUE, "ABC", buf);

    memset(buf, 0, sizeof(buf));
    strncpy(buf, "ABCDEFG", 3);
    strncpy(buf + 3, "ABCDEFG", 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCABCD", buf);
}

static void test_strndup(void)
{
    char *src;
    char *dest;

    src = "ABCD";
    dest = strndup(src, 4);
    mz_cunit_assert_string(MZ_TRUE, dest, src);
    mz_cunit_assert_int(MZ_FALSE, (int)src, (int)dest);

    src = "ABCDEFG";
    dest = strndup(src, 4);
    mz_cunit_assert_string(MZ_TRUE, "ABCD", dest);

    src = "ABCDEFG";
    dest = strndup(src, 20);
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", dest);
}

static void test_strnlen(void)
{
    mz_cunit_assert_int(MZ_TRUE, 7, strnlen("ABCDEFG", 7));
    mz_cunit_assert_int(MZ_TRUE, 0, strnlen("\0", 0));

    mz_cunit_assert_int(MZ_TRUE, 3, strnlen("ABCDEFG", 3));
    mz_cunit_assert_int(MZ_TRUE, 7, strnlen("ABCDEFG", 30));
    mz_cunit_assert_int(MZ_TRUE, 0, strnlen("\0", 5));
}

static void test_strpbrk(void)
{
    mz_cunit_assert_string(MZ_TRUE, "DEFG",    strpbrk("ABCDEFG", "D"));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", strpbrk("ABCDEFG", "DA"));
    mz_cunit_assert_string(MZ_TRUE, "CDEFG",   strpbrk("ABCDEFG", "GCE"));
    mz_cunit_assert_string(MZ_TRUE, "EFG",     strpbrk("ABCDEFG", "XE"));
    mz_cunit_assert_string(MZ_TRUE, "EFG",     strpbrk("ABCDEFG", "EX"));

    mz_cunit_assert_string(MZ_TRUE, NULL,      strpbrk("ABCDEFG", "\0"));
    mz_cunit_assert_string(MZ_TRUE, NULL,      strpbrk("ABCDEFG", "X"));
}

static void test_strrchr(void)
{
    mz_cunit_assert_string(MZ_TRUE, "DEFG", strrchr("ABCDEFG", 'D'));
    mz_cunit_assert_string(MZ_TRUE, NULL, strrchr("ABCDEFG", 'd'));
    mz_cunit_assert_string(MZ_TRUE, NULL, strrchr("ABCDEFG", 'X'));
    mz_cunit_assert_string(MZ_TRUE, "\0", strrchr("ABCDEFG", '\0'));

    mz_cunit_assert_string(MZ_TRUE, "BC", strrchr("ABCABCABC", 'B'));
}

static void test_strspn(void)
{
    mz_cunit_assert_int(MZ_TRUE, 1,  strspn("ABCDEFGHIJK", "A"));
    mz_cunit_assert_int(MZ_TRUE, 0,  strspn("ABCDEFGHIJK", "H"));
    mz_cunit_assert_int(MZ_TRUE, 4,  strspn("ABCDEFGHIJK", "ABCD"));
    mz_cunit_assert_int(MZ_TRUE, 4,  strspn("ABCDEFGHIJK", "DCBA"));

    mz_cunit_assert_int(MZ_TRUE, 4,  strspn("ABCDEFGHIJK", "XABCD"));
    mz_cunit_assert_int(MZ_TRUE, 0,  strspn("ABCDEFGHIJK", "XY"));
    mz_cunit_assert_int(MZ_TRUE, 2,  strspn("ABCDEFGHIJK", "XABD"));
}

static void test_strstr(void)
{
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", strstr("ABCDEFG", "A"));
    mz_cunit_assert_string(MZ_TRUE, "DEFG",    strstr("ABCDEFG", "DE"));
    mz_cunit_assert_string(MZ_TRUE, "ABCDEFG", strstr("ABCDEFG", "\0"));

    mz_cunit_assert_string(MZ_TRUE, "ABCABCD", strstr("ABABCABCD", "ABC"));
}

static void test_strtok(void)
{
    char buf[64];

    strcpy(buf, "  Actor('path/file', 1, 5)");

    mz_cunit_assert_string(MZ_TRUE, "Actor", strtok(buf, " (,)"));
    mz_cunit_assert_string(MZ_TRUE, "'path/file'", strtok(NULL, " (,)"));
    mz_cunit_assert_string(MZ_TRUE, "1", strtok(NULL, " (,)"));
    mz_cunit_assert_string(MZ_TRUE, "5", strtok(NULL, " (,)"));
}

static void test_strtok_r(void)
{
    char buf[64];
    char *p;

    strcpy(buf, "  Actor('path/file', 1, 5)");

    mz_cunit_assert_string(MZ_TRUE, "Actor",        strtok_r(buf,  " (,)", &p));
    mz_cunit_assert_string(MZ_TRUE, "'path/file'",  strtok_r(NULL, " (,)", &p));
    mz_cunit_assert_string(MZ_TRUE, "1",            strtok_r(NULL, " (,)", &p));
    mz_cunit_assert_string(MZ_TRUE, "5",            strtok_r(NULL, " (,)", &p));
}

void unit_test_string()
{
    static item_unit_test_t tests[] = {
        macro_item_unit(test_memchr),
        macro_item_unit(test_memcmp),
        macro_item_unit(test_memcpy),
        macro_item_unit(test_memmove),
        macro_item_unit(test_memset),
        macro_item_unit(test_strcat),
        macro_item_unit(test_strchr),
        macro_item_unit(test_strcmp),
        macro_item_unit(test_strcpy),
        macro_item_unit(test_strcspn),
        macro_item_unit(test_strdup),
        macro_item_unit(test_strerror),
        macro_item_unit(test_strlcat),
        macro_item_unit(test_strlcpy),
        macro_item_unit(test_strlen),
        macro_item_unit(test_strncat),
        macro_item_unit(test_strncmp),
        macro_item_unit(test_strncpy),
        macro_item_unit(test_strndup),
        macro_item_unit(test_strnlen),
        macro_item_unit(test_strpbrk),
        macro_item_unit(test_strrchr),
        macro_item_unit(test_strspn),
        macro_item_unit(test_strstr),
        macro_item_unit(test_strtok),
        macro_item_unit(test_strtok_r),
    };

    run_test(tests, sizeof(tests) / sizeof(tests[0]));
}

#endif

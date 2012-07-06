#ifndef __TEST_WCHAR_H__
#define __TEST_WCHAR_H__

#include <mz/mz_cunit.h>
#include <mz/mz_libs.h>

#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "test.h"

#define arr_count(arr) (sizeof(arr) / sizeof(arr[0]))

static void test_wcscat(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    wmemset(buf, 0, arr_count(buf));
    dest = wcscat(buf, L"ABCD");
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);
    
    wmemset(buf, 0, arr_count(buf));
    wcscat(buf, L"ABCD");
    wcscat(buf, L"EFG");
    wcscat(buf, L"HIJK");
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    wmemset(buf, 0, arr_count(buf));
    wcscat(buf, L"ABCD");
    wcscat(buf + 2, L"EFG");
    wcscat(buf + 4, L"HIJK");
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    dest = L"XYZ";
    wmemset(buf, 0, arr_count(buf));
    wcscat(buf, L"ABCD");
    wcscat(buf, dest);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDXYZ", buf);
}

static void test_wcschr(void)
{
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", wcschr(L"ABCDEFG", 'D'));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wcschr(L"ABCDEFG", 'd'));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wcschr(L"ABCDEFG", 'X'));
    mz_cunit_assert_wstring(MZ_TRUE, L"\0", wcschr(L"ABCDEFG", '\0'));

    mz_cunit_assert_wstring(MZ_TRUE, L"CABCABC", wcschr(L"ABCABCABC", 'C'));
}

static void test_wcscmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 1,  wcscmp(L"ABCDEFG", L"ABCD"));
    mz_cunit_assert_int(MZ_TRUE, -1, wcscmp(L"ABCD",    L"ABCDEFG"));
    mz_cunit_assert_int(MZ_TRUE, 0,  wcscmp(L"ABCDEFG", L"ABCDEFG"));

    mz_cunit_assert_int(MZ_TRUE, 1,  wcscmp(L"ABCDEFG", L"\0"));
    mz_cunit_assert_int(MZ_TRUE, 1,  wcscmp(L"ABCDEFG", L"ABCDABC"));
    mz_cunit_assert_int(MZ_TRUE, -1, wcscmp(L"ABCDABC", L"ABCDEFG"));
}

static void test_wcscpy(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    wmemset(buf, 0, arr_count(buf));
    dest = wcscpy(buf, L"ABCDEFG");
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    wmemset(buf, 0, arr_count(buf));
    wcscpy(buf, L"ABCDEFG");
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcscpy(buf, L"ABCDEFG");
    wcscpy(buf + 3, L"ABCDEFG");
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcscpy(buf, L"ABCDEFG");
    wcscpy(buf + 10, L"ABCDEFG");
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    dest = L"ABCDEFG";
    wcscpy(buf, dest);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    dest = L"ABCDEFG";
    wcscpy(buf, dest + 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", buf);
}

static void test_wcscspn(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0,  wcscspn(L"ABCDEFGHIJK", L"A"));
    mz_cunit_assert_int(MZ_TRUE, 7,  wcscspn(L"ABCDEFGHIJK", L"H"));
    mz_cunit_assert_int(MZ_TRUE, 10, wcscspn(L"ABCDEFGHIJK", L"K"));

    mz_cunit_assert_int(MZ_TRUE, 3,  wcscspn(L"ABCDEFGHIJK", L"DHK"));
    mz_cunit_assert_int(MZ_TRUE, 0,  wcscspn(L"ABCDEFGHIJK", L"AK"));
    mz_cunit_assert_int(MZ_TRUE, 3,  wcscspn(L"ABCDEFGHIJK", L"KD"));

    mz_cunit_assert_int(MZ_TRUE, 11, wcscspn(L"ABCDEFGHIJK", L"X"));
    mz_cunit_assert_int(MZ_TRUE, 11, wcscspn(L"ABCDEFGHIJK", L"XY"));
    mz_cunit_assert_int(MZ_TRUE, 3,  wcscspn(L"ABCDEFGHIJK", L"XD"));
}

static void test_wcsdup(void)
{
    wchar_t *src = L"ABCD";
    wchar_t *dest = wcsdup(src);

    mz_cunit_assert_wstring(MZ_TRUE, dest, src);
    mz_cunit_assert_int(MZ_FALSE, (int)dest, (int)src);
}

size_t wcslcat(wchar_t *dst, const wchar_t *src, size_t siz)
{
    wchar_t *d = dst;
    const wchar_t *s = src;
    size_t n = siz;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end */
    while (*d != '\0' && n-- != 0)
        d++;
    dlen = d - dst;
    n = siz - dlen;

    if (n == 0)
        return(dlen + wcslen(s));
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

static void test_wcslcat(void)
{
    wchar_t buf[64];
    wchar_t small_buf[4];
    wchar_t *dest;
    int count;

    wmemset(buf, 0, arr_count(buf));
    count = wcslcat(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    wmemset(small_buf, 0, arr_count(small_buf));
    count = wcslcat(small_buf, L"ABCDEFG", arr_count(small_buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABC", small_buf);

    wmemset(buf, 0, arr_count(buf));
    wcslcat(buf, L"ABCD", arr_count(buf));
    wcslcat(buf, L"EFG",  arr_count(buf));
    wcslcat(buf, L"HIJK", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    wmemset(buf, 0, arr_count(buf));
    wcslcat(buf, L"ABCD", arr_count(buf));
    wcslcat(buf + 2, L"EFG", arr_count(buf));
    wcslcat(buf + 4, L"HIJK", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    dest = L"XYZ";
    wmemset(buf, 0, arr_count(buf));
    wcslcat(buf, L"ABCD", arr_count(buf));
    wcslcat(buf, dest, arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDXYZ", buf);
}

size_t wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz)
{
    wchar_t *d = dst;
    const wchar_t *s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0 && --n != 0) {
        do {
            if ((*d++ = *s++) == 0)
                break;
        } while (--n != 0);
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

static void test_wcslcpy(void)
{
    wchar_t buf[64];
    wchar_t small_buf[4];
    wchar_t *dest;
    int count;

    wmemset(buf, 0, arr_count(buf));
    count = wcslcpy(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    wmemset(small_buf, 0, arr_count(small_buf));
    count = wcslcpy(small_buf, L"ABCDEFG", arr_count(small_buf));
    mz_cunit_assert_int(MZ_TRUE, 7, count);

    wmemset(buf, 0, arr_count(buf));
    wcslcpy(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcslcpy(buf, L"ABCDEFG", arr_count(buf));
    wcslcpy(buf + 3, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcslcpy(buf, L"ABCDEFG", arr_count(buf));
    wcslcpy(buf + 10, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    dest = L"ABCDEFG";
    wcslcpy(buf, dest, arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    dest = L"ABCDEFG";
    wcslcpy(buf, dest + 3, arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", buf);

    wmemset(small_buf, 0, arr_count(small_buf));
    wcslcpy(small_buf, L"ABCDEFG", arr_count(small_buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABC", small_buf);
}

static void test_wcslen(void)
{
    mz_cunit_assert_int(MZ_TRUE, 7, wcslen(L"ABCDEFG"));
    mz_cunit_assert_int(MZ_TRUE, 0, wcslen(L"\0"));
}

static void test_wcsncat(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    wmemset(buf, 0, arr_count(buf));
    dest = wcsncat(buf, L"ABCD", 4);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);
    
    wmemset(buf, 0, arr_count(buf));
    wcsncat(buf, L"ABCD", 4);
    wcsncat(buf, L"EFG", 3);
    wcsncat(buf, L"HIJK", 4);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncat(buf, L"ABCD", 4);
    wcsncat(buf + 2, L"EFG", 3);
    wcsncat(buf + 4, L"HIJK", 4);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGHIJK", buf);

    dest = L"XYZ";
    wmemset(buf, 0, arr_count(buf));
    wcsncat(buf, L"ABCD", 4);
    wcsncat(buf, dest, 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDXYZ", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncat(buf, L"ABCDEFGHIJK", 6);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEF", buf);
}

static void test_wcsncmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0,  wcsncmp(L"ABCDEFG", L"ABCD", 4));
    mz_cunit_assert_int(MZ_TRUE, 0,  wcsncmp(L"ABCDEFG", L"ABCD", 3));
    mz_cunit_assert_int(MZ_TRUE, 69, wcsncmp(L"ABCDEFG", L"ABCD", 5));

    mz_cunit_assert_int(MZ_TRUE,  0,  wcsncmp(L"ABCD", L"ABCDEFG", 4));
    mz_cunit_assert_int(MZ_TRUE,  0,  wcsncmp(L"ABCD", L"ABCDEFG", 3));
    mz_cunit_assert_int(MZ_TRUE, -69, wcsncmp(L"ABCD", L"ABCDEFG", 5));

}

static void test_wcsncpy(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    dest = wcsncpy(buf, L"ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    wmemset(buf, 0, arr_count(buf));
    wcsncpy(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncpy(buf, L"ABCDEFG", 8);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncpy(buf, L"ABCDEFG", 20);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncpy(buf, L"ABCDEFG", 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABC", buf);

    wmemset(buf, 0, arr_count(buf));
    wcsncpy(buf, L"ABCDEFG", 3);
    wcsncpy(buf + 3, L"ABCDEFG", 4);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCD", buf);

}

static void test_wcspbrk(void)
{
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG",    wcspbrk(L"ABCDEFG", L"D"));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", wcspbrk(L"ABCDEFG", L"DA"));
    mz_cunit_assert_wstring(MZ_TRUE, L"CDEFG",   wcspbrk(L"ABCDEFG", L"GCE"));
    mz_cunit_assert_wstring(MZ_TRUE, L"EFG",     wcspbrk(L"ABCDEFG", L"XE"));
    mz_cunit_assert_wstring(MZ_TRUE, L"EFG",     wcspbrk(L"ABCDEFG", L"EX"));

    mz_cunit_assert_wstring(MZ_TRUE, NULL,      wcspbrk(L"ABCDEFG", L"\0"));
    mz_cunit_assert_wstring(MZ_TRUE, NULL,      wcspbrk(L"ABCDEFG", L"X"));
}

static void test_wcsrchr(void)
{
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", wcsrchr(L"ABCDEFG", 'D'));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wcsrchr(L"ABCDEFG", 'd'));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wcsrchr(L"ABCDEFG", 'X'));
    mz_cunit_assert_wstring(MZ_TRUE, L"\0", wcsrchr(L"ABCDEFG", '\0'));

    mz_cunit_assert_wstring(MZ_TRUE, L"BC", wcsrchr(L"ABCABCABC", 'B'));
}

static void test_wcsspn(void)
{
    mz_cunit_assert_int(MZ_TRUE, 1,  wcsspn(L"ABCDEFGHIJK", L"A"));
    mz_cunit_assert_int(MZ_TRUE, 0,  wcsspn(L"ABCDEFGHIJK", L"H"));
    mz_cunit_assert_int(MZ_TRUE, 4,  wcsspn(L"ABCDEFGHIJK", L"ABCD"));
    mz_cunit_assert_int(MZ_TRUE, 4,  wcsspn(L"ABCDEFGHIJK", L"DCBA"));

    mz_cunit_assert_int(MZ_TRUE, 4,  wcsspn(L"ABCDEFGHIJK", L"XABCD"));
    mz_cunit_assert_int(MZ_TRUE, 0,  wcsspn(L"ABCDEFGHIJK", L"XY"));
    mz_cunit_assert_int(MZ_TRUE, 2,  wcsspn(L"ABCDEFGHIJK", L"XABD"));
}

static void test_wcsstr(void)
{
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", wcsstr(L"ABCDEFG", L"A"));
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG",    wcsstr(L"ABCDEFG", L"DE"));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", wcsstr(L"ABCDEFG", L"\0"));

    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCD", wcsstr(L"ABABCABCD", L"ABC"));
}

static void test_wcstok(void)
{
    wchar_t buf[64];
    wchar_t *p;

    wcscpy(buf, L"  Actor('path/file', 1, 5)");

    mz_cunit_assert_wstring(MZ_TRUE, L"Actor", wcstok(buf, L" (,)", &p));
    mz_cunit_assert_wstring(MZ_TRUE, L"'path/file'", wcstok(NULL, L" (,)", &p));
    mz_cunit_assert_wstring(MZ_TRUE, L"1", wcstok(NULL, L" (,)", &p));
    mz_cunit_assert_wstring(MZ_TRUE, L"5", wcstok(NULL, L" (,)", &p));
}

static void test_wmemchr(void)
{
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", wmemchr(L"ABCDEFG", 'D', 70));
    mz_cunit_assert_wstring(MZ_TRUE, L"DEFG", wmemchr(L"ABCDEFG", 'D', 7));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wmemchr(L"ABCDEFG", 'D', 3));

    mz_cunit_assert_wstring(MZ_TRUE, NULL, wmemchr(L"ABCDEFG", 'X', 70));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wmemchr(L"ABCDEFG", 'X', 7));
    mz_cunit_assert_wstring(MZ_TRUE, NULL, wmemchr(L"ABCDEFG", 'X', 3));

    mz_cunit_assert_wstring(MZ_TRUE, L"\0", wmemchr(L"ABCDEFG", '\0', 70));
}

static void test_wmemcmp(void)
{
    mz_cunit_assert_int(MZ_TRUE, 0, wmemcmp(L"ABCDEFG", L"ABCD", 4));
    mz_cunit_assert_int(MZ_TRUE, 0, wmemcmp(L"ABCDEFG", L"ABCD", 3));
    mz_cunit_assert_int(MZ_TRUE, 1, wmemcmp(L"ABCDEFG", L"ABCD", 5));

    mz_cunit_assert_int(MZ_TRUE,  0, wmemcmp(L"ABCD", L"ABCDEFG", 4));
    mz_cunit_assert_int(MZ_TRUE,  0, wmemcmp(L"ABCD", L"ABCDEFG", 3));
    mz_cunit_assert_int(MZ_TRUE, -1, wmemcmp(L"ABCD", L"ABCDEFG", 5));

}

static void test_wmemcpy(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    dest = wmemcpy(buf, L"ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    wmemset(buf, 0, arr_count(buf));
    wmemcpy(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemcpy(buf, L"ABCDEFG", 8);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemcpy(buf, L"ABCDEFG", 20);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemcpy(buf, L"ABCDEFG", 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABC", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemcpy(buf, L"ABCDEFG", 3);
    wmemcpy(buf + 3, L"ABCDEFG", 4);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCD", buf);

}

static void test_wmemmove(void)
{
    wchar_t buf[64];
    wchar_t *dest;

    dest = wmemmove(buf, L"ABCDEFG", 8);
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", arr_count(buf));
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 8);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABC", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 3);
    wmemmove(buf + 3, L"ABCDEFG", 4);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCD", buf);
 
    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 8);
    wmemmove(buf + 3, buf, 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCABCG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 8);
    wmemmove(buf + 7, buf, 3);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGABC", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 8);
    wmemmove(buf + 7, buf, 20);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFGABCDEFG", buf);

    wmemset(buf, 0, arr_count(buf));
    wmemmove(buf, L"ABCDEFG", 8);
    wmemmove(buf + 8, buf, 20);
    mz_cunit_assert_wstring(MZ_TRUE, L"ABCDEFG", buf);

}

static void test_wmemset(void)
{
    wchar_t buf[64];
    wchar_t *dest;
    int i;
    
    dest = wmemset(buf, 10, arr_count(buf));
    mz_cunit_assert_int(MZ_TRUE, (int)buf, (int)dest);

    wmemset(buf, 5, arr_count(buf));
    for (i = 0; i < arr_count(buf); i++)
        mz_cunit_assert_int(MZ_TRUE, 5, buf[i]);

    wmemset(buf, 0x12345678, arr_count(buf));
    for (i = 0; i < arr_count(buf); i++)
        mz_cunit_assert_int(MZ_TRUE, 0x12345678, buf[i]);

}

void unit_test_wchar()
{
    static item_unit_test_t tests[] = {
        macro_item_unit(test_wcscat),
        macro_item_unit(test_wcschr),
        macro_item_unit(test_wcscmp),
        macro_item_unit(test_wcscpy),
        macro_item_unit(test_wcscspn),
        macro_item_unit(test_wcsdup),
        macro_item_unit(test_wcslcat),
        macro_item_unit(test_wcslcpy),
        macro_item_unit(test_wcslen),
        macro_item_unit(test_wcsncat),
        macro_item_unit(test_wcsncmp),
        macro_item_unit(test_wcsncpy),
        macro_item_unit(test_wcspbrk),
        macro_item_unit(test_wcsrchr),
        macro_item_unit(test_wcsspn),
        macro_item_unit(test_wcsstr),
        macro_item_unit(test_wcstok),
        macro_item_unit(test_wmemchr),
        macro_item_unit(test_wmemcmp),
        macro_item_unit(test_wmemcpy),
        macro_item_unit(test_wmemmove),
        macro_item_unit(test_wmemset),
    };

    run_test(tests, sizeof(tests) / sizeof(tests[0]));
}

#endif

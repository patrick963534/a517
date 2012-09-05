/**
version=2.4.2
wordcount=51214
idxfilesize=899574
bookname=stardict1.3英汉辞典
author=马苏安
email=msa@wri.com.cn
description=胡正将其转换到stardict2。
date=2003.05.13
sametypesequence=tm
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define min(a, b)   ((a) < (b)) ? (a) : (b)

const char* data_path = "E:/data/other/stardict-stardict1.3-2.4.2/stardict-stardict1.3-2.4.2/";
const char* idx_file = "stardict1.3.idx";
const char* dict_file = "stardict1.3.dict";
const char* ifo_file = "stardict1.3.ifo";
const char* log_file = "result.log";

typedef struct ifo_s
{
    char   *version;
    char   *same_type_sequence;
    int     idx_file_sz;
    int     word_count;
} ifo_s;

typedef struct word_s
{
    char*   name;
    char*   phonetic;    
    char*   meaning;   
} word_s;

typedef struct idx_entry_s
{
    char*   word;
    int     offset;
    int     sz;
} idx_entry_s;

typedef struct dict_s
{
    ifo_s         ifo;

    idx_entry_s  *entrys;
    int           nentry;

    word_s       *words;
    int           nword;
} dict_s;

static dict_s dict;

static void parse_ifo_file()
{
    FILE *fp;
    char buf[1024];
    
    strcpy(buf, data_path);
    strcat(buf, ifo_file);

    if (NULL == (fp = fopen(buf, "r")))
        return;
    
    while (!feof(fp))
    {
        char* line = fgets(buf, sizeof(buf), fp);
        if (!line)
            break;

        if (strstr(line, "version") != 0)
            dict.ifo.version = strdup(&line[strchr(line, '=') - line + 1]);
        else if (strstr(line, "sametypesequence") != 0)
            dict.ifo.same_type_sequence = strdup(&line[strchr(line, '=') - line + 1]);
        else if (strstr(line, "idxfilesize") != 0)
            dict.ifo.idx_file_sz = atoi(&line[strchr(line, '=') - line + 1]);
        else if (strstr(line, "wordcount") != 0)
            dict.ifo.word_count = atoi(&line[strchr(line, '=') - line + 1]);
    }

    fclose(fp);
}

static int to_int(unsigned char* buf)
{
    int v = buf[3];

    v += buf[2] * 256;
    v += buf[1] * 256 * 256;
    v += buf[0] * 256 * 256 * 256;

    return v;
}

static void parse_idx()
{
    FILE *fp;
    char *buf;
    char  path[256];
    int   i;

    strcpy(path, data_path);
    strcat(path, idx_file);

    if (NULL == (fp = fopen(path, "r")))
        return;

    buf = malloc(dict.ifo.idx_file_sz);
    fread(buf, 1, dict.ifo.idx_file_sz, fp);
    fclose(fp);

    dict.nentry = dict.ifo.word_count;
    dict.entrys = (idx_entry_s*)calloc(dict.nentry, sizeof(dict.entrys[0]));
    i = 0;

    while (i < dict.nentry)
    {
        dict.entrys[i].word = strdup(buf);
        buf += strlen(dict.entrys[i].word) + 1;

        dict.entrys[i].offset = to_int((unsigned char*)buf);
        buf += 4;

        dict.entrys[i].sz = to_int((unsigned char*)buf);
        buf += 4;

        i++;
    }
}

static void parse_dict()
{
    FILE *fp;
    FILE *log;
    char  path[256];
    int   i;

    strcpy(path, data_path);
    strcat(path, dict_file);

    if (NULL == (fp = fopen(path, "r")))
        return;

    log = fopen(log_file, "w");

    dict.words = (word_s*)calloc(dict.nentry, sizeof(dict.words[0]));

    for (i = 0; i < dict.nentry; i++)
    {
        char* buf;
        int len;
        int left = dict.entrys[i].sz;

        buf = calloc(1, dict.entrys[i].sz);

        fseek(fp, dict.entrys[i].offset, SEEK_SET);
        fread(buf, 1, dict.entrys[i].sz, fp);

        len = min((size_t)left, strlen(buf));
        dict.words[i].phonetic = calloc(1, len + 1);
        if (len != 0)
            memcpy(dict.words[i].phonetic, buf, len);
        buf += len + 1;
        left -= len + 1;

        len = min((size_t)left, strlen(buf));
        dict.words[i].meaning = calloc(1, len + 1);
        if (len != 0)
            memcpy(dict.words[i].meaning, buf, len);
        buf += len + 1;

        fprintf(log, "%40s %-20s  %s\n", dict.entrys[i].word, dict.words[i].phonetic, dict.words[i].meaning);
    }

    fclose(log);
    fclose(fp);
}

int main()
{
    parse_ifo_file();
    parse_idx();
    parse_dict();

    return 0;
}

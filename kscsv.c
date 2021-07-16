/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    kscsv.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include <string.h>
// #include <dirent.h>

#include "kscsv.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

const char KSCSV_TAG_STRING[KSCSV_IDX_TOTAL][MAX_TAG_STRING_LENGTH] =
{
    "sn", "ts", "dt",
    "gx", "gy", "gz", "grx", "gry", "grz", "gbx", "gby", "gbz",
    "ax", "ay", "az", "arx", "ary", "arz", "abx", "aby", "abz",
    "mx", "my", "mz", "mrx", "mry", "mrz", "mbx", "mby", "mbz",
    "p", "t",
    "agx", "agy", "agz", "alx", "aly", "alz",
    "qx", "qy", "qz", "qw",
    "qgx", "qgy", "qgz", "qgw",
    "qmx", "qmy", "qmz", "qmw",
    "unknown"
};

/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

/**
 *  @brief  kscsv_get_tag_index
 */
int kscsv_get_tag_index(char *tag)
{
    for (int i = 0; i < KSCSV_IDX_TOTAL; i++)
    {
        if (strcmp(KSCSV_TAG_STRING[i], tag) == 0)
        {
            return i;
        }
    }
    return KSCSV_IDX_UNKNOWN;
}

/**
 *  @brief  kscsv_get_line_count
 */
int kscsv_get_line_count(FILE *file)
{
    char line[MAX_FILE_LINE_STRING_LENGTH] = {0};
    int lens = 0;
    rewind(file);
    while (!feof(file))
    {
        fscanf(file, "%s\n", line);
        // memset(line, 0, MAX_FILE_LINE_STRING_LENGTH);
        // fgets(line, sizeof(line), file);
        if (strlen(line) < 2)
        {
            break;
        }
        lens++;
#if 0
        printf("[%d] %s\n", lens, line);
#endif
    }
    rewind(file);
    return lens;
}

/**
 *  @brief  kscsv_get_tag
 */
int kscsv_get_tag(FILE *file, int **tags)
{
    // get first line
    char line[MAX_FILE_LINE_STRING_LENGTH] = {0};
    rewind(file);
    fscanf(file, "%s\n", line);
    // fgets(line, sizeof(line), file);
    // line[strlen(line)-1] = '\0';

    // get number of tags
    int tagcnt = -1;
    char *pline = line;
    while (*pline != 0)
    {
        if (*pline == ',')
        {
            tagcnt++;
        }
        pline++;
    }
    tagcnt = (tagcnt < 0) ? 0 : tagcnt + 2;

    // update tag index
    if (*tags == NULL)
    {
        *tags = (int *)calloc(tagcnt, sizeof(int));
    }
    char *tag = (char *)strtok(line, ",");
    int *ptags = *tags;
    while (tag != NULL) 
    {
        // TODO:
        // if index == unknow then ...
        // KSCSV_IDX_TOTAL +1, +2 ...
        *(ptags++) = kscsv_get_tag_index(tag);
        tag = (char *)strtok(NULL, ",");
    }

    return tagcnt;
}

/**
 *  @brief  kscsv_open
 */
int kscsv_open(kscsv_t *csv, char *filename)
{
    if (csv->path == NULL)
    {
        csv->path = (char *)calloc(MAX_PATH_STRING_LENGTH, sizeof(char));
    }
    if (csv->filename == NULL)
    {
        csv->filename = (char *)calloc(MAX_FILENAME_STRING_LENGTH, sizeof(char));
        strcpy(csv->filename, filename);
    }

    csv->fp = fopen(filename, "rb");
    if (csv->fp == NULL)
    {
        return KS_ERROR;
    }
    csv->lens = kscsv_get_line_count(csv->fp) - 1;
    csv->tagcnt = kscsv_get_tag(csv->fp, &csv->tags);

    return KS_OK;
}

/**
 *  @brief  kscsv_close
 */
int kscsv_close(kscsv_t *csv)
{
    fclose(csv->fp);
    free(csv->path);
    free(csv->filename);
    free(csv->tags);
    csv->path = NULL;
    csv->filename = NULL;
    csv->tags = NULL;
    kscsv_release(csv);
}

int kscsv_malloc(kscsv_t *csv, int size)
{
    // memory allocation
    csv->raw.size = size;
    for (int i = 0; i < csv->tagcnt; i++)
    {
        int idx = csv->tags[i];
        if (idx < KSCSV_IDX_UNKNOWN)
        {
            csv->mem[idx] = (unsigned int)calloc(size, sizeof(double));
        }
    }
    // TODO:
    // if have unknow tag ...
}

int kscsv_read_data(kscsv_t *csv, int index)
{
    if (index >= csv->raw.size)
    {
        return -1;
    }
    // read data
    for (int i = 0; i < csv->tagcnt-1; i++)
    {
        // TODO:
        // if have unknow tag ...
        fscanf(csv->fp, "%lf,", &((double*)csv->mem[csv->tags[i]])[index]);
        // switch (csv->tags[i])
        // {
        //     case KSCSV_TAG_INTEGER_CASE:
        //     {
        //         printf("%.0f,", *(double*)csv->mem[csv->tags[i]]);
        //         break;
        //     }
        //     default:
        //     {
        //         printf("%lf,", *(double*)csv->mem[csv->tags[i]]);
        //         break;
        //     }
        // }
    }
    fscanf(csv->fp, "%lf\n", &((double*)csv->mem[csv->tags[csv->tagcnt-1]])[index]);
    return 1;
}

/**
 *  @brief  kscsv_read
 */
int kscsv_read(kscsv_t *csv, int lens)
{
    kscsv_malloc(csv, csv->lens);

    if (feof(csv->fp))
    {
        return -1;
    }

    // read csv
    int idx = 0;
    if (lens < 0)
    {
        while (!feof(csv->fp))
        {
            kscsv_read_data(csv, idx++);
        }
    }
    else
    {
        while (!feof(csv->fp))
        {
            kscsv_read_data(csv, idx++);
            if (idx < lens)
            {
                break;
            }
        }
    }

    return idx;

    // // read csv
    // int idx = 0;
    // while (!feof(csv->fp))
    // {
    //     // read data
    //     for (int i = 0; i < csv->tagcnt-1; i++)
    //     {
    //         fscanf(csv->fp, "%lf,", &((double*)csv->mem[csv->tags[i]])[idx]);
    //         // switch (csv->tags[i])
    //         // {
    //         //     case KSCSV_TAG_INTEGER_CASE:
    //         //     {
    //         //         printf("%.0f,", *(double*)csv->mem[csv->tags[i]]);
    //         //         break;
    //         //     }
    //         //     default:
    //         //     {
    //         //         printf("%lf,", *(double*)csv->mem[csv->tags[i]]);
    //         //         break;
    //         //     }
    //         // }
    //     }
    //     fscanf(csv->fp, "%lf\n", &((double*)csv->mem[csv->tags[csv->tagcnt-1]])[idx]);
    //     // fscanf(csv->fp, "%lf\n", csv->mem[csv->tags[csv->tagcnt-1]]);
    //     // printf("%lf\n", *(double*)csv->mem[csv->tags[csv->tagcnt-1]]);
    //     // printf("%.0lf, index = %d ... %.0lf\n", ((double*)csv->mem[csv->tags[0]])[idx], csv->tags[0], csv->raw.sn[idx]);
    //     idx++;
    // }
    // return 0;
}

/**
 *  @brief  kscsv_release
 */
void kscsv_release(kscsv_t *csv)
{
    for (int i = 0; i < csv->tagcnt; i++)
    {
        free((double *)csv->mem[i]);
        csv->mem[i] = 0;
    }
}

// void kscsv_getitem()
// {
    // printf("strtoul(line, NULL, 0) = %d\n", tt);
    // printf("strtof(line, NULL) = %f\n\n", ff);

//     printf("\n-----\n");
//     char *token = (char *)strtok(line, ",");
//     while (token != NULL) 
//     {
//         printf("[%02d] %s\n", kscsv_get_item_index(token), token);
//         token = (char *)strtok(NULL, ",");
//     }
//     printf("\n-----\n");

    // DIR *d;
    // struct dirent *dir;
    // d = opendir(".");
    // if (d) {
    //     while ((dir = readdir(d)) != NULL) {
    //         printf("%s\n", dir->d_name);
    //     }
    //     closedir(d);
    // }

// }



// typedef enum
// {
//     KFILE_TEXT = 0,
//     KFILE_CSV  = 1,
//     KFILE_JSON = 2,
//     KFILE_MAX_EXTENSION_NUM

// } kfile_extension_t;

// const char KFILE_EXTENSION_STRING[KFILE_MAX_EXTENSION_NUM][MAX_TYPE_STRING_LENGTH] = 
// {
//     "text", "csv", "json"
// };

// typedef struct
// {
//     FILE *file;

//     char name[MAX_FILENAME_STRING_LENS];
//     char path[MAX_PATH_STRING_LENS];
//     kfile_type_t type;
//     char *text;

// } kfile_t;

/*************************************** END OF FILE ****************************************/

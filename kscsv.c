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

const char KSCSV_TAG_STRING[KSCSV_IDX_END][8] =
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
    for (int i = 0; i < KSCSV_IDX_END; i++)
    {
        if (strcmp(KSCSV_TAG_STRING[i], tag) == 0)
        {
            return i;
        }
    }
    return KSCSV_IDX_UNKNOWN;
}

/**
 *  @brief  kscsv_get_tag_count
 */
int kscsv_get_tag_count(char *line)
{
    int tag = -1;
    while (*line != 0)
    {
        if (*line == ',')
        {
            tag++;
        }
        line++;
    }
    return (tag < 0) ? -1 : tag + 2;
}

/**
 *  @brief  kscsv_get_tag_index_array
 */
int kscsv_get_tag_index_array(char *line, int *idxarray)
{
    char *tag = (char *)strtok(line, ",");
    int idx = 0;
    while (tag != NULL) 
    {
        idxarray[idx++] = kscsv_get_tag_index(tag);
        tag = (char *)strtok(NULL, ",");
    }
    return idx;
}

/**
 *  @brief  kscsv_check_tag_index_array
 */
int kscsv_check_tag_index_array(int *idxarray, int lens)
{
    int unknown = 0;
    for (int i = 0; i < lens; i++)
    {
        if (idxarray[i] == KSCSV_IDX_UNKNOWN)
        {
            unknown++;
        }
    }
    return (lens != unknown) ? 1 : 0;
}

/**
 *  @brief  kscsv_get_line_count
 */
int kscsv_get_line_count(FILE *file)
{
    char line[8192] = {0};
    int lens = 0;

    if (file == NULL)
    {
        return -1;
    }
    rewind(file);
    while (!feof(file))
    {
        fscanf(file, "%s\n", line);
        lens++;
#if 0
        printf("[%d] %s\n", lens, line);
#endif
    }
    return lens;
}

/**
 *  @brief  kscsv_get_line_string
 */
int kscsv_get_line_string(FILE *file, char *linebuf, int line)
{
    int lens = 0;

    if (file == NULL)
    {
        return -1;
    }
    rewind(file);
    while (!feof(file))
    {
        fscanf(file, "%s\n", linebuf);
        if (++lens == line)
        {
            return lens;
        }
    }
    return lens;
}

/**
 *  @brief  kscsv_open
 */
int kscsv_open(kscsv_t *csv, char *filename)
{
    FILE *fp;

    if (csv->path == NULL)
    {
        csv->path = (char*)malloc(sizeof(char)*MAX_PATH_STRING_LENGTH);
    }
    if (csv->filename == NULL)
    {
        csv->filename = (char*)malloc(sizeof(char)*MAX_FILENAME_STRING_LENGTH);
        strcpy(csv->filename, filename);
    }

    fp = fopen(filename, "rb");
    csv->lens = kscsv_get_line_count(fp);
    if (csv->lens < 0)
    {
        return -1;
    }

    if (csv->line == NULL)
    {
        csv->line = (char*)malloc(sizeof(char)*MAX_FILE_LINE_STRING_LENGTH);
    }
    kscsv_get_line_string(fp, csv->line, 1);    // get first line
    fclose(fp);

    csv->tagcnt = kscsv_get_tag_count(csv->line);
    if (csv->tagidx == NULL)
    {
        csv->tagidx = (int*)malloc(sizeof(int)*csv->tagcnt);
    }
    kscsv_get_tag_index_array(csv->line, csv->tagidx);
    if (kscsv_check_tag_index_array(csv->tagidx, csv->tagcnt) != 0)
    {
        csv->lens--;
    }
    return 1;
}

/**
 *  @brief  kscsv_close
 */
int kscsv_close(kscsv_t *csv)
{
    free(csv->line);
    csv->line = NULL;
}

/**
 *  @brief  kscsv_release
 */
void kscsv_release(kscsv_t *csv)
{
    free(csv->path);
    free(csv->filename);
    free(csv->tagidx);
    csv->path = NULL;
    csv->filename = NULL;
    csv->tagidx = NULL;
    kscsv_release_raw(&csv->raw);
}

/**
 *  @brief  kscsv_release_raw
 */
void kscsv_release_raw(raw_t *raw)
{

}

/**
 *  @brief  kscsv_read
 */
void kscsv_read(kscsv_t *csv)
{
    FILE *fp = fopen(csv->filename, "rb");

    fclose(fp);
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

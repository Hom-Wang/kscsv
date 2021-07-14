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
#include "kscsv.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

const char KSCSV_ITEM_STRING[KSCSV_END][8] = {
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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>

/**
 *  @brief  kscsv_get_item_index
 */
int kscsv_get_item_index(char *item)
{
    for (int i = 0; i < KSCSV_END; i++)
    {
        if (strcmp(KSCSV_ITEM_STRING[i], item) == 0)
        {
            return i;
        }
    }
    return KSCSV_UNKNOWN;
}

/**
 *  @brief  kscsv_get_item_count
 */
int kscsv_get_item_count(char *line)
{
    int item = -1;
    while (*line != 0)
    {
        printf("%c", *line);
        if (*line == ',')
        {
            item++;
        }
        line++;
    }
    return (item < 0) ? -1 : item + 2;
}

/**
 *  @brief  kscsv_get_item_index_array
 */
int kscsv_get_item_index_array(char *line, int *idxarray)
{
    char *item = (char *)strtok(line, ",");
    int count = 0;
    while (item != NULL) 
    {
        idxarray[count++] = kscsv_get_item_index(item);
        item = (char *)strtok(NULL, ",");
    }
    return count;
}

/**
 *  @brief  kscsv_check_index_array
 */
int kscsv_check_index_array(int *idxarray, int lens)
{
    int unknown = 0;
    for (int i = 0; i < lens; i++)
    {
        if (idxarray[i] == KSCSV_UNKNOWN)
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
#if 0
        printf("[%d] %s\n", lens, line);
#endif
    }
    return lens;
}

/**
 *  @brief  kscsv_open
 */
int kscsv_open(kscsv_t *csv, char *filename)
{
    FILE *fp = fopen(filename, "rb");
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
    csv->itemcnt = kscsv_get_item_index_array(csv->line, csv->itemidx);
    if (kscsv_check_index_array(csv->itemidx, csv->itemcnt) != 0)
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
}

/**
 *  @brief  kscsv_release
 */
int kscsv_release(kscsv_t *csv)
{
    free(csv->raw);
}

/**
 *  @brief  kscsv_read
 */
void kscsv_read(kscsv_t *csv)
{

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

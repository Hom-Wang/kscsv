/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    kscsv.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __KSCSV_H
#define __KSCSV_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "kStatus.h"

/* Define ----------------------------------------------------------------------------------*/

#define MAX_FILENAME_STRING_LENGTH      256
#define MAX_PATH_STRING_LENGTH          256
#define MAX_FILE_LINE_STRING_LENGTH     8192
#define MAX_TAG_STRING_LENGTH           8

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/

typedef enum
{
    KSCSV_IDX_SN    = 0,    // serial number
    KSCSV_IDX_TS    = 1,    // timestamp
    KSCSV_IDX_DT    = 2,    // delta time
    KSCSV_IDX_GX    = 3,    // gyr calibrated data x
    KSCSV_IDX_GY    = 4,    // gyr calibrated data y
    KSCSV_IDX_GZ    = 5,    // gyr calibrated data z
    KSCSV_IDX_GRX   = 6,    // gyr raw data x
    KSCSV_IDX_GRY   = 7,    // gyr raw data y
    KSCSV_IDX_GRZ   = 8,    // gyr raw data z
    KSCSV_IDX_GBX   = 9,    // gyr bias x
    KSCSV_IDX_GBY   = 10,   // gyr bias y
    KSCSV_IDX_GBZ   = 11,   // gyr bias z
    KSCSV_IDX_AX    = 12,   // acc calibrated data x
    KSCSV_IDX_AY    = 13,   // acc calibrated data y
    KSCSV_IDX_AZ    = 14,   // acc calibrated data z
    KSCSV_IDX_ARX   = 15,   // acc raw data x
    KSCSV_IDX_ARY   = 16,   // acc raw data y
    KSCSV_IDX_ARZ   = 17,   // acc raw data z
    KSCSV_IDX_ABX   = 18,   // acc bias x
    KSCSV_IDX_ABY   = 19,   // acc bias y
    KSCSV_IDX_ABZ   = 20,   // acc bias z
    KSCSV_IDX_MX    = 21,   // mag calibrated data x
    KSCSV_IDX_MY    = 22,   // mag calibrated data y
    KSCSV_IDX_MZ    = 23,   // mag calibrated data z
    KSCSV_IDX_MRX   = 24,   // mag raw data x
    KSCSV_IDX_MRY   = 25,   // mag raw data y
    KSCSV_IDX_MRZ   = 26,   // mag raw data z
    KSCSV_IDX_MBX   = 27,   // mag bias x
    KSCSV_IDX_MBY   = 28,   // mag bias y
    KSCSV_IDX_MBZ   = 29,   // mag bias z
    KSCSV_IDX_P     = 30,   // pressure
    KSCSV_IDX_T     = 31,   // temperature
    KSCSV_IDX_AGX   = 32,   // gravity x
    KSCSV_IDX_AGY   = 33,   // gravity y
    KSCSV_IDX_AGZ   = 34,   // gravity z
    KSCSV_IDX_ALX   = 35,   // linear acc x
    KSCSV_IDX_ALY   = 36,   // linear acc y
    KSCSV_IDX_ALZ   = 37,   // linear acc z
    KSCSV_IDX_QX    = 38,   // rotation vector x
    KSCSV_IDX_QY    = 39,   // rotation vector y
    KSCSV_IDX_QZ    = 40,   // rotation vector z
    KSCSV_IDX_QW    = 41,   // rotation vector w
    KSCSV_IDX_QAX   = 42,   // game rotation vector x
    KSCSV_IDX_QAY   = 43,   // game rotation vector y
    KSCSV_IDX_QAZ   = 44,   // game rotation vector z
    KSCSV_IDX_QAW   = 45,   // game rotation vector w
    KSCSV_IDX_QMX   = 46,   // geomagnetic rotation vector x
    KSCSV_IDX_QMY   = 47,   // geomagnetic rotation vector y
    KSCSV_IDX_QMZ   = 48,   // geomagnetic rotation vector z
    KSCSV_IDX_QMW   = 49,   // geomagnetic rotation vector w

    KSCSV_IDX_UNKNOWN,
    KSCSV_IDX_TOTAL,

} kscsv_item_t;

typedef struct
{
    double *sn;
    double *ts;
    double *dt;
    double *g[3], *gr[3], *gb[3];
    double *a[3], *ar[3], *ab[3];
    double *m[3], *mr[3], *mb[3];
    double *p, *t;
    double *ag[3], *al[3];
    double *q[4], *qa[4], *qm[4];
    double *unknown;
    uint64_t size;

} raw_t;

typedef struct
{
    FILE *fp;

    char *path;
    char *filename;
    int lens;
    int *tags;
    int tagcnt;
    union {
        unsigned int mem[KSCSV_IDX_TOTAL];
        raw_t raw;
    };
    // raw_t raw;

} kscsv_t;

/* Extern ----------------------------------------------------------------------------------*/

extern const char KSCSV_TAG_STRING[KSCSV_IDX_TOTAL][MAX_TAG_STRING_LENGTH];

/* Functions -------------------------------------------------------------------------------*/

int     kscsv_get_tag_count(char *line);
int     kscsv_get_tag_index(char *line);
int     kscsv_get_tag_index_array(char *line, int *idxarray);
int     kscsv_check_tag_index_array(int *idxarray, int lens);

int     kscsv_get_line_count(FILE *file);

int     kscsv_open(kscsv_t *csv, char *filename);
void    kscsv_release(kscsv_t *csv);
int     kscsv_close(kscsv_t *csv);
int     kscsv_read(kscsv_t *csv, int lens);

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/

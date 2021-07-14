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

/* Define ----------------------------------------------------------------------------------*/

// #define MAX_FILENAME_STRING_LENGTH      256
// #define MAX_PATH_STRING_LENGTH          256
#define MAX_FILE_LINE_STRING_LENGTH     8192
// #define MAX_TYPE_STRING_LENGTH          8

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/

typedef enum
{
    KSCSV_SN  = 0,      // serial number
    KSCSV_TS  = 1,      // timestamp
    KSCSV_DT  = 2,      // delta time
    KSCSV_GX  = 3,      // gyr calibrated data x
    KSCSV_GY  = 4,      // gyr calibrated data y
    KSCSV_GZ  = 5,      // gyr calibrated data z
    KSCSV_GRX = 6,      // gyr raw data x
    KSCSV_GRY = 7,      // gyr raw data y
    KSCSV_GRZ = 8,      // gyr raw data z
    KSCSV_GBX = 9,      // gyr bias x
    KSCSV_GBY = 10,     // gyr bias y
    KSCSV_GBZ = 11,     // gyr bias z
    KSCSV_AX  = 12,     // acc calibrated data x
    KSCSV_AY  = 13,     // acc calibrated data y
    KSCSV_AZ  = 14,     // acc calibrated data z
    KSCSV_ARX = 15,     // acc raw data x
    KSCSV_ARY = 16,     // acc raw data y
    KSCSV_ARZ = 17,     // acc raw data z
    KSCSV_ABX = 18,     // acc bias x
    KSCSV_ABY = 19,     // acc bias y
    KSCSV_ABZ = 20,     // acc bias z
    KSCSV_MX  = 21,     // mag calibrated data x
    KSCSV_MY  = 22,     // mag calibrated data y
    KSCSV_MZ  = 23,     // mag calibrated data z
    KSCSV_MRX = 24,     // mag raw data x
    KSCSV_MRY = 25,     // mag raw data y
    KSCSV_MRZ = 26,     // mag raw data z
    KSCSV_MBX = 27,     // mag bias x
    KSCSV_MBY = 28,     // mag bias y
    KSCSV_MBZ = 29,     // mag bias z
    KSCSV_P   = 30,     // pressure
    KSCSV_T   = 31,     // temperature
    KSCSV_AGX = 32,     // gravity x
    KSCSV_AGY = 33,     // gravity y
    KSCSV_AGZ = 34,     // gravity z
    KSCSV_ALX = 35,     // linear acc x
    KSCSV_ALY = 36,     // linear acc y
    KSCSV_ALZ = 37,     // linear acc z
    KSCSV_QX  = 38,     // rotation vector x
    KSCSV_QY  = 39,     // rotation vector y
    KSCSV_QZ  = 40,     // rotation vector z
    KSCSV_QW  = 41,     // rotation vector w
    KSCSV_QAX = 42,     // game rotation vector x
    KSCSV_QAY = 43,     // game rotation vector y
    KSCSV_QAZ = 44,     // game rotation vector z
    KSCSV_QAW = 45,     // game rotation vector w
    KSCSV_QMX = 46,     // geomagnetic rotation vector x
    KSCSV_QMY = 47,     // geomagnetic rotation vector y
    KSCSV_QMZ = 48,     // geomagnetic rotation vector z
    KSCSV_QMW = 49,     // geomagnetic rotation vector w

    KSCSV_UNKNOWN,
    KSCSV_END,

} kscsv_item_t;

typedef struct
{
    uint64_t *sn;
    uint64_t *ts;
    uint64_t *dt;
    float *g;
    float *gr;
    float *gb;
    float *a;
    float *ar;
    float *ab;
    float *m;
    float *mr;
    float *mb;
    float *p;
    float *t;
    float *ag;
    float *al;
    float *q;
    float *qa;
    float *qm;

} raw_t;

typedef struct {

    char *line;
    int lens;
    int itemidx[KSCSV_END];
    int itemcnt;
    char *path;
    char *filename;
    raw_t *raw;

} kscsv_t;

/* Extern ----------------------------------------------------------------------------------*/

extern const char KSCSV_ITEM_STRING[KSCSV_END][8];

/* Functions -------------------------------------------------------------------------------*/

int kscsv_get_item_count(char *line);
int kscsv_get_item_index(char *line);
int kscsv_get_item_index_array(char *line, int *idxarray);
int kscsv_check_index_array(int *idxarray, int lens);

int kscsv_get_line_count(FILE *file);

int kscsv_open(kscsv_t *csv, char *filename);
int kscsv_close(kscsv_t *csv);
void kscsv_read(kscsv_t *csv);

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>

#include "kscsv.h"

int main()
{
    kscsv_t csv = {0};

    printf("open csv ... ");
    if (kscsv_open(&csv, ".././log/TEST_1.csv") != KS_OK)
    // if (kscsv_open(&csv, ".././log/TEST_BIG.csv") != KS_OK)
    {
        printf("failed\n");
        return -1;
    }
    printf("ok\n\n");

    printf("csv.filename ... %s\n", csv.filename);
    printf("csv.lens ... %d\n", csv.lens);
    printf("csv.tagcnt ... %d\n\n", csv.tagcnt);
    for (int i = 0; i < csv.tagcnt; i++)
    {
        printf("[%02d] %s  ", csv.tags[i], KSCSV_TAG_STRING[csv.tags[i]]);
    }
    printf("\n");
    kscsv_read(&csv, -1);
    for (int i = 0; i < csv.lens; i++)
    {
        printf("[%04d] %.0lf %lf %lf %lf\n", i+1, csv.raw.sn[i], csv.raw.g[0][i], csv.raw.g[1][i], csv.raw.g[2][i]);
    }
    kscsv_close(&csv);

    return 0;
}

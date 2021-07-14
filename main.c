#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>

#include "kscsv.h"

int main()
{
    kscsv_t csv;

    char filename[256] = ".././log/TEST_1.csv";

    printf("open csv ... ");
    if (!kscsv_open(&csv, filename))
    {
        printf("failed\n");
        return -1;
    }
    printf("ok\n\n");

    printf("csv.lens ... %d\n", csv.lens);
    printf("csv.itemcnt ... %d\n\n", csv.itemcnt);
    for (int i = 0; i < csv.itemcnt; i++)
    {
        printf("[%02d] %s\n", csv.itemidx[i], KSCSV_ITEM_STRING[csv.itemidx[i]]);
    }
    kscsv_close(&csv);

    return 0;
}

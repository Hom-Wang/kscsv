#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>

#include "kscsv.h"

int main()
{
    kscsv_t csv = {0};

    printf("open csv ... ");
    if (!kscsv_open(&csv, ".././log/TEST_1.csv"))
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
        printf("[%02d] %s\n", csv.tagidx[i], KSCSV_TAG_STRING[csv.tagidx[i]]);
    }
    kscsv_close(&csv);

    return 0;
}

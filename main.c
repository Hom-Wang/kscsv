#include "kscsv.h"

char filename[] = ".././log/TEST_1.csv";

int opencsv(kscsv_t *csv, char *filename)
{
    if (kscsv_open(csv, filename) != KS_OK)
    {
        return KS_ERROR;
    }
    kscsv_info(csv);
    return KS_OK;
}

int main()
{
    kscsv_t csv = {0};

    // open csv
    if (opencsv(&csv, filename) != KS_OK)
    {
        printf("\nopen csv failed !!!\n");
        return -1;
    }
    // read csv
    kscsv_read(&csv, -1);

    // create csv
    char *TAG[] = {
        "sn","ts","gx","gy","gz","ax","ay","az","mx","my","mz","dt","mbx","mby","mbz"
    };
    if (kscsv_create(&csv, NULL, "output/", "_COPY", TAG, sizeof(TAG) >> 2) != KS_OK)
    {
        printf("create csv failed !!!\n");
        return -1;
    }
    // write csv
    for (int i = 0; i < csv.raw.size; i++)
    {
        // tag: sn,ts,gx,gy,gz,ax,ay,az,mx,my,mz,dt,mbx,mby,mbz
        kscsv_write(&csv, "%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f",
            csv.raw.sn[i], csv.raw.ts[i],
            csv.raw.g[0][i], csv.raw.g[1][i], csv.raw.g[2][i],
            csv.raw.a[0][i], csv.raw.a[1][i], csv.raw.a[2][i],
            csv.raw.m[0][i], csv.raw.m[1][i], csv.raw.m[2][i],
            csv.raw.dt[i],
            csv.raw.mb[0][i], csv.raw.mb[1][i], csv.raw.mb[2][i]);
    }
    // close csv
    kscsv_close(&csv);

    return 0;
}

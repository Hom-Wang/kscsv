#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>

#include "kscsv.h"

int opencsv(kscsv_t *csv, char *filename)
{
    if (kscsv_open(csv, filename) != KS_OK)
    {
        return KS_ERROR;
    }
    kscsv_info(csv);
    printf("\n");
    return KS_OK;
}

int main()
{
    kscsv_t csv = {0};
    if (opencsv(&csv, ".././log/TEST_3.csv") != KS_OK)
    {
        printf("\nopen csv failed !!!\n");
        return -1;
    }
    kscsv_read(&csv, -1);   // read all
#if 1
    // tag: sn,ts,gx,gy,gz,ax,ay,az,mx,my,mz,dt,mbx,mby,mbz
    for (int i = 0; i < csv.raw.size; i++)
    {
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.sn[i], csv.raw.ts[i],
            csv.raw.g[0][i], csv.raw.g[1][i], csv.raw.g[2][i],
            csv.raw.a[0][i], csv.raw.a[1][i], csv.raw.a[2][i],
            csv.raw.m[0][i], csv.raw.m[1][i], csv.raw.m[2][i],
            csv.raw.dt[i],
            csv.raw.mb[0][i], csv.raw.mb[1][i], csv.raw.mb[2][i]);
    }
#endif
#if 0
    // tag: sn,ts,unk[0],gy,unk[1],ax,unk[2],az,mx,my,mz,dt,mbx,mby,mbz
    for (int i = 0; i < csv.raw.size; i++)
    {
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.sn[i], csv.raw.ts[i],
            csv.raw.unknown[0][i], csv.raw.g[1][i], csv.raw.unknown[1][i],
            csv.raw.a[0][i], csv.raw.unknown[2][i], csv.raw.a[2][i],
            csv.raw.m[0][i], csv.raw.m[1][i], csv.raw.m[2][i],
            csv.raw.dt[i],
            csv.raw.mb[0][i], csv.raw.mb[1][i], csv.raw.mb[2][i]);
    }
#endif
#if 0
    // tags: unk[0],unk[1],unk[2],unk[3],unk[4],unk[5],unk[6],unk[7],unk[8],unk[9],unk[10],unk[11],unk[12],unk[13],unk[14]
    for (int i = 0; i < csv.raw.size; i++)
    {
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.unknown[0][i], csv.raw.unknown[1][i],
            csv.raw.unknown[2][i], csv.raw.unknown[3][i], csv.raw.unknown[4][i],
            csv.raw.unknown[5][i], csv.raw.unknown[6][i], csv.raw.unknown[7][i],
            csv.raw.unknown[8][i], csv.raw.unknown[9][i], csv.raw.unknown[10][i],
            csv.raw.unknown[11][i],
            csv.raw.unknown[12][i], csv.raw.unknown[13][i], csv.raw.unknown[14][i]);
    }
#endif
    kscsv_close(&csv);

    return 0;
}

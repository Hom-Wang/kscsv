#include "kscsv.h"


#define LOGFILE_NO_UNKNOWN      1
#define LOGFILE_SOME_UNKNOWN    2
#define LOGFILE_ALL_UNKNOWN     3
#define LOGFILE                 LOGFILE_NO_UNKNOWN

#if LOGFILE == LOGFILE_NO_UNKNOWN
char filename[] = ".././log/TEST_1.csv";
#elif LOGFILE == LOGFILE_SOME_UNKNOWN
char filename[] = ".././log/TEST_2.csv";
#elif LOGFILE == LOGFILE_ALL_UNKNOWN
char filename[] = ".././log/TEST_3.csv";
#endif

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
    if (opencsv(&csv, filename) != KS_OK)
    {
        printf("\nopen csv failed !!!\n");
        return -1;
    }

    while (kscsv_read(&csv, 0) != KS_ERROR)
    {
        int i = csv.raw.index;
        printf("[%4d] ", csv.raw.index);
#if (LOGFILE == LOGFILE_NO_UNKNOWN)
        // tag: sn,ts,gx,gy,gz,ax,ay,az,mx,my,mz,dt,mbx,mby,mbz
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.sn[i], csv.raw.ts[i],
            csv.raw.g[0][i], csv.raw.g[1][i], csv.raw.g[2][i],
            csv.raw.a[0][i], csv.raw.a[1][i], csv.raw.a[2][i],
            csv.raw.m[0][i], csv.raw.m[1][i], csv.raw.m[2][i],
            csv.raw.dt[i],
            csv.raw.mb[0][i], csv.raw.mb[1][i], csv.raw.mb[2][i]);
#elif (LOGFILE == LOGFILE_SOME_UNKNOWN)
        // tag: sn,ts,unk[0],gy,unk[1],ax,unk[2],az,mx,my,mz,dt,mbx,mby,mbz
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.sn[i], csv.raw.ts[i],
            csv.raw.unknown[0][i], csv.raw.g[1][i], csv.raw.unknown[1][i],
            csv.raw.a[0][i], csv.raw.unknown[2][i], csv.raw.a[2][i],
            csv.raw.m[0][i], csv.raw.m[1][i], csv.raw.m[2][i],
            csv.raw.dt[i],
            csv.raw.mb[0][i], csv.raw.mb[1][i], csv.raw.mb[2][i]);
#elif (LOGFILE == LOGFILE_ALL_UNKNOWN)
        // tags: unk[0],unk[1],unk[2],unk[3],unk[4],unk[5],unk[6],unk[7],unk[8],unk[9],unk[10],unk[11],unk[12],unk[13],unk[14]
        printf("%.0f,%.0f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n",
            csv.raw.unknown[0][i], csv.raw.unknown[1][i],
            csv.raw.unknown[2][i], csv.raw.unknown[3][i], csv.raw.unknown[4][i],
            csv.raw.unknown[5][i], csv.raw.unknown[6][i], csv.raw.unknown[7][i],
            csv.raw.unknown[8][i], csv.raw.unknown[9][i], csv.raw.unknown[10][i],
            csv.raw.unknown[11][i],
            csv.raw.unknown[12][i], csv.raw.unknown[13][i], csv.raw.unknown[14][i]);
#endif
    }

    kscsv_close(&csv);

    return 0;
}

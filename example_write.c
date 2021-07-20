#include "kscsv.h"

char filename[] = ".././log/write/TEST_0.csv";

int main()
{
    kscsv_t csv = {0};

    // create csv
    char *TAG[] = {
        "sn","ts","gx"
    };
    if (kscsv_create(&csv, filename, NULL, TAG, sizeof(TAG) >> 2) != KS_OK)
    {
        printf("create csv failed !!!\n");
        return -1;
    }

    // write
    for (int i = 0; i < 100; i++)
    {
        // tag: sn,ts,gx
        kscsv_write(&csv, "%.0f,%.0f,%.10f",
            i*1.0, i*1.0e6, i*1.0e-6);
    }

    // close csv
    kscsv_close(&csv);

    return 0;
}

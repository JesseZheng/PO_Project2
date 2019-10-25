#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float *dataProducer(int DataSetSize)
{
    static float *v;
    v = malloc(DataSetSize * sizeof(float));
    srand(time(NULL));
    for (int i = 0; i < DataSetSize; i++) {
        v[i] = 100*(float)rand()/(float)(RAND_MAX);
    }
    return v;
}


int writeDataset(float* dataset, const char *filename, int datasetSize)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    fwrite(dataset, sizeof(float), datasetSize, fp);
    fclose(fp);
    return 0;
}

int main(int argc,char *argv[])
{
	int datasetSize;

    if (argc == 2)
        datasetSize = atoi(argv[1]);
    else
        datasetSize = 50;

    char filename[256] = "Dataset";
    sprintf(filename, "%s%d", filename, datasetSize);

    //generate random dataset and save it as .txt file
    float *ds = dataProducer(datasetSize);

    writeDataset(ds, filename, datasetSize);

    printf("%s has been generated!\n", filename);

}




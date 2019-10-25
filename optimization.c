#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

const char SAVEFILE[] = "sorted";


int cmp_float(const void* _a, const void* _b)
{
    float* a = (float*)_a;
    float* b = (float*)_b;
    return *a > *b ? 1 : -1;
}

int loadDataset(float* dataset, const char *filename, int datasetSize, int bufferSize) 
{
    FILE *fp;
    fp = fopen(filename , "rb");
    for(int i=0; i < datasetSize; i += bufferSize){
        if (bufferSize > datasetSize - i)
            bufferSize = datasetSize - i;
        fread(dataset+i, sizeof(float), bufferSize, fp);
    }
    fclose(fp);
    return 0;
}

int writeDataset(float* dataset, const char *filename, int datasetSize, int bufferSize, float avg, float min, float max)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    float stats[] = {avg, min, max};
    fwrite(stats, sizeof(float), 3, fp);
    for(int i=0; i < datasetSize; i+= bufferSize){
        if (bufferSize > datasetSize - i)
            bufferSize = datasetSize - i;
        fwrite(dataset+i, sizeof(float), bufferSize, fp);
    }
    fclose(fp);
    return 0;
}

void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(float *dataset, int datasetSize)
{
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < datasetSize-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (int j = i+1; j < datasetSize; j++)
            if (dataset[j] < dataset[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        swap(&dataset[min_idx], &dataset[i]);
    }
}

void insertionSort(float *dataset, int datasetSize)
{
        int i, j;
        float key;
        for (i=1; i<datasetSize; i++) {
            key = dataset[i];
            j=i-1;
            while((j>=0) && (dataset[j]>key)) {
                    dataset[j+1] = dataset[j];
                    j--;
            }
            dataset[j+1] = key;
        }
}

void quickSort(float* dataset, int datasetSize)
{
    qsort(dataset, datasetSize, sizeof(float), cmp_float);
}


float average(float* dataset, int datasetSize)
{
    float avg, sum = 0;
    for (int i = 0; i<datasetSize; i++){
        sum = sum + dataset[i];
    }
    avg = (float)sum/datasetSize;
    return avg;
}

float minValue(float* dataset, int datasetSize)
{
    float minValue = dataset[0];
    for (int i = 1; i<datasetSize; i++){
        if (dataset[i]<minValue)
            minValue = dataset[i];
    }
    return minValue;
}

float maxValue(float* dataset, int datasetSize)
{
    float maxValue = dataset[0];
    for (int i = 1; i<datasetSize; i++){
        if (dataset[i]>maxValue)
            maxValue = dataset[i];
    }
    return maxValue;
}

int main(int argc,char *argv[])
{	
    float avg, max, min;
    char *loadfile;
    int datasetSize, bufferSize;

    if (argc == 4) {
        datasetSize = atoi(argv[1]);
        bufferSize = atoi(argv[2]);
        loadfile = argv[3];
    }
    else {
        printf("%s\n", "Usage: project2 <datasetSize> <bufferSize> <loadfile>");
        return -1;
    }
    
    // printf("original of dataset:\n");
    // for (int i = 0; i < datasetSize; i++) {
    //     printf("%f\n", ds[i]);
    // }

    float *dataSet= malloc((datasetSize)*sizeof(float));

    //load data to ds from saved file and sort
    loadDataset(dataSet, loadfile, datasetSize, bufferSize);

    // compute the avg of the dateset
    avg = average(dataSet, datasetSize);

    // find the max and min value in the dateset
    max = maxValue(dataSet, datasetSize);
    min = minValue(dataSet, datasetSize);

    printf("sorting\n");
    // selectionSort(dataSet, datasetSize);
    insertionSort(dataSet, datasetSize);
    // quickSort(dataSet, datasetSize);

    // printf("Result dataset:\n");
    // for (int i = 0; i < datasetSize; i++) {
    //     printf("%d: %f\n", i, dataSet[i]);
    // }



    printf("%s\n", "write");
    //save sorted dataset
    writeDataset(dataSet, SAVEFILE, datasetSize, bufferSize, avg, min, max);

    return 0;

}
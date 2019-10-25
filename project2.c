#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

const char  LOADFILE[] = "dataset.txt";
const char  SAVEFILE[] = "sorted.txt";


int loadDataset(float* dataset, const char *filename, int datasetSize, int bufferSize) 
{
    FILE *fp;
    fp = fopen(filename , "r");
    for(int i=0; i < datasetSize; i += bufferSize){
        if (bufferSize > datasetSize - i)
            bufferSize = datasetSize - i;
        fread(dataset+i, sizeof(float), bufferSize, fp);
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


int writeDataset(float* dataset, const char *filename, int datasetSize, int bufferSize)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    for(int i=0; i < datasetSize; i+= bufferSize){
        if (bufferSize > datasetSize - i)
            bufferSize = datasetSize - i;
        fwrite(dataset+i, sizeof(float), bufferSize, fp);
        printf("%d:%f\n", i, dataset[i]);
    }
    fclose(fp);
    return 0;
}


float *dataProducer(int DataSetSize)
{
    static float *v;
    v = malloc(DataSetSize * sizeof(float));
    srand(time(NULL));
    // printf("the generated data:\n");
    for (int i = 0; i < DataSetSize; i++) {
        v[i] = 100*(float)rand()/(float)(RAND_MAX);
        // printf("%f\n",v[i]);
    }
    return v;
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
    printf("So far so good!\n");
    float avg, max, min;

    int datasetSize, bufferSize;

    if (argc == 3) {
        datasetSize = atoi(argv[1]);
        bufferSize = atoi(argv[2]);
    }
    else {
        datasetSize = 50;
        bufferSize = 8;
    }

    //generate random dataset and save it as .txt file
    float *ds = dataProducer(datasetSize);
    
    printf("original of dataset:\n");

    for (int i = 0; i < datasetSize; i++) {
        printf("%f\n",ds[i]);
    }

    writeDataset(ds, LOADFILE, datasetSize, bufferSize);

    float dataSet[datasetSize];

    //load data to ds from saved file and sort
    loadDataset(dataSet, LOADFILE, datasetSize, bufferSize);

    printf("sorting\n");

    // compute the avg of the dateset
    avg = average(dataSet, datasetSize);

    // find the max and min value in the dateset
    max = maxValue(dataSet, datasetSize);
    min = minValue(dataSet, datasetSize);

    // selectionSort(dataSet, datasetSize);
    insertionSort(dataSet, datasetSize);

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("list of sorted data:\n");
    for(int i = datasetSize-1; i >= 0; i-- ){
        dataSet[i+3] = dataSet[i];
        printf("%d: %f\n",i,dataSet[i]);
    }

    dataSet[0] = avg;
    dataSet[1] = max;
    dataSet[2] = min;


    datasetSize = datasetSize + 3;

    //save sorted dataset
    writeDataset(dataSet,SAVEFILE, datasetSize, bufferSize);
    printf(">>>>>>>>result<<<<<<<<<<<<\n");
    for (int i = 0; i < datasetSize; i++) {
        printf("%d: %f\n",i+1, dataSet[i]);
    }

    return 0;

}
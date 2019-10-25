#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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
    // The name of input dataset file
    char *loadfile;
    // The name of output dataset file
    char savefile[20];
    int datasetSize, bufferSize;
    // Calucate the runtime
    clock_t load_start, load_finish, stats_start, stats_finish, sort_start, sort_finish, write_start, write_finish;


    if (argc == 4) {
        datasetSize = atoi(argv[1]);
        bufferSize = atoi(argv[2]);
        loadfile = argv[3];
    }
    else {
        printf("%s\n", "Usage: project2 <datasetSize> <bufferSize> <loadfile>");
        return -1;
    }

    // Generate the filename of output dataset 
    strcpy(savefile, loadfile);
    strcat(savefile, "_Sorted\0");

    // The sorted dataset is declared
    float *dataSet= malloc((datasetSize)*sizeof(float));

    printf("%s\n", "Loading..............");
    load_start = clock();
    //load data to ds from saved file and sort
    loadDataset(dataSet, loadfile, datasetSize, bufferSize);
    load_finish = clock();

    stats_start = clock();
    // compute the avg of the dateset
    avg = average(dataSet, datasetSize);
    // find the max and min value in the dateset
    max = maxValue(dataSet, datasetSize);
    min = minValue(dataSet, datasetSize);
    stats_finish = clock();

    printf("%s\n", "Sorting..............");
    sort_start = clock();
    // selectionSort(dataSet, datasetSize);
    // insertionSort(dataSet, datasetSize);
    quickSort(dataSet, datasetSize);
    sort_finish = clock();


    printf("%s\n", "Writing..............");
    write_start = clock();
    //save sorted dataset
    writeDataset(dataSet, savefile, datasetSize, bufferSize, avg, min, max);
    write_finish = clock();


    double dur_load = (double)(load_finish-load_start)/CLOCKS_PER_SEC;
    double dur_stats = (double)(stats_finish-stats_start)/CLOCKS_PER_SEC;
    double dur_sort = (double)(sort_finish-sort_start)/CLOCKS_PER_SEC;
    double dur_write = (double)(write_finish-write_start)/CLOCKS_PER_SEC;
    double totoal_time = dur_load + dur_write + dur_sort + dur_stats;
    double percent_load = dur_load/totoal_time*100.0;
    double percent_stats = dur_stats/totoal_time*100.0;
    double percent_sort = dur_sort/totoal_time*100.0;
    double percent_write = dur_write/totoal_time*100.0;
    
    printf("----------------------------------------------\n");
    printf( "Time to load data is: %f seconds %f%%\n", dur_load, percent_load);
    printf( "Time to stats data is: %f seconds %f%%\n", dur_stats, percent_stats);
    printf( "Time to sort data is: %f seconds %f%%\n", dur_sort, percent_sort);
    printf( "Time to write data is: %f seconds %f%%\n", dur_write, percent_write);
    printf("----------------------------------------------\n");
    printf( "Totoal Time: %f seconds\n", totoal_time );


    return 0;

}
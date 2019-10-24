#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char  LOADFILE[] = "dataset.txt";
const char  SAVEFILE[] = "sorted.txt";

struct Array{
    float *arr;
    int size;
}dataset,ds;   //dataset is for data generating, ds is for read/write operation.

int loadDataset (struct Array *d, const char *filename) {
    FILE *fp;
    fp = fopen( filename , "r" );
    for( int i=0; i < d->size; i++){
        fread( d->arr+i, sizeof(float), 1, fp );
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

void selectionSort(struct Array *d)
{
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < d->size-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (int j = i+1; j < d->size; j++)
            if (d->arr[j] < d->arr[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        swap(&d->arr[min_idx], &d->arr[i]);
    }
}

void insertionSort(struct Array *d)
{
        int i, j;
        float key;
        int len = d->size;
        for (i=1;i<len;i++) {
                key = d->arr[i];
                j=i-1;
                while((j>=0) && (d->arr[j]>key)) {
                        d->arr[j+1] = d->arr[j];
                        j--;
                }
                d->arr[j+1] = key;
        }
}


int writeDataset (struct Array *d, const char *filename)
{
    FILE *fp;
    char str[] = "just for test";
    fp = fopen(filename, "w" );
    for(int i=0; i < d->size; i++){
        fwrite(d->arr+i, sizeof(float), 1, fp );
        printf("write %f to file\n",*(d->arr+i));
    }
    //fwrite(str, sizeof(char), 2, fp );
    fclose(fp);
    return 0;
}


float *dataProducer(int DataSetSize)
{
    static float *v;
    v = malloc(DataSetSize * sizeof(float));
    srand(time(NULL));
    printf("the generated data:\n");
    for (int i = 0; i < DataSetSize; i++) {
        v[i] = 100*(float)rand()/(float)(RAND_MAX);
        printf("%f\n",v[i]);
    }
    
    return v;
}


float average(struct Array d)
{
    float avg, sum = 0;
    for (int i = 0; i<d.size; i++){
        sum = sum + d.arr[i];
    }
    avg = (float)sum/d.size;
    return avg;
}

int main(int argc,char *argv[])
{	
    printf("So far so good!\n");
    float avg, max, min;
    int dataSize = atoi(argv[1]);


    //generate random dataset and save it as .txt file
    dataset.arr = dataProducer(dataSize);
    dataset.size = dataSize;
    
    printf("==========================\n");
    printf("real value of dataset:\n");

    for (int i = 0; i < dataSize; i++) {
        printf("%f\n",dataset.arr[i]);
    }
    writeDataset(&dataset,LOADFILE);
    printf("original size of dataset:%d\n",dataset.size);

    //load data to ds from saved file and sort
    ds.size = dataSize;
    ds.arr = dataset.arr;
    loadDataset(&ds,LOADFILE);
    // selectionSort(&ds);
    insertionSort(&ds);

    printf(">>>>>>>>after sorting<<<<<<<<<<<<\n");
    for (int i = 0; i < dataSize; i++) {
        printf("%f\n",ds.arr[i]);
    }

    avg = average(ds);
    int length = sizeof(ds.arr)/sizeof(float);
    printf("current size of dataset: %d\n",length);

    max = ds.arr[dataSize-1];
    min = ds.arr[0];

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("list of sorted data:\n");
    for(int i = dataSize-1; i >= 0; i-- ){
        ds.arr[i+3] = ds.arr[i];
        printf("%d: %f\n",i,ds.arr[i]);
    }

    ds.arr[0] = avg;
    ds.arr[1] = max;
    ds.arr[2] = min;


    ds.size = ds.size + 3;

    //save sorted dataset
    writeDataset(&ds,SAVEFILE);
    printf(">>>>>>>>result<<<<<<<<<<<<\n");
    for (int i = 0; i < ds.size; i++) {
        printf("%d: %f\n",i+1, ds.arr[i]);
    }

    loadDataset(&ds,SAVEFILE);
    printf(">>>>>>>>check<<<<<<<<<<<<\n");
    for (int i = 0; i < ds.size; i++) {
        printf("%d: %f\n",i+1, ds.arr[i]);
    }

    return 0;

}
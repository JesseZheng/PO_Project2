# Makefile

- **make**: compile the program **without** gcc compiler optimization
- **make optimization**: compile the program **with** gcc compiler optimization
- **make clean**: clean up the executable file and dateset

# project2
- Usage: *`project2 <datasetSize> <bufferSize> <loadfile>`*
- Output dataset filename = `Dataset<datasetSize>_Sorted`
- Sorting algorithm = insertion sort
- Standard read/write buffer size **1024000**
- Read/write block size equal to the size of a single record in the file, that is a floating point number.
- gcc compiler optimization turned off

# optimization
- Usage: *`optimizaiton <datasetSize> <bufferSize> <loadfile>`*
- Sorting algorithm = quick sort
- gcc compiler optimization turned on

# datasetGenerator
- Usage: *`datasetGenerator <datasetSize>`*
- Output Filename = `Dataset<datasetSize>`

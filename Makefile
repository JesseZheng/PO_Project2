all: 
	gcc -O0 project2.c -o project2
	gcc -O0 datasetGenerator.c -o datasetGenerator
	gcc -O0 optimization.c -o optimization

optimazation:
	gcc -O3 project2.c -o project2
	gcc -O3 datasetGenerator.c -o datasetGenerator
	gcc -O3 optimization.c -o optimization

clean: 
	rm project2
	rm datasetGenerator
	rm optimization
	rm Dataset*
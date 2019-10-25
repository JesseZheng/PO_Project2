all: 
	gcc -O0 project2.c -o project2
	gcc -O0 datasetGenerator.c -o datasetGenerator
	gcc -O0 optimazation.c -o optimazation

optimazation:
	gcc -O3 project2.c -o project2
	gcc -O3 datasetGenerator.c -o datasetGenerator
	gcc -O3 optimazation.c -o optimazation

clean: 
	rm project2
	rm datasetGenerator
	rm optimazation
	rm Dataset*
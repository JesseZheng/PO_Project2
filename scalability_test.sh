N=10
size=1000
echo -e "Scalability test N="${N}" size="${size}"\n\n" > scalability_test_${N}.txt
for (( i = 0; i < 5; i++ )); 
do
	./datasetGenerator $size
	echo size = $size >> scalability_test_${N}.txt
	{ time ./optimization $size 102400 Dataset${size}; } 2>> scalability_test_${N}.txt
	echo -e "---------------\n\n" >> scalability_test_${N}.txt
	rm Dataset${size}
	rm Dataset${size}_Sorted
	((size = size * N))
done

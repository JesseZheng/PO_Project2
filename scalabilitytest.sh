N=10
size=1000
echo -e "Scalability test N="${N}" size="${size}"\n\n" > scalabilitytest-${N}.txt
for (( i = 0; i < 5; i++ )); 
do
	./datasetGenerator $size
	echo size = $size >> scalabilitytest-${N}.txt
	{ time ./optimization $size 102400 Dataset${size}; } 2>> scalabilitytest-${N}.txt
	echo "---------------" >> scalabilitytest-${N}.txt
	rm Dataset${size}
	rm Dataset${size}_Sorted
	((size = size * N))
done

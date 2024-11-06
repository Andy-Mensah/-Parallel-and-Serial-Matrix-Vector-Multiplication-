CC = mpicc
CFLAGS = -O3 -c
OBJ = 4170120.x
PILE = 4170120_main.o 4170120_vector.o
core_values := 1 2 3 4 5 6 7 8
N := 250000000

all: $(OBJ) plot

$(OBJ): $(PILE)
	rm -f ./4170120_scale.txt
	$(CC) -o $(OBJ) $(PILE)
	for i in $(core_values); do \
		mpirun -oversubscribe -np $$i --use-hwthread-cpus $(OBJ) $(N) $$i; \
	done
	

4170120_vector.o: 4170120_vector.c
	$(CC) $(CFLAGS) 4170120_vector.c


plot: ./4170120_scale.txt
	echo "#! /usr/bin/bash" > 4170120.sh
	echo "gnuplot -persist <<-EOF" >> 4170120.sh
	echo "	set title \"Number of Processors VRS TIME\"" >> 4170120.sh
	echo "	set xlabel \"Number of Processors\"" >> 4170120.sh
	echo "	set ylabel \"RUNTIME: Time(sec)\"" >> 4170120.sh
	echo "	set key left" >> 4170120.sh
	echo "	set grid" >> 4170120.sh
	echo "	set terminal png size 800,600" >> 4170120.sh
	echo "	set output \"./4170120.png\"" >> 4170120.sh
	echo "	plot \"./4170120_scale.txt\" using 2:3 title \"Vector_Vector\" lt 22 lw 3 lc 22 w lp" >> 4170120.sh
	echo "EOF" >> 4170120.sh
	chmod +x 4170120.sh
	./4170120.sh
	rm -f 4170120.sh

clean: 
	rm -f $(PILE) $(OBJ)

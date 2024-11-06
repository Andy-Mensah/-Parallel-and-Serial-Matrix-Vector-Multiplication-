CC = gcc
CFLAGS = -O3 -c
OBJ = 4170120.x
PILE = 4170120_main.o 4170120_vector.o 4170120_matrix.o

all: $(OBJ) plot

$(OBJ): $(PILE)
	$(CC) -o $(OBJ) $(PILE)
	./$(OBJ)

4170120_main.o: 4170120_main.c
	$(CC) $(CFLAGS) 4170120_main.c

4170120_vector.o: 4170120_vector.c
	$(CC) $(CFLAGS) 4170120_vector.c

4170120_matrix.o: 4170120_matrix.c
	$(CC) $(CFLAGS) 4170120_matrix.c

plot: ./4170120_serial.txt
	echo "#! /usr/bin/bash" > temp_4170120.sh
	echo "gnuplot -persist <<-EOF" >> temp_4170120.sh
	echo "	set title \"N VRS TIME\"" >> temp_4170120.sh
	echo "	set xlabel \"N\"" >> temp_4170120.sh
	echo "	set ylabel \"RUNTIME: Time(sec)\"" >> temp_4170120.sh
	echo "	set key left" >> temp_4170120.sh
	echo "	set grid" >> temp_4170120.sh
	echo "	set terminal png size 800,600" >> temp_4170120.sh
	echo "	set output \"./4170120.png\"" >> temp_4170120.sh
	echo "	plot \"./4170120_serial.txt\" using 1:3 title \"V.V/s\" lt 22 lw 3 lc 22 w lp, \"\" using 1:4 title \"M.V/s\" lt 26 lw 3 lc 7 w lp, \"\" using 1:5 title \"M.M/s\" lt 22 lw 3 lc 1 w lp" >> temp_4170120.sh
	echo "EOF" >> temp_4170120.sh
	chmod +x temp_4170120.sh
	./temp_4170120.sh
	rm temp_4170120.sh



clean:
	rm -f $(OBJ) $(PILE)

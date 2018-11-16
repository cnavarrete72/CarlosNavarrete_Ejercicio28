output1: listing7.x
	mpirun -np 4 ./listing7.x

listing7.x: listing7.c
	mpicc listing7.c -o listing7.x

clean:
	rm -f output1
	rm -f output2

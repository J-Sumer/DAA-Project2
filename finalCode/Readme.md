<!-- g++ prims.cpp -o prims
./prims ProgramTwo-Student-Files/bt7.gph > result.out 2> err.out

./nextgen type vertices edges seed | ./normalize weights max weight > ../reportGraphs/ra.gph


./generate.sh [ NUMBER_OF_INSTANCES ] TYPE NODES EDGES STARTING_SEED [ MAX_WEIGHT ]
 rn (random), gm (geometric), gw (geometric with wraparound), or dt (Delaunay triangulation)

./generate.sh 2 rn 5 10 1 6 -->

## To run out code 

For Prims 1st implementation
g++ prims1.cpp -o prims1
./prims1 <file_name> > <output_file_name> 2> <output_error_file>
e.g ./prims1 br.gph > br.out 2> br.err


For Prims 2nd implementation
g++ prims2.cpp -o prims2
./prims2 <file_name> > <output_file_name> 2> <output_error_file>
e.g ./prims2 br.gph > br.out 2> br.err


For Kruskal's implementation
g++ kruskal.cpp -o kruskal
./kruskal <file_name> > <output_file_name> 2> <output_error_file>
e.g ./kruskal br.gph > br.out 2> br.err
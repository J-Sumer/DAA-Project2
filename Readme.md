g++ prims.cpp -o prims
./prims ProgramTwo-Student-Files/bt7.gph > result.out 2> err.out

./nextgen type vertices edges seed | ./normalize weights max weight > ../reportGraphs/ra.gph


./generate.sh [ NUMBER_OF_INSTANCES ] TYPE NODES EDGES STARTING_SEED [ MAX_WEIGHT ]
 rn (random), gm (geometric), gw (geometric with wraparound), or dt (Delaunay triangulation)

./generate.sh 2 rn 5 10 1 6
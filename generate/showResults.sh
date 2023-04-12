#! /bin/bash

echo "Prims 1 results"
cat p1.err | grep "[r|c]"
echo


echo "Prims 2 results"
cat p2.err | grep "[r|c]"
echo 

echo "Kruskals results"
cat k.err | grep "[r|c]"

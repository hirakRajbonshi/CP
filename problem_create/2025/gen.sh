N=5
path="gcd_ij"
g++ "$path/gen.cpp" -o gen
for (( i=1; i<=N; i++ ))
do
    ./gen $i > $path/test$i.txt
    echo "Test $i generated!"
done

echo "Execution completed!"

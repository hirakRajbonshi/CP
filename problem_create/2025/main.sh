N=5
path="gcd_ij"
g++ "$path/main.cpp" -o main
for (( i=1; i<=N; i++ ))
do
    ./main < $path/test$i.txt > $path/output$i.txt
    echo "Test $i done!"
done

echo "Execution completed!"

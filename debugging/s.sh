NUM_TEST_CASES=1000000000000
# NUM_TEST_CASES=1
g++ gen.cpp -o "gen"
g++ main.cpp -o "main"
g++ brute.cpp -o "brute"
for ((i=1; i<=NUM_TEST_CASES; i++)); do
    
    ./gen $i
    
    ./main
    
    ./brute
    
    diff output1.txt output2.txt > /dev/null
    if [ $? -ne 0 ]; then
        echo "Test case $i failed:"
        cat input.txt
        echo "main output:"
        cat output1.txt
        echo "brute output:"
        cat output2.txt
        echo "----"
        break
    else
        echo "Test case $i passed"
    fi
done
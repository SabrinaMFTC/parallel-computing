# Removing existing .txt
rm -if results.txt

# Compiling program

# With compile parameter that turns off optimization options
# gcc -O0 matrix.c -o matrix
# time -p ./matrix

# With compile parameter that turn on all optimization options
gcc -O3 matrix.c -o matrix
time -p ./matrix

# Writing to .txt
# time -p ./matrix >> results.txt
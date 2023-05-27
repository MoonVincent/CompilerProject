./Compiler ./test_cases/quick_sort.cmm
riscv64-unknown-linux-gnu-gcc -static -o quick_sort ./build/quick_sort.s -I ./include -L ./lib -l sysy
./Compiler ./test_cases/mat.cmm
riscv64-unknown-linux-gnu-gcc -static -o mat ./build/mat.s -I ./include -L ./lib -l sysy
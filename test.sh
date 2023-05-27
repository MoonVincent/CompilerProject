bash buildCompiler.sh
bash ./buildQs.sh
echo "TESTER-1"
qemu-riscv64 ./arctest-q-riscv qemu-riscv64 ./quick_sort
bash buildMat.sh
echo "TESTER-2"
qemu-riscv64 ./arctest-m-riscv qemu-riscv64 ./mat
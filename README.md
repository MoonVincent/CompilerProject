# CompilerProject

### **环境要求**

- Linux环境
- flex 2.6.4
- bison (GNU Bison) 3.8.2
- g++
- riscv64-unknown-linux-gnu-gcc
- qemu-riscv64

### **使用方式**
- 仅测试：`bash test.sh`
- 仅编译Compiler： `bash buildCompiler.sh`
- 仅编译quick_sort：`bash buildQs.sh`
- 仅编译mat_multi：`bash mat.sh`

### **文件结构**

```
/CompilerProject

    /build ：编译产生的中间文件

    /include：运行时库头文件

    /lib：运行时库

    /Manual：参考手册（南京大学编译原理2022）

    /src：源代码
        /include：头文件
        /codeGen：目标代码生成
        /irGen：中间代码生成
        /parser：词法和语法分析
        /semantic：语义分析
        
    /test_cases：测试样例

```


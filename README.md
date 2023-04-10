# CompilerProject
The project of compiler principle

- **文件结构**：
```TXT
/CompilerProject
    /Code
		Makefile
		lexical.l
		syntax.y
		main.c
		  .
		  .
	
    /Test
		test1.cmm
		test2.cmm
		  .
		  .
	
    /parser
	
    /README.md
```

- **Code目录**:；
  <br>
    1. 用于存放所有flex，bison，C语言源文件和头文件以及Makefile
   <br>
    2. 该目录下有一个Makefile文件，请使用它。除了定义和修改一些伪目标外不可对文件做其它修改（否则助教测试失败必扣分）；
   <br>
	3. 请勿在该目录下创建子目录（如include、src等），实验的代码量还没有复杂到需要将头文件以及源文件分开管理的程度；
   <br>
	4. 避免不合理的文件include关系，比如一个C文件include另一个C文件，Makefile执行时会报错。
	<br>
- **Test目录**：	
  <br>
  1. 用于存放测试文件以及输出文件（如果有输出文件的话）；
  <br>
  2. 请将测试文件以".cmm"作为后缀名。
  <br>

- **parser**：	
<br>
  1. 用你编译生成的二进制文件替换该文件。


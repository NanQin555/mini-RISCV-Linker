# 整体流程

汇编器 .s -> .o 

链接器 .o -> elf

我们实现静态链接器 ~~maybe~~



# ELF

Executable and Linkable Format

![alt text](img/ELF_structure.png)
An ELF file has two views: the program header shows the segments used at run time, whereas the section header lists the set of sections.

ELF header

file data:
1. Program header table
2. Section header table
3. Data referred
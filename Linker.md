# ELF 格式

仅标识出重要部分 
[ELF wiki](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)

[elf manu](https://manpages.debian.org/stretch/manpages/elf.5.en.html)
 
整体：

1. ELFHeader
2. ProgramHeader
3. SectionHeader

ELFHeader:

1. e_ident[Magic_number]: 7F 45 4C 46 !ELF
2. e_type: ET_NONE(Unknown), ET_REL(Relocatable file), ET_EXEC(Executable file) ...
3. e_machine: RISC-V here
4. e_entry: memory address of the entry point from where the process starts executing
5. e_phoff: Points to the start of the program header table
6. e_shoff: Points to the start of the section header table
7. e_ehsize: Contains the size of this header
8. e_phentsize: Contains the size of a program header table entry
9. e_phnum: Contains the number of entries in the program header table
10. e_shentsize: Contains the size of a section header table entry
11. e_shnum: Contains the number of entries in the section header table
12. e_shstrndx: Contains index of the section header table entry that contains the section names

ProgramHeader:


SectionHeader:

1. sh_name: An offset to a string in the .shstrtab section that represents the name of this section
2. sh_type: Identifies the type of this header
3. sh_flags: Identifies the attributes of the section
4. sh_addr: Virtual address of the section in memory
5. sh_offset: Offset of the section in the file image
6. sh_size: Size in bytes of the section

# 解析参数

有三种参数形式 

1. -h 
2. -o <output_file>
3. -plugin-opt=<option>

需要分别解析，并保存

-o <output_file> 保存到Output

-L<path> 添加LibraryPath

-l<library> 添加remaining 后续再处理

其余参数不考虑

# 读取文件

读 -lgcc 等input文件：需要找到 Library path, 注意库的名字为 lib<xx>.a

读普通input文件

## 读文件操作

读 Object file: 需要标注该文件是否是库文件

读 Archive file
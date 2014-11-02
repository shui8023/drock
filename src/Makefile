#
#  drock的Makefile文件
#
BC_OBJECTS=$(patsubst %.c, %.o, $(wildcard ./boot/*.c))
BS_OBJECTS=$(patsubst %.S, %.o, $(wildcard ./boot/*.S))

#除去了sign.c这个文件
C_SING=$(wildcard ./tool/*.c)
C_SOURCES=$(filter-out $(C_SING), $(shell find -name *.c))
#除去了./boot/bootmain.c这个文件的.o格式,链接脚本不一样
C_OBJECTS=$(patsubst %.c, %.o, $(filter-out ./boot/bootmain.c,$(C_SOURCES)))

S_OBJECTS=$(patsubst %.S, %.o, $(filter-out ./boot/*.S,$(wildcard *.S)))

T_SOURCES=$(filter ./tool/*.c, $(wildcard *.c))

MK_BOOT_FILE=$(shell mkdir ./bin)
MK_OBJ_FILE=$(shell mkdir ./obj)

CC=gcc

AS=as

LD=ld

RM=rm

MKDIR=mkdir

QEMU=qemu-system-i386

OBJ=objcopy 

CC_FLAGE= -c  -nostdlib -fno-builtin -fno-stack-protector -gstabs+ -Wall -ggdb  -m32 

SS_FLAGE= 

#
#必须把第一个boot.S的文本段放在前面
LD_BOOT_FLAGS= -m elf_i386 -nostdlib -N -e start -Ttext 0x7C00 

LD_KERNEL_FLAGS= -nostdlib -m elf_i386  -T ./tool/kernel.lds

OBJ_FLAGS= -S -O binary  bin/bootblock.o  bin/bootblock.out

BOOTNAME=bootblock.o

all : mkdir_file $(BC_OBJECTS) $(C_OBJECTS) $(BS_OBJECTS) $(S_OBJECTS)   ld_boot ld_kernel make_tool  obj dd

mkdir_file:
	$(MK_BOOT_FILE)
.c.o:
	@echo $<...
	$(CC) $(CC_FLAGE)  $< -o $@
.S.o:
	@echo $<...
	$(CC) $(CC_FLAGE)  $< -o $@
ld_boot:
	$(LD)  $(LD_BOOT_FLAGS)  $(BS_OBJECTS) $(BC_OBJECTS) -o  ./bin/$(BOOTNAME)
ld_kernel:
	$(LD)  $(LD_KERNEL_FLAGS) $(C_OBJECTS) $(S_OBJECTS) -o ./bin/drock
make_tool:
	$(CC) $(C_SING) -o ./tool/sign
obj:
	$(OBJ) $(OBJ_FLAGS)
	./tool/sign  bin/bootblock.out bin/bootblock
dd:
	dd if=/dev/zero of=./bin/drock.img count=1000
	dd if=./bin/bootblock of=./bin/drock.img conv=notrunc
	dd if=./bin/drock  of=./bin/drock.img seek=1 conv=notrunc
qemu:
	$(QEMU) -parallel stdio -hda bin/drock.img
clean:
	rm -rf ./bin  $(BS_OBJECTS) $(BC_OBJECTS) $(C_OBJECTS)

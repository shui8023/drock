#
#  drock的Makefile文件
#

C_SOURCES=$(shell find  -name *.c)
C_OBJECTS=$(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES=$(shell find  -name *.S)
S_OBJECTS=$(patsubst %.S, %.o, $(S_SOURCES))


CC=gcc

AS=as

LD=ld

RM=rm

MKDIR=mkdir

QEMU=qemu-system-i386

OBJ=objcopy 

CC_FLAGE=-c  -nostdlib -fno-builtin -fno-stack-protector -gstabs+ -Wall -ggdb  -m32 

SS_FLAGE= 

LD_FLAGS=-m elf_i386 -nostdlib -N -e start -Ttext 0x7C00 

OBJ_FLAGS=-S -O binary  boot/bootblock.o  boot/bootblock.out

VPATH += ./boot

all : $(C_OBJECTS) $(S_OBJECTS) 

.c.o:
	@echo $<.....
	$(CC) $(CC_FLAGE)  $< -o $@
.S.o:
	$(CC) $(CC_FLAGE)  $< -o $@
LD1:
	$(LD) boot/bootasm.o boot/bootmain.o $(LD_FLAGS) -o boot/bootblock.o
OBJ:
	$(OBJ) $(OBJ_FLAGS)
	./boot/sign boot/bootblock.out boot/bootblock
DD:
	dd if=/dev/zero of=ucore.img count=1000
	dd if=boot/bootblock of=ucore.img conv=notrunc
qemu:
	$(QEMU) -parallel stdio -hda ucore.img

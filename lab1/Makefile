#
#  drock的Makefile文件
#
BC_OBJECTS=$(patsubst %.c, %.o, $(wildcard ./boot/*.c))
BS_OBJECTS=$(patsubst %.S, %.o, $(wildcard ./boot/*.S))

#除去了sign.c这个文件
C_SING=$(wildcard ./tool/*.c)
C_SOURCES=$(filter-out $(C_SING), $(shell find -name *.c))
S_SOURCES=$(shell find -name *.S)
#除去了./boot/bootmain.c这个文件的.o格式,链接脚本不一样
C_OBJECTS=$(patsubst %.c, %.o, $(filter-out ./boot/bootmain.c,$(C_SOURCES)))

S_OBJECTS=$(patsubst %.S, %.o, $(filter-out ./boot/boot.S,$(S_SOURCES)))

T_SOURCES=$(filter ./tool/*.c, $(wildcard *.c))

MK_BOOT_FILE=$(shell if [ ! -d  "./bin/" ];                 \
			then mkdir "./bin";  fi)  	

CC=gcc

AS=as

LD=ld

RM=rm

V := @
QEMU = qemu-system-i386

OBJ=objcopy 
KINCLUDE += kern/debug/ \
	    kern/driver/  \
	    kern/trap/    \
	    kern/mm/ 	

C_FLAGS += $(addprefix -I , $(KINCLUDE))	 
CC_FLAGE= -c -ffreestanding  -nostdinc  -fno-builtin -fno-stack-protector -gstabs+ -Wall -ggdb  -m32 $(C_FLAGS) -I libs
BOOT_FLAGE= -c -ffreestanding  -nostdinc  -fno-builtin -fno-stack-protector -gstabs+ -Wall -ggdb  -m32 -I ./libs -O2

#
#必须把第一个boot.S的文本段放在前面
LD_BOOT_FLAGS= -m elf_i386  -N -e start -Ttext 0x7C00 

LD_KERNEL_FLAGS=   -m elf_i386  -T ./tool/kernel.lds

OBJ_FLAGS= -S -O binary  bin/bootblock.o  bin/bootblock.out

BOOTNAME=bootblock.o

all : mkdir_file  $(C_OBJECTS)  $(S_OBJECTS)  bootmain boot_s ld_boot ld_kernel make_tool  obj dd

mkdir_file:
	$(MK_BOOT_FILE)
.c.o:
	@echo + cc  $<...
	$(V)$(CC) $(CC_FLAGE)  $< -o $@
.S.o:
	@echo + cc $<...
	$(V)$(CC) $(CC_FLAGE)  $< -o $@
bootmain:
	@echo + cc bootmain.c...
	$(V)$(CC) ./boot/bootmain.c $(BOOT_FLAGE) -o ./boot/bootmain.o
boot_s:
	@echo + cc boot/boot.S...
	$(V)$(CC) ./boot/boot.S $(BOOT_FLAGE) -o ./boot/boot.o
ld_boot:
	@echo + ld bootblock...
	$(V)$(LD)  $(LD_BOOT_FLAGS)  $(BS_OBJECTS) $(BC_OBJECTS) -o  ./bin/$(BOOTNAME) 
ld_kernel:
	@echo + ld kernel...
	$(V)$(LD)  $(LD_KERNEL_FLAGS) $(C_OBJECTS) $(S_OBJECTS) -o ./bin/drock  -e start
make_tool:
	$(V)$(CC) $(C_SING) -o ./tool/sign 
obj:
	$(V)$(OBJ) $(OBJ_FLAGS)
	./tool/sign  bin/bootblock.out bin/bootblock
dd:
	$(V)dd if=/dev/zero of=./bin/drock.img count=10000
	$(V)dd if=./bin/bootblock of=./bin/drock.img conv=notrunc
	$(V)dd if=./bin/drock  of=./bin/drock.img seek=1 conv=notrunc

.PHONY: qemu debug clean
qemu:
	$(V)$(QEMU) -parallel  stdio -hda bin/drock.img -serial null
debug:
	$(QEMU) -parallel stdio -hda bin/drock.img -S -s &
#	cgdb -x ./tool/gdbinit

clean:
	@echo rm -rf obj bin
	$(V)rm -rf ./bin  $(BS_OBJECTS) $(BC_OBJECTS) $(C_OBJECTS) $(S_OBJECTS)

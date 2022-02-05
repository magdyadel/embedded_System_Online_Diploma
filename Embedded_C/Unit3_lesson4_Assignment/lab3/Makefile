#Copy Right : Magdy

CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -mcpu=cortex-m4 -g
INCS=-I
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_name=unit3_lab4_cortexM4

all:$(Project_name).bin
	@echo "==============Bild is Done=============="
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe $(INCS) $(CFLAGS) -c $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm -rf *.o *~
	@echo "Everything clean"
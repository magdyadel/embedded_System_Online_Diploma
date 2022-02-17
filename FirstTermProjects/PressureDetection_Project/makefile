#Copy Right : Magdy

# %.x all files end with .x
# $@ replace by name of target
# $< replace by first prerequisite
# $^ replace by all prerequisites


CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -gdwarf-2

SRCDIR = src
OBJDIR = obj
INCDIR = include
BINDIR = bin

INCS=-I $(INCDIR)
LIBS=
SRC=$(wildcard $(SRCDIR)/*.c)
As=$(wildcard *.s)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
AsOBJ=$(As:.s=.o)

Project_name=pressure_detection
P_BIN_DIR = $(BINDIR)/$(Project)

all:$(P_BIN_DIR)/Project_name.bin $(P_BIN_DIR)/Project_name.hex
	@echo "==============Bild is Done=============="
%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC)gcc.exe $(INCS) $(CFLAGS) -c $< -o $@

$(P_BIN_DIR)/Project_name.elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linkerscript.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=$(BINDIR)/map_file.map
	cp $(P_BIN_DIR)/Project_name.elf $(P_BIN_DIR)/Project_name.axf

$(P_BIN_DIR)/Project_name.bin: $(P_BIN_DIR)/Project_name.elf
	$(CC)objcopy.exe -O binary $< $@
	@echo "========= Binary Out Done ========="
	
$(P_BIN_DIR)/Project_name.hex: $(P_BIN_DIR)/Project_name.elf
	$(CC)objcopy.exe -O ihex $< $@
	@echo "========= Hex Out Done ========="

clean_all:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*.elf $(BINDIR)/*.bin $(BINDIR)/*.map $(BINDIR)/*.hex $(BINDIR)/*.axf
	@echo "========= Cleaned Everything ========="
clean:
	rm -rf $(BINDIR)/*.elf $(BINDIR)/*.bin
	@echo "========= Cleaned .elf and .bin ========="
/* linker_script CortexM3
Eng.Magdy
*/

MEMORY
{
flash(RX) : ORIGIN = 0x08000000, LENGTH = 128k
sram(RWX) : ORIGIN = 0x20000000, LENGTH = 20k

}

SECTIONS
{
	.text : {
			*(.vectors*)
			*(.text*)
			*(.rodata)
			_E_text = . ;
	}> flash
	
	.data : {
			_S_DATA = . ;
			*(.data)
			. = ALIGN(4) ;		/* to make word aligned after data section */
			_E_DATA = . ;
	}>sram AT> flash 			/* virtual addresses exists in RAM but at loading time burn in FLASH */ 
	
	.bss : {
			_S_bss = . ;
			*(.bss)
			_E_bss = . ;
			. = ALIGN(4) ;
			. = . + 1000 ;
			_stack_top = . ;
	}> sram
}
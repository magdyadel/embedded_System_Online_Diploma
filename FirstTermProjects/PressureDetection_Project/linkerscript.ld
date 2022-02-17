/* linker_script
Eng.Magdy Adel
*/

MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128k
SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		*(.rodata)
		_E_text = . ; 		/* End of .text section */
	}> FLASH

	.data : 
	{
		_S_DATA = . ;		/* Start of .data section */
		*(.data)
		. = ALIGN(4) ;		/* to make word aligned after data section */
		_E_DATA = . ;		/* End of .data section */
	}>SRAM AT> FLASH 			/* virtual addresses exists in RAM but at loading time burn in FLASH */ 
	
	.bss :
	{
		_S_bss = . ;		/* Start of .bss section */
		*(.bss*)
		_E_bss = . ;		/* End of .bss section */
	}> SRAM
}

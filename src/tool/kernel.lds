ENTRY(start)

SECTIONS {
	. = 0x100000;
	
	.text : {
		*(.text)
		. = ALIGN(4096); 
	}

	PROVIDE(etext = .);
	.rodata : {
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4096);
	}


	.stab : {
		*(.stab)
		. = ALIGN(4096); 
	}

	.stabstr : {
		*(.stabstr)
		. = ALIGN(4096); 
	}
	
	.data : {
		*(.data)
		. = ALIGN(4096); 
	}

	PROVIDE(edata = .);
	.bss : {
		*(.bss)
		. = ALIGN(4096); 
	}

	PROVIDE(end = .);
}

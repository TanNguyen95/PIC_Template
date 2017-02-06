; Configuration register settings
; Microchip p16f690
 
;(See complete list and comments at the bottom of device p16f690.inc file)

	__CONFIG _INTOSC & _WDT_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _BOR_OFF & _IESO_OFF & _FCMEN_OFF

;_INTOSC			Use internal oscillator with no clock out (RA4 and RA5 pins function as I/O)
;_WDT_OFF			Watch Dog Timer Off
;_PWRTE_OFF			Power-up Timer Off
;_MCLRE_OFF			MCLR pin function is digital input, MCLR internally tied to VDD
;_CP_OFF			Program memory code protection is disabled
;_BOR_OFF			Brown-out reset Off
;_IESO_OFF			Internal-External Oscilator Switchover mode is disabled
;_FCMEN_OFF			Fail-Safe Clock Monitor is disabled (switches to internal osc if ext fails)

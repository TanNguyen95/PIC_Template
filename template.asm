;Notes:
;Read Microchip's Assembler/Linker/Librarian User's Guide, Chapter 1
; for source code instructions (Section 1.7. page 24)

;Place only labels in column 1

;----------------------------------------------------------
;----------------------------------------------------------
	TITLE Template
;----------------------------------------------------------
;----------------------------------------------------------

#DEFINE _version 1.00
;
; Update History:
;
;
; Application Description/Comments
; This is a template with a test/demo of pulsing an output port.
;
; Author
; David Martin
; Date:
;
; Hardware Notes:
;   PIC16F690 Using 4 MHz Internal Clock


;----------------------------------------------------------

;----------------------------------------------------------


; Set the default (undeclared) radix as decimal. 
	LIST R=DEC 

; Device Specification
#INCLUDE p16f690.inc		;Include device header file
#INCLUDE p16f690-CONF.inc	;Include device configuration settings.

;------------------------------------------------------
;DEFINE VARIABLES / Register Declarations

;Use movwf to store to a reg. 
;Use movf to retrieve from a reg or movlw literal

#INCLUDE registers.inc

;------------------------------------------------------
;------------------------------------------------------
;DEFINE LITERALS 
;(Assembler substitutions: use movlw to retrieve its defined value at assembly time)

;#define <name> <value> ; comment
#DEFINE LED_1 PORTC,1

;<name> EQU <value>	; comment
TIME_2ms_INT	equ	248d
 
;------------------------------------------------------
;------------------------------------------------------
;MACRO DEFINITIONS

#INCLUDE macros.inc

;------------------------------------------------------
;------------------------------------------------------
 PAGE ;Inserts a page eject into the listing file.

;**********************************************************************
;RESET_VECTOR    
 	org 0h       	; processor reset vector memory address
	goto    start	; go to beginning of the program

;**********************************************************************
;INT_VECTOR
	org 04H       		; start of interrupt vector memory address

#INCLUDE interrupts.inc	;Interrupt Service Routine


;**********************************************************************
start:

;**********************************************************************
; GENERAL CONFIGURATION SETINGS

; Module Initialization

#INCLUDE configuration-INIT.inc

;#INCLUDE timer0-INIT.inc	
;#INCLUDE comp2-INIT.inc	
;#INCLUDE MODULE3-Init.inc	
;#INCLUDE MODULE4-Init.inc	
;#INCLUDE MODULE5-Init.inc	

;*************************************************************************************************
;*************************************************************************************************
;Uncomment to Enable all Unmasked Interrupts
	
;	banksel INTCON
;	bsf	INTCON, PEIE	;enable all unmasked peripheral interrupts
;	bsf 	INTCON, GIE	;Enable Interrupts

;*************************************************************************************************
;*************************************************************************************************
;MAIN PROGRAM


main:

	BANK1
  	bcf       TRISC,0             ; make IO Pin C.0 an output
  	bcf       TRISC,1             ; make IO Pin C.1 an output
  	BANK0
MainLoop:
	bsf     PORTC,0         ; turn on port C/0
	bsf	LED_1		;turn on port C/1
	DELAY
	DELAY
	bcf       PORTC,0             ; Turn off port C/0
	bcf       LED_1             ; Turn off port C/1
	DELAY
	DELAY
	goto      MainLoop            ; Do it again...

;**********************************************************************
;**********************************************************************
;**********************************************************************

;**********************************************************************
; SUBROUTINES
;**********************************************************************

;Place subroutines here or in files included here.
#INCLUDE template-SUB.inc	;Place subroutines in this file.



;**********************************************************************
;**********************************************************************


	END

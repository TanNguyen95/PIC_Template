;======================
; File INTERRUPTS.inc
;======================

; Interrupt Service Routines for PIC 16F690

; To use these file, insert instruction "#include interrupts.inc"
; right after "org 0x04"

;===================================================================

; INTERRUPT Handling Notes

; 0- If the global Int enable bit GIE is set, 
; any unmasked interrupts will cause the PC to jump to address 0004h
; and execute all code below until the return instruction RETFIE.
; retfie will re-enable GIE and restore address before interrupt into PC.

; 1- When an interrupt is serviced the GIE is automatically cleared to disable any further interrupts.

; GIE is also cleared on Reset and needs to be set at the begining of the code.

; The return address is pushed onto the stack.

; RETFIE will exit the service routine and set the GIE bit, which re-enables unmasked interrupts.


; 2- The source(s) of the interrupt can be determined by polling the interrupt flag bits of the INTCON register.

; 3- Individual interrupt flag bits are set,regardless of the status of their
; corresponding mask bit or the GIE bit.

; 4- The interrupt flag bit(s) must be cleared in software before RETFIE or before
; re-enabling interrupts to avoid multiple interrupt requests for unmasked interrupts.

; 5- When an instruction that clears the GIE bit is executed, any interrupts that were
; pending for execution in the next cycle are ignored. 

; 6- The unmasked interrupts, which were ignored, are still pending to be serviced
; when the GIE bit is set again by the interrupt return instruction RETFIE.


;********************************************************
;********************************************************

	; Save registers before servicing interrupt
	;these need to be the first three instructions:
	movwf	W_Temp			; Save W register into W_Temp
	movf	STATUS,W		; Retrieve STATUS register data into W
	movwf	STATUS_Temp		; Save STATUS register to STATUS_Temp
	
	;add any other registers that need saving (used by both ISR and main program)
	movf	Delay1, W		; Retrieve Delay1 register data into W
	movwf	Delay1_Temp		; Save Delay1 register to Delay1_Temp
	

	; Find out what intitiated the interrupt

;---------------------------------------------------------------------
	;COMMENT OUT NEXT INSTRUCTION TO ENABLE INTERRUPT SERVICING
	goto	ExitISR
;---------------------------------------------------------------------

	;TIMER 0 (used to time)
	btfsc	INTCON,T0IF		; Timer0 Interrupt bit INTCON<2>.
	goto 	ServiceTimer0	; note: clear T0IF flag before RETFIE
;---------------------------------------------------------------------

	;COMPARATOR 2 (used to stop the counting of timer1 when a port reaches a pre-defined voltage )
	banksel	PIR2		;bank 0
	btfsc	PIR2, C2IF	;check if comp 2 interrupt flag is set.
	goto 	ServiceComp2	; note: clear C2IF flag before RETFIE

;---------------------------------------------------------------------

	; Put here additional code to monitor if other interrupts being triggered.

;---------------------------------------------------------------------

	goto	ExitISR		;Nevermind. Interrupt not caused by currently monitored events.

;============================================================
; TIMER 0
;============================================================

ServiceTimer0:
	;#INCLUDE timer0-INT.inc
	goto ExitISR

;============================================================
;COMPARATOR 2
;============================================================

ServiceComp2:
	;#INCLUDE comp2-INT.inc
	goto ExitISR

;============================================================
; EXIT ISR
;============================================================

ExitISR:

	;restore here any registers used by ISR but also needed by main code
	movf	Delay1_Temp, W	; Retrieve Delay1_Temp register data into W
	movwf	Delay1			; Restore Delay1
	
	;these 4 instructions need to be the very last ones before the retfie and in that order
	movf	STATUS_Temp,W	; Restore STATUS register
	movwf	STATUS
	swapf	W_Temp,F		;Restore working register W without afecting flags
	swapf	W_Temp,W		;movf afects zero flag. sapf does not afect flags.

	;Return from interrupt service routine will autoset GIE to re-enable unmasked interrupts
	retfie		


;============================================================

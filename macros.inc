;------------------------------------------------------
DELAY macro ;two-tenth of a second
	
	clrf	Delay1
	clrf	Delay2
;Loop:
	decfsz	Delay1,f	; Waste time.  
	goto	$-1		; The Inner loop takes 3 instructions per loop * 256 loops = 768 instructions
	decfsz	Delay2,f	; The outer loop takes and additional 3 instructions per lap * 256 loops
	goto	$-3 		; (768+3) * 256 = 197376 instructions / 1M instructions per second = 0.197 sec.
	
	endm

;------------------------------------------------------
; This macro is used to switch to the correct register bank.
; Not sure what is advantage of suing this instead of banksel

BANK0 macro
	bcf	STATUS, RP0
	bcf	STATUS, RP1
	endm

BANK1 macro
	bsf	STATUS, RP0
	bcf	STATUS, RP1
	endm

BANK2 macro
	bcf	STATUS, RP0
	bsf	STATUS, RP1
	endm

BANK3 macro
	bsf	STATUS, RP0
	bsf	STATUS, RP1
	endm
;------------------------------------------------------

;------------------------------------------------------
;------------------------------------------------------
;registers.inc
;------------------------------------------------------
;------------------------------------------------------
; Variable Register Declarations
;DEFINE VARIABLES (use movwf to store to a reg. Use movf to retrieve from a reg or movlw literal
;------------------------------------------------------

  ; Shadow/Unbanked Variables (Max 16 bytes -- 16 variables): Data memory for interrupt routines. No Need for "banksel" bank selection.
  CBLOCK 070h
    ; General
    W_Temp          ; variable used for context saving (W register) for interrupts
    STATUS_Temp     ; variable used for context saving (STATUS register) for interrupts
    Delay1, Delay2  ;used for time delay
    Delay1_Temp     ;temp variable during interrupt stack swap
    temp            ;used for temporary storage
  ENDC


  ; Bank 0 Variables (80 bytes)- Use "banksel <variable_name>" before addressing these registers
  CBLOCK 020h
    ;List variables here
  ENDC

  ; Bank 1 Variables (80 bytes)- Use "banksel variable_name" before addressing these registers
  CBLOCK 0A0h
    ;List variables here
  ENDC

  ; Bank 2 Variables (80 bytes)- Use "banksel variable_name" before addressing these registers
  CBLOCK 120h
    ;List variables here
  ENDC


;------------------------------------------------------
;------------------------------------------------------
;------------------------------------------------------
;------------------------------------------------------

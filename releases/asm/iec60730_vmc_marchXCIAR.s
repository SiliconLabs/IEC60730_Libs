;***************************************************************************//**
; @file
; @brief Variable memory March-X test
;*******************************************************************************
; # License
; <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
;*******************************************************************************
;
; The licensor of this software is Silicon Laboratories Inc. Your use of this
; software is governed by the terms of Silicon Labs Master Software License
; Agreement (MSLA) available at
; www.silabs.com/about-us/legal/master-software-license-agreement. This
; software is distributed to you in Source Code format and is governed by the
; sections of the MSLA applicable to Source Code.
;
;******************************************************************************/
	SECTION text:CONST(2)

STANDARD_RAM_ORDER:
  DCD  -4
  DCD   0
  DCD   4
  DCD   8
  DCD   12
  DCD   16
  DCD   20
  DCD   24
  DCD   28

	SECTION text:CODE(2)

  EXPORT Vmc_MarchXC_Step

;***************************************************************************//**
; public IEC60730 March X
;
; Run march X algorithm on RAM from start address to stop address
; With assembly code, please refer to book:
; [1] The Definitive Guide to ARM Cortex-M3 and Cortex M-4 Processors
;
; @param   r0 - Start address of RAM to check
;          r1 - First address of backup buffer
;          r2 - Background pattern
; @return  1 if passed, 0 if failed
;******************************************************************************/

Vmc_MarchXC_Step:
  PUSH  {r3-r7, lr}

  ; Setup inverted background pattern (r3)
  MOVS  r3, r2
  RSBS  r3, r3, #0
  SUBS  r3, r3, #1

  LDR   r4, =STANDARD_RAM_ORDER

  ; Backup buffer to be tested?
  MOVS  r5, r0
  CMP   r5, r1
  BEQ   IEC60730_MARCHCX_STEP_BUFF1

  ; Test of the RAM slice
IEC60730_MARCHCX_STEP_SAVE:
  MOVS  r5, #0
IEC60730_MARCHCX_STEP_SAVE_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  ADD   r5, r5, #4
  STR   r7, [r1, r5]
  CMP   r5, #20
  BLE   IEC60730_MARCHCX_STEP_SAVE_LOOP

  ; Step 1
IEC60730_MARCHCX_STEP_STEP1:
  MOVS  r5, #0
IEC60730_MARCHCX_STEP_STEP1_LOOP:
  LDR   r6, [r4, r5]
  STR   r2, [r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #20
  BLE   IEC60730_MARCHCX_STEP_STEP1_LOOP

  ; Step 2
IEC60730_MARCHCX_STEP_STEP2:
  MOVS  r5, #0
IEC60730_MARCHCX_STEP_STEP2_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r3, [r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #20
  BLE   IEC60730_MARCHCX_STEP_STEP2_LOOP

#ifndef USE_MARCHX
  ; Step 3 (not used at March-X test)
IEC60730_MARCHCX_STEP_STEP3:
  MOVS  r5, #0
IEC60730_MARCHCX_STEP_STEP3_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r3
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r2,[r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #20
  BLE   IEC60730_MARCHCX_STEP_STEP3_LOOP

  ; Step 4 (not used at March-X test)
IEC60730_MARCHCX_STEP_STEP4:
  MOVS  r5, #24
IEC60730_MARCHCX_STEP_STEP4_LOOP:
  SUBS  r5, r5, #4
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r3, [r0, r6]
  CMP   r5, #0
  BHI   IEC60730_MARCHCX_STEP_STEP4_LOOP
#endif ; March-X

  ; Step 5
IEC60730_MARCHCX_STEP_STEP5:
  MOVS  r5, #24
IEC60730_MARCHCX_STEP_STEP5_LOOP:
  SUBS  r5, r5, #4
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r3
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r2, [r0, r6]
  CMP   r5, #0
  BHI   IEC60730_MARCHCX_STEP_STEP5_LOOP

  ; Step 6
IEC60730_MARCHCX_STEP_STEP6:
  MOVS  r5, #0
IEC60730_MARCHCX_STEP_STEP6_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  ADD   r5, r5, #4
  CMP   r5, #20
  BLE   IEC60730_MARCHCX_STEP_STEP6_LOOP

IEC60730_MARCHCX_STEP_RESTORE:
  MOVS  r5, #24
IEC60730_MARCHCX_STEP_RESTORE_LOOP:
  LDR   r7, [r1, r5]
  SUB   r5, r5, #4
  LDR   r6, [r4, r5]
  STR   r7, [r0, r6]
  CMP   r5, #0
  BHI   IEC60730_MARCHCX_STEP_RESTORE_LOOP

  B     IEC60730_MARCHCX_STEP_MARCH_RET

  ; Step 1
IEC60730_MARCHCX_STEP_BUFF1:
  MOVS  r5, #4
IEC60730_MARCHCX_STEP_BUFF1_LOOP:
  LDR   r6, [r4, r5]
  STR   r2, [r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #32
  BLE   IEC60730_MARCHCX_STEP_BUFF1_LOOP

  ; Step 2
IEC60730_MARCHCX_STEP_BUFF2:
  MOVS  r5, #4
IEC60730_MARCHCX_STEP_BUFF2_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r3, [r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #32
  BLE   IEC60730_MARCHCX_STEP_BUFF2_LOOP

#ifndef USE_MARCHX
  ; Step 3 (not used at March-X test)
IEC60730_MARCHCX_STEP_BUFF3:
  MOVS  r5, #4
IEC60730_MARCHCX_STEP_BUFF3_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r3
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r2, [r0, r6]
  ADD   r5, r5, #4
  CMP   r5, #32
  BLE   IEC60730_MARCHCX_STEP_BUFF3_LOOP

  ; Step 4 (not used at March-X test)
IEC60730_MARCHCX_STEP_BUFF4:
  MOVS  r5, #36
IEC60730_MARCHCX_STEP_BUFF4_LOOP:
  SUBS  r5, r5, #4
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r3, [r0, r6]
  CMP   r5, #4
  BHI   IEC60730_MARCHCX_STEP_BUFF4_LOOP
#endif ; March-X

  ; Step 5
IEC60730_MARCHCX_STEP_BUFF5:
  MOVS  r5, #36
IEC60730_MARCHCX_STEP_BUFF5_LOOP:
  SUBS  r5, r5, #4
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r3
  BNE   IEC60730_MARCHCX_STEP_ERR
  STR   r2, [r0, r6]
  CMP   r5, #4
  BHI   IEC60730_MARCHCX_STEP_BUFF5_LOOP

  ; Step 6
IEC60730_MARCHCX_STEP_BUFF6:
  MOVS  r5, #4
IEC60730_MARCHCX_STEP_BUFF6_LOOP:
  LDR   r6, [r4, r5]
  LDR   r7, [r0, r6]
  CMP   r7, r2
  BNE   IEC60730_MARCHCX_STEP_ERR
  ADD   r5, r5, #4
  CMP   r5, #32
  BLE   IEC60730_MARCHCX_STEP_BUFF6_LOOP

IEC60730_MARCHCX_STEP_MARCH_RET:
  MOVS  r0, #1
  B     IEC60730_MARCHCX_STEP_RET

IEC60730_MARCHCX_STEP_ERR:
  MOVS  r0, #0

IEC60730_MARCHCX_STEP_RET:
  POP   {r3-r7, pc}

  END

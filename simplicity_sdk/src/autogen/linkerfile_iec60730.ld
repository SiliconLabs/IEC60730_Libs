/***************************************************************************//**
 * @file     linkerfile_lib.ld
 * @brief    GNU Linker Script for Cortex-M based device
 * @version  V2.2.0
 * @date     16. December 2020
 * Linker script for Silicon Labs devices
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories, Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
 MEMORY
 {
   FLASH      (rx)  : ORIGIN = 0x8000000, LENGTH = 160K
   RAM        (rwx) : ORIGIN = 0x20000080, LENGTH = 16K - 0x80
   CLASSBRAM (rw) : ORIGIN = 0x20000000, LENGTH = 0x80
 }

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __StackSeal      (only if ARMv8-M stack sealing is used)
 */

ENTRY(Reset_Handler)

SECTIONS
{

  .text :
  {
    KEEP(*(.vectors))
    *(.text*)

    KEEP(*(.init))
    KEEP(*(.fini))

    /* .ctors */
    *crtbegin.o(.ctors)
    *crtbegin?.o(.ctors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
    *(SORT(.ctors.*))
    *(.ctors)

    /* .dtors */
    *crtbegin.o(.dtors)
    *crtbegin?.o(.dtors)
    *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
    *(SORT(.dtors.*))
    *(.dtors)

    *(.rodata*)
    KEEP(*(.eh_frame*))
  } > FLASH
  /* Check sum */
    .crc :
  {
    . = ALIGN(64);
    PROVIDE (check_sum = . );
    LONG(0xAA55A55A)
  } > FLASH
  /*
   * SG veneers:
   * All SG veneers are placed in the special output section .gnu.sgstubs. Its start address
   * must be set, either with the command line option ‘--section-start’ or in a linker script,
   * to indicate where to place these veneers in memory.
   */
/*
  .gnu.sgstubs : ALIGN(32)
  {
    . = ALIGN(32);
    linker_sg_begin = .;
    KEEP(*(.gnu.sgstubs*))
    . = ALIGN(32);
  } > FLASH
  linker_sg_end = linker_sg_begin + SIZEOF(.gnu.sgstubs);
*/
  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > FLASH
  __exidx_end = .;

    .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;

    LONG (__etext)
    LONG (__data_start__)
    LONG ((__data_end__ - __data_start__) / 4)

    /* Add each additional data section here */
/*
    LONG (__etext2)
    LONG (__data2_start__)
    LONG ((__data2_end__ - __data2_start__) / 4)
*/

    __copy_table_end__ = .;
  } > FLASH

     .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    /* Add each additional bss section here */
/*
    LONG (__bss2_start__)
    LONG ((__bss2_end__ - __bss2_start__) / 4)
*/
    __zero_table_end__ = .;
  } > FLASH

   __etext = .;

  /* Start placing output sections which are loaded into RAM */
  . = ORIGIN(RAM);
  /* ARMv8-M stack sealing:
     to use ARMv8-M stack sealing uncomment '.stackseal' section
   */
  .stackseal (COPY):
  {
    __StackSeal = .;
    . = . + 8;
    . = ALIGN(8);
  } > RAM

  .noinit . (NOLOAD):
  {
    *(.noinit*);
  } > RAM

  .data . : AT (__etext)
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(vtable)
    *(SORT_BY_ALIGNMENT(.data*))
    . = ALIGN(4);

    PROVIDE(__ram_func_section_start = .);
    *(.ram)
    PROVIDE(__ram_func_section_end = .);

    . = ALIGN(4);
    /* preinit data */
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    . = ALIGN(4);
    /* init data */
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    . = ALIGN(4);
    /* finit data */
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN (__fini_array_end = .);
    KEEP(*(.jcr*))
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;

  } > RAM

 .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM AT > RAM
  .ram_no_clear (NOLOAD) :
  {
    . = ALIGN(4);
    *(.ram_no_clear*)
    . = ALIGN(4);
  } > RAM

  .stack_check (NOLOAD):
  {
    . = ALIGN(8);
    PROVIDE (stack_check = . );
    *(.stack_bottom)
    *(.stack_bottom*)
    . = ALIGN(8);
  } > RAM

/* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy (COPY):
  {
    KEEP(*(.stack*))
 /* KEEP(*(.stackseal*))*/
  } > RAM

/* User class B RAM region */
  .user_classb (NOLOAD) :
  {
    . = ALIGN(4);
    *(.rt_buf)
    *(.rt_buf*)

    . = ALIGN(4);
    /* overlap data */
    KEEP(*(.overlap*));

    . = ALIGN(4);
    PROVIDE (classb_start = . );
    *(.classb_ram)
    *(.classb_ram*)
    . = ALIGN(4);
    PROVIDE (classb_end = . );
  } > CLASSBRAM

/* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(RAM) + LENGTH(RAM);
  /* __StackLimit = __StackTop - SIZEOF(.stack_dummy); */
  __StackLimit = __StackTop - SIZEOF(.stack_dummy) - SIZEOF(.stack_check);
  PROVIDE(__stack = __StackTop);

/* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

  PROVIDE(flash_start = ORIGIN(FLASH));
  PROVIDE(ram_start = ORIGIN(RAM));
  PROVIDE(class_b_limit = ORIGIN(CLASSBRAM) + LENGTH(CLASSBRAM));

  /* Check if FLASH usage exceeds FLASH size */
  /*ASSERT( LENGTH(FLASH) >= (__etext + SIZEOF(.data)), "FLASH memory overflowed !")*/

  __ramfuncs_start__ = .;

  __vma_ramfuncs_start__ = .;
  __lma_ramfuncs_start__ = __etext + SIZEOF(.data);

  __text_application_ram_offset__ = . - __vma_ramfuncs_start__;
  text_application_ram . : AT(__lma_ramfuncs_start__ + __text_application_ram_offset__)
  {
    . = ALIGN(4);
    __text_application_ram_start__ = .;
    *(text_application_ram)
    . = ALIGN(4);
    __text_application_ram_end__ = .;
  } > RAM

  . = ALIGN(4);
  __vma_ramfuncs_end__ = .;
  __lma_ramfuncs_end__ = __lma_ramfuncs_start__ + __text_application_ram_offset__ + SIZEOF(text_application_ram);

  __ramfuncs_end__ = .;

   .heap (COPY):
  {
    __HeapBase = .;
    __end__ = .;
    end = __end__;
    _end = __end__;
    KEEP(*(.heap*))
    __HeapLimit = .;
  } > RAM

  __heap_size = __HeapLimit - __HeapBase;
  __ram_end__ = 0x20000000 + 0x40000;
  __main_flash_end__ = 0x8000000 + 0x17e000;

   /* This is where we handle flash storage blocks. We use dummy sections for finding the configured
   * block sizes and then "place" them at the end of flash when the size is known. */
  .internal_storage (DSECT) : {
    KEEP(*(.internal_storage*))
  } > FLASH

  linker_storage_end = __main_flash_end__;

  linker_storage_begin = linker_storage_end - SIZEOF(.internal_storage);
  linker_storage_size = SIZEOF(.internal_storage);
  ASSERT((linker_storage_begin >= (__etext + SIZEOF(.data))), "FLASH memory overflowed !")


}

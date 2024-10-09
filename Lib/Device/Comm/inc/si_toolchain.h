/***************************************************************************//**
 * @file
 * @brief Compiler abstraction
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef __SI_TOOLCHAIN_H__
#define __SI_TOOLCHAIN_H__

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************//**
 *
 * @addtogroup toolchain_group Toolchain Abstraction
 *
 * @brief Macros for toolchain abstraction.
 *
 * # Introduction #
 *
 * This header file contains macros that are used to provide an abstraction
 * for toolchain use in source code.  The EFR32 compiler requires C-language
 * extensions in order to fully use features of the EFR32 architecture.  All
 * compilers for EFR32 implement a set of extensions but use different names
 * and ways of implementing those extensions.  This header file provides
 * macros that are defined for each supported toolchain and can be used in
 * the source code.  This allows the source code to use EFR32 extensions and
 * remain independent of which toolchain is used for compilation.
 *
 * ## Variable and Pointer Declarations ##
 *
 * It is often useful to specify the memory area (or segment) of a variable,
 * pointer, or pointer target.  For example, you may wish to place all
 * variables in XDATA by default, but for variables used in time-sensitive
 * code you use DATA for efficient access.  In this case you declare the
 * XDATA variable in the normal C way, but declare the variables to be located
 * in the DATA segment using @ref SI_SEGMENT_VARIABLE.
 *
 * Pointers are more complicated because there are two memory spaces
 * associated with a pointer, the pointer target, and the pointer variable
 * itself.  When using default memory segment for the pointer location and
 * target, then no special macro is needed.  But if you wish to specify the
 * pointer variable location, or target memory segment, then you can use one
 * of the following macros to do this in a toolchain-independent way.
 *
 * |Pointer segment|Target segment|Macro                                   |
 * |---------------|--------------|----------------------------------------|
 * |default        |generic       |None                                    |
 * |default        |specific      |@ref SI_VARIABLE_SEGMENT_POINTER        |
 * |specific       |generic       |@ref SI_SEGMENT_POINTER                 |
 * |specific       |specific      |@ref SI_SEGMENT_VARIABLE_SEGMENT_POINTER|
 *
 * ## Prior Toolchain Abstraction Header File ##
 *
 * ## Supported Toolchains ##
 *
 * - GNU GCC
 * - IAR ICCARM
 *
 * @{
 *
 *****************************************************************************/

// Make sure there is a NULL defined if the toolchain does not provide it.
#ifndef NULL
#define NULL ((void *)0)
#endif

// -------------------------------
// GCC for ARM Cortex-M
// Provides support for code that can be compiled for 8 or 32-bit
//
#if defined (__GNUC__)

// these ignore any memory segment directives
#define SI_SEG_GENERIC
#define SI_SEG_DATA
// No clear at startup
#define SI_SEG_DATA_NO_CLEAR  __attribute__ ((section (".ram_no_clear")))
// No clear at startup and retained in power down mode
#define SI_SEG_DATA_RETAINED_NO_CLEAR  __attribute__ ((section (".ram_ret_no_clear")))
#define SI_SEG_IDATA
#define SI_SEG_XDATA
#define SI_SEG_PDATA
#define SI_SEG_BDATA
#define SI_SEG_CODE

// the following create function and variable names of the specified types
// but the EFR32-specific aspects (like memory segment) are ignored
#define SI_INTERRUPT(name, vector) void name (void)
#define SI_INTERRUPT_USING(name, vector, regnum) void name (void)
#define SI_INTERRUPT_PROTO(name, vector) void name (void)
#define SI_INTERRUPT_PROTO_USING(name, vector, regnum) void name (void)
#define SI_FUNCTION_USING(name, return_value, parameter, regnum)              \
             return_value name (parameter)
#define SI_FUNCTION_PROTO_USING(name, return_value, parameter, regnum)        \
             return_value name (parameter)
#define SI_SEGMENT_VARIABLE(name, vartype, memseg) vartype name memseg
#define SI_SEGMENT_CONST(name, vartype, memseg) const vartype name memseg
#define SI_VARIABLE_SEGMENT_POINTER(name, vartype, targseg)                  \
             vartype * name
#define SI_SEGMENT_VARIABLE_SEGMENT_POINTER(name, vartype, targseg, memseg)  \
             vartype * name
#define SI_SEGMENT_POINTER(name, vartype, memseg) vartype * name
#define SI_LOCATED_VARIABLE_NO_INIT(name, vartype, memseg, address)          \
             vartype name

// Generic pointer stuff is left out because if you are accessing
// generic pointer fields then it will need to be rewritten for 32-bit

// __NOP should be declared in cmsis header core_cmInstr.h
// extern void __NOP(void);
/// Macro to insert a no-operation (NOP) instruction.
#define NOP() __NOP()

// -------------------------------
// IAR for ARM Cortex-M
// Provides support for code that can be compiled for 8 or 32-bit
//
#elif defined (__ICCARM__)

// these ignore any memory segment directives
#define SI_SEG_GENERIC
#define SI_SEG_DATA
// No clear at startup
#define SI_SEG_DATA_NO_CLEAR  __attribute__ ((section (".ram_no_clear")))
// No clear at startup and retained in power down mode
#define SI_SEG_DATA_RETAINED_NO_CLEAR  __attribute__ ((section (".ram_ret_no_clear")))
#define SI_SEG_IDATA
#define SI_SEG_XDATA
#define SI_SEG_PDATA
#define SI_SEG_BDATA
#define SI_SEG_CODE

// the following create function and variable names of the specified types
// but the EFR32-specific aspects (like memory segment) are ignored
#define SI_INTERRUPT(name, vector) void name (void)
#define SI_INTERRUPT_USING(name, vector, regnum) void name (void)
#define SI_INTERRUPT_PROTO(name, vector) void name (void)
#define SI_INTERRUPT_PROTO_USING(name, vector, regnum) void name (void)
#define SI_FUNCTION_USING(name, return_value, parameter, regnum)              \
             return_value name (parameter)
#define SI_FUNCTION_PROTO_USING(name, return_value, parameter, regnum)        \
             return_value name (parameter)
#define SI_SEGMENT_VARIABLE(name, vartype, memseg) vartype name memseg
#define SI_SEGMENT_CONST(name, vartype, memseg) const vartype name memseg
#define SI_VARIABLE_SEGMENT_POINTER(name, vartype, targseg)                  \
             vartype * name
#define SI_SEGMENT_VARIABLE_SEGMENT_POINTER(name, vartype, targseg, memseg)  \
             vartype * name
#define SI_SEGMENT_POINTER(name, vartype, memseg) vartype * name
#define SI_LOCATED_VARIABLE_NO_INIT(name, vartype, memseg, address)          \
             vartype name

// Generic pointer stuff is left out because if you are accessing
// generic pointer fields then it will need to be rewritten for 32-bit

// __NOP should be declared in cmsis header core_cmInstr.h
// extern void __NOP(void);
/// Macro to insert a no-operation (NOP) instruction.
#define NOP() __NOP()

#else // unknown toolchain
#error Unrecognized toolchain in si_toolchain.h
#endif

/** @} */

#endif

/***************************************************************************/ /**
 * @file
 * @brief EFR32MG12P_AF_PORTS register and bit field definitions
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#if defined(__ICCARM__)
#pragma system_include /* Treat file as system include file. */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang system_header /* Treat file as system include file. */
#endif

/***************************************************************************/ /**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************/ /**
 * @addtogroup EFR32MG12P_Alternate_Function Alternate Function
 * @{
 * @defgroup EFR32MG12P_AF_Ports Alternate Function Ports
 * @{
 ******************************************************************************/

#define AF_CMU_CLK0_PORT(i)                                                    \
  ((i) == 0   ? 0                                                              \
   : (i) == 1 ? 1                                                              \
   : (i) == 2 ? 2                                                              \
   : (i) == 3 ? 2                                                              \
   : (i) == 4 ? 3                                                              \
   : (i) == 5 ? 3                                                              \
   : (i) == 6 ? 5                                                              \
   : (i) == 7 ? 5                                                              \
              : -1) /**< Port number for AF_CMU_CLK0 location number i */
#define AF_CMU_CLK1_PORT(i)                                                    \
  ((i) == 0   ? 0                                                              \
   : (i) == 1 ? 1                                                              \
   : (i) == 2 ? 2                                                              \
   : (i) == 3 ? 2                                                              \
   : (i) == 4 ? 3                                                              \
   : (i) == 5 ? 3                                                              \
   : (i) == 6 ? 5                                                              \
   : (i) == 7 ? 5                                                              \
              : -1) /**< Port number for AF_CMU_CLK1 location number i */
#define AF_CMU_CLKI0_PORT(i)                                                   \
  ((i) == 0   ? 1                                                              \
   : (i) == 1 ? 5                                                              \
   : (i) == 2 ? 2                                                              \
   : (i) == 3 ? 1                                                              \
   : (i) == 4 ? 0                                                              \
              : -1) /**< Port number for AF_CMU_CLKI0 location number i */
#define AF_PRS_CH0_PORT(i)                                                     \
  ((i) == 0    ? 5                                                             \
   : (i) == 1  ? 5                                                             \
   : (i) == 2  ? 5                                                             \
   : (i) == 3  ? 5                                                             \
   : (i) == 4  ? 5                                                             \
   : (i) == 5  ? 5                                                             \
   : (i) == 6  ? 5                                                             \
   : (i) == 7  ? 5                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
               : -1) /**< Port number for AF_PRS_CH0 location number i */
#define AF_PRS_CH1_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 5                                                              \
   : (i) == 2 ? 5                                                              \
   : (i) == 3 ? 5                                                              \
   : (i) == 4 ? 5                                                              \
   : (i) == 5 ? 5                                                              \
   : (i) == 6 ? 5                                                              \
   : (i) == 7 ? 5                                                              \
              : -1) /**< Port number for AF_PRS_CH1 location number i */
#define AF_PRS_CH2_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 5                                                              \
   : (i) == 2 ? 5                                                              \
   : (i) == 3 ? 5                                                              \
   : (i) == 4 ? 5                                                              \
   : (i) == 5 ? 5                                                              \
   : (i) == 6 ? 5                                                              \
   : (i) == 7 ? 5                                                              \
              : -1) /**< Port number for AF_PRS_CH2 location number i */
#define AF_PRS_CH3_PORT(i)                                                     \
  ((i) == 0    ? 5                                                             \
   : (i) == 1  ? 5                                                             \
   : (i) == 2  ? 5                                                             \
   : (i) == 3  ? 5                                                             \
   : (i) == 4  ? 5                                                             \
   : (i) == 5  ? 5                                                             \
   : (i) == 6  ? 5                                                             \
   : (i) == 7  ? 5                                                             \
   : (i) == 8  ? 3                                                             \
   : (i) == 9  ? 3                                                             \
   : (i) == 10 ? 3                                                             \
   : (i) == 11 ? 3                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
               : -1) /**< Port number for AF_PRS_CH3 location number i */
#define AF_PRS_CH4_PORT(i)                                                     \
  ((i) == 0   ? 3                                                              \
   : (i) == 1 ? 3                                                              \
   : (i) == 2 ? 3                                                              \
   : (i) == 3 ? 3                                                              \
   : (i) == 4 ? 3                                                              \
   : (i) == 5 ? 3                                                              \
   : (i) == 6 ? 3                                                              \
              : -1) /**< Port number for AF_PRS_CH4 location number i */
#define AF_PRS_CH5_PORT(i)                                                     \
  ((i) == 0   ? 3                                                              \
   : (i) == 1 ? 3                                                              \
   : (i) == 2 ? 3                                                              \
   : (i) == 3 ? 3                                                              \
   : (i) == 4 ? 3                                                              \
   : (i) == 5 ? 3                                                              \
   : (i) == 6 ? 3                                                              \
              : -1) /**< Port number for AF_PRS_CH5 location number i */
#define AF_PRS_CH6_PORT(i)                                                     \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 3                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
               : -1) /**< Port number for AF_PRS_CH6 location number i */
#define AF_PRS_CH7_PORT(i)                                                     \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 0                                                             \
               : -1) /**< Port number for AF_PRS_CH7 location number i */
#define AF_PRS_CH8_PORT(i)                                                     \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 0                                                             \
   : (i) == 10 ? 0                                                             \
               : -1) /**< Port number for AF_PRS_CH8 location number i */
#define AF_PRS_CH9_PORT(i)                                                     \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 0                                                             \
   : (i) == 9  ? 0                                                             \
   : (i) == 10 ? 0                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
               : -1) /**< Port number for AF_PRS_CH9 location number i */
#define AF_PRS_CH10_PORT(i)                                                    \
  ((i) == 0   ? 2                                                              \
   : (i) == 1 ? 2                                                              \
   : (i) == 2 ? 2                                                              \
   : (i) == 3 ? 2                                                              \
   : (i) == 4 ? 2                                                              \
   : (i) == 5 ? 2                                                              \
              : -1) /**< Port number for AF_PRS_CH10 location number i */
#define AF_PRS_CH11_PORT(i)                                                    \
  ((i) == 0   ? 2                                                              \
   : (i) == 1 ? 2                                                              \
   : (i) == 2 ? 2                                                              \
   : (i) == 3 ? 2                                                              \
   : (i) == 4 ? 2                                                              \
   : (i) == 5 ? 2                                                              \
              : -1) /**< Port number for AF_PRS_CH11 location number i */
#define AF_TIMER0_CC0_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_TIMER0_CC0 location number i */
#define AF_TIMER0_CC1_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER0_CC1 location number i */
#define AF_TIMER0_CC2_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER0_CC2 location number i */
#define AF_TIMER0_CC3_PORT(i)                                                  \
  (-1) /**< Port number for AF_TIMER0_CC3 location number i */
#define AF_TIMER0_CDTI0_PORT(i)                                                \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER0_CDTI0 location number i */
#define AF_TIMER0_CDTI1_PORT(i)                                                \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER0_CDTI1 location number i */
#define AF_TIMER0_CDTI2_PORT(i)                                                \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 0                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER0_CDTI2 location number i */
#define AF_TIMER0_CDTI3_PORT(i)                                                \
  (-1) /**< Port number for AF_TIMER0_CDTI3 location number i */
#define AF_TIMER1_CC0_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_TIMER1_CC0 location number i */
#define AF_TIMER1_CC1_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER1_CC1 location number i */
#define AF_TIMER1_CC2_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER1_CC2 location number i */
#define AF_TIMER1_CC3_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_TIMER1_CC3 location number i */
#define AF_TIMER1_CDTI0_PORT(i)                                                \
  (-1) /**< Port number for AF_TIMER1_CDTI0 location number i */
#define AF_TIMER1_CDTI1_PORT(i)                                                \
  (-1) /**< Port number for AF_TIMER1_CDTI1 location number i */
#define AF_TIMER1_CDTI2_PORT(i)                                                \
  (-1) /**< Port number for AF_TIMER1_CDTI2 location number i */
#define AF_TIMER1_CDTI3_PORT(i)                                                \
  (-1) /**< Port number for AF_TIMER1_CDTI3 location number i */
#define AF_WTIMER0_CC0_PORT(i)                                                 \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 0                                                             \
   : (i) == 7  ? 0                                                             \
   : (i) == 8  ? 0                                                             \
   : (i) == 9  ? 0                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 1                                                             \
   : (i) == 15 ? 1                                                             \
   : (i) == 16 ? 1                                                             \
   : (i) == 17 ? 1                                                             \
   : (i) == 18 ? 1                                                             \
   : (i) == 19 ? 1                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 2                                                             \
   : (i) == 24 ? 2                                                             \
   : (i) == 25 ? 2                                                             \
   : (i) == 26 ? 2                                                             \
   : (i) == 27 ? 2                                                             \
   : (i) == 28 ? 2                                                             \
   : (i) == 29 ? 2                                                             \
   : (i) == 30 ? 2                                                             \
   : (i) == 31 ? 2                                                             \
               : -1) /**< Port number for AF_WTIMER0_CC0 location number i */
#define AF_WTIMER0_CC1_PORT(i)                                                 \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 0                                                             \
   : (i) == 7  ? 0                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 1                                                             \
   : (i) == 15 ? 1                                                             \
   : (i) == 16 ? 1                                                             \
   : (i) == 17 ? 1                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 2                                                             \
   : (i) == 24 ? 2                                                             \
   : (i) == 25 ? 2                                                             \
   : (i) == 26 ? 2                                                             \
   : (i) == 27 ? 2                                                             \
   : (i) == 28 ? 2                                                             \
   : (i) == 29 ? 2                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_WTIMER0_CC1 location number i */
#define AF_WTIMER0_CC2_PORT(i)                                                 \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 1                                                             \
   : (i) == 15 ? 1                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 2                                                             \
   : (i) == 24 ? 2                                                             \
   : (i) == 25 ? 2                                                             \
   : (i) == 26 ? 2                                                             \
   : (i) == 27 ? 2                                                             \
   : (i) == 28 ? 3                                                             \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_WTIMER0_CC2 location number i */
#define AF_WTIMER0_CC3_PORT(i)                                                 \
  (-1) /**< Port number for AF_WTIMER0_CC3 location number i */
#define AF_WTIMER0_CDTI0_PORT(i)                                               \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 2                                                             \
   : (i) == 24 ? 3                                                             \
   : (i) == 25 ? 3                                                             \
   : (i) == 26 ? 3                                                             \
   : (i) == 27 ? 3                                                             \
   : (i) == 28 ? 3                                                             \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31                                                                 \
       ? 3                                                                     \
       : -1) /**< Port number for AF_WTIMER0_CDTI0 location number i */
#define AF_WTIMER0_CDTI1_PORT(i)                                               \
  ((i) == 0    ? 1                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 3                                                             \
   : (i) == 25 ? 3                                                             \
   : (i) == 26 ? 3                                                             \
   : (i) == 27 ? 3                                                             \
   : (i) == 28 ? 3                                                             \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31                                                                 \
       ? 5                                                                     \
       : -1) /**< Port number for AF_WTIMER0_CDTI1 location number i */
#define AF_WTIMER0_CDTI2_PORT(i)                                               \
  ((i) == 0    ? 1                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 3                                                             \
   : (i) == 25 ? 3                                                             \
   : (i) == 26 ? 3                                                             \
   : (i) == 27 ? 3                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31                                                                 \
       ? 5                                                                     \
       : -1) /**< Port number for AF_WTIMER0_CDTI2 location number i */
#define AF_WTIMER0_CDTI3_PORT(i)                                               \
  (-1) /**< Port number for AF_WTIMER0_CDTI3 location number i */
#define AF_WTIMER1_CC0_PORT(i)                                                 \
  ((i) == 0    ? 1                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 2                                                             \
   : (i) == 5  ? 2                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_WTIMER1_CC0 location number i */
#define AF_WTIMER1_CC1_PORT(i)                                                 \
  ((i) == 0    ? 1                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 2                                                             \
   : (i) == 3  ? 2                                                             \
   : (i) == 4  ? 2                                                             \
   : (i) == 5  ? 2                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_WTIMER1_CC1 location number i */
#define AF_WTIMER1_CC2_PORT(i)                                                 \
  ((i) == 0    ? 2                                                             \
   : (i) == 1  ? 2                                                             \
   : (i) == 2  ? 2                                                             \
   : (i) == 3  ? 2                                                             \
   : (i) == 4  ? 2                                                             \
   : (i) == 5  ? 2                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_WTIMER1_CC2 location number i */
#define AF_WTIMER1_CC3_PORT(i)                                                 \
  ((i) == 0    ? 2                                                             \
   : (i) == 1  ? 2                                                             \
   : (i) == 2  ? 2                                                             \
   : (i) == 3  ? 2                                                             \
   : (i) == 4  ? 2                                                             \
   : (i) == 5  ? 2                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 3                                                             \
   : (i) == 11 ? 3                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_WTIMER1_CC3 location number i */
#define AF_WTIMER1_CDTI0_PORT(i)                                               \
  (-1) /**< Port number for AF_WTIMER1_CDTI0 location number i */
#define AF_WTIMER1_CDTI1_PORT(i)                                               \
  (-1) /**< Port number for AF_WTIMER1_CDTI1 location number i */
#define AF_WTIMER1_CDTI2_PORT(i)                                               \
  (-1) /**< Port number for AF_WTIMER1_CDTI2 location number i */
#define AF_WTIMER1_CDTI3_PORT(i)                                               \
  (-1) /**< Port number for AF_WTIMER1_CDTI3 location number i */
#define AF_USART0_TX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_USART0_TX location number i */
#define AF_USART0_RX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART0_RX location number i */
#define AF_USART0_CLK_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART0_CLK location number i */
#define AF_USART0_CS_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART0_CS location number i */
#define AF_USART0_CTS_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART0_CTS location number i */
#define AF_USART0_RTS_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 0                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART0_RTS location number i */
#define AF_USART1_TX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_USART1_TX location number i */
#define AF_USART1_RX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART1_RX location number i */
#define AF_USART1_CLK_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART1_CLK location number i */
#define AF_USART1_CS_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART1_CS location number i */
#define AF_USART1_CTS_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART1_CTS location number i */
#define AF_USART1_RTS_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 1                                                             \
   : (i) == 2  ? 1                                                             \
   : (i) == 3  ? 1                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 2                                                             \
   : (i) == 7  ? 2                                                             \
   : (i) == 8  ? 2                                                             \
   : (i) == 9  ? 2                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 3                                                             \
   : (i) == 13 ? 3                                                             \
   : (i) == 14 ? 3                                                             \
   : (i) == 15 ? 3                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 0                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART1_RTS location number i */
#define AF_USART2_TX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 8                                                             \
   : (i) == 7  ? 8                                                             \
   : (i) == 8  ? 8                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 10                                                            \
               : -1) /**< Port number for AF_USART2_TX location number i */
#define AF_USART2_RX_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 8                                                             \
   : (i) == 7  ? 8                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 5                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART2_RX location number i */
#define AF_USART2_CLK_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 8                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 5                                                             \
   : (i) == 13 ? 5                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART2_CLK location number i */
#define AF_USART2_CS_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 8                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 5                                                             \
   : (i) == 12 ? 5                                                             \
   : (i) == 13 ? 5                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART2_CS location number i */
#define AF_USART2_CTS_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 8                                                             \
   : (i) == 2  ? 8                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 5                                                             \
   : (i) == 11 ? 5                                                             \
   : (i) == 12 ? 5                                                             \
   : (i) == 13 ? 5                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 10                                                            \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART2_CTS location number i */
#define AF_USART2_RTS_PORT(i)                                                  \
  ((i) == 0    ? 8                                                             \
   : (i) == 1  ? 8                                                             \
   : (i) == 2  ? 8                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 1                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 5                                                             \
   : (i) == 10 ? 5                                                             \
   : (i) == 11 ? 5                                                             \
   : (i) == 12 ? 5                                                             \
   : (i) == 13 ? 5                                                             \
   : (i) == 14 ? 5                                                             \
   : (i) == 15 ? 5                                                             \
   : (i) == 16 ? 5                                                             \
   : (i) == 17 ? 5                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 10                                                            \
   : (i) == 25 ? 10                                                            \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 0                                                             \
   : (i) == 28 ? 0                                                             \
   : (i) == 29 ? 0                                                             \
   : (i) == 30 ? 0                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_USART2_RTS location number i */
#define AF_USART3_TX_PORT(i)                                                   \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 3                                                             \
   : (i) == 4  ? 3                                                             \
   : (i) == 5  ? 3                                                             \
   : (i) == 6  ? 3                                                             \
   : (i) == 7  ? 3                                                             \
   : (i) == 8  ? 8                                                             \
   : (i) == 9  ? 8                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 1                                                             \
   : (i) == 15 ? 1                                                             \
   : (i) == 16 ? 9                                                             \
   : (i) == 17 ? 9                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 2                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 10                                                            \
               : -1) /**< Port number for AF_USART3_TX location number i */
#define AF_USART3_RX_PORT(i)                                                   \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 3                                                             \
   : (i) == 4  ? 3                                                             \
   : (i) == 5  ? 3                                                             \
   : (i) == 6  ? 3                                                             \
   : (i) == 7  ? 8                                                             \
   : (i) == 8  ? 8                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 1                                                             \
   : (i) == 15 ? 9                                                             \
   : (i) == 16 ? 9                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 2                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_USART3_RX location number i */
#define AF_USART3_CLK_PORT(i)                                                  \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 3                                                             \
   : (i) == 4  ? 3                                                             \
   : (i) == 5  ? 3                                                             \
   : (i) == 6  ? 8                                                             \
   : (i) == 7  ? 8                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 1                                                             \
   : (i) == 14 ? 9                                                             \
   : (i) == 15 ? 9                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 2                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_USART3_CLK location number i */
#define AF_USART3_CS_PORT(i)                                                   \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 3                                                             \
   : (i) == 4  ? 3                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 8                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 1                                                             \
   : (i) == 13 ? 9                                                             \
   : (i) == 14 ? 9                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_USART3_CS location number i */
#define AF_USART3_CTS_PORT(i)                                                  \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 3                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 1                                                             \
   : (i) == 12 ? 9                                                             \
   : (i) == 13 ? 9                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 10                                                            \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 10                                                            \
   : (i) == 28 ? 3                                                             \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_USART3_CTS location number i */
#define AF_USART3_RTS_PORT(i)                                                  \
  ((i) == 0    ? 3                                                             \
   : (i) == 1  ? 3                                                             \
   : (i) == 2  ? 3                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 9                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 10                                                            \
   : (i) == 25 ? 10                                                            \
   : (i) == 26 ? 10                                                            \
   : (i) == 27 ? 3                                                             \
   : (i) == 28 ? 3                                                             \
   : (i) == 29 ? 3                                                             \
   : (i) == 30 ? 3                                                             \
   : (i) == 31 ? 3                                                             \
               : -1) /**< Port number for AF_USART3_RTS location number i */
#define AF_LEUART0_TX_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_LEUART0_TX location number i */
#define AF_LEUART0_RX_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_LEUART0_RX location number i */
#define AF_LETIMER0_OUT0_PORT(i)                                               \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31                                                                 \
       ? 5                                                                     \
       : -1) /**< Port number for AF_LETIMER0_OUT0 location number i */
#define AF_LETIMER0_OUT1_PORT(i)                                               \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31                                                                 \
       ? 0                                                                     \
       : -1) /**< Port number for AF_LETIMER0_OUT1 location number i */
#define AF_PCNT0_S0IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_PCNT0_S0IN location number i */
#define AF_PCNT0_S1IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_PCNT0_S1IN location number i */
#define AF_PCNT1_S0IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 9                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 10                                                            \
               : -1) /**< Port number for AF_PCNT1_S0IN location number i */
#define AF_PCNT1_S1IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 9                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 5                                                             \
   : (i) == 19 ? 5                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_PCNT1_S1IN location number i */
#define AF_PCNT2_S0IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 9                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 10                                                            \
               : -1) /**< Port number for AF_PCNT2_S0IN location number i */
#define AF_PCNT2_S1IN_PORT(i)                                                  \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 9                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_PCNT2_S1IN location number i */
#define AF_I2C0_SDA_PORT(i)                                                    \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_I2C0_SDA location number i */
#define AF_I2C0_SCL_PORT(i)                                                    \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 2                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 3                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_I2C0_SCL location number i */
#define AF_I2C1_SDA_PORT(i)                                                    \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 8                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 9                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 2                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 10                                                            \
               : -1) /**< Port number for AF_I2C1_SDA location number i */
#define AF_I2C1_SCL_PORT(i)                                                    \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 8                                                             \
   : (i) == 4  ? 8                                                             \
   : (i) == 5  ? 1                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 9                                                             \
   : (i) == 11 ? 9                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 2                                                             \
   : (i) == 18 ? 2                                                             \
   : (i) == 19 ? 2                                                             \
   : (i) == 20 ? 5                                                             \
   : (i) == 21 ? 5                                                             \
   : (i) == 22 ? 5                                                             \
   : (i) == 23 ? 5                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 10                                                            \
   : (i) == 29 ? 10                                                            \
   : (i) == 30 ? 10                                                            \
   : (i) == 31 ? 0                                                             \
               : -1) /**< Port number for AF_I2C1_SCL location number i */
#define AF_ACMP0_OUT_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_ACMP0_OUT location number i */
#define AF_ACMP1_OUT_PORT(i)                                                   \
  ((i) == 0    ? 0                                                             \
   : (i) == 1  ? 0                                                             \
   : (i) == 2  ? 0                                                             \
   : (i) == 3  ? 0                                                             \
   : (i) == 4  ? 0                                                             \
   : (i) == 5  ? 0                                                             \
   : (i) == 6  ? 1                                                             \
   : (i) == 7  ? 1                                                             \
   : (i) == 8  ? 1                                                             \
   : (i) == 9  ? 1                                                             \
   : (i) == 10 ? 1                                                             \
   : (i) == 11 ? 2                                                             \
   : (i) == 12 ? 2                                                             \
   : (i) == 13 ? 2                                                             \
   : (i) == 14 ? 2                                                             \
   : (i) == 15 ? 2                                                             \
   : (i) == 16 ? 2                                                             \
   : (i) == 17 ? 3                                                             \
   : (i) == 18 ? 3                                                             \
   : (i) == 19 ? 3                                                             \
   : (i) == 20 ? 3                                                             \
   : (i) == 21 ? 3                                                             \
   : (i) == 22 ? 3                                                             \
   : (i) == 23 ? 3                                                             \
   : (i) == 24 ? 5                                                             \
   : (i) == 25 ? 5                                                             \
   : (i) == 26 ? 5                                                             \
   : (i) == 27 ? 5                                                             \
   : (i) == 28 ? 5                                                             \
   : (i) == 29 ? 5                                                             \
   : (i) == 30 ? 5                                                             \
   : (i) == 31 ? 5                                                             \
               : -1) /**< Port number for AF_ACMP1_OUT location number i */
#define AF_LESENSE_CH0_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH0 location number i */
#define AF_LESENSE_CH1_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH1 location number i */
#define AF_LESENSE_CH2_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH2 location number i */
#define AF_LESENSE_CH3_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH3 location number i */
#define AF_LESENSE_CH4_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH4 location number i */
#define AF_LESENSE_CH5_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH5 location number i */
#define AF_LESENSE_CH6_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH6 location number i */
#define AF_LESENSE_CH7_PORT(i)                                                 \
  ((i) == 0 ? 3 : -1) /**< Port number for AF_LESENSE_CH7 location number i */
#define AF_LESENSE_CH8_PORT(i)                                                 \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH8 location number i */
#define AF_LESENSE_CH9_PORT(i)                                                 \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH9 location number i */
#define AF_LESENSE_CH10_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH10 location number i */
#define AF_LESENSE_CH11_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH11 location number i */
#define AF_LESENSE_CH12_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH12 location number i */
#define AF_LESENSE_CH13_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH13 location number i */
#define AF_LESENSE_CH14_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH14 location number i */
#define AF_LESENSE_CH15_PORT(i)                                                \
  ((i) == 0 ? 0 : -1) /**< Port number for AF_LESENSE_CH15 location number i */
#define AF_LESENSE_ALTEX0_PORT(i)                                              \
  ((i) == 0 ? 0                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX0 location number i */
#define AF_LESENSE_ALTEX1_PORT(i)                                              \
  ((i) == 0 ? 0                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX1 location number i */
#define AF_LESENSE_ALTEX2_PORT(i)                                              \
  ((i) == 0 ? 9                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX2 location number i */
#define AF_LESENSE_ALTEX3_PORT(i)                                              \
  ((i) == 0 ? 9                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX3 location number i */
#define AF_LESENSE_ALTEX4_PORT(i)                                              \
  ((i) == 0 ? 8                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX4 location number i */
#define AF_LESENSE_ALTEX5_PORT(i)                                              \
  ((i) == 0 ? 8                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX5 location number i */
#define AF_LESENSE_ALTEX6_PORT(i)                                              \
  ((i) == 0 ? 8                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX6 location number i */
#define AF_LESENSE_ALTEX7_PORT(i)                                              \
  ((i) == 0 ? 8                                                                \
            : -1) /**< Port number for AF_LESENSE_ALTEX7 location number i */
#define AF_DBG_TDI_PORT(i)                                                     \
  ((i) == 0 ? 5 : -1) /**< Port number for AF_DBG_TDI location number i */
#define AF_DBG_TDO_PORT(i)                                                     \
  ((i) == 0 ? 5 : -1) /**< Port number for AF_DBG_TDO location number i */
#define AF_DBG_SWV_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 1                                                              \
   : (i) == 2 ? 3                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_DBG_SWV location number i */
#define AF_DBG_SWDIOTMS_PORT(i)                                                \
  ((i) == 0 ? 5 : -1) /**< Port number for AF_DBG_SWDIOTMS location number i */
#define AF_DBG_SWCLKTCK_PORT(i)                                                \
  ((i) == 0 ? 5 : -1) /**< Port number for AF_DBG_SWCLKTCK location number i */
#define AF_ETM_TCLK_PORT(i)                                                    \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 0                                                              \
   : (i) == 2 ? 8                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_ETM_TCLK location number i */
#define AF_ETM_TD0_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 0                                                              \
   : (i) == 2 ? 8                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_ETM_TD0 location number i */
#define AF_ETM_TD1_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 0                                                              \
   : (i) == 2 ? 1                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_ETM_TD1 location number i */
#define AF_ETM_TD2_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 0                                                              \
   : (i) == 2 ? 1                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_ETM_TD2 location number i */
#define AF_ETM_TD3_PORT(i)                                                     \
  ((i) == 0   ? 5                                                              \
   : (i) == 1 ? 0                                                              \
   : (i) == 2 ? 1                                                              \
   : (i) == 3 ? 2                                                              \
              : -1) /**< Port number for AF_ETM_TD3 location number i */

/** @} */
/** @} End of group EFR32MG12P_AF_Ports */
/** @} End of group Parts */

/***************************************************************************//**
 * @file iec60730_demo_micrium.h
 * @brief Oem timer header
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef IEC60730_DEMO_MICRIUM_H
#define IEC60730_DEMO_MICRIUM_H

/**************************************************************************//**
 * @brief Configuration
 *
 * return void
 *
 * Config parameters before running #iec60730_Post
 *****************************************************************************/
void iec60730_Config(void);

/**************************************************************************//**
 * @brief Initialize
 *
 * return void
 *
 * Initialize parameters before running #iec60730_Bist
 *****************************************************************************/
void iec60730_Init(void);

/**************************************************************************//**
 * @brief Initialize communication task
 *
 * return void
 *
 *****************************************************************************/
void app_comm_Init(void);

#endif /* IEC60730_DEMO_MICRIUM_H */

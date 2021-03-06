/**
 * \file
 *
 * \brief Chip-specific system clock manager configuration
 *
 * Copyright (c) 2013 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

// ===== System Clock Source Options
#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RCFAST

/* RCFAST frequency selection: 0 for 4MHz, 1 for 8MHz and 2 for 12MHz */
//#define CONFIG_RCFAST_FRANGE    0
//#define CONFIG_RCFAST_FRANGE    1
#define CONFIG_RCFAST_FRANGE    2

// ===== DFLL Options
#define CONFIG_DFLL0_FREQ             96025000
#define CONFIG_DFLL0_SOURCE           GENCLK_SRC_RCSYS
#define CONFIG_DFLL0_MUL              835 /* Fdfll = (Fclk * mul) / div */
#define CONFIG_DFLL0_DIV              1   /* Fdfll = (Fclk * mul) / div */

// ===== System Clock Bus Division Options
#define CONFIG_SYSCLK_CPU_DIV         0
#define CONFIG_SYSCLK_PBA_DIV         1
#define CONFIG_SYSCLK_PBB_DIV         1
#define CONFIG_SYSCLK_PBC_DIV         1
#define CONFIG_SYSCLK_PBD_DIV         1

#define CONFIG_CPU_HZ                 12000000
#define CONFIG_PBA_HZ                 6000000
#define CONFIG_PBB_HZ                 6000000
#define CONFIG_PBC_HZ                 6000000
#define CONFIG_PBD_HZ                 6000000

// ===== PLL Options
#define CONFIG_PLL0_SOURCE          PLL_SRC_OSC0

/* Fpll0 = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL0_MUL             (48000000UL / BOARD_OSC0_HZ)
#define CONFIG_PLL0_DIV             1

#define PLL0                        0

// ===== Generic clock
#define CONFIG_GENERIC_SRC            GENCLK_SRC_RCSYS
#define CONFIG_GENERIC_DIV            1
#define CONFIG_GENERIC_ID             2
#define CONFIG_GENERIC_CLOCK          28750

#define get_generic_clock()           \
	(CONFIG_GENERIC_DIV == 0 ? osc_get_rate(OSC_ID_RCSYS) \
	: osc_get_rate(OSC_ID_RCSYS) / (2*(CONFIG_GENERIC_DIV + 1)))

#endif /* CONF_CLOCK_H_INCLUDED */

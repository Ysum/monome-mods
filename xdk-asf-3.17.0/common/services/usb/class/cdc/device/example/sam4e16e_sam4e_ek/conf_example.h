/**
 * \file
 *
 * \brief Example configuration
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
#ifndef CONF_EXAMPLE_H_INCLUDED
#define CONF_EXAMPLE_H_INCLUDED

/* Uses UART */
#define USART_ENABLE()
#define USART_DISABLE()
#define USART_BASE       ((Usart*)UART0)
#define USART_ID         ID_UART0
#define USART_HANDLER    UART0_Handler
#define USART_INT_IRQn   UART0_IRQn

/* Uses USART1 */
/*
#define USART_ENABLE()   \
	ioport_set_pin_level(PIN_USART1_EN_IDX, PIN_USART1_EN_ACTIVE_LEVEL)
#define USART_DISABLE()  \
	ioport_set_pin_level(PIN_USART1_EN_IDX, PIN_USART1_EN_INACTIVE_LEVEL)
#define USART_BASE       ((Usart*)USART1)
#define USART_ID         ID_USART1
#define USART_HANDLER    USART1_Handler
#define USART_INT_IRQn   USART1_IRQn
*/

#define USART_INT_LEVEL  3

#endif /* CONF_EXAMPLE_H_INCLUDED */
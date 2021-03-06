/**
 * \file
 *
 * \brief NAND Flash Raw Operation Example
 *
 * Copyright (c) 2012-2014 Atmel Corporation. All rights reserved.
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

/**
 * \mainpage NAND Flash Raw Example
 *
 * \section Purpose
 *
 * This NAND Flash raw example shall show how to read and write data from/to
 * a NAND Flash connected to the chip.
 *
 * \section Description
 *
 * The required steps are:
 * <ul>
 * <li> Initialize NAND Flash. </li>
 * <li> Find a good block by erase function.</li>
 * <li> Prepare a buffer.</li>
 * <li> Write the buffer into a NAND Flash page data area.</li>
 * <li> Read the page and check data is correct.</li>
 * </ul>
 * \section Usage
 *
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
	-- NAND Flash Raw Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-I- NAND Flash driver initialized
	-I- Size of the whole device in bytes : 0x10000000
	-I- Size in bytes of one single block of a device : 0x20000
	-I- Number of blocks in the entire device : 0x800
	-I- Size of the data area of a page in bytes : 0x800
	-I- Number of pages in the entire device : 0x40
\endcode
 *
 */

#include <asf.h>
#include <string.h>

/* NAND Flash memory size. */
static uint32_t mem_size;
/* Number of blocks in NAND Flash. */
static uint32_t num_block;
/* Size of one block in the NAND Flash, in bytes. */
static uint32_t block_size;
/* Size of one page in the NAND Flash, in bytes. */
static uint32_t page_size;
/* Number of page per block. */
static uint32_t pages_per_block;

/* NAND Flash device structure. */
static struct nand_flash_raw nf_raw;
/* Address for transferring command to the NAND Flash. */
static uint32_t cmd_address = BOARD_NF_COMMAND_ADDR;
/* Address for transferring address to the NAND Flash. */
static uint32_t addr_address = BOARD_NF_ADDRESS_ADDR;
/* Address for transferring data to the NAND Flash. */
static uint32_t data_address = BOARD_NF_DATA_ADDR;

/* Temporary buffer */
uint8_t write_buffer[2048];
uint8_t read_buffer[2048];

/**
 *  Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

int main(void)
{
	uint16_t block, page;
	uint32_t i;

	uint32_t error = 0;

	/* Initialize the SAM3 system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- NAND Flash Raw Example --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	memset(&nf_raw, 0, sizeof(nf_raw));

	if (nand_flash_raw_initialize(&nf_raw, 0, cmd_address,
			addr_address, data_address)) {

		printf("-E- Device Unknown\n\r");
		return 0;
	}

	printf("-I- NAND Flash driver initialized\n\r");

	/* Get device parameters */
	mem_size = nand_flash_model_get_device_size_in_bytes(&nf_raw.model);
	block_size = nand_flash_model_get_block_size_in_bytes(&nf_raw.model);
	num_block = nand_flash_model_get_device_size_in_blocks(&nf_raw.model);
	page_size = nand_flash_model_get_page_data_size(&nf_raw.model);
	pages_per_block =
			nand_flash_model_get_block_size_in_pages(&nf_raw.model);

	printf("-I- Size of the whole device in bytes : 0x%x \n\r", mem_size);
	printf("-I- Size in bytes of one single block of a device : 0x%x \n\r",
			block_size);
	printf("-I- Number of blocks in the entire device : 0x%x \n\r",
			num_block);
	printf("-I- Size of the data area of a page in bytes : 0x%x \n\r",
			page_size);
	printf("-I- Number of pages in the entire device : 0x%x \n\r",
			pages_per_block);

	/* Erase all block and use the last good block for read/write test */
	for (i = 0; i < num_block; i++) {
		error = nand_flash_raw_erase_block(&nf_raw, i);

		if (error == NAND_COMMON_ERROR_BADBLOCK) {
			printf("-E- Block %u is BAD block. \n\r", i);
		} else {
			block = i;
		}
	}
	/* Prepare a page size buffer in SRAM. */
	printf("-I- Preparing a buffer in SRAM ...\n\r");
	for (i = 0; i < page_size; i++) {
		write_buffer[i] = i & 0xFF;
	}

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	/* Select a page. */
	page = 0;
	/* Write a page to the NAND Flash. */
	printf("-I- Write the buffer in page %d of block %d without ECC.\n\r",
			page, block);
	error = nand_flash_raw_write_page(&nf_raw, block, page, write_buffer,
			0);
	if (error) {
		printf("-E- Cannot write page %d of block %d.\n\r", page,
				block);
		return error;
	}

	/* Read the page from the NAND Flash. */
	printf("-I- Read page %d of block %d without ECC.\n\r", page, block);
	nand_flash_raw_read_page(&nf_raw, block, page, read_buffer, 0);

	/* Test if the read buffer is the same as SRAM buffer */
	error = memcmp(read_buffer, write_buffer, sizeof(write_buffer));
	if (error) {
		printf("-I- Read data is different from write data.\n\r");
		printf("-I- Need ECC module when handle this page.\n\r");

		return 0;
	}
	printf("-I- Read data matches write data.\n\r");

	printf("-I- Test passed.\n\r");

	while (1) {
		/* Do nothing */
	}
}

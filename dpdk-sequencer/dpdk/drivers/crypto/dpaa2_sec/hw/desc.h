/*-
 * This file is provided under a dual BSD/GPLv2 license. When using or
 * redistributing this file, you may do so under either license.
 *
 *   BSD LICENSE
 *
 * Copyright 2008-2016 Freescale Semiconductor Inc.
 * Copyright (c) 2016 NXP.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of the above-listed copyright holders nor the
 * names of any contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 *   GPL LICENSE SUMMARY
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * SEC descriptor composition header.
 * Definitions to support SEC descriptor instruction generation
 */

#ifndef __RTA_DESC_H__
#define __RTA_DESC_H__

/* hw/compat.h is not delivered in kernel */
#ifndef __KERNEL__
#include "hw/compat.h"
#endif

/* Max size of any SEC descriptor in 32-bit words, inclusive of header */
#define MAX_CAAM_DESCSIZE	64

#define CAAM_CMD_SZ sizeof(uint32_t)
#define CAAM_PTR_SZ sizeof(dma_addr_t)
#define CAAM_DESC_BYTES_MAX (CAAM_CMD_SZ * MAX_CAAM_DESCSIZE)
#define DESC_JOB_IO_LEN (CAAM_CMD_SZ * 5 + CAAM_PTR_SZ * 3)

/* Block size of any entity covered/uncovered with a KEK/TKEK */
#define KEK_BLOCKSIZE		16

/*
 * Supported descriptor command types as they show up
 * inside a descriptor command word.
 */
#define CMD_SHIFT		27
#define CMD_MASK		(0x1f << CMD_SHIFT)

#define CMD_KEY			(0x00 << CMD_SHIFT)
#define CMD_SEQ_KEY		(0x01 << CMD_SHIFT)
#define CMD_LOAD		(0x02 << CMD_SHIFT)
#define CMD_SEQ_LOAD		(0x03 << CMD_SHIFT)
#define CMD_FIFO_LOAD		(0x04 << CMD_SHIFT)
#define CMD_SEQ_FIFO_LOAD	(0x05 << CMD_SHIFT)
#define CMD_MOVEDW		(0x06 << CMD_SHIFT)
#define CMD_MOVEB		(0x07 << CMD_SHIFT)
#define CMD_STORE		(0x0a << CMD_SHIFT)
#define CMD_SEQ_STORE		(0x0b << CMD_SHIFT)
#define CMD_FIFO_STORE		(0x0c << CMD_SHIFT)
#define CMD_SEQ_FIFO_STORE	(0x0d << CMD_SHIFT)
#define CMD_MOVE_LEN		(0x0e << CMD_SHIFT)
#define CMD_MOVE		(0x0f << CMD_SHIFT)
#define CMD_OPERATION		((uint32_t)(0x10 << CMD_SHIFT))
#define CMD_SIGNATURE		((uint32_t)(0x12 << CMD_SHIFT))
#define CMD_JUMP		((uint32_t)(0x14 << CMD_SHIFT))
#define CMD_MATH		((uint32_t)(0x15 << CMD_SHIFT))
#define CMD_DESC_HDR		((uint32_t)(0x16 << CMD_SHIFT))
#define CMD_SHARED_DESC_HDR	((uint32_t)(0x17 << CMD_SHIFT))
#define CMD_MATHI               ((uint32_t)(0x1d << CMD_SHIFT))
#define CMD_SEQ_IN_PTR		((uint32_t)(0x1e << CMD_SHIFT))
#define CMD_SEQ_OUT_PTR		((uint32_t)(0x1f << CMD_SHIFT))

/* General-purpose class selector for all commands */
#define CLASS_SHIFT		25
#define CLASS_MASK		(0x03 << CLASS_SHIFT)

#define CLASS_NONE		(0x00 << CLASS_SHIFT)
#define CLASS_1			(0x01 << CLASS_SHIFT)
#define CLASS_2			(0x02 << CLASS_SHIFT)
#define CLASS_BOTH		(0x03 << CLASS_SHIFT)

/* ICV Check bits for Algo Operation command */
#define ICV_CHECK_DISABLE	0
#define ICV_CHECK_ENABLE	1

/* Encap Mode check bits for Algo Operation command */
#define DIR_ENC			1
#define DIR_DEC			0

/*
 * Descriptor header command constructs
 * Covers shared, job, and trusted descriptor headers
 */

/*
 * Extended Job Descriptor Header
 */
#define HDR_EXT			BIT(24)

/*
 * Read input frame as soon as possible (SHR HDR)
 */
#define HDR_RIF			BIT(25)

/*
 * Require SEQ LIODN to be the Same  (JOB HDR)
 */
#define HDR_RSLS		BIT(25)

/*
 * Do Not Run - marks a descriptor not executable if there was
 * a preceding error somewhere
 */
#define HDR_DNR			BIT(24)

/*
 * ONE - should always be set. Combination of ONE (always
 * set) and ZRO (always clear) forms an endianness sanity check
 */
#define HDR_ONE			BIT(23)
#define HDR_ZRO			BIT(15)

/* Start Index or SharedDesc Length */
#define HDR_START_IDX_SHIFT	16
#define HDR_START_IDX_MASK	(0x3f << HDR_START_IDX_SHIFT)

/* If shared descriptor header, 6-bit length */
#define HDR_DESCLEN_SHR_MASK	0x3f

/* If non-shared header, 7-bit length */
#define HDR_DESCLEN_MASK	0x7f

/* This is a TrustedDesc (if not SharedDesc) */
#define HDR_TRUSTED		BIT(14)

/* Make into TrustedDesc (if not SharedDesc) */
#define HDR_MAKE_TRUSTED	BIT(13)

/* Clear Input FiFO (if SharedDesc) */
#define HDR_CLEAR_IFIFO		BIT(13)

/* Save context if self-shared (if SharedDesc) */
#define HDR_SAVECTX		BIT(12)

/* Next item points to SharedDesc */
#define HDR_SHARED		BIT(12)

/*
 * Reverse Execution Order - execute JobDesc first, then
 * execute SharedDesc (normally SharedDesc goes first).
 */
#define HDR_REVERSE		BIT(11)

/* Propagate DNR property to SharedDesc */
#define HDR_PROP_DNR		BIT(11)

/* DECO Select Valid */
#define HDR_EXT_DSEL_VALID	BIT(7)

/* Fake trusted descriptor */
#define HDR_EXT_FTD		BIT(8)

/* JobDesc/SharedDesc share property */
#define HDR_SD_SHARE_SHIFT	8
#define HDR_SD_SHARE_MASK	(0x03 << HDR_SD_SHARE_SHIFT)
#define HDR_JD_SHARE_SHIFT	8
#define HDR_JD_SHARE_MASK	(0x07 << HDR_JD_SHARE_SHIFT)

#define HDR_SHARE_NEVER		(0x00 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_WAIT		(0x01 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_SERIAL	(0x02 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_ALWAYS	(0x03 << HDR_SD_SHARE_SHIFT)
#define HDR_SHARE_DEFER		(0x04 << HDR_SD_SHARE_SHIFT)

/* JobDesc/SharedDesc descriptor length */
#define HDR_JD_LENGTH_MASK	0x7f
#define HDR_SD_LENGTH_MASK	0x3f

/*
 * KEY/SEQ_KEY Command Constructs
 */

/* Key Destination Class: 01 = Class 1, 02 - Class 2 */
#define KEY_DEST_CLASS_SHIFT	25
#define KEY_DEST_CLASS_MASK	(0x03 << KEY_DEST_CLASS_SHIFT)
#define KEY_DEST_CLASS1		(1 << KEY_DEST_CLASS_SHIFT)
#define KEY_DEST_CLASS2		(2 << KEY_DEST_CLASS_SHIFT)

/* Scatter-Gather Table/Variable Length Field */
#define KEY_SGF			BIT(24)
#define KEY_VLF			BIT(24)

/* Immediate - Key follows command in the descriptor */
#define KEY_IMM			BIT(23)

/*
 * Already in Input Data FIFO - the Input Data Sequence is not read, since it is
 * already in the Input Data FIFO.
 */
#define KEY_AIDF		BIT(23)

/*
 * Encrypted - Key is encrypted either with the KEK, or
 * with the TDKEK if this descriptor is trusted
 */
#define KEY_ENC			BIT(22)

/*
 * No Write Back - Do not allow key to be FIFO STOREd
 */
#define KEY_NWB			BIT(21)

/*
 * Enhanced Encryption of Key
 */
#define KEY_EKT			BIT(20)

/*
 * Encrypted with Trusted Key
 */
#define KEY_TK			BIT(15)

/*
 * Plaintext Store
 */
#define KEY_PTS			BIT(14)

/*
 * KDEST - Key Destination: 0 - class key register,
 * 1 - PKHA 'e', 2 - AFHA Sbox, 3 - MDHA split key
 */
#define KEY_DEST_SHIFT		16
#define KEY_DEST_MASK		(0x03 << KEY_DEST_SHIFT)

#define KEY_DEST_CLASS_REG	(0x00 << KEY_DEST_SHIFT)
#define KEY_DEST_PKHA_E		(0x01 << KEY_DEST_SHIFT)
#define KEY_DEST_AFHA_SBOX	(0x02 << KEY_DEST_SHIFT)
#define KEY_DEST_MDHA_SPLIT	(0x03 << KEY_DEST_SHIFT)

/* Length in bytes */
#define KEY_LENGTH_MASK		0x000003ff

/*
 * LOAD/SEQ_LOAD/STORE/SEQ_STORE Command Constructs
 */

/*
 * Load/Store Destination: 0 = class independent CCB,
 * 1 = class 1 CCB, 2 = class 2 CCB, 3 = DECO
 */
#define LDST_CLASS_SHIFT	25
#define LDST_CLASS_MASK		(0x03 << LDST_CLASS_SHIFT)
#define LDST_CLASS_IND_CCB	(0x00 << LDST_CLASS_SHIFT)
#define LDST_CLASS_1_CCB	(0x01 << LDST_CLASS_SHIFT)
#define LDST_CLASS_2_CCB	(0x02 << LDST_CLASS_SHIFT)
#define LDST_CLASS_DECO		(0x03 << LDST_CLASS_SHIFT)

/* Scatter-Gather Table/Variable Length Field */
#define LDST_SGF		BIT(24)
#define LDST_VLF		BIT(24)

/* Immediate - Key follows this command in descriptor */
#define LDST_IMM_MASK		1
#define LDST_IMM_SHIFT		23
#define LDST_IMM		BIT(23)

/* SRC/DST - Destination for LOAD, Source for STORE */
#define LDST_SRCDST_SHIFT	16
#define LDST_SRCDST_MASK	(0x7f << LDST_SRCDST_SHIFT)

#define LDST_SRCDST_BYTE_CONTEXT	(0x20 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_KEY		(0x40 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_INFIFO		(0x7c << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_OUTFIFO	(0x7e << LDST_SRCDST_SHIFT)

#define LDST_SRCDST_WORD_MODE_REG	(0x00 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_JQCTRL	(0x00 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_KEYSZ_REG	(0x01 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_JQDAR	(0x01 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DATASZ_REG	(0x02 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_STAT	(0x02 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_ICVSZ_REG	(0x03 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_DCHKSM		(0x03 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PID		(0x04 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CHACTRL	(0x06 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECOCTRL	(0x06 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_IRQCTRL	(0x07 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_PCLOVRD	(0x07 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLRW		(0x08 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH0	(0x08 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_STAT		(0x09 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH1	(0x09 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH2	(0x0a << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_AAD_SZ	(0x0b << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DECO_MATH3	(0x0b << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLASS1_IV_SZ	(0x0c << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_ALTDS_CLASS1	(0x0f << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_A_SZ	(0x10 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_GTR		(0x10 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_B_SZ	(0x11 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_N_SZ	(0x12 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_PKHA_E_SZ	(0x13 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_CLASS_CTX	(0x20 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_STR		(0x20 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF	(0x40 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF_JOB	(0x41 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF_SHARED	(0x42 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF_JOB_WE	(0x45 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_DESCBUF_SHARED_WE (0x46 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_SZL	(0x70 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_SZM	(0x71 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_L	(0x72 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO_M	(0x73 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_SZL		(0x74 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_SZM		(0x75 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_IFNSR		(0x76 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_OFNSR		(0x77 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_BYTE_ALTSOURCE	(0x78 << LDST_SRCDST_SHIFT)
#define LDST_SRCDST_WORD_INFO_FIFO	(0x7a << LDST_SRCDST_SHIFT)

/* Offset in source/destination */
#define LDST_OFFSET_SHIFT	8
#define LDST_OFFSET_MASK	(0xff << LDST_OFFSET_SHIFT)

/* LDOFF definitions used when DST = LDST_SRCDST_WORD_DECOCTRL */
/* These could also be shifted by LDST_OFFSET_SHIFT - this reads better */
#define LDOFF_CHG_SHARE_SHIFT		0
#define LDOFF_CHG_SHARE_MASK		(0x3 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_NEVER		(0x1 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_OK_PROP		(0x2 << LDOFF_CHG_SHARE_SHIFT)
#define LDOFF_CHG_SHARE_OK_NO_PROP	(0x3 << LDOFF_CHG_SHARE_SHIFT)

#define LDOFF_ENABLE_AUTO_NFIFO		BIT(2)
#define LDOFF_DISABLE_AUTO_NFIFO	BIT(3)

#define LDOFF_CHG_NONSEQLIODN_SHIFT	4
#define LDOFF_CHG_NONSEQLIODN_MASK	(0x3 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_SEQ	(0x1 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_NON_SEQ	(0x2 << LDOFF_CHG_NONSEQLIODN_SHIFT)
#define LDOFF_CHG_NONSEQLIODN_TRUSTED	(0x3 << LDOFF_CHG_NONSEQLIODN_SHIFT)

#define LDOFF_CHG_SEQLIODN_SHIFT	6
#define LDOFF_CHG_SEQLIODN_MASK		(0x3 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_SEQ		(0x1 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_NON_SEQ	(0x2 << LDOFF_CHG_SEQLIODN_SHIFT)
#define LDOFF_CHG_SEQLIODN_TRUSTED	(0x3 << LDOFF_CHG_SEQLIODN_SHIFT)

/* Data length in bytes */
#define LDST_LEN_SHIFT		0
#define LDST_LEN_MASK		(0xff << LDST_LEN_SHIFT)

/* Special Length definitions when dst=deco-ctrl */
#define LDLEN_ENABLE_OSL_COUNT		BIT(7)
#define LDLEN_RST_CHA_OFIFO_PTR		BIT(6)
#define LDLEN_RST_OFIFO			BIT(5)
#define LDLEN_SET_OFIFO_OFF_VALID	BIT(4)
#define LDLEN_SET_OFIFO_OFF_RSVD	BIT(3)
#define LDLEN_SET_OFIFO_OFFSET_SHIFT	0
#define LDLEN_SET_OFIFO_OFFSET_MASK	(3 << LDLEN_SET_OFIFO_OFFSET_SHIFT)

/* CCB Clear Written Register bits */
#define CLRW_CLR_C1MODE              BIT(0)
#define CLRW_CLR_C1DATAS             BIT(2)
#define CLRW_CLR_C1ICV               BIT(3)
#define CLRW_CLR_C1CTX               BIT(5)
#define CLRW_CLR_C1KEY               BIT(6)
#define CLRW_CLR_PK_A                BIT(12)
#define CLRW_CLR_PK_B                BIT(13)
#define CLRW_CLR_PK_N                BIT(14)
#define CLRW_CLR_PK_E                BIT(15)
#define CLRW_CLR_C2MODE              BIT(16)
#define CLRW_CLR_C2KEYS              BIT(17)
#define CLRW_CLR_C2DATAS             BIT(18)
#define CLRW_CLR_C2CTX               BIT(21)
#define CLRW_CLR_C2KEY               BIT(22)
#define CLRW_RESET_CLS2_DONE         BIT(26) /* era 4 */
#define CLRW_RESET_CLS1_DONE         BIT(27) /* era 4 */
#define CLRW_RESET_CLS2_CHA          BIT(28) /* era 4 */
#define CLRW_RESET_CLS1_CHA          BIT(29) /* era 4 */
#define CLRW_RESET_OFIFO             BIT(30) /* era 3 */
#define CLRW_RESET_IFIFO_DFIFO       BIT(31) /* era 3 */

/* CHA Control Register bits */
#define CCTRL_RESET_CHA_ALL          BIT(0)
#define CCTRL_RESET_CHA_AESA         BIT(1)
#define CCTRL_RESET_CHA_DESA         BIT(2)
#define CCTRL_RESET_CHA_AFHA         BIT(3)
#define CCTRL_RESET_CHA_KFHA         BIT(4)
#define CCTRL_RESET_CHA_SF8A         BIT(5)
#define CCTRL_RESET_CHA_PKHA         BIT(6)
#define CCTRL_RESET_CHA_MDHA         BIT(7)
#define CCTRL_RESET_CHA_CRCA         BIT(8)
#define CCTRL_RESET_CHA_RNG          BIT(9)
#define CCTRL_RESET_CHA_SF9A         BIT(10)
#define CCTRL_RESET_CHA_ZUCE         BIT(11)
#define CCTRL_RESET_CHA_ZUCA         BIT(12)
#define CCTRL_UNLOAD_PK_A0           BIT(16)
#define CCTRL_UNLOAD_PK_A1           BIT(17)
#define CCTRL_UNLOAD_PK_A2           BIT(18)
#define CCTRL_UNLOAD_PK_A3           BIT(19)
#define CCTRL_UNLOAD_PK_B0           BIT(20)
#define CCTRL_UNLOAD_PK_B1           BIT(21)
#define CCTRL_UNLOAD_PK_B2           BIT(22)
#define CCTRL_UNLOAD_PK_B3           BIT(23)
#define CCTRL_UNLOAD_PK_N            BIT(24)
#define CCTRL_UNLOAD_PK_A            BIT(26)
#define CCTRL_UNLOAD_PK_B            BIT(27)
#define CCTRL_UNLOAD_SBOX            BIT(28)

/* IRQ Control Register (CxCIRQ) bits */
#define CIRQ_ADI	BIT(1)
#define CIRQ_DDI	BIT(2)
#define CIRQ_RCDI	BIT(3)
#define CIRQ_KDI	BIT(4)
#define CIRQ_S8DI	BIT(5)
#define CIRQ_PDI	BIT(6)
#define CIRQ_MDI	BIT(7)
#define CIRQ_CDI	BIT(8)
#define CIRQ_RNDI	BIT(9)
#define CIRQ_S9DI	BIT(10)
#define CIRQ_ZEDI	BIT(11) /* valid for Era 5 or higher */
#define CIRQ_ZADI	BIT(12) /* valid for Era 5 or higher */
#define CIRQ_AEI	BIT(17)
#define CIRQ_DEI	BIT(18)
#define CIRQ_RCEI	BIT(19)
#define CIRQ_KEI	BIT(20)
#define CIRQ_S8EI	BIT(21)
#define CIRQ_PEI	BIT(22)
#define CIRQ_MEI	BIT(23)
#define CIRQ_CEI	BIT(24)
#define CIRQ_RNEI	BIT(25)
#define CIRQ_S9EI	BIT(26)
#define CIRQ_ZEEI	BIT(27) /* valid for Era 5 or higher */
#define CIRQ_ZAEI	BIT(28) /* valid for Era 5 or higher */

/*
 * FIFO_LOAD/FIFO_STORE/SEQ_FIFO_LOAD/SEQ_FIFO_STORE
 * Command Constructs
 */

/*
 * Load Destination: 0 = skip (SEQ_FIFO_LOAD only),
 * 1 = Load for Class1, 2 = Load for Class2, 3 = Load both
 * Store Source: 0 = normal, 1 = Class1key, 2 = Class2key
 */
#define FIFOLD_CLASS_SHIFT	25
#define FIFOLD_CLASS_MASK	(0x03 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_SKIP	(0x00 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_CLASS1	(0x01 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_CLASS2	(0x02 << FIFOLD_CLASS_SHIFT)
#define FIFOLD_CLASS_BOTH	(0x03 << FIFOLD_CLASS_SHIFT)

#define FIFOST_CLASS_SHIFT	25
#define FIFOST_CLASS_MASK	(0x03 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_NORMAL	(0x00 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_CLASS1KEY	(0x01 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_CLASS2KEY	(0x02 << FIFOST_CLASS_SHIFT)
#define FIFOST_CLASS_BOTH	(0x03 << FIFOST_CLASS_SHIFT)

/*
 * Scatter-Gather Table/Variable Length Field
 * If set for FIFO_LOAD, refers to a SG table. Within
 * SEQ_FIFO_LOAD, is variable input sequence
 */
#define FIFOLDST_SGF_SHIFT	24
#define FIFOLDST_SGF_MASK	(1 << FIFOLDST_SGF_SHIFT)
#define FIFOLDST_VLF_MASK	(1 << FIFOLDST_SGF_SHIFT)
#define FIFOLDST_SGF		BIT(24)
#define FIFOLDST_VLF		BIT(24)

/*
 * Immediate - Data follows command in descriptor
 * AIDF - Already in Input Data FIFO
 */
#define FIFOLD_IMM_SHIFT	23
#define FIFOLD_IMM_MASK		(1 << FIFOLD_IMM_SHIFT)
#define FIFOLD_AIDF_MASK	(1 << FIFOLD_IMM_SHIFT)
#define FIFOLD_IMM		BIT(23)
#define FIFOLD_AIDF		BIT(23)

#define FIFOST_IMM_SHIFT	23
#define FIFOST_IMM_MASK		(1 << FIFOST_IMM_SHIFT)
#define FIFOST_IMM		BIT(23)

/* Continue - Not the last FIFO store to come */
#define FIFOST_CONT_SHIFT	23
#define FIFOST_CONT_MASK	(1 << FIFOST_CONT_SHIFT)
#define FIFOST_CONT		BIT(23)

/*
 * Extended Length - use 32-bit extended length that
 * follows the pointer field. Illegal with IMM set
 */
#define FIFOLDST_EXT_SHIFT	22
#define FIFOLDST_EXT_MASK	(1 << FIFOLDST_EXT_SHIFT)
#define FIFOLDST_EXT		BIT(22)

/* Input data type.*/
#define FIFOLD_TYPE_SHIFT	16
#define FIFOLD_CONT_TYPE_SHIFT	19 /* shift past last-flush bits */
#define FIFOLD_TYPE_MASK	(0x3f << FIFOLD_TYPE_SHIFT)

/* PK types */
#define FIFOLD_TYPE_PK		(0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_MASK	(0x30 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_TYPEMASK (0x0f << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A0	(0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A1	(0x01 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A2	(0x02 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A3	(0x03 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B0	(0x04 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B1	(0x05 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B2	(0x06 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B3	(0x07 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_N	(0x08 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_A	(0x0c << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_PK_B	(0x0d << FIFOLD_TYPE_SHIFT)

/* Other types. Need to OR in last/flush bits as desired */
#define FIFOLD_TYPE_MSG_MASK	(0x38 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_MSG		(0x10 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_MSG1OUT2	(0x18 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_IV		(0x20 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_BITDATA	(0x28 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_AAD		(0x30 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_ICV		(0x38 << FIFOLD_TYPE_SHIFT)

/* Last/Flush bits for use with "other" types above */
#define FIFOLD_TYPE_ACT_MASK	(0x07 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_NOACTION	(0x00 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_FLUSH1	(0x01 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST1	(0x02 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2FLUSH	(0x03 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2	(0x04 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LAST2FLUSH1 (0x05 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LASTBOTH	(0x06 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_LASTBOTHFL	(0x07 << FIFOLD_TYPE_SHIFT)
#define FIFOLD_TYPE_NOINFOFIFO	(0x0f << FIFOLD_TYPE_SHIFT)

#define FIFOLDST_LEN_MASK	0xffff
#define FIFOLDST_EXT_LEN_MASK	0xffffffff

/* Output data types */
#define FIFOST_TYPE_SHIFT	16
#define FIFOST_TYPE_MASK	(0x3f << FIFOST_TYPE_SHIFT)

#define FIFOST_TYPE_PKHA_A0	 (0x00 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A1	 (0x01 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A2	 (0x02 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A3	 (0x03 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B0	 (0x04 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B1	 (0x05 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B2	 (0x06 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B3	 (0x07 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_N	 (0x08 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_A	 (0x0c << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_B	 (0x0d << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_AF_SBOX_JKEK (0x20 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_AF_SBOX_TKEK (0x21 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_JKEK	 (0x22 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_PKHA_E_TKEK	 (0x23 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_KEK	 (0x24 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_KEY_TKEK	 (0x25 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_KEK	 (0x26 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SPLIT_TKEK	 (0x27 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_KEK	 (0x28 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_OUTFIFO_TKEK (0x29 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_MESSAGE_DATA (0x30 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_MESSAGE_DATA2 (0x31 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_RNGSTORE	 (0x34 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_RNGFIFO	 (0x35 << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_METADATA	 (0x3e << FIFOST_TYPE_SHIFT)
#define FIFOST_TYPE_SKIP	 (0x3f << FIFOST_TYPE_SHIFT)

/*
 * OPERATION Command Constructs
 */

/* Operation type selectors - OP TYPE */
#define OP_TYPE_SHIFT		24
#define OP_TYPE_MASK		(0x07 << OP_TYPE_SHIFT)

#define OP_TYPE_UNI_PROTOCOL	(0x00 << OP_TYPE_SHIFT)
#define OP_TYPE_PK		(0x01 << OP_TYPE_SHIFT)
#define OP_TYPE_CLASS1_ALG	(0x02 << OP_TYPE_SHIFT)
#define OP_TYPE_CLASS2_ALG	(0x04 << OP_TYPE_SHIFT)
#define OP_TYPE_DECAP_PROTOCOL	(0x06 << OP_TYPE_SHIFT)
#define OP_TYPE_ENCAP_PROTOCOL	(0x07 << OP_TYPE_SHIFT)

/* ProtocolID selectors - PROTID */
#define OP_PCLID_SHIFT		16
#define OP_PCLID_MASK		(0xff << OP_PCLID_SHIFT)

/* Assuming OP_TYPE = OP_TYPE_UNI_PROTOCOL */
#define OP_PCLID_IKEV1_PRF	(0x01 << OP_PCLID_SHIFT)
#define OP_PCLID_IKEV2_PRF	(0x02 << OP_PCLID_SHIFT)
#define OP_PCLID_SSL30_PRF	(0x08 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS10_PRF	(0x09 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS11_PRF	(0x0a << OP_PCLID_SHIFT)
#define OP_PCLID_TLS12_PRF	(0x0b << OP_PCLID_SHIFT)
#define OP_PCLID_DTLS10_PRF	(0x0c << OP_PCLID_SHIFT)
#define OP_PCLID_PUBLICKEYPAIR	(0x14 << OP_PCLID_SHIFT)
#define OP_PCLID_DSASIGN	(0x15 << OP_PCLID_SHIFT)
#define OP_PCLID_DSAVERIFY	(0x16 << OP_PCLID_SHIFT)
#define OP_PCLID_DIFFIEHELLMAN	(0x17 << OP_PCLID_SHIFT)
#define OP_PCLID_RSAENCRYPT	(0x18 << OP_PCLID_SHIFT)
#define OP_PCLID_RSADECRYPT	(0x19 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_MD5	(0x20 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_SHA1	(0x21 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_SHA224	(0x22 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_SHA256	(0x23 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_SHA384	(0x24 << OP_PCLID_SHIFT)
#define OP_PCLID_DKP_SHA512	(0x25 << OP_PCLID_SHIFT)

/* Assuming OP_TYPE = OP_TYPE_DECAP_PROTOCOL/ENCAP_PROTOCOL */
#define OP_PCLID_IPSEC		(0x01 << OP_PCLID_SHIFT)
#define OP_PCLID_SRTP		(0x02 << OP_PCLID_SHIFT)
#define OP_PCLID_MACSEC		(0x03 << OP_PCLID_SHIFT)
#define OP_PCLID_WIFI		(0x04 << OP_PCLID_SHIFT)
#define OP_PCLID_WIMAX		(0x05 << OP_PCLID_SHIFT)
#define OP_PCLID_SSL30		(0x08 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS10		(0x09 << OP_PCLID_SHIFT)
#define OP_PCLID_TLS11		(0x0a << OP_PCLID_SHIFT)
#define OP_PCLID_TLS12		(0x0b << OP_PCLID_SHIFT)
#define OP_PCLID_DTLS10		(0x0c << OP_PCLID_SHIFT)
#define OP_PCLID_BLOB		(0x0d << OP_PCLID_SHIFT)
#define OP_PCLID_IPSEC_NEW	(0x11 << OP_PCLID_SHIFT)
#define OP_PCLID_3G_DCRC	(0x31 << OP_PCLID_SHIFT)
#define OP_PCLID_3G_RLC_PDU	(0x32 << OP_PCLID_SHIFT)
#define OP_PCLID_3G_RLC_SDU	(0x33 << OP_PCLID_SHIFT)
#define OP_PCLID_LTE_PDCP_USER	(0x42 << OP_PCLID_SHIFT)
#define OP_PCLID_LTE_PDCP_CTRL	(0x43 << OP_PCLID_SHIFT)
#define OP_PCLID_LTE_PDCP_CTRL_MIXED	(0x44 << OP_PCLID_SHIFT)

/*
 * ProtocolInfo selectors
 */
#define OP_PCLINFO_MASK				 0xffff

/* for OP_PCLID_IPSEC */
#define OP_PCL_IPSEC_CIPHER_MASK		 0xff00
#define OP_PCL_IPSEC_AUTH_MASK			 0x00ff

#define OP_PCL_IPSEC_DES_IV64			 0x0100
#define OP_PCL_IPSEC_DES			 0x0200
#define OP_PCL_IPSEC_3DES			 0x0300
#define OP_PCL_IPSEC_NULL			 0x0B00
#define OP_PCL_IPSEC_AES_CBC			 0x0c00
#define OP_PCL_IPSEC_AES_CTR			 0x0d00
#define OP_PCL_IPSEC_AES_XTS			 0x1600
#define OP_PCL_IPSEC_AES_CCM8			 0x0e00
#define OP_PCL_IPSEC_AES_CCM12			 0x0f00
#define OP_PCL_IPSEC_AES_CCM16			 0x1000
#define OP_PCL_IPSEC_AES_GCM8			 0x1200
#define OP_PCL_IPSEC_AES_GCM12			 0x1300
#define OP_PCL_IPSEC_AES_GCM16			 0x1400
#define OP_PCL_IPSEC_AES_NULL_WITH_GMAC		 0x1500

#define OP_PCL_IPSEC_HMAC_NULL			 0x0000
#define OP_PCL_IPSEC_HMAC_MD5_96		 0x0001
#define OP_PCL_IPSEC_HMAC_SHA1_96		 0x0002
#define OP_PCL_IPSEC_AES_XCBC_MAC_96		 0x0005
#define OP_PCL_IPSEC_HMAC_MD5_128		 0x0006
#define OP_PCL_IPSEC_HMAC_SHA1_160		 0x0007
#define OP_PCL_IPSEC_AES_CMAC_96		 0x0008
#define OP_PCL_IPSEC_HMAC_SHA2_256_128		 0x000c
#define OP_PCL_IPSEC_HMAC_SHA2_384_192		 0x000d
#define OP_PCL_IPSEC_HMAC_SHA2_512_256		 0x000e

/* For SRTP - OP_PCLID_SRTP */
#define OP_PCL_SRTP_CIPHER_MASK			 0xff00
#define OP_PCL_SRTP_AUTH_MASK			 0x00ff

#define OP_PCL_SRTP_AES_CTR			 0x0d00

#define OP_PCL_SRTP_HMAC_SHA1_160		 0x0007

/* For SSL 3.0 - OP_PCLID_SSL30 */
#define OP_PCL_SSL30_AES_128_CBC_SHA		 0x002f
#define OP_PCL_SSL30_AES_128_CBC_SHA_2		 0x0030
#define OP_PCL_SSL30_AES_128_CBC_SHA_3		 0x0031
#define OP_PCL_SSL30_AES_128_CBC_SHA_4		 0x0032
#define OP_PCL_SSL30_AES_128_CBC_SHA_5		 0x0033
#define OP_PCL_SSL30_AES_128_CBC_SHA_6		 0x0034
#define OP_PCL_SSL30_AES_128_CBC_SHA_7		 0x008c
#define OP_PCL_SSL30_AES_128_CBC_SHA_8		 0x0090
#define OP_PCL_SSL30_AES_128_CBC_SHA_9		 0x0094
#define OP_PCL_SSL30_AES_128_CBC_SHA_10		 0xc004
#define OP_PCL_SSL30_AES_128_CBC_SHA_11		 0xc009
#define OP_PCL_SSL30_AES_128_CBC_SHA_12		 0xc00e
#define OP_PCL_SSL30_AES_128_CBC_SHA_13		 0xc013
#define OP_PCL_SSL30_AES_128_CBC_SHA_14		 0xc018
#define OP_PCL_SSL30_AES_128_CBC_SHA_15		 0xc01d
#define OP_PCL_SSL30_AES_128_CBC_SHA_16		 0xc01e
#define OP_PCL_SSL30_AES_128_CBC_SHA_17		 0xc01f

#define OP_PCL_SSL30_AES_256_CBC_SHA		 0x0035
#define OP_PCL_SSL30_AES_256_CBC_SHA_2		 0x0036
#define OP_PCL_SSL30_AES_256_CBC_SHA_3		 0x0037
#define OP_PCL_SSL30_AES_256_CBC_SHA_4		 0x0038
#define OP_PCL_SSL30_AES_256_CBC_SHA_5		 0x0039
#define OP_PCL_SSL30_AES_256_CBC_SHA_6		 0x003a
#define OP_PCL_SSL30_AES_256_CBC_SHA_7		 0x008d
#define OP_PCL_SSL30_AES_256_CBC_SHA_8		 0x0091
#define OP_PCL_SSL30_AES_256_CBC_SHA_9		 0x0095
#define OP_PCL_SSL30_AES_256_CBC_SHA_10		 0xc005
#define OP_PCL_SSL30_AES_256_CBC_SHA_11		 0xc00a
#define OP_PCL_SSL30_AES_256_CBC_SHA_12		 0xc00f
#define OP_PCL_SSL30_AES_256_CBC_SHA_13		 0xc014
#define OP_PCL_SSL30_AES_256_CBC_SHA_14		 0xc019
#define OP_PCL_SSL30_AES_256_CBC_SHA_15		 0xc020
#define OP_PCL_SSL30_AES_256_CBC_SHA_16		 0xc021
#define OP_PCL_SSL30_AES_256_CBC_SHA_17		 0xc022

#define OP_PCL_SSL30_AES_128_GCM_SHA256_1	 0x009C
#define OP_PCL_SSL30_AES_256_GCM_SHA384_1	 0x009D
#define OP_PCL_SSL30_AES_128_GCM_SHA256_2	 0x009E
#define OP_PCL_SSL30_AES_256_GCM_SHA384_2	 0x009F
#define OP_PCL_SSL30_AES_128_GCM_SHA256_3	 0x00A0
#define OP_PCL_SSL30_AES_256_GCM_SHA384_3	 0x00A1
#define OP_PCL_SSL30_AES_128_GCM_SHA256_4	 0x00A2
#define OP_PCL_SSL30_AES_256_GCM_SHA384_4	 0x00A3
#define OP_PCL_SSL30_AES_128_GCM_SHA256_5	 0x00A4
#define OP_PCL_SSL30_AES_256_GCM_SHA384_5	 0x00A5
#define OP_PCL_SSL30_AES_128_GCM_SHA256_6	 0x00A6

#define OP_PCL_TLS_DH_ANON_AES_256_GCM_SHA384	 0x00A7
#define OP_PCL_TLS_PSK_AES_128_GCM_SHA256	 0x00A8
#define OP_PCL_TLS_PSK_AES_256_GCM_SHA384	 0x00A9
#define OP_PCL_TLS_DHE_PSK_AES_128_GCM_SHA256	 0x00AA
#define OP_PCL_TLS_DHE_PSK_AES_256_GCM_SHA384	 0x00AB
#define OP_PCL_TLS_RSA_PSK_AES_128_GCM_SHA256	 0x00AC
#define OP_PCL_TLS_RSA_PSK_AES_256_GCM_SHA384	 0x00AD
#define OP_PCL_TLS_PSK_AES_128_CBC_SHA256	 0x00AE
#define OP_PCL_TLS_PSK_AES_256_CBC_SHA384	 0x00AF
#define OP_PCL_TLS_DHE_PSK_AES_128_CBC_SHA256	 0x00B2
#define OP_PCL_TLS_DHE_PSK_AES_256_CBC_SHA384	 0x00B3
#define OP_PCL_TLS_RSA_PSK_AES_128_CBC_SHA256	 0x00B6
#define OP_PCL_TLS_RSA_PSK_AES_256_CBC_SHA384	 0x00B7

#define OP_PCL_SSL30_3DES_EDE_CBC_MD5		 0x0023

#define OP_PCL_SSL30_3DES_EDE_CBC_SHA		 0x001f
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_2		 0x008b
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_3		 0x008f
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_4		 0x0093
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_5		 0x000a
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_6		 0x000d
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_7		 0x0010
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_8		 0x0013
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_9		 0x0016
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_10	 0x001b
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_11	 0xc003
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_12	 0xc008
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_13	 0xc00d
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_14	 0xc012
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_15	 0xc017
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_16	 0xc01a
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_17	 0xc01b
#define OP_PCL_SSL30_3DES_EDE_CBC_SHA_18	 0xc01c

#define OP_PCL_SSL30_DES40_CBC_MD5		 0x0029

#define OP_PCL_SSL30_DES_CBC_MD5		 0x0022

#define OP_PCL_SSL30_DES40_CBC_SHA		 0x0008
#define OP_PCL_SSL30_DES40_CBC_SHA_2		 0x000b
#define OP_PCL_SSL30_DES40_CBC_SHA_3		 0x000e
#define OP_PCL_SSL30_DES40_CBC_SHA_4		 0x0011
#define OP_PCL_SSL30_DES40_CBC_SHA_5		 0x0014
#define OP_PCL_SSL30_DES40_CBC_SHA_6		 0x0019
#define OP_PCL_SSL30_DES40_CBC_SHA_7		 0x0026

#define OP_PCL_SSL30_DES_CBC_SHA		 0x001e
#define OP_PCL_SSL30_DES_CBC_SHA_2		 0x0009
#define OP_PCL_SSL30_DES_CBC_SHA_3		 0x000c
#define OP_PCL_SSL30_DES_CBC_SHA_4		 0x000f
#define OP_PCL_SSL30_DES_CBC_SHA_5		 0x0012
#define OP_PCL_SSL30_DES_CBC_SHA_6		 0x0015
#define OP_PCL_SSL30_DES_CBC_SHA_7		 0x001a

#define OP_PCL_SSL30_RC4_128_MD5		 0x0024
#define OP_PCL_SSL30_RC4_128_MD5_2		 0x0004
#define OP_PCL_SSL30_RC4_128_MD5_3		 0x0018

#define OP_PCL_SSL30_RC4_40_MD5			 0x002b
#define OP_PCL_SSL30_RC4_40_MD5_2		 0x0003
#define OP_PCL_SSL30_RC4_40_MD5_3		 0x0017

#define OP_PCL_SSL30_RC4_128_SHA		 0x0020
#define OP_PCL_SSL30_RC4_128_SHA_2		 0x008a
#define OP_PCL_SSL30_RC4_128_SHA_3		 0x008e
#define OP_PCL_SSL30_RC4_128_SHA_4		 0x0092
#define OP_PCL_SSL30_RC4_128_SHA_5		 0x0005
#define OP_PCL_SSL30_RC4_128_SHA_6		 0xc002
#define OP_PCL_SSL30_RC4_128_SHA_7		 0xc007
#define OP_PCL_SSL30_RC4_128_SHA_8		 0xc00c
#define OP_PCL_SSL30_RC4_128_SHA_9		 0xc011
#define OP_PCL_SSL30_RC4_128_SHA_10		 0xc016

#define OP_PCL_SSL30_RC4_40_SHA			 0x0028

/* For TLS 1.0 - OP_PCLID_TLS10 */
#define OP_PCL_TLS10_AES_128_CBC_SHA		 0x002f
#define OP_PCL_TLS10_AES_128_CBC_SHA_2		 0x0030
#define OP_PCL_TLS10_AES_128_CBC_SHA_3		 0x0031
#define OP_PCL_TLS10_AES_128_CBC_SHA_4		 0x0032
#define OP_PCL_TLS10_AES_128_CBC_SHA_5		 0x0033
#define OP_PCL_TLS10_AES_128_CBC_SHA_6		 0x0034
#define OP_PCL_TLS10_AES_128_CBC_SHA_7		 0x008c
#define OP_PCL_TLS10_AES_128_CBC_SHA_8		 0x0090
#define OP_PCL_TLS10_AES_128_CBC_SHA_9		 0x0094
#define OP_PCL_TLS10_AES_128_CBC_SHA_10		 0xc004
#define OP_PCL_TLS10_AES_128_CBC_SHA_11		 0xc009
#define OP_PCL_TLS10_AES_128_CBC_SHA_12		 0xc00e
#define OP_PCL_TLS10_AES_128_CBC_SHA_13		 0xc013
#define OP_PCL_TLS10_AES_128_CBC_SHA_14		 0xc018
#define OP_PCL_TLS10_AES_128_CBC_SHA_15		 0xc01d
#define OP_PCL_TLS10_AES_128_CBC_SHA_16		 0xc01e
#define OP_PCL_TLS10_AES_128_CBC_SHA_17		 0xc01f

#define OP_PCL_TLS10_AES_256_CBC_SHA		 0x0035
#define OP_PCL_TLS10_AES_256_CBC_SHA_2		 0x0036
#define OP_PCL_TLS10_AES_256_CBC_SHA_3		 0x0037
#define OP_PCL_TLS10_AES_256_CBC_SHA_4		 0x0038
#define OP_PCL_TLS10_AES_256_CBC_SHA_5		 0x0039
#define OP_PCL_TLS10_AES_256_CBC_SHA_6		 0x003a
#define OP_PCL_TLS10_AES_256_CBC_SHA_7		 0x008d
#define OP_PCL_TLS10_AES_256_CBC_SHA_8		 0x0091
#define OP_PCL_TLS10_AES_256_CBC_SHA_9		 0x0095
#define OP_PCL_TLS10_AES_256_CBC_SHA_10		 0xc005
#define OP_PCL_TLS10_AES_256_CBC_SHA_11		 0xc00a
#define OP_PCL_TLS10_AES_256_CBC_SHA_12		 0xc00f
#define OP_PCL_TLS10_AES_256_CBC_SHA_13		 0xc014
#define OP_PCL_TLS10_AES_256_CBC_SHA_14		 0xc019
#define OP_PCL_TLS10_AES_256_CBC_SHA_15		 0xc020
#define OP_PCL_TLS10_AES_256_CBC_SHA_16		 0xc021
#define OP_PCL_TLS10_AES_256_CBC_SHA_17		 0xc022

#define OP_PCL_TLS_ECDHE_ECDSA_AES_128_CBC_SHA256  0xC023
#define OP_PCL_TLS_ECDHE_ECDSA_AES_256_CBC_SHA384  0xC024
#define OP_PCL_TLS_ECDH_ECDSA_AES_128_CBC_SHA256   0xC025
#define OP_PCL_TLS_ECDH_ECDSA_AES_256_CBC_SHA384   0xC026
#define OP_PCL_TLS_ECDHE_RSA_AES_128_CBC_SHA256	   0xC027
#define OP_PCL_TLS_ECDHE_RSA_AES_256_CBC_SHA384	   0xC028
#define OP_PCL_TLS_ECDH_RSA_AES_128_CBC_SHA256	   0xC029
#define OP_PCL_TLS_ECDH_RSA_AES_256_CBC_SHA384	   0xC02A
#define OP_PCL_TLS_ECDHE_ECDSA_AES_128_GCM_SHA256  0xC02B
#define OP_PCL_TLS_ECDHE_ECDSA_AES_256_GCM_SHA384  0xC02C
#define OP_PCL_TLS_ECDH_ECDSA_AES_128_GCM_SHA256   0xC02D
#define OP_PCL_TLS_ECDH_ECDSA_AES_256_GCM_SHA384   0xC02E
#define OP_PCL_TLS_ECDHE_RSA_AES_128_GCM_SHA256	   0xC02F
#define OP_PCL_TLS_ECDHE_RSA_AES_256_GCM_SHA384	   0xC030
#define OP_PCL_TLS_ECDH_RSA_AES_128_GCM_SHA256	   0xC031
#define OP_PCL_TLS_ECDH_RSA_AES_256_GCM_SHA384	   0xC032
#define OP_PCL_TLS_ECDHE_PSK_RC4_128_SHA	   0xC033
#define OP_PCL_TLS_ECDHE_PSK_3DES_EDE_CBC_SHA	   0xC034
#define OP_PCL_TLS_ECDHE_PSK_AES_128_CBC_SHA	   0xC035
#define OP_PCL_TLS_ECDHE_PSK_AES_256_CBC_SHA	   0xC036
#define OP_PCL_TLS_ECDHE_PSK_AES_128_CBC_SHA256	   0xC037
#define OP_PCL_TLS_ECDHE_PSK_AES_256_CBC_SHA384	   0xC038

/* #define OP_PCL_TLS10_3DES_EDE_CBC_MD5	0x0023 */

#define OP_PCL_TLS10_3DES_EDE_CBC_SHA		 0x001f
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_2		 0x008b
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_3		 0x008f
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_4		 0x0093
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_5		 0x000a
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_6		 0x000d
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_7		 0x0010
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_8		 0x0013
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_9		 0x0016
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_10	 0x001b
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_11	 0xc003
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_12	 0xc008
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_13	 0xc00d
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_14	 0xc012
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_15	 0xc017
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_16	 0xc01a
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_17	 0xc01b
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA_18	 0xc01c

#define OP_PCL_TLS10_DES40_CBC_MD5		 0x0029

#define OP_PCL_TLS10_DES_CBC_MD5		 0x0022

#define OP_PCL_TLS10_DES40_CBC_SHA		 0x0008
#define OP_PCL_TLS10_DES40_CBC_SHA_2		 0x000b
#define OP_PCL_TLS10_DES40_CBC_SHA_3		 0x000e
#define OP_PCL_TLS10_DES40_CBC_SHA_4		 0x0011
#define OP_PCL_TLS10_DES40_CBC_SHA_5		 0x0014
#define OP_PCL_TLS10_DES40_CBC_SHA_6		 0x0019
#define OP_PCL_TLS10_DES40_CBC_SHA_7		 0x0026

#define OP_PCL_TLS10_DES_CBC_SHA		 0x001e
#define OP_PCL_TLS10_DES_CBC_SHA_2		 0x0009
#define OP_PCL_TLS10_DES_CBC_SHA_3		 0x000c
#define OP_PCL_TLS10_DES_CBC_SHA_4		 0x000f
#define OP_PCL_TLS10_DES_CBC_SHA_5		 0x0012
#define OP_PCL_TLS10_DES_CBC_SHA_6		 0x0015
#define OP_PCL_TLS10_DES_CBC_SHA_7		 0x001a

#define OP_PCL_TLS10_RC4_128_MD5		 0x0024
#define OP_PCL_TLS10_RC4_128_MD5_2		 0x0004
#define OP_PCL_TLS10_RC4_128_MD5_3		 0x0018

#define OP_PCL_TLS10_RC4_40_MD5			 0x002b
#define OP_PCL_TLS10_RC4_40_MD5_2		 0x0003
#define OP_PCL_TLS10_RC4_40_MD5_3		 0x0017

#define OP_PCL_TLS10_RC4_128_SHA		 0x0020
#define OP_PCL_TLS10_RC4_128_SHA_2		 0x008a
#define OP_PCL_TLS10_RC4_128_SHA_3		 0x008e
#define OP_PCL_TLS10_RC4_128_SHA_4		 0x0092
#define OP_PCL_TLS10_RC4_128_SHA_5		 0x0005
#define OP_PCL_TLS10_RC4_128_SHA_6		 0xc002
#define OP_PCL_TLS10_RC4_128_SHA_7		 0xc007
#define OP_PCL_TLS10_RC4_128_SHA_8		 0xc00c
#define OP_PCL_TLS10_RC4_128_SHA_9		 0xc011
#define OP_PCL_TLS10_RC4_128_SHA_10		 0xc016

#define OP_PCL_TLS10_RC4_40_SHA			 0x0028

#define OP_PCL_TLS10_3DES_EDE_CBC_MD5		 0xff23
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA160	 0xff30
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA224	 0xff34
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA256	 0xff36
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA384	 0xff33
#define OP_PCL_TLS10_3DES_EDE_CBC_SHA512	 0xff35
#define OP_PCL_TLS10_AES_128_CBC_SHA160		 0xff80
#define OP_PCL_TLS10_AES_128_CBC_SHA224		 0xff84
#define OP_PCL_TLS10_AES_128_CBC_SHA256		 0xff86
#define OP_PCL_TLS10_AES_128_CBC_SHA384		 0xff83
#define OP_PCL_TLS10_AES_128_CBC_SHA512		 0xff85
#define OP_PCL_TLS10_AES_192_CBC_SHA160		 0xff20
#define OP_PCL_TLS10_AES_192_CBC_SHA224		 0xff24
#define OP_PCL_TLS10_AES_192_CBC_SHA256		 0xff26
#define OP_PCL_TLS10_AES_192_CBC_SHA384		 0xff23
#define OP_PCL_TLS10_AES_192_CBC_SHA512		 0xff25
#define OP_PCL_TLS10_AES_256_CBC_SHA160		 0xff60
#define OP_PCL_TLS10_AES_256_CBC_SHA224		 0xff64
#define OP_PCL_TLS10_AES_256_CBC_SHA256		 0xff66
#define OP_PCL_TLS10_AES_256_CBC_SHA384		 0xff63
#define OP_PCL_TLS10_AES_256_CBC_SHA512		 0xff65

#define OP_PCL_TLS_PVT_AES_192_CBC_SHA160	 0xff90
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA384	 0xff93
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA224	 0xff94
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA512	 0xff95
#define OP_PCL_TLS_PVT_AES_192_CBC_SHA256	 0xff96
#define OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FE	 0xfffe
#define OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FF	 0xffff

/* For TLS 1.1 - OP_PCLID_TLS11 */
#define OP_PCL_TLS11_AES_128_CBC_SHA		 0x002f
#define OP_PCL_TLS11_AES_128_CBC_SHA_2		 0x0030
#define OP_PCL_TLS11_AES_128_CBC_SHA_3		 0x0031
#define OP_PCL_TLS11_AES_128_CBC_SHA_4		 0x0032
#define OP_PCL_TLS11_AES_128_CBC_SHA_5		 0x0033
#define OP_PCL_TLS11_AES_128_CBC_SHA_6		 0x0034
#define OP_PCL_TLS11_AES_128_CBC_SHA_7		 0x008c
#define OP_PCL_TLS11_AES_128_CBC_SHA_8		 0x0090
#define OP_PCL_TLS11_AES_128_CBC_SHA_9		 0x0094
#define OP_PCL_TLS11_AES_128_CBC_SHA_10		 0xc004
#define OP_PCL_TLS11_AES_128_CBC_SHA_11		 0xc009
#define OP_PCL_TLS11_AES_128_CBC_SHA_12		 0xc00e
#define OP_PCL_TLS11_AES_128_CBC_SHA_13		 0xc013
#define OP_PCL_TLS11_AES_128_CBC_SHA_14		 0xc018
#define OP_PCL_TLS11_AES_128_CBC_SHA_15		 0xc01d
#define OP_PCL_TLS11_AES_128_CBC_SHA_16		 0xc01e
#define OP_PCL_TLS11_AES_128_CBC_SHA_17		 0xc01f

#define OP_PCL_TLS11_AES_256_CBC_SHA		 0x0035
#define OP_PCL_TLS11_AES_256_CBC_SHA_2		 0x0036
#define OP_PCL_TLS11_AES_256_CBC_SHA_3		 0x0037
#define OP_PCL_TLS11_AES_256_CBC_SHA_4		 0x0038
#define OP_PCL_TLS11_AES_256_CBC_SHA_5		 0x0039
#define OP_PCL_TLS11_AES_256_CBC_SHA_6		 0x003a
#define OP_PCL_TLS11_AES_256_CBC_SHA_7		 0x008d
#define OP_PCL_TLS11_AES_256_CBC_SHA_8		 0x0091
#define OP_PCL_TLS11_AES_256_CBC_SHA_9		 0x0095
#define OP_PCL_TLS11_AES_256_CBC_SHA_10		 0xc005
#define OP_PCL_TLS11_AES_256_CBC_SHA_11		 0xc00a
#define OP_PCL_TLS11_AES_256_CBC_SHA_12		 0xc00f
#define OP_PCL_TLS11_AES_256_CBC_SHA_13		 0xc014
#define OP_PCL_TLS11_AES_256_CBC_SHA_14		 0xc019
#define OP_PCL_TLS11_AES_256_CBC_SHA_15		 0xc020
#define OP_PCL_TLS11_AES_256_CBC_SHA_16		 0xc021
#define OP_PCL_TLS11_AES_256_CBC_SHA_17		 0xc022

/* #define OP_PCL_TLS11_3DES_EDE_CBC_MD5	0x0023 */

#define OP_PCL_TLS11_3DES_EDE_CBC_SHA		 0x001f
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_2		 0x008b
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_3		 0x008f
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_4		 0x0093
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_5		 0x000a
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_6		 0x000d
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_7		 0x0010
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_8		 0x0013
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_9		 0x0016
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_10	 0x001b
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_11	 0xc003
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_12	 0xc008
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_13	 0xc00d
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_14	 0xc012
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_15	 0xc017
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_16	 0xc01a
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_17	 0xc01b
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA_18	 0xc01c

#define OP_PCL_TLS11_DES40_CBC_MD5		 0x0029

#define OP_PCL_TLS11_DES_CBC_MD5		 0x0022

#define OP_PCL_TLS11_DES40_CBC_SHA		 0x0008
#define OP_PCL_TLS11_DES40_CBC_SHA_2		 0x000b
#define OP_PCL_TLS11_DES40_CBC_SHA_3		 0x000e
#define OP_PCL_TLS11_DES40_CBC_SHA_4		 0x0011
#define OP_PCL_TLS11_DES40_CBC_SHA_5		 0x0014
#define OP_PCL_TLS11_DES40_CBC_SHA_6		 0x0019
#define OP_PCL_TLS11_DES40_CBC_SHA_7		 0x0026

#define OP_PCL_TLS11_DES_CBC_SHA		 0x001e
#define OP_PCL_TLS11_DES_CBC_SHA_2		 0x0009
#define OP_PCL_TLS11_DES_CBC_SHA_3		 0x000c
#define OP_PCL_TLS11_DES_CBC_SHA_4		 0x000f
#define OP_PCL_TLS11_DES_CBC_SHA_5		 0x0012
#define OP_PCL_TLS11_DES_CBC_SHA_6		 0x0015
#define OP_PCL_TLS11_DES_CBC_SHA_7		 0x001a

#define OP_PCL_TLS11_RC4_128_MD5		 0x0024
#define OP_PCL_TLS11_RC4_128_MD5_2		 0x0004
#define OP_PCL_TLS11_RC4_128_MD5_3		 0x0018

#define OP_PCL_TLS11_RC4_40_MD5			 0x002b
#define OP_PCL_TLS11_RC4_40_MD5_2		 0x0003
#define OP_PCL_TLS11_RC4_40_MD5_3		 0x0017

#define OP_PCL_TLS11_RC4_128_SHA		 0x0020
#define OP_PCL_TLS11_RC4_128_SHA_2		 0x008a
#define OP_PCL_TLS11_RC4_128_SHA_3		 0x008e
#define OP_PCL_TLS11_RC4_128_SHA_4		 0x0092
#define OP_PCL_TLS11_RC4_128_SHA_5		 0x0005
#define OP_PCL_TLS11_RC4_128_SHA_6		 0xc002
#define OP_PCL_TLS11_RC4_128_SHA_7		 0xc007
#define OP_PCL_TLS11_RC4_128_SHA_8		 0xc00c
#define OP_PCL_TLS11_RC4_128_SHA_9		 0xc011
#define OP_PCL_TLS11_RC4_128_SHA_10		 0xc016

#define OP_PCL_TLS11_RC4_40_SHA			 0x0028

#define OP_PCL_TLS11_3DES_EDE_CBC_MD5		 0xff23
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA160	 0xff30
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA224	 0xff34
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA256	 0xff36
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA384	 0xff33
#define OP_PCL_TLS11_3DES_EDE_CBC_SHA512	 0xff35
#define OP_PCL_TLS11_AES_128_CBC_SHA160		 0xff80
#define OP_PCL_TLS11_AES_128_CBC_SHA224		 0xff84
#define OP_PCL_TLS11_AES_128_CBC_SHA256		 0xff86
#define OP_PCL_TLS11_AES_128_CBC_SHA384		 0xff83
#define OP_PCL_TLS11_AES_128_CBC_SHA512		 0xff85
#define OP_PCL_TLS11_AES_192_CBC_SHA160		 0xff20
#define OP_PCL_TLS11_AES_192_CBC_SHA224		 0xff24
#define OP_PCL_TLS11_AES_192_CBC_SHA256		 0xff26
#define OP_PCL_TLS11_AES_192_CBC_SHA384		 0xff23
#define OP_PCL_TLS11_AES_192_CBC_SHA512		 0xff25
#define OP_PCL_TLS11_AES_256_CBC_SHA160		 0xff60
#define OP_PCL_TLS11_AES_256_CBC_SHA224		 0xff64
#define OP_PCL_TLS11_AES_256_CBC_SHA256		 0xff66
#define OP_PCL_TLS11_AES_256_CBC_SHA384		 0xff63
#define OP_PCL_TLS11_AES_256_CBC_SHA512		 0xff65


/* For TLS 1.2 - OP_PCLID_TLS12 */
#define OP_PCL_TLS12_AES_128_CBC_SHA		 0x002f
#define OP_PCL_TLS12_AES_128_CBC_SHA_2		 0x0030
#define OP_PCL_TLS12_AES_128_CBC_SHA_3		 0x0031
#define OP_PCL_TLS12_AES_128_CBC_SHA_4		 0x0032
#define OP_PCL_TLS12_AES_128_CBC_SHA_5		 0x0033
#define OP_PCL_TLS12_AES_128_CBC_SHA_6		 0x0034
#define OP_PCL_TLS12_AES_128_CBC_SHA_7		 0x008c
#define OP_PCL_TLS12_AES_128_CBC_SHA_8		 0x0090
#define OP_PCL_TLS12_AES_128_CBC_SHA_9		 0x0094
#define OP_PCL_TLS12_AES_128_CBC_SHA_10		 0xc004
#define OP_PCL_TLS12_AES_128_CBC_SHA_11		 0xc009
#define OP_PCL_TLS12_AES_128_CBC_SHA_12		 0xc00e
#define OP_PCL_TLS12_AES_128_CBC_SHA_13		 0xc013
#define OP_PCL_TLS12_AES_128_CBC_SHA_14		 0xc018
#define OP_PCL_TLS12_AES_128_CBC_SHA_15		 0xc01d
#define OP_PCL_TLS12_AES_128_CBC_SHA_16		 0xc01e
#define OP_PCL_TLS12_AES_128_CBC_SHA_17		 0xc01f

#define OP_PCL_TLS12_AES_256_CBC_SHA		 0x0035
#define OP_PCL_TLS12_AES_256_CBC_SHA_2		 0x0036
#define OP_PCL_TLS12_AES_256_CBC_SHA_3		 0x0037
#define OP_PCL_TLS12_AES_256_CBC_SHA_4		 0x0038
#define OP_PCL_TLS12_AES_256_CBC_SHA_5		 0x0039
#define OP_PCL_TLS12_AES_256_CBC_SHA_6		 0x003a
#define OP_PCL_TLS12_AES_256_CBC_SHA_7		 0x008d
#define OP_PCL_TLS12_AES_256_CBC_SHA_8		 0x0091
#define OP_PCL_TLS12_AES_256_CBC_SHA_9		 0x0095
#define OP_PCL_TLS12_AES_256_CBC_SHA_10		 0xc005
#define OP_PCL_TLS12_AES_256_CBC_SHA_11		 0xc00a
#define OP_PCL_TLS12_AES_256_CBC_SHA_12		 0xc00f
#define OP_PCL_TLS12_AES_256_CBC_SHA_13		 0xc014
#define OP_PCL_TLS12_AES_256_CBC_SHA_14		 0xc019
#define OP_PCL_TLS12_AES_256_CBC_SHA_15		 0xc020
#define OP_PCL_TLS12_AES_256_CBC_SHA_16		 0xc021
#define OP_PCL_TLS12_AES_256_CBC_SHA_17		 0xc022

/* #define OP_PCL_TLS12_3DES_EDE_CBC_MD5	0x0023 */

#define OP_PCL_TLS12_3DES_EDE_CBC_SHA		 0x001f
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_2		 0x008b
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_3		 0x008f
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_4		 0x0093
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_5		 0x000a
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_6		 0x000d
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_7		 0x0010
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_8		 0x0013
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_9		 0x0016
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_10	 0x001b
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_11	 0xc003
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_12	 0xc008
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_13	 0xc00d
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_14	 0xc012
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_15	 0xc017
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_16	 0xc01a
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_17	 0xc01b
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA_18	 0xc01c

#define OP_PCL_TLS12_DES40_CBC_MD5		 0x0029

#define OP_PCL_TLS12_DES_CBC_MD5		 0x0022

#define OP_PCL_TLS12_DES40_CBC_SHA		 0x0008
#define OP_PCL_TLS12_DES40_CBC_SHA_2		 0x000b
#define OP_PCL_TLS12_DES40_CBC_SHA_3		 0x000e
#define OP_PCL_TLS12_DES40_CBC_SHA_4		 0x0011
#define OP_PCL_TLS12_DES40_CBC_SHA_5		 0x0014
#define OP_PCL_TLS12_DES40_CBC_SHA_6		 0x0019
#define OP_PCL_TLS12_DES40_CBC_SHA_7		 0x0026

#define OP_PCL_TLS12_DES_CBC_SHA		 0x001e
#define OP_PCL_TLS12_DES_CBC_SHA_2		 0x0009
#define OP_PCL_TLS12_DES_CBC_SHA_3		 0x000c
#define OP_PCL_TLS12_DES_CBC_SHA_4		 0x000f
#define OP_PCL_TLS12_DES_CBC_SHA_5		 0x0012
#define OP_PCL_TLS12_DES_CBC_SHA_6		 0x0015
#define OP_PCL_TLS12_DES_CBC_SHA_7		 0x001a

#define OP_PCL_TLS12_RC4_128_MD5		 0x0024
#define OP_PCL_TLS12_RC4_128_MD5_2		 0x0004
#define OP_PCL_TLS12_RC4_128_MD5_3		 0x0018

#define OP_PCL_TLS12_RC4_40_MD5			 0x002b
#define OP_PCL_TLS12_RC4_40_MD5_2		 0x0003
#define OP_PCL_TLS12_RC4_40_MD5_3		 0x0017

#define OP_PCL_TLS12_RC4_128_SHA		 0x0020
#define OP_PCL_TLS12_RC4_128_SHA_2		 0x008a
#define OP_PCL_TLS12_RC4_128_SHA_3		 0x008e
#define OP_PCL_TLS12_RC4_128_SHA_4		 0x0092
#define OP_PCL_TLS12_RC4_128_SHA_5		 0x0005
#define OP_PCL_TLS12_RC4_128_SHA_6		 0xc002
#define OP_PCL_TLS12_RC4_128_SHA_7		 0xc007
#define OP_PCL_TLS12_RC4_128_SHA_8		 0xc00c
#define OP_PCL_TLS12_RC4_128_SHA_9		 0xc011
#define OP_PCL_TLS12_RC4_128_SHA_10		 0xc016

#define OP_PCL_TLS12_RC4_40_SHA			 0x0028

/* #define OP_PCL_TLS12_AES_128_CBC_SHA256	0x003c */
#define OP_PCL_TLS12_AES_128_CBC_SHA256_2	 0x003e
#define OP_PCL_TLS12_AES_128_CBC_SHA256_3	 0x003f
#define OP_PCL_TLS12_AES_128_CBC_SHA256_4	 0x0040
#define OP_PCL_TLS12_AES_128_CBC_SHA256_5	 0x0067
#define OP_PCL_TLS12_AES_128_CBC_SHA256_6	 0x006c

/* #define OP_PCL_TLS12_AES_256_CBC_SHA256	0x003d */
#define OP_PCL_TLS12_AES_256_CBC_SHA256_2	 0x0068
#define OP_PCL_TLS12_AES_256_CBC_SHA256_3	 0x0069
#define OP_PCL_TLS12_AES_256_CBC_SHA256_4	 0x006a
#define OP_PCL_TLS12_AES_256_CBC_SHA256_5	 0x006b
#define OP_PCL_TLS12_AES_256_CBC_SHA256_6	 0x006d

/* AEAD_AES_xxx_CCM/GCM remain to be defined... */

#define OP_PCL_TLS12_3DES_EDE_CBC_MD5		 0xff23
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA160	 0xff30
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA224	 0xff34
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA256	 0xff36
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA384	 0xff33
#define OP_PCL_TLS12_3DES_EDE_CBC_SHA512	 0xff35
#define OP_PCL_TLS12_AES_128_CBC_SHA160		 0xff80
#define OP_PCL_TLS12_AES_128_CBC_SHA224		 0xff84
#define OP_PCL_TLS12_AES_128_CBC_SHA256		 0xff86
#define OP_PCL_TLS12_AES_128_CBC_SHA384		 0xff83
#define OP_PCL_TLS12_AES_128_CBC_SHA512		 0xff85
#define OP_PCL_TLS12_AES_192_CBC_SHA160		 0xff20
#define OP_PCL_TLS12_AES_192_CBC_SHA224		 0xff24
#define OP_PCL_TLS12_AES_192_CBC_SHA256		 0xff26
#define OP_PCL_TLS12_AES_192_CBC_SHA384		 0xff23
#define OP_PCL_TLS12_AES_192_CBC_SHA512		 0xff25
#define OP_PCL_TLS12_AES_256_CBC_SHA160		 0xff60
#define OP_PCL_TLS12_AES_256_CBC_SHA224		 0xff64
#define OP_PCL_TLS12_AES_256_CBC_SHA256		 0xff66
#define OP_PCL_TLS12_AES_256_CBC_SHA384		 0xff63
#define OP_PCL_TLS12_AES_256_CBC_SHA512		 0xff65

/* For DTLS - OP_PCLID_DTLS */

#define OP_PCL_DTLS_AES_128_CBC_SHA		 0x002f
#define OP_PCL_DTLS_AES_128_CBC_SHA_2		 0x0030
#define OP_PCL_DTLS_AES_128_CBC_SHA_3		 0x0031
#define OP_PCL_DTLS_AES_128_CBC_SHA_4		 0x0032
#define OP_PCL_DTLS_AES_128_CBC_SHA_5		 0x0033
#define OP_PCL_DTLS_AES_128_CBC_SHA_6		 0x0034
#define OP_PCL_DTLS_AES_128_CBC_SHA_7		 0x008c
#define OP_PCL_DTLS_AES_128_CBC_SHA_8		 0x0090
#define OP_PCL_DTLS_AES_128_CBC_SHA_9		 0x0094
#define OP_PCL_DTLS_AES_128_CBC_SHA_10		 0xc004
#define OP_PCL_DTLS_AES_128_CBC_SHA_11		 0xc009
#define OP_PCL_DTLS_AES_128_CBC_SHA_12		 0xc00e
#define OP_PCL_DTLS_AES_128_CBC_SHA_13		 0xc013
#define OP_PCL_DTLS_AES_128_CBC_SHA_14		 0xc018
#define OP_PCL_DTLS_AES_128_CBC_SHA_15		 0xc01d
#define OP_PCL_DTLS_AES_128_CBC_SHA_16		 0xc01e
#define OP_PCL_DTLS_AES_128_CBC_SHA_17		 0xc01f

#define OP_PCL_DTLS_AES_256_CBC_SHA		 0x0035
#define OP_PCL_DTLS_AES_256_CBC_SHA_2		 0x0036
#define OP_PCL_DTLS_AES_256_CBC_SHA_3		 0x0037
#define OP_PCL_DTLS_AES_256_CBC_SHA_4		 0x0038
#define OP_PCL_DTLS_AES_256_CBC_SHA_5		 0x0039
#define OP_PCL_DTLS_AES_256_CBC_SHA_6		 0x003a
#define OP_PCL_DTLS_AES_256_CBC_SHA_7		 0x008d
#define OP_PCL_DTLS_AES_256_CBC_SHA_8		 0x0091
#define OP_PCL_DTLS_AES_256_CBC_SHA_9		 0x0095
#define OP_PCL_DTLS_AES_256_CBC_SHA_10		 0xc005
#define OP_PCL_DTLS_AES_256_CBC_SHA_11		 0xc00a
#define OP_PCL_DTLS_AES_256_CBC_SHA_12		 0xc00f
#define OP_PCL_DTLS_AES_256_CBC_SHA_13		 0xc014
#define OP_PCL_DTLS_AES_256_CBC_SHA_14		 0xc019
#define OP_PCL_DTLS_AES_256_CBC_SHA_15		 0xc020
#define OP_PCL_DTLS_AES_256_CBC_SHA_16		 0xc021
#define OP_PCL_DTLS_AES_256_CBC_SHA_17		 0xc022

/* #define OP_PCL_DTLS_3DES_EDE_CBC_MD5		0x0023 */

#define OP_PCL_DTLS_3DES_EDE_CBC_SHA		 0x001f
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_2		 0x008b
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_3		 0x008f
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_4		 0x0093
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_5		 0x000a
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_6		 0x000d
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_7		 0x0010
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_8		 0x0013
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_9		 0x0016
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_10		 0x001b
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_11		 0xc003
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_12		 0xc008
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_13		 0xc00d
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_14		 0xc012
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_15		 0xc017
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_16		 0xc01a
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_17		 0xc01b
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA_18		 0xc01c

#define OP_PCL_DTLS_DES40_CBC_MD5		 0x0029

#define OP_PCL_DTLS_DES_CBC_MD5			 0x0022

#define OP_PCL_DTLS_DES40_CBC_SHA		 0x0008
#define OP_PCL_DTLS_DES40_CBC_SHA_2		 0x000b
#define OP_PCL_DTLS_DES40_CBC_SHA_3		 0x000e
#define OP_PCL_DTLS_DES40_CBC_SHA_4		 0x0011
#define OP_PCL_DTLS_DES40_CBC_SHA_5		 0x0014
#define OP_PCL_DTLS_DES40_CBC_SHA_6		 0x0019
#define OP_PCL_DTLS_DES40_CBC_SHA_7		 0x0026


#define OP_PCL_DTLS_DES_CBC_SHA			 0x001e
#define OP_PCL_DTLS_DES_CBC_SHA_2		 0x0009
#define OP_PCL_DTLS_DES_CBC_SHA_3		 0x000c
#define OP_PCL_DTLS_DES_CBC_SHA_4		 0x000f
#define OP_PCL_DTLS_DES_CBC_SHA_5		 0x0012
#define OP_PCL_DTLS_DES_CBC_SHA_6		 0x0015
#define OP_PCL_DTLS_DES_CBC_SHA_7		 0x001a

#define OP_PCL_DTLS_3DES_EDE_CBC_MD5		 0xff23
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA160		 0xff30
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA224		 0xff34
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA256		 0xff36
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA384		 0xff33
#define OP_PCL_DTLS_3DES_EDE_CBC_SHA512		 0xff35
#define OP_PCL_DTLS_AES_128_CBC_SHA160		 0xff80
#define OP_PCL_DTLS_AES_128_CBC_SHA224		 0xff84
#define OP_PCL_DTLS_AES_128_CBC_SHA256		 0xff86
#define OP_PCL_DTLS_AES_128_CBC_SHA384		 0xff83
#define OP_PCL_DTLS_AES_128_CBC_SHA512		 0xff85
#define OP_PCL_DTLS_AES_192_CBC_SHA160		 0xff20
#define OP_PCL_DTLS_AES_192_CBC_SHA224		 0xff24
#define OP_PCL_DTLS_AES_192_CBC_SHA256		 0xff26
#define OP_PCL_DTLS_AES_192_CBC_SHA384		 0xff23
#define OP_PCL_DTLS_AES_192_CBC_SHA512		 0xff25
#define OP_PCL_DTLS_AES_256_CBC_SHA160		 0xff60
#define OP_PCL_DTLS_AES_256_CBC_SHA224		 0xff64
#define OP_PCL_DTLS_AES_256_CBC_SHA256		 0xff66
#define OP_PCL_DTLS_AES_256_CBC_SHA384		 0xff63
#define OP_PCL_DTLS_AES_256_CBC_SHA512		 0xff65

/* 802.16 WiMAX protinfos */
#define OP_PCL_WIMAX_OFDM			 0x0201
#define OP_PCL_WIMAX_OFDMA			 0x0231

/* 802.11 WiFi protinfos */
#define OP_PCL_WIFI				 0xac04

/* MacSec protinfos */
#define OP_PCL_MACSEC				 0x0001

/* 3G DCRC protinfos */
#define OP_PCL_3G_DCRC_CRC7			 0x0710
#define OP_PCL_3G_DCRC_CRC11			 0x0B10

/* 3G RLC protinfos */
#define OP_PCL_3G_RLC_NULL			 0x0000
#define OP_PCL_3G_RLC_KASUMI			 0x0001
#define OP_PCL_3G_RLC_SNOW			 0x0002

/* LTE protinfos */
#define OP_PCL_LTE_NULL				 0x0000
#define OP_PCL_LTE_SNOW				 0x0001
#define OP_PCL_LTE_AES				 0x0002
#define OP_PCL_LTE_ZUC				 0x0003

/* LTE mixed protinfos */
#define OP_PCL_LTE_MIXED_AUTH_SHIFT	0
#define OP_PCL_LTE_MIXED_AUTH_MASK	(3 << OP_PCL_LTE_MIXED_AUTH_SHIFT)
#define OP_PCL_LTE_MIXED_ENC_SHIFT	8
#define OP_PCL_LTE_MIXED_ENC_MASK	(3 < OP_PCL_LTE_MIXED_ENC_SHIFT)
#define OP_PCL_LTE_MIXED_AUTH_NULL	(OP_PCL_LTE_NULL << \
					 OP_PCL_LTE_MIXED_AUTH_SHIFT)
#define OP_PCL_LTE_MIXED_AUTH_SNOW	(OP_PCL_LTE_SNOW << \
					 OP_PCL_LTE_MIXED_AUTH_SHIFT)
#define OP_PCL_LTE_MIXED_AUTH_AES	(OP_PCL_LTE_AES << \
					 OP_PCL_LTE_MIXED_AUTH_SHIFT)
#define OP_PCL_LTE_MIXED_AUTH_ZUC	(OP_PCL_LTE_ZUC << \
					 OP_PCL_LTE_MIXED_AUTH_SHIFT)
#define OP_PCL_LTE_MIXED_ENC_NULL	(OP_PCL_LTE_NULL << \
					 OP_PCL_LTE_MIXED_ENC_SHIFT)
#define OP_PCL_LTE_MIXED_ENC_SNOW	(OP_PCL_LTE_SNOW << \
					 OP_PCL_LTE_MIXED_ENC_SHIFT)
#define OP_PCL_LTE_MIXED_ENC_AES	(OP_PCL_LTE_AES << \
					 OP_PCL_LTE_MIXED_ENC_SHIFT)
#define OP_PCL_LTE_MIXED_ENC_ZUC	(OP_PCL_LTE_ZUC << \
					 OP_PCL_LTE_MIXED_ENC_SHIFT)

/* PKI unidirectional protocol protinfo bits */
#define OP_PCL_PKPROT_DSA_MSG		BIT(10)
#define OP_PCL_PKPROT_HASH_SHIFT	7
#define OP_PCL_PKPROT_HASH_MASK		(7 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_MD5		(0 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA1		(1 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA224	(2 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA256	(3 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA384	(4 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_HASH_SHA512	(5 << OP_PCL_PKPROT_HASH_SHIFT)
#define OP_PCL_PKPROT_EKT_Z		BIT(6)
#define OP_PCL_PKPROT_DECRYPT_Z		BIT(5)
#define OP_PCL_PKPROT_EKT_PRI		BIT(4)
#define OP_PCL_PKPROT_TEST		BIT(3)
#define OP_PCL_PKPROT_DECRYPT_PRI	BIT(2)
#define OP_PCL_PKPROT_ECC		BIT(1)
#define OP_PCL_PKPROT_F2M		BIT(0)

/* Blob protinfos */
#define OP_PCL_BLOB_TKEK_SHIFT		9
#define OP_PCL_BLOB_TKEK		BIT(9)
#define OP_PCL_BLOB_EKT_SHIFT		8
#define OP_PCL_BLOB_EKT			BIT(8)
#define OP_PCL_BLOB_REG_SHIFT		4
#define OP_PCL_BLOB_REG_MASK		(0xF << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_MEMORY		(0x0 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_KEY1		(0x1 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_KEY2		(0x3 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_AFHA_SBOX		(0x5 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_SPLIT		(0x7 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_REG_PKE		(0x9 << OP_PCL_BLOB_REG_SHIFT)
#define OP_PCL_BLOB_SEC_MEM_SHIFT	3
#define OP_PCL_BLOB_SEC_MEM		BIT(3)
#define OP_PCL_BLOB_BLACK		BIT(2)
#define OP_PCL_BLOB_FORMAT_SHIFT	0
#define OP_PCL_BLOB_FORMAT_MASK		0x3
#define OP_PCL_BLOB_FORMAT_NORMAL	0
#define OP_PCL_BLOB_FORMAT_MASTER_VER	2
#define OP_PCL_BLOB_FORMAT_TEST		3

/* IKE / IKEv2 protinfos */
#define OP_PCL_IKE_HMAC_MD5		0x0100
#define OP_PCL_IKE_HMAC_SHA1		0x0200
#define OP_PCL_IKE_HMAC_AES128_CBC	0x0400
#define OP_PCL_IKE_HMAC_SHA256		0x0500
#define OP_PCL_IKE_HMAC_SHA384		0x0600
#define OP_PCL_IKE_HMAC_SHA512		0x0700
#define OP_PCL_IKE_HMAC_AES128_CMAC	0x0800

/* PKI unidirectional protocol protinfo bits */
#define OP_PCL_PKPROT_TEST		BIT(3)
#define OP_PCL_PKPROT_DECRYPT		BIT(2)
#define OP_PCL_PKPROT_ECC		BIT(1)
#define OP_PCL_PKPROT_F2M		BIT(0)

/* RSA Protinfo */
#define OP_PCL_RSAPROT_OP_MASK		3
#define OP_PCL_RSAPROT_OP_ENC_F_IN	0
#define OP_PCL_RSAPROT_OP_ENC_F_OUT	1
#define OP_PCL_RSAPROT_OP_DEC_ND	0
#define OP_PCL_RSAPROT_OP_DEC_PQD	1
#define OP_PCL_RSAPROT_OP_DEC_PQDPDQC	2
#define OP_PCL_RSAPROT_FFF_SHIFT	4
#define OP_PCL_RSAPROT_FFF_MASK		(7 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_RED		(0 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_ENC		(1 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_TK_ENC	(5 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_EKT		(3 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_FFF_TK_EKT	(7 << OP_PCL_RSAPROT_FFF_SHIFT)
#define OP_PCL_RSAPROT_PPP_SHIFT	8
#define OP_PCL_RSAPROT_PPP_MASK		(7 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_RED		(0 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_ENC		(1 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_TK_ENC	(5 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_EKT		(3 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_PPP_TK_EKT	(7 << OP_PCL_RSAPROT_PPP_SHIFT)
#define OP_PCL_RSAPROT_FMT_PKCSV15	BIT(12)

/* Derived Key Protocol (DKP) Protinfo */
#define OP_PCL_DKP_SRC_SHIFT	14
#define OP_PCL_DKP_SRC_MASK	(3 << OP_PCL_DKP_SRC_SHIFT)
#define OP_PCL_DKP_SRC_IMM	(0 << OP_PCL_DKP_SRC_SHIFT)
#define OP_PCL_DKP_SRC_SEQ	(1 << OP_PCL_DKP_SRC_SHIFT)
#define OP_PCL_DKP_SRC_PTR	(2 << OP_PCL_DKP_SRC_SHIFT)
#define OP_PCL_DKP_SRC_SGF	(3 << OP_PCL_DKP_SRC_SHIFT)
#define OP_PCL_DKP_DST_SHIFT	12
#define OP_PCL_DKP_DST_MASK	(3 << OP_PCL_DKP_DST_SHIFT)
#define OP_PCL_DKP_DST_IMM	(0 << OP_PCL_DKP_DST_SHIFT)
#define OP_PCL_DKP_DST_SEQ	(1 << OP_PCL_DKP_DST_SHIFT)
#define OP_PCL_DKP_DST_PTR	(2 << OP_PCL_DKP_DST_SHIFT)
#define OP_PCL_DKP_DST_SGF	(3 << OP_PCL_DKP_DST_SHIFT)
#define OP_PCL_DKP_KEY_SHIFT	0
#define OP_PCL_DKP_KEY_MASK	(0xfff << OP_PCL_DKP_KEY_SHIFT)

/* For non-protocol/alg-only op commands */
#define OP_ALG_TYPE_SHIFT	24
#define OP_ALG_TYPE_MASK	(0x7 << OP_ALG_TYPE_SHIFT)
#define OP_ALG_TYPE_CLASS1	(0x2 << OP_ALG_TYPE_SHIFT)
#define OP_ALG_TYPE_CLASS2	(0x4 << OP_ALG_TYPE_SHIFT)

#define OP_ALG_ALGSEL_SHIFT	16
#define OP_ALG_ALGSEL_MASK	(0xff << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SUBMASK	(0x0f << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_AES	(0x10 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_DES	(0x20 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_3DES	(0x21 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_ARC4	(0x30 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_MD5	(0x40 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA1	(0x41 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA224	(0x42 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA256	(0x43 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA384	(0x44 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SHA512	(0x45 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_RNG	(0x50 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SNOW_F8	(0x60 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_KASUMI	(0x70 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_CRC	(0x90 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_SNOW_F9	(0xA0 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_ZUCE	(0xB0 << OP_ALG_ALGSEL_SHIFT)
#define OP_ALG_ALGSEL_ZUCA	(0xC0 << OP_ALG_ALGSEL_SHIFT)

#define OP_ALG_AAI_SHIFT	4
#define OP_ALG_AAI_MASK		(0x3ff << OP_ALG_AAI_SHIFT)

/* block cipher AAI set */
#define OP_ALG_AESA_MODE_MASK	(0xF0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR		(0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD128	(0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD8	(0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD16	(0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD24	(0x03 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD32	(0x04 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD40	(0x05 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD48	(0x06 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD56	(0x07 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD64	(0x08 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD72	(0x09 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD80	(0x0a << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD88	(0x0b << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD96	(0x0c << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD104	(0x0d << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD112	(0x0e << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_MOD120	(0x0f << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC		(0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_ECB		(0x20 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CFB		(0x30 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_OFB		(0x40 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_XTS		(0x50 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CMAC		(0x60 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_XCBC_MAC	(0x70 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CCM		(0x80 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_GCM		(0x90 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC_XCBCMAC	(0xa0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_XCBCMAC	(0xb0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CBC_CMAC	(0xc0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_CMAC_LTE (0xd0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CTR_CMAC	(0xe0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CHECKODD	(0x80 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DK		(0x100 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_C2K		(0x200 << OP_ALG_AAI_SHIFT)

/* randomizer AAI set */
#define OP_ALG_RNG_MODE_MASK	(0x30 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG		(0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_NZB	(0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG_OBP	(0x20 << OP_ALG_AAI_SHIFT)

/* RNG4 AAI set */
#define OP_ALG_AAI_RNG4_SH_SHIFT OP_ALG_AAI_SHIFT
#define OP_ALG_AAI_RNG4_SH_MASK	(0x03 << OP_ALG_AAI_RNG4_SH_SHIFT)
#define OP_ALG_AAI_RNG4_SH_0	(0x00 << OP_ALG_AAI_RNG4_SH_SHIFT)
#define OP_ALG_AAI_RNG4_SH_1	(0x01 << OP_ALG_AAI_RNG4_SH_SHIFT)
#define OP_ALG_AAI_RNG4_PS	(0x40 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG4_AI	(0x80 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_RNG4_SK	(0x100 << OP_ALG_AAI_SHIFT)

/* hmac/smac AAI set */
#define OP_ALG_AAI_HASH		(0x00 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_HMAC		(0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_SMAC		(0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_HMAC_PRECOMP	(0x04 << OP_ALG_AAI_SHIFT)

/* CRC AAI set*/
#define OP_ALG_CRC_POLY_MASK	(0x07 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_802		(0x01 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_3385		(0x02 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_CUST_POLY	(0x04 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DIS		(0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DOS		(0x20 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_DOC		(0x40 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_IVZ		(0x80 << OP_ALG_AAI_SHIFT)

/* Kasumi/SNOW/ZUC AAI set */
#define OP_ALG_AAI_F8		(0xc0 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_F9		(0xc8 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_GSM		(0x10 << OP_ALG_AAI_SHIFT)
#define OP_ALG_AAI_EDGE		(0x20 << OP_ALG_AAI_SHIFT)

#define OP_ALG_AS_SHIFT		2
#define OP_ALG_AS_MASK		(0x3 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_UPDATE	(0 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_INIT		(1 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_FINALIZE	(2 << OP_ALG_AS_SHIFT)
#define OP_ALG_AS_INITFINAL	(3 << OP_ALG_AS_SHIFT)

#define OP_ALG_ICV_SHIFT	1
#define OP_ALG_ICV_MASK		(1 << OP_ALG_ICV_SHIFT)
#define OP_ALG_ICV_OFF		0
#define OP_ALG_ICV_ON		BIT(1)

#define OP_ALG_DIR_SHIFT	0
#define OP_ALG_DIR_MASK		1
#define OP_ALG_DECRYPT		0
#define OP_ALG_ENCRYPT		BIT(0)

/* PKHA algorithm type set */
#define OP_ALG_PK			0x00800000
#define OP_ALG_PK_FUN_MASK		0x3f /* clrmem, modmath, or cpymem */

/* PKHA mode clear memory functions */
#define OP_ALG_PKMODE_A_RAM		BIT(19)
#define OP_ALG_PKMODE_B_RAM		BIT(18)
#define OP_ALG_PKMODE_E_RAM		BIT(17)
#define OP_ALG_PKMODE_N_RAM		BIT(16)
#define OP_ALG_PKMODE_CLEARMEM		BIT(0)

/* PKHA mode clear memory functions */
#define OP_ALG_PKMODE_CLEARMEM_ALL	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_N_RAM | \
					 OP_ALG_PKMODE_E_RAM)
#define OP_ALG_PKMODE_CLEARMEM_ABE	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_E_RAM)
#define OP_ALG_PKMODE_CLEARMEM_ABN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_AB	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_B_RAM)
#define OP_ALG_PKMODE_CLEARMEM_AEN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_E_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_AE	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_E_RAM)
#define OP_ALG_PKMODE_CLEARMEM_AN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_A	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_A_RAM)
#define OP_ALG_PKMODE_CLEARMEM_BEN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_E_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_BE	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_E_RAM)
#define OP_ALG_PKMODE_CLEARMEM_BN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_B_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_B	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_B_RAM)
#define OP_ALG_PKMODE_CLEARMEM_EN	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_E_RAM | \
					 OP_ALG_PKMODE_N_RAM)
#define OP_ALG_PKMODE_CLEARMEM_E	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_E_RAM)
#define OP_ALG_PKMODE_CLEARMEM_N	(OP_ALG_PKMODE_CLEARMEM | \
					 OP_ALG_PKMODE_N_RAM)

/* PKHA mode modular-arithmetic functions */
#define OP_ALG_PKMODE_MOD_IN_MONTY   BIT(19)
#define OP_ALG_PKMODE_MOD_OUT_MONTY  BIT(18)
#define OP_ALG_PKMODE_MOD_F2M	     BIT(17)
#define OP_ALG_PKMODE_MOD_R2_IN	     BIT(16)
#define OP_ALG_PKMODE_PRJECTV	     BIT(11)
#define OP_ALG_PKMODE_TIME_EQ	     BIT(10)

#define OP_ALG_PKMODE_OUT_B	     0x000
#define OP_ALG_PKMODE_OUT_A	     0x100

/*
 * PKHA mode modular-arithmetic integer functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_MOD_ADD	     0x002
#define OP_ALG_PKMODE_MOD_SUB_AB     0x003
#define OP_ALG_PKMODE_MOD_SUB_BA     0x004
#define OP_ALG_PKMODE_MOD_MULT	     0x005
#define OP_ALG_PKMODE_MOD_MULT_IM    (0x005 | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_MOD_MULT_IM_OM (0x005 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY)
#define OP_ALG_PKMODE_MOD_EXPO	     0x006
#define OP_ALG_PKMODE_MOD_EXPO_TEQ   (0x006 | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_MOD_EXPO_IM    (0x006 | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_MOD_EXPO_IM_TEQ (0x006 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_MOD_REDUCT     0x007
#define OP_ALG_PKMODE_MOD_INV	     0x008
#define OP_ALG_PKMODE_MOD_ECC_ADD    0x009
#define OP_ALG_PKMODE_MOD_ECC_DBL    0x00a
#define OP_ALG_PKMODE_MOD_ECC_MULT   0x00b
#define OP_ALG_PKMODE_MOD_MONT_CNST  0x00c
#define OP_ALG_PKMODE_MOD_CRT_CNST   0x00d
#define OP_ALG_PKMODE_MOD_GCD	     0x00e
#define OP_ALG_PKMODE_MOD_PRIMALITY  0x00f
#define OP_ALG_PKMODE_MOD_SML_EXP    0x016

/*
 * PKHA mode modular-arithmetic F2m functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_F2M_ADD	     (0x002 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_MUL	     (0x005 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_MUL_IM     (0x005 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY)
#define OP_ALG_PKMODE_F2M_MUL_IM_OM  (0x005 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY)
#define OP_ALG_PKMODE_F2M_EXP	     (0x006 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_EXP_TEQ    (0x006 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_F2M_AMODN	     (0x007 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_INV	     (0x008 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_R2	     (0x00c | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_GCD	     (0x00e | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_F2M_SML_EXP    (0x016 | OP_ALG_PKMODE_MOD_F2M)

/*
 * PKHA mode ECC Integer arithmetic functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_ECC_MOD_ADD    0x009
#define OP_ALG_PKMODE_ECC_MOD_ADD_IM_OM_PROJ \
				     (0x009 | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_DBL    0x00a
#define OP_ALG_PKMODE_ECC_MOD_DBL_IM_OM_PROJ \
				     (0x00a | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_MUL    0x00b
#define OP_ALG_PKMODE_ECC_MOD_MUL_TEQ (0x00b | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2  (0x00b | OP_ALG_PKMODE_MOD_R2_IN)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_MOD_MUL_R2_PROJ_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV \
					    | OP_ALG_PKMODE_TIME_EQ)

/*
 * PKHA mode ECC F2m arithmetic functions
 * Can be ORed with OP_ALG_PKMODE_OUT_A to change destination from B
 */
#define OP_ALG_PKMODE_ECC_F2M_ADD    (0x009 | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_ADD_IM_OM_PROJ \
				     (0x009 | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_DBL    (0x00a | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_DBL_IM_OM_PROJ \
				     (0x00a | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_IN_MONTY \
					    | OP_ALG_PKMODE_MOD_OUT_MONTY \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_MUL    (0x00b | OP_ALG_PKMODE_MOD_F2M)
#define OP_ALG_PKMODE_ECC_F2M_MUL_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2 \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_TIME_EQ)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV)
#define OP_ALG_PKMODE_ECC_F2M_MUL_R2_PROJ_TEQ \
				     (0x00b | OP_ALG_PKMODE_MOD_F2M \
					    | OP_ALG_PKMODE_MOD_R2_IN \
					    | OP_ALG_PKMODE_PRJECTV \
					    | OP_ALG_PKMODE_TIME_EQ)

/* PKHA mode copy-memory functions */
#define OP_ALG_PKMODE_SRC_REG_SHIFT  17
#define OP_ALG_PKMODE_SRC_REG_MASK   (7 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_SHIFT  10
#define OP_ALG_PKMODE_DST_REG_MASK   (7 << OP_ALG_PKMODE_DST_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_SHIFT  8
#define OP_ALG_PKMODE_SRC_SEG_MASK   (3 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_SHIFT  6
#define OP_ALG_PKMODE_DST_SEG_MASK   (3 << OP_ALG_PKMODE_DST_SEG_SHIFT)

#define OP_ALG_PKMODE_SRC_REG_A	     (0 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_REG_B	     (1 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_REG_N	     (3 << OP_ALG_PKMODE_SRC_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_A	     (0 << OP_ALG_PKMODE_DST_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_B	     (1 << OP_ALG_PKMODE_DST_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_E	     (2 << OP_ALG_PKMODE_DST_REG_SHIFT)
#define OP_ALG_PKMODE_DST_REG_N	     (3 << OP_ALG_PKMODE_DST_REG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_0	     (0 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_1	     (1 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_2	     (2 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_SRC_SEG_3	     (3 << OP_ALG_PKMODE_SRC_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_0	     (0 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_1	     (1 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_2	     (2 << OP_ALG_PKMODE_DST_SEG_SHIFT)
#define OP_ALG_PKMODE_DST_SEG_3	     (3 << OP_ALG_PKMODE_DST_SEG_SHIFT)

/* PKHA mode copy-memory functions - amount based on N SIZE */
#define OP_ALG_PKMODE_COPY_NSZ		0x10
#define OP_ALG_PKMODE_COPY_NSZ_A0_B0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_A0_B1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_A0_B2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_A0_B3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_A1_B0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_A1_B1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_A1_B2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_A1_B3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_A2_B0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_A2_B1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_A2_B2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_A2_B3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_A3_B0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_A3_B1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_A3_B2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_A3_B3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_B0_A0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_B0_A1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_B0_A2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_B0_A3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_B1_A0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_B1_A1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_B1_A2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_B1_A3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_B2_A0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_B2_A1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_B2_A2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_B2_A3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_B3_A0	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_B3_A1	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_NSZ_B3_A2	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_NSZ_B3_A3	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_NSZ_A_B	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_A_E	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_E)
#define OP_ALG_PKMODE_COPY_NSZ_A_N	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_N)
#define OP_ALG_PKMODE_COPY_NSZ_B_A	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_B_E	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_E)
#define OP_ALG_PKMODE_COPY_NSZ_B_N	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_N)
#define OP_ALG_PKMODE_COPY_NSZ_N_A	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_NSZ_N_B	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_NSZ_N_E	(OP_ALG_PKMODE_COPY_NSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_E)

/* PKHA mode copy-memory functions - amount based on SRC SIZE */
#define OP_ALG_PKMODE_COPY_SSZ		0x11
#define OP_ALG_PKMODE_COPY_SSZ_A0_B0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_A0_B1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_A0_B2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_A0_B3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_A1_B0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_A1_B1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_A1_B2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_A1_B3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_A2_B0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_A2_B1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_A2_B2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_A2_B3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_A3_B0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_A3_B1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_A3_B2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_A3_B3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_B | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_B0_A0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_B0_A1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_B0_A2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_B0_A3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_B1_A0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_B1_A1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_B1_A2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_B1_A3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_1 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_B2_A0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_B2_A1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_B2_A2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_B2_A3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_2 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_B3_A0	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_B3_A1	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_1)
#define OP_ALG_PKMODE_COPY_SSZ_B3_A2	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_2)
#define OP_ALG_PKMODE_COPY_SSZ_B3_A3	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_SRC_SEG_3 | \
					 OP_ALG_PKMODE_DST_REG_A | \
					 OP_ALG_PKMODE_DST_SEG_3)

#define OP_ALG_PKMODE_COPY_SSZ_A_B	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_A_E	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_E)
#define OP_ALG_PKMODE_COPY_SSZ_A_N	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_A | \
					 OP_ALG_PKMODE_DST_REG_N)
#define OP_ALG_PKMODE_COPY_SSZ_B_A	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_B_E	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_E)
#define OP_ALG_PKMODE_COPY_SSZ_B_N	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_B | \
					 OP_ALG_PKMODE_DST_REG_N)
#define OP_ALG_PKMODE_COPY_SSZ_N_A	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_A)
#define OP_ALG_PKMODE_COPY_SSZ_N_B	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_B)
#define OP_ALG_PKMODE_COPY_SSZ_N_E	(OP_ALG_PKMODE_COPY_SSZ | \
					 OP_ALG_PKMODE_SRC_REG_N | \
					 OP_ALG_PKMODE_DST_REG_E)

/*
 * SEQ_IN_PTR Command Constructs
 */

/* Release Buffers */
#define SQIN_RBS	BIT(26)

/* Sequence pointer is really a descriptor */
#define SQIN_INL	BIT(25)

/* Sequence pointer is a scatter-gather table */
#define SQIN_SGF	BIT(24)

/* Appends to a previous pointer */
#define SQIN_PRE	BIT(23)

/* Use extended length following pointer */
#define SQIN_EXT	BIT(22)

/* Restore sequence with pointer/length */
#define SQIN_RTO	BIT(21)

/* Replace job descriptor */
#define SQIN_RJD	BIT(20)

/* Sequence Out Pointer - start a new input sequence using output sequence */
#define SQIN_SOP	BIT(19)

#define SQIN_LEN_SHIFT	0
#define SQIN_LEN_MASK	(0xffff << SQIN_LEN_SHIFT)

/*
 * SEQ_OUT_PTR Command Constructs
 */

/* Sequence pointer is a scatter-gather table */
#define SQOUT_SGF	BIT(24)

/* Appends to a previous pointer */
#define SQOUT_PRE	BIT(23)

/* Restore sequence with pointer/length */
#define SQOUT_RTO	BIT(21)

/*
 * Ignore length field, add current output frame length back to SOL register.
 * Reset tracking length of bytes written to output frame.
 * Must be used together with SQOUT_RTO.
 */
#define SQOUT_RST	BIT(20)

/* Allow "write safe" transactions for this Output Sequence */
#define SQOUT_EWS	BIT(19)

/* Use extended length following pointer */
#define SQOUT_EXT	BIT(22)

#define SQOUT_LEN_SHIFT	0
#define SQOUT_LEN_MASK	(0xffff << SQOUT_LEN_SHIFT)

/*
 * SIGNATURE Command Constructs
 */

/* TYPE field is all that's relevant */
#define SIGN_TYPE_SHIFT		16
#define SIGN_TYPE_MASK		(0x0f << SIGN_TYPE_SHIFT)

#define SIGN_TYPE_FINAL		(0x00 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_FINAL_RESTORE (0x01 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_FINAL_NONZERO (0x02 << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_2		(0x0a << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_3		(0x0b << SIGN_TYPE_SHIFT)
#define SIGN_TYPE_IMM_4		(0x0c << SIGN_TYPE_SHIFT)

/*
 * MOVE Command Constructs
 */

#define MOVE_AUX_SHIFT		25
#define MOVE_AUX_MASK		(3 << MOVE_AUX_SHIFT)
#define MOVE_AUX_MS		(2 << MOVE_AUX_SHIFT)
#define MOVE_AUX_LS		(1 << MOVE_AUX_SHIFT)

#define MOVE_WAITCOMP_SHIFT	24
#define MOVE_WAITCOMP_MASK	(1 << MOVE_WAITCOMP_SHIFT)
#define MOVE_WAITCOMP		BIT(24)

#define MOVE_SRC_SHIFT		20
#define MOVE_SRC_MASK		(0x0f << MOVE_SRC_SHIFT)
#define MOVE_SRC_CLASS1CTX	(0x00 << MOVE_SRC_SHIFT)
#define MOVE_SRC_CLASS2CTX	(0x01 << MOVE_SRC_SHIFT)
#define MOVE_SRC_OUTFIFO	(0x02 << MOVE_SRC_SHIFT)
#define MOVE_SRC_DESCBUF	(0x03 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH0		(0x04 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH1		(0x05 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH2		(0x06 << MOVE_SRC_SHIFT)
#define MOVE_SRC_MATH3		(0x07 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO		(0x08 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO_CL	(0x09 << MOVE_SRC_SHIFT)
#define MOVE_SRC_INFIFO_NO_NFIFO (0x0a << MOVE_SRC_SHIFT)

#define MOVE_DEST_SHIFT		16
#define MOVE_DEST_MASK		(0x0f << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1CTX	(0x00 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2CTX	(0x01 << MOVE_DEST_SHIFT)
#define MOVE_DEST_OUTFIFO	(0x02 << MOVE_DEST_SHIFT)
#define MOVE_DEST_DESCBUF	(0x03 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH0		(0x04 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH1		(0x05 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH2		(0x06 << MOVE_DEST_SHIFT)
#define MOVE_DEST_MATH3		(0x07 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1INFIFO	(0x08 << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2INFIFO	(0x09 << MOVE_DEST_SHIFT)
#define MOVE_DEST_INFIFO	(0x0a << MOVE_DEST_SHIFT)
#define MOVE_DEST_PK_A		(0x0c << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS1KEY	(0x0d << MOVE_DEST_SHIFT)
#define MOVE_DEST_CLASS2KEY	(0x0e << MOVE_DEST_SHIFT)
#define MOVE_DEST_ALTSOURCE	(0x0f << MOVE_DEST_SHIFT)

#define MOVE_OFFSET_SHIFT	8
#define MOVE_OFFSET_MASK	(0xff << MOVE_OFFSET_SHIFT)

#define MOVE_LEN_SHIFT		0
#define MOVE_LEN_MASK		(0xff << MOVE_LEN_SHIFT)

#define MOVELEN_MRSEL_SHIFT	0
#define MOVELEN_MRSEL_MASK	(0x3 << MOVE_LEN_SHIFT)
#define MOVELEN_MRSEL_MATH0	(0 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH1	(1 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH2	(2 << MOVELEN_MRSEL_SHIFT)
#define MOVELEN_MRSEL_MATH3	(3 << MOVELEN_MRSEL_SHIFT)

#define MOVELEN_SIZE_SHIFT	6
#define MOVELEN_SIZE_MASK	(0x3 << MOVELEN_SIZE_SHIFT)
#define MOVELEN_SIZE_WORD	(0x01 << MOVELEN_SIZE_SHIFT)
#define MOVELEN_SIZE_BYTE	(0x02 << MOVELEN_SIZE_SHIFT)
#define MOVELEN_SIZE_DWORD	(0x03 << MOVELEN_SIZE_SHIFT)

/*
 * MATH Command Constructs
 */

#define MATH_IFB_SHIFT		26
#define MATH_IFB_MASK		(1 << MATH_IFB_SHIFT)
#define MATH_IFB		BIT(26)

#define MATH_NFU_SHIFT		25
#define MATH_NFU_MASK		(1 << MATH_NFU_SHIFT)
#define MATH_NFU		BIT(25)

/* STL for MATH, SSEL for MATHI */
#define MATH_STL_SHIFT		24
#define MATH_STL_MASK		(1 << MATH_STL_SHIFT)
#define MATH_STL		BIT(24)

#define MATH_SSEL_SHIFT		24
#define MATH_SSEL_MASK		(1 << MATH_SSEL_SHIFT)
#define MATH_SSEL		BIT(24)

#define MATH_SWP_SHIFT		0
#define MATH_SWP_MASK		(1 << MATH_SWP_SHIFT)
#define MATH_SWP		BIT(0)

/* Function selectors */
#define MATH_FUN_SHIFT		20
#define MATH_FUN_MASK		(0x0f << MATH_FUN_SHIFT)
#define MATH_FUN_ADD		(0x00 << MATH_FUN_SHIFT)
#define MATH_FUN_ADDC		(0x01 << MATH_FUN_SHIFT)
#define MATH_FUN_SUB		(0x02 << MATH_FUN_SHIFT)
#define MATH_FUN_SUBB		(0x03 << MATH_FUN_SHIFT)
#define MATH_FUN_OR		(0x04 << MATH_FUN_SHIFT)
#define MATH_FUN_AND		(0x05 << MATH_FUN_SHIFT)
#define MATH_FUN_XOR		(0x06 << MATH_FUN_SHIFT)
#define MATH_FUN_LSHIFT		(0x07 << MATH_FUN_SHIFT)
#define MATH_FUN_RSHIFT		(0x08 << MATH_FUN_SHIFT)
#define MATH_FUN_SHLD		(0x09 << MATH_FUN_SHIFT)
#define MATH_FUN_ZBYT		(0x0a << MATH_FUN_SHIFT) /* ZBYT is for MATH */
#define MATH_FUN_FBYT		(0x0a << MATH_FUN_SHIFT) /* FBYT is for MATHI */
#define MATH_FUN_BSWAP		(0x0b << MATH_FUN_SHIFT)

/* Source 0 selectors */
#define MATH_SRC0_SHIFT		16
#define MATH_SRC0_MASK		(0x0f << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG0		(0x00 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG1		(0x01 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG2		(0x02 << MATH_SRC0_SHIFT)
#define MATH_SRC0_REG3		(0x03 << MATH_SRC0_SHIFT)
#define MATH_SRC0_IMM		(0x04 << MATH_SRC0_SHIFT)
#define MATH_SRC0_DPOVRD	(0x07 << MATH_SRC0_SHIFT)
#define MATH_SRC0_SEQINLEN	(0x08 << MATH_SRC0_SHIFT)
#define MATH_SRC0_SEQOUTLEN	(0x09 << MATH_SRC0_SHIFT)
#define MATH_SRC0_VARSEQINLEN	(0x0a << MATH_SRC0_SHIFT)
#define MATH_SRC0_VARSEQOUTLEN	(0x0b << MATH_SRC0_SHIFT)
#define MATH_SRC0_ZERO		(0x0c << MATH_SRC0_SHIFT)
#define MATH_SRC0_ONE		(0x0f << MATH_SRC0_SHIFT)

/* Source 1 selectors */
#define MATH_SRC1_SHIFT		12
#define MATHI_SRC1_SHIFT	16
#define MATH_SRC1_MASK		(0x0f << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG0		(0x00 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG1		(0x01 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG2		(0x02 << MATH_SRC1_SHIFT)
#define MATH_SRC1_REG3		(0x03 << MATH_SRC1_SHIFT)
#define MATH_SRC1_IMM		(0x04 << MATH_SRC1_SHIFT)
#define MATH_SRC1_DPOVRD	(0x07 << MATH_SRC1_SHIFT)
#define MATH_SRC1_VARSEQINLEN	(0x08 << MATH_SRC1_SHIFT)
#define MATH_SRC1_VARSEQOUTLEN	(0x09 << MATH_SRC1_SHIFT)
#define MATH_SRC1_INFIFO	(0x0a << MATH_SRC1_SHIFT)
#define MATH_SRC1_OUTFIFO	(0x0b << MATH_SRC1_SHIFT)
#define MATH_SRC1_ONE		(0x0c << MATH_SRC1_SHIFT)
#define MATH_SRC1_JOBSOURCE	(0x0d << MATH_SRC1_SHIFT)
#define MATH_SRC1_ZERO		(0x0f << MATH_SRC1_SHIFT)

/* Destination selectors */
#define MATH_DEST_SHIFT		8
#define MATHI_DEST_SHIFT	12
#define MATH_DEST_MASK		(0x0f << MATH_DEST_SHIFT)
#define MATH_DEST_REG0		(0x00 << MATH_DEST_SHIFT)
#define MATH_DEST_REG1		(0x01 << MATH_DEST_SHIFT)
#define MATH_DEST_REG2		(0x02 << MATH_DEST_SHIFT)
#define MATH_DEST_REG3		(0x03 << MATH_DEST_SHIFT)
#define MATH_DEST_DPOVRD	(0x07 << MATH_DEST_SHIFT)
#define MATH_DEST_SEQINLEN	(0x08 << MATH_DEST_SHIFT)
#define MATH_DEST_SEQOUTLEN	(0x09 << MATH_DEST_SHIFT)
#define MATH_DEST_VARSEQINLEN	(0x0a << MATH_DEST_SHIFT)
#define MATH_DEST_VARSEQOUTLEN	(0x0b << MATH_DEST_SHIFT)
#define MATH_DEST_NONE		(0x0f << MATH_DEST_SHIFT)

/* MATHI Immediate value */
#define MATHI_IMM_SHIFT		4
#define MATHI_IMM_MASK		(0xff << MATHI_IMM_SHIFT)

/* Length selectors */
#define MATH_LEN_SHIFT		0
#define MATH_LEN_MASK		(0x0f << MATH_LEN_SHIFT)
#define MATH_LEN_1BYTE		0x01
#define MATH_LEN_2BYTE		0x02
#define MATH_LEN_4BYTE		0x04
#define MATH_LEN_8BYTE		0x08

/*
 * JUMP Command Constructs
 */

#define JUMP_CLASS_SHIFT	25
#define JUMP_CLASS_MASK		(3 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_NONE		0
#define JUMP_CLASS_CLASS1	(1 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_CLASS2	(2 << JUMP_CLASS_SHIFT)
#define JUMP_CLASS_BOTH		(3 << JUMP_CLASS_SHIFT)

#define JUMP_JSL_SHIFT		24
#define JUMP_JSL_MASK		(1 << JUMP_JSL_SHIFT)
#define JUMP_JSL		BIT(24)

#define JUMP_TYPE_SHIFT		20
#define JUMP_TYPE_MASK		(0x0f << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_LOCAL		(0x00 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_LOCAL_INC	(0x01 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_GOSUB		(0x02 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_LOCAL_DEC	(0x03 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_NONLOCAL	(0x04 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_RETURN	(0x06 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_HALT		(0x08 << JUMP_TYPE_SHIFT)
#define JUMP_TYPE_HALT_USER	(0x0c << JUMP_TYPE_SHIFT)

#define JUMP_TEST_SHIFT		16
#define JUMP_TEST_MASK		(0x03 << JUMP_TEST_SHIFT)
#define JUMP_TEST_ALL		(0x00 << JUMP_TEST_SHIFT)
#define JUMP_TEST_INVALL	(0x01 << JUMP_TEST_SHIFT)
#define JUMP_TEST_ANY		(0x02 << JUMP_TEST_SHIFT)
#define JUMP_TEST_INVANY	(0x03 << JUMP_TEST_SHIFT)

/* Condition codes. JSL bit is factored in */
#define JUMP_COND_SHIFT		8
#define JUMP_COND_MASK		((0xff << JUMP_COND_SHIFT) | JUMP_JSL)
#define JUMP_COND_PK_0		BIT(15)
#define JUMP_COND_PK_GCD_1	BIT(14)
#define JUMP_COND_PK_PRIME	BIT(13)
#define JUMP_COND_MATH_N	BIT(11)
#define JUMP_COND_MATH_Z	BIT(10)
#define JUMP_COND_MATH_C	BIT(9)
#define JUMP_COND_MATH_NV	BIT(8)

#define JUMP_COND_JQP		(BIT(15) | JUMP_JSL)
#define JUMP_COND_SHRD		(BIT(14) | JUMP_JSL)
#define JUMP_COND_SELF		(BIT(13) | JUMP_JSL)
#define JUMP_COND_CALM		(BIT(12) | JUMP_JSL)
#define JUMP_COND_NIP		(BIT(11) | JUMP_JSL)
#define JUMP_COND_NIFP		(BIT(10) | JUMP_JSL)
#define JUMP_COND_NOP		(BIT(9) | JUMP_JSL)
#define JUMP_COND_NCP		(BIT(8) | JUMP_JSL)

/* Source / destination selectors */
#define JUMP_SRC_DST_SHIFT		12
#define JUMP_SRC_DST_MASK		(0x0f << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_MATH0		(0x00 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_MATH1		(0x01 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_MATH2		(0x02 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_MATH3		(0x03 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_DPOVRD		(0x07 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_SEQINLEN		(0x08 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_SEQOUTLEN		(0x09 << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_VARSEQINLEN	(0x0a << JUMP_SRC_DST_SHIFT)
#define JUMP_SRC_DST_VARSEQOUTLEN	(0x0b << JUMP_SRC_DST_SHIFT)

#define JUMP_OFFSET_SHIFT	0
#define JUMP_OFFSET_MASK	(0xff << JUMP_OFFSET_SHIFT)

/*
 * NFIFO ENTRY
 * Data Constructs
 *
 */
#define NFIFOENTRY_DEST_SHIFT	30
#define NFIFOENTRY_DEST_MASK	((uint32_t)(3 << NFIFOENTRY_DEST_SHIFT))
#define NFIFOENTRY_DEST_DECO	(0 << NFIFOENTRY_DEST_SHIFT)
#define NFIFOENTRY_DEST_CLASS1	(1 << NFIFOENTRY_DEST_SHIFT)
#define NFIFOENTRY_DEST_CLASS2	((uint32_t)(2 << NFIFOENTRY_DEST_SHIFT))
#define NFIFOENTRY_DEST_BOTH	((uint32_t)(3 << NFIFOENTRY_DEST_SHIFT))

#define NFIFOENTRY_LC2_SHIFT	29
#define NFIFOENTRY_LC2_MASK	(1 << NFIFOENTRY_LC2_SHIFT)
#define NFIFOENTRY_LC2		BIT(29)

#define NFIFOENTRY_LC1_SHIFT	28
#define NFIFOENTRY_LC1_MASK	(1 << NFIFOENTRY_LC1_SHIFT)
#define NFIFOENTRY_LC1		BIT(28)

#define NFIFOENTRY_FC2_SHIFT	27
#define NFIFOENTRY_FC2_MASK	(1 << NFIFOENTRY_FC2_SHIFT)
#define NFIFOENTRY_FC2		BIT(27)

#define NFIFOENTRY_FC1_SHIFT	26
#define NFIFOENTRY_FC1_MASK	(1 << NFIFOENTRY_FC1_SHIFT)
#define NFIFOENTRY_FC1		BIT(26)

#define NFIFOENTRY_STYPE_SHIFT	24
#define NFIFOENTRY_STYPE_MASK	(3 << NFIFOENTRY_STYPE_SHIFT)
#define NFIFOENTRY_STYPE_DFIFO	(0 << NFIFOENTRY_STYPE_SHIFT)
#define NFIFOENTRY_STYPE_OFIFO	(1 << NFIFOENTRY_STYPE_SHIFT)
#define NFIFOENTRY_STYPE_PAD	(2 << NFIFOENTRY_STYPE_SHIFT)
#define NFIFOENTRY_STYPE_SNOOP	(3 << NFIFOENTRY_STYPE_SHIFT)
#define NFIFOENTRY_STYPE_ALTSOURCE ((0 << NFIFOENTRY_STYPE_SHIFT) \
					| NFIFOENTRY_AST)
#define NFIFOENTRY_STYPE_OFIFO_SYNC ((1 << NFIFOENTRY_STYPE_SHIFT) \
					| NFIFOENTRY_AST)
#define NFIFOENTRY_STYPE_SNOOP_ALT ((3 << NFIFOENTRY_STYPE_SHIFT) \
					| NFIFOENTRY_AST)

#define NFIFOENTRY_DTYPE_SHIFT	20
#define NFIFOENTRY_DTYPE_MASK	(0xF << NFIFOENTRY_DTYPE_SHIFT)

#define NFIFOENTRY_DTYPE_SBOX	(0x0 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_AAD	(0x1 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_IV	(0x2 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_SAD	(0x3 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_ICV	(0xA << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_SKIP	(0xE << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_MSG	(0xF << NFIFOENTRY_DTYPE_SHIFT)

#define NFIFOENTRY_DTYPE_PK_A0	(0x0 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_A1	(0x1 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_A2	(0x2 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_A3	(0x3 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_B0	(0x4 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_B1	(0x5 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_B2	(0x6 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_B3	(0x7 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_N	(0x8 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_E	(0x9 << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_A	(0xC << NFIFOENTRY_DTYPE_SHIFT)
#define NFIFOENTRY_DTYPE_PK_B	(0xD << NFIFOENTRY_DTYPE_SHIFT)

#define NFIFOENTRY_BND_SHIFT	19
#define NFIFOENTRY_BND_MASK	(1 << NFIFOENTRY_BND_SHIFT)
#define NFIFOENTRY_BND		BIT(19)

#define NFIFOENTRY_PTYPE_SHIFT	16
#define NFIFOENTRY_PTYPE_MASK	(0x7 << NFIFOENTRY_PTYPE_SHIFT)

#define NFIFOENTRY_PTYPE_ZEROS		(0x0 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_RND_NOZEROS	(0x1 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_INCREMENT	(0x2 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_RND		(0x3 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_ZEROS_NZ	(0x4 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_RND_NZ_LZ	(0x5 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_N		(0x6 << NFIFOENTRY_PTYPE_SHIFT)
#define NFIFOENTRY_PTYPE_RND_NZ_N	(0x7 << NFIFOENTRY_PTYPE_SHIFT)

#define NFIFOENTRY_OC_SHIFT	15
#define NFIFOENTRY_OC_MASK	(1 << NFIFOENTRY_OC_SHIFT)
#define NFIFOENTRY_OC		BIT(15)

#define NFIFOENTRY_PR_SHIFT	15
#define NFIFOENTRY_PR_MASK	(1 << NFIFOENTRY_PR_SHIFT)
#define NFIFOENTRY_PR		BIT(15)

#define NFIFOENTRY_AST_SHIFT	14
#define NFIFOENTRY_AST_MASK	(1 << NFIFOENTRY_AST_SHIFT)
#define NFIFOENTRY_AST		BIT(14)

#define NFIFOENTRY_BM_SHIFT	11
#define NFIFOENTRY_BM_MASK	(1 << NFIFOENTRY_BM_SHIFT)
#define NFIFOENTRY_BM		BIT(11)

#define NFIFOENTRY_PS_SHIFT	10
#define NFIFOENTRY_PS_MASK	(1 << NFIFOENTRY_PS_SHIFT)
#define NFIFOENTRY_PS		BIT(10)

#define NFIFOENTRY_DLEN_SHIFT	0
#define NFIFOENTRY_DLEN_MASK	(0xFFF << NFIFOENTRY_DLEN_SHIFT)

#define NFIFOENTRY_PLEN_SHIFT	0
#define NFIFOENTRY_PLEN_MASK	(0xFF << NFIFOENTRY_PLEN_SHIFT)

/* Append Load Immediate Command */
#define FD_CMD_APPEND_LOAD_IMMEDIATE			BIT(31)

/* Set SEQ LIODN equal to the Non-SEQ LIODN for the job */
#define FD_CMD_SET_SEQ_LIODN_EQUAL_NONSEQ_LIODN		BIT(30)

/* Frame Descriptor Command for Replacement Job Descriptor */
#define FD_CMD_REPLACE_JOB_DESC				BIT(29)

#endif /* __RTA_DESC_H__ */

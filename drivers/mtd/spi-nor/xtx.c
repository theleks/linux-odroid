// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021, Chris Morgan <macromorgan@hotmail.com>
 * Based on XMC SPI NOR module
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#include <linux/mtd/spi-nor.h>

#include "core.h"

static const struct flash_info xtx_parts[] = {
       /* XTX (XTX Technology Limited) */
       { "XT25F128B", INFO(0x0b4018, 0, 64 * 1024, 256,
                            SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
                            SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) },
};

static int xtx_set_4byte_addr_mode(struct spi_nor *nor, bool enable)
{
       int ret;

       ret = spi_nor_set_4byte_addr_mode(nor, enable);
       if (ret || enable)
               return ret;

       ret = spi_nor_write_enable(nor);
       if (ret)
               return ret;

       ret = spi_nor_write_ear(nor, 0);
       if (ret)
               return ret;

       return spi_nor_write_disable(nor);
}

static void xtx_default_init(struct spi_nor *nor)
{
       nor->params->set_4byte_addr_mode = xtx_set_4byte_addr_mode;
}

static const struct spi_nor_fixups xtx_fixups = {
       .default_init = xtx_default_init,
};

const struct spi_nor_manufacturer spi_nor_xtx = {
       .name = "xtx",
       .parts = xtx_parts,
       .nparts = ARRAY_SIZE(xtx_parts),
//     .fixups = &xtx_fixups,
};

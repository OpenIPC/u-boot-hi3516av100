#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	:= $(obj)libmtd.a

COBJS-$(CONFIG_MTD_DEVICE) += mtdcore.o
COBJS-$(CONFIG_MTD_PARTITIONS) += mtdpart.o
COBJS-$(CONFIG_MTD_CONCAT) += mtdconcat.o
COBJS-$(CONFIG_HAS_DATAFLASH) += at45.o
COBJS-$(CONFIG_FLASH_CFI_DRIVER) += cfi_flash.o
COBJS-$(CONFIG_FLASH_CFI_MTD) += cfi_mtd.o
COBJS-$(CONFIG_HAS_DATAFLASH) += dataflash.o
COBJS-$(CONFIG_FLASH_CFI_LEGACY) += jedec_flash.o
COBJS-$(CONFIG_MW_EEPROM) += mw_eeprom.o
COBJS-$(CONFIG_SPEARSMI) += spr_smi.o
ifdef CONFIG_HIFMC
COBJS-$(CONFIG_HIFMC) += hifmc_common.o
COBJS-$(CONFIG_HI3521A) += hifmc_hi3521a.o
COBJS-$(CONFIG_HI3518EV200) += hifmc_hi3518ev200.o
COBJS-$(CONFIG_HI3516CV300) += hifmc_hi3516cv300.o
COBJS-$(CONFIG_HI3531A) += hifmc_hi3531a.o
COBJS-$(CONFIG_HI3536C) += hifmc_hi3536c.o
COBJS-$(CONFIG_HI3536DV100) += hifmc_hi3536dv100.o
COBJS-$(CONFIG_HI3519) += hifmc_hi3519.o
COBJS-$(CONFIG_HI3519V101) += hifmc_hi3519.o
COBJS-$(CONFIG_HI3559) += hifmc_hi3559.o
COBJS-$(CONFIG_HI3556) += hifmc_hi3559.o
COBJS-$(CONFIG_HI3516AV200) += hifmc_hi3516av200.o
endif

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################

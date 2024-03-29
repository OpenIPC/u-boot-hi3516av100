#
# (C) Copyright 2002-2006
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).a
LIBGCC	= $(obj)libgcc.a

GLSOBJS	+= _ashldi3.o
GLSOBJS	+= _ashrdi3.o
GLSOBJS	+= _divsi3.o
GLSOBJS	+= _lshrdi3.o
GLSOBJS	+= _modsi3.o
GLSOBJS	+= _udivsi3.o
GLSOBJS	+= _umodsi3.o

GLCOBJS	+= div0.o
SOBJS-y	+= mmu.o
SOBJS-$(CONFIG_HI3516A) += cache_ops.o
SOBJS-$(CONFIG_HI3536) += cache_ops.o
SOBJS-$(CONFIG_HI3536C) += cache_ops.o
SOBJS-$(CONFIG_HI3536DV100) += cache_ops.o
SOBJS-$(CONFIG_HI3521A) += cache_ops.o
SOBJS-$(CONFIG_HI3519) += cache_ops.o
SOBJS-$(CONFIG_HI3519V101) += cache_ops.o
SOBJS-$(CONFIG_HI3516AV200) += cache_ops.o
SOBJS-$(CONFIG_HI3559) += cache_ops.o
COBJS-y	+= board.o
COBJS-y	+= bootm.o
COBJS-y	+= cache.o
COBJS-y	+= process.o
ifndef CONFIG_SYS_NO_CP15_CACHE
COBJS-y	+= cache-cp15.o
endif
COBJS-y	+= interrupts.o
COBJS-y	+= reset.o
COBJS-y += ddr_layout.o
COBJS-y += ddr_size.o
COBJS-y += cpu_info.o

SOBJS-$(CONFIG_USE_ARCH_MEMSET) += memset.o
SOBJS-$(CONFIG_USE_ARCH_MEMCPY) += memcpy.o

ifdef CONFIG_SNAPSHOT_BOOT
COBJS-y += $(shell if [ $(__ARM_ARCH__) -eq 7 ] ; then \
	echo "hibernate.o"; \
	else if [ $(__ARM_ARCH__) -eq 5 ] ; then \
	echo "hibernate_arm9.o"; fi; fi)

SOBJS-y += $(shell if [ $(__ARM_ARCH__) -eq 7 ] ; then \
	echo "cpu_helper_a7.o"; fi)
SOBJS-y += bootm_asm.o
endif

SRCS	:= $(GLSOBJS:.o=.S) $(GLCOBJS:.o=.c) \
	   $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))
LGOBJS	:= $(addprefix $(obj),$(GLSOBJS)) \
	   $(addprefix $(obj),$(GLCOBJS))

# Always build libarm.a
TARGETS	:= $(LIB)

# Build private libgcc only when asked for
ifdef USE_PRIVATE_LIBGCC
TARGETS	+= $(LIBGCC)
endif

# For EABI conformant tool chains, provide eabi_compat()
ifneq (,$(findstring -mabi=aapcs-linux,$(PLATFORM_CPPFLAGS)))
TARGETS	+= $(obj)eabi_compat.o
endif

all:	$(TARGETS)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(LIBGCC): $(obj).depend $(LGOBJS)
	$(AR) $(ARFLAGS) $@ $(LGOBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################

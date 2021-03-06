
#ifndef __HISILICON_ETHV100_SYS_H
#define __HISILICON_ETHV100_SYS_H

void hieth_sys_init(void);
void hieth_sys_exit(void);

void hieth_set_crg_phy_mode(unsigned char is_rmii_mode);
void set_inner_phy_addr(u32 phyaddr);
void set_efuse_unread(void);

void hieth_sys_startup(void);
void hieth_sys_allstop(void);

void set_phy_valtage(void);
#endif


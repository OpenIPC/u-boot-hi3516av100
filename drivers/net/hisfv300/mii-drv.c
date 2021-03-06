
#include "hieth.h"
#include "mdio.h"
#include <config.h>

/* MDIO Bus Interface */
static struct hieth_mdio_local mdio_bus_ld;
extern unsigned char U_PHY_ADDR;
extern unsigned char D_PHY_ADDR;
extern char U_PHY_NAME[MAX_PHY_NAME_LEN];
extern char D_PHY_NAME[MAX_PHY_NAME_LEN];
static int hieth_mdiobus_read(char *devname, unsigned char addr, 
		unsigned char reg, unsigned short *value)
{
	*value = hieth_mdio_read(&mdio_bus_ld, addr, reg);

	return 0;
}

static int hieth_mdiobus_write(char *devname, unsigned char addr, 
		unsigned char reg, unsigned short value)
{
	hieth_mdio_write(&mdio_bus_ld, addr, reg, value);
	
	return 0;
}

#define PHY_ID_KSZ8051		0x00221550
#define PHY_ID_KSZ8081		0x00221560
#define PHY_ID_MASK		0xFFFFFFF0

//added by wzh 2009-4-15
unsigned int get_phy_device(char *devname, unsigned char phyaddr)
{
	u32 phy_id = 0;
	u16 id1 = 0, id2 = 0;
	
	if (miiphy_read(devname, phyaddr, PHY_PHYIDR1, &id1)) {
		printf("%s,%d:PHY_PHYIDR1 read failed!\n", __func__, __LINE__);
		return -1;
	}
	if (miiphy_read(devname, phyaddr, PHY_PHYIDR2, &id2)) {
		printf("%s,%d:PHY_PHYIDR2 read failed!\n", __func__, __LINE__);
		return -1;
	}

	phy_id = (id1 & 0xffff) << 16;
	phy_id |= (id2 & 0xffff);

	/* If the phy_id is all Fs, there is no device there */
	if (0xffffffff == phy_id || 0 == phy_id
		|| phy_id == 0xFFFF || phy_id == 0xFFFF0000)
	{
		return -1;
	}

	/* run this at RMII mode */
	if (HIETH_MII_RMII_MODE_U == 1)
	{
		/* PHY-KSZ8051RNL */
		if ((phy_id & PHY_ID_MASK) == PHY_ID_KSZ8051) {
			unsigned short reg = 0;

			if (miiphy_read(devname, phyaddr, 0x1F, &reg)) {
				printf("PHY 0x1F read failed\n");
				return -1;
			}
			reg |= BIT(7); /* set phy RMII 50MHz clk;*/
			if (miiphy_write(devname, phyaddr, 0x1F, reg)) {
				printf("PHY 0x1F write failed\n");
				return -1;
			}

			if (miiphy_read(devname, phyaddr, 0x16, &reg)) {
				printf("PHY 0x16 read failed\n");
				return -1;
			}
			reg |= BIT(1); /* set phy RMII override; */
			if (miiphy_write(devname, phyaddr, 0x16, reg)) {
				printf("PHY 0x16 write failed\n");
				return -1;
			}
		}

		/* PHY-KSZ8081 */
		if ((phy_id & PHY_ID_MASK) == PHY_ID_KSZ8081) {
			unsigned short val = 0;

			if (miiphy_read(devname, phyaddr, 0x1F, &val) != 0) {
				printf("PHY 0x1F read failed\n");
				return -1;
			};
			val |= BIT(7);       /* set phy RMII 50MHz clk; */
			if (miiphy_write(devname, phyaddr, 0x1F, val) != 0) {
				printf("PHY 0x1F write failed\n");
				return -1;
			}
		}
	}
	return 0;
}

static int mdio_registered;

int hieth_mdiobus_driver_init(void)
{
	mdio_bus_ld.iobase_phys = ETH_IO_ADDRESS_BASE;
	mdio_bus_ld.mdio_frqdiv = ETH_MDIO_FRQDIV;

	hieth_mdio_init(&mdio_bus_ld);
	
	if (!mdio_registered) {
		/* UpEther PHY init */
		miiphy_register(U_PHY_NAME, hieth_mdiobus_read,
				hieth_mdiobus_write);

		/* DownEther PHY init */
		miiphy_register(D_PHY_NAME, hieth_mdiobus_read,
				hieth_mdiobus_write);

		mdio_registered = 1;
	}

	if(!get_phy_device(U_PHY_NAME,U_PHY_ADDR))
	{
		miiphy_reset(U_PHY_NAME, U_PHY_ADDR);
	    miiphy_set_current_dev(U_PHY_NAME);
	}

	if(!get_phy_device(D_PHY_NAME,D_PHY_ADDR))
	{	
		miiphy_reset(D_PHY_NAME, D_PHY_ADDR);
	    miiphy_set_current_dev(D_PHY_NAME);
	}
	return 0;
}

void hieth_mdiobus_driver_exit(void)
{
    /*add this to avoid the first time to use eth will print 'No such device: XXXXX' message.*/
    if (!miiphy_get_current_dev())
        return;

	/* UpEther PHY exit */
	if(!get_phy_device(U_PHY_NAME,U_PHY_ADDR))
	{
		miiphy_reset(U_PHY_NAME, U_PHY_ADDR);
	}
	
	/* DownEther PHY exit */
	if(!get_phy_device(D_PHY_NAME,D_PHY_ADDR))
	{	
		miiphy_reset(D_PHY_NAME, D_PHY_ADDR);
	}
		
	hieth_mdio_exit(&mdio_bus_ld);
}


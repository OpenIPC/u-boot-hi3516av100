#!/bin/sh -e

export ARCH=arm
export CROSS_COMPILE=${CROSS_COMPILE:-arm-hisiv510-linux-}

OUTPUTDIR="${HOME}/src/hisi/uboot"
SOCS="hi3516d hi3516a"

for soc in ${SOCS};do

make clean
make hi3516a_config
cp reg_info_${soc}.bin .reg

make -j8
make mini-boot.bin

cp mini-boot.bin ${OUTPUTDIR}/u-boot-${soc}v100-universal.bin
#cp mini-boot.bin /srv/tftp/u-boot-${soc}v100-universal.bin

done


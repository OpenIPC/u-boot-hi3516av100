#!/bin/sh -e

export ARCH=arm
export CROSS_COMPILE=${CROSS_COMPILE:-arm-hisiv510-linux-}

OUTPUTDIR="${HOME}/src/hisi/uboot"
SOCS="hi3516a hi3516d"

for soc in ${SOCS};do

sed -i s/hi3516.v100/${soc}v100/ include/configs/hi3516a.h
make clean
make hi3516a_config
cp reg_info_${soc}.bin .reg

make -j8
make mini-boot.bin

cp mini-boot.bin ${OUTPUTDIR}/u-boot-${soc}v100-universal.bin
#cp mini-boot.bin /srv/tftp/u-boot-${soc}v100-universal.bin

done


#!/bin/sh

PLATFORM=freescale
if [ `dd if=/dev/mmcblk0 bs=512 skip=1024 count=1 | grep -c "HW CONFIG"` == 1 ]; then
	PLATFORM=ntx508
fi

(

	if [ ! -e /etc/wpa_supplicant/wpa_supplicant.conf ]; then
		cp /etc/wpa_supplicant/wpa_supplicant.conf.template /etc/wpa_supplicant/wpa_supplicant.conf
	fi

) &

INTERFACE=wlan0
WIFI_MODULE=ar6000
if [ $PLATFORM == ntx508 ]; then
	INTERFACE=eth0
	WIFI_MODULE=dhd
fi

export INTERFACE
export WIFI_MODULE

export QWS_MOUSE_PROTO="tslib_nocal:/dev/input/event1"
export QWS_KEYBOARD=imx508kbd:/dev/input/event0
export QWS_DISPLAY=Transformed:imx508:Rot90
export NICKEL_HOME=/mnt/onboard/.kobo
export LD_LIBRARY_PATH=/usr/local/Kobo
export WIFI_MODULE_PATH=/drivers/$PLATFORM/wifi/$WIFI_MODULE.ko
export LANG=en_US.UTF-8
export UBOOT_MMC=/etc/u-boot/$PLATFORM/u-boot.mmc
export UBOOT_RECOVERY=/etc/u-boot/$PLATFORM/u-boot.recovery

/usr/local/Kobo/nickel -qws &

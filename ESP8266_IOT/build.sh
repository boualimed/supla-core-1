#!/bin/sh

###
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# 
# @author Przemyslaw Zygmunt przemek@supla.org
#
###

DEP_LIBS="-lssl"
CFG_SECTOR=0x3C
NOSSL=0

export COMPILE=gcc
export SDK_PATH=${ESP_SDK_PATH}
export SRC_ROOT=`pwd`

case $1 in
   "dht11_esp01")
   ;;
   "dht22_esp01")
   ;;
   "am2302_esp01")
   ;;
   "thermometer_esp01")
   ;;
   "thermometer_esp01_ds_gpio0")
   ;;
   "wifisocket")
   ;;
   "wifisocket_esp01")
   ;;
   "wifisocket_54")
   ;;
   "gate_module")
   ;;
   "gate_module_mem")
   ;;
   "gate_module_dht11")
   ;;
   "gate_module_dht22")
   ;;
   "gate_module_esp01")
   ;;
   "gate_module_esp01_ds")
   ;;
   "gate_module_wroom")
     CFG_SECTOR=0xBC
   ;;
   "gate_module2_wroom")
     CFG_SECTOR=0xBC
   ;;
   "gate_module_wroom_mem")
     CFG_SECTOR=0xBC
   ;;
   "gate_module2_wroom_mem")
     CFG_SECTOR=0xBC
   ;;
   "rs_module")
   ;;
   "rs_module_wroom")
     CFG_SECTOR=0xBC
   ;;
   "starter1_module_wroom")
     CFG_SECTOR=0xBC
   ;;
   "jangoe_wifisocket")
   ;;
   "jangoe_rs")
   ;;
   "sonoff")
     CFG_SECTOR=0xBC
   ;;
   "sonoff_ds18b20")
     CFG_SECTOR=0xBC
   ;;
   "EgyIOT")
     DEP_LIBS="-lpwm"
     NOSSL=1
   ;;
   "dimmer")
     DEP_LIBS="-lpwm"
     NOSSL=1
   ;;
   "zam_row_01")
     CFG_SECTOR=0xBC
   ;;
   "rgbw")
     DEP_LIBS="-lpwm"
     NOSSL=1
   ;;
   "rgbw_wroom")
     DEP_LIBS="-lpwm -lssl"
     CFG_SECTOR=0xBC
   ;;
   "h801")
     DEP_LIBS="-lpwm -lssl"
     CFG_SECTOR=0xBC
   ;;
   *)
   echo "Usage:"
   echo "       build.sh BOARD_TYPE";
   echo "--------------------------";
   echo " Board types:             ";
   echo "              dht11_esp01";
   echo "              dht22_esp01";
   echo "              am2302_esp01";
   echo "              thermometer_esp01";
   echo "              thermometer_esp01_ds_gpio0";
   echo "              wifisocket  ";
   echo "              wifisocket_esp01";
   echo "              wifisocket_esp01_thermometer";
   echo "              wifisocket_54";
   echo "              gate_module";
   echo "              gate_module_mem";
   echo "              gate_module_dht11";
   echo "              gate_module_dht22";
   echo "              gate_module_esp01";
   echo "              gate_module_esp01_ds";
   echo "              gate_module_wroom";
   echo "              gate_module_wroom_mem";
   echo "              gate_module2_wroom";
   echo "              gate_module2_wroom_mem";
   echo "              rs_module";
   echo "              rs_module_wroom";
   echo "              starter1_module_wroom";
   echo "              jangoe_rs";
   echo "              jangoe_wifisocket";
   echo "              sonoff";
   echo "              sonoff_ds18b20";
   echo "              EgyIOT";
   echo "              dimmer";
   echo "              zam_row_01";
   echo "              rgbw";
   echo "              rgbw_wroom";
   echo "              h801";
   echo
   echo
   exit;
   ;;

esac

make clean

BOARD_NAME=$1

if [ "$NOSSL" -eq 1 ]; then
    EXTRA="NOSSL=1"
    BOARD_NAME="$1"_nossl
else
    EXTRA="NOSSL=0"
fi

make SUPLA_DEP_LIBS="$DEP_LIBS" BOARD=$1 CFG_SECTOR="$CFG_SECTOR" BOOT=new APP=1 SPI_SPEED=40 SPI_MODE=DIO SPI_SIZE_MAP=2 $EXTRA #&& \
cp bin/upgrade/user1.1024.new.2.bin bin/"$BOARD_NAME"_user1.1024.new.2.bin && \
cp $SDK_PATH/bin/boot_v1.6.bin bin/boot_v1.6.bin

exit 0

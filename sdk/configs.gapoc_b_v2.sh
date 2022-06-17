if [  -n "${ZSH_VERSION:-}" ]; then
	DIR="$(readlink -f -- "${(%):-%x}")"
	DIRNAME="$(dirname $DIR)"
	GAP_SDK_HOME=$(dirname $DIRNAME)
	export GAP_SDK_HOME
	#echo $(dirname "$(readlink -f ${(%):-%N})")
else
	export GAP_SDK_HOME="$(dirname $(dirname "$(readlink -f "${BASH_SOURCE[0]}")"))"
fi

source $GAP_SDK_HOME/configs/clean.sh
source $GAP_SDK_HOME/configs/openocd-gap8.sh

export TARGET_CHIP_FAMILY="GAP8"
export TARGET_CHIP="GAP8_V2"
export TARGET_NAME="gap_rev1"
export BOARD_NAME=gapoc_b
export PULP_CURRENT_CONFIG=$BOARD_NAME@config_file=boards/gapoc_b_revb.json
export GVSOC_CONFIG=boards/gapoc_b_revb
export OPENOCD_CHIP_TARGET=target/gap8revb.tcl
export GAPY_OPENOCD_CABLE=interface/jlink.cfg
export OPENOCD_CABLE=interface/jlink.cfg
#export OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-ocd-h.cfg
export PLPBRIDGE_CABLE=ftdi

export GAPY_TARGET=gapoc_b_v2

source $GAP_SDK_HOME/configs/common.sh

#!/bin/bash

DEVICE=$1
PROJ_DIR=$2
TOOL_CHAINS=$3

echo Device: ${DEVICE}
echo ProjDir: ${PROJ_DIR}

if [ -d ${PROJ_DIR}/scripts ]; then
echo "Directory scripts already exists"
rm -rf ${PROJ_DIR}/scripts
fi
mkdir -p ${PROJ_DIR}/scripts

cp ../Make/gcc_crc16.sh ${PROJ_DIR}/scripts
cp ../Make/gcc_crc32.sh ${PROJ_DIR}/scripts

if [ "${TOOL_CHAINS}" = "IAR" ]; then
  if [ -d ${PROJ_DIR}/CMSIS/${DEVICE} ]; then
    echo "Directory CMSIS already exists"
    cp ../Lib/Device/${DEVICE}/Source/IAR/${DEVICE}.icf ${PROJ_DIR}/CMSIS/${DEVICE}
  fi
else
  if [ -d ${PROJ_DIR}/CMSIS/${DEVICE} ]; then
    echo "Directory CMSIS already exists"
    cp ../Lib/Device/${DEVICE}/Source/GCC/${DEVICE}.ld ${PROJ_DIR}/CMSIS/${DEVICE}
  fi
fi

#!/bin/bash

if [ $1 == "NTSCU" ] ; then
    SRC_ISO="GZLE01.iso"
    SRC_MAP="maps/framework.map"
    BLD_ISO="build/twwgz.iso"
    BLD_MAP="build/GZLE01.map"
    LINK_BASE="0x8040_DB20"
elif [ $1 == "NTSCJ" ] ; then
    SRC_ISO="GZLJ01.iso"
    SRC_MAP="maps/framework.map"
    BLD_ISO="build/twwgz.iso"
    BLD_MAP="build/GZLJ01.map"
    LINK_BASE="0x8040_1000"
else 
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s=@srcIso=$SRC_ISO=g" RomHack-template.toml > RomHack.toml
sed -i "s=@srcMap=$SRC_MAP=g" RomHack.toml
sed -i "s=@bldIso=$BLD_ISO=g" RomHack.toml
sed -i "s=@bldMap=$BLD_MAP=g" RomHack.toml
sed -i "s=@linkBase=$LINK_BASE=g" RomHack.toml
#!/bin/bash

if [ $1 == "NTSCU" ] ; then
    ARENALO="0x80301854"
    ARENALO_VAL="0x3c608045"
    MAIN="0x80006338"
    MAIN_TRAMPOLINE="0x80338668"
    FIRST_INSTRUCTION="0x9421fff0"
    RETURN_TO_MAIN="0x4BCCDCD0"
elif [ $1 == "NTSCJ" ] ; then
    ARENALO="0x802ff5d4"
    ARENALO_VAL="0x3c608045"
    MAIN="0x80006338"
    MAIN_TRAMPOLINE="0x80336068"
    FIRST_INSTRUCTION="0x9421fff0"
    RETURN_TO_MAIN="0x4bcd02d0"
else
    echo "Invalid region: $1"
    exit 1
fi

echo "Compiling for $1"
sed "s/@arenaLo:/$ARENALO:/g" patch.asm > regional-patch.asm
sed -i "s/@arenaLoVal/$ARENALO_VAL/g" regional-patch.asm
sed -i "s/@main:/$MAIN:/g" regional-patch.asm
sed -i "s/@mainTrampoline:/$MAIN_TRAMPOLINE:/g" regional-patch.asm
sed -i "s/@firstInstruction/$FIRST_INSTRUCTION/g" regional-patch.asm
sed -i "s/@returnMn/$RETURN_TO_MAIN/g" regional-patch.asm
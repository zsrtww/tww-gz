#!/bin/bash

clangFormatTargets=$(find . -type f ! -path './external/*' ! -path './build*' ! -path './common*' -type f -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx|c\)')

for inputFile in $clangFormatTargets
do
    clang-format-10 -style=file $inputFile > $inputFile-formatted
    diff $inputFile $inputFile-formatted
    if [ $? != 0 ] ; then
        rm $inputFile-formatted
        exit 1
    else
        rm $inputFile-formatted
    fi
done

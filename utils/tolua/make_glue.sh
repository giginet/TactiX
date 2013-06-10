#!/bin/sh
PROJECTNAME=TactiX
GLUEPATH=../../TactiX/Classes
GLUENAME=LuaBind
PACKAGENAME=tactix.pkg
HEADERPATH=../../TactiX/Classes/include
./tolua++ -n $PROJECTNAME -o ${GLUEPATH}/${GLUENAME}.cpp -H ${HEADERPATH}/${GLUENAME}.h $PACKAGENAME

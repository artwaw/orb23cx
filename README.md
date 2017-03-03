# Orbtalk to 3CX v.14 cost table converter
## This tool converts Orbtalks call rates CSV file into 3CX XML file ready to be upload into CDR prefixes cost settings.

* Build with Qt5.8/MinGW 5.3.0 x32
* To run some Qt libraries should be present on $PATH or in program dir:
    * Qt5Core.dll
    * Qt5Gui.dll
    * QtWidgets.dll
    * libwinpthread-1.dll
    * libstdc++-6.dll
    * libgcc_s_dw2-1.dll

* Icon is build and compiled into the .exe

## Broader desc:

3CX can use the table of prefixes associated with rates to estimate external call costs. Orbtalk provides calls table as CSV file.
Since prefix/ratio tables built into 3CX are not even remotely accurate I tried to incorporate Orbtalk's prefix table into the system.
* Problem: 3CX provides a table of 130 prefixes. Orbtalk's table is almost 58.000 prefixes.
*Solution: 3CX can import the table formated as simple XML file. This program takes input as CSV downloaded form Orbtalks giving XML as output.
The output file is ready to be uploaded into 3CX CDR setup window.

## Known issues:

* Not program related but 3CX can not take into the account one time fees for setting up the connection. So anyway number provided will not be 100% accurate.
* CDR to work requires the prefixes masks to be very precisely assigned. I.E.: 020 AND 20 as local, 00 as international, etc. Please refer to 3CX docs.


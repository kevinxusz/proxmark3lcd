proxmark3lcd
============

This repository contains working code for a Proxmark3 LCD device to read/write/emulate RFID tags.

Currently, only 125kHz HID tags have been successfully read and emulated.

This project incorporates code from two sources:

* [Proxmark3 @ Google Code](http://proxmark3.googlecode.com/svn/trunk)
* [Null Space Labs](http://www.032.la/svn/listing.php?repname=032&path=%2FProxmark3_LCD%2Ftrunk%2Fsource%2F&#a5f33ddfcd9ad27f6841dd37aa0812211)

Other resources: 
* [Null Space Labs' build notes](http://wiki.032.la/nsl/Proxmark3_LCD)
* [Original Proxmark3](http://cq.cx/proxmark3.pl)
* [Sourcery CodeBench Lite Edition](http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/)

I had a lot of trouble with flashing the device initially but ended up having a lot of success using a [Bus Pirate](http://dangerousprototypes.com/docs/Bus_Pirate) and OpenOCD. An example configuration file is present in tools/. Once bootrom.elf and fullimage.elf are built, it is possible to use the following commands in the telnet interface to flash the device:

\> halt  
\> flash erase\_sector 0 0 15  
\> flash erase\_sector 1 0 15  
\> flash write\_image ../armsrc/obj/fullimage.elf  
\> flash write\_image ../bootrom/obj/bootrom.elf  


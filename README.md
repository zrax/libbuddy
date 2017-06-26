General Information
===================

_libbuddy_ is a simple C library for manage _i-Buddy_ devices on _Linux_.

Installation
============

    ./configure
    make
    make install

Troubleshoot permissions:

Edit _/lib/udev/rules.d/60-libbuddy2.rules_ file: 

    SUBSYSTEMS=="usb", ATTRS{idVendor}=="1130", ATTRS{idProduct}=="00??", GROUP="ibuddy", SYMLINK+="ibuddy%n" 

and add your user to group _ibuddy_:

    sudo gpasswd -a $USER ibuddy

_tested on Ubuntu 16.04 LTS, Debian 6.0 (Squeeze), and Red Hat Enterprise 6_

Dependencies
============

 * libusb-1.0


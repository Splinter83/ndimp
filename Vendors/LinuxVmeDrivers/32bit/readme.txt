*******************************************************************************
*
* Concurrent Technologies Linux Enhanced VME Device Driver Package
*
* Copyright 2000-2009 Concurrent Technologies.
*
*
*******************************************************************************

1. Introduction

This software package contains the Concurrent Technologies Linux Enhanced VME device 
driver. This device driver allows the user to access the VME bus by providing 
an interface to the Tundra Universe II and TSI148 device.

This package contains  Linux VME driver kernel modules compiled for
RHEL4 and 5. The package also contains all the necessary files to allow the
user build their own kernel version of the driver.

_______________________________________________________________________________

2. Package Contents

readme.txt           - this file containing installation instructions.
history.txt          - version history information.
linuxenhancedvme_rev0X - linux enhanced VME device driver user guide
linuxvmeen-xx.i386.rpm - a rpm file containing the software where xx is the 
		       version number.
                       
_______________________________________________________________________________

3. Installing The Linux Enhanced VME Device Driver Package

Customers using legacy Linux VME driver would need to migrate to Enhanced API.

The software is distributed in Red Hat package format and therefore requires
the Red Hat Package Manager (rpm) to be installed on the target system.

You will need to be logged in as root user to install the package.

Copy the rpm file, from the distribution media, to a directory of your choice
on the target system.

Install the package by typing:

rpm -iv linuxvmeen-xx.i386.rpm    where xx is the version number

The following sub-directories and files will be created:

/usr/local/linuxvmeen
  ins         	           - Script file to load the driver module.
  uns         	           - Script file to unload the driver module.
  Makefile                 - Makefile to build the driver module.
  systest.sh               - Helper script used by the Makefile.
  vme_api_en.h             - Linux VME driver Enhanced API header file.
  vme_krnapi.c		       - Linux VME driver Kernel API file
  vme_driver.c             - Linux VME driver source file.
  vme_driver.h             - Linux VME driver header file.              
  vme_os.c                 - Operating system interface source file.
  vme_os.h                 - Operating system interface header file.
  vme_proc.c               - Proc file system interface source file.
  vme_proc.h               - Proc file system interface header file.
  vme_types.h              - Type definition header file.
  vme_version.h            - Version information header file.

/usr/local/linuxvmeen/kernel-x.x.xx.
  vmedriver.ko 	           - Linux VME driver kernel module.
  
/usr/local/linuxvmeen/cct_modules
  libcctvmeen.a            - Linux VME Enhanced API static library file.
  libvmedriver24.a         - Linux VME driver library file.
  libvmedriver26.a         - Linux VME driver library file.

/usr/local/linuxvmeen_util
  libcctvmeen.a            - Linux VME static library file (soft link).
  vme_api_en.h             - Linux VME driver enhanced API header file.
  linuxvmeen-xx.tgz          - Linux VME Utility program in a tar gzip file.
                             where xx is the version number

/usr/local/linuxvmeen_examples
  libcctvmeen.a            - Linux VME static library file (soft link).
  vme_api_en.h             - Linux VME driver Enhanced API header file.
  linuxvmeen_examples-xx.tgz - Example programs from the User Guide.
                             where xx is the version number

/usr/local/linuxvmeen_kapi_example
  linuxvmeen_kapi_example-xx.tgz - Example driver for Linux VME Kernel API
			         usage

If you wish to use the Linux VME Utility programs, they can be extracted
from the tar gzip files by typing:

tar -zxvf linuxvmeen-xx.tgz    where xx is the version number

The following files will be created in /usr/local/linuxvmeen_util.

  Makefile    - Makefile to build the Linux VME Utility program.
  main.c      - C source file for the Linux VME Utility program.
  main.h      - Header file for the Linux VME Utility program.
  thread.c    - C source file for the Linux VME Utility program.
  thread.h    - Header file for the Linux VME Utility program.
  linuxvmeen    - Executables for Linux VME Utility program 

Once the installation is complete, please refer to the User Guide for
information on using this device driver on a Concurrent Technologies VME board.

_______________________________________________________________________________

4. Building the Linux Enhanced VME Driver

First install the Linux Enhanced VME driver package on your development system as 
described above. The following will also be required:

GNU development tools (gcc, make, binutils etc), gcc version 3.2 or later.
A configured Linux kernel source tree, a version 2.4 or 2.6 kernel is required. 

The Linux Enhanced VME driver can be compiled by using the Makefile provided and this,
by default, will build the driver for the currently running kernel. If you wish
to build the driver for a kernel other than the running one you will need to 
change the kernel version and source location by editing the Makefile.

To build the Linux Enhanced VME Driver, change to Linux Enhanced VME driver directory and then
run make as follows:

cd /usr/local/linuxvmeen
make all

Once the build has completed, a new Linux Enhanced VME driver kernel module will have
been created in a kernel version sub-directory. Copy this file to your target
system and install the new Linux Enhanced VME driver kernel module in the normal way.

_______________________________________________________________________________

5. Uninstalling The Linux Enhanced VME Device Driver Package 

You will need to be logged in as root user to uninstall the package.

The software package can be removed by typing:

rpm -ev linuxvmeen

However, this will not remove the files extracted from the linuxvmeen-xxx.tgz
files or any files created in the sub-directories following the installation.
These will need to be removed manually.

_______________________________________________________________________________

6. Building the Linux VME Kernel API Example Driver

If you want to use the Linux VME Kernel API Example Driver,then it first needs
to be extracted from the tar gzip file by typing:

tar -zxvf linuxvmeen_kapi_example-xx.tgz    where xx is the version number

On untarring, following directories will be created.

example_driver           - Example driver demonstrating the usage of
                           the Linux VME Kernel APIs
example_app              - Example application used to invoke the
                           above mentioned example driver

To build the  example driver, change to the example driver directory and then 
run the following.Please note that in case of Linux 2.6 kernels, you first
need to built the linux VME driver to generate the Module.symvers file which needs
to be then copied to the local folder of the example driver:

Linux 2.6 Kernels:
cd /usr/local/linuxvmeen_kapi_example/example_driver/
cp ../../linuxvmeen/vme_api_en.h .
cp ../../linuxvmeen/Module.symvers .   
make

Linux 2.4 Kernels:
cd /usr/local/linuxvmeen_kapi_example/example_driver/
cp ../../linuxvmeen/vme_api_en.h .
make

Once the driver is built,use the ins and uns script to install and uninstall
the driver.The application program in the example_app directory can then be
used to issue the ioctls which execute the test code.

_______________________________________________________________________________

7. BIOS Configurations

You will need to configure the PCI address window in the BIOS for some of the
boards as the driver will be allocating the PCI addresses when configuring the 
PCI slave images from this PCI address window.Also on some boards,you can 
reserve physical memory from the BIOS which will be then used for the VME images
and DMA by the driver.Please refer the user manual for more details.

_______________________________________________________________________________

8. Known Issues

The Linux kernel, version 2.4.2, shipped with Red Hat 7.1 does not handle memory 
reserved at boot time correctly. Hence, the Linux VME driver DMA and VME image
functions will not work properly with this kernel. If you need these capabilities
you can either upgrade your Linux kernel, version 2.4.9 has been verified to work,
or use another method of obtaining reserved memory along with the Linux VME driver
vme_reserveMemory function.


The automatic probing, used by the Linux Vme driver, to determine the size of
reserved memory is disabled on boards which have a chipset with an integrated
graphics controller e.g. the VP 315/01x board. In this case, the reserved memory
size can be passed to the Linux VME driver, as a module parameter, at load time. 
Please see the script file provided, to load the driver, and the User Guide for 
more information on the module load options and reserving memory.


The SMP Linux kernel, shipped with Red Hat Enterprise 4.0, does not setup
APIC operation correctly when used on a VX 405/04x board. It is therefore necessary
to update the kernel to a newer version. Linux kernels 2.6.11.6, 2.6.17 and
2.6.17.8 have been verified to work correctly on this board.

_______________________________________________________________________________



#include "../include/OPB_interface.h"

#ifndef LINUX_VERSION_CODE
	#include <linux/version.h>
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18))
  #define PAGE_SIZE sysconf(_SC_PAGESIZE)
#else
  #include <asm/page.h>
#endif


#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#include "../include/OPB_globals.h"


//extern int devHandle;

EN_PCI_IMAGE_DATA idata;

/*!
 * Initilialize VME board interface
 * @return Returns device handle, -1 otherwise
 */
int init_board(const EN_VME_DEVICE device_type, const UINT32 vme_lower_address, const UINT32 data_width) {
	int devHandle;
	memset((char *) &idata, 0, sizeof(EN_PCI_IMAGE_DATA));
	devHandle = vme_openDevice(device_name[device_type]);

	if (devHandle < 0) {
		printf("Unable to open PCI image 0\n");
		return -1;
	} else {
		if (open_image(devHandle, vme_lower_address, data_width) < 0){
			return -1;
		}
	}
	return devHandle;
}

int init_interrupt_board(){
	int ctrlHandle;
	ctrlHandle = vme_openDevice(device_name[EN_CTL]);
	if (ctrlHandle < 0) {
			printf("Unable to open CTL image 0\n");
			return -1;
	}
	return ctrlHandle;
}

int open_image(const int dev_handle, const UINT32 vme_base_add, const UINT32 data_width){
	memset((char *) &idata, 0, sizeof(EN_PCI_IMAGE_DATA));
	idata.pciAddress = 0;
	idata.pciAddressUpper = 0;
	idata.vmeAddress = vme_base_add;
	idata.vmeAddressUpper = 0;
	idata.size = IMAGE_SIZE;
	idata.sizeUpper = 0;
	idata.readPrefetch = 1;
	idata.prefetchSize = 0;
	idata.postedWrites = 1;
	idata.sstMode = 0;
	idata.dataWidth = data_width;
	idata.addrSpace = EN_VME_A32;
	idata.type = EN_LSI_DATA;
	idata.mode = EN_LSI_USER;
	idata.vmeCycle = 0;
	idata.sstbSel = 0;
	idata.ioremap = 1;

	if (vme_enablePciImage(dev_handle, &idata) < 0) {
		printf("Error - failed to enable PCI image 0 (%s)\n",
				strerror(errno));
		return -1;
	}

	return 0;
}

/*!
 * Closes devHandle argument board interface
 * @param devHandle
 * @return 0 if OK, otherwise a negative number
 */
int close_device(int devHandle) {
	int result;
	result = vme_disablePciImage(devHandle);
	if (result < 0) {
		printf("Error - failed to disable PCI image 0 (%s)\n", strerror(errno));
		return result;
	}
	vme_closeDevice(devHandle);
	return 0;
}

int openbus_read(int devHandle, UINT16 regAddr) {

	int result = 0;
	UINT8 buf[2];
	//On word read -> Big Endian
	result = vme_read(devHandle, regAddr, buf, 2);

	if (result < 0) {
		printf("Error - failed to read data (%s)\n", strerror(errno));
		return -1;
	}

	return (buf[0] | (buf[1] << 8));

}

int openbus_write(int devHandle, UINT16 regAddr, UINT16 val) {

	int result;
	UINT8 buf[2];
//On word write -> Big Endian
	buf[1] = (val & 0xFF00) >> 8;
	buf[0] = (val & 0xFF);

	result = vme_write(devHandle, regAddr, buf, 2);
	if (result < 0) {
		printf("Error - failed to write data (%s)\n", strerror(errno));
	}

	return result;

}

int openbus_write32(int devHandle, UINT16 addr, UINT32 val) {
	int result;
	UINT8 buf[4];

	buf[0] = (val & 0xff000000) >> 24;
	buf[1] = (val & 0xff0000) >> 16;
	buf[2] = (val & 0xff00) >> 8;
	buf[3] = (val & 0xff);

	result = vme_write(devHandle, addr, buf, 4);

	if (result < 0) {
		printf("Error - failed to write data (%s)\n", strerror(errno));
	}

	return result;
}

int openbus_read32(int devHandle, UINT16 addr, UINT8 *error) {

	int result = 0;
	UINT8 buf[4];
	*error = 0;
	int i = 0;

	result = vme_read(devHandle, addr, buf, 4);

	if (result < 0) {
		printf("Error - failed to read data (%s)\n", strerror(errno));
		*error = 1;
		return -1;
	}

	result = 0;

	for(i; i < 4; ++i)
		result |= (buf[3-i] << (i * 8));

	return result;

}

int openbus_read8(int devHandle, UINT16 regAddr){
	int result = 0;
	UINT8 buf[1];

	result = vme_read(devHandle, regAddr, buf, 1);

	if (result < 0) {
		printf("Error - failed to read data (%s)\n", strerror(errno));
		return -1;
	}

	return buf[0];
}

int openbus_read24(int devHandle, UINT16 regAddr){
	int result = 0;
	UINT8 buf[3];
	int i = 0;

	result = vme_read(devHandle, regAddr, buf, 3);
//On triple read -> Big Endian
	if (result < 0) {
		printf("Error - failed to read data (%s)\n", strerror(errno));
		return -1;
	}

	result = 0;

	for(i = 0; i < 3; ++i)
		result |= (buf[i] << (i * 8));

	return result;
}

int openbus_write8(int devHandle, UINT16 addr, UINT8 val){
	int result;
	UINT8 buf[1];

	buf[0] = val;

	result = vme_write(devHandle, addr, buf, 1);
	if (result < 0) {
		printf("Error - failed to write data (%s)\n", strerror(errno));
	}

	return result;
}

int openbus_write24(int devHandle, UINT16 addr, UINT32 val){
	int result;
	UINT8 buf[3];
//On triple write -> Big Endian
	buf[2] = (val & 0xFF0000) >> 16;
	buf[1] = (val & 0xFF00) >> 8;
	buf[0] = (val & 0xFF);

	result = vme_write(devHandle, addr, buf, 3);
	if (result < 0) {
		printf("Error - failed to write data (%s)\n", strerror(errno));
	}

	return result;
}

int openbus_enableIncomingInterrupt(INT32 deviceHandle){
	int result = 0;
	result = vme_setInterruptMode(deviceHandle,EN_INT_MODE_RORA);
	if(result != 0){
		printf("Error - failed to set interrupt as RORA  (%s)\n", strerror(errno));
		return result;
	}
	result = vme_enableInterrupt(deviceHandle,EN_IRQ1);
	if(result != 0){
		printf("Error - failed to enable interrupt (%s)\n", strerror(errno));
		return result;
	}
	return result;
}

int openbus_WaitInterruptVIRQ1(INT32 deviceHandle,UINT32 waitTimer){
    int result = 0;
    const UINT32 selectedInts = 0x1;
    UINT32 intNum;

    result = vme_waitInterrupt(deviceHandle,selectedInts,waitTimer,&intNum);

    if((result != 0) || (intNum & 0x80000000)){
		printf("Error - failed to wait interrupt IRQ1  (%s)\n", strerror(errno));
		return result;
    }

    if(!(intNum & selectedInts)){
    	printf("Error - unexpected interrupt received\n");
    	return -1;
    }

    return result;
}

int openbus_ReadInterrupt(INT32 deviceHandle,UINT32* status){
	int result = 0;
	EN_VME_INT_INFO info;
	result = vme_readInterruptInfo(deviceHandle,&info);
	if(result < 0){
		printf("Error - failed to read interrupt info for IRQ1  (%s)\n", strerror(errno));
		return result;
	}

	if(info.intNum & 0x1){
		/*TODO
		 * LEGGERE VALORI
		 * */
		;
	}

	return result;
}


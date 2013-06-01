#ifndef OPB_INTERFACE_H_
#define OPB_INTERFACE_H_

#include "OPB_definitions.h"
#include "vme_api_en.h"

#define VME_ADDRESS_LOWER 0x20000000
#define VME_OPT_DEFAULT_ADDR 0x28000000
#define IMAGE_SIZE 0x10000

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * Initializes PCI-VME board
 * @param  device_type Device to be opened.
 * @param vme_lower_address VME lower address
 * @param data_width Width of data to be transfered (0 = 8bit, 1 = 16bit, 2 = 32bit)
 * @return A number \< 0 if it was unable to open the PCI image, otherwise the device handle
 */
int init_board(const EN_VME_DEVICE device_type, const UINT32 vme_lower_address, const UINT32 data_width);

/**
 * Initializes VME control image
 * @return A number \< 0 if it was unable to open the Control image, otherwise the control device handle
 */
int init_interrupt_board();

/*!
 * Open a VME window of 64KB size
 * @param dev_handle Device handler returned by init_board function
 * @param vme_base_add VME base address
 * @param data_width Width of data to be transfered (0 = 8bit, 1 = 16bit, 2 = 32bit)
 * @return 0 if ok, -1 otherwise
 */
int open_image(const int dev_handle, const UINT32 vme_base_add, const UINT32 data_width);

/*!
 * Closes a device
 * @param devHandle Device handler returned by init_board function
 * @return
 */
int close_device(int devHandle);

// Read Write Functions

/*!
 * Writes the argument \c val to \c regAddr argument address
 * @param regAddr Address
 * @param val Value
 */
int openbus_write(int devHandle, UINT16 regAddr, UINT16 val);

/*!
 * Returns read data from \c regAddr argumetn address
 * @param regAddr Address
 * @return Read data
 */
int openbus_read(int devHandle, UINT16 regAddr);

int openbus_read8(int devHandle, UINT16 regAddr);
int openbus_read24(int devHandle, UINT16 regAddr);
int openbus_read32(int devHandle, UINT16 addr, UINT8 *error);

int openbus_write8(int devHandle, UINT16 addr, UINT8 val);
int openbus_write24(int devHandle, UINT16 addr, UINT32 val);
int openbus_write32(int devHandle, UINT16 addr, UINT32 val);


int openbus_enableIncomingInterrupt(INT32 deviceHandle);
int openbus_WaitInterruptVIRQ1(INT32 deviceHandle, UINT32 waitTimer);
int openbus_ReadInterrupt(INT32 deviceHandle,UINT32* status);

#ifdef __cplusplus
}
#endif

#endif //OPB_INTERFACE_H_

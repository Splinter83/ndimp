/*
 * Skeleton.cpp
 *
 *  Created on: 08/set/2012
 *      Author: grande
 */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "Skeleton.h"
#include "external_vars.h"

#include "Logger.h"

#include "VmeAbstractionDevice.h"
#include "GlobalTypes.h"

Skeleton::Skeleton() {
	uno_walking = 0x1;
}

UINT8 Skeleton::execTest(const BoardInterfaceType& bt,int num_argomenti, ...) {

	Logger::getLogger()->Log(INFO_LEVEL, "***Start Skeleton Test***");

/*	va_list argP;
	va_start(argP, num_argomenti);
	int i = va_arg(argP, int);
	va_end(argP);
*/
	SKELETON_ADDRESS = GlobalData::instance()->GetInterfaceData(bt)->arbitered_io + 0x4;

	int shift = 0;
	for (int i = 0; i < 16; i++) {
		uno_walking = 1;
		if ((i < 4) || (i == 8)) {
			uno_walking <<= shift;
			vmeDev->write(SKELETON_ADDRESS, uno_walking);
			usleep(MSEC_TO_USEC(2));
			vmeDev->read(SKELETON_ADDRESS, uno_walking_read);
			if (uno_walking_read != uno_walking ) {
				snprintf(this->strError,MAX_BUF_SIZE,"Error during Skeleton Test:\n"
						"The expected value at address 0x%08x is 0x%04x,"
						"while the read value is 0x%04x", SKELETON_ADDRESS, uno_walking, uno_walking_read);

				Logger::getLogger()->Log(INFO_LEVEL,
						"***Error: Skeleton Test: the value expected in the uno walking was %x, the value read is %x***",
						uno_walking << shift, uno_walking_read);
				return TEST_NOK;
			}
			if(i == 8)
				break;
			if (i == 3) {
				shift = 8;
				i = 7; //jump to 8th bit
			} else {
				shift++;
			}
		}
	}

	Logger::getLogger()->Log(INFO_LEVEL, "***End Skeleton Test***");

	return 0;
}


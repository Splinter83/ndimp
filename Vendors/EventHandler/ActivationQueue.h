/*
 * SimpStimpProject: ActivationQueue.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef ACTIVATIONQUEUE_H_
#define ACTIVATIONQUEUE_H_

#include "OOQueue.h"

class IActiveObjectCommand;

typedef OOQueue<IActiveObjectCommand *> ActivationQueue;

#endif /* ACTIVATIONQUEUE_H_ */

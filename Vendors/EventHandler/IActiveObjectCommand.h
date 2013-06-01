/*
 * SimpStimpProject: IActiveObjectCommand.h
 *
 *  Created on: 05/ott/2012
 *  Author: Emanuele Galli
 *  Copyright 2012 Sky-Technologies Srl.
 */

#ifndef IACTIVEOBJECTCOMMAND_H_
#define IACTIVEOBJECTCOMMAND_H_

class ActiveObject;

class IActiveObjectCommand {
public:
	IActiveObjectCommand();
	virtual ~IActiveObjectCommand();

    ////    Operations    ////

    virtual void Destroy() = 0;

    virtual void Execute(ActiveObject * context) = 0;
};

#endif /* IACTIVEOBJECTCOMMAND_H_ */

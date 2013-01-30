/*
 * ProcessorAllocater.h
 *
 *  Created on: 2012/11/30
 *      Author: sakakibara
 */

#ifndef PROCESSORALLOCATER_H_
#define PROCESSORALLOCATER_H_

#include "../common/Common.h"
#include "EventTask.h"
#include "../data/Signal.h"
#include "../service/UnixDomainSocketManager.h"

class ProcessorAllocater : public EventTask {
public:
	ProcessorAllocater(Library* lib);
	virtual ~ProcessorAllocater();

	cl_int doTask(SocketData* socketData, UnixDomainSocketManager* manager);
};

#endif /* PROCESSORALLOCATER_H_ */

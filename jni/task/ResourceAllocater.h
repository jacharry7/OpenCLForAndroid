/*
 * ResourceAllocater.h
 *
 *  Created on: 2012/12/01
 *      Author: sakakibara
 */

#ifndef RESOURCEALLOCATER_H_
#define RESOURCEALLOCATER_H_

#include "../common/Common.h"
#include "EventTask.h"
#include "../data/Signal.h"
#include "../service/UnixDomainSocketManager.h"

class ResourceAllocater : public EventTask {
public:
	ResourceAllocater(Library* lib);
	virtual ~ResourceAllocater();

	cl_int doTask(SocketData* socketData, UnixDomainSocketManager* manager);
};

#endif /* RESOURCEALLOCATER_H_ */

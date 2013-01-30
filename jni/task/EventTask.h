/*
 * EventTask.h
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#ifndef EVENTTASK_H_
#define EVENTTASK_H_

#include "../common/Common.h"
#include "../common/Converter.h"
#include "../common/Library.h"
#include "../data/SocketData.h"
#include "../service/UnixDomainSocketManager.h"

class EventTask {
public:
	Library* mLib;

	EventTask(Library* lib);
	virtual ~EventTask();

	virtual cl_int doTask(SocketData* socketData, UnixDomainSocketManager* manager) = 0;
	virtual SocketData* convertToSoketData(string data);
	virtual string convertToSendData(SocketData* socketData);
};

#endif /* EVENTTASK_H_ */

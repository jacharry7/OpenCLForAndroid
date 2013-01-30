/*
 * ProcessorInfoManager.h
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#ifndef PROCESSORINFOMANAGER_H_
#define PROCESSORINFOMANAGER_H_

#include "../common/Common.h"
#include "EventTask.h"
#include "../data/Signal.h"
#include "../service/UnixDomainSocketManager.h"

class ProcessorInfoManager : public EventTask {
private:
	DeviceTable* getDeviceTable();
	int setDeviceTable(DeviceTable* devTable);
	vector<cl_device_id>* getDevices();
public:
	ProcessorInfoManager(Library* lib);
	virtual ~ProcessorInfoManager();
	string getDeviceNameListStr(DeviceTable* devTable);

	cl_int doTask(SocketData* socketData, UnixDomainSocketManager* manager);
};

#endif /* PROCESSORINFOMANAGER_H_ */

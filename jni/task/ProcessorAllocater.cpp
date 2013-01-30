/*
 * ProcessorAllocater.cpp
 *
 *  Created on: 2012/11/30
 *      Author: sakakibara
 */

#include "ProcessorAllocater.h"

ProcessorAllocater::ProcessorAllocater(Library* lib) :
		EventTask(lib) {

}

ProcessorAllocater::~ProcessorAllocater() {
}

cl_int ProcessorAllocater::doTask(SocketData* socketData,
		UnixDomainSocketManager* manager) {
	string sendData;
	string ret;
	string data;
	SocketData* tmpSocketData;

	switch (socketData->getSignal()->getIntVal()) {
	case SIGNAL_INSTRUCT_PROCESSOR:
		sendData = convertToSendData(socketData);
		ret = manager->start(sendData);
		// data copy
		tmpSocketData = convertToSoketData(ret);
		socketData->getExecData()->setDeviceName(
				tmpSocketData->getExecData()->getDeviceName(
						FLAG_DEVICE_CURRENT), FLAG_DEVICE_CURRENT);
		socketData->getExecData()->setDeviceType(
				tmpSocketData->getExecData()->getDeviceType(
						FLAG_DEVICE_CURRENT), FLAG_DEVICE_CURRENT);
		delete tmpSocketData;
		break;
	default:
		break;
	}

	return CL_SUCCESS;
}

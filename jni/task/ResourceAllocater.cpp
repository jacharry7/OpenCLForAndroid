/*
 * ResourceAllocater.cpp
 *
 *  Created on: 2012/12/01
 *      Author: sakakibara
 */

#include "ResourceAllocater.h"

ResourceAllocater::ResourceAllocater(Library* lib) :
		EventTask(lib) {

}

ResourceAllocater::~ResourceAllocater() {
}

cl_int ResourceAllocater::doTask(SocketData* socketData,
		UnixDomainSocketManager* manager) {
	string sendData;
	string ret;
	string data;
	SocketData* tmpSocketData;
	KernelCode* tmpKernel;
	ResourceSizeData* tmpResData;
	WorkItemSizeList* tmpWsList;
	ResourceSizeData* resData;

	switch (socketData->getSignal()->getIntVal()) {
	case SIGNAL_INSTRUCT_RESOURCES:
		sendData = convertToSendData(socketData);
		ret = manager->start(sendData);
		// data copy
		tmpSocketData = convertToSoketData(ret);
//		tmpSocketData->print();
		tmpKernel = tmpSocketData->getExecData()->getKernelCode(KERNEL_INDEX);
		if (tmpKernel != NULL) {
			for (int i = 0; i < tmpKernel->getFuncNum(); i++) {
				resData =
						socketData->getExecData()->getKernelCode(KERNEL_INDEX)->getFuncData(
								i)->getResourceSize(FLAG_DEVICE_CURRENT);
				tmpResData = tmpKernel->getFuncData(i)->getResourceSize(
						FLAG_DEVICE_CURRENT);
				// loop flg = FLAG_GLOBAL or LOCAL_WORKSIZE
				for (int flg = 0; flg < 2; flg++) {
					tmpWsList = tmpResData->getWorkSizeList(flg);
					for (int index = 0; index < tmpWsList->getDim(); index++) {
						resData->addWorkItemSize(tmpWsList->getSize(index),
								flg);
					}
				}
			}
		}
		delete tmpSocketData;
		break;
	default:
		break;
	}

	return CL_SUCCESS;
}

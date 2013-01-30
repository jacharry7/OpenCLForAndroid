/*
 * ProcessorInfoManager.cpp
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#include "ProcessorInfoManager.h"

ProcessorInfoManager::ProcessorInfoManager(Library* lib) :
		EventTask(lib) {
}

ProcessorInfoManager::~ProcessorInfoManager() {
}

cl_int ProcessorInfoManager::doTask(SocketData* socketData,
		UnixDomainSocketManager* manager) {
	string sendData;
	string ret;
	string data;

	switch (socketData->getSignal()->getIntVal()) {
	case SIGNAL_CONNECT_APP:
		// deviceTable取得
		setDeviceTable(socketData->getExecData()->getDevTable());
#ifdef DEBUG
		socketData->getExecData()->getDevTable()->print();
#endif
		sendData = convertToSendData(socketData);
		ret = manager->start(sendData);
#ifdef DEBUG
		printf("ret : %s\n", ret.c_str());
#endif
		// signalがSIGNAL_CONNECT_DATA_LOADの場合、下のcaseへ
		if (Converter::toSignal(ret) != SIGNAL_CONNECT_DATA_LOAD) {
			break;
		}
	case SIGNAL_CONNECT_DATA_LOAD:
		/* TODO 他に取得するものを入れる */
		socketData->setSignal(SIGNAL_CONNECT_DATA_LOAD);
		data = getDeviceNameListStr(socketData->getExecData()->getDevTable());
		socketData->setData(data);
		sendData = convertToSendData(socketData);
		ret = manager->start(sendData);
		break;
	default:
		break;
	}

	return CL_SUCCESS;
}
int ProcessorInfoManager::setDeviceTable(DeviceTable* devTable) {

	//
	// platformsの取得
	//
	cl_platform_id* platforms;
	cl_uint num_platforms;
	// get number of available platforms
	cl_int err = mLib->clGetPlatformIDs(0, NULL, &num_platforms);
//	printf("err=%d,num_platforms=%d\n", err, num_platforms);
	if (CL_SUCCESS != err) {
		printf("err!\n");
		return -1;
	}
	platforms = (cl_platform_id*) malloc(
			sizeof(cl_platform_id) * num_platforms);
	if (NULL == platforms) {
		printf("malloc err!\n");
		return -1;
	}
	err = mLib->clGetPlatformIDs(num_platforms, platforms, NULL);
	/*	for (unsigned int ui = 0; ui < num_platforms; ui++) {
	 printf("clGetPlatformIDs err=%d platforms[%d]=%x\n", err, ui,
	 (unsigned int) platforms[0]);
	 }
	 */
	if (CL_SUCCESS != err) {
		printf("clGetPlatformIDs err!\n");
		return -1;
	}

	//
	// deviceListの取得
	//
	int size = 0;
	cl_device_id* devices;
	cl_uint num_devices = 0;
	for (cl_uint ui = 0; ui < num_platforms; ++ui) {
		err = mLib->clGetDeviceIDs(platforms[ui], CL_DEVICE_TYPE_ALL, 0, NULL,
				&num_devices);
//		printf("clGetDeviceIDs err=%d,num_devices=%d\n", err, num_devices);
		if (CL_SUCCESS != err) {
			printf("err!\n");
			return -1;
		}
		devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
		if (NULL == devices) {
			printf("malloc err!\n");
			return -1;
		}
		err = mLib->clGetDeviceIDs(platforms[ui], CL_DEVICE_TYPE_ALL,
				num_devices, devices, NULL);
		if (CL_SUCCESS != err) {
			printf("err!\n");
			return -1;
		}
		char name[64];
		for (cl_uint uid = 0; uid < num_devices; ++uid) {
			/*			printf("clGetDeviceIDs err=%d,devices[%d]=%x\n", err, ui,
			 (unsigned int) devices[ui]);
			 */
			err = mLib->clGetDeviceInfo(devices[uid], CL_DEVICE_NAME, sizeof(char) * 64,
					name, NULL);
			devTable->insertNameTable(devices[uid], name);
			devTable->insertPlatTable(devices[uid], platforms[ui]);
//			deviceList->push_back(devices[ui]);
			size++;
		}
		delete devices;
	}
	delete platforms;
	return size;
/*
	char name[64];
	cl_int err;
	int size = 0;
	vector<cl_device_id>* devList = getDevices();
	size = devList->size();
	if (devList == NULL)
		return 0;
	vector<cl_device_id>::iterator it = devList->begin(); // イテレータのインスタンス化
	while (it != devList->end()) // 末尾要素まで
	{
		err = mLib->clGetDeviceInfo(*it, CL_DEVICE_NAME, sizeof(char) * 64,
				name, NULL);
		if (CL_SUCCESS != err) {
			printf("clGetDeviceInfo err!\n");
			return 0;
		}
		devTable->insertNameTable(*it, name);
		++it; // イテレータを１つ進める
	}
	delete devList;
*/

}

vector<cl_device_id>* ProcessorInfoManager::getDevices() {
	//
	// platformsの取得
	//
	cl_platform_id* platforms;
	cl_uint num_platforms;
	// get number of available platforms
	cl_int err = mLib->clGetPlatformIDs(0, NULL, &num_platforms);
//	printf("err=%d,num_platforms=%d\n", err, num_platforms);
	if (CL_SUCCESS != err) {
		printf("err!\n");
		return NULL;
	}
	platforms = (cl_platform_id*) malloc(
			sizeof(cl_platform_id) * num_platforms);
	if (NULL == platforms) {
		printf("malloc err!\n");
		return NULL;
	}
	err = mLib->clGetPlatformIDs(num_platforms, platforms, NULL);
	/*	for (unsigned int ui = 0; ui < num_platforms; ui++) {
	 printf("clGetPlatformIDs err=%d platforms[%d]=%x\n", err, ui,
	 (unsigned int) platforms[0]);
	 }
	 */
	if (CL_SUCCESS != err) {
		printf("clGetPlatformIDs err!\n");
		return NULL;
	}

	//
	// deviceListの取得
	//
	vector<cl_device_id>* deviceList = new vector<cl_device_id>();
	cl_device_id* devices;
	cl_uint num_devices = 0;
	for (cl_uint ui = 0; ui < num_platforms; ++ui) {
		err = mLib->clGetDeviceIDs(platforms[ui], CL_DEVICE_TYPE_ALL, 0, NULL,
				&num_devices);
//		printf("clGetDeviceIDs err=%d,num_devices=%d\n", err, num_devices);
		if (CL_SUCCESS != err) {
			printf("err!\n");
			return NULL;
		}
		devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
		if (NULL == devices) {
			printf("malloc err!\n");
			return NULL;
		}
		err = mLib->clGetDeviceIDs(platforms[ui], CL_DEVICE_TYPE_ALL,
				num_devices, devices, NULL);
		if (CL_SUCCESS != err) {
			printf("err!\n");
			return NULL;
		}

		for (cl_uint ui = 0; ui < num_devices; ++ui) {
			/*			printf("clGetDeviceIDs err=%d,devices[%d]=%x\n", err, ui,
			 (unsigned int) devices[ui]);
			 */
			deviceList->push_back(devices[ui]);
		}
		delete devices;
	}
	delete platforms;

	return deviceList;
}

string ProcessorInfoManager::getDeviceNameListStr(DeviceTable* devTable) {
	string str = "";
	map<cl_device_id, string>* table = devTable->getNameTable();
	for (map<cl_device_id, string>::iterator itpairstri = table->begin();
			itpairstri != table->end(); itpairstri++) {
		// イテレータは pair<const cl_device_id, string> 型なので、
		str += itpairstri->second + DATA_SEPARATOR + DATA_ARRAY_SEPARATOR;
	}
	return str;
}


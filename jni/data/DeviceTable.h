/*
 * DeviceTable.h
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#ifndef DEVICETABLE_H_
#define DEVICETABLE_H_

#include "../common/Common.h"

class DeviceTable {
private:
	map<cl_device_id, string> mDevNameTable;
	map<cl_device_id, cl_platform_id> mDevPlatTable;
public:
	DeviceTable();
	virtual ~DeviceTable();

	string getDeviceNameFromDevId(cl_device_id deviceId);
	cl_device_id getDeviceIdFromName(string deviceName);
	cl_platform_id getPlatIdFromDevId(cl_device_id deviceId);
	cl_device_id getDeviceIdFromPlatId(cl_platform_id platformId);

	map<cl_device_id, string>* getNameTable();
	void setNameTable(map<cl_device_id, string> devTable);
	map<cl_device_id, cl_platform_id>* getPlatTable();
	void setPlatTable(map<cl_device_id, cl_platform_id> devTable);

	void insertNameTable(cl_device_id deviceId, string name);
	void insertPlatTable(cl_device_id deviceId, cl_platform_id platId);

	void print();
	void copy(DeviceTable* origin);
};

#endif /* DEVICETABLE_H_ */

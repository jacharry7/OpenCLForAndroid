/*
 * DeviceTable.cpp
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#include "DeviceTable.h"

DeviceTable::DeviceTable() {

}

DeviceTable::~DeviceTable() {
}

string DeviceTable::getDeviceNameFromDevId(cl_device_id deviceId) {
	return mDevNameTable[deviceId];
}

cl_device_id DeviceTable::getDeviceIdFromName(string deviceName) {
	for (map<cl_device_id, string>::iterator itpair = mDevNameTable.begin();
			itpair != mDevNameTable.end(); itpair++) {
		if(itpair->second == deviceName){
			return itpair->first;
		}
	}
	printf("getDeviceIdFromName : No DeviceId From Name(%s)\n",deviceName.c_str());
	return NULL;
}

cl_platform_id DeviceTable::getPlatIdFromDevId(cl_device_id deviceId){
	return mDevPlatTable[deviceId];
}
cl_device_id DeviceTable::getDeviceIdFromPlatId(cl_platform_id platformId){
	for (map<cl_device_id, cl_platform_id>::iterator itpair = mDevPlatTable.begin();
			itpair != mDevPlatTable.end(); itpair++) {
		if(itpair->second == platformId){
			return itpair->first;
		}
	}
	return NULL;
}


map<cl_device_id, string>* DeviceTable::getNameTable() {
	return &mDevNameTable;
}

void DeviceTable::setNameTable(map<cl_device_id, string> devTable) {
	mDevNameTable = devTable;
}
map<cl_device_id, cl_platform_id>* DeviceTable::getPlatTable(){
	return &mDevPlatTable;
}
void DeviceTable::setPlatTable(map<cl_device_id, cl_platform_id> devTable){
	mDevPlatTable = devTable;
}

void DeviceTable::insertNameTable(cl_device_id device_id, string name) {
	mDevNameTable.insert(map<cl_device_id, string>::value_type(device_id, name));
}
void DeviceTable::insertPlatTable(cl_device_id deviceId, cl_platform_id platId){
	mDevPlatTable.insert(map<cl_device_id, cl_platform_id>::value_type(deviceId, platId));
}


void DeviceTable::print() {
	printf("devNameTable :");
	for (map<cl_device_id, string>::iterator itpair = mDevNameTable.begin();
			itpair != mDevNameTable.end(); itpair++) {
		cl_device_id devId = itpair->first; // イテレータからキーが得られる。
		string name = itpair->second; // イテレータから値が得られる。
		printf("(%x, %s),", (unsigned int) devId, name.c_str());
	}
	printf("\ndevPlatTable :");
	for (map<cl_device_id, cl_platform_id>::iterator itpair = mDevPlatTable.begin();
			itpair != mDevPlatTable.end(); itpair++) {
		cl_device_id devId = itpair->first; // イテレータからキーが得られる。
		cl_platform_id platId = itpair->second; // イテレータから値が得られる。
		printf("(%x, %x),", (unsigned int) devId, (unsigned int)platId);
	}
	printf("\n");
}

void DeviceTable::copy(DeviceTable* origin){
	for (map<cl_device_id, string>::iterator itpair = origin->mDevNameTable.begin();
			itpair != origin->mDevNameTable.end(); itpair++) {
		mDevNameTable.insert(map<cl_device_id, string>::value_type(itpair->first, itpair->second));
	}
	for (map<cl_device_id, cl_platform_id>::iterator itpair = origin->mDevPlatTable.begin();
			itpair != origin->mDevPlatTable.end(); itpair++) {
		mDevPlatTable.insert(map<cl_device_id, cl_platform_id>::value_type(itpair->first, itpair->second));
	}
}

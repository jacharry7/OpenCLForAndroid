/*
 * ExecData.cpp
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#include "ExecData.h"

ExecData::ExecData() {
	mStartTime = 0;
	mExecTime = 0;
	mKernelNum = 0;
	mDeviceType[0] = 0;
	mDeviceType[1] = 0;
}
ExecData::~ExecData() {

}

//override
string ExecData::createSendData() {
	string sendData;
	sendData += createStartTag(TAG_EXECDATA);
	if (mAppId != "") {
		sendData += createTag(TAG_APPID, mAppId);
	}
	stringstream ss;
	if (mStartTime != 0) {
		ss << mStartTime;
		sendData += createTag(TAG_STARTTIME, ss.str());
		ss.clear();
		ss.str("");
	}
	if (mExecTime != 0) {
		ss << mExecTime;
		sendData += createTag(TAG_EXECTIME, ss.str());
		ss.clear();
		ss.str("");
	}
	if (mDeviceName[0] != "") {
		sendData += createTag(TAG_DEVICENAME_SELECTED, mDeviceName[0]);
	}
	if (mDeviceName[1] != "") {
		sendData += createTag(TAG_DEVICENAME, mDeviceName[1]);
	}
	if (mDeviceType[0] != 0) {
		ss << mDeviceType[0];
		sendData += createTag(TAG_DEVICETYPE_SELECTED, ss.str());
		ss.clear();
		ss.str("");
	}
	if (mDeviceType[1] != 0) {
		ss << mDeviceType[1];
		sendData += createTag(TAG_DEVICETYPE, ss.str());
		ss.clear();
		ss.str("");
	}
	if(mKernelNum != 0){
		ss << mKernelNum;
		sendData += createTag(TAG_KERNELNUM, ss.str());
		ss.clear();
		ss.str("");
	}
	//kernellist
	if (mKernelCodeList.size() != 0) {
		sendData += createStartTag(TAG_KERNELLIST);
		for (int i = 0; i < mKernelCodeList.size(); i++) {
			sendData += mKernelCodeList[i].createSendData();
		}
		sendData += createEndTag(TAG_KERNELLIST);
	}
	sendData += createEndTag(TAG_EXECDATA);
	return sendData;
}
void ExecData::print() {
	printf("//---ExecData------------\n");

	if (mAppId != "")
		printf("appId : %s\n", mAppId.c_str());
	if (mStartTime != 0)
		printf("startTime : %ld\n", mStartTime);
	if (mExecTime != 0)
		printf("execTime : %ld\n", mExecTime);
	if (mDeviceName[0] != "")
		printf("deviceNameSelected : %s\n", mDeviceName[0].c_str());
	if (mDeviceName[1] != "")
		printf("deviceName : %s\n", mDeviceName[1].c_str());
	if (mDeviceType[0] != 0)
		printf("deviceTypeSelected : %lu\n", (unsigned long) mDeviceType[0]);
	if (mDeviceType[1] != 0)
		printf("deviceType : %lu\n", (unsigned long) mDeviceType[1]);
	if (mKernelNum != 0)
		printf("kernelNum : %d\n", mKernelNum);

	for (vector<KernelCode>::iterator itr = mKernelCodeList.begin();
			itr != mKernelCodeList.end(); ++itr) {
		KernelCode* p = &*itr;
		p->print();
	}
}

string ExecData::getAppId() {
	return mAppId;
}
void ExecData::setAppId(string appId) {
	mAppId = appId;
}
long ExecData::getStartTime() {
	return mStartTime;
}
void ExecData::setStartTime(long startTime) {
	mStartTime = startTime;
}
void ExecData::setStartTime(string startTime) {
	stringstream ss;
	long val = -1;
	ss << startTime;
	ss >> val;
	setStartTime(val);
}
long ExecData::getExecTime() {
	return mExecTime;
}
void ExecData::setExecTime(long execTime) {
	mExecTime = execTime;
}
void ExecData::setExecTime(string execTime) {
	stringstream ss;
	long val = -1;
	ss << execTime;
	ss >> val;
	setExecTime(val);
}
string ExecData::getDeviceName(int flag) {
	if (flag == 0 || flag == 1) {
		return mDeviceName[flag];
	}
	return NULL;
}
void ExecData::setDeviceName(string name, int flag) {
	if (flag == 0 || flag == 1) {
		mDeviceName[flag] = name;
	}
}
cl_device_type ExecData::getDeviceType(int flag) {
	if (flag == 0 || flag == 1) {
		return mDeviceType[flag];
	}
	cl_device_type type;
	return type;
}
void ExecData::setDeviceType(cl_device_type deviceType, int flag) {
	if (flag == 0 || flag == 1) {
		mDeviceType[flag] = deviceType;
	}
}
int ExecData::getKernelNum() {
	return mKernelNum;
}
void ExecData::setKernelNum(int kernelNum) {
	mKernelNum = kernelNum;
}
void ExecData::setKernelNum(string kernelNum) {
	int numInt = -1;
	stringstream ss;
	ss << kernelNum;
	ss >> numInt;
	setKernelNum(numInt);
}

vector<KernelCode>* ExecData::getKernelCodeList() {
	return &mKernelCodeList;
}
void ExecData::setKernelCodeList(vector<KernelCode> kernelCodeList) {
	mKernelCodeList = kernelCodeList;
}

KernelCode* ExecData::getKernelCode(int index) {
	if((int)mKernelCodeList.size() > index){
		return &mKernelCodeList[index];
	}
	return NULL;
}

void ExecData::addKernelCode() {
	KernelCode kernelCode;
	mKernelCodeList.push_back(kernelCode);
	mKernelNum++;
}

cl_device_id ExecData::getDevIdBySetDevice(int flag) {
	return mDevTable.getDeviceIdFromName(mDeviceName[flag]);
}

cl_platform_id ExecData::getPlatIdByDevId(cl_device_id devId) {
	return mDevTable.getPlatIdFromDevId(devId);
}

DeviceTable* ExecData::getDevTable() {
	return &mDevTable;
}
void ExecData::setDevTable(DeviceTable devTable) {
	mDevTable.setNameTable(*(devTable.getNameTable()));
}
/*
 ExecData::ExecData(const ExecData& execData) {
 mStartTime = -1;
 mExecTime = -1;
 setAppId(execData.mAppId);
 setStartTime(execData.mStartTime);
 setExecTime(execData.mExecTime);
 setDeviceName(execData.mDeviceName[0], 0);
 setDeviceName(execData.mDeviceName[1], 1);
 setDeviceType(execData.mDeviceType[0], 0);
 setDeviceType(execData.mDeviceType[1], 1);

 vector<FuncData>* vecFunc = new vector<FuncData>;
 for (int i = 0; i < execData.mFuncDataList.size(); i++) {
 FuncData funcData = execData.mFuncDataList[i];
 vecFunc->push_back(funcData);
 }
 mFuncDataList = *vecFunc;
 /*
 for(int i=0;i<execData.mFuncDataList.size();i++){
 FuncData* func = new FuncData(*execData.mFuncDataList[i]);
 mFuncDataList.push_back(func);
 //		FuncData func = *FuncData(execData.mFuncDataList[i]);
 //		mFuncDataList.push_back(&func);
 }
 */
/*
 vector<KernelCode>* vecKernel = new vector<KernelCode>;
 for (int i = 0; i < execData.mKernelCodeList.size(); i++) {
 KernelCode kernel = execData.mKernelCodeList[i];
 vecKernel->push_back(kernel);
 }
 mKernelCodeList = *vecKernel;
 }
 */

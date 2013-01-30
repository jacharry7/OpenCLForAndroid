/*
 * ExecData.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef EXECDATA_H_
#define EXECDATA_H_

#include "../common/Common.h"
#include "TagData.h"
#include "FuncData.h"
#include "KernelCode.h"
#include "DeviceTable.h"

class ExecData : public TagData{
private:
	string mAppId;
	long mStartTime;
	long mExecTime;
	// 0:selected 1:current
	string mDeviceName[2];
	cl_device_type mDeviceType[2];
	int mKernelNum;
	vector<KernelCode> mKernelCodeList;

	DeviceTable mDevTable;

public:
	ExecData();
	virtual ~ExecData();
	string getAppId();
	void setAppId(string appId);
	long getStartTime();
	void setStartTime(long startTime);
	void setStartTime(string startTime);
	long getExecTime();
	void setExecTime(long execTime);
	void setExecTime(string execTime);
	string getDeviceName(int flag);
	void setDeviceName(string name, int flag);
	cl_device_type getDeviceType(int flag);
	void setDeviceType(cl_device_type deviceType, int flag);

	int getKernelNum();
	void setKernelNum(int kernelNum);
	void setKernelNum(string kernelNum);
	vector<KernelCode>* getKernelCodeList();
	void setKernelCodeList(vector<KernelCode> kernelCodeList);
	KernelCode* getKernelCode(int index);
	void addKernelCode();

	cl_device_id getDevIdBySetDevice(int flag);
	cl_platform_id getPlatIdByDevId(cl_device_id devId);
	DeviceTable* getDevTable();
	void setDevTable(DeviceTable devTable);
	string createSendData();
	void print();

//	ExecData(const ExecData& execData);

};

#endif /* EXECDATA_H_ */

/*
 * Converter.h
 *
 *  Created on: 2012/11/22
 *      Author: sakakibara
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "Common.h"
#include "../data/SocketData.h"
#include "../tinyxml/tinyxml.h"

class Converter {
private:
	static const string socketTagList[];
	static const int socketTagListSize;
	static const string execTagList[];
	static const int execTagListSize;
	static const string funcTagList[];
	static const int funcTagListSize;
	static const string resSizeTagList[];
	static const int resSizeTagListSize;
	static const string workItemSizeTagList[];
	static const int workItemSizeTagListSize;
	static const string kernelTagList[];
	static const int kernelTagListSize;
	int mFuncNum;
	int mFuncListIndex;
	int mKernelNum;
	int mKernelListIndex;
	int mIsResSize;
	int mIsGws;
public:
	Converter();
	virtual ~Converter();

	SocketData* toSocketData(string data);
	bool setSocketDataFromElement(SocketData* socketData,
			TiXmlElement* ele, const string key);
	void setSocketDataFromClass(SocketData* socketData,
			TiXmlElement* ele, const string key, const string* list,
			const int listSize);
	void setSocketDataFromArrayClass(SocketData* socketData,
			TiXmlElement* ele, const string key, const string* list, const int listSize);
	void setSocketData(SocketData* socketData, const string key,
			const string value);
	static string toSendData(SocketData* data);
	static string createTagData(string tagName, string data);
	static int toSignal(string data);
	static string getTagData(string data, string tagName);
	static cl_device_type getClDeviceType(string deviceTypeStr);

	/*
	 static int toSocketName(string data, string* socketName, int index);
	 static bool checkData(string data);
	 */
};

#endif /* CONVERTER_H_ */

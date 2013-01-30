/*
 * Converter.cpp
 *
 *  Created on: 2012/11/22
 *      Author: sakakibara
 */

#include "Converter.h"

const string Converter::socketTagList[] = { TAG_SIGNAL, TAG_SOCKETNAME,
		TAG_DATA, TAG_EXECDATA };
const int Converter::socketTagListSize = 4;
const string Converter::execTagList[] = { TAG_APPID, TAG_STARTTIME,
		TAG_EXECTIME, TAG_DEVICENAME_SELECTED, TAG_DEVICENAME,
		TAG_DEVICETYPE_SELECTED, TAG_DEVICETYPE, TAG_KERNELNUM, TAG_KERNELLIST };
const int Converter::execTagListSize = 9;
const string Converter::kernelTagList[] = { TAG_KERNELNAME, TAG_KERNELHASH ,TAG_FUNCNUM, TAG_FUNCLIST, };
const int Converter::kernelTagListSize = 4;
const string Converter::funcTagList[] = { TAG_FUNCNAME,
		TAG_RESOURCESIZE_SELECTED, TAG_RESOURCESIZE };
const int Converter::funcTagListSize = 3;
const string Converter::resSizeTagList[] = { TAG_GLOBALWORKSIZE,
		TAG_LOCALWORKSIZE };
const int Converter::resSizeTagListSize = 2;
const string Converter::workItemSizeTagList[] = { TAG_WORKSIZE };
const int Converter::workItemSizeTagListSize = 1;


Converter::Converter() {
	mFuncNum = 0;
	mFuncListIndex = -1;
	mKernelNum = 0;
	mKernelListIndex = -1;
	mIsResSize = -1;
	mIsGws = -1;
}

Converter::~Converter() {
}

SocketData* Converter::toSocketData(string data) {

	SocketData* socketData = new SocketData();
	TiXmlDocument xml;
	map<string, string> xmlmap;

	if (xml.Parse(data.c_str()) != 0) {
		const string key = TAG_SOCKETDATA;
		TiXmlElement* socket = xml.FirstChildElement(key.c_str());
		if (socket != NULL) {
			setSocketDataFromClass(socketData, socket, key, socketTagList,
					socketTagListSize);
		}
	}
	return socketData;
}
bool Converter::setSocketDataFromElement(SocketData* socketData,
		TiXmlElement* ele, const string key) {
	TiXmlElement* el = ele->FirstChildElement(key.c_str());
	if (el == NULL)
		return false;

	//printf("%s\n",key.c_str());

	const char* keyc = NULL;
	const string* tagList = NULL;
	int tagListSize = 0;
	if (key == TAG_EXECDATA) {
		setSocketDataFromClass(socketData, el, key, execTagList,
				execTagListSize);
	} else if (key == TAG_FUNCLIST) {
		keyc = TAG_FUNCDATA;
		tagList = funcTagList;
		tagListSize = funcTagListSize;
		/*TODO resize */
		if(mFuncNum != 0){
			socketData->getExecData()->getKernelCode(mKernelListIndex)->getFuncDataList()->resize(mFuncNum);
			for (TiXmlElement* el2 = el->FirstChildElement(keyc); el2 != NULL;
					el2 = el2->NextSiblingElement(keyc)) {
	//			socketData->getExecData()->addFuncData();
				mFuncListIndex++;
				for (int i = 0; i < tagListSize; i++) {
					setSocketDataFromElement(socketData, el2, tagList[i]);
				}
			}
			mFuncListIndex = -1;
		}else{
			printf("Parse Error : please <funcnum> parameter!\n");
			return false;
		}
	} else if (key == TAG_RESOURCESIZE){
		mIsResSize = FLAG_DEVICE_CURRENT;
		setSocketDataFromClass(socketData, el, key, resSizeTagList,
				resSizeTagListSize);
	} else if( key == TAG_RESOURCESIZE_SELECTED) {
		mIsResSize = FLAG_DEVICE_SELECTED;
		setSocketDataFromClass(socketData, el, key, resSizeTagList,
				resSizeTagListSize);
	} else if (key == TAG_GLOBALWORKSIZE || key == TAG_LOCALWORKSIZE) {
		if(key == TAG_GLOBALWORKSIZE) mIsGws = FLAG_GLOBALWORKSIZE;
		else if (key == TAG_LOCALWORKSIZE) mIsGws = FLAG_LOCALWORKSIZE;
		keyc = TAG_WORKSIZE;
		tagList = workItemSizeTagList;
		tagListSize = workItemSizeTagListSize;
		for (TiXmlElement* el2 = el->FirstChildElement(keyc); el2 != NULL;
				el2 = el2->NextSiblingElement(keyc)) {
			//printf("%s : %s\n",keyc, el2->GetText());
			setSocketData(socketData, keyc,el2->GetText());
		}
	} else if (key == TAG_KERNELLIST) {
		keyc = TAG_KERNEL;
		tagList = kernelTagList;
		tagListSize = kernelTagListSize;
		/*TODO resize */
		if(mKernelNum != 0){
			socketData->getExecData()->getKernelCodeList()->resize(mKernelNum);
			for (TiXmlElement* el2 = el->FirstChildElement(keyc); el2 != NULL;
					el2 = el2->NextSiblingElement(keyc)) {
				//socketData->getExecData()->addKernelCode();
				mKernelListIndex++;
				for (int i = 0; i < tagListSize; i++) {
					setSocketDataFromElement(socketData, el2, tagList[i]);
				}
			}
			mKernelListIndex = -1;
		}else{
			printf("Parse Error : please <kernelnum> parameter!\n");
			return false;
		}
	} else {
		setSocketData(socketData, key, el->GetText());
	}
	return true;
}
void Converter::setSocketDataFromClass(SocketData* socketData,
		TiXmlElement* ele, const string key, const string* list,
		const int listSize) {
	for (int i = 0; i < listSize; i++) {
		setSocketDataFromElement(socketData, ele, list[i]);
	}
}

void Converter::setSocketDataFromArrayClass(SocketData* socketData,
		TiXmlElement* ele, const string key, const string* tagList,
		const int tagListSize) {

}

void Converter::setSocketData(SocketData* socketData, const string key,
		const string value) {
	if (key == TAG_SIGNAL) {
		socketData->setSignal(value);
	} else if (key == TAG_SOCKETNAME) {
		socketData->setSocketName(value);
	} else if (key == TAG_APPID) {
		socketData->getExecData()->setAppId(value);
	} else if (key == TAG_STARTTIME) {
		socketData->getExecData()->setStartTime(value);
	} else if (key == TAG_EXECTIME) {
		socketData->getExecData()->setExecTime(value);
	} else if (key == TAG_DEVICENAME) {
		socketData->getExecData()->setDeviceName(value,FLAG_DEVICE_CURRENT);
	} else if (key == TAG_DEVICENAME_SELECTED) {
		socketData->getExecData()->setDeviceName(value,FLAG_DEVICE_SELECTED);
	} else if (key == TAG_DEVICETYPE) {
		socketData->getExecData()->setDeviceType(getClDeviceType(value),FLAG_DEVICE_CURRENT);
	} else if (key == TAG_DEVICETYPE_SELECTED) {
		socketData->getExecData()->setDeviceType(getClDeviceType(value),FLAG_DEVICE_SELECTED);
	} else if (key == TAG_KERNELNUM) {
		stringstream ss;
		int numInt = -1;
		ss << value;
		ss >> numInt;
		socketData->getExecData()->setKernelNum(numInt);
		mKernelNum = numInt;
	} else if(key == TAG_KERNELNAME){
		socketData->getExecData()->getKernelCode(mKernelListIndex)->setName(value);
	} else if(key == TAG_KERNELHASH){
		socketData->getExecData()->getKernelCode(mKernelListIndex)->setHash(value);
	} else if (key == TAG_FUNCNUM){
		stringstream ss;
		int numInt = -1;
		ss << value;
		ss >> numInt;
		socketData->getExecData()->getKernelCode(mKernelListIndex)->setFuncNum(numInt);
		mFuncNum = numInt;
	} else if (key == TAG_FUNCNAME) {
		socketData->getExecData()->getKernelCode(mKernelListIndex)->getFuncData(mFuncListIndex)->setFuncName(value);
	} else if(key == TAG_WORKSIZE){
		socketData->getExecData()->getKernelCode(mKernelListIndex)->getFuncData(mFuncListIndex)->getResourceSize(mIsResSize)->getWorkSizeList(mIsGws)->addWorkItemSize(value);
	}
}

string Converter::toSendData(SocketData* data) {
	string sendData = data->createSendData();
	return sendData;
}

int Converter::toSignal(string data) {
	int sigInt = -1;
	string str = getTagData(data, TAG_SIGNAL);
	if (!str.empty()) {
		stringstream ss;
		ss << str;
		ss >> sigInt;
		return sigInt;
	}
	return sigInt;
}
string Converter::getTagData(string data, string tagName) {
	unsigned int start = 0;
	unsigned int end = 0;
	string startTag = "<" + tagName + ">";
	string endTag = "</" + tagName + ">";
	if ((start = data.find(startTag)) != string::npos) {
		start += startTag.length();
		if ((end = data.find(endTag, (unsigned int) start)) != string::npos) {
			string str(data.substr(start, end - start));
			return str;
		}
	}
	return "";
}

cl_device_type Converter::getClDeviceType(string deviceTypeStr){
	cl_device_type deviceType;
	long deviceTypeLong = 0;
	stringstream ss;
	ss << deviceTypeStr;
	ss >> deviceTypeLong;

	switch(deviceTypeLong){
	case (1 << 0):
		deviceType = CL_DEVICE_TYPE_DEFAULT;
		break;
	case (1 << 1):
		deviceType = CL_DEVICE_TYPE_CPU;
		break;
	case (1 << 2):
		deviceType = CL_DEVICE_TYPE_GPU;
		break;
	case (1 << 3):
		deviceType = CL_DEVICE_TYPE_ACCELERATOR;
		break;
	case (1 << 4):
		//deviceType =  CL_DEVICE_TYPE_CUSTOM;
		break;
	case 0xffffffff:
		deviceType = CL_DEVICE_TYPE_ALL;
		break;
	default:
		break;
	}
	return deviceType;
}

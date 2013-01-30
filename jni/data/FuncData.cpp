/*
 * FuncData.cpp
 *
 *  Created on: 2FLAG_DEVICE_SELECTEDFLAG_DEVICE_CURRENT2/FLAG_DEVICE_CURRENTFLAG_DEVICE_CURRENT/24
 *      Author: sakakibara
 */

#include "FuncData.h"

FuncData::FuncData() {
	mResourceSize = new ResourceSizeData[2]();
	mResourceSize[FLAG_DEVICE_SELECTED].setFlag(FLAG_DEVICE_SELECTED);
	mResourceSize[FLAG_DEVICE_CURRENT].setFlag(FLAG_DEVICE_CURRENT);
}

FuncData::~FuncData() {
	delete[] mResourceSize;
}

string FuncData::getFuncName() {
	return mName;
}
void FuncData::setFuncName(string name) {
	mName = name;
}
ResourceSizeData* FuncData::getResourceSize(int flag) {
	if (flag == FLAG_DEVICE_SELECTED || flag == FLAG_DEVICE_CURRENT) {
		return &mResourceSize[flag];
	}
	return NULL;
}
void FuncData::setResourceSize(ResourceSizeData sizeData, int flag) {
	if (flag == FLAG_DEVICE_SELECTED || flag == FLAG_DEVICE_CURRENT) {
		mResourceSize[flag] = sizeData;
	}
}

void FuncData::addWorkItemSize(int size, int resFlag, int wlFlag) {
	if (resFlag == FLAG_DEVICE_SELECTED || resFlag == FLAG_DEVICE_CURRENT) {
		mResourceSize[resFlag].addWorkItemSize(size, wlFlag);
	}
}

// override
string FuncData::createSendData() {
	string sendData;
	sendData += createStartTag(TAG_FUNCDATA);
	if (mName != "")
		sendData += createTag(TAG_FUNCNAME, mName);
	if (mResourceSize[FLAG_DEVICE_SELECTED].getWorkSizeList(FLAG_GLOBALWORKSIZE)->getDim()
			!= 0
			|| mResourceSize[FLAG_DEVICE_SELECTED].getWorkSizeList(
					FLAG_LOCALWORKSIZE)->getDim() != 0) {
		sendData += createStartTag(TAG_RESOURCESIZE_SELECTED);
		sendData += mResourceSize[FLAG_DEVICE_SELECTED].createSendData();
		sendData += createEndTag(TAG_RESOURCESIZE_SELECTED);
	}
	if (mResourceSize[FLAG_DEVICE_CURRENT].getWorkSizeList(FLAG_GLOBALWORKSIZE)->getDim()
			!= 0
			|| mResourceSize[FLAG_DEVICE_CURRENT].getWorkSizeList(
					FLAG_LOCALWORKSIZE)->getDim() != 0) {
		sendData += createStartTag(TAG_RESOURCESIZE);
		sendData += mResourceSize[FLAG_DEVICE_CURRENT].createSendData();
		sendData += createEndTag(TAG_RESOURCESIZE);
	}
	sendData += createEndTag(TAG_FUNCDATA);
	return sendData;
}
void FuncData::print() {
	printf("funcname : %s\n", mName.c_str());
//	if(mResourceSize[FLAG_DEVICE_SELECTED] != null){
	printf("/SelectedRes/\n");
	mResourceSize[FLAG_DEVICE_SELECTED].print();
//	}
//	if(mResourceSize[FLAG_DEVICE_CURRENT] != null){
	printf("/CurrentRes/\n");
	mResourceSize[FLAG_DEVICE_CURRENT].print();
//	}
}

FuncData::FuncData(const FuncData& funcData) {
	mResourceSize = new ResourceSizeData[2]();
	setFuncName(funcData.mName);
	mResourceSize[FLAG_DEVICE_SELECTED].setFlag(FLAG_DEVICE_SELECTED);
	mResourceSize[FLAG_DEVICE_CURRENT].setFlag(FLAG_DEVICE_CURRENT);
//	if (mResourceSize != NULL) {
//	ResourceSizeData resData = funcData.mResourceSize[FLAG_DEVICE_SELECTED];
//		setResourceSize(funcData.mResourceSize[FLAG_DEVICE_SELECTED], FLAG_DEVICE_SELECTED);
//		setResourceSize(funcData.mResourceSize[FLAG_DEVICE_CURRENT], FLAG_DEVICE_CURRENT);
//	}
//	}
}
/*
 FuncData& FuncData::Copy(const FuncData& funcData){
 if(this == &funcData) return *this;
 delete[] mResourceSize;
 mResourceSize = new ResourceSizeData[2]();
 setFuncName(funcData.mName);
 //	setResourceSize(funcData.mResourceSize[FLAG_DEVICE_SELECTED], FLAG_DEVICE_SELECTED);
 //	setResourceSize(funcData.mResourceSize[FLAG_DEVICE_CURRENT], FLAG_DEVICE_CURRENT);
 return *this;
 }
 FuncData& FuncData::operator =(const FuncData& funcData){
 return Copy(funcData);
 }
 */

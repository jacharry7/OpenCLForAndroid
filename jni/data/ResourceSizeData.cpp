/*
 * ResourceSizeData.cpp
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#include "ResourceSizeData.h"

ResourceSizeData::ResourceSizeData() {
	mWorkSizeList = new WorkItemSizeList[2];
	mWorkSizeList[0].setFlag(FLAG_GLOBALWORKSIZE);
	mWorkSizeList[1].setFlag(FLAG_LOCALWORKSIZE);
}
ResourceSizeData::ResourceSizeData(int flag) {
	mWorkSizeList = new WorkItemSizeList[2];
	mWorkSizeList[0].setFlag(FLAG_GLOBALWORKSIZE);
	mWorkSizeList[1].setFlag(FLAG_LOCALWORKSIZE);
	mFlag = flag;
}

ResourceSizeData::~ResourceSizeData() {
	delete[] mWorkSizeList;
}

WorkItemSizeList* ResourceSizeData::getWorkSizeList(int flag) {
	if (flag == FLAG_GLOBALWORKSIZE || flag == FLAG_LOCALWORKSIZE) {
		return &mWorkSizeList[flag];
	}
	WorkItemSizeList wisList;
	return NULL;
}
void ResourceSizeData::setWorkSizeList(WorkItemSizeList workSizeList,
		int flag) {
	if (flag == FLAG_GLOBALWORKSIZE || flag == FLAG_LOCALWORKSIZE) {
		mWorkSizeList[flag] = workSizeList;
	}
}

void ResourceSizeData::addWorkItemSize(int size, int flag) {
	if (flag == FLAG_GLOBALWORKSIZE || flag == FLAG_LOCALWORKSIZE) {
		mWorkSizeList[flag].addWorkItemSize(size);
	}
}

void ResourceSizeData::setFlag(int flag) {
	mFlag = flag;
}

// override
string ResourceSizeData::createSendData() {
	string sendData;
	if (mWorkSizeList[FLAG_GLOBALWORKSIZE].getDim() != 0) {
		sendData += createStartTag(TAG_GLOBALWORKSIZE);
		sendData += mWorkSizeList[FLAG_GLOBALWORKSIZE].createSendData();
		sendData += createEndTag(TAG_GLOBALWORKSIZE);
	}
	if (mWorkSizeList[FLAG_LOCALWORKSIZE].getDim() != 0) {
		sendData += createStartTag(TAG_LOCALWORKSIZE);
		sendData += mWorkSizeList[FLAG_LOCALWORKSIZE].createSendData();
		sendData += createEndTag(TAG_LOCALWORKSIZE);
	}
	return sendData;
}
void ResourceSizeData::print() {
	if (mWorkSizeList[FLAG_GLOBALWORKSIZE].getDim() != 0) {
		printf("/GWS\n");
		mWorkSizeList[FLAG_GLOBALWORKSIZE].print();
	}
	if (mWorkSizeList[FLAG_LOCALWORKSIZE].getDim() != 0) {
		printf("/LWS\n");
		mWorkSizeList[FLAG_LOCALWORKSIZE].print();
	}
}

ResourceSizeData& ResourceSizeData::Copy(const ResourceSizeData& resSizeData) {
	if (this == &resSizeData)
		return *this;
	mWorkSizeList = new WorkItemSizeList[2];
	mWorkSizeList[0].setFlag(FLAG_GLOBALWORKSIZE);
	mWorkSizeList[1].setFlag(FLAG_LOCALWORKSIZE);
	setWorkSizeList(resSizeData.mWorkSizeList[0], FLAG_GLOBALWORKSIZE);
	setWorkSizeList(resSizeData.mWorkSizeList[1], FLAG_LOCALWORKSIZE);
	return *this;
}
ResourceSizeData& ResourceSizeData::operator =(
		const ResourceSizeData& resSizeData) {
	return Copy(resSizeData);
}

/*
 ResourceSizeData::ResourceSizeData(const ResourceSizeData& resourceSizeData){
 //	setFlag(resourceSizeData.mFlag);
 //	WorkItemSizeList wis = resourceSizeData.mWorkSizeList[0];
 //	setWorkSizeList(wis,0);
 //	setWorkSizeList(resourceSizeData.mWorkSizeList[0],0);
 //	setWorkSizeList(resourceSizeData.mWorkSizeList[1],1);
 }

 */

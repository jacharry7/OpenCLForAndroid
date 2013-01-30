/*
 * WrokItemSizeList.cpp
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#include "WorkItemSizeList.h"

WorkItemSizeList::WorkItemSizeList() {
	mDim = 0;
	mSizeList = new size_t[3];
}

WorkItemSizeList::~WorkItemSizeList() {
	delete[] mSizeList;
}
void WorkItemSizeList::addWorkItemSize(int wis){
	mSizeList[mDim] = wis;
	mDim++;
}
void WorkItemSizeList::addWorkItemSize(string wis){
	stringstream ss;
	int val = -1;
	ss << wis;
	ss >> val;
	addWorkItemSize(val);
}
int WorkItemSizeList::getSize(int dim){
	if(dim >= 0 && dim <= 3){
		return mSizeList[dim];
	}
	return -1;
}
size_t* WorkItemSizeList::getSizeList(){
	return mSizeList;
}
void WorkItemSizeList::setSizeList(size_t* sizeList){
	mSizeList = sizeList;
}
int WorkItemSizeList::getDim(){
	return mDim;
}
void WorkItemSizeList::setDim(int dim){
	mDim = dim;
}
void WorkItemSizeList::setFlag(int flag){
	mFlag = flag;
}
//override
string WorkItemSizeList::createSendData(){
	string sendData;
	stringstream ss;
	for(int i=0;i<mDim;i++){
		ss << mSizeList[i];
		sendData += createTag(TAG_WORKSIZE,ss.str());
		ss.clear();
		ss.str("");
	}
	return sendData;
}
void WorkItemSizeList::print(){
	printf("dim : %d\n", mDim);
/*	for(unsigned int i =0;i<mSizeList.size();i++){
		printf("%d/",mSizeList[i]);
	}
*/
	for(int i=0;i<mDim;i++){
		printf("%d/",mSizeList[i]);
	}
	printf("\n");
}

WorkItemSizeList& WorkItemSizeList::Copy(const WorkItemSizeList& wisList){
	if(this == &wisList) return *this;
	delete[] mSizeList;
	mDim = 0;
	mSizeList = new size_t[3];
	for(int i=0;i<wisList.mDim;i++){
		mSizeList[i] = wisList.mSizeList[i];
	}
	return *this;
}
WorkItemSizeList& WorkItemSizeList::operator =(const WorkItemSizeList& wisList){
	return Copy(wisList);
}

/*
WorkItemSizeList::WorkItemSizeList(const WorkItemSizeList& workItemSizeList){
	setDim(workItemSizeList.mDim);
	setFlag(workItemSizeList.mFlag);
	if(workItemSizeList.mSizeList != NULL){
		for(int i=0;i<mDim;i++){
			mSizeList[i] = workItemSizeList.mSizeList[i];
		}
	}
	/*
	vector<int>* vec = new vector<int>;
	for (int i = 0; i < workItemSizeList.mSizeList.size(); i++) {
		vec->push_back(workItemSizeList.mSizeList[i]);
	}
	mSizeList = *vec;
}
*/


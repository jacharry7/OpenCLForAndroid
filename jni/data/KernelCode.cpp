/*
 * KernelCode.cpp
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#include "KernelCode.h"

KernelCode::KernelCode() {
	mFuncNum = 0;
}

KernelCode::~KernelCode() {
}

//override
string KernelCode::createSendData() {
	string sendData;
	sendData += createStartTag(TAG_KERNEL);
	if (mName != "")
		sendData += createTag(TAG_KERNELNAME, mName);
	if (mHash != "")
		sendData += createTag(TAG_KERNELHASH, mHash);
	if (mFuncNum != 0) {
		stringstream ss;
		ss << mFuncNum;
		sendData += createTag(TAG_FUNCNUM, ss.str());
	}
	//funclist
	sendData += createStartTag(TAG_FUNCLIST);
	for (int i = 0; i < mFuncDataList.size(); i++) {
		sendData += mFuncDataList[i].createSendData();
	}
	sendData += createEndTag(TAG_FUNCLIST);
	sendData += createEndTag(TAG_KERNEL);
	return sendData;
}
void KernelCode::print() {
	if (mName != "")
		printf("kernelname : %s\n", mName.c_str());
	if (mHash != "")
		printf("kernelhash : %s\n", mHash.c_str());
	if (mFuncNum != 0)
		printf("funcNum : %d\n", mFuncNum);

	for (vector<FuncData>::iterator itr = mFuncDataList.begin();
			itr != mFuncDataList.end(); ++itr) {
		FuncData* p = &*itr;
		p->print();
	}
}

bool KernelCode::isFuncName(string name){
	for (vector<FuncData>::iterator itr = mFuncDataList.begin();
			itr != mFuncDataList.end(); ++itr) {
		FuncData* p = &*itr;
		if(name == p->getFuncName()){
			return true;
		}
	}
	return false;
}
string KernelCode::getName() {
	return mName;
}
void KernelCode::setName(string name) {
	mName = name;
}
string KernelCode::getHash() {
	return mHash;
}
void KernelCode::setHash(string hash) {
	mHash = hash;
}

int KernelCode::getFuncNum() {
	return mFuncNum;
}
void KernelCode::setFuncNum(int num) {
	mFuncNum = num;
}
void KernelCode::setFuncNum(string num) {
	stringstream ss;
	int numInt = -1;
	ss << num;
	ss >> numInt;
	mFuncNum = numInt;
}
vector<FuncData>* KernelCode::getFuncDataList() {
	return &mFuncDataList;
}
void KernelCode::setFuncDataList(vector<FuncData> funcDataList) {
	mFuncDataList = funcDataList;
}
FuncData* KernelCode::getFuncData(const int index) {
	return &mFuncDataList[index];
}
FuncData* KernelCode::getFuncData(const string name){
	for (vector<FuncData>::iterator itr = mFuncDataList.begin();
			itr != mFuncDataList.end(); ++itr) {
		FuncData* p = &*itr;
		if(p->getFuncName() == name)
			return p;
	}
	return NULL;
}
void KernelCode::setFuncData(FuncData funcData, int index) {
	mFuncDataList[index] = funcData;
}
void KernelCode::addFuncData() {
	FuncData* funcData = new FuncData();
	mFuncDataList.push_back(*funcData);
	mFuncNum++;
}

KernelCode::KernelCode(const KernelCode& kernelCode) {
	mFuncNum = kernelCode.mFuncNum;
	setName(kernelCode.mName);
	setHash(kernelCode.mHash);
}

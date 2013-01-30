/*
 * SocketData.cpp
 *
 *  Created on: 2012/11/22
 *      Author: sakakibara
 */

#include "SocketData.h"

SocketData::SocketData() {

}

SocketData::~SocketData(){

}

string SocketData::createSendData(){
	string sendData;
	sendData += createStartTag(TAG_SOCKETDATA);
	sendData += mSignal.createSendData();
	sendData += createTag(TAG_SOCKETNAME, mName);
	if(mData != "") sendData += createTag(TAG_DATA, mData);
	sendData += mExecData.createSendData();
	sendData += createEndTag(TAG_SOCKETDATA);
	return sendData;
}

void SocketData::print(){
	printf("//---SocketData------------\n");
	mSignal.print();
	if(mName != "") printf("socketname : %s\n",mName.c_str());
	if(mData != "") printf("data : %s\n",mData.c_str());
	mExecData.print();
	printf("//-------------------------\n");
}

Signal* SocketData::getSignal(){
	return &mSignal;
}

string SocketData::getSocketName(){
	return mName;
}

string SocketData::getData(){
	return mData;
}
void SocketData::setSignal(Signal signal){
	mSignal = signal;
}
void SocketData::setSignal(int signal){
	mSignal.setIntVal(signal);
}
void SocketData::setSocketName(string name){
	mName = name;
}
void SocketData::setData(string data){
	mData = data;
}
ExecData* SocketData::getExecData(){
	return &mExecData;
}
void SocketData::setExecData(ExecData* execData){
	mExecData = *execData;
}


/*
SocketData::SocketData(const SocketData& socketData){
	setSignal(socketData.mSignal);
	setSocketName(socketData.mName);
	if(socketData.mData != ""){
		setData(socketData.mData);
	}
	mExecData = socketData.mExecData;
}
*/

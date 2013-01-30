/*
 * EventTask.cpp
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#include "EventTask.h"

EventTask::EventTask(Library* lib) {
	mLib = lib;
}

EventTask::~EventTask() {
}

SocketData* EventTask::convertToSoketData(string data){
	Converter converter;
	SocketData* socketData = converter.toSocketData(data);
	return socketData;
}

string EventTask::convertToSendData(SocketData* socketData){
	string sendData = Converter::toSendData(socketData);
	return sendData;
}


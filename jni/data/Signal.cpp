/*
 * Signal.cpp
 *
 *  Created on: 2012/11/21
 *      Author: sakakibara
 */

#include "Signal.h"
#include "../common/Converter.h"

Signal::Signal() {
	mSignal = -1;
}

Signal::Signal(int signal){
	mSignal = signal;
}

Signal::Signal(const string signal){
	stringstream ss;
	int val = -1;
	ss << signal;
	ss >> val;
	mSignal = val;
}

Signal::Signal(const string data, bool flag) {
	if(flag){
		mSignal = Converter::toSignal(data);
	}else{
		stringstream ss;
		int intVal = -1;
		ss << data;
		ss >> intVal;
		mSignal = intVal;
	}
}

Signal::~Signal() {
}

bool Signal::checkSignal() {
	return true;
}

bool Signal::checkConnectSignal() {
	return true;
}

int Signal::getIntVal() {
	return mSignal;
}

void Signal::setIntVal(int signal) {
	mSignal = signal;
}

string Signal::toString() {
	stringstream ss;
	ss << mSignal;
	string str(ss.str());
	return str;
}

Signal& Signal::operator=(Signal &signal){
	mSignal = signal.getIntVal();
	return *this;
}

string Signal::createSendData(){
	return createTag(TAG_SIGNAL, toString());
}

void Signal::print(){
	printf("signal : %s\n",toString().c_str());
}

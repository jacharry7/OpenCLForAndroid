/*
 * Signal.h
 *
 *  Created on: 2012/11/21
 *      Author: sakakibara
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include "../common/Common.h"
#include "TagData.h"

class Signal : public TagData{
private:
	static const string START_TAG;
	static const string END_TAG;

	int mSignal;
public:
	Signal();
	Signal(int signal);
	Signal(const string signal);
	Signal(const string data, bool flag);
	virtual ~Signal();
	bool checkSignal();
	bool checkConnectSignal();
	int getIntVal();
	void setIntVal(int signal);
	string toString();

	Signal& operator=(Signal &signal);

	//
	string createSendData();
	void print();
};

#endif /* SIGNAL_H_ */

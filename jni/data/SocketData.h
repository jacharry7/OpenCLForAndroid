/*
 * SocketData.h
 *
 *  Created on: 2012/11/22
 *      Author: sakakibara
 */

#ifndef SOCKETDATA_H_
#define SOCKETDATA_H_

#include "../common/Common.h"
#include "Signal.h"
#include "ExecData.h"
#include "TagData.h"

class SocketData : public TagData{
private:
	Signal mSignal;
	string mName;
	string mData;
	ExecData mExecData;

public:
	SocketData();
	virtual ~SocketData();
	Signal* getSignal();
	void	setSignal(Signal signal);
	void setSignal(int signal);
	string getSocketName();
	void	setSocketName(string name);
	string	getData();
	void	setData(string data);
	ExecData* getExecData();
	void setExecData(ExecData* execData);

	//override
	string createSendData();
	void print();

//	SocketData(const SocketData& socketData);
};

#endif /* SOCKETDATA_H_ */

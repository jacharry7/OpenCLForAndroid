/*
 * KernelCode.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef KERNELCODE_H_
#define KERNELCODE_H_

#include "../common/Common.h"
#include "TagData.h"
#include "FuncData.h"

class KernelCode : public TagData{
private:
	string mName;
	string mHash;
	int mFuncNum;
	vector<FuncData> mFuncDataList;
public:
	KernelCode();
	KernelCode(string hash);
	virtual ~KernelCode();
	bool isFuncName(string name);
	string getName();
	void setName(string name);
	string getHash();
	void setHash(string hash);
	int getFuncNum();
	void setFuncNum(int num);
	void setFuncNum(string num);
	vector<FuncData>* getFuncDataList();
	void setFuncDataList(vector<FuncData> funcDataList);
	FuncData* getFuncData(int index);
	FuncData* getFuncData(const string name);
	void setFuncData(FuncData funcData,int index);
	void addFuncData();

	//override
	string createSendData();
	void print();

	KernelCode(const KernelCode& kernelCode);
};

#endif /* KERNELCODE_H_ */

/*
 * FuncData.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef FUNCDATA_H_
#define FUNCDATA_H_

#include "../common/Common.h"
#include "TagData.h"
#include "ResourceSizeData.h"

class FuncData : public TagData {
private:
	string mName;
	ResourceSizeData* mResourceSize;
public:
	FuncData();
	virtual ~FuncData();
	string getFuncName();
	void setFuncName(string name);
	ResourceSizeData* getResourceSize(int flag);
	void setResourceSize(ResourceSizeData sizeData, int flag);
	void addWorkItemSize(int size, int resFlag, int wlFlag);

	// override
	string createSendData();
	void print();

	FuncData(const FuncData& funcData);
//	FuncData& Copy(const FuncData& funcData);
//	FuncData& operator =(const FuncData& funcData);
};

#endif /* FUNCDATA_H_ */

/*
 * WrokItemSizeList.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef WORKITEMSIZELIST_H_
#define WORKITEMSIZELIST_H_

#include "../common/Common.h"
#include "TagData.h"

class WorkItemSizeList : public TagData{
private:
	size_t* mSizeList;
	int mDim;
	int mFlag;
public:
	WorkItemSizeList();
	virtual ~WorkItemSizeList();
	void addWorkItemSize(int wis);
	void addWorkItemSize(string wis);
	int getSize(int dim);
	size_t* getSizeList();
	void setSizeList(size_t* sizeList);
	int getDim();
	void setDim(int dim);
	void setFlag(int flag);

	//override
	string createSendData();
	void print();

	WorkItemSizeList& Copy(const WorkItemSizeList& wisList);
	WorkItemSizeList& operator =(const WorkItemSizeList& wisList);
//	WorkItemSizeList(const WorkItemSizeList& workItemSizeList);
};

#endif /* WROKITEMSIZELIST_H_ */

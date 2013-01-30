/*
 * ResourceSizeData.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef RESOURCESIZEDATA_H_
#define RESOURCESIZEDATA_H_

#include "../common/Common.h"
#include "TagData.h"
#include "WorkItemSizeList.h"

class ResourceSizeData : public TagData{
private:
	WorkItemSizeList* mWorkSizeList;
	int mFlag;
public:
	ResourceSizeData();
	ResourceSizeData(int flag);
	virtual ~ResourceSizeData();
	WorkItemSizeList* getWorkSizeList(int flag);
	void setWorkSizeList(WorkItemSizeList workSizeList,int flag);
	void addWorkItemSize(int size, int flag);
	void setFlag(int flag);
	// override
	string createSendData();
	void print();

	ResourceSizeData& Copy(const ResourceSizeData& resSizeData);
	ResourceSizeData& operator =(const ResourceSizeData& resSizeData);
//	ResourceSizeData(const ResourceSizeData& resourceSizeData);
};

#endif /* RESOURCESIZEDATA_H_ */

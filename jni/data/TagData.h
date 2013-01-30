/*
 * TagData.h
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#ifndef TAGDATA_H_
#define TAGDATA_H_

#include "../common/Common.h"

class TagData {
public:
	TagData();
	virtual ~TagData();

	string createTag(const string tagName, const string data);
	string createStartTag(const string tagName);
	string createEndTag(const string tagName);

	virtual string createSendData(){return NULL;};
	virtual void print(){};
};

#endif /* TAGDATA_H_ */

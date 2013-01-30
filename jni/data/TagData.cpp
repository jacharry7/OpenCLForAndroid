/*
 * TagData.cpp
 *
 *  Created on: 2012/11/24
 *      Author: sakakibara
 */

#include "TagData.h"

TagData::TagData() {

}

TagData::~TagData() {
}

string TagData::createTag(const string tagName, const string data){
	string tag = "<" + tagName + ">";
	tag += data;
	tag += "</" + tagName + ">";
	return tag;
}
string TagData::createStartTag(const string tagName){
	return "<" + tagName + ">";
}
string TagData::createEndTag(const string tagName){
	return "</" + tagName + ">";
}


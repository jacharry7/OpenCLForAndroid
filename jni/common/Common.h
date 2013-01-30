/*
 * common.h
 *
 *  Created on: 2012/11/21
 *      Author: sakakibara
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "CL/cl.h"

#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <dlfcn.h>

using namespace std;

//#define DEBUG

/* PROGRAM's LIMIT */
#define KERNEL_INDEX 0

/* SOCKET */
// socket path
#define SOCKET_DIR_PATH "ailab."//"/tmp/"
#define APP_SOCKET_BASE "_app"//"_socket"
#define CONNECT_SOCKET "connect"
#define DISCONNECT_MESSAGE "quit"

/* SIGNALs */
#define SIGNAL_MAX_SIZE 				6
// kind of SIGNALs
#define SIGNAL_CONNECT_APP 			10
#define SIGNAL_CONNECT_DATA_LOAD	11
#define SIGNAL_INSTRUCT_PROCESSOR	20
#define SIGNAL_INSTRUCT_RESOURCES	30
#define SIGNAL_SAVE_KERNEL_HASH		40
#define SIGNAL_SAVE_TIME_EXECUTE	50

/* TAGs */
// SocketData TAGs
#define TAG_SOCKETDATA "socket"
#define TAG_SIGNAL "signal"
#define TAG_SOCKETNAME "sockname"
#define TAG_DATA "data"
#define TAG_EXECDATA "exec"
// ExecData TAGs
#define TAG_APPID "appid"
#define TAG_STARTTIME "starttime"
#define TAG_EXECTIME "exectime"
#define TAG_DEVICENAME_SELECTED "devnameed"
#define TAG_DEVICENAME "devname"
#define TAG_DEVICETYPE_SELECTED "devtypeed"
#define TAG_DEVICETYPE "devtype"
#define TAG_KERNELNUM "kernelnum"
#define TAG_KERNELLIST "kernellist"
// KernelData TAGs
#define TAG_KERNEL "kernel"
#define TAG_KERNELNAME "kernelname"
#define TAG_KERNELHASH "hash"
#define TAG_FUNCNUM "funcnum"
#define TAG_FUNCLIST "funclist"
// FuncData TAGs
#define TAG_FUNCDATA "func"
#define TAG_FUNCNAME "funcname"
#define TAG_RESOURCESIZE_SELECTED "ressized"
#define TAG_RESOURCESIZE "ressize"
#define TAG_GLOBALWORKSIZE "gws"
#define TAG_LOCALWORKSIZE "lws"
#define TAG_WORKSIZE "size"

/* FLAGs */
#define FLAG_DEVICE_SELECTED 0
#define FLAG_DEVICE_CURRENT 1
#define FLAG_GLOBALWORKSIZE 0
#define FLAG_LOCALWORKSIZE 1

/* DATA */
#define DATA_SEPARATOR ","
#define DATA_ARRAY_SEPARATOR "|"
#define DATA_DEVICE_NAMES "devnames"


#endif /* COMMON_H_ */

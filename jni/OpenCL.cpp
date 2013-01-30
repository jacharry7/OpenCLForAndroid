#include "common/Common.h"
#include "common/Library.h"
#include "service/UnixDomainSocketManager.h"
#include "task/ProcessorInfoManager.h"
#include "task/ProcessorAllocater.h"
#include "task/ResourceAllocater.h"
#include "data/ExecData.h"
#include "data/KernelCode.h"
#include "md5/md5.h"

#include <sys/time.h>

namespace wrappedopencl {

#define DEBUG
#define DEBUG_CHANGE_DEVICE
#define DEBUG_CHANGE_WORKSIZE

#define DEBUG_TAG "wrappedopencl"

#ifdef __cplusplus
extern "C" {
#endif

//void init(void) __attribute__((constructor));
//void fini(void) __attribute__((destructor));

static string APP_SOCKET;
static Library* library;
static SocketData* socketData;
static ExecData* execData;
static UnixDomainSocketManager* connectSocketManager;
static UnixDomainSocketManager* appSocketManager;

static bool isConnect = true;
static bool isChangeDevice = false;
static struct timeval startTime;
static bool isStart = false;
static string funcname_current = "";
static DeviceTable* devTable = NULL;

/**
 * original functions
 */
/**
 * constructor,destructor
 */
void initData(){
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "initData()");
#endif
	string appId = "test";
	APP_SOCKET = appId + APP_SOCKET_BASE;

	if(socketData != NULL) delete socketData;
	socketData = new SocketData();
	socketData->getExecData()->setAppId(appId);
	execData = socketData->getExecData();
}

void init(void) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"[constructor]function : init()\n");
#endif
	library = new Library();
	if (library->loadFunctions() != CL_SUCCESS) {
		exit(1);
	}
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"OK loadFunctions()\n");
#endif
	initData();

	connectSocketManager = new UnixDomainSocketManager(CONNECT_SOCKET);
	if (connectSocketManager->connectSocket() == -1) {
		isConnect = false;
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"Failed to Connect Server!\n");
#endif
	} else {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"Connect ConnectServer!\n");
#endif
		socketData->setSignal(SIGNAL_CONNECT_APP);
		socketData->setSocketName(CONNECT_SOCKET);

		ProcessorInfoManager task(library);
		task.doTask(socketData, connectSocketManager);
		/*devTableのdeepcopy*/
		devTable = new DeviceTable();
		devTable->copy(socketData->getExecData()->getDevTable());
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"init devId:%x\n",(unsigned int)devTable->getDeviceIdFromName("Intel(R) Core(TM) i5-3470 CPU @ 3.20GHz"));

		appSocketManager = new UnixDomainSocketManager(APP_SOCKET);
		if (appSocketManager->connectSocket() == -1) {
			isConnect = false;
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"Failed to AppServer!\n");
#endif
		}else{
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"Connect AppServer!\n");
#endif
		}

	}

}

void fini(void) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"[destructor]function : fini()\n");
#endif
	/* TODO
	 * destructorで呼ばないと
	 * loopで困るのでとりあえずcomment out
	 */
	/*
	if (appSocketManager != NULL) {
		appSocketManager->start(DISCONNECT_MESSAGE);
		appSocketManager->closeSocket();
		delete appSocketManager;
	}
	if (connectSocketManager != NULL) {
//#ifdef DEBUG
		/*TODO TEST サービスもそのまま切断してしまう*/
//		connectSocketManager->start(DISCONNECT_MESSAGE);
//#endif
//		connectSocketManager->closeSocket();
//		delete connectSocketManager;
//	}
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"DisConnect Server!\n");

	/* libraryは何故かおちる
	 * data系は繰り返すために必要
	 */
	/*
	if (library != NULL)
		delete library;
	if (socketData != NULL)
		delete socketData;
	if(devTable != NULL)
		delete devTable;
	*/
}

char* getHash(char* src) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "getHash()");
#endif
	md5_state_t state;
	md5_byte_t digest[16];
	char* hex_output = new char[16 * 2 + 1];
	int di;
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *) src, strlen(src));
	md5_finish(&state, digest);
	for (di = 0; di < 16; ++di) {
		sprintf(hex_output + di * 2, "%02x", digest[di]);
	}
#ifdef DEBUG
//	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"hash:%s\n", hex_output);
#endif
	return hex_output;
}
/*
void createWorkItemSizeData() {
	WorkItemSizeList* wsList = NULL;
	KernelCode* kernel = socketData->getExecData()->getKernelCode(KERNEL_INDEX);
	if (kernel != NULL) {
		int size = kernel->getFuncNum();
		lws_current = new size_t*[size];
		int dim = 0;
		for (int i = 0; i < size; i++) {
			// loop flg = FLAG_GLOBAL or LOCAL_WORKSIZE
			for (int flg = 0; flg < 2; flg++) {
				wsList = kernel->getFuncData(i)->getResourceSize(
						FLAG_DEVICE_CURRENT)->getWorkSizeList(flg);
				dim = wsList->getDim();
				lws_current[i] = new size_t[dim];
				for (int j = 0; j < wsList->getDim(); j++) {
					if (flg == 1) {
						lws_current[i][j] = wsList->getSize(j);
					}
				}
			}
		}
	}
}
*/
/**
 * プラットフォームAPI
 */
/*
 cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id* platforms,
 cl_uint* num_platforms) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clGetPlatformIDs()");
 #endif
 cl_int ret = library->clGetPlatformIDs(num_entries, platforms,
 num_platforms);
 return ret;
 }
 */

cl_int clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type,
		cl_uint num_entries, cl_device_id * devices, cl_uint * num_devices) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clGetDeviceIDs()");
#endif
	cl_int ret;
	/*
	 if (isChangeDevice) {
	 cl_device_id devId = socketData->getExecData()->getDevIdBySetDevice(
	 FLAG_DEVICE_CURRENT);
	 cl_device_type type = socketData->getExecData()->getDeviceType(
	 FLAG_DEVICE_CURRENT);
	 cl_platform_id platId = socketData->getExecData()->getPlatIdByDevId(
	 devId);
	 cl_device_id id = socketData->getExecData()->getDevIdBySetDevice(
	 FLAG_DEVICE_CURRENT);
	 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"(id)=(%x)\n",(unsigned int)id);
	 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"(plat,type,dev)=(%x,%x,%x)\n",platId, type, (unsigned int)id);
	 ret = library->clGetDeviceIDs(platId, type, num_entries,
	 &id, num_devices);
	 } else {
	 */
	ret = library->clGetDeviceIDs(platform, device_type, num_entries, devices,
			num_devices);
	//}
	return ret;
}
/*
 cl_int clGetDeviceInfo(cl_device_id device, cl_device_info param_name,
 size_t param_value_size, void* param_value,
 size_t* param_value_size_ret) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clGetDeviceInfo()");
 #endif
 cl_int ret = library->clGetDeviceInfo(device, param_name, param_value_size,
 param_value, param_value_size_ret);
 return ret;
 }
 */
cl_context clCreateContext(const cl_context_properties *properties,
		cl_uint num_devices, const cl_device_id *devices,
		void (CL_CALLBACK *pfn_notify)(const char *errinfo,
				const void *private_info, size_t cb, void *user_data),
		void *user_data, cl_int *errcode_ret) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clCreateContext()");
#endif
	initData();
#ifdef DEBUG_CHANGE_DEVICE
	if (isConnect && !isChangeDevice) {
		socketData->setSignal(SIGNAL_INSTRUCT_PROCESSOR);
		socketData->setSocketName(APP_SOCKET);
		string devName = execData->getDevTable()->getDeviceNameFromDevId(*devices);
		execData->setDeviceName(devName, FLAG_DEVICE_SELECTED);
		ProcessorAllocater task(library);
		task.doTask(socketData, appSocketManager);
		isChangeDevice = true;
	}
//	cl_device_id devId = execData->getDevIdBySetDevice(FLAG_DEVICE_CURRENT);
	string devName = socketData->getExecData()->getDeviceName(
			FLAG_DEVICE_CURRENT);
	cl_device_id devId = devTable->getDeviceIdFromName(devName);
	cl_context ret;
	if (devId != NULL) {
		ret = library->clCreateContext(properties, 1, &devId, pfn_notify,
				user_data, errcode_ret);
	} else {
		ret = library->clCreateContext(properties, num_devices, devices,
				pfn_notify, user_data, errcode_ret);
	}
	return ret;
#else
	cl_context ret = library->clCreateContext(properties, num_devices, devices,
			pfn_notify, user_data, errcode_ret);
	return ret;
#endif
}

cl_context clCreateContextFromType(const cl_context_properties *properties,
		cl_device_type device_type,
		void (CL_CALLBACK *pfn_notify)(const char *errinfo,
				const void *private_info, size_t cb, void *user_data),
		void *user_data, cl_int *errcode_ret) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clCreateContextFromType()");
#endif
	init();
	initData();
#ifdef DEBUG_CHANGE_DEVICE
	if (isConnect && !isChangeDevice) {
		socketData->setSignal(SIGNAL_INSTRUCT_PROCESSOR);
		socketData->setSocketName(APP_SOCKET);
		execData->setDeviceType(device_type, FLAG_DEVICE_SELECTED);
		ProcessorAllocater task(library);
		task.doTask(socketData, appSocketManager);
		isChangeDevice = true;
	}

	cl_context ret;
	cl_device_type type = execData->getDeviceType(FLAG_DEVICE_CURRENT);
	if (type != NULL) {
		device_type = type;
#ifdef DEBUG
		if (device_type == CL_DEVICE_TYPE_GPU)
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"CHANGE! device_type : CL_DEVICE_TYPE_GPU\n");
		else if (device_type == CL_DEVICE_TYPE_CPU)
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"CHANGE! device_type : CL_DEVICE_TYPE_CPU\n");
#endif
		cl_context_properties cps[3];
		string devName = socketData->getExecData()->getDeviceName(
				FLAG_DEVICE_CURRENT);
		cl_device_id devId = devTable->getDeviceIdFromName(devName);
#ifdef DEBUG
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"DevName:%s\n",devName.c_str());
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"devId:%x\n",(unsigned int)devId);
#endif
		cl_platform_id platId = devTable->getPlatIdFromDevId(devId);
		cps[0] = (cl_context_properties) CL_CONTEXT_PLATFORM;
		cps[1] = (cl_context_properties) platId;
		cps[2] = (cl_context_properties) 0;
#ifdef DEBUG
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"CHANGE! platform_id : %x\n", (unsigned int) cps[1]);
#endif
		ret = library->clCreateContextFromType(cps, device_type, pfn_notify,
				user_data, errcode_ret);
	} else {
		ret = library->clCreateContextFromType(properties, device_type,
				pfn_notify, user_data, errcode_ret);
	}
	return ret;
#else
	cl_context ret = library->clCreateContextFromType(properties, device_type,
			pfn_notify, user_data, errcode_ret);
	return ret;
#endif //DEBUG_CHANGE_DEVICE
}
/**
 * コマンドキューAPI
 */
cl_command_queue clCreateCommandQueue(cl_context context, cl_device_id device,
		cl_command_queue_properties properties, cl_int* errcode_ret) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clCreateCommandQueue()");
#endif
	cl_command_queue ret;
#ifdef DEBUG_CHANGE_DEVICE
	if (isConnect && isChangeDevice) {
		string devName = socketData->getExecData()->getDeviceName(
				FLAG_DEVICE_CURRENT);
		cl_device_id devId = devTable->getDeviceIdFromName(devName);
		if (devId != NULL) {
			device = devId;
		}
	}
#endif
	ret = library->clCreateCommandQueue(context, device, properties,
			errcode_ret);
	return ret;
}
/*
 cl_int clReleaseCommandQueue(cl_command_queue command_queue) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clReleaseCommandQueue()");
 #endif
 cl_int ret = library->clReleaseCommandQueue(command_queue);
 return ret;
 }
 */
/**
 * メモリオブジェクトAPI
 */
/*
 cl_int clReleaseMemObject(cl_mem memobj) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clReleaseMemObject()");
 #endif
 cl_int ret = library->clReleaseMemObject(memobj);
 return ret;
 }
 */

/**
 * プログラムオブジェクトAPI
 */
/*
 cl_int clReleaseProgram(cl_program program) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clReleaseProgram()");
 #endif
 cl_int ret = library->clReleaseProgram(program);
 return ret;
 }
 */
cl_int clBuildProgram(cl_program program, cl_uint num_devices,
		const cl_device_id *device_list, const char *options,
		void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
		void *user_data) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clBuildProgram()");
#endif
	cl_int ret;
#ifdef DEBUG_CHANGE_DEVICE
	if (isConnect && isChangeDevice) {
		string devName = socketData->getExecData()->getDeviceName(
				FLAG_DEVICE_CURRENT);
		cl_device_id devId = devTable->getDeviceIdFromName(devName);
		if (devId != NULL) {
			ret = library->clBuildProgram(program, 1, &devId, options,
					pfn_notify, user_data);
			return ret;
		}
	}
#endif
	ret = library->clBuildProgram(program, num_devices, device_list, options,
			pfn_notify, user_data);
	return ret;
}
/**
 * カーネルオブジェクトAPI
 */
cl_kernel clCreateKernel(cl_program program, const char *kernel_name,
		cl_int *errcode_ret) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clCreateKernel()");
#endif
#ifdef DEBUG_CHANGE_WORKSIZE
	size_t size;
/* このあたりよくわからんけどおちるので放置
	cl_int reti = library->clGetProgramInfo(program, CL_PROGRAM_SOURCE, 0,
			NULL, &size);
	reti = library->clGetProgramInfo(program, CL_PROGRAM_SOURCE, size, src,
			&size);
*/
	char* src = new char[size];
	//char* hashc = getHash(src);
	char* hashc = new char[size];
	string hash("test");

	/*TODO 1プログラム1カーネルコードという前提 */
	KernelCode* kernel = execData->getKernelCode(KERNEL_INDEX);
	if (kernel == NULL) {
		execData->addKernelCode();
		// kernelnameは取得できない
		kernel = execData->getKernelCode(KERNEL_INDEX);
		kernel->setHash(hash);
	}
	if (!kernel->isFuncName(kernel_name)) { //既に存在するか確認
		kernel->addFuncData();
		int fsize = kernel->getFuncNum();
		kernel->getFuncData(fsize - 1)->setFuncName(kernel_name);
	}
	delete src;
	delete hashc;
#endif
	cl_kernel ret = library->clCreateKernel(program, kernel_name, errcode_ret);
	return ret;
}
/*
 cl_int clReleaseKernel(cl_kernel kernel) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clReleaseKernel()");
 #endif
 cl_int ret = library->clReleaseKernel(kernel);
 return ret;
 }
 */
/*
 cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size,
 const void *arg_value) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clSetKernelArg()");
 #endif
 cl_int ret = library->clSetKernelArg(kernel, arg_index, arg_size,
 arg_value);
 return ret;
 }
 */

/**
 * カーネル実行API
 */
cl_int clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel,
		cl_uint work_dim, const size_t *global_work_offset,
		const size_t *global_work_size, const size_t *local_work_size,
		cl_uint num_events_in_wait_list, const cl_event *event_wait_list,
		cl_event *event) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clEnqueueNDRangeKernel()");
	if (command_queue != NULL) {
		cl_device_id device_id;
		cl_int rets = library->clGetCommandQueueInfo(command_queue,
				CL_QUEUE_DEVICE, sizeof(cl_device_id), &device_id, NULL);
		char name[64];
		rets = library->clGetDeviceInfo(device_id, CL_DEVICE_NAME,
				sizeof(char) * 64, name, NULL);
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"using device_name : %s\n", name);
	}
#endif
	cl_int ret;
#ifdef DEBUG_CHANGE_WORKSIZE
	char name[128];
	library->clGetKernelInfo(kernel, CL_KERNEL_FUNCTION_NAME,
			sizeof(char) * 128, name, NULL);
	string funcName(name);
	FuncData* func = execData->getKernelCode(KERNEL_INDEX)->getFuncData(
			funcName);
	WorkItemSizeList* wsList =
			func->getResourceSize(FLAG_DEVICE_CURRENT)->getWorkSizeList(
					FLAG_LOCALWORKSIZE);
	if (isConnect) {
		if (funcname_current != funcName && wsList->getDim() == 0) {
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"/*****Change func : %s\n", funcName.c_str());
#endif
			funcname_current = funcName;
			socketData->setSignal(SIGNAL_INSTRUCT_RESOURCES);
			socketData->setSocketName(APP_SOCKET);
			for (int i = 0; i < (int) work_dim; i++) {
				func->addWorkItemSize(local_work_size[i], FLAG_DEVICE_SELECTED,
						FLAG_LOCALWORKSIZE);
			}
			ResourceAllocater task(library);
			task.doTask(socketData, appSocketManager);
#ifdef DEBUG
			int size =
					func->getResourceSize(FLAG_DEVICE_CURRENT)->getWorkSizeList(
							FLAG_LOCALWORKSIZE)->getSize(0);
			if (size != 0) {
				__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"GET lws[0] : %d\n", size);
			}
#endif
		}
		if (wsList->getDim() > 0) {
			const size_t* lws = wsList->getSizeList();
#ifdef DEBUG
			__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"CHANGE! %s - lws[0] : %d\n", funcName.c_str(), lws[0]);
#endif
			ret = library->clEnqueueNDRangeKernel(command_queue, kernel,
					work_dim, global_work_offset, global_work_size, lws,
					num_events_in_wait_list, event_wait_list, event);
		} else {
			ret = library->clEnqueueNDRangeKernel(command_queue, kernel,
					work_dim, global_work_offset, global_work_size,
					local_work_size, num_events_in_wait_list, event_wait_list,
					event);
		}
	} else {
		ret = library->clEnqueueNDRangeKernel(command_queue, kernel, work_dim,
				global_work_offset, global_work_size, local_work_size,
				num_events_in_wait_list, event_wait_list, event);
	}
#else
	ret = library->clEnqueueNDRangeKernel(command_queue, kernel,
			work_dim, global_work_offset, global_work_size, local_work_size,
			num_events_in_wait_list, event_wait_list, event);
#endif
	//時間取得
	if (!isStart) {
		gettimeofday(&startTime, NULL);
		isStart = true;
	}
	return ret;
}
/*
 cl_int clReleaseEvent(cl_event event) {
 #ifdef DEBUG
 __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clReleaseEvent()");
 #endif
 cl_int ret = library->clReleaseEvent(event);
 return ret;
 }
 */
/**
 * 終了待ちAPI
 */
cl_int clFlush(cl_command_queue command_queue) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clFlush()");
#endif
	cl_int ret = library->clFlush(command_queue);

	/*TODO destructorの代わり */
	fini();

	return ret;
}
cl_int clFinish(cl_command_queue command_queue) {
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"function : %s\n", "clFinish()");
#endif
	cl_int ret = library->clFinish(command_queue);
	if (isStart) {
		struct timeval endTime;
		gettimeofday(&endTime, NULL);
		double timeSum = (endTime.tv_sec - startTime.tv_sec)
				+ (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
#ifdef DEBUG
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG,"%f秒かかりました\n", timeSum);
#endif
		isStart = false;
	}
	return ret;
}

} // namespace wrappedopencl

#ifdef __cplusplus
}
#endif

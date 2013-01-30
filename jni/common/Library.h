/*
 * Library.h
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * typedef
 */
/**
 * プラットフォームAPI
 */
typedef cl_int (*func_clGetPlatformIDs)(cl_uint, cl_platform_id*, cl_uint*);
typedef cl_int (*func_clGetPlatformInfo)(cl_platform_id, cl_platform_info,
		size_t, void*, size_t*);
typedef cl_int (*func_clGetDeviceIDs)(cl_platform_id /* platform */,
		cl_device_type /* device_type */, cl_uint /* num_entries */,
		cl_device_id * /* devices */, cl_uint * /* num_devices */
		);
typedef cl_int (*func_clGetDeviceInfo)(cl_device_id, cl_device_info, size_t,
		void*, size_t*);
typedef cl_context (*func_clCreateContext)(const cl_context_properties*,
		cl_uint, const cl_device_id*,
		void (CL_CALLBACK *)(const char*, const void*, size_t, void*), void*,
		cl_int*);
typedef cl_context (*func_clCreateContextFromType)(const cl_context_properties*,
		cl_device_type,
		void (CL_CALLBACK *)(const char*, const void*, size_t, void*), void*,
		cl_int*);
typedef cl_int (*func_clReleaseContext)(cl_context);
typedef cl_int (*func_clGetContextInfo)(cl_context, cl_context_info, size_t,
		void*, size_t*);
/**
 * コマンドキューAPI
 */
typedef cl_command_queue (*func_clCreateCommandQueue)(cl_context, cl_device_id,
		cl_command_queue_properties, cl_int*);
typedef cl_int (*func_clReleaseCommandQueue)(cl_command_queue);
typedef cl_int (*func_clGetCommandQueueInfo)(cl_command_queue,
		cl_command_queue_info, size_t, void*, size_t*);
/**
 * メモリオブジェクトAPI
 */
typedef cl_mem (*func_clCreateBuffer)(cl_context, cl_mem_flags, size_t, void*,
		cl_int*);
typedef cl_int (*func_clEnqueueReadBuffer)(cl_command_queue, cl_mem, cl_bool,
		size_t, size_t, void*, cl_uint, const cl_event*, cl_event*);
typedef cl_int (*func_clEnqueueWriteBuffer)(cl_command_queue, cl_mem, cl_bool,
		size_t, size_t, const void*, cl_uint, const cl_event *, cl_event *);
typedef cl_int (*func_clReleaseMemObject)(cl_mem);
/**
 * プログラムオブジェクトAPI
 */
typedef cl_program (*func_clCreateProgramWithSource)(cl_context, cl_uint,
		const char**, const size_t*, cl_int*);
typedef cl_program (*func_clCreateProgramWithBinary)(cl_context, cl_uint,
		const cl_device_id*, const size_t*, const unsigned char**, cl_int*,
		cl_int*);
typedef cl_int (*func_clReleaseProgram)(cl_program);
typedef cl_int (*func_clBuildProgram)(cl_program, cl_uint, const cl_device_id*,
		const char*, void (CL_CALLBACK *)(cl_program, void*), void*);
typedef cl_int (*func_clGetProgramInfo)(cl_program, cl_program_info, size_t,
		void*, size_t*);
/**
 * カーネルオブジェクトAPI
 */
typedef cl_kernel (*func_clCreateKernel)(cl_program, const char*, cl_int*);
typedef cl_int (*func_clReleaseKernel)(cl_kernel);
typedef cl_int (*func_clSetKernelArg)(cl_kernel, cl_uint, size_t, const void*);
typedef cl_int (*func_clGetKernelInfo)(cl_kernel, cl_kernel_info, size_t, void*, size_t*);
/**
 * カーネル実行API
 */
typedef cl_int (*func_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel,
		cl_uint, const size_t*, const size_t*, const size_t*, cl_uint,
		const cl_event*, cl_event*);
/**
 * イベントオブジェクトAPI
 */
typedef cl_int (*func_clWaitForEvents)(cl_uint, const cl_event*);
typedef cl_int (*func_clReleaseEvent)(cl_event);
/**
 * 終了待ちAPI
 */
typedef cl_int (*func_clFlush)(cl_command_queue);
typedef cl_int (*func_clFinish)(cl_command_queue);
/**
 * 変数
 */

class Library {
private:
	void *dl_handle;

	func_clGetPlatformIDs p_clGetPlatformIDs;
	//func_clGetPlatformInfo p_clGetPlatformInfo;
	func_clGetDeviceIDs p_clGetDeviceIDs;
	func_clGetDeviceInfo p_clGetDeviceInfo;
	func_clCreateContext p_clCreateContext;
	func_clCreateContextFromType p_clCreateContextFromType;
	//func_clReleaseContext p_clReleaseContext;
	func_clCreateCommandQueue p_clCreateCommandQueue;
	func_clReleaseCommandQueue p_clReleaseCommandQueue;
	func_clGetCommandQueueInfo p_clGetCommandQueueInfo;
	//func_clCreateBuffer p_clCreateBuffer;
	//func_clEnqueueReadBuffer p_clEnqueueReadBuffer;
	//func_clEnqueueWriteBuffer p_clEnqueueWriteBuffer;
	func_clReleaseMemObject p_clReleaseMemObject;
	//func_clCreateProgramWithSource p_clCreateProgramWithSource;
	//func_clCreateProgramWithBinary p_clCreateProgramWithBinary;
	func_clReleaseProgram p_clReleaseProgram;
	func_clBuildProgram p_clBuildProgram;
	func_clGetProgramInfo p_clGetProgramInfo;
	func_clCreateKernel p_clCreateKernel;
	func_clReleaseKernel p_clReleaseKernel;
	func_clSetKernelArg p_clSetKernelArg;
	func_clGetKernelInfo p_clGetKernelInfo;
	func_clEnqueueNDRangeKernel p_clEnqueueNDRangeKernel;
	//func_clWaitForEvents p_clWaitForEvents;
	func_clReleaseEvent p_clReleaseEvent;
	func_clFlush p_clFlush;
	func_clFinish p_clFinish;

	cl_platform_id *changed_platforms;
	cl_device_id *changed_devices;
	cl_device_type changed_device_type;
public:
	Library();
	virtual ~Library();
	cl_int loadFunctions();

	cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id* platforms,
			cl_uint* num_platforms);
	//cl_int clGetPlatformInfo(
	//		cl_platform_id platform,
	//		cl_platform_info param_name,
	//		size_t param_value_size,
	//		void* param_value,
	//		size_t* param_value_size_ret
	//);
	cl_int clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type,
			cl_uint num_entries, cl_device_id * devices, cl_uint * num_devices);
	cl_int clGetDeviceInfo(cl_device_id device, cl_device_info param_name,
			size_t param_value_size, void* param_value,
			size_t* param_value_size_ret);
	cl_context clCreateContext(const cl_context_properties *properties,
			cl_uint num_devices, const cl_device_id *devices,
			void (CL_CALLBACK *pfn_notify)(const char *errinfo,
					const void *private_info, size_t cb, void *user_data),
			void *user_data, cl_int *errcode_ret);
	cl_context clCreateContextFromType(const cl_context_properties *properties,
			cl_device_type device_type,
			void (CL_CALLBACK *pfn_notify)(const char *errinfo,
					const void *private_info, size_t cb, void *user_data),
			void *user_data, cl_int *errcode_ret);
	//cl_int clReleaseContext(
	//		cl_context context
	//);

	/**
	 * コマンドキューAPI
	 */
	cl_command_queue clCreateCommandQueue(cl_context context,
			cl_device_id device, cl_command_queue_properties properties,
			cl_int* errcode_ret);
	cl_int clReleaseCommandQueue(cl_command_queue command_queue);
	cl_int clGetCommandQueueInfo(cl_command_queue, cl_command_queue_info,
			size_t, void*, size_t*);
	/**
	 * メモリオブジェクトAPI
	 */
	//cl_mem clCreateBuffer(
	//		cl_context context,
	//		cl_mem_flags flags,
	//		size_t size,
	//		void *host_ptr,
	//		cl_int *errcode_ret
	//);
	//cl_int clEnqueueReadBuffer(
	//		cl_command_queue command_queue,
	//		cl_mem buffer,
	//		cl_bool blocking_read,
	//		size_t offset,
	//		size_t cb,
	//		void* ptr,
	//		cl_uint num_events_in_wait_list,
	//		const cl_event* event_wait_list,
	//		cl_event* event
	//);
	//cl_int clEnqueueWriteBuffer(
	//		cl_command_queue command_queue,
	//		cl_mem buffer,
	//		cl_bool blocking_write,
	//		size_t offset,
	//		size_t cb,
	//		const void* ptr,
	//		cl_uint num_events_in_wait_list,
	//		const cl_event* event_wait_list,
	//		cl_event * event
	//);
	cl_int clReleaseMemObject(cl_mem memobj);
	/**
	 * プログラムオブジェクトAPI
	 */
	//cl_program clCreateProgramWithSource(
	//		cl_context context,
	//		cl_uint count,
	//		const char **strings,
	//		const size_t *lengths,
	//		cl_int *prrcode_ret
	//);
	//cl_program clCreateProgramWithBinary(
	//		cl_context context,
	//		cl_uint num_devices,
	//		const cl_device_id *device_list,
	//		const size_t *lengths,
	//		const unsigned char **binaries,
	//		cl_int *binary_status,
	//		cl_int *errcode_ret
	//);
	cl_int clReleaseProgram(cl_program program);
	cl_int clBuildProgram(cl_program program, cl_uint num_devices,
			const cl_device_id *device_list, const char *options,
			void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
			void *user_data);
	cl_int clGetProgramInfo(cl_program program, cl_program_info param_name, size_t param_value_size,
			void* param_value, size_t* param_value_size_ret);
	/**
	 * カーネルオブジェクトAPI
	 */
	cl_kernel clCreateKernel(cl_program program, const char *kernel_name,
			cl_int *errcode_ret);
	cl_int clReleaseKernel(cl_kernel kernel);
	cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size,
			const void *arg_value);
	cl_int clGetKernelInfo(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);

	/**
	 * カーネル実行API
	 */
	cl_int clEnqueueNDRangeKernel(cl_command_queue command_queue,
			cl_kernel kernel, cl_uint work_dim,
			const size_t *global_work_offset, const size_t *global_work_size,
			const size_t *local_work_size, cl_uint num_events_in_wait_list,
			const cl_event *event_wait_list, cl_event *event);
	/**
	 * イベントオブジェクトAPI
	 */
	//cl_int clWaitForEvents(
	//		cl_uint num_events,
	//		const cl_event *event_list
	//);
	cl_int clReleaseEvent(cl_event event);

	/**
	 * 終了待ちAPI
	 */
	cl_int clFlush(cl_command_queue command_queue);
	cl_int clFinish(cl_command_queue command_queue);
};

#ifdef __cplusplus
}
#endif

#endif /* LIBRARY_H_ */

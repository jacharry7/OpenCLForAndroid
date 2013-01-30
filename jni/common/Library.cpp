/*
 * Library.cpp
 *
 *  Created on: 2012/11/29
 *      Author: sakakibara
 */

#include "Library.h"

Library::Library() {

}

Library::~Library() {
	if (dl_handle) {
		dlclose(dl_handle);
	}
#ifdef DEBUG
	printf("OK dlclose()\n");
#endif
	free(changed_platforms);
	free(changed_devices);
}

cl_int Library::loadFunctions() {
#ifdef DEBUG_PRINT
	printf("function : %s\n", "loadFinctions()");
#endif
	dlerror();

	const char* path_lib = "/usr/lib/libOpenCL.so";
	dl_handle = dlopen(path_lib, RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
		printf("dlerror : %s\n", dlerror());
		exit(1);
	}
#ifdef DEBUG_PRINT
	printf("dlopen %s\n", "Load:libOpenCL.so");
#endif
	dlerror();
	p_clGetPlatformIDs = (func_clGetPlatformIDs) dlsym(dl_handle,
			"clGetPlatformIDs");
//	p_clGetPlatformInfo = (func_clGetPlatformInfo)dlsym(dl_handle, "clGetPlatformInfo");
	p_clGetDeviceIDs = (func_clGetDeviceIDs) dlsym(dl_handle, "clGetDeviceIDs");
	p_clGetDeviceInfo = (func_clGetDeviceInfo) dlsym(dl_handle,
			"clGetDeviceInfo");
	p_clCreateContext = (func_clCreateContext) dlsym(dl_handle,
			"clCreateContext");
	p_clCreateContextFromType = (func_clCreateContextFromType) dlsym(dl_handle,
			"clCreateContextFromType");
//	p_clReleaseContext = (func_clReleaseContext)dlsym(dl_handle, "clReleaseContext");
	p_clCreateCommandQueue = (func_clCreateCommandQueue) dlsym(dl_handle,
			"clCreateCommandQueue");
//	p_clReleaseCommandQueue = (func_clReleaseCommandQueue) dlsym(dl_handle,
//			"clReleaseCommandQueue");
	p_clGetCommandQueueInfo = (func_clGetCommandQueueInfo) dlsym(dl_handle,
			"clGetCommandQueueInfo");
//	p_clCreateBuffer = (func_clCreateBuffer)dlsym(dl_handle, "clCreateBuffer");
//	p_clEnqueueReadBuffer = (func_clEnqueueReadBuffer)dlsym(dl_handle, "clEnqueueReadBuffer");
//	p_clEnqueueWriteBuffer = (func_clEnqueueWriteBuffer)dlsym(dl_handle, "clEnqueueWriteBuffer");
//	p_clReleaseMemObject = (func_clReleaseMemObject) dlsym(dl_handle,
//			"clReleaseMemObject");
//	p_clCreateProgramWithSource = (func_clCreateProgramWithSource)dlsym(dl_handle, "clCreateProgramWithSource");
//	p_clCreateProgramWithBinary = (func_clCreateProgramWithBinary)dlsym(dl_handle, "clCreateProgramWithBinary");
//	p_clReleaseProgram = (func_clReleaseProgram) dlsym(dl_handle,
//			"clReleaseProgram");
	p_clBuildProgram = (func_clBuildProgram) dlsym(dl_handle, "clBuildProgram");
	p_clGetProgramInfo = (func_clGetProgramInfo) dlsym(dl_handle,
			"clGetProgramInfo");
	p_clCreateKernel = (func_clCreateKernel) dlsym(dl_handle, "clCreateKernel");
//	p_clReleaseKernel = (func_clReleaseKernel) dlsym(dl_handle,
//			"clReleaseKernel");
	p_clSetKernelArg = (func_clSetKernelArg) dlsym(dl_handle, "clSetKernelArg");
	p_clGetKernelInfo = (func_clGetKernelInfo) dlsym(dl_handle, "clGetKernelInfo");
	p_clEnqueueNDRangeKernel = (func_clEnqueueNDRangeKernel) dlsym(dl_handle,
			"clEnqueueNDRangeKernel");
//	p_clWaitForEvents = (func_clWaitForEvents)dlsym(dl_handle, "clWaitForEvents");
//	p_clReleaseEvent = (func_clReleaseEvent) dlsym(dl_handle, "clReleaseEvent");
	p_clFlush = (func_clFlush) dlsym(dl_handle, "clFlush");
	p_clFinish = (func_clFinish) dlsym(dl_handle, "clFinish");
#ifdef DEBUG_PRINT
	printf("dlerror : %s\n", dlerror());
#endif
	return CL_SUCCESS;
}

cl_int Library::clGetPlatformIDs(cl_uint num_entries, cl_platform_id* platforms,
		cl_uint* num_platforms) {
	cl_int ret = p_clGetPlatformIDs(num_entries, platforms, num_platforms);
	return ret;
}

//cl_int clGetPlatformInfo(
//		cl_platform_id platform,
//		cl_platform_info param_name,
//		size_t param_value_size,
//		void* param_value,
//		size_t* param_value_size_ret
//)
//{
//	printf("function : %s\n","clGetPlatformInfo()");
//	  cl_int ret = library->p_clGetPlatformInfo(
//			  platform,
//			  param_name,
//			  param_value_size,
//			  param_value,
//			  param_value_size_ret
//	  );
//	  return ret;
//}

cl_int Library::clGetDeviceIDs(cl_platform_id platform,
		cl_device_type device_type, cl_uint num_entries, cl_device_id * devices,
		cl_uint * num_devices) {
	cl_int ret = p_clGetDeviceIDs(platform, device_type, num_entries, devices,
			num_devices);
	return ret;
}

cl_int Library::clGetDeviceInfo(cl_device_id device, cl_device_info param_name,
		size_t param_value_size, void* param_value,
		size_t* param_value_size_ret) {
	cl_int ret = p_clGetDeviceInfo(device, param_name, param_value_size,
			param_value, param_value_size_ret);
	return ret;
}

cl_context Library::clCreateContext(const cl_context_properties *properties,
		cl_uint num_devices, const cl_device_id *devices,
		void (CL_CALLBACK *pfn_notify)(const char *errinfo,
				const void *private_info, size_t cb, void *user_data),
		void *user_data, cl_int *errcode_ret) {
	cl_context ret = p_clCreateContext(properties, num_devices, devices,
			pfn_notify, user_data, errcode_ret);
	return ret;
}

cl_context Library::clCreateContextFromType(
		const cl_context_properties *properties, cl_device_type device_type,
		void (CL_CALLBACK *pfn_notify)(const char *errinfo,
				const void *private_info, size_t cb, void *user_data),
		void *user_data, cl_int *errcode_ret) {
	cl_context ret = p_clCreateContextFromType(properties, device_type,
			pfn_notify, user_data, errcode_ret);
	return ret;
}

//cl_int clReleaseContext(
//		cl_context context
//)
//{
//	printf("function : %s\n","clReleaseContext()");
//	cl_int ret = library->p_clReleaseContext(
//			context
//	);
//	return ret;
//}

/**
 * コマンドキューAPI
 */
cl_command_queue Library::clCreateCommandQueue(cl_context context,
		cl_device_id device, cl_command_queue_properties properties,
		cl_int* errcode_ret) {
	cl_command_queue ret = p_clCreateCommandQueue(context, device, properties,
			errcode_ret);
	return ret;
}
/*
cl_int Library::clReleaseCommandQueue(cl_command_queue command_queue) {
	cl_int ret = p_clReleaseCommandQueue(command_queue);
	return ret;
}
*/
cl_int Library::clGetCommandQueueInfo(cl_command_queue command_queue,
		cl_command_queue_info param_name, size_t param_value_size,
		void* param_value, size_t* param_value_size_ret) {
	cl_int ret = p_clGetCommandQueueInfo(command_queue, param_name,
			param_value_size, param_value, param_value_size_ret);
	return ret;
}
/**
 * メモリオブジェクトAPI
 */
//cl_mem clCreateBuffer(
//		cl_context context,
//		cl_mem_flags flags,
//		size_t size,
//		void *host_ptr,
//		cl_int *errcode_ret
//)
//{
//	  cl_mem ret = library->p_clCreateBuffer(
//			  context,
//			  flags,
//			  size,
//			  host_ptr,
//			  errcode_ret
//	  );
//	  return ret;
//}
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
//)
//{
//	cl_int ret = library->p_clEnqueueReadBuffer(
//			command_queue,
//			buffer,
//			blocking_read,
//			offset,
//			cb,
//			ptr,
//			num_events_in_wait_list,
//			event_wait_list,
//			event
//	);
//	return ret;
//}
//
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
//)
//{
//	printf("function : %s\n","clEnqueueWriteBuffer()");
//	  cl_int ret = library->p_clEnqueueWriteBuffer(
//			  command_queue,
//			  buffer,
//			  blocking_write,
//			  offset,
//			  cb,
//			  ptr,
//			  num_events_in_wait_list,
//			  event_wait_list,
//			  event
//	  );
//	  return ret;
//
//}
/*
cl_int Library::clReleaseMemObject(cl_mem memobj) {
	cl_int ret = p_clReleaseMemObject(memobj);
	return ret;
}
*/
/**
 * プログラムオブジェクトAPI
 */
//cl_program clCreateProgramWithSource(
//		cl_context context,
//		cl_uint count,
//		const char **strings,
//		const size_t *lengths,
//		cl_int *prrcode_ret
//)
//{
//	printf("function : %s\n","clCreateProgramWithSource()");
//	  cl_program ret = library->p_clCreateProgramWithSource(
//			  context,
//			  count,
//			  strings,
//			  lengths,
//			  prrcode_ret
//	  );
//	  return ret;
//}
//
//cl_program clCreateProgramWithBinary(
//		cl_context context,
//		cl_uint num_devices,
//		const cl_device_id *device_list,
//		const size_t *lengths,
//		const unsigned char **binaries,
//		cl_int *binary_status,
//		cl_int *errcode_ret
//)
//{
//	printf("function : %s\n","clCreateProgramWithBinary()");
//	  cl_program ret = library->p_clCreateProgramWithBinary(
//			  context,
//			  num_devices,
//			  device_list,
//			  lengths,
//			  binaries,
//			  binary_status,
//			  errcode_ret
//	  );
//
//	  return ret;
//}
/*
cl_int Library::clReleaseProgram(cl_program program) {
	cl_int ret = p_clReleaseProgram(program);
	return ret;
}
*/
cl_int Library::clBuildProgram(cl_program program, cl_uint num_devices,
		const cl_device_id *device_list, const char *options,
		void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
		void *user_data) {
	cl_int ret = p_clBuildProgram(program, num_devices, device_list, options,
			pfn_notify, user_data);
	return ret;
}

cl_int Library::clGetProgramInfo(cl_program program, cl_program_info param_name,
		size_t param_value_size, void* param_value,
		size_t* param_value_size_ret) {
	cl_int ret = p_clGetProgramInfo(program, param_name, param_value_size,
			param_value, param_value_size_ret);
	return ret;
}

/**
 * カーネルオブジェクトAPI
 */
cl_kernel Library::clCreateKernel(cl_program program, const char *kernel_name,
		cl_int *errcode_ret) {
	cl_kernel ret = p_clCreateKernel(program, kernel_name, errcode_ret);
	return ret;
}
/*
cl_int Library::clReleaseKernel(cl_kernel kernel) {
	cl_int ret = p_clReleaseKernel(kernel);
	return ret;
}
cl_int Library::clSetKernelArg(cl_kernel kernel, cl_uint arg_index,
		size_t arg_size, const void *arg_value) {
	cl_int ret = p_clSetKernelArg(kernel, arg_index, arg_size, arg_value);
	return ret;
}
*/
cl_int Library::clGetKernelInfo(cl_kernel kernel, cl_kernel_info param_name,
		size_t param_value_size, void* param_value,
		size_t* param_value_size_ret) {
	cl_int ret = p_clGetKernelInfo(kernel, param_name, param_value_size, param_value, param_value_size_ret);
	return ret;
}

/**
 * カーネル実行API
 */
cl_int Library::clEnqueueNDRangeKernel(cl_command_queue command_queue,
		cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset,
		const size_t *global_work_size, const size_t *local_work_size,
		cl_uint num_events_in_wait_list, const cl_event *event_wait_list,
		cl_event *event) {
	cl_int ret = p_clEnqueueNDRangeKernel(command_queue, kernel, work_dim,
			global_work_offset, global_work_size, local_work_size,
			num_events_in_wait_list, event_wait_list, event);
	return ret;
}

/**
 * イベントオブジェクトAPI
 */
//cl_int clWaitForEvents(
//		cl_uint num_events,
//		const cl_event *event_list
//)
//{
//	  cl_int ret = library->clWaitForEvents(
//			  num_events,
//			  event_list
//	  );
//	  return ret;
//}
/*
cl_int Library::clReleaseEvent(cl_event event) {
	cl_int ret = p_clReleaseEvent(event);
	return ret;
}
*/
/**
 * 終了待ちAPI
 */
cl_int Library::clFlush(cl_command_queue command_queue) {
	cl_int ret = p_clFlush(command_queue);
	return ret;
}
cl_int Library::clFinish(cl_command_queue command_queue) {
	cl_int ret = p_clFinish(command_queue);
	return ret;
}


LOCAL_PATH := $(call my-dir)

#include $(call all-subdir-makefiles)

include $(CLEAR_VARS)
LOCAL_MODULE    := OpenCLw
LOCAL_SRC_FILES := \
common/Converter.cpp \
common/Library.cpp \
data/DeviceTable.cpp \
data/ExecData.cpp \
data/FuncData.cpp \
data/KernelCode.cpp \
data/ResourceSizeData.cpp \
data/Signal.cpp \
data/SocketData.cpp \
data/TagData.cpp \
data/WorkItemSizeList.cpp \
md5/md5.c \
md5/md5main.c \
service/UnixDomainSocketManager.cpp \
task/EventTask.cpp \
task/ProcessorAllocater.cpp \
task/ProcessorInfoManager.cpp \
task/ResourceAllocater.cpp \
tinyxml/tinystr.cpp \
tinyxml/tinyxml.cpp \
tinyxml/tinyxmlerror.cpp \
tinyxml/tinyxmlparser.cpp \
OpenCL.cpp
LOCAL_LDLIBS    := -llog -ldl
LOCAL_SHARED_LIBRARIES := 
include $(BUILD_SHARED_LIBRARY)

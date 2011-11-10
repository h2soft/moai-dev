#================================================================#
# libuslscore
#================================================================#
include $(CLEAR_VARS)

LOCAL_MODULE := libuslscore
LOCAL_LDLIBS := -llog -lstring -lm -lz

#----------------------------------------------------------------#
# header search paths
#----------------------------------------------------------------#
LOCAL_C_INCLUDES := $(SRC_PATH)/src \
$(SRC_PATH)/src/uslscore \
$(SRC_PATH)/src/moai-lua-5.1.3/src

#----------------------------------------------------------------#
# included files
#----------------------------------------------------------------#
LOCAL_SRC_FILES := $(SRC_PATH)/src/uslscore/uslscore-pch.cpp \
$(SRC_PATH)/src/uslscore/STLString.cpp \
$(SRC_PATH)/src/uslscore/USBase64Cipher.cpp \
$(SRC_PATH)/src/uslscore/USByteStream.cpp \
$(SRC_PATH)/src/uslscore/USCipher.cpp \
$(SRC_PATH)/src/uslscore/USCipherStream.cpp \
$(SRC_PATH)/src/uslscore/USDeflater.cpp \
$(SRC_PATH)/src/uslscore/USDeviceTime_apple.cpp \
$(SRC_PATH)/src/uslscore/USDeviceTime_posix.cpp \
$(SRC_PATH)/src/uslscore/USDeviceTime_win32.cpp \
$(SRC_PATH)/src/uslscore/USDirectoryItr.cpp \
$(SRC_PATH)/src/uslscore/USFilename.cpp \
$(SRC_PATH)/src/uslscore/USFileStream.cpp \
$(SRC_PATH)/src/uslscore/USFileSys.cpp \
$(SRC_PATH)/src/uslscore/USInflater.cpp \
$(SRC_PATH)/src/uslscore/USLog.cpp \
$(SRC_PATH)/src/uslscore/uslscore.cpp \
$(SRC_PATH)/src/uslscore/USMemStream.cpp \
$(SRC_PATH)/src/uslscore/USStream.cpp \
$(SRC_PATH)/src/uslscore/USStreamFormatter.cpp \
$(SRC_PATH)/src/uslscore/USZip.cpp \
$(SRC_PATH)/src/uslscore/USZipFile.cpp

include $(BUILD_STATIC_LIBRARY)
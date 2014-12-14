################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cnntrain.cpp \
../src/convolution_layer.cpp \
../src/relu_layer.cpp \
../src/norm_layer.cpp \
../src/pooling_layer.cpp \
../src/sigmoid.cpp \
../src/softmax.cpp \
../src/softmaxloss.cpp \
../src/softmaxloss_bp.cpp \
../src/convolution_layer_bp.cpp \
../src/pooling_layer_bp.cpp \
../src/norm_layer_bp.cpp \
../src/training_data_read.cpp 

OBJS += \
./src/cnntrain.o \
./src/convolution_layer.o \
./src/relu_layer.o \
./src/norm_layer.o \
./src/pooling_layer.o \
./src/sigmoid.o \
./src/softmax.o \
./src/softmaxloss.o \
./src/softmaxloss_bp.o \
./src/convolution_layer_bp.o \
./src/pooling_layer_bp.o \
./src/norm_layer_bp.o \
./src/training_data_read.o 

CPP_DEPS += \
./src/cnntrain.d \
./src/convolution_layer.d \
./src/norm_layer.d \
./src/pooling_layer.d \
./src/sigmoid.d \
./src/relu_layer.d \
./src/softmax.d \
./src/softmaxloss.d \
./src/softmaxloss_bp.d \
./src/convolution_layer_bp.d \
./src/pooling_layer_bp.d \
./src/norm_layer_bp.d \
./src/training_data_read.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv -I"../inc" -I/usr/local/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



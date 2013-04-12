################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include envvars.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: init distocache

init:
	chmod 755 chkIncludes.sh
	sh chkIncludes.sh
	
# Tool invocations
distocache: init $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C++ Linker'
	g++ $(PTHREADS) -L/usr/local/lib -o "distocache" $(OBJS) $(USER_OBJS) $(LIBS) $(EX_LIBS)
	@echo 'Finished building target: $@'
	rm -Rf distocache-server
	mkdir distocache-server
	cp -Rf ../resources/* distocache-server/
	cp -Rf distocache distocache-server/
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS) $(OBJS) $(C_DEPS) $(CC_DEPS) $(CPP_DEPS) $(EXECUTABLES) $(CXX_DEPS) $(C_UPPER_DEPS) distocache
	rm -rf distocache-server
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

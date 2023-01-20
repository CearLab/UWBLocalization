CC = gcc -Wall -Wextra

SOURCEDIRS = . ../common ../ranging_service/wrapper ../ranging_service/adjm_proto ../ranging_service
vpath %.c $(SOURCEDIRS)
CFLAGS += ${addprefix -I,$(SOURCEDIRS)}

srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)
deps = $(srcs:.c=.d)
exec = test

LIBNAME = libUWBranging.so

$(LIBNAME): ipc_interface.o ranging_api.o cubes_common.o cubes_wrapper.o ipc_proto.o network_handler.o range_scheduler.o ranging_service.o serial.o
	$(CC) $^ -shared -o libUWBranging.so -lrt
# a generic method for compiling all source .c files into
# object .o files with automatic creation of file dependencies
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -lrt -fPIC

-include $(deps)

# "clean" target, to remove all binaries ("make clean")
.PHONY: clean
clean:
	rm -f *.o *.d $(ALL_TARGETS)

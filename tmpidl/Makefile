################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify            #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       March 9, 2022                                                  #
################################################################################

TARGET_LIB := libtmpidl.so
BUILD_DIR := ./build
SRC_DIRS := .
SRCS := $(shell find $(SRC_DIRS) -name "*.c")
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

ifdef omp
	CFLAGS := $(CFLAGS) -MMD -MP -I../ -O3 -fPIC -flto -fopenmp -DNDEBUG
	LFLAGS := -O3 -flto -fopenmp -shared
else
	CFLAGS := $(CFLAGS) -MMD -MP -I../ -O3 -fPIC -flto -DNDEBUG
	LFLAGS := -O3 -flto -shared
endif

.PHONY: clean install uninstall all

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@ -lm

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

install:
	cp $(TARGET_LIB) /usr/local/lib/$(TARGET_LIB)

uninstall:
	rm -rf $(BUILD_DIR)
	rm -f /usr/local/lib/$(TARGET_LIB)

-include $(DEPS)


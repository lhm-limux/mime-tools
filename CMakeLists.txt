# Mime-Tools
#
# Copyright (C) 2017 Max Harmathy <max.harmathy@web.de>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.


cmake_minimum_required(VERSION 2.8.12)

project(mime-tools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
set(QT_MINIMUM_VERSION 5.2.0)


add_executable(mime-assocs-for mime-assocs-for.cpp)
target_link_libraries(mime-assocs-for Qt5::Core)

# Copyright (c) 2014-present, The osquery authors
#
# This source code is licensed as defined by the LICENSE file found in the
# root directory of this source tree.
#
# SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)

project("ping_extension")

addOsqueryExtension(
  "${PROJECT_NAME}"
  main.cpp
)


add_executable(ping_test helpers.cpp ping_test.cpp)
# add_osquery_executable(ping_test ping_test.cpp)
target_link_libraries(ping_test PRIVATE
thirdparty_googletest
# osquery_cxx_settings
# osquery_core
# osquery_sdk_pluginsdk
# osquery_sql
)

add_test(NAME ping_test COMMAND ping_test)
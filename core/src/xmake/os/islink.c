/*!The Make-like Build Utility based on Lua
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2015 - 2018, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        islink.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME                "islink"
#define TB_TRACE_MODULE_DEBUG               (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#ifndef TB_CONFIG_OS_WINDOWS
#   include <sys/stat.h>
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_int_t xm_os_islink(lua_State* lua)
{
    // check
    tb_assert_and_check_return_val(lua, 0);

    // get the path 
    tb_char_t const* path = luaL_checkstring(lua, 1);
    tb_check_return_val(path, 0);

    // is link?
#if defined(TB_CONFIG_OS_WINDOWS)
    lua_pushboolean(lua, tb_false);
#elif defined(TB_CONFIG_POSIX_HAVE_STAT64)
    struct stat64 st = {0};
    lua_pushboolean(lua, !lstat64(path, &st) && S_ISLNK(st.st_mode));
#else
    struct stat st = {0};
    lua_pushboolean(lua, !lstat(path, &st) && S_ISLNK(st.st_mode));
#endif

    // ok
    return 1;
}
/*
 * File: os.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_OS_H
#define LG_OS_H

#include <stdio.h>
#include <stdbool.h>

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32) && !defined(_CYGWIN_)
#define LG_USE_WINAPI
#include <windows.h>
#define LG_PATH_DELIM_CHAR '\\'
#define LG_PATH_DELIM_STR "\\"
#else
#define LG_USE_LINUX_API
#define LG_PATH_DELIM_CHAR '/'
#define LG_PATH_DELIM_STR "/"
#endif

 /* Returns true if dir_path points to an existing directory. */
bool _does_dir_exist(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    DWORD ftyp = GetFileAttributesA(abs_path);
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
    else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;
    }
    return false;
#endif
}

/* Creates the directory in dir_path and returns true if successful. */
bool _create_dir(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    /* TODO: Recursive folder creation, i.e. create parent folder(s) */
    return CreateDirectoryA(abs_path, NULL) != 0;
#endif
}

bool _remove_dir(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    return RemoveDirectoryA(abs_path) == 0;
#endif
    return false;
}

/* TODO */
bool _remove_file(const char* abs_path)
{
    return true;
}

/* Returns true if filepath points to an existing file. */
bool _does_file_exist(const char* abs_path)
{
    FILE* f = fopen(abs_path, "r");
    if (f)
    {
        fclose(f);
        return true;
    }
    return false;
}

#endif /* LG_OS_H */

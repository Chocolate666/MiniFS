//
//	mfs_coresystem.cpp
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	Class MiniFS: Basic definition.
//

#include "mini_file_system.h"
#include <Windows.h>

MiniFS::MiniFS()
{
    mount_flag = false;
    SetConsoleTitle(L"Mini-FS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "Mini File System [版本 3.2.13]" << std::endl;
    std::cout << "(c) 2018 AlphaBeta。保留所有权利。" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

MiniFS::~MiniFS()
{
}

#ifdef SYSTEM_TEST

void MiniFS::Test_createFile(int file_num)
{
    if (file_num < 1)
        return;
    for (int i = 1; i < file_num; i++)
    {
        std::string file_name = std::to_string(i);
        this->createFile((char *)file_name.data());
    }
}

#endif
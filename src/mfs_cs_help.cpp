//
//	mfs_cs_help.cpp
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	Class MiniFS: This file implementation Help Module of Mini File System.
//

#include "mini_file_system.h"

inline void HelpOutput(const char cmd_name[], const char cmd_content[],
					   const char cmd_layout[])
{
	std::cout.setf(std::ios::left);
	std::cout.fill('.');
	std::cout.width(12);
	std::cout << cmd_name;
	std::cout.fill(' ');
	std::cout.width(18);
	std::cout << cmd_content;
	std::cout << "指令格式: ";
	std::cout.fill(' ');
	std::cout << cmd_layout << std::endl;
	std::cout.unsetf(std::ios::left);
}

inline void HelpDetail(const char cmd_name[], const char cmd_layout[],
					   const char cmd_content[], const char cmd_example[])
{
	std::cout << " " << cmd_name << std::endl;
	std::cout << " 指令格式: " << cmd_layout << std::endl;
	std::cout << " 指令含义: " << cmd_content << std::endl;
	std::cout << " 指令示例: " << cmd_example << std::endl;
}

void MiniFS::showHelp(int mode)
{
	puts(" ");
	switch (mode)
	{
	case 0:
		HelpOutput(" create ", " 创建空间", "create <name> [size(可选)]");
		HelpOutput(" mount ", " 安装空间", "mount <name>");
		HelpOutput(" fmt ", " 格式化空间", "fmt [size(可选)]");
		HelpOutput(" close ", " 退出空间", "close");
		HelpOutput(" dr ", " 显示目录", "dr");
		HelpOutput(" cp ", " 拷贝文件", "cp <name_old> <name_new>");
		HelpOutput(" dl ", " 删除文件", "dl <name>");
		HelpOutput(" tree ", " 显示目录树", "tp <name>");
		HelpOutput(" move ", " 移动文件", "more <name1> <name2>");
		HelpOutput(" att ", " 显示文件属性", "att <name>");
		HelpOutput(" help ", " 帮助信息", "help [命令名(可选)]");
		HelpOutput(" end ", " 退出程序", "end");
		HelpOutput(" mkdir ", " 新建文件夹", "mkdir <dirName>");
		HelpOutput(" touch ", " 新建文件", "touch <filename>");
		HelpOutput(" lrb ", " 显示回收站", "lrb");
		HelpOutput(" crb ", " 清空回收站", "crb");
		HelpOutput(" map ", " 显示文件占用块号", "map <filename>");
		HelpOutput(" cd ", " 位置转移", "cd dirName");
		HelpOutput(" opt ", " 优化空间", "opt");
		HelpOutput(" rec ", " 恢复文件(夹)", "rec <name>");
		HelpOutput(" fd ", " 查找文件(夹)", "fd <name>");
		break;

	case 1:
		HelpDetail("create", "create <name> [size(可选)]",
				   "用 create 命令建立一个新的 Mini-FS 空间",
				   "create SName 建立一个名为 SName 大小为 1G 的 Windows 文件作为存储空间 \n\t  create SName 2048 建立一个名为 SName 大小为 2G 的 Windows 文件作为存储空间");
		break;

	case 2:
		HelpDetail("mount", "mount <name>", "用 mount 命令安装要操作的空间",
				   "mount SName 在 Mini-FS 中安装(打开)空间 SName，为后续操作进行准备");
		break;

	case 3:
		HelpDetail("fmt", "fmt [size(可选)]", "用 fmt 命令格式化当前的空间",
				   "fmt 初始化当前打开的 SName 空间，簇大小设置为 4KB \n\t  fmt 8 初始化当前打开的 SName 空间，簇大小设置为 8KB");
		break;

	case 4:
		HelpDetail("close", "close", "用 close 命令退出 Mini-FS", "close 退出并关闭 Mini-FS 系统");
		break;

	case 5:
		HelpDetail("dr", "dr", "dr 显示当前目录下的文件目录", "dr 显示当前目录下所有文件及文件夹");
		break;

	case 6:
		HelpDetail("cp", "cp <name1> <name2>", "用 cp 命令拷贝文件",
				   "cp wFName sFName 将文件从 Windows 空间中拷贝至 Mini-FS 空间中 \n\t   cp sFName wFName 将文件从 Mini-FS 空间中拷贝至 Windows 空间中 \n\t   cp sFName1 sFName2 将文件从 Mini-FS 空间中拷贝至 Mini-FS 空间中");
		break;

	case 7:
		HelpDetail("dl", "dl <name>", "用 dl 命令删除空间中的文件",
				   "dl sFName 将文件 sFName 从空间中删除");
		break;

	case 8:
		HelpDetail("tree", "tree", "用 tree 命令显示目录树", "tree 显示目录树");
		break;

	case 9:
		HelpDetail("move", "move <name1> <name2>", "用 move 命令移动文件",
				   "move name1 name2 将 name1 文件移动到 name2");
		break;

	case 10:
		HelpDetail("att", "att <name>", "用 att 命令显示文本属性",
				   "att sFName 显示名为 sFName 的文件的文件属性(文件名、拓展名、创建时间、文件大小)");
		break;

	case 11:
		HelpDetail("help", "help [命令名(可选)]", "用 help 命令获取帮助信息",
				   "help 显示系统名称及含义 \n\t   help create 显示 create 的指令格式等详细信息");
		break;

	case 12:
		HelpDetail("end", "end", "用 end 命令退出程序", "end 退出程序");
		break;

	case 13:
		HelpDetail("mkdir", "mkdir <dirName>", "用 mkdir 命令新建文件夹",
				   "mkdir 新建名为 dirName 的文件夹");
		break;

	case 14:
		HelpDetail("touch", "touch <fileName>", "用 touch 命令新建文件",
				   "touch 新建名为 fileName 的文件");
		break;

	case 15:
		HelpDetail("lrb", "lrb", "用 lrb 命令显示回收站内容", "lrb 显示回收站内容");
		break;

	case 16:
		HelpDetail("crb", "crb", "用 crb 命令清空回收站", "crb 清空回收站");
		break;

	case 17:
		HelpDetail("map", "map <filename>", "用 map 命令显示文件使用块号", "map filename 显示名为 filename 文件的占用的所有块号");
		break;

	case 18:
		HelpDetail("cd", "cd <dirName>", "用 cd 命令进行位置转移", "cd dirName 移动到 dirName 目录下");
		break;

	case 19:
		HelpDetail("opt", "opt", "用 opt 命令优化当前空间，将文件尽可能连续存放", "opt 优化当前空间");
		break;

	case 20:
		HelpDetail("rec", "rec <name>", "用 rec 命令恢复文件(夹)", "rec name 恢复 name 文件(夹)");
		break;

	case 21:
		HelpDetail("fd", "fd <name>", "用 fd 命令查找文件(夹)", "fd name 查找 name 文件(夹)");
		break;
	}
}
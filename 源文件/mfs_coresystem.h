//
//	mfs_coresystem.h
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	This is the core structures of Mini File System.
//
#pragma once
#ifndef __MFS_CORESYSTEM_H__
#define __MFS_CORESYSTEM_H__
// #define SYSTEM_TEST  // 系统测试时所用的宏定义

///	微型文件系统 (Mini File System)
class MiniFS
{
  private:
	bool mount_flag;				  // 空间打开标记
	MBR mbr;						  // 主引导记录
	FILE *space_fp;					  // 当前空间(文件)指针
	uint_8 *CAB;					  // 簇分配位图
	uint_32 CAB_occupu_byte;		  // CAB占用字节数
	uint_32 *FAT;					  // 文件分配表
	std::vector<Directory> directory; // 文件目录
	char *buffer;					  // 空间输入输出缓冲区

  public:
	MiniFS();
	~MiniFS();

	//	命令解析模块			<mfs_cs_cmd.cpp>
  public:
	int cmd(void);

  private:
	void printFilePath(void);

	//	帮助系统模块			<mfs_cs_help.cpp>
  private:
	void showHelp(int mode = 0);

	//	硬盘读写模块			<mfs_cs_diskio.cpp>
  private:
	void readMBR(void);
	void writeMBR(void) const;
	void readCAB(void);
	void writeCAB(void);
	void readFAT(void);
	void writeFAT(void);
	void readCluster(const uint_32 cluster);
	void writeCluster(const uint_32 cluster);
	Directory readDirectory(const uint_32 dir_entrance) const;
	void rewriteDirectory(const Directory dir);
	void newWriteDirectory(const Directory dir) const;

	//	空间操作模块			<mfs_cs_spaceop.cpp>
  private:
	int createSpace(char name[], uint_32 space_size = 1024, uint_32 cluster_size = 4);
	int mountSpace(char name[]);
	int formatSpace(uint_32 cluster_size = 4);
	int closeSpace(void);

	//  文件操作模块			<mfs_cs_fileop.cpp>
  private:
	int showDirectory(void);
	void treeDirectory(void);
	int occupyCluster(char filename[]);
	int changeDirectory(char filename[]);
	int makeDir(char filename[]);
	int createFile(char filename[]);
	int findFile(char expression[]);
	int copyFile(char filename_1[], char filename_2[]);
	int moveFile(char filename_1[], char filename_2[]);
	int showAttribute(const char filename[]);
	int deleteFile(char filename[]);
	int recoverFile(char filename[]);
	void showRecycleBin(void);
	void emptyRecycleBin(void);
	void optimization(void);

	// 有关递归操作函数
	void treeRecur(uint_32 dir_entrance, std::vector<int> &path);
	void findRecur(char expression[], uint_32 dir_entrance, std::vector<std::string> &path, bool &empty);
	void delRecur(uint_32 dir_entrance);
	void showRBRecur(uint_32 dir_entrance, std::vector<std::string> &path, bool &empty, int mode = 0);
	void emptyRBRecur(uint_32 dir_entrance);

	//  系统测试模块
#ifdef SYSTEM_TEST

  private:
	void Test_createFile(int file_num);

#endif
};

#endif

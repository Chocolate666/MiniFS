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
// #define SYSTEM_TEST  // ϵͳ����ʱ���õĺ궨��

///	΢���ļ�ϵͳ (Mini File System)
class MiniFS
{
  private:
	bool mount_flag;				  // �ռ�򿪱��
	MBR mbr;						  // ��������¼
	FILE *space_fp;					  // ��ǰ�ռ�(�ļ�)ָ��
	uint_8 *CAB;					  // �ط���λͼ
	uint_32 CAB_occupu_byte;		  // CABռ���ֽ���
	uint_32 *FAT;					  // �ļ������
	std::vector<Directory> directory; // �ļ�Ŀ¼
	char *buffer;					  // �ռ��������������

  public:
	MiniFS();
	~MiniFS();

	//	�������ģ��			<mfs_cs_cmd.cpp>
  public:
	int cmd(void);

  private:
	void printFilePath(void);

	//	����ϵͳģ��			<mfs_cs_help.cpp>
  private:
	void showHelp(int mode = 0);

	//	Ӳ�̶�дģ��			<mfs_cs_diskio.cpp>
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

	//	�ռ����ģ��			<mfs_cs_spaceop.cpp>
  private:
	int createSpace(char name[], uint_32 space_size = 1024, uint_32 cluster_size = 4);
	int mountSpace(char name[]);
	int formatSpace(uint_32 cluster_size = 4);
	int closeSpace(void);

	//  �ļ�����ģ��			<mfs_cs_fileop.cpp>
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

	// �йصݹ��������
	void treeRecur(uint_32 dir_entrance, std::vector<int> &path);
	void findRecur(char expression[], uint_32 dir_entrance, std::vector<std::string> &path, bool &empty);
	void delRecur(uint_32 dir_entrance);
	void showRBRecur(uint_32 dir_entrance, std::vector<std::string> &path, bool &empty, int mode = 0);
	void emptyRBRecur(uint_32 dir_entrance);

	//  ϵͳ����ģ��
#ifdef SYSTEM_TEST

  private:
	void Test_createFile(int file_num);

#endif
};

#endif

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
	std::cout << "ָ���ʽ: ";
	std::cout.fill(' ');
	std::cout << cmd_layout << std::endl;
	std::cout.unsetf(std::ios::left);
}

inline void HelpDetail(const char cmd_name[], const char cmd_layout[],
					   const char cmd_content[], const char cmd_example[])
{
	std::cout << " " << cmd_name << std::endl;
	std::cout << " ָ���ʽ: " << cmd_layout << std::endl;
	std::cout << " ָ���: " << cmd_content << std::endl;
	std::cout << " ָ��ʾ��: " << cmd_example << std::endl;
}

void MiniFS::showHelp(int mode)
{
	puts(" ");
	switch (mode)
	{
	case 0:
		HelpOutput(" create ", " �����ռ�", "create <name> [size(��ѡ)]");
		HelpOutput(" mount ", " ��װ�ռ�", "mount <name>");
		HelpOutput(" fmt ", " ��ʽ���ռ�", "fmt [size(��ѡ)]");
		HelpOutput(" close ", " �˳��ռ�", "close");
		HelpOutput(" dr ", " ��ʾĿ¼", "dr");
		HelpOutput(" cp ", " �����ļ�", "cp <name_old> <name_new>");
		HelpOutput(" dl ", " ɾ���ļ�", "dl <name>");
		HelpOutput(" tree ", " ��ʾĿ¼��", "tp <name>");
		HelpOutput(" move ", " �ƶ��ļ�", "more <name1> <name2>");
		HelpOutput(" att ", " ��ʾ�ļ�����", "att <name>");
		HelpOutput(" help ", " ������Ϣ", "help [������(��ѡ)]");
		HelpOutput(" end ", " �˳�����", "end");
		HelpOutput(" mkdir ", " �½��ļ���", "mkdir <dirName>");
		HelpOutput(" touch ", " �½��ļ�", "touch <filename>");
		HelpOutput(" lrb ", " ��ʾ����վ", "lrb");
		HelpOutput(" crb ", " ��ջ���վ", "crb");
		HelpOutput(" map ", " ��ʾ�ļ�ռ�ÿ��", "map <filename>");
		HelpOutput(" cd ", " λ��ת��", "cd dirName");
		HelpOutput(" opt ", " �Ż��ռ�", "opt");
		HelpOutput(" rec ", " �ָ��ļ�(��)", "rec <name>");
		HelpOutput(" fd ", " �����ļ�(��)", "fd <name>");
		break;

	case 1:
		HelpDetail("create", "create <name> [size(��ѡ)]",
				   "�� create �����һ���µ� Mini-FS �ռ�",
				   "create SName ����һ����Ϊ SName ��СΪ 1G �� Windows �ļ���Ϊ�洢�ռ� \n\t  create SName 2048 ����һ����Ϊ SName ��СΪ 2G �� Windows �ļ���Ϊ�洢�ռ�");
		break;

	case 2:
		HelpDetail("mount", "mount <name>", "�� mount ���װҪ�����Ŀռ�",
				   "mount SName �� Mini-FS �а�װ(��)�ռ� SName��Ϊ������������׼��");
		break;

	case 3:
		HelpDetail("fmt", "fmt [size(��ѡ)]", "�� fmt �����ʽ����ǰ�Ŀռ�",
				   "fmt ��ʼ����ǰ�򿪵� SName �ռ䣬�ش�С����Ϊ 4KB \n\t  fmt 8 ��ʼ����ǰ�򿪵� SName �ռ䣬�ش�С����Ϊ 8KB");
		break;

	case 4:
		HelpDetail("close", "close", "�� close �����˳� Mini-FS", "close �˳����ر� Mini-FS ϵͳ");
		break;

	case 5:
		HelpDetail("dr", "dr", "dr ��ʾ��ǰĿ¼�µ��ļ�Ŀ¼", "dr ��ʾ��ǰĿ¼�������ļ����ļ���");
		break;

	case 6:
		HelpDetail("cp", "cp <name1> <name2>", "�� cp ������ļ�",
				   "cp wFName sFName ���ļ��� Windows �ռ��п����� Mini-FS �ռ��� \n\t   cp sFName wFName ���ļ��� Mini-FS �ռ��п����� Windows �ռ��� \n\t   cp sFName1 sFName2 ���ļ��� Mini-FS �ռ��п����� Mini-FS �ռ���");
		break;

	case 7:
		HelpDetail("dl", "dl <name>", "�� dl ����ɾ���ռ��е��ļ�",
				   "dl sFName ���ļ� sFName �ӿռ���ɾ��");
		break;

	case 8:
		HelpDetail("tree", "tree", "�� tree ������ʾĿ¼��", "tree ��ʾĿ¼��");
		break;

	case 9:
		HelpDetail("move", "move <name1> <name2>", "�� move �����ƶ��ļ�",
				   "move name1 name2 �� name1 �ļ��ƶ��� name2");
		break;

	case 10:
		HelpDetail("att", "att <name>", "�� att ������ʾ�ı�����",
				   "att sFName ��ʾ��Ϊ sFName ���ļ����ļ�����(�ļ�������չ��������ʱ�䡢�ļ���С)");
		break;

	case 11:
		HelpDetail("help", "help [������(��ѡ)]", "�� help �����ȡ������Ϣ",
				   "help ��ʾϵͳ���Ƽ����� \n\t   help create ��ʾ create ��ָ���ʽ����ϸ��Ϣ");
		break;

	case 12:
		HelpDetail("end", "end", "�� end �����˳�����", "end �˳�����");
		break;

	case 13:
		HelpDetail("mkdir", "mkdir <dirName>", "�� mkdir �����½��ļ���",
				   "mkdir �½���Ϊ dirName ���ļ���");
		break;

	case 14:
		HelpDetail("touch", "touch <fileName>", "�� touch �����½��ļ�",
				   "touch �½���Ϊ fileName ���ļ�");
		break;

	case 15:
		HelpDetail("lrb", "lrb", "�� lrb ������ʾ����վ����", "lrb ��ʾ����վ����");
		break;

	case 16:
		HelpDetail("crb", "crb", "�� crb ������ջ���վ", "crb ��ջ���վ");
		break;

	case 17:
		HelpDetail("map", "map <filename>", "�� map ������ʾ�ļ�ʹ�ÿ��", "map filename ��ʾ��Ϊ filename �ļ���ռ�õ����п��");
		break;

	case 18:
		HelpDetail("cd", "cd <dirName>", "�� cd �������λ��ת��", "cd dirName �ƶ��� dirName Ŀ¼��");
		break;

	case 19:
		HelpDetail("opt", "opt", "�� opt �����Ż���ǰ�ռ䣬���ļ��������������", "opt �Ż���ǰ�ռ�");
		break;

	case 20:
		HelpDetail("rec", "rec <name>", "�� rec ����ָ��ļ�(��)", "rec name �ָ� name �ļ�(��)");
		break;

	case 21:
		HelpDetail("fd", "fd <name>", "�� fd ��������ļ�(��)", "fd name ���� name �ļ�(��)");
		break;
	}
}
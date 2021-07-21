/**
 *	main.cpp
 *
 *		Copyright (c) 2018 AlphaBeta Team. All rights reserved.
 *
 *	This is application of Mini File System.
 *
 *
 *	Mini File System Project:
 *		Team:		AlphaBeta.
 *		Member:		Linfeng Li, Runbang Xu, Bole Ma, Chi Zhang, Dalin Miao.
 *		Tutor:		Chunxia Zhang, Shuoying Chen.
 *		Company:	School of Computer Science, Beijing Institute of Technology.
 *		Version:	3.2.13 (Release).
 *		Submit:		September 11th, 2018.
 *
**/

#include "mini_file_system.h"

int main(int argc, char *argv[])
{
	MiniFS simulated_disk;
	while (simulated_disk.cmd())
		;
	return 0;
}

//
//	mfs_algorithm.h
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	This is the algorithm library that Mini File System need.
//
#pragma once
#ifndef __MFS_ALGORITHM_H__
#define __MFS_ALGORITHM_H__


/// 微型文件系统算法库
namespace MfsAlg
{
	/// 位操作
			// 位操作: 置位1
	bool	BitSet(uint_8 table[], uint_32 size, uint_32 bit_No);
			// 位操作: 置零
	bool	BitReset(uint_8 table[], uint_32 size, uint_32 bit_No);
			// 位操作: 查找0值位号
	uint_32	BitFindRoom(uint_8 table[], uint_32 size);
			// 位操作: 查找第i位是否为1
	uint_32 BitCheck(uint_8 table[], uint_32 size, uint_32 bit_No);



	/// 计算最小值
	uint_32	Min(const uint_32 x, const uint_32 y, const uint_32 z);


	/// 编辑距离算法
	int		LevenDistance(const std::string source, const std::string target);
	//uint_32	LevenDistance(const char source[], const char target[]);


	/// 分割路径
	void	cutPath(char name[], std::vector<std::string>& path);


	/// 字符串匹配


}











#endif

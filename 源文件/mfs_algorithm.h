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


/// ΢���ļ�ϵͳ�㷨��
namespace MfsAlg
{
	/// λ����
			// λ����: ��λ1
	bool	BitSet(uint_8 table[], uint_32 size, uint_32 bit_No);
			// λ����: ����
	bool	BitReset(uint_8 table[], uint_32 size, uint_32 bit_No);
			// λ����: ����0ֵλ��
	uint_32	BitFindRoom(uint_8 table[], uint_32 size);
			// λ����: ���ҵ�iλ�Ƿ�Ϊ1
	uint_32 BitCheck(uint_8 table[], uint_32 size, uint_32 bit_No);



	/// ������Сֵ
	uint_32	Min(const uint_32 x, const uint_32 y, const uint_32 z);


	/// �༭�����㷨
	int		LevenDistance(const std::string source, const std::string target);
	//uint_32	LevenDistance(const char source[], const char target[]);


	/// �ָ�·��
	void	cutPath(char name[], std::vector<std::string>& path);


	/// �ַ���ƥ��


}











#endif

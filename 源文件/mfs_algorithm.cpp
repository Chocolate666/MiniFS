//
//	mfs_algorithm.cpp
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	This is the implementation of algorithm library.
//

#include "mini_file_system.h"


/// 仅限本文件使用
static const uint_8 set_mask[8]   = {128,  64,  32,  16,   8,   4,   2,   1};
static const uint_8 reset_mask[8] = {127, 191, 223, 239, 247, 251, 253, 254};



/// <summary> 位操作: 置位1 </summary>
/// <param name="table"> 待置位数组 </param>
/// <param name="size"> 数组有效位数目 </param>
/// <param name="bit_no"> 置1的位置 </param>
/// <return> true:置位成功; false:置位失败 </return>
bool MfsAlg::BitSet(uint_8 table[], uint_32 size, uint_32 bit_No)
{
	if (bit_No >= size) {
		return false;
	}
	table[bit_No >> 3] |= set_mask[bit_No & 7];
	return true;
}


/// <summary> 位操作: 置零 </summary>
/// <return> true:置零成功; false:置零失败 </return>
bool MfsAlg::BitReset(uint_8 table[], uint_32 size, uint_32 bit_No)
{
	if (bit_No >= size) {
		return false;
	}
	table[bit_No >> 3] &= reset_mask[bit_No & 7];
	return true;
}


/// <summary> 位操作: 检查某位取值 </summary>
/// <return> 0:该位为0; 1:该位为1; 2:访问越界 </return>
uint_32 MfsAlg::BitCheck(uint_8 table[], uint_32 size, uint_32 bit_No)
{
	if (bit_No >= size) {
		return 2;
	}
	if ((table[bit_No >> 3] & set_mask[bit_No & 7]) != 0){
		return 1;
	}
	else return 0;
}


/// <summary> 位操作: 查找0值位号 </summary>
/// <return> true:置零成功; 0xffffffff:无空位置 </return>
uint_32	MfsAlg::BitFindRoom(uint_8 table[], uint_32 size)
{
	bool flag = false;
	uint_32 bit_No = 0xffffffff;

	uint_32 byte_num = (uint_32)ceil(size / 8.0);
	for (uint_32 i = 0; i < byte_num; i++) {
		if (table[i] == 255) continue;
		for (uint_32 j = 0; j < 8; j++) {
			if ((table[i] & set_mask[j]) == 0) {
				bit_No = i * 8 + j;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}

	if (bit_No >= size) {
		bit_No = 0xffffffff;
	}
	return bit_No;
}


/// <summary> 最小编辑距离算法 </summary>
/// <return> 字符串source与字符串target的最小编辑距离 </return>
int MfsAlg::LevenDistance(const std::string source, const std::string target)
{
	int n = source.length();
	int m = target.length();
	if (m == 0)
		return n;
	if (n == 0)
		return m;

	std::vector<std::vector<int>> matrix(n + 1);
	for (int i = 0; i <= n; i++)
		matrix[i].resize(m + 1);

	for (int i = 1; i <= n; i++)
		matrix[i][0] = i;
	for (int i = 1; i <= m; i++)
		matrix[0][i] = i;

	for (int i = 1; i <= n; i++)
	{
		const char si = source[i - 1];
		for (int j = 1; j <= m; j++)
		{
			const char dj = target[j - 1];
			int cost;
			if (si == dj)
				cost = 0;
			else
				cost = 1;
			const int above = matrix[i - 1][j] + 1;
			const int left = matrix[i][j - 1] + 1;
			const int diag = matrix[i - 1][j - 1] + cost;
			matrix[i][j] = std::min(above, std::min(left, diag));
		}
	}
	return matrix[n][m];
}


/// <summary> 计算x,y,z最小值 </summary>
uint_32 MfsAlg::Min(const uint_32 x, const uint_32 y, const uint_32 z)
{
	uint_32 min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}


/// <summary> 分割路径 </summary>
/// <return> 传入完整路径name[], 依次分割成path向量 </return>
void MfsAlg::cutPath(char name[], std::vector<std::string> &path) {
	std::string cur_path = "";
	int len = strlen(name);
	for (int i = 0; i < len; i++) {
		if (name[i] == '\\' || name[i] == '/') {
			path.push_back(cur_path);
			cur_path.clear();
		}
		else {
			cur_path += name[i];
		}
	}
	if (cur_path.length())
		path.push_back(cur_path);
}
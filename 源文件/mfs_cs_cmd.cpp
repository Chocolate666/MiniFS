//
//	mfs_cs_cmd.cpp
//
//		Copyright (c) AlphaBeta Team. All rights reserved.
//
//	Class MiniFS: This file realizes the external input and output command parsing.
//

#include "mini_file_system.h"
#include <Windows.h>

std::string command_array[] = {"create", "mount", "fmt", "dr", "cp", "dl", "att", "help", "close", "end", "mkdir", "tree", "move", "lrb", "crb", "map", "cd", "touch", "opt", "rec", "fd"};
int command_distance[21];

void MiniFS::printFilePath(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 粉色
    printf("\nMini-FS:");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    std::vector<Directory>::iterator iter;
    for (iter = directory.begin(); iter != directory.end(); iter++)
        printf("\\%s", (*iter).header.name);
    putchar('>');
}

int MiniFS::cmd(void)
{
    this->printFilePath();
    char delim = ' ';
    std::string input_temp = "";
    std::string command_input = "";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    // 每次只读取一行命令，多次输入由外界循环控制
    std::getline(std::cin, command_input);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY);

    // 防止空输入
    if ((command_input[0] == ' ' && command_input.length() == 1) || command_input.length() < 1)
        return 1;

    // 去除多余的空格
    bool space_flag = true;
    for (int i = 0; i < (int)command_input.length(); i++)
    {
        if (command_input[i] == ' ')
        {
            if (space_flag)
                input_temp += command_input[i];
            space_flag = false;
        }
        else
        {
            space_flag = true;
            input_temp += command_input[i];
        }
    }
    if (input_temp[0] == ' ')
        command_input = input_temp.substr(1);
    else
        command_input = input_temp;

    // 防止空输入
    if ((command_input[0] == ' ' && command_input.length() == 1) || command_input.length() < 1)
        return 1;

    // 按空格 ' ' 切分输入的一行字符串
    std::vector<std::string> command_vector;
    command_vector.clear();
    std::istringstream iss(command_input);
    std::string temp;

    while (std::getline(iss, temp, delim))
        command_vector.emplace_back(std::move(temp));

    int command_num = command_vector.size();
    std::string command = command_vector[0];

    // example: create space_name; space_name 可以包含路径   ok
    if (command == "create")
    {
        int re; // 接收函数返回值

        if (command_num == 2)
        {
            re = this->createSpace((char *)command_vector[1].data(), (uint_32)1024, (uint_32)4);
        }
        else if (command_num == 3)
        {
            std::regex reg_pattern_space_size("^\\+?[1-9][0-9]*$"); // 空间大小必须为非0整数
            if (!std::regex_match(command_vector[2], reg_pattern_space_size))
            {
                std::cout << " " << command_vector[2] << " 不是非零整数!" << std::endl;
                return 1;
            }

            int space_size = atoi((char *)command_vector[2].data());
            if (space_size < 64 || space_size > 4194304)
            {
                std::cout << " " << command_vector[2] << " 不能小于 64 或大于 4194304!" << std::endl;
                return 1;
            }

            re = this->createSpace((char *)command_vector[1].data(), (uint_32)space_size, 4);
        }
        else if (command_num == 4)
        {
            int f_pos = 0, f_size_pos = 0;
            for (int i = 1; i < 4; i++)
            {
                if (command_vector[i] == "-f")
                {
                    f_pos = i;
                    f_size_pos = i + 1;
                    break;
                }
            }

            if (f_pos == f_size_pos || f_pos == 3) // -f参数必须出现且不可能是最后一个
            {
                std::cout << " 参数错误!" << std::endl;
                return 1;
            }

            std::regex reg_pattern_cluster_size("^\\+?[1-9][0-9]*$");
            if (!std::regex_match(command_vector[f_size_pos], reg_pattern_cluster_size))
            {
                std::cout << " " << command_vector[f_size_pos] << " 不是非零整数!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[f_size_pos].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[f_size_pos] << " 不是建议参数!(应{x|1<=x<=64 且 x为2的幂次方})" << std::endl;
                return 1;
            }

            int file_pos = 1 ^ 2 ^ 3 ^ f_pos ^ f_size_pos;
            re = this->createSpace((char *)command_vector[file_pos].data(), (uint_32)1024, (uint_32)cluster_size);
        }
        else if (command_num == 5)
        {
            int f_pos = 0, f_size_pos = 0;
            for (int i = 1; i < 5; i++)
            {
                if (command_vector[i] == "-f")
                {
                    f_pos = i;
                    f_size_pos = i + 1;
                    break;
                }
            }

            if (f_pos == 1 || f_pos == 4 || f_pos == f_size_pos) // 5参数下，空间名默认在第二位
            {
                std::cout << " 参数错误!" << std::endl;
                return 1;
            }

            std::regex reg_pattern_cluster_size("^\\+?[1-9][0-9]*$");
            if (!std::regex_match(command_vector[f_size_pos], reg_pattern_cluster_size))
            {
                std::cout << " " << command_vector[f_size_pos] << " 不是非零整数!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[f_size_pos].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[f_size_pos] << " 不是建议参数!(应{x|1<=x<=64 且 x为2的幂次方})" << std::endl;
                return 1;
            }

            int space_size_pos = 2 ^ 3 ^ 4 ^ f_pos ^ f_size_pos;
            std::regex reg_pattern_space_size("^\\+?[1-9][0-9]*$"); // 空间大小必须为非0整数
            if (!std::regex_match(command_vector[space_size_pos], reg_pattern_space_size))
            {
                std::cout << " " << command_vector[space_size_pos] << " 不是非零整数!" << std::endl;
                return 1;
            }

            int space_size = atoi((char *)command_vector[space_size_pos].data());
            if (space_size < 64 || space_size > 4194304)
            {
                std::cout << " " << command_vector[space_size_pos] << " 不能小于 64 或大于 4194304!" << std::endl;
                return 1;
            }

            re = this->createSpace((char *)command_vector[1].data(), (uint_32)space_size, (uint_32)cluster_size);
        }
        else
        {
            std::cout << " " << command << " 参数错误!" << std::endl;
            return 1;
        }

        switch (re)
        {
        case 1:
            std::cout << " 空间创建成功!" << std::endl;
            break;
        case -1:
            std::cout << " 空间路径错误!" << std::endl;
            break;
        case -2:
            std::cout << " 空间名长度超限!" << std::endl;
            break;
        case -3:
            std::cout << " 空间名重复!" << std::endl;
            break;
        default:
            std::wcout << " 出现未知错误!" << std::endl;
            break;
        }
    }

    // example: mount space_name; space_name 可以包含路径 ok
    else if (command == "mount")
    {
        if (this->mount_flag)
        {
            std::cout << " 当前已经打开一个空间!" << std::endl;
            return 1;
        }

        if (command_num == 2)
        {
            std::ifstream ifs(command_vector[1].c_str());
            if (ifs)
            {
                if (this->mountSpace((char *)command_vector[1].data()) != 1)
                    std::cout << " " << command_vector[1] << " 打开失败!" << std::endl;
                else
                    this->mount_flag = true;
            }
            else
                std::cout << " " << command_vector[1] << " 不存在此路径!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: dr; 显示当前文件夹下的文件目录  ok
    else if (command == "dr")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->showDirectory();
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: cp filename_old filename_new;  ok
    // 有从外部系统->Mini-FS、Mini-FS->外部系统、Mini-FS->Mini-FS三种情况
    else if (command == "cp")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 3)
        {
            if (this->copyFile((char *)command_vector[1].data(), (char *)command_vector[2].data()) != 1)
                std::cout << " 路径不存在!" << std::endl;
            else
                std::cout << " 成功拷贝文件!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: dl filename; 删除空间中的文件  ok
    else if (command == "dl")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->deleteFile((char *)command_vector[1].data()) != 1)
                std::cout << " 删除文件失败!" << std::endl;
            else
                std::cout << " 成功删除文件!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: att filename; 显示文件属性  ok
    else if (command == "att")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            if (this->showAttribute(".") != 1)
                std::cout << " 无此文件!" << std::endl;
        }
        else if (command_num == 2)
        {
            if (this->showAttribute((char *)command_vector[1].data()) != 1)
                std::cout << " 无此文件!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: help [命令名(可选)];   ok
    else if (command == "help")
    {
        if (command_num == 1)
        {
            this->showHelp(0);
        }
        else if (command_num == 2)
        {
            if (command_vector[1] == "create")
                this->showHelp(1);
            else if (command_vector[1] == "mount")
                this->showHelp(2);
            else if (command_vector[1] == "fmt")
                this->showHelp(3);
            else if (command_vector[1] == "close")
                this->showHelp(4);
            else if (command_vector[1] == "dr")
                this->showHelp(5);
            else if (command_vector[1] == "cp")
                this->showHelp(6);
            else if (command_vector[1] == "dl")
                this->showHelp(7);
            else if (command_vector[1] == "tree")
                this->showHelp(8);
            else if (command_vector[1] == "move")
                this->showHelp(9);
            else if (command_vector[1] == "att")
                this->showHelp(10);
            else if (command_vector[1] == "help")
                this->showHelp(11);
            else if (command_vector[1] == "end")
                this->showHelp(12);
            else if (command_vector[1] == "mkdir")
                this->showHelp(13);
            else if (command_vector[1] == "touch")
                this->showHelp(14);
            else if (command_vector[1] == "lrb")
                this->showHelp(15);
            else if (command_vector[1] == "crb")
                this->showHelp(16);
            else if (command_vector[1] == "map")
                this->showHelp(17);
            else if (command_vector[1] == "cd")
                this->showHelp(18);
            else if (command_vector[1] == "opt")
                this->showHelp(19);
            else if (command_vector[1] == "rec")
                this->showHelp(20);
            else if (command_vector[1] == "fd")
                this->showHelp(21);
            else
                std::cout << command_vector[1] << " 不是一个正确的命令名称!" << std::endl;
        }
        else
            std::cout << command << " 参数错误!" << std::endl;
    }

    // example: close;  关闭当前空间  ok
    else if (command == "close")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            this->closeSpace(); // 需要做一些回写操作
            this->mount_flag = false;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: fmt [size(可选)]; 格式化当前空间  ok
    else if (command == "fmt")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }

        if (command_num == 1)
        {
            this->formatSpace(); // 默认为 4
            std::cout << " 格式化成功!" << std::endl;
        }
        else if (command_num == 2)
        {
            std::regex reg_pattern_size("^\\+?[1-9][0-9]*$"); // 非0整数
            if (!std::regex_match(command_vector[1], reg_pattern_size))
            {
                std::cout << " " << command_vector[1] << " 不是非零整数!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[1].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[1] << " 不是建议参数!(应{x|1<=x<=64 且 x为2的幂次方})" << std::endl;
                return 1;
            }

            this->formatSpace((uint_32)cluster_size);
            std::cout << " 格式化成功!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: end; 退出程序  ok
    else if (command == "end")
    {
        if (command_num == 1)
            return 0;
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: mkdir <name>; 创建名为 name 文件夹  ok
    else if (command == "mkdir")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (command_vector[1].length() > 8)
            {
                std::cout << " 创建" << command_vector[1] << " 失败，文件夹名称过长!" << std::endl;
                return 1;
            }

            if (this->makeDir((char *)command_vector[1].data()) == -1)
                std::cout << " " << command_vector[1] << " 文件夹重名!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: cd <dirname>; 移动到 dirname 文件夹  ok
    else if (command == "cd")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->changeDirectory((char *)command_vector[1].data()) != 1)
                std::cout << " " << command_vector[1] << " 不存在!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: touch filename; 创建 filename 文件  ok
    else if (command == "touch")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (command_vector[1].length() > 12)
            {
                std::cout << " 创建" << command_vector[1] << " 失败，文件名称过长!" << std::endl;
                return 1;
            }

            if (this->createFile((char *)command_vector[1].data()) == -1)
                std::cout << " " << command_vector[1] << " 文件重名!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: tree; 打印目录树   ok
    else if (command == "tree")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->treeDirectory();
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: lrb; 显示回收站  ok
    else if (command == "lrb")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->showRecycleBin();
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: crb; 清空回收站  ok
    else if (command == "crb")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }

        if (command_num == 1)
        {
            this->emptyRecycleBin();
            std::cout << " 回收站清空完毕!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: map; 查看文件使用块号  ok
    else if (command == "map")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->occupyCluster((char *)command_vector[1].data()) != 1)
                std::cout << " 查找文件失败!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: opt; 优化空间
    else if (command == "opt")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            this->optimization();
            std::cout << "\n" << " 磁盘整理完成!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: move; 移动文件(夹)  ok
    else if (command == "move")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 3)
        {
            int re = this->moveFile((char *)command_vector[1].data(),
                (char *)command_vector[2].data());

            switch (re)
            {
            case 1:
                std::cout << " 移动成功!" << std::endl;
                break;
            case -1:
                std::cout << " 当前在被移动文件内!" << std::endl;
                break;
            case -2:
                std::cout << " 移动失败!" << std::endl;
                break;
            default:
                break;
            }
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: rec <name>; 恢复文件(夹)
    else if (command == "rec")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->recoverFile((char *)command_vector[1].data()) != 1)
                std::cout << " 无此文件!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

    // example: fd <name>; 查找文件
    else if (command == "fd")
    {
        if (!this->mount_flag)
        {
            std::cout << " 当前没有打开空间!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->findFile((char *)command_vector[1].data()) != 1)
                std::cout << " " << command_vector[1] << " 不存在!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }

#ifdef SYSTEM_TEST
    // 专用于系统测试时进行一些自动化操作
    else if (command == "TEST")
    {
        if (command_num == 3)
        {
            if (command_vector[1] == "touch")  // 测试 touch 命令
            {
                if (!this->mount_flag)
                {
                    std::cout << " 当前没有打开空间!" << std::endl;
                    return 1;
                }
                std::regex reg_pattern_test_num("^\\+?[1-9][0-9]*$");
                if (!std::regex_match(command_vector[2], reg_pattern_test_num))
                {
                    std::cout << " " << command_vector[2] << " 不是非零整数!" << std::endl;
                    return 1;
                }
                int test_num = atoi((char *)command_vector[2].data());
                this->Test_createFile(test_num);
            }
            else
                std::cout << " " << command_vector[1] << " 无此命令的测试!" << std::endl;
        }
        else
            std::cout << " " << command << " 参数错误!" << std::endl;
    }
#endif
  
    else
    {
        std::cout << " " << command << " 不是一个正确的命令!" << std::endl;
        bool if_dis = false;
        for (int i = 0; i < 21; i++)
        {
            command_distance[i] = MfsAlg::LevenDistance(command, command_array[i]);
            if (command_distance[i] < 3)
                if_dis = true;
        }
        if (!if_dis)
            return 1;
        std::cout << " 您是想输入 ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        bool dis_flag = false;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (command_distance[j] == i)
                {
                    std::cout << command_array[j] << " ";
                    if (i <= 1)
                        dis_flag = true;
                }
            }
            if (dis_flag)
                break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY);
        std::cout << "命令吗?" << std::endl;
    }

    return 1;
}
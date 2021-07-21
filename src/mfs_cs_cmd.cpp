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
                            FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ��ɫ
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
    // ÿ��ֻ��ȡһ�����������������ѭ������
    std::getline(std::cin, command_input);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY);

    // ��ֹ������
    if ((command_input[0] == ' ' && command_input.length() == 1) || command_input.length() < 1)
        return 1;

    // ȥ������Ŀո�
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

    // ��ֹ������
    if ((command_input[0] == ' ' && command_input.length() == 1) || command_input.length() < 1)
        return 1;

    // ���ո� ' ' �з������һ���ַ���
    std::vector<std::string> command_vector;
    command_vector.clear();
    std::istringstream iss(command_input);
    std::string temp;

    while (std::getline(iss, temp, delim))
        command_vector.emplace_back(std::move(temp));

    int command_num = command_vector.size();
    std::string command = command_vector[0];

    // example: create space_name; space_name ���԰���·��   ok
    if (command == "create")
    {
        int re; // ���պ�������ֵ

        if (command_num == 2)
        {
            re = this->createSpace((char *)command_vector[1].data(), (uint_32)1024, (uint_32)4);
        }
        else if (command_num == 3)
        {
            std::regex reg_pattern_space_size("^\\+?[1-9][0-9]*$"); // �ռ��С����Ϊ��0����
            if (!std::regex_match(command_vector[2], reg_pattern_space_size))
            {
                std::cout << " " << command_vector[2] << " ���Ƿ�������!" << std::endl;
                return 1;
            }

            int space_size = atoi((char *)command_vector[2].data());
            if (space_size < 64 || space_size > 4194304)
            {
                std::cout << " " << command_vector[2] << " ����С�� 64 ����� 4194304!" << std::endl;
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

            if (f_pos == f_size_pos || f_pos == 3) // -f������������Ҳ����������һ��
            {
                std::cout << " ��������!" << std::endl;
                return 1;
            }

            std::regex reg_pattern_cluster_size("^\\+?[1-9][0-9]*$");
            if (!std::regex_match(command_vector[f_size_pos], reg_pattern_cluster_size))
            {
                std::cout << " " << command_vector[f_size_pos] << " ���Ƿ�������!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[f_size_pos].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[f_size_pos] << " ���ǽ������!(Ӧ{x|1<=x<=64 �� xΪ2���ݴη�})" << std::endl;
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

            if (f_pos == 1 || f_pos == 4 || f_pos == f_size_pos) // 5�����£��ռ���Ĭ���ڵڶ�λ
            {
                std::cout << " ��������!" << std::endl;
                return 1;
            }

            std::regex reg_pattern_cluster_size("^\\+?[1-9][0-9]*$");
            if (!std::regex_match(command_vector[f_size_pos], reg_pattern_cluster_size))
            {
                std::cout << " " << command_vector[f_size_pos] << " ���Ƿ�������!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[f_size_pos].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[f_size_pos] << " ���ǽ������!(Ӧ{x|1<=x<=64 �� xΪ2���ݴη�})" << std::endl;
                return 1;
            }

            int space_size_pos = 2 ^ 3 ^ 4 ^ f_pos ^ f_size_pos;
            std::regex reg_pattern_space_size("^\\+?[1-9][0-9]*$"); // �ռ��С����Ϊ��0����
            if (!std::regex_match(command_vector[space_size_pos], reg_pattern_space_size))
            {
                std::cout << " " << command_vector[space_size_pos] << " ���Ƿ�������!" << std::endl;
                return 1;
            }

            int space_size = atoi((char *)command_vector[space_size_pos].data());
            if (space_size < 64 || space_size > 4194304)
            {
                std::cout << " " << command_vector[space_size_pos] << " ����С�� 64 ����� 4194304!" << std::endl;
                return 1;
            }

            re = this->createSpace((char *)command_vector[1].data(), (uint_32)space_size, (uint_32)cluster_size);
        }
        else
        {
            std::cout << " " << command << " ��������!" << std::endl;
            return 1;
        }

        switch (re)
        {
        case 1:
            std::cout << " �ռ䴴���ɹ�!" << std::endl;
            break;
        case -1:
            std::cout << " �ռ�·������!" << std::endl;
            break;
        case -2:
            std::cout << " �ռ������ȳ���!" << std::endl;
            break;
        case -3:
            std::cout << " �ռ����ظ�!" << std::endl;
            break;
        default:
            std::wcout << " ����δ֪����!" << std::endl;
            break;
        }
    }

    // example: mount space_name; space_name ���԰���·�� ok
    else if (command == "mount")
    {
        if (this->mount_flag)
        {
            std::cout << " ��ǰ�Ѿ���һ���ռ�!" << std::endl;
            return 1;
        }

        if (command_num == 2)
        {
            std::ifstream ifs(command_vector[1].c_str());
            if (ifs)
            {
                if (this->mountSpace((char *)command_vector[1].data()) != 1)
                    std::cout << " " << command_vector[1] << " ��ʧ��!" << std::endl;
                else
                    this->mount_flag = true;
            }
            else
                std::cout << " " << command_vector[1] << " �����ڴ�·��!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: dr; ��ʾ��ǰ�ļ����µ��ļ�Ŀ¼  ok
    else if (command == "dr")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->showDirectory();
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: cp filename_old filename_new;  ok
    // �д��ⲿϵͳ->Mini-FS��Mini-FS->�ⲿϵͳ��Mini-FS->Mini-FS�������
    else if (command == "cp")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 3)
        {
            if (this->copyFile((char *)command_vector[1].data(), (char *)command_vector[2].data()) != 1)
                std::cout << " ·��������!" << std::endl;
            else
                std::cout << " �ɹ������ļ�!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: dl filename; ɾ���ռ��е��ļ�  ok
    else if (command == "dl")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->deleteFile((char *)command_vector[1].data()) != 1)
                std::cout << " ɾ���ļ�ʧ��!" << std::endl;
            else
                std::cout << " �ɹ�ɾ���ļ�!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: att filename; ��ʾ�ļ�����  ok
    else if (command == "att")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            if (this->showAttribute(".") != 1)
                std::cout << " �޴��ļ�!" << std::endl;
        }
        else if (command_num == 2)
        {
            if (this->showAttribute((char *)command_vector[1].data()) != 1)
                std::cout << " �޴��ļ�!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: help [������(��ѡ)];   ok
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
                std::cout << command_vector[1] << " ����һ����ȷ����������!" << std::endl;
        }
        else
            std::cout << command << " ��������!" << std::endl;
    }

    // example: close;  �رյ�ǰ�ռ�  ok
    else if (command == "close")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            this->closeSpace(); // ��Ҫ��һЩ��д����
            this->mount_flag = false;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: fmt [size(��ѡ)]; ��ʽ����ǰ�ռ�  ok
    else if (command == "fmt")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }

        if (command_num == 1)
        {
            this->formatSpace(); // Ĭ��Ϊ 4
            std::cout << " ��ʽ���ɹ�!" << std::endl;
        }
        else if (command_num == 2)
        {
            std::regex reg_pattern_size("^\\+?[1-9][0-9]*$"); // ��0����
            if (!std::regex_match(command_vector[1], reg_pattern_size))
            {
                std::cout << " " << command_vector[1] << " ���Ƿ�������!" << std::endl;
                return 1;
            }

            int cluster_size = atoi((char *)command_vector[1].data());
            if ((cluster_size & (cluster_size - 1)) || cluster_size > 64)
            {
                std::cout << " " << command_vector[1] << " ���ǽ������!(Ӧ{x|1<=x<=64 �� xΪ2���ݴη�})" << std::endl;
                return 1;
            }

            this->formatSpace((uint_32)cluster_size);
            std::cout << " ��ʽ���ɹ�!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: end; �˳�����  ok
    else if (command == "end")
    {
        if (command_num == 1)
            return 0;
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: mkdir <name>; ������Ϊ name �ļ���  ok
    else if (command == "mkdir")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (command_vector[1].length() > 8)
            {
                std::cout << " ����" << command_vector[1] << " ʧ�ܣ��ļ������ƹ���!" << std::endl;
                return 1;
            }

            if (this->makeDir((char *)command_vector[1].data()) == -1)
                std::cout << " " << command_vector[1] << " �ļ�������!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: cd <dirname>; �ƶ��� dirname �ļ���  ok
    else if (command == "cd")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->changeDirectory((char *)command_vector[1].data()) != 1)
                std::cout << " " << command_vector[1] << " ������!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: touch filename; ���� filename �ļ�  ok
    else if (command == "touch")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (command_vector[1].length() > 12)
            {
                std::cout << " ����" << command_vector[1] << " ʧ�ܣ��ļ����ƹ���!" << std::endl;
                return 1;
            }

            if (this->createFile((char *)command_vector[1].data()) == -1)
                std::cout << " " << command_vector[1] << " �ļ�����!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: tree; ��ӡĿ¼��   ok
    else if (command == "tree")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->treeDirectory();
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: lrb; ��ʾ����վ  ok
    else if (command == "lrb")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
            this->showRecycleBin();
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: crb; ��ջ���վ  ok
    else if (command == "crb")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }

        if (command_num == 1)
        {
            this->emptyRecycleBin();
            std::cout << " ����վ������!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: map; �鿴�ļ�ʹ�ÿ��  ok
    else if (command == "map")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->occupyCluster((char *)command_vector[1].data()) != 1)
                std::cout << " �����ļ�ʧ��!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: opt; �Ż��ռ�
    else if (command == "opt")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 1)
        {
            this->optimization();
            std::cout << "\n" << " �����������!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: move; �ƶ��ļ�(��)  ok
    else if (command == "move")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 3)
        {
            int re = this->moveFile((char *)command_vector[1].data(),
                (char *)command_vector[2].data());

            switch (re)
            {
            case 1:
                std::cout << " �ƶ��ɹ�!" << std::endl;
                break;
            case -1:
                std::cout << " ��ǰ�ڱ��ƶ��ļ���!" << std::endl;
                break;
            case -2:
                std::cout << " �ƶ�ʧ��!" << std::endl;
                break;
            default:
                break;
            }
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: rec <name>; �ָ��ļ�(��)
    else if (command == "rec")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->recoverFile((char *)command_vector[1].data()) != 1)
                std::cout << " �޴��ļ�!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

    // example: fd <name>; �����ļ�
    else if (command == "fd")
    {
        if (!this->mount_flag)
        {
            std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
            return 1;
        }
        if (command_num == 2)
        {
            if (this->findFile((char *)command_vector[1].data()) != 1)
                std::cout << " " << command_vector[1] << " ������!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }

#ifdef SYSTEM_TEST
    // ר����ϵͳ����ʱ����һЩ�Զ�������
    else if (command == "TEST")
    {
        if (command_num == 3)
        {
            if (command_vector[1] == "touch")  // ���� touch ����
            {
                if (!this->mount_flag)
                {
                    std::cout << " ��ǰû�д򿪿ռ�!" << std::endl;
                    return 1;
                }
                std::regex reg_pattern_test_num("^\\+?[1-9][0-9]*$");
                if (!std::regex_match(command_vector[2], reg_pattern_test_num))
                {
                    std::cout << " " << command_vector[2] << " ���Ƿ�������!" << std::endl;
                    return 1;
                }
                int test_num = atoi((char *)command_vector[2].data());
                this->Test_createFile(test_num);
            }
            else
                std::cout << " " << command_vector[1] << " �޴�����Ĳ���!" << std::endl;
        }
        else
            std::cout << " " << command << " ��������!" << std::endl;
    }
#endif
  
    else
    {
        std::cout << " " << command << " ����һ����ȷ������!" << std::endl;
        bool if_dis = false;
        for (int i = 0; i < 21; i++)
        {
            command_distance[i] = MfsAlg::LevenDistance(command, command_array[i]);
            if (command_distance[i] < 3)
                if_dis = true;
        }
        if (!if_dis)
            return 1;
        std::cout << " ���������� ";
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
        std::cout << "������?" << std::endl;
    }

    return 1;
}
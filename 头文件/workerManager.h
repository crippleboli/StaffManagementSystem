//
// Created by Macbook on 2025/12/12.
//

#ifndef STAFFMANAGEMENTSYSTEM_WORKERMANAGER_H
#define STAFFMANAGEMENTSYSTEM_WORKERMANAGER_H

#include "iostream"
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"
using namespace std;

#include "fstream"
#define FILENAME "../empFile.txt"

class WorkerManager {
public:
    WorkerManager();     // 构造函数

    ~WorkerManager();    // 析构函数

    void Show_Menu();    // 展示菜单函数

    void ExitSystem();   // 退出系统

    int m_EmpNum;        // 记录职工人数

    Worker ** m_EmpArray;// 职工数组指针  数组中放的是指针

    void save();          // 保存文件

    void Add_Emp();        // 添加职工

    void init_Emp();       // 根据文件已有数据初始化运行时的员工数组

    bool m_FileIsEmpty;    // 用于判断文件是否为空

    int  get_EmpNum();     // 记录文件中的人数

    void show_Emp();       // 显示职工

    void Del_Emp();        // 按职工编号删除职工

    int IsExist(int id);   // 记录指定职工编号的职工是否存在 返回数组位置

    void Mod_Emp();        // 修改职工

    void Find_Emp();       // 查找职工

    void Sort_Emp();       // 按照序号进行排序

    void Clean_File();     // 清空文件
};

#endif //STAFFMANAGEMENTSYSTEM_WORKERMANAGER_H
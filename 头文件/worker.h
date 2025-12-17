//
// Created by Macbook on 2025/12/12.
//

#ifndef STAFFMANAGEMENTSYSTEM_WORKER_H
#define STAFFMANAGEMENTSYSTEM_WORKER_H
#include "iostream"
using namespace std;

class Worker {
public:

    // 显示个人信息
    virtual void showInfo() =0;
    // 获取岗位名称
    virtual string getDeptName() =0;

    // 析构函数
    virtual ~Worker() {}

    int m_Id;           // 职工编号
    string m_Name;      // 职工姓名
    int m_Dept;         // 部门编号
};

#endif //STAFFMANAGEMENTSYSTEM_WORKER_H
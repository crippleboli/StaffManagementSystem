//
// Created by Macbook on 2025/12/12.
//

#ifndef STAFFMANAGEMENTSYSTEM_EMPLOYEE_H
#define STAFFMANAGEMENTSYSTEM_EMPLOYEE_H
#include "iostream"
#include "worker.h"
using namespace std;

class Employee:public Worker {
public:
    // 有参构造函数
    Employee(int id, string name, int dId);
    // 显示个人信息  重写 virtual写不写不影响
    virtual void showInfo();
    // 获取岗位名称
    virtual string getDeptName();
};

#endif //STAFFMANAGEMENTSYSTEM_EMPLOYEE_H
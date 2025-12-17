//
// Created by Macbook on 2025/12/15.
//

#include "../头文件/manager.h"

// 有参构造函数
Manager::Manager(int id,string name, int dId) {
    this->m_Id = id;
    this->m_Name =name;
    this->m_Dept =dId;
}

// 显示职工信息
void Manager::showInfo() {
    cout<<"职工编号："<<this->m_Id
    <<"\t职工姓名："<<this->m_Name
    <<"\t岗位："<<this->getDeptName()
    <<"\t岗位职责：完成老板交给的任务,并向普通员工下发任务"<<endl;
}

// 显示部门信息
string Manager::getDeptName() {
    return "经理";
}



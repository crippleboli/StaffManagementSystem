#include "iostream"
using namespace std;
#include "../头文件/workerManager.h"
#include "../头文件/worker.h"
#include "../头文件/employee.h"
#include "../头文件/manager.h"
#include "../头文件/boss.h"

int main() {

    // Worker *worker =NULL;
    //
    // worker = new Manager(2,"jack",2);
    // worker->showInfo();
    // delete worker;
    //
    // worker = new Employee(1,"tom",1);
    // worker->showInfo();
    // delete worker;
    //
    // worker = new Boss(3,"jerry",3);
    // worker->showInfo();
    // delete worker;

    // 实例化管理者对象
    WorkerManager wm;
    int choice;  // 用户选择选项

    while (1) {
        // 调用展示菜单成员函数
        wm.Show_Menu();

        cout<<"请输入您的选择："<<endl;
        cin>>choice;

        switch (choice) {
            case 0:  // 退出系统
                wm.ExitSystem();
                break;
            case 1:  // 增加职工
                wm.Add_Emp();
                break;
            case 2:  // 显示职工
                wm.show_Emp();
                break;
            case 3:  // 删除职工
                wm.Del_Emp();
                break;
            case 4:  // 修改职工
                wm.Mod_Emp();
                break;
            case 5:  // 查找职工
                wm.Find_Emp();
                break;
            case 6:  // 职工排序
                wm.Sort_Emp();
                break;
            case 7:  // 清空文件
                wm.Clean_File();
                break;
            default:
                break;
        }
    }





    return 0;
}
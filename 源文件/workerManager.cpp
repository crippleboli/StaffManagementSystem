#include "../头文件/workerManager.h"



WorkerManager::WorkerManager() {

    ifstream ifs;
    ifs.open(FILENAME,ios::in); // 读文件

    // 1.文件不存在
    if (!ifs.is_open()) {
        //cout<<"文件不存在！"<<endl;
        // 初始化属性
        // 初始化记录人数
        this->m_EmpNum =0;
        // 初始化数组指针
        this->m_EmpArray =NULL;
        // 初始化判断文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 2.文件存在但为空
    char ch;
    ifs>>ch;
    if (ifs.eof()) {
        // 文件为空
        //cout<<"文件为空！"<<endl;
        // 初始化记录人数
        this->m_EmpNum =0;
        // 初始化数组指针
        this->m_EmpArray =NULL;
        // 初始化判断文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 3.文件存在且有数据
    int num =this->get_EmpNum();
    //cout << "职工人数为："<<num<<endl;
    // 初始化记录人数
    this->m_EmpNum =num;
    // 开辟指针数组空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    // 初识化指针数组
    this->init_Emp();
    // 初始化判断文件标志为不空
    this->m_FileIsEmpty = false;

    // for (int i=0;i<this->m_EmpNum;i++) {
    //     cout<<"职工编号："<<this->m_EmpArray[i]->m_Id<<" "
    //     <<"职工姓名："<<this->m_EmpArray[i]->m_Name<<" "
    //     <<"部门编号："<<this->m_EmpArray[i]->m_Dept<<endl;
    // }

}


void WorkerManager::Show_Menu() {
    cout <<"*********************"<<endl;
    cout << "**欢迎使用职工管理系统**"<<endl;
    cout << "*****1.增加职工信息*****"<<endl;
    cout << "*****2.显示职工信息*****"<<endl;
    cout << "*****3.删除离职职工*****"<<endl;
    cout << "*****4.修改职工信息*****"<<endl;
    cout << "*****5.查找职工信息*****"<<endl;
    cout << "*****6.按照编号排序*****"<<endl;
    cout << "*****7.清空所有文档*****"<<endl;
    cout << "*****0.退出管理程序*****"<<endl;
    cout <<"*********************"<<endl;
}

void WorkerManager::ExitSystem() {
    cout<<"欢迎下次使用"<<endl;
    exit(0);
}

void WorkerManager::Add_Emp() {
    cout<<"请输入添加职工数量："<<endl;
    int addNum; //记录用户的输入数量
    cin>>addNum;

    if (addNum>0) {

        int newSize = this->m_EmpNum +addNum; //新空间人数

        // 开辟新空间
        Worker ** newSpace = new Worker*[newSize];

        // 原来空间下的数据移动到新的空间
        if (this->m_EmpArray!= NULL) {  // 原来的指针数组不空时进行移动
                for (int i =0;i<this->m_EmpNum;i++) {
                    newSpace[i]=this->m_EmpArray[i];
                }
        }

        // 新的空间处添加新的数据
        for (int i=0;i<addNum;i++) {
            int id;         // 职工编号
            string name;    // 职工姓名
            int dSelect;    // 部门选择

            cout<< "请输入第"<<i+1<<"个新职工编号："<<endl;
            cin>>id;
            cout<< "请输入第"<<i+1<<"个新职工姓名："<<endl;
            cin>>name;
            cout<< "请选择该职工岗位："<<endl;
            cout<< "1.普通职工"<<endl;
            cout<< "2.经理"<<endl;
            cout<< "3.老板"<<endl;
            cin>>dSelect;

            Worker *worker =NULL;
            switch (dSelect) {
                case 1:
                    worker =new Employee(id,name,1);
                    break;
                case 2:
                    worker =new Manager(id,name,2);
                    break;
                case 3:
                    worker = new Boss(id,name,3);
                    break;
                default:
                    break;
            }

            // 职工指针保存至数组
            newSpace[this->m_EmpNum + i] = worker;
        }

        // 释放原来的存储指针的数组
        delete[] this->m_EmpArray;
        // 更新新的空间指向
        this->m_EmpArray =newSpace;
        // 更新新的职工人数
        this->m_EmpNum = newSize;
        // 更新职工文件不为空
        this->m_FileIsEmpty =false;
        // 成功添加后 保存至文件
        this->save();
        // 提示添加成功
        cout<<"成功添加"<<addNum<<"名新职工!"<<endl;
    }else {
        cout<<"输入数据有误！"<<endl;
    }

}


WorkerManager::~WorkerManager() {
        if (this->m_EmpArray!= NULL) {
            for (int i=0;i<this->m_EmpNum;i++) {
                if (this->m_EmpArray[i] !=NULL) {
                    delete this->m_EmpArray[i];
                }
            }

            delete[] this->m_EmpArray;
            this->m_EmpArray =NULL;
        }
}


void WorkerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME,ios::out); // 输出方式/写文件
    for (int i=0;i<this->m_EmpNum;i++) {
        ofs<<this->m_EmpArray[i]->m_Id<<" "
            <<this->m_EmpArray[i]->m_Name<<" "
            <<this->m_EmpArray[i]->m_Dept<<endl;
    }
    ofs.close();
}

// 统计文件中的人数
int WorkerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;
    int num =0;

    while (ifs>>id && ifs>>name && ifs>>dId) {
        num++;  // 统计人数
    }
    return num;
}


void WorkerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;

    int index=0;
    while (ifs>>id && ifs>>name && ifs>>dId) {
        Worker *worker =NULL;
        if (dId ==1) {
            worker = new Employee(id,name,dId);
        }else if (dId == 2) {
            worker = new Manager(id,name,dId);
        }else if (dId == 3) {
            worker = new Boss(id,name,dId);
        }

        this->m_EmpArray[index] = worker;
        index ++;
    }

    ifs.close();
}


void WorkerManager::show_Emp() {

    // 判断文件是否为空
    if (this->m_FileIsEmpty) {
        cout<<"文件不存在或记录为空！"<<endl;
    }else {
        for (int i=0;i<this->m_EmpNum;i++) {
            this->m_EmpArray[i]->showInfo();
        }
    }
}


void WorkerManager::Del_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空！" << endl;
    } else {
        cout << "请输入想要删除的职工编号：" << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);

        if (index == -1) {
            cout << "删除失败,未找到该职工！" << endl;
        } else {
            // 数据前移
            for (int i = index; i < this->m_EmpNum - 1; i++) {
                // 注意需要-1防止最后的越界访问
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            // 更新记录人员个数
            this->m_EmpNum--;
            // 更新至文件
            this->save();

            cout << "删除成功！" << endl;
        }
    }
}

// 寻找指定id的职工的数组位置
int WorkerManager::IsExist(int id) {
    int index = -1;

    for (int i =0;i<this->m_EmpNum;i++) {

        if (this->m_EmpArray[i]->m_Id == id) {
            index =i;
            break;
        }
    }
    return index;
}

// 修改职工
void WorkerManager::Mod_Emp() {

    if (this->m_FileIsEmpty) {
        cout<<"文件不存在或记录为空！"<<endl;
    }else {
        cout << "请输入修改的职工编号：" << endl;
        int id;
        cin>>id;
        int ret = this->IsExist(id);
        if (ret==-1) {
            cout << "修改失败，查无此人！" << endl;
        }else {
            delete this->m_EmpArray[ret];

            int newID = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到" << id << "号职工,请输入新的职工编号：" << endl;
            cin >> newID;
            cout << "请输入新的姓名：" << endl;
            cin >> newName;
            cout << "请输入部门编号：" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect) {
                case 1:
                    worker = new Employee(newID, newName, dSelect);
                    break;
                case 2:
                    worker = new Manager(newID, newName, dSelect);
                    break;
                case 3:
                    worker = new Boss(newID, newName, dSelect);
                    break;
                default:
                    break;
            }
            // 更新到数组中
            this->m_EmpArray[ret] = worker;
            cout << "修改成功！" << endl;
            // 保存到文件中
            this->save();
        }
    }
}

void WorkerManager::Find_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空！" << endl;
    }else {
        cout << "请输入查找方式：" << endl;
        cout << "1.按职工编号查找" << endl;
        cout << "2.按职工姓名查找" << endl;

        int select =0;
        cin>>select;

        if (select==1) {
            // 按职工编号查找
            int id;
            cout << "请输入查找的职工编号：" << endl;
            cin>>id;

            int ret = IsExist(id);
            if (ret==-1) {
                cout << "查找失败，查无此人！" << endl;
            }else {
                cout << "查找成功，该职工信息如下：" << endl;
                this->m_EmpArray[ret]->showInfo();
            }

        }else if (select==2) {
            // 按职工姓名查找
            string name;
            cout << "请输入查找的姓名：" << endl;
            cin>>name;

            bool flag =false; // 默认找不到
            for (int i=0;i<this->m_EmpNum;i++) {
                if (this->m_EmpArray[i]->m_Name == name) {
                    flag =true;
                    cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_Id <<endl;
                    cout << "该职工信息如下：" << endl;
                    this->m_EmpArray[i]->showInfo();
                    break;
                }
            }

            if (flag ==false) {
                cout << "查无此人，查找失败！" << endl;
            }


        }else {
            cout << "输入选项有误！" << endl;
        }

    }
}



void WorkerManager::Sort_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或记录为空！" << endl;
    }else {
        cout << "请选择排序方式：" << endl;
        cout << "1.按职工编号升序排序" << endl;
        cout << "2.按职工编号降序排序" << endl;

        int select =0;
        cin>>select;
        for (int i=0;i<this->m_EmpNum;i++) {


            int minOrMax = i; // 声明本轮最小或最大值的下标 初始化为第一个
            for (int j = i + 1; j < this->m_EmpNum; j++) {
                if (select == 1) {
                    if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[minOrMax]->m_Id) {
                        minOrMax = j;
                    }
                } else {
                    if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[minOrMax]->m_Id) {
                        minOrMax = j;
                    }
                }
            }
            if (i!=minOrMax) {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] =this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] =temp;
            }

        }

        cout << "排序成功！排序后的结果为：" << endl;
        this->save();
        this->show_Emp();
    }

}

// 清空文件
void WorkerManager::Clean_File() {
    cout << "确认清空？" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;

    int select;
    cin>>select;

    if (select ==1) {
        // 清空文件
        ofstream ofs(FILENAME,ios::trunc);
        ofs.close();

        if (this->m_EmpArray!=NULL) {
            for (int i=0;i<this->m_EmpNum;i++) {
                // 删除堆区每个职工对象
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] =NULL;
            }

            delete[] this->m_EmpArray;
            this->m_EmpArray =NULL;
            this->m_EmpNum =0;
            this->m_FileIsEmpty =true;

        }

        cout << "清空成功！" << endl;
    }
}




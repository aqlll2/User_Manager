#ifndef __USER_H
#define __USER_H

//头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//宏定义
#define MAX_NAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define HASH_SIZE 10




//结构体的定义
//用户的信息
typedef struct {
    char username[MAX_NAME_LEN];//用户名
    char password[MAX_PASSWORD_LEN];//用户密码
    int isAdmin; // 是否为管理员
} User;
//哈希链表的节点
typedef struct Node {
    User user;//用户数据域
    struct Node* next;//链表的下一个节点
} Node;

extern Node* hashtable[HASH_SIZE];

//函数声明

// Hash函数，将用户名映射到哈希表中的索引
int hash(char* username);

//函数功能：添加用户
//函数参数：要添加的表的地址
//函数参数2：要添加的用户名
void addUser(Node** hashtable, User user);

//函数功能：查找用户根据用户名
//函数参数：要查找的表
//函数参数2：要查找的用户名
User* findUser(Node** hashtable, char* username);

//函数功能 ：从文件中加载用户
//函数参数：要加载的表
//函数参数2：要存储信息的文件名
void loadUsersFromFile(Node** hashtable, const char* filename);


//函数功能：保存信息到文件
//函数参数：要保存的表
//函数参数2:要保存到的位置
void saveUsersToFile(Node** hashtable, const char* filename);


// 添加用户子菜单
void addUserMenu();


// 添加管理员子菜单
void addAdminMenu();


// 修改用户信息子菜单
void modifyUserMenu(User* currentUser);


// 删除用户子菜单
void deleteUserMenu();


// 管理员菜单
void adminMenu(User* currentUser);


// 用户菜单
void userMenu(User* currentUser);



// 初始化管理员账户
void initializeAdmins(Node** hashtable);


//运行函数
void run();


#endif




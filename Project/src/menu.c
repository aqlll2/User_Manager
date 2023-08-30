#include "../include/User.h"


// 添加用户子菜单
void addUserMenu() {
    char username[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("请输入要添加的用户名：");
    scanf("%s", username);

    User* user = findUser(hashtable, username);
    if (user != NULL) {
        printf("该用户名已经存在！\n");
        return;
    }

    printf("请输入要添加的用户密码：");
    scanf("%s", password);

    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.isAdmin = 0;

    addUser(hashtable, newUser);

    saveUsersToFile(hashtable, "users.txt"); // 保存用户数据到文件

    printf("用户添加成功！\n");
}


// 添加管理员子菜单
void addAdminMenu() {
    char username[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("请输入要添加的管理名：");
    scanf("%s", username);

    User* user = findUser(hashtable, username);
    if (user != NULL) {
        printf("该管理已经存在！\n");
        return;
    }

    printf("请输入要添加的管理员密码：");
    scanf("%s", password);

    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.isAdmin = 1;

    addUser(hashtable, newUser);

    saveUsersToFile(hashtable, "users.txt"); // 保存用户数据到文件

    printf("管理员添加成功！\n");
}
// 修改用户信息子菜单
void modifyUserMenu(User* currentUser) {
    char username[MAX_NAME_LEN];
    char newPassword[MAX_PASSWORD_LEN];

    printf("请输入要修改的用户名：");
    scanf("%s", username);

    User* user = findUser(hashtable, username);
    if (user == NULL) {
        printf("找不到该用户！\n");
        return;
    }
    
    // 如果当前用户是管理员且不是自己，则无法修改其他管理员的信息
    if (currentUser->isAdmin == 1 \
			&& currentUser->isAdmin == ((findUser(hashtable,username))->isAdmin) \
			&& strcmp(currentUser->username, username) != 0) { 
        printf("权限不足，无法修改其他管理员的信息！\n");
        return;
    }

    printf("请输入新的用户密码：");
    scanf("%s", newPassword);

    strcpy(user->password, newPassword);

    saveUsersToFile(hashtable, "users.txt"); // 保存用户数据到文件

    printf("用户信息修改成功！\n");
}

// 删除用户子菜单
void deleteUserMenu() {
    char username[MAX_NAME_LEN];

    printf("请输入要删除的用户名：");
    scanf("%s", username);

    int index = hash(username);
    Node* curr = hashtable[index];
    Node* prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->user.username, username) == 0) {
            if (prev == NULL) {
                hashtable[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr); // 释放内存
            saveUsersToFile(hashtable, "users.txt"); // 保存用户数据到文件
            printf("用户删除成功！\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("找不到该用户！\n");
}

// 查询用户信息子菜单
void queryUserMenu() {
    char username[MAX_NAME_LEN];

    printf("请输入要查询的用户名：");
    scanf("%s", username);

    User* user = findUser(hashtable, username);
    if (user == NULL) {
        printf("找不到该用户！\n");
        return;
    }

    printf("用户名：%s\n", user->username);
    printf("密码：%s\n", user->password);
}

// 管理员菜单
void adminMenu(User* currentUser) {
    while (1) {
        printf("\n===== 操作选项 =====\n");
        printf("1. 添加用户\n");
        printf("2. 删除用户\n");
        printf("3. 修改用户信息\n");
        printf("4. 查询用户信息\n");
        printf("5. 添加另一个管理员\n");
        printf("6. 退出\n");

        int choice;
        printf("请输入操作选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUserMenu();
                break;
            case 2:
                deleteUserMenu();
                break;
            case 3:
                modifyUserMenu(currentUser);
                break;
            case 4:
                queryUserMenu();
                break;
            case 5:
                if (currentUser->isAdmin) {
                    addUserMenu(); // 添加管理员
                } else {
                    printf("权限不足，无法添加管理员！\n");
                }
                break;
            case 6:
                printf("退出\n");
                return;
            default:
                printf("无效的输入\n");

		}
	}
}


// 用户菜单
void userMenu(User* currentUser) {
    while (1) {
        printf("\n===== 操作选项 =====\n");
        printf("1. 查询个人信息\n");
        printf("2. 修改密码\n");
        printf("3. 退出\n");

        int choice;
        printf("请输入操作选项：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                queryUserMenu();
                break;
            case 2:
                modifyUserMenu(currentUser);
                break;
            case 3:
                printf("退出\n");
                return;
            default:
                printf("无效的输入\n");
        }
    }
}





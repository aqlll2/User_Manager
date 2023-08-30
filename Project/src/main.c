#include "../include/User.h"

Node* hashtable[HASH_SIZE];
// 开始运行
void run() {
	for (int i = 0; i < HASH_SIZE; i++) {
        hashtable[i] = NULL; // 初始化哈希表中的每个位置为NULL
    }
    
    loadUsersFromFile(hashtable, "users.txt"); // 从文件中加载用户数据

    while (1) {
        printf("\n===== 用户登录 =====\n");
        printf("1. 普通用户登录\n");
        printf("2. 管理员登录\n");
        printf("3. 退出\n");

        int choice;
        printf("请输入选项：");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("退出\n");
            saveUsersToFile(hashtable, "users.txt"); // 退出前保存用户数据到文件
            break;
        } else if (choice == 1) {
            char username[MAX_NAME_LEN];
            char password[MAX_PASSWORD_LEN];

            printf("请输入用户名：");
            scanf("%s", username);
            printf("请输入密码：");
            scanf("%s", password);

            User* user = findUser(hashtable, username);

            if (user != NULL && !user->isAdmin && strcmp(user->password, password) == 0) {
                printf("登录成功！\n");
                userMenu(user);
            } else {
                printf("用户名或密码错误！\n");
            }
        } else if (choice == 2) {
            char username[MAX_NAME_LEN];
            char password[MAX_PASSWORD_LEN];

            printf("请输入管理员用户名：");
            scanf("%s", username);
            printf("请输入管理员密码：");
            scanf("%s", password);

            User* admin = findUser(hashtable, username);

            if (admin != NULL && admin->isAdmin && strcmp(admin->password, password) == 0) {
                printf("管理员登录成功！\n");
                adminMenu(admin);
            } else {
                printf("管理员用户名或密码错误！\n");
            }
        } else {
            printf("无效的选项\n");
        }
    }
}

int main() {

//initializeAdmins(hashtable); // 初始化管理员账户
run(); // 开始运行


return 0;
}


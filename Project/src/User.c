#include "../include/User.h"


// Hash函数，将用户名映射到哈希表中的索引
int hash(char* username) {
    int sum = 0;
    for (int i = 0; i < strlen(username); i++) {
        sum += username[i];
    }
    return sum % HASH_SIZE;
}

// 添加用户
void addUser(Node** hashtable, User user) {
    int index = hash(user.username);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->user = user;
    newNode->next = NULL;

    if (hashtable[index] == NULL) {
        hashtable[index] = newNode; // 哈希表中该位置为空，直接插入新节点
    } else {
        Node* curr = hashtable[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode; // 遍历到链表末尾，加入新节点
    }
}

// 根据用户名查找用户
User* findUser(Node** hashtable, char* username) {
    int index = hash(username);
    Node* curr = hashtable[index];

    while (curr != NULL) {
        if (strcmp(curr->user.username, username) == 0) {
            return &(curr->user); // 找到用户，返回指针
        }
        curr = curr->next;
    }

    return NULL; // 用户不存在，返回NULL
}


// 从文件中加载用户
void loadUsersFromFile(Node** hashtable, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    char line[MAX_NAME_LEN + MAX_PASSWORD_LEN + 10];
    while (fgets(line, sizeof(line), file)) {
        char username[MAX_NAME_LEN];
        char password[MAX_PASSWORD_LEN];
        int isAdmin;

        sscanf(line, "%s %s %d", username, password, &isAdmin);//解析读取到的一行字符串

        User newUser;
        strcpy(newUser.username, username);
        strcpy(newUser.password, password);
        newUser.isAdmin = isAdmin;

        addUser(hashtable, newUser);
    }

    fclose(file);
}

// 将用户数据保存到文件
void saveUsersToFile(Node** hashtable, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法保存文件\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashtable[i];
        while (curr != NULL) {
            fprintf(file, "%s %s %d\n", curr->user.username, curr->user.password, curr->user.isAdmin);
            curr = curr->next;
        }
    }

    fclose(file);
}


// 初始化管理员账户
void initializeAdmins(Node** hashtable) {
    User admin1, admin2;

    strcpy(admin1.username, "admin1");
    strcpy(admin1.password, "admin1");
    admin1.isAdmin = 1;
    addUser(hashtable, admin1);
    strcpy(admin2.username, "admin2");
    strcpy(admin2.password, "admin2");
    admin2.isAdmin = 1;
    addUser(hashtable, admin2);
	
}
















#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100
#define FILE_NAME "todo.txt"

struct Task {
    char text[MAX_LEN];
    int done; // 0 = not done, 1 = done
};

void save(struct Task tasks[], int n) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: Could not save file.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d|%s\n", tasks[i].done, tasks[i].text);
    }
    fclose(fp);
}

int load(struct Task tasks[]) {
    FILE *fp = fopen(FILE_NAME, "r");
    int n = 0;
    if (fp == NULL) return 0; // no file yet

    while (fscanf(fp, "%d|%[^\n]\n", &tasks[n].done, tasks[n].text) == 2) {
        n++;
    }
    fclose(fp);
    return n;
}

void addTask(struct Task tasks[], int *n) {
    if (*n >= MAX_TASKS) {
        printf("List is full!\n");
        return;
    }
    getchar(); // clear buffer
    printf("Enter new task: ");
    fgets(tasks[*n].text, MAX_LEN, stdin);
    tasks[*n].text[strcspn(tasks[*n].text, "\n")] = '\0'; 
    tasks[*n].done = 0;
    (*n)++;
    save(tasks, *n);
    printf("Task added.\n");
}

void editTask(struct Task tasks[], int n) {
    int num;
    printf("Enter task number to edit: ");
    scanf("%d", &num);
    if (num < 1 || num > n) {
        printf("Invalid number.\n");
        return;
    }
    getchar(); // clear buffer
    printf("Enter new text: ");
    fgets(tasks[num - 1].text, MAX_LEN, stdin);
    tasks[num - 1].text[strcspn(tasks[num - 1].text, "\n")] = '\0';
    save(tasks, n);
    printf("Task updated.\n");
}

void markDone(struct Task tasks[], int n) {
    int num;
    printf("Enter task number to mark complete: ");
    scanf("%d", &num);
    if (num < 1 || num > n) {
        printf("Invalid number.\n");
        return;
    }
    tasks[num - 1].done = 1;
    save(tasks, n);
    printf("Marked as complete.\n");
}

void viewTasks(struct Task tasks[], int n) {
    if (n == 0) {
        printf("No tasks.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (tasks[i].done)
            printf("[DONE]  %s\n", tasks[i].text); 
        else
            printf("%d. %s\n", i + 1, tasks[i].text);
    }
}

int main() {
    struct Task tasks[MAX_TASKS];
    int n = load(tasks);
    int choice;

    while (1) {
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Mark Complete\n");
        printf("4. View Tasks\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(tasks, &n); break;
            case 2: editTask(tasks, n); break;
            case 3: markDone(tasks, n); break;
            case 4: viewTasks(tasks, n); break;
            case 5: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}

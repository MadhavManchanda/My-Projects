#include <iostream>
#include <string>
#include <stack>
#include<queue>
struct Task {
    int id;
    std::string description;
    bool completed;
    Task* next;

    Task(int i, const std::string& desc)
        : id(i), description(desc), completed(false), next(nullptr) {}
};

class TaskList {
private:
    Task* head;
    int nextId;

public:
    TaskList() : head(nullptr), nextId(1) {}

    void addTask(const std::string& description) {
        Task* newTask = new Task(nextId++, description);
        newTask->next = head;
        head = newTask;
        std::cout << "Task added: " << newTask->description << "\n";
    }

    Task* removeTask(int id) {
        Task* temp = head;
        Task* prev = nullptr;

        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            std::cout << "Task not found!\n";
            return nullptr;
        }

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        std::cout << "Task removed: " << temp->description << "\n";
        return temp; // Return the removed task
    }

    void completeTask(int id) {
        Task* temp = head;

        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            std::cout << "Task not found!\n";
            return;
        }

        temp->completed = true;
        std::cout << "Task completed: " << temp->description << "\n";
    }

    void displayTasks() const {
        Task* temp = head;
        while (temp != nullptr) {
            std::cout << "Task ID: " << temp->id << ", Description: " << temp->description
                      << ", Completed: " << (temp->completed ? "Yes" : "No") << "\n";
            temp = temp->next;
        }
    }

    Task* getHead() const {
        return head;
    }
};

class UndoStack {
private:
    std::stack<Task*> undoStack;

public:
    void push(Task* task) {
        undoStack.push(task);
    }

    Task* pop() {
        if (undoStack.empty()) {
            std::cout << "No task to undo!\n";
            return nullptr;
        }
        Task* task = undoStack.top();
        undoStack.pop();
        return task;
    }
};

int main() {
    TaskList taskList;
    UndoStack undoStack;
    int choice;
    std::string description;
    int taskId;

    do {
        std::cout << "\nTo-Do List Menu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. Complete Task\n";
        std::cout << "4. Display Tasks\n";
        std::cout << "5. Undo Last Removal\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore(); // To consume the newline left by std::cin
                std::getline(std::cin, description);
                taskList.addTask(description);
                break;
            case 2: {
                std::cout << "Enter task ID to remove: ";
                std::cin >> taskId;
                Task* removedTask = taskList.removeTask(taskId);
                if (removedTask) {
                    undoStack.push(removedTask); // Push the removed task onto the undo stack
                }
                break;
            }
            case 3:
                std::cout << "Enter task ID to complete: ";
                std::cin >> taskId;
                taskList.completeTask(taskId);
                break;
            case 4:
                std::cout << "\nCurrent tasks:\n";
                taskList.displayTasks();
                break;
            case 5: {
                Task* lastRemovedTask = undoStack.pop();
                if (lastRemovedTask) {
                    taskList.addTask(lastRemovedTask->description);
                    std::cout << "Undo successful, task re-added: " << lastRemovedTask->description << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting the application.\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class Task {
public:
    std::string title;
    std::string description;

    Task(const std::string& title, const std::string& description)
        : title(title), description(description) {}

    bool operator<(const Task& other) const {
        return title < other.title;
    }
};

void addTask(std::vector<Task>& tasks) {
    std::string title, description;
    std::cout << "Enter the task title: ";
    std::getline(std::cin, title);
    std::cout << "Enter the task description: ";
    std::getline(std::cin, description);
    tasks.emplace_back(title, description);
    std::cout << "Task '" << title << "' added.\n";
}

void removeTask(std::vector<Task>& tasks) {
    int taskNumber;
    std::cout << "Enter the task number to remove: ";
    std::cin >> taskNumber;
    std::cin.ignore();
    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        std::cout << "Are you sure you want to remove '" << tasks[taskNumber - 1].title << "'? (y/n): ";
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();
        if (confirm == 'y' || confirm == 'Y') {
            tasks.erase(tasks.begin() + taskNumber - 1);
            std::cout << "Task removed.\n";
        }
    } else {
        std::cout << "Invalid task number.\n";
    }
}

void viewTasks(std::vector<Task>& tasks) {
    std::sort(tasks.begin(), tasks.end());
    std::cout << "Your Todo List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].title << " - " << tasks[i].description << "\n";
    }
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.title << "\n" << task.description << "\n";
    }
}

void loadTasks(std::vector<Task>& tasks) {
    std::ifstream file("tasks.txt");
    std::string title, description;
    while (std::getline(file, title) && std::getline(file, description)) {
        tasks.emplace_back(title, description);
    }
}

int main() {
    std::vector<Task> tasks;
    loadTasks(tasks);
    int choice;
    do {
        std::cout << "\nWelcome to the Todo List Application!\n";
        std::cout << "Please choose an option:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. View Tasks\n";
        std::cout << "4. Exit\n";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
            case 1:
                addTask(tasks);
                saveTasks(tasks);
                break;
            case 2:
                removeTask(tasks);
                saveTasks(tasks);
                break;
            case 3:
                viewTasks(tasks);
                break;
            case 4:
                std::cout << "Exiting the application: Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
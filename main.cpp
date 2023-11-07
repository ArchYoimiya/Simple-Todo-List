#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(const string &desc, bool comp = false) : description(desc), completed(comp) {}
};

class TodoList {
private:
    vector<Task> tasks;
    const string filename;

    void loadTasks() {
        ifstream file(filename);
        if (file) {
            string description;
            bool completed;
            while (file >> completed) {
                file.ignore(); // Ignore the space after completed
                getline(file, description);
                tasks.emplace_back(description, completed);
            }
        }
        file.close();
    }

    void saveTasks() {
        ofstream file(filename);
        for (const auto &task : tasks) {
            file << (task.completed ? 1 : 0) << ' ' << task.description << endl;
        }
        file.close();
    }

public:
    TodoList(const string &fname) : filename(fname) {
        loadTasks();
    }

    ~TodoList() {
        saveTasks();
    }

    void addTask(const string &taskDescription) {
        tasks.emplace_back(taskDescription);
    }

    void completeTask(int taskIndex) {
        if (taskIndex >= 0 && taskIndex < tasks.size()) {
            tasks[taskIndex].completed = true;
        } else {
            cerr << "Invalid task index.\n";
        }
    }

    void removeTask(int taskIndex) {
        if (taskIndex >= 0 && taskIndex < tasks.size()) {
            tasks.erase(tasks.begin() + taskIndex);
        } else {
            cerr << "Invalid task index.\n";
        }
    }

    void showTasks() {
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].completed ? "x" : " ") << "] " << tasks[i].description << endl;
        }
    }
};

int main() {
    TodoList myTodoList("todolist.txt");
    string command;
    string taskDescription;
    int taskIndex;

    while (true) {
        cout << "Enter command (add, complete, remove, show, exit): ";
        cin >> command;

        if (command == "add") {
            cout << "Enter a description of the new task: ";
            cin.ignore(); // Ignore the newline left in the input stream
            getline(cin, taskDescription);
            myTodoList.addTask(taskDescription);
        } else if (command == "complete") {
            cout << "Enter the index of the task to complete: ";
            cin >> taskIndex;
            myTodoList.completeTask(taskIndex - 1);
        } else if (command == "remove") {
            cout << "Enter the index of the task to remove: ";
            cin >> taskIndex;
            myTodoList.removeTask(taskIndex - 1);
        } else if (command == "show") {
            myTodoList.showTasks();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}


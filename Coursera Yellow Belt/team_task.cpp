#include <iostream>
#include <exception>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  TasksInfo GetPersonTasksInfo(const string& person){
      TasksInfo sordata = data.at(person);
      vector<TaskStatus> del_key_with_0;
      for (auto& [key, value]: sordata){
          if (value == 0){
              del_key_with_0.push_back(key);
          }
      }
      for (auto& item: del_key_with_0){
          sordata.erase(item);
      }
      return sordata;
  } 
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
      if (data.count(person) == 0){
      data[person] = {{TaskStatus::NEW,1},{TaskStatus::IN_PROGRESS,0}, {TaskStatus::TESTING, 0}, {TaskStatus::DONE, 0}};
      }else{
          data[person][TaskStatus::NEW] += 1;
      }
  }
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){
      if (data.count(person) != 0){
          int temp = task_count;
          TasksInfo upgrated_task;
          TasksInfo unupgrated_task;
          for (auto& [key, value]: data[person]){
            switch (key){
            case TaskStatus::NEW:
                if (value>=temp){
                    upgrated_task[TaskStatus::IN_PROGRESS] = temp;
                    unupgrated_task[TaskStatus::NEW] = value - temp;
                    temp = 0;
                }else{
                    unupgrated_task[TaskStatus::NEW] = 0;
                    upgrated_task[TaskStatus::IN_PROGRESS] = value;
                    temp -= value;
                }
                break;
            case TaskStatus::IN_PROGRESS:
                if (value >= temp){
                    upgrated_task[TaskStatus::TESTING] = temp;
                    unupgrated_task[TaskStatus::IN_PROGRESS] = value - temp;
                    temp = 0;
                }else{
                    unupgrated_task[TaskStatus::IN_PROGRESS] = 0;
                    upgrated_task[TaskStatus::TESTING] = value;
                    temp -=value;
                }
                break;
            case TaskStatus::TESTING:
                if( value >= temp){
                    upgrated_task[TaskStatus::DONE] = temp;
                    unupgrated_task[TaskStatus::TESTING] = value - temp;
                    temp = 0;
                }else{
                    unupgrated_task[TaskStatus::TESTING] = 0;
                    upgrated_task[TaskStatus::DONE] = value;
                    temp -= value;
                }
                break;
            case TaskStatus::DONE:
                break;
            }
          }
          for (auto& [key, value]: data[person]){
              switch(key){
                case TaskStatus::NEW:
                    data[person][TaskStatus::NEW] = upgrated_task[TaskStatus::NEW] + 
                                                    unupgrated_task[TaskStatus::NEW];
                    break;
                case TaskStatus::IN_PROGRESS:
                    data[person][TaskStatus::IN_PROGRESS] = upgrated_task[TaskStatus::IN_PROGRESS] + 
                                                    unupgrated_task[TaskStatus::IN_PROGRESS];
                    break;
                case TaskStatus::TESTING:
                    data[person][TaskStatus::TESTING] = upgrated_task[TaskStatus::TESTING] + 
                                                    unupgrated_task[TaskStatus::TESTING];
                    break;
                case TaskStatus::DONE:
                    data[person][TaskStatus::DONE] += upgrated_task[TaskStatus::DONE] + 
                                                    unupgrated_task[TaskStatus::DONE];
                    break;     
              }
          }
          vector<TaskStatus> delet_upd_task;
          for (auto& [key, value] : upgrated_task){
              if (value == 0){
                  delet_upd_task.push_back(key);
              }
          }
          vector<TaskStatus> delet_unupd_task;
          for(auto& [key,value]: unupgrated_task){
              if (value == 0){
                  delet_unupd_task.push_back(key);
              }
          }
          for (auto& i: delet_upd_task){
              upgrated_task.erase(i);
          }
          for (auto& i: delet_unupd_task){
              unupgrated_task.erase(i);
          }
          return make_tuple(upgrated_task, unupgrated_task);

      }else{
          tuple<TasksInfo, TasksInfo> emp;
          return emp;
      }
  }
private:
    map<string, TasksInfo> data;
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
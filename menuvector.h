#ifndef UNTITLED_MENUVECTOR_H
#define UNTITLED_MENUVECTOR_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "struct.h"

////////////////////////////////////
std::string weekdays[] = {"Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"};
int auds[] = {310, 311, 312, 313, 314};
std::string line = "-------------------------------------\n";

Struct *data = new Struct();
std::vector<std::vector<Struct>> vec(7);
////////////////////////////////////

void list_lessons(){
    int i = 1;

    for(auto weekdaay: vec){
        for(auto item: weekdaay){
            std::cout << line << i << "| ";
            std::cout << weekdays[item.weekday] << " Lesson:" << item.lesson_number << " Auditorium:" << item.auditorium_number << std::endl;
            std::cout << "Group:" << item.group_number << " Discipline code:" << item.discipline_code << std::endl;
            std::cout << line;
            i++;
        }
    }
}

std::vector<int> check_free_auditorias(int day, int les_num){
    std::vector<int> free_auds(auds, auds + 5);

    for(auto item: vec[day-1])
        if(item.weekday == day - 1 && item.lesson_number == les_num)
            free_auds.erase(std::find(free_auds.begin(), free_auds.end(), item.auditorium_number));

    return free_auds;
}


void add_lesson(){
    int day, les_num, aud, disc;
    std::string group;

    for(int i = 0; i < 6; i++) std::cout << i + 1 << "| " << weekdays[i] << std::endl;
    std::cout << "Enter weekday:";
    std::cin >> day;
    data->weekday = day - 1;

    std::cout << "Enter lesson number:";
    std::cin >> les_num;
    data->lesson_number = les_num;

    std::cout << "Free auditorias now:";
    for(auto item: check_free_auditorias(day, les_num)){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout << "Enter auditoria number:";
    std::cin >> aud;
    data->auditorium_number = aud;

    std::cout << "Enter group num:";
    std::cin >> group;
    data->group_number = group;

    std::cout << "Enter discipline code:";
    std::cin >> disc;
    data->discipline_code = disc;

    vec[day-1].push_back(*data);
}

void reschedule_lesson() {
    list_lessons();

    int answer;
    std::cout << "Which lesson do you want to reschedule?\n:";
    std::cin >> answer;

    int i = 1;

    for (auto& weekday : vec) {
        for (auto& item : weekday) {
            if (i == answer) {
                int new_weekday;
                for (int i = 0; i < 6; i++) {
                    std::cout << i + 1 << "| " << weekdays[i] << std::endl;
                }
                std::cout << "Enter new weekday:";
                std::cin >> new_weekday;

                bool exists_on_new_weekday = false;
                for (auto& wd : vec) {
                    for (auto& it : wd) {
                        if (it.weekday == new_weekday - 1 && it.lesson_number == item.lesson_number + 1) {
                            exists_on_new_weekday = true;
                            break;
                        }
                    }
                    if (exists_on_new_weekday) {
                        break;
                    }
                }

                if (exists_on_new_weekday) {
                    item.weekday = (item.weekday + 1) % 7;
                    std::cout << "Lesson already exists on new weekday, so rescheduled to the next day.\n";
                } else {
                    item.weekday = new_weekday - 1;
                    std::cout << "Lesson rescheduled successfully!\n";
                }

                list_lessons();
                return;
            }
            i++;
        }
    }

    std::cout << "Lesson not found.\n";
}


void list_lessons_by_discipline_code(int discipline_code){
    int i = 1;

    for(auto weekdaay: vec){
        for(auto item: weekdaay){
            if(item.discipline_code == discipline_code){
                std::cout << line << i << "| ";
                std::cout << weekdays[item.weekday] << " Lesson:" << item.lesson_number << " Auditorium:" << item.auditorium_number << std::endl;
                std::cout << "Group:" << item.group_number << " Discipline code:" << item.discipline_code << std::endl;
                std::cout << line;
                i++;
            }
        }
    }
}


void menuvec(){
    while(true) {
        std::cout << "1| Add lesson" << std::endl;
        std::cout << "2| List lessons" << std::endl;
        std::cout << "3| Reschedule a lesson" << std::endl;
        std::cout << "4| List lessons by discipline code" << std::endl;
        std::cout << "5| Exit" << std::endl;

        int answer = 0;
        std::cout << ":";
        std::cin >> answer;

        if(answer == 1){
            add_lesson();
        } else if(answer == 2){
            list_lessons();
        } else if (answer == 3){
            reschedule_lesson();
        } else if (answer == 4){
            int discipline_code;
            std::cout << "Enter discipline code:";
            std::cin >> discipline_code;
            list_lessons_by_discipline_code(discipline_code);
        } else {
            break;
        }
    }
}
#endif //UNTITLED_MENU_H
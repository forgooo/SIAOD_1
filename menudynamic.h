#ifndef UNTITLED_MENUDYNAMIC_H
#define UNTITLED_MENUDYNAMIC_H
#include <iostream>
#include <string>
#include "struct.h"

////////////////////////////////////
int SIZE = 6;
std::string weekdays[] = {"Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"};
int auds[] = {310, 311, 312, 313, 314};
std::string line = "-------------------------------------\n";

Struct *data = new Struct();
Struct **vec;

int vecles[] = {-1, -1, -1, -1, -1, -1};

////////////////////////////////////

void list_lessons() {
    int m = 1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (vec[i][j].auditorium_number != 0) {
                std::cout << line << m << "| ";
                std::cout << weekdays[vec[i][j].weekday] << " Lesson:" << vec[i][j].lesson_number << " Auditorium:"
                          << vec[i][j].auditorium_number << std::endl;
                std::cout << "Group:" << vec[i][j].group_number << " Discipline code:" << vec[i][j].discipline_code
                          << std::endl;
                std::cout << line;
                m++;
            }
        }
    }
}

bool check_free_auditorias(int day, int les_num, int aud) {
    for (int i = 0; i < SIZE; i++) {
        if (vec[day-1][i].lesson_number == les_num && vec[day-1][i].auditorium_number == aud) {
            return false;
        }
    }
    return true;
}

void add_lesson(){
    int day, les_num, aud, disc;
    int group;

    for(int i = 0; i < 6; i++) std::cout << i + 1 << "| " << weekdays[i] << std::endl;
    std::cout << "Enter weekday:";
    std::cin >> day;
    data->weekday = day - 1;

    std::cout << "Enter lesson number:";
    std::cin >> les_num;
    data->lesson_number = les_num;

    std::cout << "Free auditorias now:";
    for (auto aud : auds) {
        if (check_free_auditorias(day, les_num, aud)) {
            std::cout << aud << " ";
        }
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


    vecles[day-1]++;
    vec[day-1][vecles[day-1]++] = *data;
}

void reschedule_lesson() {
    list_lessons();

    int answer;
    std::cout << "Which lesson do you want to reschedule?" << std::endl;
    std::cout << ":";
    std::cin >> answer;

    int count = 0;
    Struct *selected = nullptr;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (vec[i][j].auditorium_number != 0) {
                count++;
                if (count == answer) {
                    selected = &vec[i][j];
                    break;
                }
            }
        }
        if (selected != nullptr) {
            break;
        }
    }

    if (selected == nullptr) {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    int new_weekday;
    for(int i = 0; i < 6; i++) std::cout << i + 1 << "| " << weekdays[i] << std::endl;
    std::cout << "Enter weekday:";
    std::cin >> new_weekday;
    new_weekday--;

    int new_les_num;
    std::cout << "Enter new lesson number (1-6):";
    std::cin >> new_les_num;

    bool found = false;

    for (int i = 0; i < SIZE; i++) {
        if (check_free_auditorias(new_weekday + 1, new_les_num + 1, auds[i])) {
            selected->weekday = new_weekday;
            selected->lesson_number = new_les_num;
            selected->auditorium_number = auds[i];
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No free auditoriums on the new day and time." << std::endl;
    }
}




void list_lessons_by_discipline_code(int discipline_code){
    int i = 1;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(vec[i][j].discipline_code == discipline_code){
                std::cout << line << i << "| ";
                std::cout << weekdays[vec[i][j].weekday] << " Lesson:" << vec[i][j].lesson_number << " Auditorium:" << vec[i][j].auditorium_number << std::endl;
                std::cout << "Group:" << vec[i][j].group_number << " Discipline code:" << vec[i][j].discipline_code << std::endl;
                std::cout << line;
                i++;
            }
        }
    }
}

void start(){
    vec = new Struct*[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        vec[i] = new Struct[SIZE];
    }
}

void menudyn(){
    start();
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
        } else if(answer == 3){
            reschedule_lesson();
        } else if(answer == 4){
            int discipline_code;
            std::cout << "Enter discipline code: ";
            std::cin >> discipline_code;
            list_lessons_by_discipline_code(discipline_code);
        } else if(answer == 5){
            break;
        } else{
            std::cout << "Invalid input\n";
        }
    }
}

#endif //UNTITLED_MENU_H
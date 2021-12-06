/*
VS STUDIO 2022 17.0.1

ВАРИАНТ 7
Б9120-09.03.04прогин, подгруппа 4
Рольщиков Максим Евгеньевич

Предметная область:
Университет. Обязательные сущности: студент, группа, расписание занятий, предмет.

Реализация в файле univer.h
*/


#include <iostream>
#include <string>
#include "univer.h"

int main()
{
    setlocale(0, ""); //Включаем кирриллицу
    StudyGroup group1("B9120");
    StudyGroup group2("M2020");

    Student st1("Иванов", "Иван", "Иванович");
    Student st2("Рольщиков", "Максим", "Евгеньевич");
    Student st3("Коршунов", "Марк", "Миронович");
    Student st4("Сидорова", "София", "Ивановна");

    group1.PinStudent(st1);
    group1.PinStudent(st2);
    group2.PinStudent(st3);
    group2.PinStudent(st4);

    Schedule schedule;

    Subject sbj1("Матанализ", "Зиновьев Павел Владимирович", "10:10", &group1);
    Subject sbj2(sbj1);
    sbj2.set_discipline("Философия");
    sbj2.set_time("11:50");
    sbj2.set_teacher_fio("Каменев Сергей Валентинович");
    schedule.AddSubject(sbj1);
    schedule.AddSubject(sbj2);

    Subject sbj3("Матанализ", "Зиновьев Павел Владимирович", "8:30", &group2);
    Subject sbj4("Матанализ", "Зиновьев Павел Владимирович", "15:10", &group2);
    schedule.AddSubject(sbj3);
    schedule.AddSubject(sbj4);


    std::cout << "Расписание группы: " << group1.get_groupNum() << "\n";
    std::cout << schedule.GetStudyGroupScheduleLikeString(group1.get_groupNum());
    std::cout << "\nДля студентов:\n";
    std::cout << group1.GetAllStudentsLikeString() << "\n";

    std::cout << "Расписание группы: " << group2.get_groupNum() << "\n";
    std::cout << schedule.GetStudyGroupScheduleLikeString(group2.get_groupNum());
    std::cout << "\nДля студентов:\n";
    std::cout << group2.GetAllStudentsLikeString() << "\n";
}

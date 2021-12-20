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

    Teacher t1("Зиновьев", "Павел",  "Владимирович");
    t1.SetDiscipline("Матанализ");
    Teacher t2("Каменев", "Сергей",  "Валентинович");
    t2.SetDiscipline("Философия");
    Teacher t3("Осипова", "Марина",  "Анатольевна");
    t3.SetDiscipline("Матанализ");

    Schedule schedule;

    Subject sbj1("Матанализ", t1, "10:10", &group1);
    Subject sbj2(sbj1);
    sbj2.set_discipline("Философия");
    sbj2.set_time("11:50");
    sbj2.set_teacher(t2);
    schedule.AddSubject(sbj1);
    schedule.AddSubject(sbj2);

    Subject sbj3("Матанализ", t1, "8:30", &group2);
    Subject sbj4("Матанализ", t1, "15:10", &group2);
    schedule.AddSubject(sbj3);
    schedule.AddSubject(sbj4);


    std::cout << "Расписание группы: " << group1.get_groupNum() << "\n";
    std::cout << schedule.GetStudyGroupScheduleAsString(group1.get_groupNum());
    std::cout << "\nДля студентов:\n";
    std::cout << group1.GetAllStudentsAsString() << "\n";

    std::cout << "Расписание группы: " << group2.get_groupNum() << "\n";
    std::cout << schedule.GetStudyGroupScheduleAsString(group2.get_groupNum());
    std::cout << "\nДля студентов:\n";
    std::cout << group2.GetAllStudentsAsString() << "\n\n";

    AllSubjectTeachers mathTeachers;
    mathTeachers.set_subjectName("Матанализ");
    mathTeachers.PinTeacher(t1);
    mathTeachers.PinTeacher(t3);
    std::cout << "Предмет " << mathTeachers.get_subjectName() << " ведут:\n";
    std::cout << mathTeachers.GetAllTeachersAsString();
}

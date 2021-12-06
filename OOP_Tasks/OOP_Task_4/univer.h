#pragma once
#include <list>
#include <string>

/// <summary> Класс описывающий студента </summary>
class Student
{
private:
	
	int unique_id; //Уникальный идентифиватор студента
	std::string name; //Имя
	std::string surname; //Фамилия
	std::string patronymic; //Отчество

public:
	static int UNIQUE_ID;
	/// <summary> Студент со стандартными параметрами </summary>
	Student():name("Ivan"), surname("Ivanov")
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> Студент с указанными именем, фамилией и отчеством </summary>
	Student(std::string name, std::string surname, std::string patronymic = "") :name(name),
		surname(surname), patronymic(patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> Копирует данные student и создает новый объект класса Student </summary>
	Student(const Student& student) :name(student.name),
		surname(student.surname), patronymic(student.patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> Возвращает имя студента </summary>
	std::string get_name() { return name; }

	/// <summary> Возвращает фамилию студента </summary>
	std::string get_surname() { return surname; }

	/// <summary> Возвращает отчество студента </summary>
	std::string get_patronymic() { return patronymic; }

	/// <summary> Возвращает данные студента в виде строки </summary>
	std::string to_string()
	{
		return name + " " + surname + " " + patronymic;
	}

	bool operator ==(const Student& student) const
	{
		bool res = name == student.name;
		res = res && surname == student.surname;
		res = res && patronymic == student.patronymic;
		res = res && unique_id == student.unique_id;
		return res;
	}

	bool operator !=(const Student& student) const { return !operator==(student); }

	Student& operator=(const Student& student)
	{
		//Проверяем на самоприсваивание
		if (this == &student)
			return *this;

		name = student.name;
		surname = student.surname;
		patronymic = student.patronymic;

		return *this;
	}
};

int Student::UNIQUE_ID = 0;

/// <summary>
/// Учебная группа
/// </summary>
class StudyGroup
{
private:
	//Список студентов этой группы
	std::list <Student*> students;
	std::string groupNum;
public:
	StudyGroup() :groupNum("A0001")
	{

	}
	
	StudyGroup(std::string groupNum) :groupNum(groupNum)
	{
		
	}
	
	/// <summary> Возвращает список студентов этой группы в виде строки </summary>
	std::string GetAllStudentsLikeString()
	{
		std::string output = "";
		for (Student* s : students) output = output + s->to_string() + "\n";
		return output;
	}

	/// <summary>
	/// Прикрепляет студента к группе
	/// </summary>
	void PinStudent(Student &student)
	{
		students.push_back(&student);
		students.unique();
	}

	/// <summary>
	/// Открепляет студента от группы
	/// </summary>
	void UnPinStudent(Student& student)
	{
		students.remove(&student);
	}

	/// <summary>
	/// Устанавливает номер группы
	/// </summary>
	std::string set_groupNum(std::string groupNum) { this->groupNum = groupNum; }

	/// <summary>
	/// Возвращает номер группы
	/// </summary>
	std::string get_groupNum() { return groupNum; }
};

/// <summary>
/// Класс описывающий учебный предмет
/// </summary>
class Subject
{
private:
	//Название дисциплины
	std::string discipline;
	std::string teacher_fio;
	std::string time;
	//Для какой учебной группы
	StudyGroup* subjectStudyGroup;

public:
	Subject() : discipline("standart_discipline"), teacher_fio("Ivanov Ivan"), time("8:30"), subjectStudyGroup(nullptr)
	{

	}

	Subject(std::string discipline, std::string teacher_fio, std::string time, StudyGroup* group) : discipline(discipline),
		teacher_fio(teacher_fio), time(time), subjectStudyGroup(group)
	{

	}

	/// <summary> Конструктор копирования Subject </summary>
	Subject(const Subject& subject) : discipline(subject.discipline),
		teacher_fio(subject.teacher_fio), time(subject.time), subjectStudyGroup(subject.subjectStudyGroup)
	{

	}

	/// <summary> Устанавливает время предмета </summary>
	void set_time(std::string time) { this->time = time; }

	/// <summary> Устанавливает дисциплину предмета </summary>
	void set_discipline(std::string discipline) { this->discipline = discipline; }

	/// <summary> Устанавливает ФИО преподавателя предмета </summary>
	void set_teacher_fio(std::string time) { this->teacher_fio = teacher_fio; }

	/// <summary> Устанавливает группу для которого предмет </summary>
	void set_subjectStudyGroup(StudyGroup* group) { subjectStudyGroup = group; }

	/// <summary>
	/// Возвращает данные предмета в виде строки
	/// </summary>
	std::string to_string()
	{
		return "Время: " + time + " Группа: " + subjectStudyGroup->get_groupNum() + " " + discipline + " " + teacher_fio;
	}

	/// <summary>
	/// Возвращает номер группы, для которой предназначен предмет
	/// </summary>
	std::string get_studyGroupNum() { return subjectStudyGroup->get_groupNum(); }
};

/// <summary>
/// Класс хранящий учебное расписание
/// </summary>
class Schedule
{
private:
	std::list <Subject*> subjects;

public:
	Schedule() {}

	/// <summary>
	/// Добавляет предмет в учебное расписание
	/// </summary>
	void AddSubject(Subject& subject)
	{
		subjects.push_back(&subject);
	}

	/// <summary>
	/// Удаляет предмет из учебного расписания
	/// </summary>
	void RemoveSubject(Subject& subject)
	{
		subjects.remove(&subject);
	}

	/// <summary>
	/// Возвращает расписание по группе в виде строки
	/// </summary>
	std::string GetStudyGroupScheduleLikeString(std::string groupNum)
	{
		std::string output = "";
		for (Subject* s : subjects)
		{
			if (s->get_studyGroupNum() == groupNum)
				output = output + s->to_string() + "\n";
		}
		return output;
	}

	std::string to_string()
	{
		std::string output = "";
		for (Subject* s : subjects)
		{
			output = output + s->to_string() + "\n";
		}
		return output;
	}
};
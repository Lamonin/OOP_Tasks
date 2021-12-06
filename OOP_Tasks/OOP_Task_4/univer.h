#pragma once
#include <list>
#include <string>

/// <summary> ����� ����������� �������� </summary>
class Student
{
private:
	
	int unique_id; //���������� ������������� ��������
	std::string name; //���
	std::string surname; //�������
	std::string patronymic; //��������

public:
	static int UNIQUE_ID;
	/// <summary> ������� �� ������������ ����������� </summary>
	Student():name("Ivan"), surname("Ivanov")
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> ������� � ���������� ������, �������� � ��������� </summary>
	Student(std::string name, std::string surname, std::string patronymic = "") :name(name),
		surname(surname), patronymic(patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> �������� ������ student � ������� ����� ������ ������ Student </summary>
	Student(const Student& student) :name(student.name),
		surname(student.surname), patronymic(student.patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> ���������� ��� �������� </summary>
	std::string get_name() { return name; }

	/// <summary> ���������� ������� �������� </summary>
	std::string get_surname() { return surname; }

	/// <summary> ���������� �������� �������� </summary>
	std::string get_patronymic() { return patronymic; }

	/// <summary> ���������� ������ �������� � ���� ������ </summary>
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
		//��������� �� ����������������
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
/// ������� ������
/// </summary>
class StudyGroup
{
private:
	//������ ��������� ���� ������
	std::list <Student*> students;
	std::string groupNum;
public:
	StudyGroup() :groupNum("A0001")
	{

	}
	
	StudyGroup(std::string groupNum) :groupNum(groupNum)
	{
		
	}
	
	/// <summary> ���������� ������ ��������� ���� ������ � ���� ������ </summary>
	std::string GetAllStudentsLikeString()
	{
		std::string output = "";
		for (Student* s : students) output = output + s->to_string() + "\n";
		return output;
	}

	/// <summary>
	/// ����������� �������� � ������
	/// </summary>
	void PinStudent(Student &student)
	{
		students.push_back(&student);
		students.unique();
	}

	/// <summary>
	/// ���������� �������� �� ������
	/// </summary>
	void UnPinStudent(Student& student)
	{
		students.remove(&student);
	}

	/// <summary>
	/// ������������� ����� ������
	/// </summary>
	std::string set_groupNum(std::string groupNum) { this->groupNum = groupNum; }

	/// <summary>
	/// ���������� ����� ������
	/// </summary>
	std::string get_groupNum() { return groupNum; }
};

/// <summary>
/// ����� ����������� ������� �������
/// </summary>
class Subject
{
private:
	//�������� ����������
	std::string discipline;
	std::string teacher_fio;
	std::string time;
	//��� ����� ������� ������
	StudyGroup* subjectStudyGroup;

public:
	Subject() : discipline("standart_discipline"), teacher_fio("Ivanov Ivan"), time("8:30"), subjectStudyGroup(nullptr)
	{

	}

	Subject(std::string discipline, std::string teacher_fio, std::string time, StudyGroup* group) : discipline(discipline),
		teacher_fio(teacher_fio), time(time), subjectStudyGroup(group)
	{

	}

	/// <summary> ����������� ����������� Subject </summary>
	Subject(const Subject& subject) : discipline(subject.discipline),
		teacher_fio(subject.teacher_fio), time(subject.time), subjectStudyGroup(subject.subjectStudyGroup)
	{

	}

	/// <summary> ������������� ����� �������� </summary>
	void set_time(std::string time) { this->time = time; }

	/// <summary> ������������� ���������� �������� </summary>
	void set_discipline(std::string discipline) { this->discipline = discipline; }

	/// <summary> ������������� ��� ������������� �������� </summary>
	void set_teacher_fio(std::string time) { this->teacher_fio = teacher_fio; }

	/// <summary> ������������� ������ ��� �������� ������� </summary>
	void set_subjectStudyGroup(StudyGroup* group) { subjectStudyGroup = group; }

	/// <summary>
	/// ���������� ������ �������� � ���� ������
	/// </summary>
	std::string to_string()
	{
		return "�����: " + time + " ������: " + subjectStudyGroup->get_groupNum() + " " + discipline + " " + teacher_fio;
	}

	/// <summary>
	/// ���������� ����� ������, ��� ������� ������������ �������
	/// </summary>
	std::string get_studyGroupNum() { return subjectStudyGroup->get_groupNum(); }
};

/// <summary>
/// ����� �������� ������� ����������
/// </summary>
class Schedule
{
private:
	std::list <Subject*> subjects;

public:
	Schedule() {}

	/// <summary>
	/// ��������� ������� � ������� ����������
	/// </summary>
	void AddSubject(Subject& subject)
	{
		subjects.push_back(&subject);
	}

	/// <summary>
	/// ������� ������� �� �������� ����������
	/// </summary>
	void RemoveSubject(Subject& subject)
	{
		subjects.remove(&subject);
	}

	/// <summary>
	/// ���������� ���������� �� ������ � ���� ������
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
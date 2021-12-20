#pragma once
#include <list>
#include <string>

class Person
{
protected:
	std::string name; //���
	std::string surname; //�������
	std::string patronymic; //��������

public:
	/// <summary> Person �� ������������ ����������� </summary>
	Person() :name("Ivan"), surname("Ivanov")
	{
	}

	/// <summary> Person � ���������� ������, �������� � ��������� </summary>
	Person( std::string surname, std::string name, std::string patronymic = "") :name(name),
		surname(surname), patronymic(patronymic)
	{
	}

	/// <summary> ���������� ��� Person </summary>
	std::string GetName() { return name; }

	/// <summary> ���������� ������� Person </summary>
	std::string GetSurname() { return surname; }

	/// <summary> ���������� �������� Person </summary>
	std::string GetPatronymic() { return patronymic; }

	virtual std::string to_string()
	{
		return surname + " " + name + " " + patronymic;
	}
};

class Teacher : public Person
{
private:
	std::string discipline;

public:
	Teacher():Person()
	{

	}

	Teacher(std::string surname, std::string name,  std::string patronymic = "") :Person(surname, name, patronymic)
	{

	}

	std::string to_string() override
	{
		return Person::to_string() + " " + discipline;
	}

	void SetDiscipline(std::string discipline) { this->discipline = discipline; }

	std::string GetDiscipline() { return discipline; }
};

/// <summary> ����� ����������� �������� </summary>
class Student: public Person
{
private:
	int unique_id; //���������� ������������� ��������

public:
	static int UNIQUE_ID;
	/// <summary> ������� �� ������������ ����������� </summary>
	Student():Person()
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> ������� � ���������� ������, �������� � ��������� </summary>
	Student(std::string surname, std::string name,  std::string patronymic = "") :Person(surname, name,  patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> �������� ������ student � ������� ����� ������ ������ Student </summary>
	Student(const Student& student) :Person(student.surname, student.name,  student.patronymic)
	{
		UNIQUE_ID++;
		unique_id = UNIQUE_ID;
	}

	/// <summary> ���������� ������ �������� � ���� ������ </summary>
	std::string to_string() override
	{
		return std::to_string(unique_id) + " " + Person::to_string();
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

template <class T>
class UniverPersonGroup
{
private:
	std::list <T*> members;
public:
	void PinPerson(T &person)
	{
		members.push_back(&person);
		members.unique();
	}

	void UnPinPerson(T &person)
	{
		members.remove(&person);
	}

	std::string to_string()
	{
		std::string output = "";
		for (T* s : members) output = output + s->to_string() + "\n";
		return output;
	}
};

/// <summary> ������� ������ </summary>
class StudyGroup
{
private:
	//������ ��������� ���� ������
	UniverPersonGroup<Student> students;
	std::string groupNum;
public:
	StudyGroup() :groupNum("A0001")
	{

	}
	
	StudyGroup(std::string groupNum) :groupNum(groupNum)
	{
		
	}
	
	/// <summary> ���������� ������ ��������� ���� ������ � ���� ������ </summary>
	std::string GetAllStudentsAsString()
	{
		return students.to_string();
	}

	/// <summary> ����������� �������� � ������ </summary>
	void PinStudent(Student &student)
	{
		students.PinPerson(student);
	}

	/// <summary> ���������� �������� �� ������ </summary>
	void UnPinStudent(Student& student)
	{
		students.UnPinPerson(student);
	}

	/// <summary> ������������� ����� ������ </summary>
	void set_groupNum(std::string groupNum) { this->groupNum = groupNum; }

	/// <summary> ���������� ����� ������ </summary>
	std::string get_groupNum() { return groupNum; }
};

class AllSubjectTeachers
{
private:
	UniverPersonGroup<Teacher> teachers;
	std::string subjectName;
public:
	void PinTeacher(Teacher& teacher)
	{
		teachers.PinPerson(teacher);
	}

	void UnPinTeacher(Teacher& teacher)
	{
		teachers.UnPinPerson(teacher);
	}

	std::string GetAllTeachersAsString()
	{
		return teachers.to_string();
	}

	std::string get_subjectName() { return subjectName; }
	void set_subjectName(std::string subjectName) { this->subjectName = subjectName; }
};

/// <summary> ����� ����������� ������� ������� </summary>
class Subject
{
private:
	//�������� ����������
	std::string discipline;
	std::string time;
	Teacher _teacher;
	//��� ����� ������� ������
	StudyGroup* subjectStudyGroup;

public:
	Subject() : discipline("standart_discipline"), time("8:30"), subjectStudyGroup(nullptr)
	{
		
	}

	Subject(std::string discipline, Teacher teacher, std::string time, StudyGroup* group) : discipline(discipline),
		_teacher(teacher), time(time), subjectStudyGroup(group)
	{

	}

	/// <summary> ����������� ����������� Subject </summary>
	Subject(const Subject& subject) : discipline(subject.discipline),
		_teacher(subject._teacher), time(subject.time), subjectStudyGroup(subject.subjectStudyGroup)
	{

	}

	/// <summary> ������������� ����� �������� </summary>
	void set_time(std::string time) { this->time = time; }

	/// <summary> ������������� ���������� �������� </summary>
	void set_discipline(std::string discipline) { this->discipline = discipline; }

	/// <summary> ������������� ������������� �������� </summary>
	void set_teacher(Teacher teacher) { this->_teacher = teacher; }

	/// <summary> ������������� ������ ��� ������� ������� </summary>
	void set_subjectStudyGroup(StudyGroup* group) { subjectStudyGroup = group; }

	/// <summary> ���������� ������ �������� � ���� ������ </summary>
	std::string to_string()
	{
		return "�����: " + time + " ������: " + subjectStudyGroup->get_groupNum() + " " + discipline + " " + _teacher.to_string();
	}

	/// <summary>
	/// ���������� ����� ������, ��� ������� ������������ �������
	/// </summary>
	std::string get_studyGroupNum() { return subjectStudyGroup->get_groupNum(); }
};

/// <summary> ����� �������� ������� ���������� </summary>
class Schedule
{
private:
	std::list <Subject*> subjects;

public:
	Schedule() {}

	/// <summary> ��������� ������� � ������� ���������� </summary>
	void AddSubject(Subject& subject)
	{
		subjects.push_back(&subject);
	}

	/// <summary> ������� ������� �� �������� ���������� </summary>
	void RemoveSubject(Subject& subject)
	{
		subjects.remove(&subject);
	}

	/// <summary> ���������� ���������� �� ������ � ���� ������ </summary>
	std::string GetStudyGroupScheduleAsString(std::string groupNum)
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
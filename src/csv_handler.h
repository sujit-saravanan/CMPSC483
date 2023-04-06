#pragma once
#include "rapidcsv.h"
#include "magic_enum.h"

// In order to add a new major, just put the same name you have in the csv here and the code will take care of the rest
enum class StudentMajorTypes {
        BME,
        CMPEN,
        CMPSC,
        DS,
        ED,
        EE,
        EGEE,
        ESC,
        IE,
        MATSE,
        ME,
};

struct StudentData {
        StudentMajorTypes m_major;
        std::string m_comment;
        std::string m_project_id;
        std::string m_last_name;
        std::string m_first_name;
        std::string m_campus_id;
        bool m_nda;
        bool m_ip;
        bool m_on_campus;
};
struct ProjectData {
        std::vector<StudentMajorTypes> m_third_preferences;
        std::string                    m_course_time;
        std::string                    m_course_name;
        std::string                    m_company_name;
        std::string                    m_project_title;
        StudentMajorTypes              m_first_preference{StudentMajorTypes::BME};
        StudentMajorTypes              m_second_preference{StudentMajorTypes::BME};
        bool                           m_confidentiality{false};
        bool                           m_ip{false};
        bool                           m_physical_prototype{false};
};




class ProjectDataHandler {
public:
        explicit ProjectDataHandler(const char *csv_filepath) noexcept;
        ~ProjectDataHandler() = default;
        
public:
        void parse(const char* csv_filepath) noexcept;
        std::unordered_map<std::string, ProjectData>& projectsMap();
        
private:
        std::unordered_map<std::string, ProjectData> m_projects_map;
};




class StudentDataHandler {
public:
        explicit StudentDataHandler(const char *csv_filepath) noexcept;
        ~StudentDataHandler() = default;
        
public:
        void parse(const char* csv_filepath) noexcept;
        void parse(const std::string &body) noexcept;
        std::unordered_map<std::string, StudentData> &studentsMap();
        std::unordered_map<std::string, std::vector<std::string>> &projectStudentsMap();
private:
        std::unordered_map<std::string, StudentData> m_students_map;
        std::unordered_map<std::string, std::vector<std::string>> m_project_students_map;
};




class InstructorDataHandler{
public:
        explicit InstructorDataHandler(const char *csv_filepath) noexcept;
        ~InstructorDataHandler() = default;
        
public:
        void parse(const char* csv_filepath) noexcept;
        std::unordered_map<std::string, std::vector<std::string>> &instructorProjectsMap();
        
private:
        std::unordered_map<std::string, std::vector<std::string>> m_instructor_projects_map;
};




class CsvHandler {
public:
        CsvHandler(ProjectDataHandler &project_data, StudentDataHandler &student_data, InstructorDataHandler &instructor_data);
        ~CsvHandler() = default;
        
public:
        ProjectDataHandler&    projectData();
        StudentDataHandler&    studentData();
        InstructorDataHandler& instructorData();
        std::string pretty_format();
        std::string json_format();
        std::string simple_format();

private:
        ProjectDataHandler    &m_project_data;
        StudentDataHandler    &m_student_data;
        InstructorDataHandler &m_instructor_data;
};
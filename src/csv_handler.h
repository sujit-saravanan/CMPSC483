#pragma once
#include "rapidcsv.h"
#include "magic_enum.h"
#include <unordered_map>

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
        std::string       m_comment;
        std::string       m_project_id;
        std::string       m_last_name;
        std::string       m_first_name;
        std::string       m_campus_id;
        bool              m_nda;
        bool              m_ip;
        bool              m_on_campus;
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
        void parse(const char* csv_filepath) noexcept; // Parses a csv into main memory
        void parse(const std::string &body) noexcept;
        std::unordered_map<std::string, ProjectData>& projectsMap(); // Used to access the private m_projects_map
        
private:
        std::unordered_map<std::string, ProjectData> m_projects_map; // Every project has an id, this maps that id to a ProjectData struct
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
        std::unordered_map<std::string, StudentData> m_students_map; // Maps a student id to a StudentData struct
        std::unordered_map<std::string, std::vector<std::string>> m_project_students_map; // Maps a project id to a student
};



class InstructorDataHandler{
public:
        explicit InstructorDataHandler(const char *csv_filepath) noexcept;
        ~InstructorDataHandler() = default;
        
public:
        void parse(const char* csv_filepath) noexcept;
        void parse(const std::string &body) noexcept;
        
        std::unordered_map<std::string, std::vector<std::string>> &instructorProjectsMap();
        
private:
        std::unordered_map<std::string, std::vector<std::string>> m_instructor_projects_map; // Maps an instructor name to a project id
};



enum class ProjectHealth {
        dangerous,
        ok,
        good
};

class CsvHandler {
public:
        CsvHandler(ProjectDataHandler &project_data, StudentDataHandler &student_data, InstructorDataHandler &instructor_data, const char* unassigned_students_csv_filepath);
        ~CsvHandler() = default;
        
private:
        ProjectHealth rateHealth(const ProjectData &project_data, const std::vector<std::string> &students);
        
public:
        ProjectDataHandler&    projectData();
        StudentDataHandler&    studentData();
        InstructorDataHandler& instructorData();
        
        std::string json_format();
        
        void unassign_student(const std::string &instructor_name, const std::string &project_id, const std::string &student_id);
        void assign_student(const std::string &instructor_name, const std::string &project_id, const std::string &student_id);
        
        void parse(const std::string &body) noexcept;
        std::string export_csv();

private:
        ProjectDataHandler    &m_project_data;
        StudentDataHandler    &m_student_data;
        InstructorDataHandler &m_instructor_data;
        std::vector<StudentData> m_unnasigned_students;
};
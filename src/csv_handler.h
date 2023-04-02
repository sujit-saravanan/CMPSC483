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

struct ProjectData {
        std::vector<StudentMajorTypes> m_third_preferences;
        std::string                    m_course_time;
        std::string                    m_course_name;
        std::string_view               m_company_name;
        std::string_view               m_project_title;
        StudentMajorTypes              m_first_preference{StudentMajorTypes::BME};
        StudentMajorTypes              m_second_preference{StudentMajorTypes::BME};
        bool                           m_confidentiality{false};
        bool                           m_ip{false};
        bool                           m_physical_prototype{false};
};

struct ProjectDataParser {
        explicit ProjectDataParser(const char *csv_filepath) noexcept;
        ~ProjectDataParser() = default;
        
        std::unordered_map<std::string, ProjectData> m_projects_map;
};

struct StudentData {
        StudentMajorTypes m_major;
        std::string m_comments;
        bool m_nda;
        bool m_ip;
        bool m_campus_id;
        std::string m_last_name;
        std::string m_first_name;
        std::string m_on_campus;
};
struct StudentDataParser {
        explicit StudentDataParser(const char *csv_filepath) noexcept;
        ~StudentDataParser() = default;
        
        std::unordered_map<std::string, StudentData> m_students_map;
        std::unordered_map<std::string, std::vector<std::string>> m_project_students_map;
};
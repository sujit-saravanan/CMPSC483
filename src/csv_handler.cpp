#include "csv_handler.h"
ProjectDataParser::ProjectDataParser(const char *csv_filepath) noexcept {
        auto projects = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));
        
        size_t m_count = projects.GetRowCount();
        
        std::vector<std::string> project_ids    = projects.GetColumn<std::string>("ProjectID");
        std::vector<std::string> company_names  = projects.GetColumn<std::string>("CompanyName");
        std::vector<std::string> project_titles = projects.GetColumn<std::string>("ProjectTitle");
        
        std::vector<std::array<int, magic_enum::enum_count<StudentMajorTypes>()>> major_preferences;
        for (int i = 0; i < m_count; i++) {
                std::array<int, magic_enum::enum_count<StudentMajorTypes>()> preferences{};
                for (int j = 0; j < magic_enum::enum_count<StudentMajorTypes>(); j++)
                        preferences[j] = projects.GetCell<int>(std::string(magic_enum::enum_name((StudentMajorTypes)j)), i);
                major_preferences.push_back(preferences);
        }
        
        std::vector<int> confidentialities   = projects.GetColumn<int>("Confidentiality");
        std::vector<int> ips                 = projects.GetColumn<int>("IP");
        std::vector<std::string> course_times        = projects.GetColumn<std::string>("CourseTime");
        std::vector<std::string> course_names        = projects.GetColumn<std::string>("CourseName");
        std::vector<int> physical_prototypes = projects.GetColumn<int>("PhysicalPrototype");
        
        projects.Clear();
        
        for (int i = 0; i < m_count; i++) {
                ProjectData data;
                data.m_course_time        = course_times[i];
                data.m_course_name        = course_names[i];
                data.m_company_name       = company_names[i];
                data.m_project_title      = project_titles[i];
                data.m_confidentiality    = confidentialities[i];
                data.m_ip                 = ips[i];
                data.m_physical_prototype = physical_prototypes[i];
                
                for (int major = 0; major < magic_enum::enum_count<StudentMajorTypes>(); major++){
                        int rank = major_preferences[i][major];
                        switch (rank) {
                                case 0: continue;
                                case 1: data.m_first_preference = static_cast<StudentMajorTypes>(major); break;
                                case 2: data.m_second_preference = static_cast<StudentMajorTypes>(major); break;
                                case 3: data.m_third_preferences.push_back(static_cast<StudentMajorTypes>(major)); break;
                                default: ERROR("INVALID RANK: RANK SHOULD BE 3 OR BELOW, (%s, %s)", std::string(data.m_project_title).c_str(), std::string(magic_enum::enum_name(static_cast<StudentMajorTypes>(major))).c_str()); break;
                        }
                }
                
                m_projects_map[project_ids[i]] = data;
        }
        for (const auto& title : m_projects_map){
                std::cout << title.first << ": " << title.second.m_project_title << "\n";
        }
}
StudentDataParser::StudentDataParser(const char *csv_filepath) noexcept {
        auto students = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));
        
        std::vector<StudentMajorTypes> majors(students.GetRowCount());
        
        for (int i = 0; const auto& major : students.GetColumn<std::string>("Major"))
                majors[i] = magic_enum::enum_cast<StudentMajorTypes>(major).value();
        
        std::vector<std::string> project_ids = students.GetColumn<std::string>("ProjectID");
        std::vector<std::string> comments    = students.GetColumn<std::string>("Comments");
        std::vector<int>         ndas        = students.GetColumn<int>("Student_NDA");
        std::vector<int>         ips         = students.GetColumn<int>("Student_IP");
        std::vector<std::string> campus_ids  = students.GetColumn<std::string>("campus_id");
        std::vector<std::string> last_names  = students.GetColumn<std::string>("last_name");
        std::vector<std::string> first_names = students.GetColumn<std::string>("first_name");
        std::vector<std::string> on_campuss  = students.GetColumn<std::string>("OnCampus");
        
        
        for (int i = 0; i < students.GetRowCount(); i++){
                m_students_map[campus_ids[i]] = {};
                m_student_project_map[campus_ids[i]] = project_ids[i];
                m_student_project_map[campus_ids[i]] = project_ids[i];
                m_project_students_map[project_ids[i]].push_back(campus_ids[i]);
                std::cout << first_names[i] << " " << last_names[i] << "(" << campus_ids[i] << "): " << project_ids[i] << "\n";
        }
}

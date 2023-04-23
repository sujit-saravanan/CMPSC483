#include "csv_handler.h"
#include "json.h"
using namespace nlohmann;

ProjectDataHandler::ProjectDataHandler(const char *csv_filepath) noexcept {
        parse(csv_filepath);
}
void ProjectDataHandler::parse(const char *csv_filepath) noexcept {
        auto projects = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));
        
        size_t m_count = projects.GetRowCount();
        
        std::vector<std::string> project_ids = projects.GetColumn<std::string>("ProjectID");
        std::vector<std::string> company_names = projects.GetColumn<std::string>("CompanyName");
        std::vector<std::string> project_titles = projects.GetColumn<std::string>("ProjectTitle");
        
        std::vector<std::array<int, magic_enum::enum_count<StudentMajorTypes>()>> major_preferences;
        for (int i = 0; i < m_count; i++) {
                std::array<int, magic_enum::enum_count<StudentMajorTypes>()> preferences{};
                for (int j = 0; j < magic_enum::enum_count<StudentMajorTypes>(); j++)
                        preferences[j] = projects.GetCell<int>(std::string(magic_enum::enum_name((StudentMajorTypes) j)), i);
                major_preferences.push_back(preferences);
        }
        
        std::vector<std::string> course_times = projects.GetColumn<std::string>("CourseTime");
        std::vector<std::string> course_names = projects.GetColumn<std::string>("CourseName");
        std::vector<int> confidentialities = projects.GetColumn<int>("Confidentiality");
        std::vector<int> ips = projects.GetColumn<int>("IP");
        std::vector<int> physical_prototypes = projects.GetColumn<int>("PhysicalPrototype");
        
        projects.Clear();
        
        for (int i = 0; i < m_count; i++) {
                ProjectData data = {
                        .m_course_time        = course_times[i],
                        .m_course_name        = course_names[i],
                        .m_company_name       = company_names[i],
                        .m_project_title      = project_titles[i],
                        .m_confidentiality    = static_cast<bool>(confidentialities[i]),
                        .m_ip                 = static_cast<bool>(ips[i]),
                        .m_physical_prototype = static_cast<bool>(physical_prototypes[i]),
                };
                
                for (int major = 0; major < magic_enum::enum_count<StudentMajorTypes>(); major++) {
                        int rank = major_preferences[i][major];
                        switch (rank) {
                                case 0:
                                        continue;
                                case 1:
                                        data.m_first_preference = static_cast<StudentMajorTypes>(major);
                                        break;
                                case 2:
                                        data.m_second_preference = static_cast<StudentMajorTypes>(major);
                                        break;
                                case 3:
                                        data.m_third_preferences.push_back(static_cast<StudentMajorTypes>(major));
                                        break;
                                default:
                                        ERROR("INVALID RANK: RANK SHOULD BE 3 OR BELOW, (%s, %s)", std::string(data.m_project_title).c_str(), std::string(magic_enum::enum_name(static_cast<StudentMajorTypes>(major))).c_str());
                                        break;
                        }
                }
                
                m_projects_map[project_ids[i]] = data;
        }
        
}
std::unordered_map<std::string, ProjectData> &ProjectDataHandler::projectsMap() {
        return m_projects_map;
}

StudentDataHandler::StudentDataHandler(const char *csv_filepath) noexcept {
        parse(csv_filepath);
}
void StudentDataHandler::parse(const char *csv_filepath) noexcept {
        auto students = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));
        
        std::vector<StudentMajorTypes> majors(students.GetRowCount());
        
        for (int i = 0; const auto &major: students.GetColumn<std::string>("Major"))
                majors[i++] = magic_enum::enum_cast<StudentMajorTypes>(major).value();
        
        auto project_ids = students.GetColumn<std::string>("ProjectID");
        auto comments = students.GetColumn<std::string>("Comments");
        auto campus_ids = students.GetColumn<std::string>("campus_id");
        auto last_names = students.GetColumn<std::string>("last_name");
        auto first_names = students.GetColumn<std::string>("first_name");
        auto ndas = students.GetColumn<int>("Student_NDA");
        auto ips = students.GetColumn<int>("Student_IP");
        auto on_campus = students.GetColumn<std::string>("OnCampus");
        std::vector<bool> on_campus_bools;
        on_campus_bools.reserve(on_campus.size());
        
        for (const auto &str: on_campus) {
                if (str == "Yes")
                        on_campus_bools.push_back("Yes");
                else
                        on_campus_bools.push_back("No");
        }
        
        std::unordered_map<std::string, std::vector<std::string>> project_students_map;
        for (int i = 0; i < students.GetRowCount(); i++) {
                StudentData data = {
                        .m_major      = majors[i],
                        .m_comment    = comments[i],
                        .m_project_id = project_ids[i],
                        .m_last_name  = last_names[i],
                        .m_first_name = first_names[i],
                        .m_campus_id  = campus_ids[i],
                        .m_nda        = static_cast<bool>(ndas[i]),
                        .m_ip         = static_cast<bool>(ips[i]),
                        .m_on_campus  = on_campus_bools[i],
                };
                
                m_students_map[campus_ids[i]] = data;
                project_students_map[project_ids[i]].push_back(campus_ids[i]);
        }
        m_project_students_map = project_students_map;
}
void StudentDataHandler::parse(const std::string &body) noexcept {
        std::stringstream sstream(body);
        rapidcsv::Document students(sstream, rapidcsv::LabelParams(0, -1));
        
        std::vector<StudentMajorTypes> majors(students.GetRowCount());
        
        for (int i = 0; const auto &major: students.GetColumn<std::string>("Major"))
                majors[i++] = magic_enum::enum_cast<StudentMajorTypes>(major).value();
        
        auto project_ids = students.GetColumn<std::string>("ProjectID");
        auto comments = students.GetColumn<std::string>("Comments");
        auto campus_ids = students.GetColumn<std::string>("campus_id");
        auto last_names = students.GetColumn<std::string>("last_name");
        auto first_names = students.GetColumn<std::string>("first_name");
        auto ndas = students.GetColumn<int>("Student_NDA");
        auto ips = students.GetColumn<int>("Student_IP");
        auto on_campus = students.GetColumn<std::string>("OnCampus");
        std::vector<bool> on_campus_bools;
        on_campus_bools.reserve(on_campus.size());
        
        for (const auto &str: on_campus) {
                if (str == "Yes")
                        on_campus_bools.push_back("Yes");
                else
                        on_campus_bools.push_back("No");
        }
        
        std::unordered_map<std::string, std::vector<std::string>> project_students_map;
        for (int i = 0; i < students.GetRowCount(); i++) {
                StudentData data = {
                        .m_major      = majors[i],
                        .m_comment    = comments[i],
                        .m_project_id = project_ids[i],
                        .m_last_name  = last_names[i],
                        .m_first_name = first_names[i],
                        .m_campus_id  = campus_ids[i],
                        .m_nda        = static_cast<bool>(ndas[i]),
                        .m_ip         = static_cast<bool>(ips[i]),
                        .m_on_campus  = on_campus_bools[i],
                };
                
                m_students_map[campus_ids[i]] = data;
                project_students_map[project_ids[i]].push_back(campus_ids[i]);
        }
        m_project_students_map = project_students_map;
}
std::unordered_map<std::string, StudentData> &StudentDataHandler::studentsMap() {
        return m_students_map;
}
std::unordered_map<std::string, std::vector<std::string>> &StudentDataHandler::projectStudentsMap() {
        return m_project_students_map;
}

InstructorDataHandler::InstructorDataHandler(const char *csv_filepath) noexcept {
        parse(csv_filepath);
}
void InstructorDataHandler::parse(const char *csv_filepath) noexcept {
        auto instructors = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));
        
        std::vector<std::string> instructor_names = instructors.GetColumn<std::string>("InstructorName");
        std::vector<std::string> project_ids = instructors.GetColumn<std::string>("ProjectID");
        std::unordered_map<std::string, std::vector<std::string>> instructor_projects_map;
        
        
        for (int i = 0; i < instructors.GetRowCount(); i++)
                instructor_projects_map[instructor_names[i]].push_back(project_ids[i]);
        m_instructor_projects_map = instructor_projects_map;
}
std::unordered_map<std::string, std::vector<std::string>> &InstructorDataHandler::instructorProjectsMap() { return m_instructor_projects_map; }

CsvHandler::CsvHandler(ProjectDataHandler &project_data, StudentDataHandler &student_data, InstructorDataHandler &instructor_data, const char *unassigned_students_csv_filepath)
        : m_project_data(project_data), m_student_data(student_data), m_instructor_data(instructor_data) {
        auto students = rapidcsv::Document(unassigned_students_csv_filepath, rapidcsv::LabelParams(0, -1));
        std::vector<std::string> first_names = students.GetColumn<std::string>("First Name");
        std::vector<std::string> last_names = students.GetColumn<std::string>("Last Name");
        std::vector<std::string> campus_ids = students.GetColumn<std::string>("E-mail Address");
        for (auto &email: campus_ids) {
                size_t at_location = email.find_first_of('@');
                email.resize(at_location);
//                std::cout << email << "\n";
        }
        for (const auto &id: campus_ids)
                std::cout << id << "\n";
        std::vector<std::string> courses = students.GetColumn<std::string>("Course");
        std::vector<StudentMajorTypes> majors;
        majors.reserve(courses.size());
        for (const auto &course: courses) {
                size_t gap_location = course.find_first_of(' ');
                auto major = course.substr(0, gap_location);
                
                if (magic_enum::enum_cast<StudentMajorTypes>(major).has_value())
                        majors.push_back(magic_enum::enum_cast<StudentMajorTypes>(major).value());
                else if (major == "EDSGN")
                        majors.push_back(StudentMajorTypes::ED);
        }
        
        std::cout << first_names.size() << "\n";
        std::cout << last_names.size() << "\n";
        std::cout << campus_ids.size() << "\n";
        std::cout << courses.size() << "\n";
        std::cout << majors.size() << "\n";
        
        
        for (int i = 0; i < majors.size(); i++) {
                StudentData data = {
                        .m_major      = majors[i],
                        .m_comment    = "",
                        .m_project_id = "",
                        .m_last_name  = last_names[i],
                        .m_first_name = first_names[i],
                        .m_campus_id  = campus_ids[i],
                        .m_nda        = true,
                        .m_ip         = true,
                        .m_on_campus  = true,
                };
                
                m_unnasigned_students.emplace_back(data);
        }
}
std::string CsvHandler::pretty_format() {
        std::string ret;
        for (const auto &instructor_projects_pair: m_instructor_data.instructorProjectsMap()) {
                ret += instructor_projects_pair.first + ":\n";
                for (const auto &project_id: instructor_projects_pair.second) {
                        ret += "\t" + project_id + ": [";
                        ret += magic_enum::enum_name((m_project_data.projectsMap())[project_id].m_first_preference);
                        ret += ", ";
                        ret += magic_enum::enum_name((m_project_data.projectsMap())[project_id].m_second_preference);
                        ret += ", ";
                        for (const auto &tertiary_preference: (m_project_data.projectsMap())[project_id].m_third_preferences) {
                                ret += magic_enum::enum_name(tertiary_preference);
                                ret += ", ";
                        }
                        ret += "]\n";
                        
                        for (const auto &student_id: (m_student_data.projectStudentsMap())[project_id])
                                ret += "\t\t" + m_student_data.studentsMap()[student_id].m_first_name + " " + m_student_data.studentsMap()[student_id].m_last_name + "(" + student_id + ")" + "\n";
                }
        }
        return ret;
}



ProjectHealth CsvHandler::rateHealth(const ProjectData &project_data, const std::vector<std::string> &students) {
        if (students.size() <= 3)
                return ProjectHealth::dangerous;
        
        int score = 0;
        bool has_primary = false;
        for (const auto &student_id: students) {
                auto student_data = (studentData().studentsMap())[student_id];
                if (student_data.m_major == project_data.m_first_preference) {
                        score += 3;
                        has_primary = true;
                        continue;
                }
                if (student_data.m_major == project_data.m_second_preference) {
                        score += 2;
                        continue;
                }
                for (auto major: project_data.m_third_preferences) {
                        if (student_data.m_major == major) {
                                score += 1;
                                break;
                        }
                }
        }
        
        if (!has_primary)
                return ProjectHealth::dangerous;
        
        if (score < 11)
                return ProjectHealth::ok;
        
        return ProjectHealth::good;
}

std::string CsvHandler::json_format() {
        json ret;
        for (const auto &instructor_projects_pair: m_instructor_data.instructorProjectsMap()) {
                for (const auto &project_id: instructor_projects_pair.second) {
                        auto project_data = (projectData().projectsMap())[project_id];
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["project-title"] = project_data.m_project_title;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["company-name"] = project_data.m_company_name;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["first-preference"] = project_data.m_first_preference;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["second-preference"] = project_data.m_second_preference;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["third-preferences"] = project_data.m_third_preferences;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["nda"] = project_data.m_confidentiality;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["ip"] = project_data.m_ip;
                        ret["Assigned Students"][instructor_projects_pair.first][project_id]["health"] = rateHealth(project_data, (studentData().projectStudentsMap())[project_id]);
                        
                        for (const auto &student_id: (studentData().projectStudentsMap())[project_id]) {
                                auto student_data = (studentData().studentsMap())[student_id];
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["major"] = student_data.m_major;
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["first-name"] = student_data.m_first_name;
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["last-name"] = student_data.m_last_name;
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["nda"] = student_data.m_nda;
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["ip"] = student_data.m_ip;
                                ret["Assigned Students"][instructor_projects_pair.first][project_id]["students"][student_id]["on-campus"] = student_data.m_on_campus;
                        }
                }
        }
        
        for (const auto &student: m_unnasigned_students) {
                ret["Unassigned Students"][student.m_campus_id]["major"] = student.m_major;
                ret["Unassigned Students"][student.m_campus_id]["first-name"] = student.m_first_name;
                ret["Unassigned Students"][student.m_campus_id]["last-name"] = student.m_last_name;
                ret["Unassigned Students"][student.m_campus_id]["nda"] = student.m_nda;
                ret["Unassigned Students"][student.m_campus_id]["ip"] = student.m_ip;
                ret["Unassigned Students"][student.m_campus_id]["on-campus"] = student.m_on_campus;
        }
        return ret.dump(4);
}
std::string CsvHandler::simple_format() {
        std::string ret;
        ret += "Instructor,Project,Students\n";
        for (const auto &instructor_projects_pair: m_instructor_data.instructorProjectsMap()) {
                for (const auto &project_id: instructor_projects_pair.second) {
                        ret += instructor_projects_pair.first + "," + m_project_data.projectsMap()[project_id].m_project_title;
                        ret += ",{";
                        for (const auto &student_id: (m_student_data.projectStudentsMap())[project_id]) {
                                ret += m_student_data.studentsMap()[student_id].m_first_name + " " + m_student_data.studentsMap()[student_id].m_last_name + "(" + student_id + ")" + "     ";
                        }
                        ret += "}\n";
                }
        }
        return ret;
}

ProjectDataHandler &CsvHandler::projectData() { return m_project_data; }
StudentDataHandler &CsvHandler::studentData() { return m_student_data; }
InstructorDataHandler &CsvHandler::instructorData() { return m_instructor_data; }


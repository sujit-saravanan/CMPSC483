#include "server.h"
#include "rapidcsv.h"
#include <magic_enum.hpp>

const char    *HOST = "localhost";
const int32_t PORT  = 8080;


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
    explicit ProjectDataParser(const char *csv_filepath) noexcept {
        auto projects = rapidcsv::Document(csv_filepath, rapidcsv::LabelParams(0, -1));

        m_count = projects.GetRowCount();

        m_project_ids    = projects.GetColumn<std::string>("ProjectID");
        m_company_names  = projects.GetColumn<std::string>("CompanyName");
        m_project_titles = projects.GetColumn<std::string>("ProjectTitle");

        for (int i = 0; i < m_count; i++) {
            std::array<int, magic_enum::enum_count<StudentMajorTypes>()> preferences{};
            for (int j = 0; j < magic_enum::enum_count<StudentMajorTypes>(); j++)
                preferences[j] = projects.GetCell<int>(std::string(magic_enum::enum_name((StudentMajorTypes)j)), i);
            e_major_preferences.push_back(preferences);
        }

        m_confidentialities   = projects.GetColumn<int>("Confidentiality");
        m_ips                 = projects.GetColumn<int>("IP");
        m_course_times        = projects.GetColumn<std::string>("CourseTime");
        m_course_names        = projects.GetColumn<std::string>("CourseName");
        m_physical_prototypes = projects.GetColumn<int>("PhysicalPrototype");

        projects.Clear();
    }

    ~ProjectDataParser() = default;

    std::vector<std::string>                                                  m_project_ids;
    std::vector<std::string>                                                  m_company_names;
    std::vector<std::string>                                                  m_project_titles;
    std::vector<std::array<int, magic_enum::enum_count<StudentMajorTypes>()>> e_major_preferences;
    std::vector<int>                                                          m_confidentialities;
    std::vector<int>                                                          m_ips;
    std::vector<std::string>                                                  m_course_times;
    std::vector<std::string>                                                  m_course_names;
    std::vector<int>                                                          m_physical_prototypes;

    size_t m_count;
};

int main() {
    rapidcsv::Document student_assignments("assets/data/studentAssignments.csv", rapidcsv::LabelParams(0, 0));

    auto project_data = new ProjectDataParser("assets/data/projectsFinal.csv");
    std::unordered_map<std::string, ProjectData> projects_map;

    for (int i = 0; i < project_data->m_count; i++) {
        ProjectData data;
        data.m_course_time        = project_data->m_course_times[i];
        data.m_course_name        = project_data->m_course_names[i];
        data.m_company_name       = project_data->m_company_names[i];
        data.m_project_title      = project_data->m_project_titles[i];
        data.m_confidentiality    = project_data->m_confidentialities[i];
        data.m_ip                 = project_data->m_ips[i];
        data.m_physical_prototype = project_data->m_physical_prototypes[i];

        for (int major = 0; major < magic_enum::enum_count<StudentMajorTypes>(); major++){
            int rank = project_data->e_major_preferences[i][major];
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

        projects_map[project_data->m_project_ids[i]] = data;
    }

    for (const auto& title : projects_map){
        std::cout << title.first << ": " << title.second.m_project_title << "\n";
    }

    delete project_data;

//    auto database = std::make_unique<Database>("example.db");
//    database->table("STUDENTS", {
//            {"ID",      "INT PRIMARY KEY"},
//            {"NAME",    "TEXT"},
//            {"SURNAME", "TEXT"},
//            {"MAJOR",   "CHAR(8)"},
//    });
//
//    database->insert("STUDENTS", "1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0")
//            ->insert("STUDENTS", "2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22")
//            ->insert("STUDENTS", "3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0");

    const char *SUPER_SECRET_NUMBER = "780375235";

    auto server = (new Server())
            ->page("/", "assets/pages/home")
            ->page("/", "assets/styles")
            ->page("/", "assets/fonts")
            ->page("/", "assets/textures")
            ->page("/admin", "assets/pages/admin")
            ->page("/admin", "assets/textures");

    server->get("/log", REQ_RES {
                std::cout << "qowegfhqkwjehf\n\n";
                res.set_content(SUPER_SECRET_NUMBER, "text/json");
            })
            ->get("/test", REQ_RES {
                std::cout << "qowegfhqkwjehf\n\n";
                res.set_content(SUPER_SECRET_NUMBER, "text/json");
            })
            ->get("/export_csv", REQ_RES {
                std::cout << "requested CSV export\n";
                res.set_content("requested CSV export", "text/json");
            })
            ->get("/upload_csv", REQ_RES {
                std::cout << "requested CSV update\n";
                res.set_content("requested CSV update", "text/json");
            });

    server->post("/csv", REQ_RES {
        std::cout << req.body << "\n";
    });


    server->listen(HOST, PORT);
    server->m_server.stop();

    return 0;
}

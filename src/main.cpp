#include "server.h"
#include <unordered_map>
#include "csv_handler.h"


const char *HOST = "localhost";
const int32_t PORT = 8080;

int main() {
        auto project_data = ProjectDataHandler("assets/data/projectsFinal.csv");
        auto student_data = StudentDataHandler("assets/data/studentAssignments.csv");
        auto instructor_data = InstructorDataHandler("assets/data/sectionInfo.csv");
        CsvHandler handler = CsvHandler(project_data, student_data, instructor_data, "assets/data/students without prefs.csv");
        
        auto server = (new Server())
                ->page("/", "assets/pages/home")
                ->page("/home", "assets/pages/home")
                ->page("/admin", "assets/pages/admin")
                ->page("/assignments", "assets/pages/assignments")
                ->page("/shared", "assets/shared");
        
        server->get("/update_csv", REQ_RES {
                        res.set_content("requested CSV update", "text/json");
                })
                ->get("/instructor_project_student_tree_get", REQ_RES {
                        res.set_content(handler.json_format(), "text/csv");
                })
                ->get("/export_csv", REQ_RES {
                        res.set_content(handler.export_csv(), "text/csv");
                });
        
        
        int i = 0;
        const char* test[4] = {"projectsFinal.csv", "sectionInfo.csv", "studentAssignments.csv", "students without prefs.csv"};
        server->post("/csv", REQ_RES {
                        if (i > 3)
                                i=0;
                        
                        switch (i) {
                                case 0:
                                        project_data.parse(req.body);
                                        break;
                                case 1:
                                        instructor_data.parse(req.body);
                                        break;
                                case 2:
                                        student_data.parse(req.body);
                                        break;
                                case 3:
                                        handler.parse(req.body);
                                        break;
                                default:
                                        break;
                        }
                        i++;
                        res.status = 200;
                })
                ->post("/unassign_student", REQ_RES {
                        nlohmann::json request_json = nlohmann::json::parse(req.body);
                        
                        handler.unassign_student(request_json["instructor_name"], request_json["project_id"], request_json["student_id"]);
                        res.status = 200;
                })
                ->post("/assign_student", REQ_RES {
                        nlohmann::json request_json = nlohmann::json::parse(req.body);
                        
                        handler.assign_student(request_json["instructor_name"], request_json["project_id"], request_json["student_id"]);
                        res.status = 200;
                });
        
        
        server->listen(HOST, PORT);
        server->m_server.stop();
        
        return 0;
}

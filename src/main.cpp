#include "server.h"
#include <unordered_map>
#include "csv_handler.h"


const char *HOST = "localhost";
const int32_t PORT = 8080;

int main() {
        auto project_data    = ProjectDataHandler("assets/data/projectsFinal.csv");
        auto student_data    = StudentDataHandler("assets/data/studentAssignments.csv");
        auto instructor_data = InstructorDataHandler("assets/data/sectionInfo.csv");
        CsvHandler handler   = CsvHandler(project_data, student_data, instructor_data, "assets/data/students without prefs.csv");
        std::cout << handler.json_format() << "\n";
        
        auto server = (new Server())
                ->page("/", "assets/pages/home")
                ->page("/home", "assets/pages/home")
                ->page("/admin", "assets/pages/admin")
                ->page("/assignments", "assets/pages/assignments")
                ->page("/shared", "assets/shared");
        
        server->get("/export_csv", REQ_RES {
                        res.set_content("requested CSV export", "text/json");
                })
                ->get("/update_csv", REQ_RES {
                        res.set_content("requested CSV update", "text/json");
                })
                ->get("/simple_csv_get", REQ_RES {
                        res.set_content(handler.simple_format(), "text/csv");
                })
                ->get("/instructor_project_student_tree_get", REQ_RES {
                        res.set_content(handler.json_format(), "text/csv");
                });
        
        
        server->post("/csv", REQ_RES {
                student_data.parse(req.body);
        });
        
        
        server->listen(HOST, PORT);
        server->m_server.stop();
        
        return 0;
}

#include "server.h"
#include <unordered_map>
#include "csv_handler.h"


const char *HOST = "localhost";
const int32_t PORT = 8080;


int main() {
        auto project_data    = ProjectDataHandler("assets/data/projectsFinal.csv");
        auto student_data    = StudentDataHandler("assets/data/studentAssignments.csv");
        auto instructor_data = InstructorDataHandler("assets/data/sectionInfo.csv");
        CsvHandler handler   = CsvHandler(project_data, student_data, instructor_data);
        
        std::cout << handler.simple_format() << "\n";
        
        
        
        const char *SUPER_SECRET_NUMBER = "780375235";
        
        auto server = (new Server())
                ->page("/admin", "assets/pages/admin")
                ->page("/search", "assets/pages/search")
                ->page("/exchange", "assets/pages/exchange")
                ->page("/shared", "assets/shared");
        
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
                ->get("/update_csv", REQ_RES {
                        std::cout << "requested CSV update\n";
                        res.set_content("requested CSV update", "text/json");
                })
                ->get("/simple_csv_get", REQ_RES {
                        std::cout << "requested CSV update\n";
                        res.set_content(handler.simple_format(), "text/csv");
                });
        
        server->post("/csv", REQ_RES {
                student_data.parse(req.body);
        });
        
        
        server->listen(HOST, PORT);
        server->m_server.stop();
        
        return 0;
}

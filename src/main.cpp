#include "server.h"
#include "logger.h"
#include <unordered_map>
#include "csv_handler.h"


const char    *HOST = "localhost";
const int32_t PORT  = 8080;


int main() {
    auto project_data = new ProjectDataParser("assets/data/projectsFinal.csv");
    auto student_data = new StudentDataParser("assets/data/studentAssignments.csv");
    

    

    delete project_data;
    

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

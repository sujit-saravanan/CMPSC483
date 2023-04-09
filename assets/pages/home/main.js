let activeSidebarElement = document.getElementById("sidebar-home-element");

// These three are just debug functions, they can be deleted once querying for completion percentage is finished
function grow(amount){
    let complete_teams_circle = document.getElementById('completed-teams-circle');
    let completed_teams_percentage = parseFloat(complete_teams_circle.children[0].textContent);


    completed_teams_percentage += amount;
    completed_teams_percentage = Math.min(completed_teams_percentage, 100);

    complete_teams_circle.children[0].textContent = completed_teams_percentage.toFixed(2) + "%";
    complete_teams_circle.style.backgroundImage   = "conic-gradient(var(--circle-foreground) " + completed_teams_percentage.toFixed(2) + "%"+ ", var(--circle-background) 0)";
}
function shrink(amount){
    let complete_teams_circle = document.getElementById('completed-teams-circle');
    let completed_teams_percentage = parseFloat(complete_teams_circle.children[0].textContent);


    completed_teams_percentage -= amount;
    completed_teams_percentage = Math.max(completed_teams_percentage, 0);

    complete_teams_circle.children[0].textContent = completed_teams_percentage.toFixed(2) + "%";
    complete_teams_circle.style.backgroundImage   = "conic-gradient(var(--circle-foreground) " + completed_teams_percentage.toFixed(2) + "%"+ ", var(--circle-background) 0)";
}
function testRequest(){
    fetch('/log')
        .then((response) => response.text())
        .then((data) => console.log(data));
}

// Update these two functions to get the info from the server
function getTeamsCompletion(){
    return 10.00;
}
function getAssignedStudentsCompletion(){
    return 0.00
}

// Update this function with the proper html for the three pages
function setContent(currentPage){
    /*
    if (currentPage === "Home"){
        document.getElementById("main").innerHTML=
            "        <div class=\"main-cards\">\n" +
            "\n" +
            "            <div class=\"card\">\n" +
            "                <div class=\"card-header\">\n" +
            "                    <h1>Completed Teams</h1>\n" +
            "                    progress\n" +
            "                    <button onclick=\"grow(5)\">add5</button>\n" +
            "                    <button onclick=\"shrink(5)\">sub5</button>\n" +
            "\n" +
            "                    <button onclick=\"testRequest(5)\">testRequest5</button>\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"circle\" id=\"completed-teams-circle\">\n" +
            "                    <div class=\"inner\"></div>\n" +
            "                </div>\n" +
            "\n" +
            "            </div>\n" +
            "\n" +
            "            <div class=\"card\">\n" +
            "                <div class=\"card-header\">\n" +
            "                    <h1>Assigned Students</h1>\n" +
            "                    progress\n" +
            "                </div>\n" +
            "\n" +
            "                <div class=\"circle\" id=\"assigned-students-circle\">\n" +
            "                    <div class=\"inner\"></div>\n" +
            "                </div>\n" +
            "            </div>\n" +
            "\n" +
            "            <div class=\"card\">\n" +
            "                <div class=\"card-header\">\n" +
            "                    <h1>Student Major Distribution</h1>\n" +
            "                </div>\n" +
            "            </div>\n" +
            "\n" +
            "        </div>"

        let completed_teams_percentage = getTeamsCompletion();
        let assigned_students_percentage = getAssignedStudentsCompletion();

        let complete_teams_circle = document.getElementById('completed-teams-circle');
        let assigned_students_circle = document.getElementById('assigned-students-circle');


        complete_teams_circle.children[0].textContent    = completed_teams_percentage.toFixed(2) + "%";
        assigned_students_circle.children[0].textContent = assigned_students_percentage.toFixed(2) + "%";

        complete_teams_circle.style.backgroundImage    = "conic-gradient(var(--circle-foreground) " + completed_teams_percentage.toFixed(2) + "%"+ ", var(--circle-background) 0)";
        assigned_students_circle.style.backgroundImage = "conic-gradient(var(--circle-foreground) " + assigned_students_percentage.toFixed(2) + "%"+ ", var(--circle-background) 0)";

    }
    if (currentPage === "Assignments"){
        document.getElementById("main").innerHTML="Assignments";
    }
    if (currentPage === "Export"){
        document.getElementById("main").innerHTML="Export";
    }
    */
}


function setActiveSidebarElement(element){
    activeSidebarElement.classList.remove("active");
    activeSidebarElement = element;
    activeSidebarElement.classList.add("active");

    setContent(element.children[1].textContent)
}

setContent("Home");
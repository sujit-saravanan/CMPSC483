const StudentMajorTypes = ["BME", "CMPEN", "CMPSC", "DS", "ED", "EE", "EGEE", "ESC", "IE", "MATSE", "ME"];
async function get_InstructorProjectStudentTree() {
    const res = await fetch("/instructor_project_student_tree_get");
    return await res.json();
}

function YesNo(bool){
    if (bool) return "Yes";
    return "No";
}

//<div class="dropdown">
//     <button class="dropbtn">Dropdown
//       <i class="fa fa-caret-down"></i>
//     </button>
//     <div class="dropdown-content">
//       <a href="#">Link 1</a>
//       <a href="#">Link 2</a>
//       <a href="#">Link 3</a>
//     </div>
//   </div>

async function createInstructorDropDown() {
    const data = await get_InstructorProjectStudentTree();
    let navbar = document.getElementById("navbar");

    let dropdown = document.createElement("div");
    dropdown.classList.add("dropdown");

    let dropbtn = document.createElement("button");
    dropbtn.classList.add("dropbtn");
    dropbtn.appendChild(document.createTextNode("Instructors"));
    dropdown.appendChild(dropbtn);

    let dropdown_content = document.createElement("div");
    dropdown_content.classList.add("dropdown-content");
    let all_anchor = document.createElement("a");
    all_anchor.appendChild(document.createTextNode("Global View"));
    all_anchor.onclick = async  ()=>{
        generateAssignedProjectCardsAll();
    }
    dropdown_content.appendChild(all_anchor);
    for (let instructor in data["Assigned Students"]){
        let instructor_anchor = document.createElement("a");
        instructor_anchor.appendChild(document.createTextNode(instructor));
        instructor_anchor.onclick = async ()=>{
            await generateAssignedProjectCards(instructor);
        };
        dropdown_content.appendChild(instructor_anchor);
    }
    dropdown.appendChild(dropdown_content);

    navbar.appendChild(dropdown);
}
createInstructorDropDown();
function createRequirementsTR(tbody, key, value){
    let row = tbody.insertRow();

    let header = document.createElement("th");
    header.appendChild(document.createTextNode(key));
    row.append(header);

    let body = document.createElement("td");
    body.appendChild(document.createTextNode(value));
    row.append(body);
}

function createRequirementsTRArray(tbody, key, array){
    let row = tbody.insertRow();

    let header = document.createElement("th");
    header.appendChild(document.createTextNode(key));
    row.append(header);

    let body = document.createElement("td");

    if (array){
        let str = ""
        str += StudentMajorTypes[array[0]];
        for (let preference in array)
            str += ", " + StudentMajorTypes[preference];
        body.appendChild(document.createTextNode(str));
    }


    row.append(body);
}

function createCard(project){
    let project_title = project["project-title"];
    let company_name = project["company-name"];
    let first_preference = project["first-preference"];
    let second_preference = project["second-preference"];
    let third_preference = project["third-preferences"];
    let project_nda = project["nda"];
    let project_ip = project["ip"];
    let students = project["students"]
    const ret = document.createElement("div");
    ret.classList.add("assigned-list-element")

    // Creating project header
    const projectHeader = document.createElement("div");
    projectHeader.classList.add("project-header");

    const projectTitle = document.createElement("div");
    projectTitle.classList.add("project-title");
    projectTitle.appendChild(document.createTextNode(project_title));
    const companyName = document.createElement("div");
    companyName.classList.add("company-name");
    companyName.appendChild(document.createTextNode(company_name));

    projectHeader.appendChild(projectTitle);
    projectHeader.appendChild(companyName);

    console.log(project["health"]);
    switch (project["health"]){
        case 0:
            projectHeader.style.backgroundColor = "#dd7777";
            break;
        case 1:
            projectHeader.style.backgroundColor = "#dddd77";
            break;
        case 2:
            projectHeader.style.backgroundColor = "#77DD77";
            break;
    }


    // Creating project content
    const projectContent = document.createElement("div");
    projectContent.classList.add("project-content");

    //    Creating project requirement
    const projectRequirements = document.createElement("div");
    projectRequirements.classList.add("project-requirements");

    const projectMajorPreferences = document.createElement("table");
    projectMajorPreferences.classList.add("project-major-preferences");
    let projectMajorPreferencesTBody = projectMajorPreferences.createTBody();
    createRequirementsTR(projectMajorPreferencesTBody, "Primary:", StudentMajorTypes[first_preference]);
    createRequirementsTR(projectMajorPreferencesTBody, "Secondary:", StudentMajorTypes[second_preference]);
    createRequirementsTRArray(projectMajorPreferencesTBody, "Tertiary:", third_preference);


    const projectSpecialRequirements = document.createElement("table");
    projectSpecialRequirements.classList.add("project-special-requirements");
    let projectSpecialRequirementsTBody = projectSpecialRequirements.createTBody();
    createRequirementsTR(projectSpecialRequirementsTBody, "NDA:", YesNo(project_nda));
    createRequirementsTR(projectSpecialRequirementsTBody, "IP:", YesNo(project_ip));

    projectRequirements.appendChild(projectMajorPreferences);
    projectRequirements.appendChild(projectSpecialRequirements);

    //    Creating assigned students
    const projectAssignedStudents = document.createElement("div");
    projectAssignedStudents.classList.add("project-assigned-students");

    for (let student_id in students){
        let student = students[student_id]
        const ProjectAssignedStudentInfo = document.createElement("div");
        ProjectAssignedStudentInfo.classList.add("project-assigned-student-info");

        const ProjectAssignedStudentNameMajor = document.createElement("table");
        ProjectAssignedStudentNameMajor.classList.add("project-assigned-student-name-major");
        let ProjectAssignedStudentNameMajorTBody = ProjectAssignedStudentNameMajor.createTBody();
        createRequirementsTR(ProjectAssignedStudentNameMajorTBody, "First Name:", student["first-name"]);
        createRequirementsTR(ProjectAssignedStudentNameMajorTBody, "Last Name:", student["last-name"]);
        createRequirementsTR(ProjectAssignedStudentNameMajorTBody, "Major:", StudentMajorTypes[student["major"]]);


        const ProjectAssignedStudentRequirements = document.createElement("table");
        ProjectAssignedStudentRequirements.classList.add("project-assigned-student-requirements");
        let ProjectAssignedStudentRequirementsTBody = ProjectAssignedStudentRequirements.createTBody();
        createRequirementsTR(ProjectAssignedStudentRequirementsTBody, "NDA:", YesNo(student["nda"]));
        createRequirementsTR(ProjectAssignedStudentRequirementsTBody, "IP:", YesNo(student["ip"]));

        ProjectAssignedStudentInfo.appendChild(ProjectAssignedStudentNameMajor);
        ProjectAssignedStudentInfo.appendChild(ProjectAssignedStudentRequirements);
        projectAssignedStudents.appendChild(ProjectAssignedStudentInfo);
    }



    projectContent.appendChild(projectRequirements);
    projectContent.appendChild(projectAssignedStudents);


    ret.appendChild(projectHeader);
    ret.appendChild(projectContent);
    return ret
}



async function generateAssignedProjectCards(instructor_name) {
    let card_title = document.getElementById("current_instructor_view_title");
    card_title.innerText = instructor_name + "'s Assignments";
    const data = await get_InstructorProjectStudentTree();
    const assigned_list = document.getElementById("assigned-list");

    while (assigned_list.firstChild) {
        assigned_list.removeChild(assigned_list.firstChild)
    }

    for (const project_id in data["Assigned Students"][instructor_name]){
        const project = data["Assigned Students"][instructor_name][project_id];
        assigned_list.appendChild(createCard(project));
    }


}

async function generateUnassignedStudentCardsAll() {
    const data = await get_InstructorProjectStudentTree();
    const unassigned_list = document.getElementById("unassigned-list");

    while (unassigned_list.firstChild) {
        unassigned_list.removeChild(unassigned_list.firstChild)
    }

    let students = data["Unassigned Students"];
    for (let student_id in data["Unassigned Students"]){
        let student = students[student_id]
        const UnassignedStudentInfo = document.createElement("div");
        UnassignedStudentInfo.classList.add("unassigned-student-info");

        const UnassignedStudentNameMajor = document.createElement("table");
        UnassignedStudentNameMajor.classList.add("unassigned-student-name-major");
        let UnassignedStudentNameMajorTBody = UnassignedStudentNameMajor.createTBody();
        createRequirementsTR(UnassignedStudentNameMajorTBody, "First Name:", student["first-name"]);
        createRequirementsTR(UnassignedStudentNameMajorTBody, "Last Name:", student["last-name"]);
        createRequirementsTR(UnassignedStudentNameMajorTBody, "Major:", StudentMajorTypes[student["major"]]);


        const UnassignedStudentRequirements = document.createElement("table");
        UnassignedStudentRequirements.classList.add("unassigned-student-requirements");
        let UnassignedStudentRequirementsTBody = UnassignedStudentRequirements.createTBody();
        createRequirementsTR(UnassignedStudentRequirementsTBody, "NDA:", YesNo(student["nda"]));
        createRequirementsTR(UnassignedStudentRequirementsTBody, "IP:", YesNo(student["ip"]));

        UnassignedStudentInfo.appendChild(UnassignedStudentNameMajor);
        UnassignedStudentInfo.appendChild(UnassignedStudentRequirements);
        unassigned_list.appendChild(UnassignedStudentInfo);
    }
}

async function generateAssignedProjectCardsAll() {
    let card_title = document.getElementById("current_instructor_view_title");
    card_title.innerText = "All Assignments";

    const data = await get_InstructorProjectStudentTree();
    const assigned_list = document.getElementById("assigned-list");

    while (assigned_list.firstChild) {
        assigned_list.removeChild(assigned_list.firstChild)
    }

    for (let instructor_name in data["Assigned Students"]){
        for (const project_id in data["Assigned Students"][instructor_name]){
            const project = data["Assigned Students"][instructor_name][project_id];
            assigned_list.appendChild(createCard(project));
        }
    }

}

generateAssignedProjectCardsAll();
generateUnassignedStudentCardsAll();
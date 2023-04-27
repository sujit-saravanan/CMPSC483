const StudentMajorTypes = ["BME", "CMPEN", "CMPSC", "DS", "ED", "EE", "EGEE", "ESC", "IE", "MATSE", "ME"];

let active_project;
let current_view;

async function get_InstructorProjectStudentTree() {
    const res = await fetch("/instructor_project_student_tree_get");
    return await res.json();
}

async function assign_student(student_id) {
    let json_data =
        '{' +
        '    "instructor_name": "' + active_project.instructor_name + '",' +
        '    "project_id": "' + active_project.project_id + '",' +
        '    "student_id": "' + student_id + '"' +
        '}'

    const res = await fetch("/assign_student", {
        method: "POST",
        body: json_data,
    });

    if (current_view === "allViewNoInstructor") {
        await generateAssignedProjectCardsAll();
    } else {
        await generateAssignedProjectCards(current_view);
    }
    await generateUnassignedStudentCardsAll();
    updateBars();
}

async function unassign_student(instructor_name, project_id, student_id) {
    let json_data =
        '{' +
        '    "instructor_name": "' + instructor_name + '",' +
        '    "project_id": "' + project_id + '",' +
        '    "student_id": "' + student_id + '"' +
        '}'

    const res = await fetch("/unassign_student", {
        method: "POST",
        body: json_data,
    });
    if (current_view === "allViewNoInstructor") {
        await generateAssignedProjectCardsAll();
    } else {
        await generateAssignedProjectCards(current_view);
    }
    await generateUnassignedStudentCardsAll();
    updateBars();
}


function YesNo(bool) {
    if (bool) return "Yes";
    return "No";
}


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
    all_anchor.onclick = async () => {
        generateAssignedProjectCardsAll();
    }
    dropdown_content.appendChild(all_anchor);
    for (let instructor in data["Assigned Students"]) {
        let instructor_anchor = document.createElement("a");
        instructor_anchor.appendChild(document.createTextNode(instructor));
        instructor_anchor.onclick = async () => {
            await generateAssignedProjectCards(instructor);
        };
        dropdown_content.appendChild(instructor_anchor);
    }
    dropdown.appendChild(dropdown_content);

    navbar.appendChild(dropdown);
}

createInstructorDropDown();

function createRequirementsTR(tbody, key, value) {
    let row = tbody.insertRow();

    let header = document.createElement("th");
    header.appendChild(document.createTextNode(key));
    row.append(header);

    let body = document.createElement("td");
    body.appendChild(document.createTextNode(value));
    row.append(body);
}

function createRequirementsTRArray(tbody, key, array) {
    let row = tbody.insertRow();

    let header = document.createElement("th");
    header.appendChild(document.createTextNode(key));
    row.append(header);

    let body = document.createElement("td");

    if (array) {
        let str = ""
        str += StudentMajorTypes[array[0]];
        for (let preference in array)
            str += ", " + StudentMajorTypes[preference];
        body.appendChild(document.createTextNode(str));
    }


    row.append(body);
}

function createCard(project, instructor_name, project_id) {
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
    projectHeader.onclick = function () {
        projectHeader.children[0].checked = true
        active_project = {instructor_name, project_id};
    };

    const projectTitle = document.createElement("div");
    projectTitle.classList.add("project-title");
    projectTitle.appendChild(document.createTextNode(project_title));
    const companyName = document.createElement("div");
    companyName.classList.add("company-name");
    companyName.appendChild(document.createTextNode(company_name));
    const projectRadio = document.createElement("input");
    projectRadio.classList.add("project-radio");
    projectRadio.type = "radio";
    projectRadio.name = "projectRadio";
    if (project_id === active_project.project_id) {
        projectRadio.checked = true;
    }
    projectRadio.onclick = function () {
        active_project = {instructor_name, project_id};
    };

    projectHeader.appendChild(projectRadio);
    projectHeader.appendChild(projectTitle);
    projectHeader.appendChild(companyName);

    switch (project["health"]) {
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

    for (let student_id in students) {
        let student = students[student_id]
        const ProjectAssignedStudentInfo = document.createElement("div");
        ProjectAssignedStudentInfo.classList.add("project-assigned-student-info");

        const ProjectAssignedStudentInfoTable = document.createElement("div");
        ProjectAssignedStudentInfoTable.classList.add("project-assigned-student-info-table");

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

        ProjectAssignedStudentInfoTable.appendChild(ProjectAssignedStudentNameMajor);
        ProjectAssignedStudentInfoTable.appendChild(ProjectAssignedStudentRequirements);

        const ProjectAssignedStudentButton = document.createElement("div");
        ProjectAssignedStudentButton.classList.add("project-assigned-student-button");
        ProjectAssignedStudentButton.appendChild(document.createTextNode(">"))
        ProjectAssignedStudentButton.onclick = async () => {
            await unassign_student(instructor_name, project_id, student_id);
        }


        ProjectAssignedStudentInfo.appendChild(ProjectAssignedStudentInfoTable);
        ProjectAssignedStudentInfo.appendChild(ProjectAssignedStudentButton);
        projectAssignedStudents.appendChild(ProjectAssignedStudentInfo);
    }


    projectContent.appendChild(projectRequirements);
    projectContent.appendChild(projectAssignedStudents);


    ret.appendChild(projectHeader);
    ret.appendChild(projectContent);
    return ret
}

async function getRatios() {
    const data = await get_InstructorProjectStudentTree();
    let total = 0;
    let dangerous = 0;
    let ok = 0;
    let healthy = 0;

    let assigned = 0;
    let unassigned = 0;
    if (data["Unassigned Students"] !== undefined)
        unassigned = Object.keys(data["Unassigned Students"]).length;
    for (let instructor_name in data["Assigned Students"]) {
        for (let project_id in data["Assigned Students"][instructor_name]) {
            total++;
            switch (data["Assigned Students"][instructor_name][project_id]["health"]) {
                case 0:
                    dangerous++;
                    break;
                case 1:
                    ok++
                    break;
                case 2:
                    healthy++
                    break;
                default:
                    break;
            }
            let st = data["Assigned Students"][instructor_name][project_id]["students"];
            if (st !== undefined)
                if (Object.keys(data["Assigned Students"][instructor_name][project_id]["students"]).length > 0)
                    assigned += Object.keys(data["Assigned Students"][instructor_name][project_id]["students"]).length;
        }
    }


    let project_bar_ratios = {
        total: total,
        healthy: healthy,
        ok: ok,
        dangerous: dangerous
    }
    let student_bar_ratios = {
        total: unassigned + assigned,
        unassigned: unassigned,
        assigned: assigned
    }
    return {
        project_bar_ratios: project_bar_ratios,
        student_bar_ratios: student_bar_ratios
    };
}

async function updateBars() {
    let project_bar = document.getElementById("project_bar");
    let student_bar = document.getElementById("student_bar");
    const ratios = await getRatios();

    project_bar.children[0].style.width = 100 * ratios.project_bar_ratios.healthy / ratios.project_bar_ratios.total + "%";
    project_bar.children[1].style.width = 100 * ratios.project_bar_ratios.ok / ratios.project_bar_ratios.total + "%";
    project_bar.children[2].style.width = 100 * ratios.project_bar_ratios.dangerous / ratios.project_bar_ratios.total + "%";
    student_bar.children[0].style.width = 100 * ratios.student_bar_ratios.assigned / ratios.student_bar_ratios.total + "%";
    student_bar.children[1].style.width = 100 * ratios.student_bar_ratios.unassigned / ratios.student_bar_ratios.total + "%";
}

async function generateAssignedProjectCards(instructor_name) {
    current_view = instructor_name;
    let card_title = document.getElementById("current_instructor_view_title");
    card_title.innerText = instructor_name + "'s Assignments";
    const data = await get_InstructorProjectStudentTree();
    const assigned_list = document.getElementById("assigned-list");

    while (assigned_list.firstChild) {
        assigned_list.removeChild(assigned_list.firstChild)
    }

    let i = true;
    for (const project_id in data["Assigned Students"][instructor_name]) {
        if (i && active_project.instructor_name !== instructor_name) {
            active_project = {instructor_name, project_id};
            i = false;
        }
        const project = data["Assigned Students"][instructor_name][project_id];

        let card = createCard(project, instructor_name, project_id);
        if (project_id === active_project.project_id) {
            card.children[0].children[0].checked = true;
        }
        assigned_list.appendChild(card);

    }


}

async function generateUnassignedStudentCardsAll() {
    const data = await get_InstructorProjectStudentTree();
    const unassigned_list = document.getElementById("unassigned-list");

    while (unassigned_list.firstChild) {
        unassigned_list.removeChild(unassigned_list.firstChild)
    }

    let students = data["Unassigned Students"];
    for (let student_id in data["Unassigned Students"]) {
        let student = students[student_id]
        const UnassignedStudentInfo = document.createElement("div");
        UnassignedStudentInfo.classList.add("unassigned-student-info");

        const UnassignedStudentInfoTable = document.createElement("div");
        UnassignedStudentInfoTable.classList.add("unassigned-student-info-table");

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


        const UnassignedStudentButton = document.createElement("div");
        UnassignedStudentButton.classList.add("unassigned-student-button");
        UnassignedStudentButton.appendChild(document.createTextNode("<"))
        UnassignedStudentButton.onclick = async () => {
            await assign_student(student_id);
        }

        UnassignedStudentInfoTable.appendChild(UnassignedStudentNameMajor);
        UnassignedStudentInfoTable.appendChild(UnassignedStudentRequirements);

        UnassignedStudentInfo.appendChild(UnassignedStudentButton);
        UnassignedStudentInfo.appendChild(UnassignedStudentInfoTable);
        unassigned_list.appendChild(UnassignedStudentInfo);
    }
}

async function generateAssignedProjectCardsAll() {
    current_view = "allViewNoInstructor";
    let card_title = document.getElementById("current_instructor_view_title");
    card_title.innerText = "All Assignments";

    const data = await get_InstructorProjectStudentTree();
    const assigned_list = document.getElementById("assigned-list");

    while (assigned_list.firstChild) {
        assigned_list.removeChild(assigned_list.firstChild)
    }

    let i = 0;
    for (let instructor_name in data["Assigned Students"]) {
        for (const project_id in data["Assigned Students"][instructor_name]) {
            const project = data["Assigned Students"][instructor_name][project_id];
            if (active_project == null || (i < 1 && current_view !== "allViewNoInstructor")) {
                active_project = {instructor_name, project_id};

            }
            assigned_list.appendChild(createCard(project, instructor_name, project_id));
            i++
        }
    }

}

generateAssignedProjectCardsAll();
generateUnassignedStudentCardsAll();
updateBars();

const projectSearchInput = document.getElementById("projectSearch");
const companySearchInput = document.getElementById("companySearch");
const courseTimeSelect = document.getElementsByID("coursetime-select")
const primarySelect = document.getElementById("primary-select");
const secondarySelect = document.getElementById("secondary-select");
const tertiarySelect = document.getElementById("tertiary-select");

projectSearchInput.addEventListener("keyup", searchAndFilter);
companySearchInput.addEventListener("keyup", searchAndFilter);
courseTimeSelect.addEventListener("change", searchAndFilter);
primarySelect.addEventListener("change", searchAndFilter);
secondarySelect.addEventListener("change", searchAndFilter);
tertiarySelect.addEventListener("change", searchAndFilter);

function searchAndFilter() {
  var projectCards = document.getElementsByClassName("project-card");
  var projectCardContents = document.getElementsByClassName("project-card-content");
  for (var i = 0; i < projectCards.length; i++) {
    projectCards[i].style.display = "none";
    projectCardContents[i].style.display = "none";
  }
  
  const projectSearchTerm = projectSearchInput.value.toLowerCase();
  const companySearchTerm = companySearchInput.value.toLowerCase();
  var primaryFilter = document.getElementById("primary-select").value;
  var secondaryFilter = document.getElementById("secondary-select").value;
  var tertiaryFilter = document.getElementById("tertiary-select").value;

  for (var i = 0; i < projectCards.length; i++) {
    const projectName = projectCards[i].querySelector("td:first-child").textContent.toLowerCase();
    const companyName = projectCards[i].querySelector("td:nth-child(2)").textContent.toLowerCase();

    var primaryValue = projectCards[i].getElementsByTagName("td")[3].textContent;
    var secondaryValue = projectCards[i].getElementsByTagName("td")[4].textContent;
    var tertiaryValue = projectCards[i].getElementsByTagName("td")[5].textContent;

    var not_show = projectSearchTerm != "" && !projectName.includes(projectSearchTerm) 
               || companySearchTerm != "" && !companyName.includes(companySearchTerm)
               || primaryFilter !== "" && primaryValue !== primaryFilter
               || secondaryFilter !== "" && secondaryValue !== secondaryFilter
               || tertiaryFilter !== "" && !tertiaryValue.includes(tertiaryFilter);

    if (not_show) {
      projectCards[i].style.display = "none";
    } else {
      projectCards[i].style.display = "";
    }
  }
}

function toggleCard(element) {
  var content = element.nextElementSibling;

  element.classList.toggle("active");

  if (content && content.style.display === "none") {
    content.style.display = "table-row";
    var students = content.getElementsByClassName("student-names")[0];
    if (students) {
      students.style.display = "block";
    }
  } else {
    content.style.display = "none";
    var students = content.getElementsByClassName("student-names")[0];
    if (students) {
      students.style.display = "none";
    }
  }
}


function getProjectInstructorMap() {
  var projectInstructorMap = {};
  fetch("/project_instructor_map")
    .then(response => response.json())
    .then(data => {
      Object.keys(data).forEach(key => {
        projectInstructorMap[key] = data[key];
      });
    })
    .catch(error => console.error(error));

  return projectInstructorMap;
}

function getProjectData() {
  const tableBody = document.getElementById("project-info");
  const projectInstructorMap = getProjectInstructorMap();

  fetch("/project_json")
    .then(response => response.json())
    .then(data => {
      Object.keys(data).forEach(key => {
        const val = data[key];
        const tbody = document.querySelector("#project-info");
        const template = document.querySelector('#project-card-temp');

        const clone = template.content.cloneNode(true);
        let td = clone.querySelectorAll("td");

        // set project-card
        td[0].textContent = val.projectTitle;
        td[1].textContent = val.companyName;
        td[2].textContent = val.courseTime;
        td[3].textContent = val.firstPreference;
        td[4].textContent = val.secondPreference;
        td[5].textContent = val.thirdPreference;
        td[6].textContent = 1000; // TODO: get actual number from database

        // set project-card-content
        td[8].textContent = val.courseName;
        td[9].textContent = val.courseTime;
        td[10].textContent = projectInstructorMap[key];
        td[11].textContent = val.ip;
        td[12].textContent = val.confidentiality;
        td[13].textContent = val.physicalPrototype;

        const button = clone.getElementById("customizeMenu");
        button.id = "button-" + key;
        button.setAttribute("data-bs-target", "#"+key);

        const modal = clone.getElementById("staticBackdrop");
        modal.id = key;

        td[15].textContent = val.projectTitle;

        tbody.appendChild(clone);
      });
    })
    .catch(error => console.error(error));
}
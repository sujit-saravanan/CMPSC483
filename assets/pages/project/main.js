const projectSearchInput = document.getElementById('projectSearch');
const companySearchInput = document.getElementById('companySearch');
const primarySelect = document.getElementById('primary-select');
const secondarySelect = document.getElementById('secondary-select');
const tertiarySelect = document.getElementById('tertiary-select');

projectSearchInput.addEventListener('keyup', searchProjects);
companySearchInput.addEventListener('keyup', searchCompany);
primarySelect.addEventListener('change', filterByMajor);
secondarySelect.addEventListener('change', filterByMajor);
tertiarySelect.addEventListener('change', filterByMajor);


function searchProjects() {
  const searchTerm = projectSearchInput.value.toLowerCase();
  const rows = document.querySelectorAll('.project-card');
  rows.forEach((row) => {
    const projectName = row.querySelector('td:first-child').textContent.toLowerCase();
    if (projectName.includes(searchTerm)) {
      row.style.display = 'table-row';
    } else {
      row.style.display = 'none';
    }
  });
}

function searchCompany() {
  const searchTerm = companySearchInput.value.toLowerCase();
  const rows = document.querySelectorAll('.project-card');
  rows.forEach((row) => {
    const companyName = row.querySelector('td:nth-child(2)').textContent.toLowerCase();
    if (companyName.includes(searchTerm)) {
      row.style.display = 'table-row';
    } else {
      row.style.display = 'none';
    }
  });
}

function filterMajors() {
  var primaryFilter = document.getElementById("primary-select").value;
  var secondaryFilter = document.getElementById("secondary-select").value;
  var tertiaryFilter = document.getElementById("tertiary-select").value;

  var projectCards = document.getElementsByClassName("project-card");

  for (var i = 0; i < projectCards.length; i++) {
    var primaryValue = projectCards[i].getElementsByTagName("td")[2].textContent;
    var secondaryValue = projectCards[i].getElementsByTagName("td")[3].textContent;
    var tertiaryValue = projectCards[i].getElementsByTagName("td")[4].textContent;

    if (primaryFilter !== "" && primaryValue !== primaryFilter) {
      projectCards[i].style.display = "none";
    } else if (secondaryFilter !== "" && secondaryValue !== secondaryFilter) {
      projectCards[i].style.display = "none";
    } else if (tertiaryFilter !== "" && tertiaryValue !== tertiaryFilter) {
      projectCards[i].style.display = "none";
    } else {
      projectCards[i].style.display = "";
    }
  }
}

document.getElementById("primary-select").addEventListener("change", filterProjects);
document.getElementById("secondary-select").addEventListener("change", filterProjects);
document.getElementById("tertiary-select").addEventListener("change", filterProjects);

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

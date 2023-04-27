const upload_map = new Map();
const file_map = new Map();
const actualBtns = document.getElementsByClassName("file-upload-button");

for (let button in actualBtns) {
    if (actualBtns[button].type !== "file")
        break;
    upload_map[actualBtns[button].id] = false;
    actualBtns[button].addEventListener('change', function () {
        uploadCSVToServer(this.files[0], this.id);
    })
}


async function send_csv(file) {
    const response = await fetch("/csv", {
        method: "POST",
        headers: {
            "Content-Type": "text/csv",
        },
        body: file
    });
    return response.text();
}

async function upload() {
    let alert_string = "";
    for (let key in upload_map)
        if (!upload_map[key])
            alert_string += "Missing " + key + "\n";

    if (alert_string !== "") {
        alert(alert_string);
        return;
    }

    for (let key in file_map)
        await send_csv(file_map[key]);

    alert("Uploaded CSV!");
}

async function export_csv() {
    const response = await fetch("/export_csv", {
        method: "GET",
    })
    .then(response => response.blob())
    .then(blob => {
        let a = document.createElement("a");
        a.href = URL.createObjectURL(blob);
        a.setAttribute("download", "final_export.csv");
        a.click();
    });
}

async function download() {
    await export_csv();
}

function uploadCSVToServer(file, id) {
    console.log(upload_map)
    switch (id) {
        case "button-projectsFinal":
            if (file.name !== "projectsFinal.csv") {
                alert("Incorrect filename, expected \"projectsFinal.csv\"");
                return;
            }

            upload_map["button-projectsFinal"] = true;
            file_map["button-projectsFinal"] = file;
            break;
        case "button-sectionInfo":
            if (file.name !== "sectionInfo.csv") {
                alert("Incorrect filename, expected \"sectionInfo.csv\"");
                return;
            }

            upload_map["button-sectionInfo"] = true;
            file_map["button-sectionInfo"] = file;
            break;
        case "button-studentAssignments":
            if (file.name !== "studentAssignments.csv") {
                alert("Incorrect filename, expected \"studentAssignments.csv\"");
                return;
            }

            upload_map["button-studentAssignments"] = true;
            file_map["button-studentAssignments"] = file;
            break;
        case "button-studentsWithoutPrefs":
            if (file.name !== "students without prefs.csv") {
                alert("Incorrect filename, expected \"students without prefs.csv\"");
                return;
            }

            upload_map["button-studentsWithoutPrefs"] = true;
            file_map["button-studentsWithoutPrefs"] = file;
            break;
    }
}


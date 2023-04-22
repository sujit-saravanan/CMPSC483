async function send_csv(file) {
    const response = await fetch("/csv", {
        method: "POST",
        mode: "cors",
        cache: "no-cache",
        credentials: "same-origin",
        headers: {
            "Content-Type": "text/csv",
        },
        redirect: "follow",
        referrerPolicy: "no-referrer",
        body: file
    });
    return response.text();
}

async function update_csv() {
    const response = await fetch("/simple_csv_get", {
        method: "GET",
        mode: "cors",
        cache: "no-cache",
        credentials: "same-origin",
        headers: {
            "Content-Type": "text/plain",
        },
        redirect: "follow",
        referrerPolicy: "no-referrer",
    });
    return response.text();
}

function csv_string_to_table(csv_string, element_to_insert_table) {
    var rows = csv_string.trim().split(/\r?\n|\r/); // Regex to split/separate the CSV rows
    var table = '';
    var table_rows = '';
    var table_header = '';

    rows.forEach(function (row, row_index) {
        var table_columns = '';
        var columns = row.split(','); // split/separate the columns in a row
        columns.forEach(function (column, column_index) {
            table_columns += row_index == 0 ? '<th>' + column + '</th>' : '<td>' + column + '</td>';
        });
        if (row_index == 0) {
            table_header += '<tr>' + table_columns + '</tr>';
        } else {
            table_rows += '<tr>' + table_columns + '</tr>';
        }
    });

    table += '<table>';
    table += '<thead>';
    table += table_header;
    table += '</thead>';
    table += '<tbody>';
    table += table_rows;
    table += '</tbody>';
    table += '</table>';

    element_to_insert_table.innerHTML = table;
}

function uploadCSVToServer(file) {
    if (file.name === "studentAssignments.csv") {
        send_csv(file).then(() => {
            if (confirm("Confirm upload?")) {
                update_csv().then((response) => {
                    csv_string_to_table(response, document.getElementById("current-assignments-table"));
                    console.log(response);
                });
            }
        });
    } else {
        alert("Please upload the studentAssignments.csv file");
    }
}

function dropHandler(ev, zone) {
    ev.preventDefault();

    zone.style.backgroundColor = "var(--bg-light-bright)";
    zone.style.borderColor = "var(--blue)";
    zone.children[0].style.filter = "invert(18%) sepia(44%) saturate(2474%) hue-rotate(201deg) brightness(95%) contrast(89%)";
    zone.children[1].children[1].style.color = "var(--blue)";
    zone.children[1].style.color = "black";

    if (ev.dataTransfer.items[0].kind === "file") {
        uploadCSVToServer(ev.dataTransfer.items[0].getAsFile());
    }
}

function dragOverHandler(ev, zone) {
    if (ev.dataTransfer.items) {
        for (let i = 0; i < ev.dataTransfer.items.length; i++) {
            if (ev.dataTransfer.items[i].kind !== "file") {
                return
            }
        }
    }

    zone.style.backgroundColor = "var(--navy)";
    zone.style.borderColor = "var(--navy)";
    zone.children[0].style.filter = "invert(100%)";
    zone.children[1].children[1].style.color = "var(--bg-light-bright)";
    zone.children[1].style.color = "var(--bg-light-bright)";

    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();
}

function dragLeaveHandler(ev, zone) {
    zone.style.backgroundColor = "var(--bg-light-bright)";
    zone.style.borderColor = "var(--blue)";
    zone.children[0].style.filter = "invert(18%) sepia(44%) saturate(2474%) hue-rotate(201deg) brightness(95%) contrast(89%)";
    zone.children[1].children[1].style.color = "var(--blue)";
    zone.children[1].style.color = "black";

    // Prevent default behavior (Prevent file from being opened)
    ev.preventDefault();
}

const actualBtn = document.getElementById('actual-btn');
actualBtn.addEventListener('change', function () {
    uploadCSVToServer(this.files[0]);
})
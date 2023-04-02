function dropHandler(ev) {
  console.log("File(s) dropped");

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();

  if (ev.dataTransfer.items) {
    // Use DataTransferItemList interface to access the file(s)
    [...ev.dataTransfer.items].forEach((item, i) => {
      // If dropped items aren't files, reject them
      if (item.kind === "file") {
        const file = item.getAsFile();
        console.log(`… file[${i}].name = ${file.name}`);
      }
    });
  } else {
    // Use DataTransfer interface to access the file(s)
    [...ev.dataTransfer.files].forEach((file, i) => {
      console.log(`… file[${i}].name = ${file.name}`);
    });
  }
}
function dragOverHandler(ev, zone) {
    if (ev.dataTransfer.items) {
    for (let i = 0; i < ev.dataTransfer.items.length; i++){
        if (ev.dataTransfer.items[i].kind !== "file") {
            return
        }
    }
  }


  console.log("File(s) in drop zone");
  zone.style.backgroundColor = "var(--navy)";
  zone.style.borderColor = "var(--navy)";
  zone.children[0].style.filter = "invert(100%)";
  zone.children[1].children[0].style.color = "var(--bg-light-bright)";
  zone.children[1].style.color = "var(--bg-light-bright)";

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();
}

function dragLeaveHandler(ev, zone) {
  console.log("File(s) in drop zone");
  zone.style.backgroundColor = "var(--bg-light-bright)";
  zone.style.borderColor = "var(--blue)";
  zone.children[0].style.filter = "invert(18%) sepia(44%) saturate(2474%) hue-rotate(201deg) brightness(95%) contrast(89%)";
  zone.children[1].children[0].style.color = "var(--blue)";
  zone.children[1].style.color = "var(--blue)";

  // Prevent default behavior (Prevent file from being opened)
  ev.preventDefault();
}
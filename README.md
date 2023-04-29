# Learning Factory Dashboard Capstone Project
The Learning Factory's current approach towards the assignment of students is inefficient and requires far too many man hours spent on the tedious editing of documents. For this project, we were assigned the creation of a dashboard that allows Learning Factory staff to easily view, manage, and update student-project assignments for students enrolled in the program.

Our sponsor has stated a series of requirements, for both the functionality as well as the appearance of the dashboard:

### Appearance:
- The sponsor has requested all relevant information, ranging from the current “healthiness” (Whether or not a project has an adequate number of primary majors) of all of the projects to the current proportion of assigned versus unassigned students. Naturally, all of the projects and students should also be within view.
  - We determined that the best design would be a two table format that showcases all of the projects on one side, and all of the unassigned students on the other side. Both tables should be filterable by the relevant information tags, ranging from name to requirements for both projects as well as students.
  - In order to satisfy the requirement of having the state of the current assignments easily viewable, a section that displays information such as the healthiness of the current assignments as well as how many students are unassigned could be displayed at the top of the assignments page, or another page entirely.
    - Further discussion determined that the former would be easier to implement, as well as more adequately match our sponsor’s preference of having all information visible in an easy to parse manner.
### Functionality:
- The functionality of the dashboard is very straight forward. We would first need to obtain instructor, student, and project information either from the Learning Factory’s database, or our sponsor’s script which outputs a series of CSV files. Then, we’d allow for manipulation of the state we received, before either sending an update request to the database or exporting a CSV for our client to do with what they wished.
  - Ultimately, we went with the CSV approach as it was easier to implement, and allowed the sponsor to use their already created script.
- Originally, we assumed that the application would require basic CRUD functionality for all of the relevant data points (Instructors, Students, Projects). However, while working on the project, we realized that a partial implementation would work just fine. Unfortunately, our partial implementation resulted in having to effectively re-send the entire state we were managing for every single request, which while allowed for easy synchronization between multiple users, was less than ideal as it resulted in around 500ms of latency between users initiating a request and the request completing. A more extensive solution is currently required for a reasonable user experience.


### Future changes:
- The biggest change that needs to be made at some point is porting the script that our sponsor is using to generate the initial student-project assignments over to the server, as while allowing for the sponsor to upload their own set of data greatly simplified our task, it ultimately is not a good user experience and is rife with problems.
- We also need to implement a better solution for synchronization than simply sending all of our state to the user(s) on every request, a 500ms latency between input and response is simply unacceptable.
- The UI itself needs additional polishing, the current design is quite simplistic and missing the polish of a finished product.



# Dependencies
OS: Unix based operating system<br>

rang:    	https://aur.archlinux.org/packages/rang-git<br>
cpp-httplib: https://aur.archlinux.org/packages/cpp-httplib-compiled<br>
sqlite:  	https://archlinux.org/packages/core/x86_64/sqlite/<br>
stitch:  	https://github.com/sujit-saravanan/stitch

# Commands to install
```
git clone https://github.com/sujit-saravanan/CMPSC483.git
cd CMPSC483
chmod +x build.sh
./build.sh
```

# Command to run
```
stitch run release
```
or
```
stitch run dev
```
or
```
./build.sh
```

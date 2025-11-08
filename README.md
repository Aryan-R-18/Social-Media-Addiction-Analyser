```markdown
# Social Media Addiction Analyzer

![C](https://img.shields.io/badge/Built%20with-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)
![License](https://img.shields.io/badge/License-Open%20Source-green)
![Status](https://img.shields.io/badge/Status-Active-success)

A C-based console application that tracks and analyzes users’ social media usage.  
It records app activity, categorizes usage by time slots, generates reports, and provides helpful suggestions to reduce excessive screen time.

---

## 🧩 Features
- Register and manage multiple users  
- Log daily app usage with time duration and time slots (Morning/Afternoon/Night)  
- Automatically analyze total and slot-wise usage  
- Generate detailed text-based reports in the `reports/` folder  
- Provide personalized suggestions to manage screen time  
- Persistent storage of user data in the `data/` folder  

---

## ⚙️ Requirements
- GCC Compiler  
- Make Utility (optional but recommended)  
- OS: Windows / Linux / macOS  

---

## 🗂️ Project Structure
```

SocialMediaAddictionAnalyzer/
│
├── include/
│   ├── user.h
│   ├── usage.h
│   ├── analysis.h
│   ├── suggestions.h
│   └── file_handler.h
│
├── src/
│   ├── main.c
│   ├── user.c
│   ├── usage.c
│   ├── analysis.c
│   ├── suggestions.c
│   └── file_handler.c
│
├── data/          ← stores user and usage data
├── reports/       ← stores generated reports
└── Makefile

````

---

## 🧠 How to Compile and Run
### Step 1: Open terminal in the project folder  
```bash
cd SocialMediaAddictionAnalyzer
````

### Step 2: Compile using Make

```bash
make
```

### Step 3: Run the executable

```bash
./addictionAnalyzer   # Linux/macOS
addictionAnalyzer.exe  # Windows
```

---

## 🧭 How to Use

1. **Register New User** → Enter a username (only letters, numbers, underscores allowed)
2. **List Users** → View all registered users
3. **Log Usage** → Enter app name, duration (in minutes), and time slot
4. **View Daily Report** → Shows usage summary and suggestions
5. **Save & Exit** → Saves all data to files

---

## 📁 Output Files

* **data/users.txt** → List of users
* **data/usage_username.txt** → Usage records per user
* **reports/report_username.txt** → Detailed analysis and suggestions

---

## 🚀 Future Enhancements

* Add a graphical frontend (React/HTML)
* Develop a backend using Node.js or Python Flask for database management
* Visualize usage trends with charts and real-time analytics
* Include AI-based personalized digital well-being recommendations

---

## 👨‍💻 Author

Developed by **Aryan Rajguru**
VSSUT, Burla

```
```

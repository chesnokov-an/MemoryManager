# Laboratory Work No. 3: Class Hierarchy
## Variant N: Memory Manager

### 📘 Project Description
This project implements a **system of automatic memory management** allocated to running programs.
Physically, memory is represented by a **single fixed-size array** that is shared by all programs.
The system supports working with different types of memory elements, error tracking, and usage statistics.

---

### 🧩 Main Entities

#### 1. Memory Element *(base class)*
An abstract class describing the common interface of all memory elements.  
It is extended by creating new descendants (for example, a memory segment of an external device).

---

#### 2. Types of Memory Elements

##### 🔹 Single Variable
**The descriptor contains:**
- Variable name  
- Size of allocated memory  
- Pointer to the allocated region  

##### 🔹 Array
**The descriptor contains:**
- Array name  
- Total size of allocated memory  
- Size of a single element  
- Pointer to the allocated region  

##### 🔹 Shared Memory Segment
**The descriptor contains:**
- Segment name  
- Size of allocated memory  
- Element size  
- Pointer to the allocated region  
- List of programs that have access to the segment  

##### 🔹 Reference
**The descriptor contains:**
- Reference name  
- Pointer to another variable of the same program  
  or to a shared segment declared in another program  

---

### 🧠 Logical Structure

#### Program Container
Stores data about all allocated memory regions belonging to a specific program.  
Provides **access to memory by variable names**.

#### System Table
Stores data about all registered programs:
- Path to the executable file  
- Memory quota (maximum amount that the program can request)  
- List of data about allocated memory  

The table template class is implemented as a **hash table with separate chaining**.

---

### ⚙️ Main System Functions

#### For a variable:
- Get value  
- Change value  
- Create a reference to the variable  

#### For an array and a shared segment:
- Get an element value by index  
- Get values in an index range  
- Write a new value  

#### For a shared segment:
- Grant access to a program  
- Revoke a program’s access to the segment  

#### For a program:
- Allocate memory of the specified type  
- Free memory  
- Get access to an existing shared segment  
- Display all information about used memory  
- Display data about shared segments  
- Calculate the total amount of used memory \*  

\* This operation is implemented in multithreaded mode.  
Each group of memory elements is processed **in a separate thread**.

#### For the entire system:
- Display a summary of memory usage  
- Show the share of memory used by each program  
- Display memory operation errors (per program and system-wide)  
- Show invalid references (to freed memory)  
- Perform **memory defragmentation**

---

### ⚠️ Error Handling
The system must record and log the following types of errors:
- Out-of-bounds memory access  
- Memory leak (repeated allocation without deallocation)  
- Access by a non-existent identifier  
- Reference to freed memory  

All errors are stored in a **special error list**.

---

This project uses Dear ImGui and GLFW.
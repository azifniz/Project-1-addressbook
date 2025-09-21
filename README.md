# 📇 Address Book in C

A simple **Address Book Management System** built in C.  
It allows users to add, search, edit, delete, list, and save contacts with built-in validation for input fields.  

---

## ✨ Features
- ➕ **Add Contact** – Create a new contact with name, phone, and email  
- 🔍 **Search Contact** – Find by name, phone, or email  
- ✏️ **Edit Contact** – Update a contact’s details  
- ❌ **Delete Contact** – Remove a contact by index, phone, or email  
- 📜 **List Contacts** – Display all stored contacts  
- 💾 **Save Contacts** – Persist contacts to `Addressbookcontacts.csv`  
- 📂 **Load Contacts** – Automatically loads saved contacts at startup  
- UI **User Interface** - Uniform themed statements for ease of readability
---

## 🛡️ Input Validation
- **Name** → Only alphabets and spaces, no leading spaces, cannot be empty  
- **Phone** → Exactly 10 digits, only numbers, no duplicates  
- **Email** → Must end with a valid domain (default: `@gmail.com`, `@yahoo.com`, `@outlook.com`)  
  - Local part allows: letters, numbers, `_`, `.`  
  - No duplicate emails allowed  

---

## 📂 Project Structure
├── main.c # Entry point, handles menu navigation <br>
├── contacts.c # Core features (add, search, edit, delete, list, save, load)<br>
├── contacts.h # Header for feature functions + struct definition<br>
├── validation.c # Validation logic for name, phone, and email<br>
├── validation.h # Header for validation functions<br>
└── Addressbookcontacts.csv # Data file (created after saving)<br>

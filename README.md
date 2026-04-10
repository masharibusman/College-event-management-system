# College Event Management System

A C-based event management system developed during my 2nd year of college. This console application allows administrators to manage events and students to register for events.

## Features

### Admin Features
- **Event Management**: Add, delete, and modify events
- **View Events**: Display all available events
- **Attendee Management**: View event attendees
- **Secure Login**: Admin authentication system

### Student Features
- **Account Creation**: Register new student accounts
- **Event Registration**: Register for available events
- **Event Viewing**: Browse all available events
- **Secure Login**: Student authentication system

## How to Run

1. **Compile the program:**
   ```bash
   gcc Untitled123.cpp -o event_management
   ```

2. **Run the executable:**
   ```bash
   ./event_management
   ```

## Default Admin Credentials
- **Admin ID:** Buddha
- **Password:** bit525

## File Structure
- `Untitled123.cpp` - Main source code
- `events.txt` - Stores event data (auto-generated)
- `registration.txt` - Stores student credentials (auto-generated)

## Data Structures
- **Event Structure**: ID, name, date, attendees, venue
- **Student Structure**: Roll number, password

## Input Validation
- Date format validation (DD-MM-YYYY)
- Name validation (alphabets and spaces only)
- Mobile number validation (10 digits)
- Email format validation

## Technologies Used
- **Language:** C
- **File I/O:** Text file storage
- **Data Structures:** Arrays and structures

## Future Enhancements
- Database integration
- GUI interface
- Email notifications
- Advanced reporting features

---
*This project was developed as part of my college coursework in 2nd year.*
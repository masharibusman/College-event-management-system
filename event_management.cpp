#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100
#define EVENT_NAME_LEN 100
#define FILE_NAME "events.txt"
#define VENUE_LEN 100
#define STUDENT_FILE "registration.txt"
#define MOBILE_LEN 11
#define EMAIL_LEN 50
#define BRANCH_LEN 50

// Event structure
typedef struct {
    int id; // Unique ID for each event
    char name[EVENT_NAME_LEN];
    char date[11]; // Format: DD-MM-YYYY
    int attendees;
    char venue[VENUE_LEN];
} Event;

// Student structure for registration
typedef struct {
    char roll_number[15];
    char password[20];
} Student;

Event events[MAX_EVENTS]; // Array for storing events
int event_count = 0; // Total number of events

// Function prototypes
void load_events();
void save_events();
void add_event();
void delete_event();
void modify_event();
void view_events();
void view_event_attendees();
void admin_login();
void student_login();
int get_integer_input();
void get_string_input(char *input, int length);
int is_valid_date(const char *date);
int is_valid_name(const char *name);
int is_valid_attendees(int attendees);
int is_valid_mobile(const char *mobile);
int is_valid_email(const char *email);
void register_event(const char *student_name);
void register_student();
int check_student_credentials(const char *roll_number, const char *password);

// Main function
int main() {
	
	printf(" ******** **    ** ******** **     ** ******** **         ** ********  ******* ********       \n");
    printf(" ******** **    ** ******** ***    ** ******** **         ** ******** ******** ********       \n");
    printf(" **   	  **    ** **       ****   **    **    **         **    **    **       **             \n");
    printf(" ******** **    ** ******** ** **  **    **    **    *    **    **    ******** ********       \n");
    printf(" ******** **    ** ******** **  ** **    **    **   ***   **    **    ******** ********       \n");
    printf(" **       **    ** **       **   ****    **    **  ** **  **    **          ** **             \n");
    printf(" ********  **  **  ******** **    ***    **    ** **   ** ** ******** ******** ********       \n");
    printf(" ********   ****   ******** **     **    **    ***       *** ******** *******  ********       \n\n");
    
    load_events();

    while (1) {
        printf("Main Menu:\n");
        printf("1. Admin Login\n");
        printf("2. Student Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        
        int choice = get_integer_input();

        switch (choice) {
            case 1:
                admin_login();
                break;
            case 2:
                student_login();
                break;
            case 3:
                save_events();  // Save events before exiting the program
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    } 
    return 0;
}

// Admin login function
void admin_login() {
    char admin_id[20];
    char password[20];

    printf("Enter Admin ID: ");
    get_string_input(admin_id, sizeof(admin_id));
    printf("Enter Password: ");
    get_string_input(password, sizeof(password));

    if (strcmp(admin_id, "Buddha") == 0 && strcmp(password, "bit525") == 0) {
        int choice;
        while (1) {
            printf("\nAdmin Menu:\n");
            printf("1. Add Event\n");
            printf("2. Delete Event\n");
            printf("3. Modify Event\n");
            printf("4. View Events\n");
            printf("5. View Event Attendees\n");
            printf("6. Exit\n");
            printf("Select an option: ");
            
            choice = get_integer_input();

            switch (choice) {
                case 1: add_event(); break;
                case 2: delete_event(); break;
                case 3: modify_event(); break;
                case 4: view_events(); break;
                case 5: view_event_attendees(); break;
                case 6: return;
                default: printf("Invalid option. Please try again.\n");
            }
        }
    } else {
        printf("Invalid credentials.\n");
    }
}

// Student login function
void student_login() {
    char roll_number[15], password[20];

    printf("Enter Roll Number: ");
    get_string_input(roll_number, sizeof(roll_number));
    printf("Enter Password: ");
    get_string_input(password, sizeof(password));

    if (check_student_credentials(roll_number, password)) {
        int choice;
        while (1) {
            printf("\nStudent Menu:\n");
            printf("1. View Events\n");
            printf("2. Register for an Event\n");
            printf("3. Logout\n");
            printf("Select an option: ");
            
            choice = get_integer_input();

            switch (choice) {
                case 1: view_events(); break;
                case 2: {
                    char student_name[50];
                    printf("Enter your name: ");
                    get_string_input(student_name, sizeof(student_name));

                    // Validate student name
                    if (!is_valid_name(student_name)) {
                        printf("Invalid name. Please use only alphabets and spaces.\n");
                        return;
                    }
                    register_event(student_name);
                    break;
                }
                case 3: return; // Logout
                default: printf("Invalid option. Please try again.\n");
            }
        }
    } else {
        printf("No account found with that Roll Number. Create a new account.\n");
        register_student();
    }
}

// Function to check student credentials
int check_student_credentials(const char *roll_number, const char *password) {
    FILE *file = fopen(STUDENT_FILE, "r");
    if (!file) {
        return 0; // File not found
    }

    Student student;
    while (fscanf(file, "%s %s", student.roll_number, student.password) == 2) {
        if (strcmp(student.roll_number, roll_number) == 0 && strcmp(student.password, password) == 0) {
            fclose(file);
            return 1; // Found
        }
    }

    fclose(file);
    return 0; // Not found
}

// Register a new student
void register_student() {
    char roll_number[15], password[20];

    printf("Create a new account\n");
    printf("Enter Roll Number: ");
    get_string_input(roll_number, sizeof(roll_number));
    printf("Create a Password: ");
    get_string_input(password, sizeof(password));

    FILE *file = fopen(STUDENT_FILE, "a");
    if (file) {
        fprintf(file, "%s %s\n", roll_number, password);
        fclose(file);
        printf("Account created successfully!\n");
    } else {
        printf("Error: Could not open file for registration.\n");
    }
}

// Get integer input function
int get_integer_input() {
    int value;
    while (1) {
        if (scanf("%d", &value) == 1) {
            while (getchar() != '\n'); // Clear the input buffer
            return value;
        } else {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n'); // Clear invalid input
        }
    }
}

// Get string input function
void get_string_input(char *input, int length) {
    fgets(input, length, stdin);
    input[strcspn(input, "\n")] = 0; // Remove trailing newline

    // Check if newline is missing, meaning the buffer has leftover characters
    if (strlen(input) == length - 1 && input[length - 2] != '\n') {
        while (getchar() != '\n');  // Clear the buffer
    }
}


// Validate name function (for both event names and student names)
int is_valid_name(const char *name) {
    return strlen(name) > 0; // Check that the name is not empty
}

int is_valid_attendees(int attendees) {
    return attendees >= 0; // Attendees must be a non-negative number
}


// Validate date function (DD-MM-YYYY)
int is_valid_date(const char *date) {
    if (strlen(date) != 10 || date[2] != '-' || date[5] != '-') return 0;
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Skip dashes
        if (date[i] < '0' || date[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// Validate mobile number function (10 digits)
int is_valid_mobile(const char *mobile) {
    if (strlen(mobile) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (mobile[i] < '0' || mobile[i] > '9') return 0;
    }
    return 1;
}

// Validate email address function
int is_valid_email(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return (at && dot && at < dot);
}

// Event registration function
void register_event(const char *student_name) {
    int event_id;
    char branch[BRANCH_LEN], mobile[MOBILE_LEN], email[EMAIL_LEN];

    printf("Enter Event ID you want to participate in: ");
    event_id = get_integer_input();

    // Validate event ID
    int event_found = 0;
    for (int i = 0; i < event_count; i++) {
        if (events[i].id == event_id) {
            event_found = 1;
            break;
        }
    }
    if (!event_found) {
        printf("Event not found. Please check the Event ID.\n");
        return;
    }

    // Get and validate branch
    printf("Enter your branch: ");
    get_string_input(branch, sizeof(branch));
    if (!is_valid_name(branch)) {
        printf("Invalid branch name. Please try again.\n");
        return;
    }

    // Get and validate mobile number
    printf("Enter your mobile number: ");
    get_string_input(mobile, sizeof(mobile));
    if (!is_valid_mobile(mobile)) {
        printf("Invalid mobile number. Please try again.\n");
        return;
    }

    // Get and validate email
    printf("Enter your email address: ");
    get_string_input(email, sizeof(email));
    if (!is_valid_email(email)) {
        printf("Invalid email address. Please try again.\n");
        return;
    }

    // Registration successful
    printf("You have successfully registered for the event!\n");
}

// Function to load events from file
void load_events() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file) {
        while (fscanf(file, "%d %s %s %d %s", &events[event_count].id, 
                events[event_count].name, events[event_count].date, 
                &events[event_count].attendees, events[event_count].venue) == 5) {
            event_count++;
        }
        fclose(file);
    }
}

// Function to save events to file
void save_events() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file) {
        for (int i = 0; i < event_count; i++) {
            fprintf(file, "%d %s %s %d %s\n", events[i].id, events[i].name, 
                    events[i].date, events[i].attendees, events[i].venue);
        }
        fclose(file);
    } else {

        printf("Error: Could not save events.\n");
    }
}

// Function to add a new event
void add_event() {
    if (event_count >= MAX_EVENTS) {
        printf("Event limit reached.\n");
        return;
    }

    // Assign a unique ID (incremental)
    events[event_count].id = event_count + 1;

    // Get event name
    printf("Enter event name: ");
    get_string_input(events[event_count].name, sizeof(events[event_count].name));

    // Check for duplicate event name
    for (int i = 0; i < event_count; i++) {
        if (strcmp(events[i].name, events[event_count].name) == 0) {
            printf("Event already registered with the name '%s'. Please try a different name.\n", events[event_count].name);
            return; // Exit the function to avoid adding the event
        }
    }

    // Validate event name
    if (!is_valid_name(events[event_count].name)) {
        printf("Invalid event name. Please try again.\n");
        return;
    }

    // Get event date
    printf("Enter event date (DD-MM-YYYY): ");
    char date[11];
    get_string_input(date, sizeof(date));

    // Validate event date
    if (!is_valid_date(date)) {
        printf("Invalid date format. Please use DD-MM-YYYY.\n");
        return;
    }
    strcpy(events[event_count].date, date);

    // Get number of attendees
    printf("Enter number of attendees: ");
    events[event_count].attendees = get_integer_input();

    // Validate number of attendees
    if (!is_valid_attendees(events[event_count].attendees)) {
        printf("Invalid number of attendees. Please try again.\n");
        return;
    }

    //event venue
    printf("Enter Venue:");
    get_string_input(events[event_count].venue, sizeof(events[event_count].venue));

    event_count++;
    printf("Event added successfully with ID: %d\n", events[event_count - 1].id);

    save_events();  // Save events immediately after adding
}


// Function to delete an event
void delete_event() {
    int id;
    printf("Enter Event ID to delete: ");
    id = get_integer_input();

    int found = 0;
    for (int i = 0; i < event_count; i++) {
        if (events[i].id == id) {
            for (int j = i; j < event_count - 1; j++) {
                events[j] = events[j + 1];
            }
            event_count--;
            found = 1;
            printf("Event deleted successfully!\n");
            save_events();
            break;
        }
    }

    if (!found) {
        printf("Event with ID %d not found.\n", id);
    }
}

// Function to modify an event
void modify_event() {
    int id;
    printf("Enter Event ID to modify: ");
    id = get_integer_input();

    int found = 0;
    for (int i = 0; i < event_count; i++) {
        if (events[i].id == id) {
            printf("Modifying Event ID: %d\n", id);

            printf("Enter new Event Name: ");
            get_string_input(events[i].name, EVENT_NAME_LEN);

            // Validate event name
            if (!is_valid_name(events[i].name)) {
                printf("Invalid event name. Please use only alphabets and spaces.\n");
                return;
            }

            printf("Enter new Event Date (DD-MM-YYYY): ");
            get_string_input(events[i].date, sizeof(events[i].date));

            // Validate event date
            if (!is_valid_date(events[i].date)) {
                printf("Invalid date format. Please enter in DD-MM-YYYY format.\n");
                return;
            }

            printf("Enter new Number of Attendees: ");
            events[i].attendees = get_integer_input();

            printf("Enter new Venue: ");
            get_string_input(events[i].venue, VENUE_LEN);

            printf("Event modified successfully!\n");
            save_events();
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Event with ID %d not found.\n", id);
    }
}

// Function to view all events
void view_events() {
    printf("\nList of Events:\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-10s %-30s %-12s %-10s %-30s\n", "Event ID", "Name", "Date", "Attendees", "Venue");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < event_count; i++) {
        printf("%-10d %-30s %-12s %-10d %-30s\n", events[i].id, events[i].name, events[i].date, events[i].attendees, events[i].venue);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

// Function to view event attendees (currently placeholders)
void view_event_attendees() {
    int id;
    printf("Enter event ID to view attendees: ");
    id = get_integer_input();

    for (int i = 0; i < event_count; i++) {
        if (events[i].id == id) {
            printf("Number of attendees for event '%s' (ID: %d): %d\n", events[i].name, id, events[i].attendees);
            return;
        }
    }
    printf("Event not found.\n");
}


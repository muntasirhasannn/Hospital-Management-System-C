#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 50
#define PATIENT_FILE "patients.txt"

//=====PATIENT MANAGEMENT=====
// Structure for Patient
typedef struct
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char bloodGroup[6];
    char address[100];
    int isActive;
} Patient;

// Patient data
Patient patients[MAX_PATIENTS];

int patientCount = 0;

// Function prototypes

void addPatient();
void updatePatient();
void deletePatient();
void displayPatients();
void searchPatient();
void savePatients();
void loadPatients();
void patientMenu();

// Function to search patient by ID
int searchPatientByID(int id)
{
    // Search through all patients
    for (int i = 0; i < patientCount; i++)
    {
        // Check if patient ID matches
        if (patients[i].id == id && patients[i].isActive == 1)
        {
            return i;
        }
    }

    // Patient not found
    return -1;
}

// Function for 1. Add Patient
void addPatient()
{
    Patient p;

    printf("\n=====================================================================\n");
    printf("                         ADD NEW PATIENT\n");
    printf("=====================================================================\n");

    // Check if patient storage is full
    if (patientCount >= MAX_PATIENTS)
    {
        printf("\nPatient database is full.\n");
        return;
    }

    // 1. Enter Patient ID
    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);

    // Check for duplicate Patient ID
    if (searchPatientByID(p.id) != -1)
    {
        printf("\nA patient with this ID already exists.\n");
        return;
    }

    // 2. Enter patient name
    printf("Enter Full Name: ");
    scanf("%s", p.name);

    // 3. Enter patient age
    printf("Enter Age: ");
    scanf("%d", &p.age);

    // 4. Enter patient gender
    printf("Enter Gender: ");
    scanf("%s", p.gender);

    // 5. Enter patient phone number
    printf("Enter Phone Number: ");
    scanf("%s", p.phone);

    // 6. Enter blood group
    printf("Enter Blood Group: ");
    scanf("%s", p.bloodGroup);

    // 7. Enter address
    printf("Enter Address: ");
    scanf("%s", p.address);

    // Mark patient as active
    p.isActive = 1;

    // Store patient in array
    patients[patientCount] = p;

    patientCount++;

    // Save patient data
    savePatients();

    printf("\nPatient added successfully!\n");
}

// Function for 2. Update Patient
void updatePatient()
{
    int patientID;
    int index;

    printf("\n=====================================================================\n");
    printf("                         UPDATE PATIENT\n");
    printf("=====================================================================\n");

    // 1. Enter Patient ID
    printf("\nEnter Patient ID: ");
    scanf("%d", &patientID);

    // 2. Search for patient
    index = searchPatientByID(patientID);

    // Check if patient exists
    if (index == -1)
    {
        printf("\nPatient ID not found.\n");
        return;
    }

    // 3. Display current information
    printf("\nCurrent Patient Information:\n");
    printf("Patient ID  : %d\n", patients[index].id);
    printf("Name        : %s\n", patients[index].name);
    printf("Age         : %d\n", patients[index].age);
    printf("Gender      : %s\n", patients[index].gender);
    printf("Phone       : %s\n", patients[index].phone);
    printf("Blood Group : %s\n", patients[index].bloodGroup);
    printf("Address     : %s\n", patients[index].address);

    printf("\nEnter new information:\n");

    // 4. Update name
    printf("Enter Name: ");
    scanf("%s", patients[index].name);

    // 5. Update age
    printf("Enter Age: ");
    scanf("%d", &patients[index].age);

    // 6. Update gender
    printf("Enter Gender: ");
    scanf("%s", patients[index].gender);

    // 7. Update phone
    printf("Enter Phone Number: ");
    scanf("%s", patients[index].phone);

    // 8. Update blood group
    printf("Enter Blood Group: ");
    scanf("%s", patients[index].bloodGroup);

    // 9. Update address
    printf("Enter Address: ");
    scanf("%s", patients[index].address);

    // Save updated information
    savePatients();

    printf("\nPatient information updated successfully!\n");
}

// Function for 3. Delete Patient
void deletePatient()
{
    int patientID;
    int index;
    char choice;

    printf("\n=====================================================================\n");
    printf("                         DELETE PATIENT\n");
    printf("=====================================================================\n");

    // 1. Enter Patient ID
    printf("\nEnter Patient ID: ");
    scanf("%d", &patientID);

    // 2. Search for patient
    index = searchPatientByID(patientID);

    // Check if patient exists
    if (index == -1)
    {
        printf("\nPatient ID not found.\n");
        return;
    }

    // 3. Display patient information
    printf("\nPatient found!\n");
    printf("Patient ID  : %d\n", patients[index].id);
    printf("Name        : %s\n", patients[index].name);
    printf("Age         : %d\n", patients[index].age);
    printf("Gender      : %s\n", patients[index].gender);
    printf("Phone       : %s\n", patients[index].phone);
    printf("Blood Group : %s\n", patients[index].bloodGroup);

    // 4. Confirm deletion
    printf("\nDo you want to delete this patient? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        // Mark patient as inactive
        patients[index].isActive = 0;

        // Save updated data
        savePatients();

        printf("\nPatient deleted successfully!\n");
    }
    else
    {
        printf("\nDeletion cancelled.\n");
    }
}

// Function for 4. Display All Patients
void displayPatients()
{
    printf("=================================================================================\n");
    printf("                                 ALL PATIENTS\n");
    printf("=================================================================================\n");

    printf("%-8s %-20s %-6s %-10s %-15s %-10s %-25s\n",
           "ID",
           "Name",
           "Age",
           "Gender",
           "Phone",
           "Blood",
           "Address");

    printf("---------------------------------------------------------------------------------\n");

    int count = 0;

    // Search through all patients
    for (int i = 0; i < patientCount; i++)
    {
        // Display only active patients
        if (patients[i].isActive == 1)
        {
            count++;

            printf("%-8d %-20s %-6d %-10s %-15s %-10s %-25s\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].phone,
                   patients[i].bloodGroup,
                   patients[i].address);
        }
    }

    printf("=================================================================================\n");

    // Check if there are no active patients
    if (count == 0)
    {
        printf("No patient records found.\n");
    }
}

// Function for 5. Search Patient
void searchPatient()
{
    int patientID;
    int index;

    printf("\n=====================================================================\n");
    printf("                         SEARCH PATIENT\n");
    printf("=====================================================================\n");

    // Enter Patient ID
    printf("\nEnter Patient ID: ");
    scanf("%d", &patientID);

    // Search for patient
    index = searchPatientByID(patientID);

    // Check if patient exists
    if (index == -1)
    {
        printf("\nPatient ID not found.\n");
        return;
    }

    // Display patient information
    printf("\nPatient found!\n");

    printf("Patient ID  : %d\n", patients[index].id);
    printf("Name        : %s\n", patients[index].name);
    printf("Age         : %d\n", patients[index].age);
    printf("Gender      : %s\n", patients[index].gender);
    printf("Phone       : %s\n", patients[index].phone);
    printf("Blood Group : %s\n", patients[index].bloodGroup);
    printf("Address     : %s\n", patients[index].address);
}

// Sorting patients by name

  void sortPatientsByName()
{
    int i, j;
    Patient temp;

    for (i = 0; i < patientCount - 1; i++)
    {
        for (j = i + 1; j < patientCount; j++)
        {
            if (strcmp(patients[i].name, patients[j].name) > 0)
            {
                temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
}

// Function to save patients to file
void savePatients()
{
    FILE *file;

    // Open patient file for writing
    file = fopen(PATIENT_FILE, "w");

    if (file == NULL)
    {
        printf("\nError opening patient file.\n");
        return;
    }



    // Save all active patients
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].isActive == 1)
        {
            fprintf(file,
                    "%d %s %d %s %s %s %s\n",
                    patients[i].id,
                    patients[i].name,
                    patients[i].age,
                    patients[i].gender,
                    patients[i].phone,
                    patients[i].bloodGroup,
                    patients[i].address);
        }
    }

    // Close file
    fclose(file);
}

// Function to load patients from file
void loadPatients()
{
    FILE *file;

    // Open patient file for reading
    file = fopen(PATIENT_FILE, "r");

    // If file doesn't exist, start with empty database
    if (file == NULL)
    {
        return;
    }

    patientCount = 0;

    // Read patients from file
   while (fscanf(file, "%d %s %d %s %s %s %s",
              &patients[patientCount].id,
              patients[patientCount].name,
              &patients[patientCount].age,
              patients[patientCount].gender,
              patients[patientCount].phone,
              patients[patientCount].bloodGroup,
              patients[patientCount].address) == 7)
{
    patientCount++;
}
    // Close file
    fclose(file);
}

// Patient Management Menu
void patientMenu()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("=====================================================================\n");
        printf("                         PATIENT MANAGEMENT\n");
        printf("=====================================================================\n");

        printf("1. Add Patient\n");
        printf("2. Update Patient\n");
        printf("3. Delete Patient\n");
        printf("4. Display All Patients\n");
        printf("5. Search Patient\n");
        printf("6. Return to Main Menu\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char choice_01;

            while (1)
            {
                addPatient();

                printf("\nDo you want to return to Patient Management Menu? (Y/N): ");
                scanf(" %c", &choice_01);

                if (choice_01 == 'Y' || choice_01 == 'y')
                {
                    break;
                }
                else if (choice_01 == 'N' || choice_01 == 'n')
                {
                    continue;
                }
                else
                {
                    printf("\nInvalid choice! Please enter Y or N.\n");
                }
            }

            break;
        }

        case 2:
        {
            char choice_02;

            while (1)
            {
                updatePatient();

                printf("\nDo you want to return to Patient Management Menu? (Y/N): ");
                scanf(" %c", &choice_02);

                if (choice_02 == 'Y' || choice_02 == 'y')
                {
                    break;
                }
                else if (choice_02 == 'N' || choice_02 == 'n')
                {
                    continue;
                }
                else
                {
                    printf("\nInvalid choice! Please enter Y or N.\n");
                }
            }

            break;
        }

        case 3:
        {
            char choice_03;

            while (1)
            {
                deletePatient();

                printf("\nDo you want to return to Patient Management Menu? (Y/N): ");
                scanf(" %c", &choice_03);

                if (choice_03 == 'Y' || choice_03 == 'y')
                {
                    break;
                }
                else if (choice_03 == 'N' || choice_03 == 'n')
                {
                    continue;
                }
                else
                {
                    printf("\nInvalid choice! Please enter Y or N.\n");
                }
            }

            break;
        }

        case 4:
        {
            char choice_04;

            while (1)
            {
                displayPatients();

                printf("\nDo you want to return to Patient Management Menu? (Y/N): ");
                scanf(" %c", &choice_04);

                if (choice_04 == 'Y' || choice_04 == 'y')
                {
                    break;
                }
                else if (choice_04 == 'N' || choice_04 == 'n')
                {
                    continue;
                }
                else
                {
                    printf("\nInvalid choice! Please enter Y or N.\n");
                }
            }

            break;
        }

        case 5:
        {
            char choice_05;

            while (1)
            {
                searchPatient();

                printf("\nDo you want to return to Patient Management Menu? (Y/N): ");
                scanf(" %c", &choice_05);

                if (choice_05 == 'Y' || choice_05 == 'y')
                {
                    break;
                }
                else if (choice_05 == 'N' || choice_05 == 'n')
                {
                    continue;
                }
                else
                {
                    printf("\nInvalid choice! Please enter Y or N.\n");
                }
            }

            break;
        }

        case 6:
            printf("\nReturning to Main Menu...\n");
            return;

        default:
            printf("\nInvalid choice! Please try again!\n");
        }
    }
}

//=====ROOM MANAGEMENT=====
// Structure for Room and Bed
typedef struct
{
    int roomNo;
    char roomType[20];
    char bedNo[10];
    int charge;
    int occupied;
    int patientID;
} Bed;

// Bed data
Bed beds[18] =
    {
        // FLOOR 01

        {101, "General", "B1", 1245, 0, -1},
        {101, "General", "B2", 1245, 1, 1005},
        {102, "Cabin", "B1", 2500, 0, -1},
        {103, "Cabin", "B1", 2500, 0, -1},
        {104, "ICU", "B1", 5000, 1, 1010},
        {105, "ICU", "B1", 5000, 0, -1},

        // FLOOR 02

        {201, "General", "B1", 1245, 1, 1085},
        {201, "General", "B2", 1245, 1, 1067},
        {202, "Cabin", "B1", 2500, 0, -1},
        {203, "Cabin", "B1", 2500, 1, 1025},
        {204, "ICU", "B1", 5000, 0, -1},
        {205, "ICU", "B1", 5000, 0, -1},

        // FLOOR 03

        {301, "General", "B1", 1245, 1, 1049},
        {301, "General", "B2", 1245, 0, -1},
        {302, "Cabin", "B1", 2500, 0, -1},
        {303, "Cabin", "B1", 2500, 0, -1},
        {304, "ICU", "B1", 5000, 1, 1080},
        {305, "ICU", "B1", 5000, 1, 1078}};

// Function for 1. View All Rooms and Beds
void viewAllBeds(Bed beds[], int totalBeds)
{
    printf("\n");
    printf("==========================================================================\n");
    printf("                              ALL ROOMS & BEDS\n");
    printf("==========================================================================\n");

    printf("%-10s %-15s %-10s %-12s %-12s %-10s\n",
           "Room No.", "Room Type", "Bed No.", "Charge/Day", "Status", "Patient ID");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < totalBeds; i++)
    {
        printf("%-10d %-15s %-10s %-12d ",
               beds[i].roomNo,
               beds[i].roomType,
               beds[i].bedNo,
               beds[i].charge);

        if (beds[i].occupied == 0)
        {
            printf("%-12s %-10s\n", "Available", "-");
        }
        else
        {
            printf("%-12s %-10d\n",
                   "Occupied",
                   beds[i].patientID);
        }
    }

    printf("=====================================================================\n");
}

// Function for 2. Admit Patient
// Displays only available rooms and beds
void displayAvailableBeds()
{
    printf("\n");
    printf("=====================================================================\n");
    printf("                       AVAILABLE ROOMS & BEDS\n");
    printf("=====================================================================\n");

    printf("%-5s %-10s %-15s %-10s %-12s\n",
           "No.", "Room No.", "Room Type", "Bed No.", "Charge/Day");

    printf("---------------------------------------------------------------------\n");

    int count = 0;

    for (int i = 0; i < 18; i++)
    {
        if (beds[i].occupied == 0)
        {
            count++;

            printf("%-5d %-10d %-15s %-10s %-12d\n",
                   count,
                   beds[i].roomNo,
                   beds[i].roomType,
                   beds[i].bedNo,
                   beds[i].charge);
        }
    }

    printf("=====================================================================\n");

    if (count == 0)
    {
        printf("No beds are currently available.\n");
    }
}

// Function for 2. Admit Patient - UPDATED
void assignBed(Bed beds[], int size)
{
    int patientID;
    int roomNo;
    char bedNo[10];
    int patientIndex;

    printf("\n===== ASSIGN BED =====\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    // Search for patient in the patient database
    patientIndex = searchPatientByID(patientID);

    if (patientIndex != -1)
    {
        // Patient found - display their information
        printf("\n===== PATIENT INFORMATION =====\n");
        printf("Patient ID      : %d\n", patients[patientIndex].id);
        printf("Patient Name    : %s\n", patients[patientIndex].name);
        printf("Age             : %d\n", patients[patientIndex].age);
        printf("Gender          : %s\n", patients[patientIndex].gender);
        printf("Phone           : %s\n", patients[patientIndex].phone);
        printf("Blood Group     : %s\n", patients[patientIndex].bloodGroup);
        printf("Address         : %s\n\n", patients[patientIndex].address);
    }
    else
    {
        // Patient not found
        printf("\nWarning: Patient ID not found in records.\n");
        printf("Proceeding with bed assignment anyway...\n\n");
    }

    printf("Enter Room No.: ");
    scanf("%d", &roomNo);

    printf("Enter Bed No.: ");
    scanf("%s", bedNo);

    // Search through all beds
    for (int i = 0; i < size; i++)
    {
        // Check if the Room Number and Bed Number match
        if (beds[i].roomNo == roomNo &&
            strcmp(beds[i].bedNo, bedNo) == 0)
        {
            // Check if the selected bed is available
            if (beds[i].occupied == 0)
            {
                // Assign the Patient ID to the bed
                beds[i].patientID = patientID;

                // Change the bed status from Available to Occupied
                beds[i].occupied = 1;

                // Display confirmation message
                printf("\n===== BED ASSIGNMENT CONFIRMED =====\n");
                printf("Patient ID : %d\n", beds[i].patientID);
                printf("Room No.   : %d\n", beds[i].roomNo);
                printf("Bed No.    : %s\n", beds[i].bedNo);
                printf("Charge/Day : %d Tk\n", beds[i].charge);
                printf("Status     : Occupied\n");
                printf("=====================================\n");

                // Stop the function after successfully assigning the bed
                return;
            }
            else
            {
                // The selected bed is already occupied
                printf("\nThis bed is already occupied.\n");
                return;
            }
        }
    }

    printf("\nRoom or bed not found.\n");
}

// Function for 3. Discharge Patient
void dischargePatient(Bed beds[], int size)
{
    int patientID;
    char choice;

    printf("\n===== DISCHARGE PATIENT =====\n");

    // 1. Enter Patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    // 2. Find patient's room and bed
    for (int i = 0; i < size; i++)
    {
        if (beds[i].patientID == patientID)
        {
            printf("\nPatient found!\n");
            printf("Patient ID : %d\n", beds[i].patientID);
            printf("Room No.   : %d\n", beds[i].roomNo);
            printf("Bed No.    : %s\n", beds[i].bedNo);
            printf("Status     : Occupied\n");

            // 3. Confirm discharge
            printf("\nDo you want to discharge this patient? (Y/N): ");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y')
            {
                // 4. Free the room/bed
                beds[i].occupied = 0;

                // 5. Remove patient assignment
                beds[i].patientID = -1;

                printf("\nPatient discharged successfully!\n");
                printf("Room %d - Bed %s is now Available.\n",
                       beds[i].roomNo,
                       beds[i].bedNo);

                return;
            }
            else
            {
                printf("\nDischarge cancelled.\n");
                return;
            }
        }
    }

    printf("\nPatient ID not found.\n");
}

//=====APPOINTMENT MANAGEMENT=====
// -------------------- STRUCTURES --------------------



struct Doctor
{
    int id;
    char name[50];
    char specialization[50];
};

struct Appointment
{
    int id;
    int patientID;
    int doctorID;
    char date[20];
    char time[10];
    char status[20];
};

// -------------------- DOCTOR DATA --------------------

struct Doctor doctors[MAX_DOCTORS] = {
    {201, "Dr. Khan", "Cardiologist"},
    {202, "Dr. Smith", "Dentist"},
    {203, "Dr. Ahmed", "Dermatologist"},
    {204, "Dr. Lee", "Neurologist"},
    {205, "Dr. Sara", "Pediatrician"},
    {206, "Dr. Johnson", "Orthopedist"},
    {207, "Dr. Williams", "Oncologist"},
    {208, "Dr. Brown", "Psychiatrist"},
    {209, "Dr. Jones", "Urologist"},
    {210, "Dr. Garcia", "Gastroenterologist"},
    {211, "Dr. Martinez", "Ophthalmologist"},
    {212, "Dr. Taylor", "Rheumatologist"},
    {213, "Dr. Anderson", "Endocrinologist"},
    {214, "Dr. Thomas", "Nephrologist"},
    {215, "Dr. Moore", "Pulmonologist"},
    {216, "Dr. Jackson", "Hematologist"},
    {217, "Dr. White", "Immunologist"},
    {218, "Dr. Harris", "Infectiologist"},
    {219, "Dr. Martin", "Hepatologist"},
    {220, "Dr. Thompson", "Cardiologist"},
    {221, "Dr. Garcia", "Neurologist"},
    {222, "Dr. Rodriguez", "Dentist"},
    {223, "Dr. Wilson", "Dermatologist"},
    {224, "Dr. Davis", "Ophthalmologist"},
    {225, "Dr. Hernandez", "Orthopedist"},
    {226, "Dr. Lopez", "Psychiatrist"},
    {227, "Dr. Gonzalez", "Urologist"},
    {228, "Dr. Perez", "Gastroenterologist"},
    {229, "Dr. Sanchez", "Pediatrician"},
    {230, "Dr. Ramirez", "Oncologist"},
    {231, "Dr. Torres", "Rheumatologist"},
    {232, "Dr. Flores", "Endocrinologist"},
    {233, "Dr. Rivera", "Nephrologist"},
    {234, "Dr. Cruz", "Pulmonologist"},
    {235, "Dr. Morales", "Hematologist"},
    {236, "Dr. Guerrero", "Immunologist"},
    {237, "Dr. Calderon", "Infectiologist"},
    {238, "Dr. Romero", "Hepatologist"},
    {239, "Dr. Castro", "Cardiologist"},
    {240, "Dr. Vargas", "Neurologist"},
    {241, "Dr. Campos", "Dentist"},
    {242, "Dr. Fuentes", "Dermatologist"},
    {243, "Dr. Rivas", "Ophthalmologist"},
    {244, "Dr. Salazar", "Orthopedist"},
    {245, "Dr. Delgado", "Psychiatrist"},
    {246, "Dr. Valenzuela", "Urologist"},
    {247, "Dr. Silva", "Gastroenterologist"},
    {248, "Dr. Espinoza", "Pediatrician"},
    {249, "Dr. Araya", "Oncologist"},
    {250, "Dr. Muñoz", "Rheumatologist"},
};

// -------------------- APPOINTMENTS --------------------

struct Appointment appointments[MAX_APPOINTMENTS];

int appointmentCount = 0;

// -------------------- FIND PATIENT --------------------

int findPatient(int id)
{
    int i;

    for (i = 0; i < patientCount; i++)
{
    if (patients[i].id == id && patients[i].isActive == 1)
    {
        return i;
    }
}

    return -1;
}

// -------------------- FIND DOCTOR --------------------

int findDoctor(int id)
{
    int i;

    for (i = 0; i < MAX_DOCTORS; i++)
    {
        if (doctors[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// -------------------- FIND APPOINTMENT --------------------

int findAppointment(int id)
{
    int i;

    for (i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

// -------------------- BOOK APPOINTMENT --------------------

void bookAppointment()
{

    int appointmentID;
    int patientID;
    int doctorID;

    int patientIndex;
    int doctorIndex;

    printf("\n===== BOOK APPOINTMENT =====\n");

    // Appointment ID
    printf("Enter Appointment ID: ");
    scanf("%d", &appointmentID);

    // Check if appointment ID already exists
    if (findAppointment(appointmentID) != -1)
    {
        printf("This Appointment ID already exists.\n");
        return;
    }

    // Patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    patientIndex = searchPatientByID(patientID);

    if (patientIndex == -1)
    {
        printf("Patient not found in records.\n");
        return;
    }

    // Display patient information from patient records
    printf("\n===== PATIENT INFORMATION =====\n");
    printf("Patient ID      : %d\n", patients[patientIndex].id);
    printf("Patient Name    : %s\n", patients[patientIndex].name);
    printf("Age             : %d\n", patients[patientIndex].age);
    printf("Gender          : %s\n", patients[patientIndex].gender);
    printf("Phone           : %s\n", patients[patientIndex].phone);
    printf("Blood Group     : %s\n", patients[patientIndex].bloodGroup);
    printf("Address         : %s\n\n", patients[patientIndex].address);

    // Doctor ID
    printf("Enter Doctor ID: ");
    scanf("%d", &doctorID);

    doctorIndex = findDoctor(doctorID);

    if (doctorIndex == -1)
    {
        printf("Doctor not found.\n");
        return;
    }

    printf("\n===== DOCTOR INFORMATION =====\n");
    printf("Doctor ID       : %d\n", doctors[doctorIndex].id);
    printf("Doctor Name     : %s\n", doctors[doctorIndex].name);
    printf("Specialization  : %s\n\n", doctors[doctorIndex].specialization);

    // Date
    printf("Enter Appointment Date (DD/MM/YYYY): ");
    scanf("%s", appointments[appointmentCount].date);

    // Time
    printf("Enter Appointment Time (HH:MM): ");
    scanf("%s", appointments[appointmentCount].time);

    // Save appointment information
    appointments[appointmentCount].id = appointmentID;

    appointments[appointmentCount].patientID = patientID;

    appointments[appointmentCount].doctorID = doctorID;

    strcpy(appointments[appointmentCount].status, "Confirmed");

    // Display confirmation
    printf("\n====================================\n");
    printf("       APPOINTMENT CONFIRMED\n");
    printf("====================================\n");

    printf("Appointment ID : %d\n", appointmentID);

    printf("Patient Name   : %s\n", patients[patientIndex].name);

    printf("Patient ID     : %d\n", patientID);

    printf("Doctor Name    : %s\n", doctors[doctorIndex].name);

    printf("Doctor ID      : %d\n", doctorID);

    printf("Specialization : %s\n", doctors[doctorIndex].specialization);

    printf("Date           : %s\n", appointments[appointmentCount].date);

    printf("Time           : %s\n", appointments[appointmentCount].time);

    printf("Status         : Confirmed\n");

    printf("=====================================================================\n");

    appointmentCount++;
}

// -------------------- CANCEL APPOINTMENT --------------------

void cancelAppointment()
{

    int id;
    int index;
    char choice;

    printf("\n===== CANCEL APPOINTMENT =====\n");

    printf("Enter Appointment ID: ");
    scanf("%d", &id);

    index = findAppointment(id);

    if (index == -1)
    {
        printf("Appointment not found.\n");
        return;
    }

    // Check if already cancelled
    if (strcmp(appointments[index].status, "Cancelled") == 0)
    {
        printf("This appointment is already cancelled.\n");
        return;
    }

    // Display appointment details
    int patientIndex;
    int doctorIndex;

    patientIndex = findPatient(appointments[index].patientID);

    doctorIndex = findDoctor(appointments[index].doctorID);

    printf("\nAppointment Details\n");
    printf("-----------------------------\n");

    printf("Appointment ID : %d\n",
           appointments[index].id);

    printf("Patient        : %s\n",
           patients[patientIndex].name);

    printf("Doctor         : %s\n",
           doctors[doctorIndex].name);

    printf("Date           : %s\n",
           appointments[index].date);

    printf("Time           : %s\n",
           appointments[index].time);

    printf("Status         : %s\n",
           appointments[index].status);

    // Ask for confirmation
    printf("\nDo you want to cancel this appointment? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {

        strcpy(appointments[index].status, "Cancelled");

        printf("\nAppointment cancelled successfully.\n");
    }
    else
    {

        printf("\nAppointment was not cancelled.\n");
    }
}

// -------------------- VIEW APPOINTMENTS --------------------

void viewAppointments()
{

    int i;

    sortPatientsByName();

    printf("\n");
    printf("=====================================================================\n");
    printf("                          VIEW APPOINTMENTS\n");
    printf("=====================================================================\n");

    if (appointmentCount == 0)
    {

        printf("No appointments found.\n");

        return;
    }

    for (i = 0; i < appointmentCount; i++)
    {

        int patientIndex;
        int doctorIndex;

        patientIndex =
            findPatient(appointments[i].patientID);

        doctorIndex =
            findDoctor(appointments[i].doctorID);

        printf("\nAppointment %d\n", i + 1);

        printf("-----------------------------\n");

        printf("Appointment ID : %d\n",
               appointments[i].id);

        printf("Patient        : %s\n",
               patients[patientIndex].name);

        printf("Doctor         : %s\n",
               doctors[doctorIndex].name);

        printf("Date           : %s\n",
               appointments[i].date);

        printf("Time           : %s\n",
               appointments[i].time);

        printf("Status         : %s\n",
               appointments[i].status);
    }

    printf("\n=====================================================================\n");
}

// -------------------- VIEW PATIENTS --------------------

void viewPatients()
{
    int i;

    printf("\n");
    printf("=================================================================================\n");
    printf("                              ALL REGISTERED PATIENTS\n");
    printf("=================================================================================\n");

    // Load fresh data from file to ensure we have latest patient records
    loadPatients();
    sortPatientsByName();
    if (patientCount == 0)
    {
        printf("No patient records found.\n");
        return;
    }

    printf("%-8s %-20s %-6s %-10s %-15s %-10s %-25s\n",
           "ID",
           "Name",
           "Age",
           "Gender",
           "Phone",
           "Blood",
           "Address");

    printf("---------------------------------------------------------------------------------\n");

    for (i = 0; i < patientCount; i++)
    {
        if (patients[i].isActive == 1)
        {
            printf("%-8d %-20s %-6d %-10s %-15s %-10s %-25s\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].gender,
                   patients[i].phone,
                   patients[i].bloodGroup,
                   patients[i].address);
        }
    }

    printf("=================================================================================\n");
}

// -------------------- VIEW DOCTORS --------------------

void viewDoctors()
{

    int i;

    printf("\n");
    printf("=====================================================================\n");
    printf("                              DOCTORS\n");
    printf("=====================================================================\n");

    for (i = 0; i < MAX_DOCTORS; i++)
    {

        printf("\nDoctor ID      : %d\n",
               doctors[i].id);

        printf("Doctor Name    : %s\n",
               doctors[i].name);

        printf("Specialization : %s\n",
               doctors[i].specialization);
    }
}

//=====BILLING MANAGEMENT=====
struct Bill
{
    int patientID;
    char patientName[50];

    int stayDays;

    double consultationFee;
    double roomCharge;
    double medicineCost;

    double totalBill;
    double finalBill;

    double amountPaid;
    double dueAmount;

    char status[20];
};

struct Bill bills[50];

int billCount = 0;

// Generate Bill

void generateBill()
{
    int patientIndex;
    int patientID;
    char choice;

    printf("\n");
    printf("=====================================================================\n");
    printf("                         GENERATE BILL\n");
    printf("=====================================================================\n");

    // Ask for patient ID and try to auto-fill patient info
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    patientIndex = searchPatientByID(patientID);

    if (patientIndex != -1)
    {
        // Patient found in patients[] array — auto-fill name and show info
        printf("\nPatient found:\n");
        printf("Patient ID  : %d\n", patients[patientIndex].id);
        printf("Patient Name: %s\n", patients[patientIndex].name);
        printf("Age         : %d\n", patients[patientIndex].age);
        printf("Gender      : %s\n", patients[patientIndex].gender);
        printf("Phone       : %s\n", patients[patientIndex].phone);
        printf("Blood Group : %s\n", patients[patientIndex].bloodGroup);
        printf("Address     : %s\n\n", patients[patientIndex].address);

        bills[billCount].patientID = patientID;
        strncpy(bills[billCount].patientName,
                patients[patientIndex].name,
                sizeof(bills[billCount].patientName) - 1);
        bills[billCount].patientName[sizeof(bills[billCount].patientName) - 1] = '\0';
    }
    else
    {
        // Patient not found: allow manual entry or cancel
        printf("\nPatient not found in records.\n");
        printf("Do you want to enter patient name manually? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y')
        {
            bills[billCount].patientID = patientID;
            printf("Enter Patient Name: ");
            scanf("%s", bills[billCount].patientName);
        }
        else
        {
            printf("Bill generation cancelled.\n");
            return;
        }
    }

    // Continue collecting bill details
    printf("Enter Stay Days: ");
    scanf("%d", &bills[billCount].stayDays);

    printf("Enter Consultation Fee: ");
    scanf("%lf", &bills[billCount].consultationFee);

    printf("Enter Room Charge: ");
    scanf("%lf", &bills[billCount].roomCharge);

    printf("Enter Medicine Cost: ");
    scanf("%lf", &bills[billCount].medicineCost);

    bills[billCount].totalBill =
        bills[billCount].consultationFee +
        bills[billCount].roomCharge +
        bills[billCount].medicineCost;

    bills[billCount].finalBill = bills[billCount].totalBill;

    // 10% discount if stay more than 10 days
    if (bills[billCount].stayDays > 10)
    {
        bills[billCount].finalBill =
            bills[billCount].totalBill - (bills[billCount].totalBill * 0.10);

        printf("\n10%% Discount Applied!\n");
    }

    printf("\nEnter Amount Paid: ");
    scanf("%lf", &bills[billCount].amountPaid);

    bills[billCount].dueAmount =
        bills[billCount].finalBill - bills[billCount].amountPaid;

    if (bills[billCount].dueAmount <= 0.0)
    {
        bills[billCount].dueAmount = 0.0;
        strcpy(bills[billCount].status, "Paid");
    }
    else
    {
        strcpy(bills[billCount].status, "Due");
    }

    printf("\nBill Generated Successfully!\n");

    printf("\nTotal Bill: %.2lf Tk\n", bills[billCount].totalBill);
    printf("Final Bill: %.2lf Tk\n", bills[billCount].finalBill);
    printf("Due Amount: %.2lf Tk\n", bills[billCount].dueAmount);

    billCount++;
}

// View Bill

void viewBill()
{
    int patientID;
    int found = 0;

    printf("\nEnter Patient ID: ");
    scanf("%d", &patientID);

    for (int i = 0; i < billCount; i++)
    {

        if (bills[i].patientID == patientID)
        {

            found = 1;

            printf("\n");
            printf("=====================================================================\n");
            printf("                         BILL DETAILS\n");
            printf("=====================================================================\n");

            printf("Patient ID      : %d\n",
                   bills[i].patientID);

            printf("Patient Name    : %s\n",
                   bills[i].patientName);

            printf("Stay Days       : %d\n",
                   bills[i].stayDays);

            printf("Total Bill      : %.2lf Tk\n",
                   bills[i].totalBill);

            printf("Final Bill      : %.2lf Tk\n",
                   bills[i].finalBill);

            printf("Amount Paid     : %.2lf Tk\n",
                   bills[i].amountPaid);

            printf("Due Amount      : %.2lf Tk\n",
                   bills[i].dueAmount);

            printf("Status          : %s\n",
                   bills[i].status);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nPatient Bill Not Found!\n");
    }
}

// Payment

void payment()
{
    int patientID;
    double amount;

    printf("\nEnter Patient ID: ");
    scanf("%d", &patientID);

    for (int i = 0; i < billCount; i++)
    {

        if (bills[i].patientID == patientID)
        {

            printf("Current Due Amount: %.2lf Tk\n",
                   bills[i].dueAmount);

            printf("Enter Payment Amount: ");
            scanf("%lf", &amount);

            bills[i].amountPaid =
                bills[i].amountPaid + amount;

            bills[i].dueAmount =
                bills[i].finalBill -
                bills[i].amountPaid;

            if (bills[i].dueAmount == 0)
            {
                strcpy(bills[i].status, "Paid");
            }

            else
            {
                strcpy(bills[i].status, "Due");
            }

            printf("\nPayment Updated Successfully!\n");

            printf("Remaining Due: %.2lf Tk\n",
                   bills[i].dueAmount);

            return;
        }
    }

    printf("\nPatient Bill Not Found!\n");
}

int main()
{
    while (1)
    {
        int choice;

        printf("\n");
        printf("=====================================================================\n");
        printf("                         HOSPITAL MANAGEMENT SYSTEM\n");
        printf("=====================================================================\n");

        printf("1. Patient Management\n");
        printf("2. Room Management\n");
        printf("3. Appointment Management\n");
        printf("4. Billing Management\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            loadPatients();
            patientMenu();
            break;

        case 2:
        {
            int choice;

            while (1)
            {
                printf("\n");
                printf("=====================================================================\n");
                printf("                         ROOM MANAGEMENT\n");
                printf("=====================================================================\n");

                printf("1. View All Rooms and Beds\n");
                printf("2. Admit Patient\n");
                printf("3. Discharge Patient\n");
                printf("4. Return to Main Menu\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                {
                    char choice_02;

                    while (1)
                    {
                        viewAllBeds(beds, 18);

                        printf("\nDo you want to return to Room Management Menu? (Y/N): ");
                        scanf(" %c", &choice_02);

                        if (choice_02 == 'Y' || choice_02 == 'y')
                        {
                            break;
                        }
                        else if (choice_02 == 'N' || choice_02 == 'n')
                        {
                            continue;
                        }
                        else
                        {
                            printf("\nInvalid choice! Please enter Y or N.\n");
                        }
                    }

                    break;
                }

                case 2:
                {
                    char choice_03;

                    while (1)
                    {
                        displayAvailableBeds();
                        assignBed(beds, 18);

                        printf("\nDo you want to return to Room Management Menu? (Y/N): ");
                        scanf(" %c", &choice_03);

                        if (choice_03 == 'Y' || choice_03 == 'y')
                        {
                            break;
                        }
                        else if (choice_03 == 'N' || choice_03 == 'n')
                        {
                            continue;
                        }
                        else
                        {
                            printf("\nInvalid choice! Please enter Y or N.\n");
                        }
                    }

                    break;
                }

                case 3:
                    dischargePatient(beds, 18);
                    break;

                case 4:
                    printf("\nReturning to Main Menu...\n");
                    goto mainMenu;

                default:
                    printf("\nInvalid choice! Please try again!\n");
                }
            }

            break;
        }

        case 3:
        {
            int choice;

            do
            {

                printf("\n");
                printf("=====================================================================\n");
                printf("                         HOSPITAL APPOINTMENT SYSTEM\n");
                printf("=====================================================================\n");

                printf("1. Book Appointment\n");
                printf("2. Cancel Appointment\n");
                printf("3. View Appointments\n");
                printf("4. View Patients\n");
                printf("5. View Doctors\n");
                printf("6. Return to main menu\n");

                printf("=====================================================================\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {

                case 1:
                    bookAppointment();
                    break;

                case 2:
                    cancelAppointment();
                    break;

                case 3:
                    viewAppointments();
                    break;

                case 4:
                    viewPatients();
                    break;

                case 5:
                    viewDoctors();
                    break;

                case 6:
                    printf("\nReturning to main menu...\n");
                    break;

                default:
                    printf("\nInvalid choice. Please try again.\n");
                }

            } while (choice!= 0);
            break;
        }

        case 4:{
            int choice;

            while (1)
            {

                printf("\n");
                printf("=====================================================================\n");
                printf("                         BILLING MANAGEMENT\n");
                printf("=====================================================================\n");

                printf("1. Generate Bill\n");
                printf("2. View Bill\n");
                printf("3. Payment\n");
                printf("4. Return to Main Menu\n");

                printf("\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {

                case 1:
                    generateBill();
                    break;

                case 2:
                    viewBill();
                    break;

                case 3:
                    payment();
                    break;

                case 4:
                    printf("\nReturning to Main Menu...\n");
                    goto mainMenu;

                default:
                    printf("\nInvalid Choice!\n");
                }
            }
            break;}

        case 5:
            printf("\nExiting program...\n");
            return 0;

        default:
            printf("\nInvalid choice! Please try again!\n");
        }

    mainMenu:;
    }

    return 0;
}

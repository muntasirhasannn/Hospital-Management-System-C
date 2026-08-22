#include <stdio.h>
#include <math.h>
#include <strings.h>

// Structure for Room and Bed
typedef struct
{
    int roomNo;
    char roomType[20];
    char bedNo[10];
    int charge;
    int occupied;
    int patientID;
}Bed;

// Bed data
Bed beds[18] =
{
    //FLOOR 01

    {101, "General", "B1", 1245, 0, -1},
    {101, "General", "B2", 1245, 1, 1005},
    {102, "Cabin",   "B1", 2500, 0, -1},
    {103, "Cabin",   "B1", 2500, 0, -1},
    {104, "ICU",     "B1", 5000, 1, 1010},
    {105, "ICU",     "B1", 5000, 0, -1},

    //FLOOR 02

    {201, "General", "B1", 1245, 1, 1085},
    {201, "General", "B2", 1245, 1, 1067},
    {202, "Cabin",   "B1", 2500, 0, -1},
    {203, "Cabin",   "B1", 2500, 1, 1025},
    {204, "ICU",     "B1", 5000, 0, -1},
    {205, "ICU",     "B1", 5000, 0, -1},

    //FLOOR 03

    {301, "General", "B1", 1245, 1, 1049},
    {301, "General", "B2", 1245, 0, -1},
    {302, "Cabin",   "B1", 2500, 0, -1},
    {303, "Cabin",   "B1", 2500, 0, -1},
    {304, "ICU",     "B1", 5000, 1, 1080},
    {305, "ICU",     "B1", 5000, 1, 1078}
};


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


// Function for 2. Admit Patient
void assignBed(Bed beds[], int size)
{
    int patientID;
    int roomNo;
    char bedNo[10];

    printf("\n===== ASSIGN BED =====\n");

    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

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
                printf("\nBed assigned successfully!\n");
                printf("Patient ID : %d\n", beds[i].patientID);
                printf("Room No.   : %d\n", beds[i].roomNo);
                printf("Bed No.    : %s\n", beds[i].bedNo);
                printf("Status     : Occupied\n");

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

int main()
{
    while (1)
    {
        int choiceee;

        printf("\n");
        printf("=====================================================================\n");
        printf("                         HOSPITAL MANAGEMENT SYSTEM\n");
        printf("=====================================================================\n");

        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Room Management\n");
        printf("4. Appointment Management\n");
        printf("5. Billing Management\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choiceee);

        switch (choiceee)
        {
            case 1:
                printf("\nPatient Management selected.\n");
                break;

            case 2:
                printf("\nDoctor Management selected.\n");
                break;

            case 3:
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

            case 4:
                printf("\nAppointment Management selected.\n");
                break;

            case 5:
                printf("\nBilling Management selected.\n");
                break;

            case 6:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again!\n");
        }

        mainMenu:
        ;
    }

    return 0;
}
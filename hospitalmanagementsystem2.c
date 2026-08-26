#include <stdio.h>
#include <string.h>


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

    printf("\n");
    printf("=====================================================================\n");
    printf("                         GENERATE BILL\n");
    printf("=====================================================================\n");


    printf("Enter Patient ID: ");
    scanf("%d",&bills[billCount].patientID);


    printf("Enter Patient Name: ");
    scanf("%s",bills[billCount].patientName);


    printf("Enter Stay Days: ");
    scanf("%d",&bills[billCount].stayDays);



    printf("Enter Consultation Fee: ");
    scanf("%lf",&bills[billCount].consultationFee);


    printf("Enter Room Charge: ");
    scanf("%lf",&bills[billCount].roomCharge);


    printf("Enter Medicine Cost: ");
    scanf("%lf",&bills[billCount].medicineCost);



    bills[billCount].totalBill =
    bills[billCount].consultationFee +
    bills[billCount].roomCharge +
    bills[billCount].medicineCost;



    bills[billCount].finalBill =
    bills[billCount].totalBill;



    // 10% discount if stay more than 10 days

    if(bills[billCount].stayDays > 10)
    {
        bills[billCount].finalBill =
        bills[billCount].totalBill -
        (bills[billCount].totalBill * 10 / 100);


        printf("\n10%% Discount Applied!\n");
    }



    printf("\nEnter Amount Paid: ");
    scanf("%lf",&bills[billCount].amountPaid);



    bills[billCount].dueAmount =
    bills[billCount].finalBill -
    bills[billCount].amountPaid;



    if(bills[billCount].dueAmount == 0)
    {
        strcpy(bills[billCount].status,"Paid");
    }

    else
    {
        strcpy(bills[billCount].status,"Due");
    }



    printf("\nBill Generated Successfully!\n");


    printf("\nTotal Bill: %.2lf Tk\n",
    bills[billCount].totalBill);


    printf("Final Bill: %.2lf Tk\n",
    bills[billCount].finalBill);


    printf("Due Amount: %.2lf Tk\n",
    bills[billCount].dueAmount);



    billCount++;

}



// View Bill

void viewBill()
{
    int patientID;
    int found = 0;


    printf("\nEnter Patient ID: ");
    scanf("%d",&patientID);



    for(int i=0; i<billCount; i++)
    {

        if(bills[i].patientID == patientID)
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



    if(found == 0)
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
    scanf("%d",&patientID);



    for(int i=0; i<billCount; i++)
    {

        if(bills[i].patientID == patientID)
        {

            printf("Current Due Amount: %.2lf Tk\n",
            bills[i].dueAmount);



            printf("Enter Payment Amount: ");
            scanf("%lf",&amount);



            bills[i].amountPaid =
            bills[i].amountPaid + amount;



            bills[i].dueAmount =
            bills[i].finalBill -
            bills[i].amountPaid;



            if(bills[i].dueAmount == 0)
            {
                strcpy(bills[i].status,"Paid");
            }

            else
            {
                strcpy(bills[i].status,"Due");
            }



            printf("\nPayment Updated Successfully!\n");


            printf("Remaining Due: %.2lf Tk\n",
            bills[i].dueAmount);



            return;

        }

    }


    printf("\nPatient Bill Not Found!\n");

}



// Billing Menu

void billingManagement()
{
    int choice;


    while(1)
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
        scanf("%d",&choice);



        switch(choice)
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
                return;


            default:
                printf("\nInvalid Choice!\n");

        }

    }

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void adminLogin();
void userLogin();
void addChannels();
void modifyChannelPrice();
void modifyDiscount();
void viewalldiscounts();
void selectChannels();
void selectPredefinedPlan();
void viewCurrentPredefinedPlan();
void changePredefinedPlan();
void viewAllChannels(); // New function for Admin side
double calculateTotalCost(char selectedChannels[][50], int numChannels);


// Global variables
int isAdminLoggedIn = 0;
char selectedPredefinedPlan[100];
int main() {
    int choice;
    while (1) {
        printf("Welcome to DTH Billing System\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                printf("Thank you for using DTH Billing System.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void adminLogin() {
    char username[20], password[20];

    printf("Admin Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

     // For simplicity, let's add four random predefined plans with channels and prices
    FILE* plansFile = fopen("plans.txt", "w");
    if (plansFile != NULL) {
        fprintf(plansFile, "Plan 1: Channel A, Channel B, Channel C, Channel D $40.00\n");
        fprintf(plansFile, "Plan 2: Channel B, Channel E, Channel F, Channel G $35.00\n");
        fprintf(plansFile, "Plan 3: Channel C, Channel H, Channel I, Channel J $30.00\n");
        fprintf(plansFile, "Plan 4: Channel A, Channel D, Channel F, Channel H $45.00\n");
        fclose(plansFile);
    } else {
        printf("Error opening plans file.\n");
    }

    // For simplicity, we're using "admin" as the username and password
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        isAdminLoggedIn = 1;
        printf("Admin login successful.\n");

          int adminChoice;
        while (1) {
            printf("Admin Functions: \n");
            printf("1. Add Channels\n");
            printf("2. Modify Channel Price\n");
            printf("3. Modify Discount\n");
            printf("4. view All Channels\n");
            printf("5. view user discounts \n");
            printf("6. logout \n");
            printf("Enter your choice:");
            scanf("%d", &adminChoice);
    
            switch (adminChoice) {
                case 1:
                    addChannels();
                    break;
                case 2:
                    modifyChannelPrice();
                    break;
                case 3:
                    modifyDiscount();
                    break;
                case 4:
                    viewAllChannels(); // Call the new function to view all channels
                    break; 
                case 5:
                    viewalldiscounts();
                    break;   
                case 6:
                    printf("Admin logout successful.\n");
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int hasSelectedPredefinedPlan = 1;
int selectedPredefinedPlanIndex = 0;
// selectedPredefinedPlanIndex = hasSelectedPredefinedPlan - 1;
char predefinedPlans[4][100] = {
    "Plan 1: Zee_tv, zee_sports, zee_News, Zee_Entertaintement",
    "Plan 2: colours, colors_sports, colors_movies, Colors_series",
    "Plan 3: Nick_tv, cartoon_Network, ND_sports, ND_tv",
    "Plan 4: f1_sports, MotoGT_tv, Tennis_tv, Jio_Sports"
};

char currentSelectedPlan[100]; 

void userLogin() {
    char username[20], password[20];

    printf("User Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);


    // For simplicity, we're using "user" as the username and password
    if (strcmp(username, "user") == 0 && strcmp(password, "user") == 0) {
        printf("User login successful.\n");
        // selectChannels();
        // selectPredefinedPlans();

        int userChoice;
        while (1) {
            printf("User Functions:\n");
            printf("1. Select Channels\n");
            printf("2. Select Predefined Plans\n");
            printf("3. Change Predefined Plan\n");
            printf("4. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &userChoice);

            switch (userChoice) {
                case 1:
                    selectChannels();
                    break;
                case 2:
                    if (!hasSelectedPredefinedPlan) {
                        selectPredefinedPlan();
                        hasSelectedPredefinedPlan = 1;
                    } else {
                        printf("You have already selected a predefined plan.\n");
                    }
                    break;
                case 3:
                    changePredefinedPlan();
                    break;
                case 4:
                    printf("User logout successful.\n");
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void addChannels() {
       if (isAdminLoggedIn) {
        char channelName[50];
        int channelPrice;

        printf("Admin: Adding channels.\n");
        printf("Enter channel name: ");
        scanf("%s", channelName);
        printf("Enter channel price: ");
        scanf("%d", &channelPrice);

        // Save channel details to a file
        FILE* channelFile = fopen("channels.txt", "a");
        fprintf(channelFile, "%s %d\n", channelName, channelPrice);
        fclose(channelFile);

        printf("Channel added successfully.\n");
    } else {
        printf("You are not authorized to perform this action.\n");
    }
}

void modifyChannelPrice() {
     if (isAdminLoggedIn) {
        char channelName[50];
        double newChannelPrice;
        double currentChannelPrice;
        int found = 0;

        printf("Admin: Modifying channel price.\n");

        // Read channel name and new price from admin
        printf("Enter channel name: ");
        scanf(" %[^\n]", channelName);
        printf("Enter new channel price: ");
        scanf("%lf", &newChannelPrice);

        // Open channels file in read mode
        FILE* channelsFile = fopen("channels.txt", "r");
        if (channelsFile != NULL) {
            // Read each line from the file and check if the channel exists
            char line[100];
            while (fgets(line, sizeof(line), channelsFile)) {
                char name[50];
                double price;
                sscanf(line, "%[^,],%lf", name, &price);
                if (strcmp(name, channelName) == 0) {
                    currentChannelPrice = price;
                    found = 1;
                    break;
                }
            }
            fclose(channelsFile);

            if (found) {
                // Open channels file in write mode and update the price
                channelsFile = fopen("channels.txt", "w");
                FILE* tempFile = fopen("temp.txt", "w");
                if (channelsFile != NULL && tempFile != NULL) {
                    FILE* tempFile = fopen("temp.txt", "w");
                    while (fgets(line, sizeof(line), channelsFile)) {
                        char name[50];
                        double price;
                        sscanf(line, "%[^,],%lf", name, &price);
                        if (strcmp(name, channelName) == 0) {
                            fprintf(tempFile, "%s,%.2lf\n", name, newChannelPrice);
                        } else {
                            fprintf(tempFile, "%s,%.2lf\n", name, price);
                        }
                    }
                    fclose(channelsFile);
                    fclose(tempFile);
                    remove("channels.txt");
                    rename("temp.txt", "channels.txt");
                    printf("Channel price modified successfully.\n");
                } else {
                    printf("Error opening files for updating.\n");
                }
            } else {
                printf("Channel not found.\n");
            }
        } else {
            printf("Error opening channels file.\n");
        }
    } else {
        printf("You are not authorized to perform this action.\n");
    }
}

void modifyDiscount() {
    if (isAdminLoggedIn) {
        char username[20];
        double newDiscount;
        double currentDiscount;
        int found = 0;

        printf("Admin: Modifying discount.\n");

        // Read username and new discount from admin
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter new discount (in percentage): ");
        scanf("%lf", &newDiscount);

        // Open users file in read mode or create it if it doesn't exist
        FILE* usersFile = fopen("users.txt", "a+");
        if (usersFile != NULL) {
            // Read each line from the file and check if the user exists
            char line[100];
            while (fgets(line, sizeof(line), usersFile)) {
                char name[20];
                double discount;
                sscanf(line, "%[^,],%lf", name, &discount);
                if (strcmp(name, username) == 0) {
                    currentDiscount = discount;
                    found = 1;
                    break;
                }
            }

            if (found) {
                // Open users file in write mode and update the discount
                FILE* tempFile = fopen("temp.txt", "w");
                if (tempFile != NULL) {
                    rewind(usersFile); // Reset file pointer to the beginning
                    while (fgets(line, sizeof(line), usersFile)) {
                        char name[20];
                        double discount;
                        sscanf(line, "%[^,],%lf", name, &discount);
                        if (strcmp(name, username) == 0) {
                            fprintf(tempFile, "%s,%.2lf\n", name, newDiscount);
                        } else {
                            fprintf(tempFile, "%s,%.2lf\n", name, discount);
                        }
                    }
                    fclose(tempFile);
                    fclose(usersFile);
                    remove("users.txt");
                    rename("temp.txt", "users.txt");
                    printf("Discount modified successfully.\n");
                } else {
                    printf("Error opening temp file for updating.\n");
                }
            } else {
                // User not found, so add a new entry
                fprintf(usersFile, "%s,%.2lf\n", username, newDiscount);
                fclose(usersFile);
                printf("User not found, so a new entry has been created with the discount.\n");
            }
        } else {
            printf("Error opening users file.\n");
        }
    } else {
        printf("You are not authorized to perform this action.\n");
    }
}
void viewalldiscounts(){
    printf("Admin: Viewing all the user discounts.\n");

    FILE* discountFile = fopen("users.txt","r");
    if (discountFile != NULL) {
        char line[100];
        printf("All Available Channels:\n");
        while (fgets(line, sizeof(line), discountFile)) {
            char name[50];
            // int  discount;
            sscanf(line, "%s %lf", name);
            printf("%s\n", name);
        }
        fclose(discountFile);
    } else {
        printf("Error opening channels file.\n");
    }
}
void viewAllChannels() {
    printf("Admin: Viewing all channels.\n");

    // Open channels file in read mode
    FILE* channelsFile = fopen("channels.txt", "r");
    if (channelsFile != NULL) {
        char line[100];
        printf("All Available Channels:\n");
        while (fgets(line, sizeof(line), channelsFile)) {
            char name[50];
            double price;
            sscanf(line, "%s %lf", name, &price);
            printf("%s - $%.2lf\n", name, price);
        }
        fclose(channelsFile);
    } else {
        printf("Error opening channels file.\n");
    }
}

double calculateTotalCost(char selectedChannels[][50], int numChannels) {
    double totalCost = 0.0;

    // Open channels file in read mode
    FILE* channelsFile = fopen("channels.txt", "r");
    if (channelsFile != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), channelsFile)) {
            char name[50];
            double price;
            sscanf(line, "%s %lf", name, &price);
            for (int i = 0; i < numChannels; i++) {
                if (strcmp(selectedChannels[i], name) == 0) {
                    totalCost += price;
                    break;
                }
            }
        }
        fclose(channelsFile);
    } else {
        printf("Error opening channels file.\n");
    }

    return totalCost;
}
void selectChannels() {
    printf("User: Selecting channels.\n");

    // Open channels file in read mode
    FILE* channelsFile = fopen("channels.txt", "r");
    if (channelsFile != NULL) {
        char line[100];
        int numChannels = 0;
        char selectedChannels[10][50]; // Assuming the user can select up to 10 channels

        printf("Available Channels:\n");
        while (fgets(line, sizeof(line), channelsFile)) {
            char name[50];
            double price;
            sscanf(line, "%s %lf", name, &price);
            printf("%s - $%.2lf\n", name, price);
            printf("Do you want to select this channel? (yes/no): ");
            char choice[5];
            scanf("%s", choice);
            if (strcmp(choice, "yes") == 0) {
                strcpy(selectedChannels[numChannels], name);
                numChannels++;
            }
        }
        fclose(channelsFile);

        if (numChannels > 0) {
            double totalCost = calculateTotalCost(selectedChannels, numChannels);
            printf("Total cost for selected channels: $%.2lf\n", totalCost);
        } else {
            printf("No channels selected.\n");
        }
    } else {
        printf("Error opening channels file.\n");
    }
}

void selectPredefinedPlan() {
    if (!hasSelectedPredefinedPlan) {
        double planCosts[4] = { 200.00, 201.00, 202.00, 203.00 };
        printf("Available Predefined Plans:\n");
        for (int i = 0; i < 4; i++) {
            printf("%d. %s $%.2lf\n", i + 1, predefinedPlans[i], planCosts[i]);
        }

        printf("Select a predefined plan (1-4): ");
        int selection;
        scanf("%d", &selection);

        if (selection >= 1 && selection <= 4) {
            hasSelectedPredefinedPlan = 1;
            strcpy(selectedPredefinedPlan, predefinedPlans[selection - 1]); // Update selectedPredefinedPlan
            printf("You have selected the following predefined plan:\n");
            printf("%s\n", selectedPredefinedPlan); // Display the selected plan
        } else {
            printf("Invalid plan selection.\n");
        }
    } else {
        printf("You have already selected a predefined plan.\n");
    }
}
void changePredefinedPlan() {
    printf("User: Changing predefined plan.\n");

    char newPlan[100];

    double planCosts[4] = { 200.00, 201.00, 202.00, 203.00 };

    printf("Available Predefined Plans:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s $%.2lf\n", predefinedPlans[i],planCosts[i]);
    }

    // Prompt the user to enter the new predefined plan
    printf("Enter the new predefined plan: ");
    getchar(); // Consume the newline character left in the input buffer
    fgets(newPlan, sizeof(newPlan), stdin);
    newPlan[strcspn(newPlan, "\n")] = '\0'; // Remove the newline character

    // Display the updated predefined plan
    printf("Your new predefined plan: %s\n", newPlan);
}


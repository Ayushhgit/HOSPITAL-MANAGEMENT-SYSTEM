#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATIENTS 100
#define MAX_NAME_LENGTH 30
#define MAX_DISEASE_LENGTH 30

struct Patient {
    char name[MAX_NAME_LENGTH];
    char disease[MAX_DISEASE_LENGTH];
    int cabin;
    int phone;
    int age;
};

int numPatients = 0;
struct Patient patients[MAX_PATIENTS];

// Function prototypes
void clearInputBuffer();
void readDataFromFile();
void writeDataToFile();
void addPatient();
void viewPatients();
void searchPatients();
void editPatient();
void deletePatient();

int main() {
    readDataFromFile();

    int choice;
    do {
        printf("Simple Hospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patients\n");
        printf("4. Edit Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatients();
                break;
            case 4:
                editPatient();
                break;
            case 5:
                deletePatient();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 6);

    writeDataToFile();
    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readDataFromFile() {
    FILE *file = fopen("patient.txt", "r");
    if (file != NULL) {
        numPatients = fread(patients, sizeof(struct Patient), MAX_PATIENTS, file);
        fclose(file);
    }
}

void writeDataToFile() {
    FILE *file = fopen("patient.txt", "w");
    if (file != NULL) {
        fwrite(patients, sizeof(struct Patient), numPatients, file);
        fclose(file);
    }
}

void addPatient() {
    if (numPatients < MAX_PATIENTS) {
        printf("Enter patient's name: ");
        fgets(patients[numPatients].name, MAX_NAME_LENGTH, stdin);
        patients[numPatients].name[strcspn(patients[numPatients].name, "\n")] = '\0'; // Remove trailing newline

        printf("Enter disease: ");
        fgets(patients[numPatients].disease, MAX_DISEASE_LENGTH, stdin);
        patients[numPatients].disease[strcspn(patients[numPatients].disease, "\n")] = '\0'; // Remove trailing newline

        printf("Enter age: ");
        scanf("%d", &patients[numPatients].age);
        clearInputBuffer();

        printf("Enter cabin number: ");
        scanf("%d", &patients[numPatients].cabin);

        printf("Enter phone number: ");
        scanf("%d", &patients[numPatients].phone);

        numPatients++;
        printf("Patient added successfully!\n");
    } else {
        printf("Maximum number of patients reached!\n");
    }
}

void viewPatients() {
    if (numPatients > 0) {
        for (int i = 0; i < numPatients; i++) {
            printf("Patient %d\n", i + 1);
            printf("Name: %s\n", patients[i].name);
            printf("Disease: %s\n", patients[i].disease);
            printf("Age: %d\n", patients[i].age);
            printf("Cabin: %d\n", patients[i].cabin);
            printf("Phone: %d\n", patients[i].phone);
            printf("\n");
        }
    } else {
        printf("No patients found!\n");
    }
}

void searchPatients() {
    if (numPatients > 0) {
        int choice;
        printf("Search Patients By:\n");
        printf("1. Name\n");
        printf("2. Disease\n");
        printf("3. Cabin Number\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                searchByName();
                break;
            case 2:
                searchByDisease();
                break;
            case 3:
                searchByCabin();
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } else {
        printf("No patients found!\n");
    }
}

void searchByName() {
    char searchName[MAX_NAME_LENGTH];
    printf("Enter patient's name to search: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline

    int found = 0;
    for (int i = 0; i < numPatients; i++) {
        if (strcmp(searchName, patients[i].name) == 0) {
            printf("Patient found:\n");
            printf("Name: %s\n", patients[i].name);
            printf("Disease: %s\n", patients[i].disease);
            printf("Age: %d\n", patients[i].age);
            printf("Cabin: %d\n", patients[i].cabin);
            printf("Phone: %d\n", patients[i].phone);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Patient not found!\n");
    }
}

void searchByDisease() {
    char searchDisease[MAX_DISEASE_LENGTH];
    printf("Enter disease to search: ");
    fgets(searchDisease, MAX_DISEASE_LENGTH, stdin);
    searchDisease[strcspn(searchDisease, "\n")] = '\0'; // Remove trailing newline

    int found = 0;
    for (int i = 0; i < numPatients; i++) {
        if (strcmp(searchDisease, patients[i].disease) == 0) {
            printf("Patient found:\n");
            printf("Name: %s\n", patients[i].name);
            printf("Disease: %s\n", patients[i].disease);
            printf("Age: %d\n", patients[i].age);
            printf("Cabin: %d\n", patients[i].cabin);
            printf("Phone: %d\n", patients[i].phone);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Patient not found!\n");
    }
}

void searchByCabin() {
    int searchCabin;
    printf("Enter cabin number to search: ");
    scanf("%d", &searchCabin);

    int found = 0;
    for (int i = 0; i < numPatients; i++) {
        if (searchCabin == patients[i].cabin) {
            printf("Patient found:\n");
            printf("Name: %s\n", patients[i].name);
            printf("Disease: %s\n", patients[i].disease);
            printf("Age: %d\n", patients[i].age);
            printf("Cabin: %d\n", patients[i].cabin);
            printf("Phone: %d\n", patients[i].phone);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Patient not found!\n");
    }
}

void editPatient() {
    if (numPatients > 0) {
        char searchName[MAX_NAME_LENGTH];
        printf("Enter patient's name to edit: ");
        fgets(searchName, MAX_NAME_LENGTH, stdin);
        searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline

        int found = 0;
        for (int i = 0; i < numPatients; i++) {
            if (strcmp(searchName, patients[i].name) == 0) {
                printf("Patient found:\n");
                printf("Name: %s\n", patients[i].name);
                printf("Disease: %s\n", patients[i].disease);
                printf("Age: %d\n", patients[i].age);
                printf("Cabin: %d\n", patients[i].cabin);
                printf("Phone: %d\n", patients[i].phone);
                printf("\n");

                printf("Enter new patient details:\n");
                printf("Name: ");
                fgets(patients[i].name, MAX_NAME_LENGTH, stdin);
                patients[i].name[strcspn(patients[i].name, "\n")] = '\0'; // Remove trailing newline

                printf("Disease: ");
                fgets(patients[i].disease, MAX_DISEASE_LENGTH, stdin);
                patients[i].disease[strcspn(patients[i].disease, "\n")] = '\0'; // Remove trailing newline

                printf("Age: ");
                scanf("%d", &patients[i].age);
                clearInputBuffer();

                printf("Cabin: ");
                scanf("%d", &patients[i].cabin);

                printf("Phone: ");
                scanf("%d", &patients[i].phone);

                printf("Patient details updated!\n");
                found = 1;
            }
        }
        if (!found) {
            printf("Patient not found!\n");
        }
    } else {
        printf("No patients found!\n");
    }
}

void deletePatient() {
    if (numPatients > 0) {
        char searchName[MAX_NAME_LENGTH];
        printf("Enter patient's name to delete: ");
        fgets(searchName, MAX_NAME_LENGTH, stdin);
        searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline

        int found = 0;
        for (int i = 0; i < numPatients; i++) {
            if (strcmp(searchName, patients[i].name) == 0) {
                printf("Patient found and deleted:\n");
                printf("Name: %s\n", patients[i].name);
                printf("Disease: %s\n", patients[i].disease);
                printf("Age: %d\n", patients[i].age);
                printf("Cabin: %d\n", patients[i].cabin);
                printf("Phone: %d\n", patients[i].phone);
                printf("\n");

                // Shift remaining patients
                for (int j = i; j < numPatients - 1; j++) {
                    patients[j] = patients[j + 1];
                }
                numPatients--;
                printf("Patient deleted successfully!\n");
                found = 1;
            }
        }
        if (!found) {
            printf("Patient not found!\n");
        }
    } else {
        printf("No patients found!\n");
    }
}


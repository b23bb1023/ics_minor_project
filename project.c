#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Include time.h library for timestamps

#define MAX_CATEGORIES 100


typedef struct  Expense {
    char category[50];
    float amount;
    time_t timestamp; // Timestamp for expense
} Expense;

struct Expense expenses[MAX_CATEGORIES]; // Global array to store expenses

// Function to display budget summary
void displayBudget(float income, float budgetLimit, float totalExpenses) {
    printf("\n--- Budget Summary ---\n");
    printf("Income: $%.2f\n", income);
    printf("Budget Limit: $%.2f\n", budgetLimit);

    // Calculate remaining balance
    float remainingBalance = income - totalExpenses;
    printf("Remaining Balance: $%.2f\n", remainingBalance);

    // Check if total expenses exceed budget limit and display a warning
    if (totalExpenses > budgetLimit) {
        printf("\n*** WARNING: Total expenses have exceeded the budget limit! ***\n");
    }
}

// Function to display categories and expenses
void displayCategoriesAndExpenses(struct Expense expenses[], int numExpenses) {
    printf("\n--- Categories and Expenses ---\n");
    for (int i = 0; i < numExpenses; ++i) {
        printf("%d. Category: %s, Amount: $%.2f, Timestamp: %s",
            i + 1,
            expenses[i].category,
            expenses[i].amount,
            asctime(localtime(&expenses[i].timestamp))); // Convert timestamp to string
    }
}

void deleteExpense(Expense expenses[], int *numExpenses, float *totalExpenses) {
    if (*numExpenses > 0) {
        displayCategoriesAndExpenses(expenses, *numExpenses);

        int deleteIndex;
        printf("Please select the category you want to delete (1 to %d): ", *numExpenses);
        scanf("%d", &deleteIndex);

        if (deleteIndex >= 1 && deleteIndex <= *numExpenses) {
            // Subtract deleted expense amount from total expenses
            *totalExpenses -= expenses[deleteIndex - 1].amount;

            // Shift elements in the array to remove the selected expense
            for (int j = deleteIndex - 1; j < *numExpenses - 1; ++j) {
                strcpy(expenses[j].category, expenses[j + 1].category);
                expenses[j].amount = expenses[j + 1].amount;
            }

            // Set the last element to empty
            strcpy(expenses[*numExpenses - 1].category, "");
            expenses[*numExpenses - 1].amount = 0;

            // Decrement the number of expenses
            (*numExpenses)--;

            printf("Expense deleted successfully! 😊\n");
        } else {
            printf("\n*** ERROR: Invalid index selected! ***\n");
        }
    } else {
        printf("\n*** ERROR: There are no expenses to delete! ***\n");
    }
}

void fun(int editIndex)
{
    int newAmount;
    printf("Enter new amount for %s: $", expenses[editIndex - 1].category);
    scanf("%d",&newAmount);
    expenses[editIndex - 1].amount+=newAmount;
    if(expenses[editIndex - 1].amount<0)
        {
            printf("the decrement value cannot be greater than original value , please enter a valid amount \n");
            expenses[editIndex - 1].amount-=newAmount;
           
        fun(editIndex);
       
    }}

int main() {
    printf("\n \t\t\t\t\t\t\t\t\t***************\n");
    printf(" \t\t\t\t\t\t\t\t\t****      \n");
    printf(" \t\t\t\t\t\t\t\t\t***      \n");
    printf(" \t\t\t\t\t\t\t\t\t**      \n");
    printf(" \t\t\t\t\t\t\t\t\t*      \n");
    printf(" \t\t\t\t\t\t\t\t\t**      \n");
    printf(" \t\t\t\t\t\t\t\t\t***************\n");
    printf(" \t\t\t\t\t\t\t\t\t**      \n");
    printf(" \t\t\t\t\t\t\t\t\t*      \n");
    printf(" \t\t\t\t\t\t\t\t\t**      \n");
    printf(" \t\t\t\t\t\t\t\t\t***      \n");
    printf(" \t\t\t\t\t\t\t\t\t****      \n");
    printf(" \t\t\t\t\t\t\t\t\t****************\n\n");
    printf("\t\t\t\t\t\t\t\t-----EXPENSENTRY : Budget WatchDog-----\n");


    // User inputs for income and budget limit and stuff
    float income, budgetLimit, remainingBalance;
    printf("Enter your monthly income: $");
    scanf("%f", &income);

    printf("Enter your budget limit: $");
    scanf("%f", &budgetLimit);
    if (budgetLimit > income) {
        printf("BudgetLimit cannot be greater than income please retry --- \n");
        return 0;
    }

    int numExpenses = 0;
    float totalExpenses = 0.0; // Total expenses counter remember

    int choice;
    do {
        printf("\n--- Personal Budget Manager ---\n");
        printf("1. Add Expense\n");
        printf("2. Edit Expense\n");
        printf("3. Display Budget and expenses\n");
        printf("4. Edit Budget\n");
        printf("5. Delete Expense\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add Expense
                if (numExpenses <= MAX_CATEGORIES) {
                    char category[50];
                    float amount;

                    printf("Enter expense category: ");
                    scanf("%s", category);

                    printf("Enter expense amount: $");
                    scanf("%f", &amount);

                    // Check if expense amount is negative
                    if (amount < 0) {
                        printf("\n*** ERROR: Expense amount cannot be negative! ***\n");
                        break;
                    }

                    // Check if expense category is empty
                    if (strlen(category) == 0 || amount == 0) {
                        printf("\n*** ERROR: Expense category or amount cannot be empty! ***\n");
                        break;
                    }

                    // Update total expenses
                    totalExpenses += amount;

                    // Add expense to the array with timestamp very impt
                    strcpy(expenses[numExpenses].category, category);
                    expenses[numExpenses].amount = amount;
                    expenses[numExpenses].timestamp = time(NULL); // Get current time
                    numExpenses++;

                    // Display budget summary complete
                    displayBudget(income, budgetLimit, totalExpenses);

                    printf("Expense added successfully! 😊\n");
                } else {
                    printf("Maximum number of categories reached. 😕\n");
                }
                break;

            case 2:
                  // Edit Expense
                if (numExpenses > 0) {
                    displayCategoriesAndExpenses(expenses, numExpenses);
                    printf("For decrement, input a negative value; for increment, input a positive value. \n");
                   
                    int editIndex;
                    printf("Select the index to edit (1 to %d): ", numExpenses);
                    scanf("%d", &editIndex);
                   
                    if (editIndex >= 1 && editIndex <= numExpenses) {
                        float newAmount;

                       
                        printf("Enter new amount for %s: $", expenses[editIndex - 1].category);
                        scanf("%f", &newAmount);
                       
                       
                        expenses[editIndex - 1].amount+=newAmount;
                        if(expenses[editIndex - 1].amount<0)
                        {
                            printf("the decrement value cannot be greater than original value , please enter a valid amount \n");
                            expenses[editIndex - 1].amount-=newAmount;
                            fun(editIndex);
                           
                        }
                       
                        // Check if total expenses will exceed income
                        if ((income - (totalExpenses - expenses[editIndex - 1].amount + newAmount)) < 0) {
                            printf("\n*** ERROR: Total expenses cannot exceed the income! Reverting edit. ***\n");
                        }
                        else {
                            // Update the expense amount
                            totalExpenses -= expenses[editIndex - 1].amount; 
                            // Subtract old amount
                            // Update amount
                            totalExpenses += newAmount; // Add new amount

                            printf("Expense edited successfully! 😊\n");
                        }
                    } else {
                        printf("\n*** ERROR: Invalid index selected! ***\n");
                    }
                } else {
                    printf("\n*** ERROR: No expenses to edit! ***\n");
                }
                break;


            case 3:
                // Display budget summary
                displayBudget(income, budgetLimit, totalExpenses);
                displayCategoriesAndExpenses(expenses, numExpenses);
                break;

            case 4:
                // Edit Budget
                printf("Enter new monthly income: $");
                scanf("%f", &income);

                printf("Enter new budget limit: $");
                scanf("%f", &budgetLimit);

                printf("Budget edited successfully! 😊\n");
                break;

            case 5:
                deleteExpense(expenses, &numExpenses, &totalExpenses); // Call to deleteExpense function
                break;
            case 6:
                // Exit
                printf("Exiting Personal Budget Manager. Goodbye! 😊\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option. 😕\n");
        }
    } while (choice != 6);

    return 0;
}
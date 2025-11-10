#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Transaction structure (linked list)
typedef struct Transaction {
    char type[20];
    double amount;
    struct Transaction *next;
} Transaction;

// Account structure
typedef struct Account {
    int accountNumber;
    char name[50];
    double balance;
    Transaction *history;
    struct Account *next;   // Linked list of accounts
} Account;

Account *head = NULL; // Global head pointer for accounts

// Function prototypes
Account* createAccount(int accNo, const char *name, double initialBalance);
Account* findAccount(int accNo);
void deposit(Account *acc, double amount);
void withdraw(Account *acc, double amount);
void transfer(Account *from, Account *to, double amount);
void checkBalance(Account *acc);
void addTransaction(Account *acc, const char *type, double amount);
void printTransactions(Account *acc);

int main() {
    int choice, accNo, accNo2;
    char name[50];
    double amount;
    Account *acc, *acc2;

    while (1) {
        printf("\n--- Bank Account Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Check Balance\n");
        printf("6. Show Transactions\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter account number: ");
                scanf("%d", &accNo);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter initial balance: ");
                scanf("%lf", &amount);
                acc = createAccount(accNo, name, amount);
                acc->next = head;
                head = acc;
                printf("Account created successfully!\n");
                break;

            case 2:
                printf("Enter account number: ");
                scanf("%d", &accNo);
                acc = findAccount(accNo);
                if (acc) {
                    printf("Enter amount to deposit: ");
                    scanf("%lf", &amount);
                    deposit(acc, amount);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 3:
                printf("Enter account number: ");
                scanf("%d", &accNo);
                acc = findAccount(accNo);
                if (acc) {
                    printf("Enter amount to withdraw: ");
                    scanf("%lf", &amount);
                    withdraw(acc, amount);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 4:
                printf("Enter sender account number: ");
                scanf("%d", &accNo);
                acc = findAccount(accNo);
                printf("Enter receiver account number: ");
                scanf("%d", &accNo2);
                acc2 = findAccount(accNo2);
                if (acc && acc2) {
                    printf("Enter amount to transfer: ");
                    scanf("%lf", &amount);
                    transfer(acc, acc2, amount);
                } else {
                    printf("One or both accounts not found!\n");
                }
                break;

            case 5:
                printf("Enter account number: ");
                scanf("%d", &accNo);
                acc = findAccount(accNo);
                if (acc) {
                    checkBalance(acc);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 6:
                printf("Enter account number: ");
                scanf("%d", &accNo);
                acc = findAccount(accNo);
                if (acc) {
                    printTransactions(acc);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 7:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Create a new account dynamically
Account* createAccount(int accNo, const char *name, double initialBalance) {
    Account *acc = (Account*)malloc(sizeof(Account));
    acc->accountNumber = accNo;
    strcpy(acc->name, name);
    acc->balance = initialBalance;
    acc->history = NULL;
    acc->next = NULL;
    return acc;
}

// Find account by account number
Account* findAccount(int accNo) {
    Account *temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNo)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add transaction to linked list
void addTransaction(Account *acc, const char *type, double amount) {
    Transaction *newTrans = (Transaction*)malloc(sizeof(Transaction));
    strcpy(newTrans->type, type);
    newTrans->amount = amount;
    newTrans->next = acc->history;
    acc->history = newTrans;
}

// Deposit function
void deposit(Account *acc, double amount) {
    acc->balance += amount;
    addTransaction(acc, "Deposit", amount);
    printf("Deposited %.2f to %s's account.\n", amount, acc->name);
}

// Withdraw function
void withdraw(Account *acc, double amount) {
    if (amount > acc->balance) {
        printf("Insufficient balance in %s's account!\n", acc->name);
        return;
    }
    acc->balance -= amount;
    addTransaction(acc, "Withdraw", amount);
    printf("Withdrew %.2f from %s's account.\n", amount, acc->name);
}

// Transfer function
void transfer(Account *from, Account *to, double amount) {
    if (amount > from->balance) {
        printf("Insufficient balance in %s's account for transfer!\n", from->name);
        return;
    }
    from->balance -= amount;
    to->balance += amount;
    addTransaction(from, "Transfer Out", amount);
    addTransaction(to, "Transfer In", amount);
    printf("Transferred %.2f from %s to %s.\n", amount, from->name, to->name);
}

// Check balance
void checkBalance(Account *acc) {
    printf("%s's account balance: %.2f\n", acc->name, acc->balance);
}

// Print transaction history
void printTransactions(Account *acc) {
    Transaction *temp = acc->history;
    if (!temp) {
        printf("No transactions found for %s.\n", acc->name);
        return;
    }
    printf("Transaction history for %s:\n", acc->name);
    while (temp != NULL) {
        printf("%s: %.2f\n", temp->type, temp->amount);
        temp = temp->next;
    }
}

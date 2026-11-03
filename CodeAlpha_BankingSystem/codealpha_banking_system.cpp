#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Transaction Class to store details of each transaction
class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double amt) {
        type = t;
        amount = amt;
    }

    void displayTransaction() const {
        cout << "- " << type << ": Rs. " << fixed << setprecision(2) << amount << endl;
    }
};

// BankAccount Class
class BankAccount {
private:
    int accountNumber;
    string holderName;
    double balance;
    vector<Transaction> transactions;

public:
    BankAccount(int accNo, string name, double initialDeposit) {
        accountNumber = accNo;
        holderName = name;
        balance = initialDeposit;
        transactions.push_back(Transaction("Initial Deposit", initialDeposit));
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction("Deposit", amount));
            cout << "\n[Success] Deposit completed successfully!\n";
        } else {
            cout << "\n[Error] Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "\n[Success] Withdrawal completed successfully!\n";
        } else {
            cout << "\n[Error] Insufficient balance or invalid amount!\n";
        }
    }

    void transfer(double amount, BankAccount &targetAccount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Transfer Out", amount));
            
            targetAccount.balance += amount;
            targetAccount.transactions.push_back(Transaction("Transfer In", amount));
            
            cout << "\n[Success] Amount transferred successfully to Account #" << targetAccount.getAccountNumber() << "!\n";
        } else {
            cout << "\n[Error] Transfer failed! Insufficient funds or invalid amount.\n";
        }
    }

    void displayAccountInfo() const {
        cout << "\n========================================\n";
        cout << "           ACCOUNT INFORMATION          \n";
        cout << "========================================\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Holder Name    : " << holderName << endl;
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        cout << "========================================\n";
    }

    void displayTransactionHistory() const {
        cout << "\n========================================\n";
        cout << "          TRANSACTION HISTORY           \n";
        cout << "========================================\n";
        if (transactions.empty()) {
            cout << "No transactions found.\n";
        } else {
            for (size_t i = 0; i < transactions.size(); i++) {
                transactions[i].displayTransaction();
            }
        }
        cout << "========================================\n";
    }
};

int main() {
    vector<BankAccount> accounts;
    int choice;

    do {
        cout << "\n=== CODEALPHA BANKING SYSTEM ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Funds" << endl;
        cout << "5. View Account Info & Balance" << endl;
        cout << "6. View Transaction History" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            double initialDeposit;

            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin >> name;
            cout << "Enter Initial Deposit Amount: ";
            cin >> initialDeposit;

            accounts.push_back(BankAccount(accNo, name, initialDeposit));
            cout << "\n[Success] Account created successfully!\n";

        } else if (choice >= 2 && choice <= 6) {
            if (accounts.empty()) {
                cout << "\n[Warning] No accounts exist yet. Please create an account first!\n";
                continue;
            }

            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;

            BankAccount *acc = NULL;
            for (size_t i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accNo) {
                    acc = &accounts[i];
                    break;
                }
            }

            if (acc == NULL) {
                cout << "\n[Error] Account not found!\n";
                continue;
            }

            if (choice == 2) {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc->deposit(amount);
            } 
            else if (choice == 3) {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc->withdraw(amount);
            } 
            else if (choice == 4) {
                int targetAccNo;
                cout << "Enter Target Account Number: ";
                cin >> targetAccNo;

                BankAccount *targetAcc = NULL;
                for (size_t i = 0; i < accounts.size(); i++) {
                    if (accounts[i].getAccountNumber() == targetAccNo) {
                        targetAcc = &accounts[i];
                        break;
                    }
                }

                if (targetAcc == NULL) {
                    cout << "\n[Error] Target account not found!\n";
                } else if (targetAcc->getAccountNumber() == acc->getAccountNumber()) {
                    cout << "\n[Error] Cannot transfer funds to the same account!\n";
                } else {
                    double amount;
                    cout << "Enter amount to transfer: ";
                    cin >> amount;
                    acc->transfer(amount, *targetAcc);
                }
            } 
            else if (choice == 5) {
                acc->displayAccountInfo();
            } 
            else if (choice == 6) {
                acc->displayTransactionHistory();
            }

        } else if (choice == 7) {
            cout << "\nThank you for using CodeAlpha Banking System!\n";
        } else {
            cout << "\n[Error] Invalid choice! Please select between 1 to 7.\n";
        }

    } while (choice != 7);

    return 0;
}

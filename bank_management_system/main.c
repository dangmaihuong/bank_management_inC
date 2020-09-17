/*
Huong Dang 15September2020

This project is a bank management system written in C language.

Users can create a new account, update information of an existing
account, view and manage transactions, check the details of an 
existing account, remove existing account and view customers’ list.

*/



#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

void menu(void);
void new_acc(void);
void edit_acc(void);
void transaction(void);
void interest(void);
void delete(void);
void acc_list(void);
void close(void);

int main_exit, i=0, j=0;


struct date {
	int day, month, year;
};

struct {
	char name[60], address[60], acc_type[10];
	int acc_num, age;
	double phone_num;
	float balance;
	struct date dob;			//acc date of birth
	struct date deposit;		//create new acc date

}add, edit, check, era, trans;


int main() {
	
	char enter_pass[10] = {0}, true_pass[10] = "shameless";

	printf("Enter the password: ");
	scanf_s("%s", enter_pass, 10);
	//printf("\n%s", enter_pass);		//checking the input password


	//compare the password users enter and the right password
	if(strcmp(true_pass, enter_pass) == 0) {	//if the password entered is right
		printf("\nPassword is right!...\n...LOADING TO THE SYSTEM...");
		//sytem("cls");
		menu();			//appear menu to choose with your acc
	}
	else {
		printf("\nYou have entered the wrong password T-T");
	login_try:
		printf("\nEnter 1 to try again, or enter 0 to exit: ");
		scanf_s("%d", &main_exit);
		if(main_exit == 1) {
			system("cls");
			main();
		}
		else if (main_exit == 0) {
			system("cls");
			close();
		}
		else {
			printf("\nNo option have been choose!");
			//delay(1000000000);
			system("cls");
			goto login_try;
		}
	}
	return 0;
}



//OPTION 7: This function is to use as exit all the options = main page 
void close(void) {
	system("cls");
	printf("\n\n\n\n\t\t\t HOME PAGE \t\t\t\n\n\n\n");
}


//this function is used as choosing the menu for each action
void menu(void) {
	int choice;
	system("cls");
	printf("\nCHOOSING YOUR FOLLOWING ACTION BELOW, by entering the respective number:");
	printf("\n1. Create new account.\n2. Update information of existing account.\n3. Transaction.\n4. Information of existing account.\n5. Delete existing accoung.\n6. Customer's list.\n7. Exit.\nENTER YOUR CHOICE: ");
	scanf_s("%d", &choice);

	system("cls");
	switch (choice) {
	case 1: new_acc();
		break;
	case 2: edit_acc();
		break;
	case 3: transaction();
		break;
	case 4: interest();
		break;
	case 5: delete();
		break;
	case 6: acc_list();
		break;
	case 7: close();
		break;
	}
}






//Option 1: Create new account
void new_acc() {
	int choice;
	printf("You choose to CREAT NEW ACCOUNT\n");
	
	FILE* ptr;									//declare a pointer of type file.
	errno_t err;
	err = fopen_s(&ptr, "bank_management.txt", "a+");		//open both reading and appending (file will be created)

	if (!err && ptr != NULL) {			//testing for a non-null pointer
		system("cls");
		printf("ADD DATA to new account\n");
		printf("\nEnter date (dd/mm/yyyy): ");
		scanf_s("%d %d %d", &add.deposit.day, &add.deposit.month, &add.deposit.year);

		//enter new acc_num and check if is used or not
	account_number:
		printf("\nEnter new account number: ");
		scanf_s("%d", &check.acc_num);
		while (fscanf_s(ptr, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) { //when the file is not empty
			if (check.acc_num == add.acc_num) {
				printf("\nYour entered account number has been used! Please try other account number!!!!\n");
				goto account_number;
			}
		}

		add.acc_num = check.acc_num;

		printf("\nEnter name: ");
		scanf_s("%s", add.name, 60);
		printf("\nEnter DOB (dd/mm/yyyy): ");
		scanf_s("%d %d %d", &add.dob.day, &add.dob.month, &add.dob.year);
		printf("\nYour age?: ");
		scanf_s("%d", &add.age);
		printf("\nWhere do you live: ");
		scanf_s("%s", add.address, 60);
		printf("\nType of your account?(Enter 'Saving' or 'Current'): ");
		scanf_s("%s", add.acc_type, 10);
		printf("\nBalance of this account: ");
		scanf_s("%f", &add.balance);
		printf("\nEnter phone number: ");
		scanf_s("%lf", &add.phone_num);

		fprintf_s(ptr, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year,
			add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);

		fclose(ptr);
		printf("\nAccount has been created!!!!\n");
	add_invalid:
		printf("Enter 1 for the main menu and 0 to exit: ");
		scanf_s("%d", &choice);
		system("cls");
		if (choice == 1) {
			menu();
		}
		else if (choice == 0) {
			close();
		}
		else {
			printf("\nInvalid input! Try again!!!!!\n");
			goto add_invalid;
		}
	}
	else {
		close();
	}
}



//Option 2: Edit the account details
void edit_acc(void) {
	int choice, flag=0;
	FILE* old, * new;
	errno_t err;
	err = fopen_s(&old, "bank_management.txt", "r");
	err = fopen_s(&new, "bank_management_new.txt", "w"); //create new file, first enter change infor, then replace old file

	printf("\nEnter your account number: ");
	scanf_s("%d", &edit.acc_num);

	if (!err && old != NULL && new != NULL) { //when file pointer is not NULL
		while (fscanf_s(old, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
			
			//when program found the entered account number, user can change infor
			if (edit.acc_num == add.acc_num) {
				flag = 1;
				printf("\nAccount FOUND!\nInformation of this account number is:\n");
				printf(" Account_number: %d\n Name: %s\n DOB: %d-%d-%d\n Age: %d\n Address: %s\n Phone_number: %lf\n Type: %s\n Balance: %f\n Deposit_date: %d-%d-%d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year,
					add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
				printf("\nYou can change these follow information: (1)Name/ (2)DOB/ (3)Address/ (4)Phone_number\n");
				printf("\nEnter your choice according to its label number (choose from 1 to 4): ");
				scanf_s("%d", &choice);
				if (choice == 1) {
					printf("Enter new name: ");
					scanf_s("%s", &edit.name, 60);
					fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, edit.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
				}
				else if (choice == 2) {
					printf("Enter new date of birth: ");
					scanf_s("%d %d %d", &edit.dob.day, &edit.dob.month, &edit.dob.year);
					fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, edit.dob.day, edit.dob.month, edit.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
		        }
				else if (choice == 3) {
					printf("Enter new address: ");
					scanf_s("%s", &edit.address, 60);
					fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, edit.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
				}
				else if(choice == 4) {
					printf("Enter new phone number: ");
					scanf_s("%lf", &edit.phone_num);
					fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, edit.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
				}
				system("cls");
				printf("\n\n\nCHANGE SAVED!!!\n\n\n");
			}
			else {
				fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
			}
		}

		fclose(old);
		fclose(new);
		remove("bank_management.txt");
		int ret = rename("bank_management_new.txt", "bank_management.txt");
		//printf("%d rename value", ret);
	}

	if (flag == 0) {
		printf("\nYour account number NOT FOUND!!!!");

		edit_invalid:
		printf("\nEnter 1 to try again, 2 to go to menu and 3 to home page: ");
		scanf_s("%d", &main_exit);
		if (main_exit == 1) {
			edit_acc();
		}
		else if (main_exit == 2) {
			menu();
		}
		else if (main_exit == 3) {
			close();
		}
		else {
			printf("\n\nINVALID input! Please try again!\n\n");
			goto edit_invalid;
		}
	}
	else if (flag == 1) {
	finish_edit_invalid:
		printf("\n\nEnter 1 to go to menu and 0 to home page: ");
		scanf_s("%d", &main_exit);
		if (main_exit == 0) {
			close();
		}
		else if (main_exit == 1) {
			menu();
		}
		else {
			printf("\nINVALID input! Please try again!!!\n\n");
			goto finish_edit_invalid;
		}
	}

}



//Option 3: User withdraw or deposit into the account
void transaction(void) {
	int choice, flag=0;
	FILE* old, * new;
	errno_t err;
	err = fopen_s(&old, "bank_management.txt", "r");
	err = fopen_s(&new, "bank_management_new.txt", "w");

	printf("\nEnter your account number: ");
	scanf_s("%d", &trans.acc_num);
	
	if (!err && old != NULL && new != NULL) {
		while (fscanf_s(old, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
			if (add.acc_num == trans.acc_num) {
				flag = 1;
				if (_strcmpi(add.acc_type, "Saving") == 0) {
					printf("\n\nYOU CAN NOT deposit or withdraw with SAVING ACCOUNT\n\n");
					printf("Enter 1 to go to menu and 2 to exit");
					scanf_s("%d", &main_exit);
					if (main_exit == 1) {
						menu();
					}
					else {
						close();
					}
				}
				else {
					printf("\nEnter 1 for withdraw and enter 2 for deposit");
					scanf_s("%d", &choice);
					if (choice == 1) {
						printf("How much you want to withdraw: ");
						scanf_s("%f", &trans.balance);
						add.balance = add.balance - trans.balance;
						fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
						printf("\nWithdraw successfully!!!!\n");
					}
					else if (choice == 2) {
						printf("How much you want to deposit: ");
						scanf_s("%f", &trans.balance);
						add.balance = add.balance + trans.balance;
						fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
						printf("\nDeposit successfully!!!!\n");
					}
				}
			}
			else {
				fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
			}
		}
		fclose(old);
		fclose(new);
		remove("bank_management.txt");
		int ret = rename("bank_management_new.txt", "bank_management.txt");
		printf("%d rename record", ret);
	}
	if (flag == 0) {
		printf("\nYOUR ACCOUNT NUMBER NOT FOUND");
	transaction_invalid: 
		printf("\nEnter 1 to try again, 2 to go to menu and 3 to exit");
		scanf_s("%d", &main_exit);
		if (main_exit == 1) {
			transaction();
		}
		else if (main_exit == 2) {
			menu();
		}
		else if (main_exit == 3) {
			close();
		}
		else {
			printf("\nINVALID input! Please try again!\n");
			goto transaction_invalid;
		}
		
	}
	else {
		printf("\nYour transaction is completed.\nEnter 1 for menu and 2 for home page");
		scanf_s("%d", &main_exit);
		if (main_exit == 1) {
			menu();
		}
		else {
			close();
		}
	}
}


//Option 4: Calculate interest of saving account
void interest(void) {
	int flag = 0;
	FILE* ptr;
	errno_t err;
	err = fopen_s(&ptr, "bank_management.txt", "r");

	printf("\nEnter your account number: ");
	scanf_s("%d", &check.acc_num);

	if (!err && ptr != NULL) {
		while (fscanf_s(ptr, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
			if (add.acc_num == check.acc_num) {
				if (_strcmpi(add.acc_type, "Saving") == 0) {
					flag = 1; 
					float rate = 0.02;
					float interest_month = add.balance * rate;
					printf("\nYou will receive %f$ every month", interest_month);
				}
				else {
					printf("\nYou CAN NOT receive interest by CURRENT account");
				}
			}
		}
		fclose(ptr);
		if (flag == 1) {
			printf("What do you want to do next: Enter 1 returning to menu or Enter 2 to exit: ");
			scanf_s("%d", &main_exit);
			if (main_exit == 1) {
				menu();
			}
			else {
				close();
			}
		}
		else {
		interest_invalid: 
			printf("\nYour account number NOT FOUND\nEnter 1 to try again, 2 for menu and 3 to exit: ");
			scanf_s("%d", &main_exit);
			if (main_exit == 1) {
				interest();
			}
			else if (main_exit == 2) {
				menu();
			}
			else if (main_exit == 3) {
				close();
			}
			else {
				printf("\nINVALID input\n");
				goto interest_invalid;
			}
		}
	}
}


//Option 5: Delete account
void delete(void) {
	int flag = 0;
	FILE* old, * new;
	errno_t err;
	err = fopen_s(&old, "bank_management.txt", "r");
	err = fopen_s(&new, "bank_management_new.txt", "w");

	printf("\nEnter your account number (the one you want to delete): ");
	scanf_s("%d", &era.acc_num);

	if(!err && old != NULL && new != NULL) {
		while (fscanf_s(old, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
			if (add.acc_num != era.acc_num) {
				fprintf_s(new, "%d %s %d %d %d %d %s %lf %s %f %d %d %d\n", add.acc_num, add.name, add.dob.day, add.dob.month, add.dob.year, add.age, add.address, add.phone_num, add.acc_type, add.balance, add.deposit.day, add.deposit.month, add.deposit.year);
			}
			else {
				printf("\nACCOUNT IS DELETED SUCCESSFULLY\n");
				flag = 1;
			}
		}
		fclose(old);
		fclose(new);
		remove("bank_management.txt");
		int ret = rename("bank_management_new.txt", "bank_management.txt");
		if (flag == 1) {
			printf("What do you want to do next: Enter 1 returning to menu or Enter 2 to exit: ");
			scanf_s("%d", &main_exit);
			if (main_exit == 1) {
				menu();
			}
			else {
				close();
			}
		}
		else {
		ear_invalid:
			printf("\nYour account number NOT FOUND\nEnter 1 to try again, 2 for menu and 3 to exit: ");
			scanf_s("%d", &main_exit);
			if (main_exit == 1) {
				interest();
			}
			else if (main_exit == 2) {
				menu();
			}
			else if (main_exit == 3) {
				close();
			}
			else {
				printf("\nINVALID input\n");
				goto ear_invalid;
			}
		}
	}
}



// Option 6: User can view the account list and its details
void acc_list(void){
	
	int list_num=0;

	FILE* list;
	errno_t err;
	err = fopen_s(&list, "bank_management.txt", "r");		//open reading 

	system("cls");
	printf("\nACCOUNT NUMBER\t\t NAME \t\t\t ADDRESS \t\t\t PHONE\n");


	if (!err && list != NULL) {
		while (fscanf_s(list, "%d %s %d %d %d %d %s %lf %s %f %d %d %d", &add.acc_num, add.name, _countof(add.name), &add.dob.day,
			&add.dob.month, &add.dob.year, &add.age, add.address, _countof(add.address), &add.phone_num,
			add.acc_type, _countof(add.acc_type), &add.balance, &add.deposit.day, &add.deposit.month, &add.deposit.year) != EOF) {
			printf("\n%d\t\t\t %s \t\t\t %s \t\t\t %f \n", add.acc_num, add.name, add.address, add.phone_num);
			list_num++;
		}

		if (list_num == 0) {
			printf("\nNO DATA FOUND, the list is empty!\nRETURN TO HOME PAGE...");
			close();
		}

	acc_list_invalid:
		printf("Enter 1 to the MENU and 0 to HOME PAGE: ");
		scanf_s("%d", &main_exit);
		system("cls");
		if (main_exit == 1) {
			menu();
		}
		else if (main_exit == 0) {
			close();
		}
		else {
			printf("\nINVALID INPUT! Try again!!!!\n");
			goto acc_list_invalid;
		}
	}
}
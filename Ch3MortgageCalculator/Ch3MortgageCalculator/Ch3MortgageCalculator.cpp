#include <iostream> 
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	//test values: 267369.15 30 2.988 300.58 1353.78
	//input variables
	double amountLoan; //monetary value 
	int lengthMortgage; //in years 
	double annualInterestRate; //percentage 
	double annualPropertyTax; //monetary value
	double annualInsuranceCost; //monetary value

	//gets mortgage info from user 
	cout << "Enter the loan amount, year length of the mortgage, annual interest rate, annual property tax, and annual insurance cost IN THAT ORDER" << endl;
	cin >> amountLoan >> lengthMortgage >> annualInterestRate >> annualPropertyTax >> annualInsuranceCost;

	//calculated variables
	int numPayments = lengthMortgage * 12;
	double monthlyInterestRate = annualInterestRate / 1200;
	double monthlyPropertyTaxPaid = annualPropertyTax / 12;
	double monthlyInsurancePaid = annualInsuranceCost / 12;
	//Calculating totalMonthlyPayment
	double totalMonthlyPayment = (monthlyInterestRate * pow((1 + monthlyInterestRate), numPayments));
	totalMonthlyPayment = (totalMonthlyPayment / (pow((1 + monthlyInterestRate), numPayments) - 1)) * amountLoan;
	totalMonthlyPayment = totalMonthlyPayment + monthlyPropertyTaxPaid + monthlyInsurancePaid;
	//End of totalMonthlyPayment calculation
	double totalInterestPaid = ((totalMonthlyPayment - monthlyPropertyTaxPaid - monthlyInsurancePaid) - (amountLoan / numPayments)) * numPayments;
	double totalInsurancePaid = annualInsuranceCost * lengthMortgage;
	double totalPropertyTaxPaid = annualPropertyTax * lengthMortgage;
	double totalPaidBack = totalInsurancePaid + totalInterestPaid + totalPropertyTaxPaid + amountLoan;

	//outputs mortgage info inputted above used in calculations  
	cout << setprecision(2) << fixed;
	cout << "Loan Amount: " << amountLoan << endl;
	cout << "Mortgage Length: " << lengthMortgage << endl;
	cout << "Annual Interest Rate: " << annualInterestRate << endl;
	cout << "Annual Property Tax: " << annualPropertyTax << endl;
	cout << "Annual Insurance Cost: " << annualInsuranceCost << endl << endl;

	// Output Calculations
	cout << left << setw(30) << "Loan Amount: " << "$" << right << setw(15) << amountLoan << endl;
	cout << left << setw(30) << "Number of Payments: " << ' ' << right << setw(15) << numPayments << endl;
	cout << left << setw(30) << "Monthly Interest Rate: " << "%" << right << setw(15) << monthlyInterestRate * 100 << endl;
	cout << left << setw(30) << "Monthly Property Tax Paid: " << "$" << right << setw(15) << monthlyPropertyTaxPaid << endl;
	cout << left << setw(30) << "Monthly Insurance Paid: " << "$" << right << setw(15) << monthlyInsurancePaid << endl;
	cout << left << setw(30) << "Total Monthly Payment: " << "$" << right << setw(15) << totalMonthlyPayment << endl;
	cout << left << setw(30) << "Total Interest Paid: " << "$" << right << setw(15) << totalInterestPaid << endl;
	cout << left << setw(30) << "Total Insurance Paid: " << "$" << right << setw(15) << totalInsurancePaid << endl;
	cout << left << setw(30) << "Total Property Tax Paid" << "$" << right << setw(15) << totalPropertyTaxPaid << endl;
	cout << left << setw(30) << "Total Paid Back" << "$" << right << setw(15) << totalPaidBack << endl;

	cout << "\nPress \"Enter\" to exit:";
	cin.ignore(100, '\n');
	cin.get();

	return(0);
}
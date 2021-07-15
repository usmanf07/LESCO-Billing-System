#include<iostream>
#include<fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>

using namespace std;

template <typename T, typename T2>
void destructList(T2**& List, int size)
{
	for(int i = 0; i < size; i++)
		delete List[i];
	delete[] List;
}

class Helper
{
public:

	// returns c string length till null char

	static int StringLenght(char* str)
	{

		int strlength = 0;

		for (char* i = str; *i != '\0'; i++)
		{
			strlength++;
		}

		return strlength;
	}

	// generates random date to set for new registeration

	static int setCurrentDate()
	{
		time_t t = time(0);  

		tm* now = localtime(&t);

		int day = now->tm_mday + 15;

		if (day > 31)
		{
			day = 31;
		}

		string Day;

		if (day < 10)
		{
			Day = "0" + to_string(day);
		}
		else
		{
			Day = to_string(day);
		}

		int month = (now->tm_mon + 1);

		string Month;

		if (month < 10)
		{
			Month = "0" + to_string(month);
		}
		else
		{
			Month = to_string(month);
		}

		int year = (now->tm_year + 1900);

		string Year = to_string(year);

		string Date = Year + Month + Day;

		int date = stoi(Date);

		return date;
	}

	// printing the current Date

	static void displayDate(int date)
	{
		if (date == 0)
		{
			cout << "NULL";
		}

		else
		{
			string Date = to_string(date);

			char char_year[5] , char_month[3] , char_day[3];

			int x = 0;
			int y;

			for (y = 0; x < 4; y++, x++)
			{
				char_year[y] = Date[x];
			}
			char_year[y] = '\0';

			for (y = 0; x < 6; y++, x++)
			{
				char_month[y] = Date[x];
			}
			char_month[y] = '\0';

			for (y = 0; x < 8; y++, x++)
			{
				char_day[y] = Date[x];
			}
			char_day[y] = '\0';

			cout << char_day << "/" << char_month << "/" << char_year;
		}
	}

	// returns the required date

	static int getCurrentDate(int dueDateCheck = 0)
	{
		time_t t = time(0);  

		tm* now = localtime(&t);

		int day = now->tm_mday;

		if (dueDateCheck == 1)
		{
			day += 7;
		}
		int month = (now->tm_mon + 1);

		if (day > 30)
		{
			day = day - 30;
			month++;
		}
		string Day;

		if (day < 10)
		{
			Day = "0" + to_string(day);
		}
		else
		{
			Day = to_string(day);
		}

		string Month;

		if (month < 10)
		{
			Month = "0" + to_string(month);
		}
		else
		{
			Month = to_string(month);
		}

		int year = (now->tm_year + 1900);

		string Year = to_string(year);

		string Date = Year + Month + Day;

		int date = stoi(Date);

		return date;
	}

	//Function for allocating space and deep copying

	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = StringLenght(buffer);

		char* pointer = 0;

		if (strLen > 0)
		{
			pointer = new char[strLen + 1];

			char* tempDest = pointer;

			for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
			{
				*tempDest = *tempSrc;
			}

			*tempDest = '\0';
		}

		return pointer;
	}

	// Function for comparing two strings and returning true if they match

	static bool SearchString(char* MainString, char* found)                  
	{
		int length = StringLenght(MainString);

		int foundlength = StringLenght(found);

		if (length < foundlength)
		{
			length = foundlength;
		}

		int check = 0;

		for (int i = 0; i < length; i++)
		{
			if (found[0] == MainString[i])
			{
				for (int j = 0, k = i; j < foundlength && k < length; j++, k++)
				{
					if (found[j] == MainString[k])
					{
						check++;
					}
				}
			}
			if (check == length)
			{
				return true;
			}
			else
			{
				check = 0;
			}
		}
		return false;
	}
};

class Tarrif;
class Billing;
class Customer;
class Employee;
class LESCO;

// A Class that handles the Tarrif Tax File to save the different fixed charges, tax
// percentage, and regular and peak prices for the units, which will help in bill
// calculation
class Tarrif
{

public:
	double phase1_com_reg_Price;
	double phase1_dom_reg_Price;
	double phase3_com_reg_Price;
	double phase3_com_peak_Price;
	double phase3_dom_reg_Price;
	double phase3_dom_peak_Price;

	double phase1_dom_fixedCharges;
	double phase1_com_fixedCharges;
	double phase3_dom_fixedCharges;
	double phase3_com_fixedCharges;

	double phase1_dom_taxPercentage;
	double phase1_com_taxPercentage;
	double phase3_dom_taxPercentage;
	double phase3_com_taxPercentage;

	Tarrif();
	void LoadTarrifTaxInfo(ifstream & tarrifTax);
	void updateTarrifFile();
};

// Tarrif Class Constructor
Tarrif::Tarrif()
{
	phase1_com_reg_Price = 0;
	phase1_dom_reg_Price = 0;
	phase3_com_reg_Price = 0;
	phase3_com_peak_Price = 0;
	phase3_dom_reg_Price = 0;
	phase3_dom_peak_Price = 0;

	phase1_dom_fixedCharges = 0;
	phase1_com_fixedCharges = 0;
	phase3_dom_fixedCharges = 0;
	phase3_com_fixedCharges = 0;

	phase1_dom_taxPercentage = 0;
	phase1_com_taxPercentage = 0;
	phase3_dom_taxPercentage = 0;
	phase3_com_taxPercentage = 0;
}

// reads and saves tarrif tax information from file
void Tarrif::LoadTarrifTaxInfo(ifstream& tarrifTax)
{

	if (tarrifTax.is_open())
	{
		char tempMeter[50];
		tarrifTax.get(tempMeter, 50, ',');
		tarrifTax.ignore();
		tarrifTax >> phase1_dom_reg_Price;
		tarrifTax.ignore();		
		tarrifTax.ignore();
		tarrifTax >> phase1_dom_taxPercentage;
		tarrifTax.ignore();
		tarrifTax >> phase1_dom_fixedCharges;

		tarrifTax.get(tempMeter, 50, ',');
		tarrifTax.ignore();
		tarrifTax >> phase1_com_reg_Price;
		tarrifTax.ignore();		
		tarrifTax.ignore();
		tarrifTax >> phase1_com_taxPercentage;
		tarrifTax.ignore();
		tarrifTax >> phase1_com_fixedCharges;

		tarrifTax.get(tempMeter, 50, ',');
		tarrifTax.ignore();
		tarrifTax >> phase3_dom_reg_Price;
		tarrifTax.ignore();		
		tarrifTax >> phase3_dom_peak_Price;
		tarrifTax.ignore();
		tarrifTax >> phase3_dom_taxPercentage;
		tarrifTax.ignore();
		tarrifTax >> phase3_dom_fixedCharges;

		tarrifTax.get(tempMeter, 50, ',');
		tarrifTax.ignore();
		tarrifTax >> phase3_com_reg_Price;
		tarrifTax.ignore();		
		tarrifTax >> phase3_com_peak_Price;
		tarrifTax.ignore();
		tarrifTax >> phase3_com_taxPercentage;
		tarrifTax.ignore();
		tarrifTax >> phase3_com_fixedCharges;

		tarrifTax.close();
	}

}

// incase tax information changes, as a real time LESCO example, it can be easily updated in thr records as well
// as for the calculations
void Tarrif::updateTarrifFile()
{
	bool flag = false;

	int phase = 0;

	while (!flag)
	{
		cout << "1. Update Information for Phase-1 Meter" << endl;
		cout << "2. Update Information for Phase-3 Meter" << endl;

		switch (getch())
		{
		case '1':
			phase = 1;
			flag = true;
			break;

		case '2':
			phase = 2;
			flag = true;
			break;

		default:
			cout << "Invalid input. Enter again." << endl << endl;
			break;
		}
	}

	if (phase == 1)
	{
		flag = false;

		while (!flag)
		{
			cout << "1. Domestic Customer" << endl;
			cout << "2. Commercial Customer" << endl;

			switch (getch())
			{
			case '1':
				cout << "Enter the regular unit price: " << endl;
				cin >> phase1_dom_reg_Price;

				cout << "Enter the tax percentage: " << endl;
				cin >> phase1_dom_taxPercentage;

				cout << "Enter the fixed charges: " << endl;
				cin >> phase1_dom_fixedCharges;
				flag = true;
				break;

			case '2':
				cout << "Enter the regular unit price: " << endl;
				cin >> phase1_com_reg_Price;

				cout << "Enter the tax percentage: " << endl;
				cin >> phase1_com_taxPercentage;

				cout << "Enter the fixed charges: " << endl;
				cin >> phase1_com_fixedCharges;
				flag = true;
				break;

			default:
				cout << "Invalid input. Enter again." << endl << endl;
				break;
			}
		}
	}

	if (phase == 2)
	{
		flag = false;

		while (!flag)
		{
			cout << "1. Domestic Customer" << endl;
			cout << "2. Commercial Customer" << endl;

			switch (getch())
			{
			case '1':
				cout << "Enter the regular unit price: " << endl;
				cin >> phase3_dom_reg_Price;

				cout << "Enter the peak hour unit price: " << endl;
				cin >> phase3_dom_peak_Price;

				cout << "Enter the tax percentage: " << endl;
				cin >> phase3_dom_taxPercentage;

				cout << "Enter the fixed charges: " << endl;
				cin >> phase3_dom_fixedCharges;

				flag = true;
				break;


			case '2':
				cout << "Enter the regular unit price: " << endl;
				cin >> phase3_com_reg_Price;

				cout << "Enter the peak hour unit price: " << endl;
				cin >> phase3_com_peak_Price;

				cout << "Enter the tax percentage: " << endl;
				cin >> phase3_com_taxPercentage;

				cout << "Enter the fixed charges: " << endl;
				cin >> phase3_com_fixedCharges;
				flag = true;
				break;

			default:
				cout << "Invalid input. Enter again." << endl << endl;
				break;
			}
		}
	}

	ofstream fout("TarrifTaxInfo.txt");

	fout << "1Phase" << "," << phase1_dom_reg_Price << ",," << phase1_dom_taxPercentage << "," << phase1_dom_fixedCharges << endl;
	fout << "1Phase" << "," << phase1_com_reg_Price << ",," << phase1_com_taxPercentage << "," << phase1_com_fixedCharges << endl;
	fout << "3Phase" << "," << phase3_dom_reg_Price << "," << phase3_dom_peak_Price << "," << phase3_dom_taxPercentage << "," << phase3_dom_fixedCharges << endl;
	fout << "3Phase" << "," << phase3_com_reg_Price << "," << phase3_com_peak_Price << "," << phase3_com_taxPercentage << "," << phase3_com_fixedCharges;
}

// A Class to implement calculation of bill, using given customer tax information and setting
// status of the bill to either paid or unpaid, as well as setting due and fixed date
class Billing
{
protected:
	int dueDate;
	int paidDate;
	char* billerID;
	char* billStatus;
	int fixedCharges;
	int billingMonth;
	int readingEntryDate;
	double salesTaxAmount;
	double electricityCost;
	double totalBillingAmount;
	double currentMeter_Regular;

public:
	Billing();
	~Billing();
	char* getBillerID();

	virtual void print();
	virtual char* getBillStatus();
	virtual double getTotalBill();

	virtual void updateBillingFile(ofstream&);
	virtual void calculateBill(double, double);
	virtual void setStatus(char*, double&, double&);
	virtual void addNewBillingInfo(char*, char*, char*);
	virtual void loadBillingInfoFromFile(ifstream&, char*);

	virtual int getDueDate();
	virtual int getFixedCharges();
	virtual double getSalesTaxAmount();
	virtual double getElectricityCost();
	virtual double getCurrentMeterReading();
};

// Billing Class Constructor
Billing::Billing()
{
	dueDate = 0;
	paidDate = 0;
	fixedCharges = 0;
	billingMonth = 0;
	salesTaxAmount = 0;
	electricityCost = 0;
	totalBillingAmount = 0;
	currentMeter_Regular = 0;
	billStatus = billerID = nullptr;
}

// Billing Class Destructor
Billing::~Billing()
{
	if (billStatus)
	{
		delete[] billStatus;
	}

	if (billerID)
	{
		delete[] billerID;
	}
}

// Getters for accessing private / protected members in other Classes
double Billing::getElectricityCost()
{
	return electricityCost;
}

double Billing::getSalesTaxAmount()
{
	return salesTaxAmount;
}

int Billing::getFixedCharges()
{
	return fixedCharges;
}

int Billing::getDueDate()
{
	return dueDate;
}

char* Billing::getBillerID()
{
	return billerID;
}

double Billing::getCurrentMeterReading()
{
	return currentMeter_Regular;
}

char* Billing::getBillStatus()
{
	return billStatus;
}

double Billing::getTotalBill()
{
	return totalBillingAmount;
}

// setting a newly added customer's bill and status
void Billing::addNewBillingInfo(char* ID, char* customertype, char* metertype)
{
	billerID = ID;

	time_t t = time(0);                                                   // get time now

	tm* now = localtime(&t);

	int month = (now->tm_mon + 1);

	string Month;

	if(month < 10)
		Month = "0" + to_string(month);

	else
	{
		Month = to_string(month);
	}

	billingMonth = stoi(Month);

	currentMeter_Regular = 0;

	readingEntryDate = Helper::getCurrentDate();

	totalBillingAmount = 0;

	dueDate = Helper::getCurrentDate(1);

	Tarrif TarrifInfo;

	ifstream readTax("TarrifTaxInfo.txt");

	TarrifInfo.LoadTarrifTaxInfo(readTax);

	readTax.close();

	if (customertype[0] == 'd' && metertype[0] == '1')
	{
		electricityCost = TarrifInfo.phase1_dom_reg_Price;
		fixedCharges = TarrifInfo.phase1_dom_fixedCharges;
		salesTaxAmount = TarrifInfo.phase1_dom_taxPercentage;
	}

	else if (customertype[0] == 'c' && metertype[0] == '1')
	{
		electricityCost = TarrifInfo.phase1_com_reg_Price;
		fixedCharges = TarrifInfo.phase1_com_fixedCharges;
		salesTaxAmount = TarrifInfo.phase1_com_taxPercentage;
	}

	paidDate = 0;

	billStatus = "0";
}

// reads existing customers billing information from file and sets variables
void Billing::loadBillingInfoFromFile(ifstream& fin, char* biller_ID)
{
	billerID = biller_ID;

	fin >> billingMonth;
	fin.ignore();
	fin >> currentMeter_Regular;
	fin.ignore();
	fin.ignore();
	fin >> readingEntryDate;
	fin.ignore();
	fin >> electricityCost;
	fin.ignore();
	fin.ignore();
	fin >> salesTaxAmount;
	fin.ignore();
	fin >> fixedCharges;
	fin.ignore();
	fin >> totalBillingAmount;
	fin.ignore();
	fin >> dueDate;
	fin.ignore();

	char tempBillStatus[10];

	fin.getline(tempBillStatus, 100, ',');

	billStatus = Helper::GetStringFromBuffer(tempBillStatus);

	fin >> paidDate;
}

// sets status of bill of existing customers
void Billing::setStatus(char* status, double& regUnits, double& peakUnits)
{
	if (status[0] == '0')
	{
		billStatus = status;
		paidDate = 0;

		readingEntryDate = Helper::getCurrentDate();
		regUnits = currentMeter_Regular;

		cout << "Enter the current meter reading: " << endl;
		cin >> currentMeter_Regular;

		while (currentMeter_Regular < regUnits)
		{
			cout << "\nEnter reading greater than previous\n";
			cin >> currentMeter_Regular;
		}

		calculateBill(regUnits, 0);
		dueDate = Helper::getCurrentDate(1);
	}

	if (status[0] == 'p')
	{
		billStatus = status;
		paidDate = Helper::getCurrentDate();

		regUnits = currentMeter_Regular;
		peakUnits = 0;
		readingEntryDate = 0;
		dueDate = 0;
		totalBillingAmount = 0;
	}
}

// formula implementation of bill calculation
void Billing::calculateBill(double regUnits, double peakUnits)
{
	int unitsConsumed = currentMeter_Regular - regUnits;
	int costOfElectricity = unitsConsumed * electricityCost;

	costOfElectricity += costOfElectricity * (salesTaxAmount / 100);
	costOfElectricity += fixedCharges;
	totalBillingAmount = costOfElectricity;
}

// incase of new addition or change, updation of file with new values
void Billing::updateBillingFile(ofstream& fout)
{
	fout << billerID << "," << billingMonth << "," << currentMeter_Regular << ",," << readingEntryDate << "," << electricityCost << ",,"
		<< salesTaxAmount << "," << fixedCharges << "," << totalBillingAmount << "," << dueDate << "," << billStatus << "," << paidDate;
}

// interface print for billing month, meter type, costs, taxes, and percentages
void Billing::print()
{

	cout << "Billing Month:   " << billingMonth << endl;
	cout << "Current Meter:   " << currentMeter_Regular << endl;
	cout << "Entry Date:   ";

	Helper::displayDate(readingEntryDate);

	cout << endl;

	cout << "Electricity Cost:   " << electricityCost << endl;
	cout << "Sales Tax Amount:   " << salesTaxAmount << endl;
	cout << "Fixed Charges:   " << fixedCharges << endl;
	cout << "Total Amount:   " << totalBillingAmount << endl;
	cout << "Due Date:   ";

	Helper::displayDate(dueDate);

	cout << endl << "Bill Status:   ";

	if (billStatus[0] == '0')
	{
		cout << "UNPAID" << endl;
	}
	if (billStatus[0] == 'p')
	{
		cout << "PAID" << endl;
	}

	cout << "Paid Date:   ";

	Helper::displayDate(paidDate);
	cout << endl;
}

// A Class that is inherited with Billing Class and handles phase 3 meter calculations separately
// by also incooperating Polymorphism
class phase3Meter : public Billing
{
private:
	double currentMeter_Peak;
	double electricityCost_Peak;

public:
	void print();

	double getTotalBill();
	char* getBillStatus();

	void updateBillingFile(ofstream&);
	void calculateBill(double, double);
	void setStatus(char*, double&, double&);
	void addNewBillingInfo(char*, char*, char*);
	void loadBillingInfoFromFile(ifstream&, char*);
};

// A Class to handle all Customer Functionality, and saving its personal attributes as well as meter information
class Customer
{
private:
	Billing* biller;

	char* meterType;
	int customerDOB;
	char* customerID;

	int connectionDate;
	char* customerName;
	char* customerType;
	char* customerPhone;
	double regularUnits;
	double peakHourUnits;
	char* customerAddress;

public:
	Customer();
	~Customer();

	int getPeakUnits();
	int getRegularUnits();

	char* getBillStatus();

	char* getMeterType();
	char* getCustomerID();
	int   getCustomerDOB();
	char* getCustomerType();
	char* getCustomerName();
	char* getCustomerPhone();
	char* getCustomerAddress();

	void PrintCustomer();
	void addNewCustomer(Customer**&, int);
	void setBillStatus(char*);
	void LoadSingleCustomer(ifstream&);
	void billingSetter(Billing* bills);
	void updateCustomerFile(ofstream&);

};

// Customer Class's Constructor
Customer::Customer()
{
	customerID = 0;
	customerDOB = 0;
	regularUnits = 0;
	peakHourUnits = 0;
	connectionDate = 0;

	customerPhone = 0;

	meterType = nullptr;
	customerType = nullptr;
	customerName = nullptr;
	customerAddress = nullptr;

	biller = nullptr;
}

// Destructor of Customer Class
Customer::~Customer()
{
	if(biller)
		biller = NULL;

	if (meterType)
		delete [] meterType;

	if (customerName)
		delete [] customerName;

	if (customerType)
		delete [] customerType;

	if (customerAddress)
		delete [] customerAddress;

	if (customerPhone)
		delete [] customerPhone;

	if (customerID)
		delete [] customerID;
}

// getters for private Customer Attributes

char* Customer::getCustomerID()
{
	return customerID;
}

char* Customer::getCustomerName()
{
	return customerName;
}

char* Customer::getCustomerAddress()
{
	return customerAddress;
}

char* Customer::getCustomerPhone()
{
	return customerPhone;
}

int Customer::getCustomerDOB()
{
	return customerDOB;
}

char* Customer::getMeterType()
{
	return meterType;
}

char* Customer::getCustomerType()
{
	return customerType;
}

char* Customer::getBillStatus()
{
	return biller -> getBillStatus();
}

int Customer::getRegularUnits()
{
	return regularUnits;
}

int Customer::getPeakUnits()
{
	return peakHourUnits;
}

void Customer::billingSetter(Billing* bills)
{
	biller = bills;
}

// sets bill status according to passed units and previous status
void Customer::setBillStatus(char* status)
{
	biller -> setStatus(status, regularUnits, peakHourUnits);
}

// Reading one customer from file, and saving it's attributes respectively
void Customer::LoadSingleCustomer(ifstream& CustomerData)
{

	char tempCustomerName[50], tempCustomerType[50], tempCustomerPhase[50], tempCustomerAddress[50], tempCustomerPhone[50];
	char tempID[10];

	CustomerData.get(tempID, 1000, ',');

	customerID = Helper::GetStringFromBuffer(tempID);

	CustomerData.ignore();

	CustomerData >> customerDOB;

	CustomerData.ignore();

	CustomerData.get(tempCustomerName, 1000, ',');

	customerName = Helper::GetStringFromBuffer(tempCustomerName);

	CustomerData.ignore();

	CustomerData.get(tempCustomerAddress, 1000, ',');

	customerAddress = Helper::GetStringFromBuffer(tempCustomerAddress);

	CustomerData.ignore();

	CustomerData.get(tempCustomerPhone, 1000, ',');

	customerPhone = Helper::GetStringFromBuffer(tempCustomerPhone);

	CustomerData.ignore();

	CustomerData.get(tempCustomerType, 1000, ',');

	customerType = Helper::GetStringFromBuffer(tempCustomerType);

	CustomerData.ignore();

	CustomerData.get(tempCustomerPhase, 1000, ',');

	meterType = Helper::GetStringFromBuffer(tempCustomerPhase);

	CustomerData.ignore();

	CustomerData >> connectionDate;

	CustomerData.ignore();

	CustomerData >> regularUnits;

	if (meterType[0] == '3')
	{
		CustomerData.ignore();

		CustomerData >> peakHourUnits;
	}
}

// incase of new Customer, updates the Customer file with the input attributes on run time
void Customer::updateCustomerFile(ofstream& fout)
{
	fout << customerID << "," << customerDOB << "," << customerName << "," << customerAddress << "," << customerPhone << "," << customerType
		<< "," << meterType << "," << connectionDate << "," << regularUnits;

	if (meterType[0] == '3')
	{
		fout << "," << peakHourUnits;
	}
}

// takes new Customer Information while registration
void Customer::addNewCustomer(Customer**& List, int total)
{

	char temp[500];

	cout << "Enter customer's name: " << endl;
	cin.ignore();
	cin.getline(temp, 500);

	customerName = Helper::GetStringFromBuffer(temp);

	cout << "Enter customer's DOB in the format(YYYYMMDD): " << endl;
	cin >> customerDOB;

	cout << "Enter customer's address: " << endl;
	cin.ignore();
	cin.getline(temp, 500);

	customerAddress = Helper::GetStringFromBuffer(temp);

	cout << "Enter customer's phone number: " << endl;

	cin.getline(temp, 500);
	customerPhone = Helper::GetStringFromBuffer(temp);

	bool flag = false;

	while (!flag)
	{
		cout << "Customer Type: " << endl;

		cout << "1. Domestic          2. Commercial" << endl;

		switch (getch())
		{
		case '1':
			customerType = "domestic";
			flag = true;
			break;
		case '2':
			customerType = "commercial";
			flag = true;
			break;

		default:
			cout << "Invalid input. Enter again." << endl << endl;
			break;
		}
	}
	regularUnits = 0;


	flag = false;

	while (!flag)
	{
		cout << "Meter Type" << endl;
		cout << "1. 1-Phase         2. 3-Phase" << endl;
		switch (getch())
		{
		case '1':
			meterType = "1Phase";
			biller = new Billing();
			flag = true;
			break;
		case '2':
			meterType = "3Phase";
			peakHourUnits = 0;
			biller = new phase3Meter();
			flag = true;
			break;
		default:
			cout << "Invalid input. Enter again." << endl << endl;
			break;
		}
	}

	connectionDate = Helper::getCurrentDate();
	char tempID[5];
	flag = false;
	while(!flag)
	{
		flag = true;
		int number = rand() % 9000 + 1000;
		int i;

		sprintf(tempID, "%d", number);                                                     // generating random valid ID

		for(int i = 0; i < total; i++)
		{
			char* temp = List[i] -> getCustomerID();
			if(Helper::SearchString(temp, tempID))
				flag = false;
		}
		
	}

	customerID = Helper::GetStringFromBuffer(tempID);
}

// Printing of Single Customer with all attributes as well
void Customer::PrintCustomer()
{

	cout << "Customer ID  :   " << customerID << endl;

	cout << "Date of Birth:   ";

	Helper::displayDate(customerDOB);
	cout << endl;

	cout << "Customer Name:   " << customerName << endl;

	cout << "House address:   " << customerAddress << endl;

	cout << "Phone Number :   " << customerPhone << endl;

	cout << "Customer Type:   " << customerType << endl;

	cout << "Meter Type   :   " << meterType << endl;

	cout << "Regular Units:   " << regularUnits << endl;

	if (meterType[0] == '3')
	{
		cout << "Peak Units   :   " << peakHourUnits << endl;
	}

	biller->print();
}

char* phase3Meter::getBillStatus()
{
	return billStatus;
}

void phase3Meter::addNewBillingInfo(char* ID, char* customertype, char* metertype)
{
	billerID = ID;
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);

	int month = (now->tm_mon + 1);

	string Month;

	if(month < 10)
		Month = "0" + to_string(month);
	else
	{
		Month = to_string(month);
	}

	billingMonth = stoi(Month);

	currentMeter_Regular = 0;
	currentMeter_Peak = 0;

	readingEntryDate = Helper::getCurrentDate();

	totalBillingAmount = 0;

	dueDate = Helper::getCurrentDate();

	Tarrif TarrifInfo;
	ifstream readTax("TarrifTaxInfo.txt");
	TarrifInfo.LoadTarrifTaxInfo(readTax);
	readTax.close();

	if(customertype[0] == 'd' && metertype[0] == '3')
	{
		electricityCost_Peak = TarrifInfo.phase3_dom_peak_Price;
		electricityCost = TarrifInfo.phase3_dom_reg_Price;
		salesTaxAmount = TarrifInfo.phase3_dom_taxPercentage;
		fixedCharges = TarrifInfo.phase3_dom_fixedCharges;
	}

	else if(customertype[0] == 'c' && metertype[0] == '3')
	{
		electricityCost_Peak = TarrifInfo.phase3_com_peak_Price;
		electricityCost = TarrifInfo.phase3_com_reg_Price;
		salesTaxAmount = TarrifInfo.phase3_com_taxPercentage;
		fixedCharges = TarrifInfo.phase3_com_fixedCharges;
	}

	paidDate = 0;

	billStatus = "0";
}

void phase3Meter::loadBillingInfoFromFile(ifstream& fin, char* biller_ID)
{
	billerID = biller_ID;
	fin >> billingMonth;
	fin.ignore();
	fin >> currentMeter_Regular;
	fin.ignore();
	fin >> currentMeter_Peak;
	fin.ignore();
	fin>>readingEntryDate;
	fin.ignore();
	fin>>electricityCost;
	fin.ignore();
	fin>>electricityCost_Peak;
	fin.ignore();
	fin>>salesTaxAmount;
	fin.ignore();
	fin>>fixedCharges;
	fin.ignore();
	fin>>totalBillingAmount;
	fin.ignore();
	fin >> dueDate;
	fin.ignore();
	char tempBillStatus[10];
	fin.getline(tempBillStatus, 100, ',');
	billStatus = Helper::GetStringFromBuffer(tempBillStatus);
	fin >> paidDate;
}

void phase3Meter::setStatus(char* status, double& regUnits, double& peakUnits)
{
	if(status[0] == '0')
	{
		billStatus = status;
		paidDate = 0;
		readingEntryDate = Helper::getCurrentDate();
		regUnits = currentMeter_Regular;
		peakUnits = currentMeter_Peak;
		cout << "Enter the current meter regular reading: "<<endl;
		cin >> currentMeter_Regular;
		while(currentMeter_Regular<regUnits)
		{
			cout << "\nEnter the current meter greater than previos:\n "<<endl;
			cin >> currentMeter_Regular;

		}
		cout << "Enter the current meter peak hour reading: "<<endl;
		cin >> currentMeter_Peak;

		while(currentMeter_Peak<peakUnits)
		{
			cout << "\nEnter the current meter peak greater than previos: \n"<<endl;
			cin >> currentMeter_Peak;

		}

		calculateBill(regUnits, currentMeter_Peak);
		dueDate = Helper::getCurrentDate(1);
	}

	if(status[0] == 'p')
	{
		billStatus = status;
		paidDate = Helper::getCurrentDate();

		regUnits = currentMeter_Regular;
		peakUnits = currentMeter_Peak;
		readingEntryDate = 0;
		dueDate = 0;
		totalBillingAmount = 0;
	}
}

void phase3Meter::updateBillingFile(ofstream& fout)
{
	fout<<billerID<<","<<billingMonth<<","<<currentMeter_Regular<<","<<currentMeter_Peak
		<<","<<readingEntryDate<<","<<electricityCost<<","<<electricityCost_Peak<<","
		<<salesTaxAmount<<","<<fixedCharges<<","<<totalBillingAmount<<","<< dueDate<<","
		<< billStatus<<","<< paidDate;
}

void phase3Meter::calculateBill(double regUnits, double peakUnits)
{
	double regUnitsConsumed = currentMeter_Regular - regUnits;
	double peakUnitsConsumed = currentMeter_Peak - peakUnits;
	double costOfRegElectricity = regUnitsConsumed * electricityCost;
	double costOfPeakElectricity = peakUnitsConsumed * electricityCost_Peak;
	double costOfElectricity = costOfRegElectricity + costOfPeakElectricity;

	costOfElectricity += costOfElectricity * (salesTaxAmount / 100);
	costOfElectricity += fixedCharges;
	totalBillingAmount = costOfElectricity;
}

double phase3Meter::getTotalBill()
{
	return totalBillingAmount;
}

void phase3Meter::print()
{
	cout<<"Billing Month:   "<<billingMonth<<endl;
	cout<<"Current Meter:   "<<currentMeter_Regular<<endl;
	cout<<"Current Meter Peak:   "<<currentMeter_Peak<<endl;
	cout<<"Entry Date:   ";
	Helper::displayDate(readingEntryDate);
	cout<<endl;
	cout<<"Electricity Cost:   "<<electricityCost<<endl;
	cout<<"Electricity Cost Peak:   "<<electricityCost_Peak<<endl;
	cout<<"Sales Tax Amount:   "<<salesTaxAmount<<endl;
	cout<<"Fixed Charges:   "<<fixedCharges<<endl;
	cout<<"Total Amount:   "<<totalBillingAmount<<endl;
	cout<<"Due Date:   ";
	Helper::displayDate(dueDate);
	cout<<endl;
	cout<<"Bill Status:   ";
	if(billStatus[0] == '0')
		cout<<"UNPAID"<<endl;
	if(billStatus[0] == 'p')
		cout<<"PAID"<<endl;
	cout<<"Paid Date:   ";
	Helper::displayDate(paidDate);
	cout<<endl;
}

class Employee
{
private:
	char* employeeID;
	char* employeePass;
	Tarrif** customerBill;

public:
	Employee();
	~Employee();
	void loadFromFile(ifstream& fin);
	void printEmployee();
	bool updatePassword();
	char* getEmployeeID();
	char* getEmployeePass();
	bool setBillStatus(Customer*&);
	void addNewCustomer(Customer**&, Billing**&,int&);
};

//constructor
Employee::Employee()
{
	employeeID = NULL;
	employeePass = NULL;
	customerBill = NULL;
}

//destructor
Employee::~Employee()
{
	if (employeeID)
		delete [] employeeID;

	if (employeePass)
		delete [] employeePass;

	if(customerBill)
		customerBill = NULL;
}

char* Employee::getEmployeeID()
{
	return employeeID;
}

void Employee::addNewCustomer(Customer**& customerlist, Billing**& billinglist,int& totalcustomer)
{
	customerlist[totalcustomer] = new Customer();

	customerlist[totalcustomer] -> addNewCustomer(customerlist, totalcustomer);
	char* customerid = customerlist[totalcustomer] -> getCustomerID();
	char* customertype = customerlist[totalcustomer] -> getCustomerType();
	char* metertype = customerlist[totalcustomer] -> getMeterType();
	if(metertype[0] == '1')
		billinglist[totalcustomer] = new Billing();

	if(metertype[0] == '3')
		billinglist[totalcustomer] = new phase3Meter();

	billinglist[totalcustomer] -> addNewBillingInfo(customerid, customertype, metertype);
	customerlist[totalcustomer] -> billingSetter(billinglist[totalcustomer]);
	totalcustomer++;

}

char* Employee::getEmployeePass()
{
	return employeePass;
}

// Loads Single Employees Data from Employee File
void Employee::loadFromFile(ifstream& fin)
{
	char temp[100];

	char TempUserName[50];

	char TempPassword[50];

	fin.getline(temp, 100, '\n');

	int length = Helper::StringLenght(temp);

	int i = 0;

	for (i = 0; ; i++)
	{
		if (temp[i] == ',')
		{
			break;
		}

		TempUserName[i] = temp[i];
	}
	TempUserName[i] = '\0';

	employeeID = Helper::GetStringFromBuffer(TempUserName);

	i += 2;

	int j = 0;

	for (j = 0; i < length; j++, i++)
	{
		TempPassword[j] = temp[i];
	}

	TempPassword[j] = '\0';

	employeePass = Helper::GetStringFromBuffer(TempPassword);
}

// Password Change Option for Single Value
bool Employee::updatePassword()
{
	bool passwordChanged = false;

	char temp[100];

	cout << "Enter your current password: \t";

	cin >> temp;

	char* oldPassword = Helper::GetStringFromBuffer(temp);

	cout << "Enter your new password: \t";

	cin >> temp;

	char* newPassword = Helper::GetStringFromBuffer(temp);

	while (Helper::StringLenght(newPassword) < 4)
	{
		cout << "Please enter a password greater than 4 digits!\n";

		cin >> temp;
		newPassword = Helper::GetStringFromBuffer(temp);
	}

	while (!passwordChanged)
	{
		if (Helper::SearchString(employeePass, oldPassword))
		{
			passwordChanged = true;

			delete[] employeePass;

			employeePass = Helper::GetStringFromBuffer(newPassword);

			cout << "Password changed successfully\n";
		}

		else
		{
			system("cls");
			passwordChanged = false;

			cout << "The entered current password is invalid, Please try again!\n";

			cout << "If you want to go back, please enter B\n";
			cout << "Enter your current password: \t";

			cin >> temp;

			if (temp[0] == 'b' || temp[0] == 'B')
			{
				break;
			}

			oldPassword = Helper::GetStringFromBuffer(temp);

			cout << "Enter your new password: \t";
			cin >> temp;

			newPassword = Helper::GetStringFromBuffer(temp);
		}
	}
	return passwordChanged;
}

// Employee can set Customers Bill Status
bool Employee::setBillStatus(Customer*& customer)
{
	int bill_status;
	char* billstatus;

	bool flag = false;

	while (!flag)
	{
		cout << "1. Paid" << endl;
		cout << "2. unpaid" << endl;

		switch (getch())
		{
		case '1':
			billstatus = "paid";
			flag = true;
			break;

		case '2':
			billstatus = "0";
			flag = true;
			break;

		default:
			cout << "Invalid input. Enter again." << endl << endl;
			break;
		}
	}
	char* temp = customer->getBillStatus();

	if (temp[0] == 'p' && billstatus[0] == 'p')
	{
		cout << "This Bill has been already marked as paid!" << endl;
		return false;
	}

	if (temp[0] == '0' && billstatus[0] == '0')
	{
		cout << "This Bill is already unpaid!" << endl;
		return false;
	}

	else
	{
		customer->setBillStatus(billstatus);
		return true;
	}
}

// prints Employee ID and Password
void Employee::printEmployee()
{
	cout << employeeID << ", " << employeePass;
}

// Main Class that contains both employees and customers information as well as calculates and provides bills overall
class LESCO
{
private:
	int totalEmployee;
	int totalCustomers;
	Customer** customerList;
	Employee** employeeList;
	Employee* CurrentEmployee;
	Customer* CurrentCustomer;
	Customer* CustomerLogin;
	Billing** billingList;

public:
	LESCO();
	void loadDataFromFile();
	void updateTarrifFile();
	void updateBillingInfo();

	Employee* employeeLogin();
	Employee* SearchEmployeeID(char*);

	Customer* searchCustomerID(char*);

	void changeEmployeePassword();
	void saveUpdatedEmployeeList();


	void setBillStatus();
	void getBillsReport();
	void AssociateBills();
	void loadBillingInfo();
	void ViewCurrentBill();
	void registerCustomer();
	void ViewCustomerInfo();
	char* getCurrentEmployee();
	char* getCurrentCustomer();
	void updateCustomerInfo();
	void calculateTotalBills();

	Customer* CustomerMainLogin();
	Customer* CustomerViewBillLogin();

	~LESCO();
};

// LESCO Class COnstructor
LESCO::LESCO()
{
	totalEmployee = 0;
	totalCustomers = 0;
	customerList = nullptr;
	employeeList = nullptr;
	billingList = nullptr;
}

// Simultaneously loads all files data by using Classes and sets their attributes
void LESCO::loadDataFromFile()
{
	ifstream readEmployees("EmployeesData.txt");
	if (readEmployees.is_open())
	{
		char tempList[100] = { '\0' };

		while (!readEmployees.eof())
		{
			readEmployees.getline(tempList, 100, '\n');
			totalEmployee++;
		}

		readEmployees.close();
		readEmployees.open("EmployeesData.txt");
		int i = 0;
		employeeList = new Employee * [totalEmployee];

		while (i < totalEmployee)
		{
			employeeList[i] = new Employee();
			employeeList[i]->loadFromFile(readEmployees);
			i++;
		}
		readEmployees.close();
	}
	totalCustomers = 0;
	ifstream readCustomers("CustomerInfo.txt");

	if (readCustomers.is_open())
	{
		int i = 0;

		while (!readCustomers.eof())
		{
			char a[200];

			readCustomers.getline(a, 200, '\n');
			totalCustomers++;


		}
		readCustomers.close();

		ifstream readCustomers("CustomerInfo.txt");

		customerList = new Customer * [totalCustomers + 5];

		while (i < totalCustomers)
		{

			customerList[i] = new Customer();
			customerList[i]->LoadSingleCustomer(readCustomers);
			readCustomers.ignore();
			i++;
		}
		readCustomers.close();
		i = 0;
	}
}

// getters for LESCO Class members

char* LESCO::getCurrentEmployee()
{
	return CurrentEmployee->getEmployeeID();
}

char* LESCO::getCurrentCustomer()
{
	return CurrentCustomer->getCustomerID();
}

// returns employee if searched employee is found
Employee* LESCO::SearchEmployeeID(char* ID)
{
	for (int i = 0; i < totalEmployee; i++)
	{
		char* compareID = employeeList[i]->getEmployeeID();

		if (Helper::SearchString(ID, compareID))
			return employeeList[i];
	}

	return nullptr;
}

// Final LESCO calculation of bills for all customers according to phases
void LESCO::calculateTotalBills()
{
	for (int i = 0; i < totalCustomers; i++)
	{
		if (billingList[i]->getTotalBill() == 0)
		{

			int regUnitsConsumed = 0;
			int peakUnitsConsumed = 0;

			char* metertype = customerList[i]->getMeterType();
			char* customerType = customerList[i]->getCustomerType();

			if (metertype[0] == '1')
			{
				peakUnitsConsumed = 0;
				regUnitsConsumed = customerList[i]->getRegularUnits();
				billingList[i]->calculateBill(regUnitsConsumed, peakUnitsConsumed);
			}

			if (metertype[0] == '3')
			{
				regUnitsConsumed = customerList[i]->getRegularUnits();
				peakUnitsConsumed = customerList[i]->getPeakUnits();
				billingList[i]->calculateBill(regUnitsConsumed, peakUnitsConsumed);
			}

		}
	}
}

// Updation of the tarrif file
void LESCO::updateTarrifFile()
{
	ifstream fin("TarrifTaxInfo.txt");

	Tarrif TarrifInfo;

	TarrifInfo.LoadTarrifTaxInfo(fin);

	TarrifInfo.updateTarrifFile();
}

// for every customer sets their bill status
void LESCO::setBillStatus()
{
	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < totalCustomers; i++)
	{
		cout << i + 1 << ". " << "Customer ID: " << customerList[i]->getCustomerID() << "\tCurrent Bill Status: ";

		char* temp = billingList[i]->getBillStatus();

		if (temp[0] == '0')
		{
			cout << "UNPAID";
		}
		if (temp[0] == 'p')
		{
			cout << "PAID";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------------" << endl;
	char customerid[10];
	cout << "Enter the customer ID: " << endl;
	cin >> customerid;
	if (CurrentCustomer == searchCustomerID(customerid))
	{

		if (CurrentEmployee->setBillStatus(CurrentCustomer))
		{
			cout << "Bill Status Successfully Changed!" << endl;
			updateCustomerInfo();
			updateBillingInfo();
		}
	}

	else
		cout << "No such customer exist with the ID " << customerid << endl;
}

// updation of file for all customers bill
void LESCO::updateBillingInfo()
{
	ofstream fout("BillingInfo.txt");

	for (int i = 0; i < totalCustomers; i++)
	{
		billingList[i]->updateBillingFile(fout);

		if (i < totalCustomers - 1)
			fout << endl;
	}
}

// searchs and checks if the sent ID matches
Customer* LESCO::searchCustomerID(char* str1)
{
	int i = 0;
	while (i < totalCustomers)
	{
		char* str2 = customerList[i]->getCustomerID();

		if (Helper::SearchString(str1, str2)) //If a friend ID is matched, return true
		{
			return customerList[i];
		}

		i++;
	}

	return false;
}

// Printing of how many bills of customers are paid or not efficient in keeping
// track of all bills and updates
void LESCO::getBillsReport()
{
	int unpaidBills = 0;
	int paidBills = 0;

	for (int i = 0; i < totalCustomers; i++)
	{
		char* temp = billingList[i]->getBillStatus();

		if (temp[0] == '0')
			unpaidBills++;

		if (temp[0] == 'p')
			paidBills++;
	}

	cout << "Total Bills Paid: " << paidBills << endl;
	cout << "Total Bills Unpaid: " << unpaidBills;
}

// Associates bill with the customers
void LESCO::AssociateBills()
{
	int i = 0;
	while (i < totalCustomers)
	{
		char* tempID = billingList[i]->getBillerID();

		int j = 0;

		while (j < totalCustomers)
		{
			char* customerID = customerList[j]->getCustomerID();
			if (Helper::SearchString(tempID, customerID))
			{
				customerList[j]->billingSetter(billingList[i]);
				break;
			}
			j++;
		}
		i++;
	}
}

// Employee can login through LESCO's portal as well as update password in both file and password variable
Employee* LESCO::employeeLogin()
{
	bool userFlag = false;
	char temp[50];
	int attempt = 0;

	while (!userFlag && attempt < 4)
	{
		cout << "Enter Employee ID: \t";
		cin >> temp;
		char* userName = Helper::GetStringFromBuffer(temp);

		if (SearchEmployeeID(userName))
		{
			userFlag = true;
			CurrentEmployee = SearchEmployeeID(userName);
			attempt += 3;
		}

		else
		{
			system("cls");
			cout << "No such employee exists with the ID \"" << userName << "\" Please try again!" << endl;
			userFlag = false;
			attempt++;
		}
	}

	if (userFlag == true)
	{
		userFlag = false;
		attempt = 0;
		cout << "Enter Your Password: \t";
		cin >> temp;
		char* password = Helper::GetStringFromBuffer(temp);
		char* comparePass = CurrentEmployee->getEmployeePass();
		while (!userFlag && attempt < 3)
		{

			if (Helper::SearchString(comparePass, password))
			{
				userFlag = true;
				system("cls");
				cout << "Successfully Logged In!" << endl;
				return CurrentEmployee;
			}
			else
			{
				cout << "The password you entered is Invalid, Please try again!" << endl;
				userFlag = false;
				attempt++;
				cout << "Enter Your Password: \t";
				cin >> temp;
				password = Helper::GetStringFromBuffer(temp);
				comparePass = CurrentEmployee->getEmployeePass();
			}
		}
		cout << "You acount has been temporarily disabled. Log In again" << endl << endl;
		return 0;
	}
	else
	{
		cout << "You acount has been temporarily disabled. Log In again" << endl << endl;
		return 0;
	}
}

// writing into Customers File with updated version of customers list
void LESCO::updateCustomerInfo()
{
	ofstream fout("CustomerInfo.txt");

	for (int i = 0; i < totalCustomers; i++)
	{
		customerList[i]->updateCustomerFile(fout);

		if (i != totalCustomers - 1)
			fout << endl;
	}
}

// Billing Information is loaded from Billing File
void LESCO::loadBillingInfo()
{
	ifstream fin("BillingInfo.txt");

	if (fin.is_open())
	{
		char* billerID;
		billingList = new Billing * [totalCustomers + 5];

		for (int i = 0; i < totalCustomers; i++)
		{
			char tempID[10];

			fin.get(tempID, 1000, ',');

			billerID = Helper::GetStringFromBuffer(tempID);

			char* customerID = customerList[i]->getCustomerID();

			if (Helper::SearchString(billerID, customerID))
			{
				char* meterType = customerList[i]->getMeterType();

				if (meterType[0] == '1')
				{
					billingList[i] = new Billing();
				}
				if (meterType[0] == '3')
				{
					billingList[i] = new phase3Meter();
				}
				fin.ignore();
				billingList[i]->loadBillingInfoFromFile(fin, billerID);
			}
			fin.ignore();

		}
	}
}

// LESCO can register new Customers at run time
void LESCO::registerCustomer()
{
	CurrentEmployee->addNewCustomer(customerList, billingList, totalCustomers);
	updateCustomerInfo();
	updateBillingInfo();
}

// Option to view Customers Information by taking customer ID
void LESCO::ViewCustomerInfo()
{

	cout << "--------------------------------------------------------" << endl;
	for (int i = 0; i < totalCustomers; i++)
	{
		cout << i + 1 << ". " << "Customer ID: " << customerList[i]->getCustomerID();
		cout << endl;
	}
	cout << "--------------------------------------------------------" << endl;
	char customerid[10];
	cout << "Enter the customer ID to view their Bill Information: " << endl;

	cin >> customerid;

	for (int i = 0; i < totalCustomers; i++)
	{
		char* temp = customerList[i]->getCustomerID();

		if (Helper::SearchString(temp, customerid))
		{
			customerList[i]->PrintCustomer();
		}
	}
}

// The employee has an option of changing passwords
void LESCO::changeEmployeePassword()
{
	CurrentEmployee->updatePassword();
	saveUpdatedEmployeeList();
}

// in case of change of employee password, or an update , employee file is updated
void LESCO::saveUpdatedEmployeeList()
{
	ofstream fout("EmployeesData.txt");

	for (int i = 0; i < totalEmployee; i++)
	{
		fout << employeeList[i]->getEmployeeID();

		fout << ", ";

		fout << employeeList[i]->getEmployeePass();
		if (i != totalEmployee - 1)
			fout << endl;
	}

}

LESCO::~LESCO()
{
	
	destructList<Customer>(customerList, totalCustomers);
	destructList<Employee>(employeeList, totalEmployee);
	destructList<Billing>(billingList, totalCustomers);

	if(CurrentEmployee)
		CurrentEmployee = NULL;
	if(CurrentCustomer)
		CurrentCustomer = NULL;
	if(CustomerLogin)
		CustomerLogin = NULL;
}

// Customer's initial login system using ID and birthday as a password
Customer* LESCO::CustomerMainLogin()
{
	bool flag = false;
	int attempt = 0;
	char tempBuffer[50];
	cout << "Enter Customer ID :  ";
	cin >> tempBuffer;
	char* userName = Helper::GetStringFromBuffer(tempBuffer);

	while (flag == false && attempt < 3)
	{
		if (searchCustomerID(userName))
		{
			flag = true;
			CurrentCustomer = searchCustomerID(userName);
			attempt += 3;
		}
		else
		{
			system("cls");
			cout << "No such customer is registered with the ID \"" << userName << "\" Please try again!" << endl;
			flag = false;
			cout << "Enter Customer ID: \t";
			cin >> tempBuffer;
			userName = Helper::GetStringFromBuffer(tempBuffer);
		}
		attempt++;
	}
	attempt = 0;
	int password;
	if (flag == true)
	{
		
		flag = false;

		

		while (!flag && attempt < 4)
		{
			cout << "Enter Your Password: \t";
			cin >> password;
	
			if (password == CurrentCustomer->Customer::getCustomerDOB())
			{
				flag = true;
				system("cls");
				cout << "Successfully Logged In!" << endl;
				return CurrentCustomer;
			}
			else
			{
				cout << "The password you entered is Invalid, Please try again!" << endl;
				attempt++;
			}
		}
		cout << "You are left with no more attempts. Log In again" << endl << endl;
		return false;
	}
	else
	{
		cout << "You acount has been temporarily disabled. Log In again" << endl << endl;
		return 0;
	}
}

// For a Customer to view their bill, they need to provide meter credentials
Customer* LESCO::CustomerViewBillLogin()
{
	bool flag = false;
	int attempt = 0;
	char tempBuffer[50];
	double currentMeter_Reading;
	double enteredMeter_Reading;

	for (int i = 0; i < totalCustomers; i++)
	{
		if (Helper::SearchString(billingList[i]->getBillerID(), CurrentCustomer->getCustomerID()))
			currentMeter_Reading = billingList[i]->getCurrentMeterReading();
	}

	while (attempt < 4)
	{
		cout << "Enter Meter Type (1Phase or 3Phase) :  ";
		cin >> tempBuffer;

		if (*tempBuffer == *CurrentCustomer->getMeterType())
		{
			cout << "Enter the current meter reading : ";
			cin >> enteredMeter_Reading;

			if (enteredMeter_Reading == currentMeter_Reading)
			{
				cout << endl << endl << "Your current bill is displaying now : " << endl << endl;
				return CurrentCustomer;
			}
			else
			{
				cout << endl << endl << "You have entered wrong current reading. Try again" << endl;
				return 0;
			}
		}
		else
		{
			cout << "You have entered the wrong phase. Try again" << endl << endl;
			attempt++;
		}
	}
	cout << "You do not have any more attempts. Log In again" << endl;
	return 0;
}

// LESCO is responsible for printing the current bill generated for a particular customer
void LESCO::ViewCurrentBill()
{
	cout << "___________________________" << endl << endl;
	cout << "                           Electricity Bill                                      " << endl << endl;
	cout << "___________________________" << endl << endl;

	cout << "Bill Status  : " << CurrentCustomer->getBillStatus() << endl << endl;
	cout << "___________________________" << endl << endl;

	cout << "Customer Name  : " << CurrentCustomer->getCustomerName() << "       ";
	cout << "Customer ID    : " << CurrentCustomer->getCustomerID() << endl << endl;
	cout << "___________________________" << endl << endl;

	cout << "Customer's date of birth : " << CurrentCustomer->getCustomerDOB() << endl << endl;
	cout << "Customer's Address       : " << CurrentCustomer->getCustomerAddress() << endl << endl;
	cout << "Customer's phone number  : " << CurrentCustomer->getCustomerPhone() << endl << endl;
	cout << "___________________________" << endl << endl;

	cout << "Customer's meter type    : " << CurrentCustomer->getMeterType() << endl << endl;
	cout << "Customer Type            : " << CurrentCustomer->getCustomerType() << endl << endl;
	cout << "___________________________" << endl << endl;

	cout << "Regular units            : " << CurrentCustomer->getRegularUnits() << endl << endl;
	cout << "Peak units               : " << CurrentCustomer->getPeakUnits() << endl << endl;

	for (int i = 0; i < totalCustomers; i++)
	{
		if (Helper::SearchString(billingList[i]->getBillerID(), CurrentCustomer->getCustomerID()))
		{
			cout << "Electricity cost         : " << billingList[i]->getElectricityCost() << endl << endl;
			cout << "Sales Tax Amount         : " << billingList[i]->getSalesTaxAmount() << endl << endl;
			cout << "Fixed Charges            : " << billingList[i]->getFixedCharges() << endl << endl;
			cout << "___________________________" << endl << endl;
			cout << "Due Bill Amount          : " << billingList[i]->getTotalBill() << endl << endl;
			cout << "___________________________" << endl << endl;
			cout << "Due Date                 : " << billingList[i]->getDueDate() << endl << endl;
			break;
		}
	}
}

void main()
{
	LESCO Obj;                                                                  // initalization of Lesco's object that will carry out all functions

	Obj.loadDataFromFile();
	Obj.loadBillingInfo();

	Obj.calculateTotalBills();

	Obj.AssociateBills();

	bool flag = false;

	int userType = 0;
line:	Sleep(200); cout << "\t\t\t L";
		Sleep(200); cout << "E";
		Sleep(200); cout << "S";
		Sleep(200); cout << "C";
		Sleep(200); cout << "O" << endl << endl;
	while (!flag) // user interface for both employees and customers
	{
		
		cout << "\t  Login As " << endl;
		cout << "1. Employee         2. Customer" << endl;
		switch (getch())
		{
		case '1':
			userType = 1;
			flag = true;
			break;
		case '2':
			userType = 2;
			flag = true;
			break;
		default:
			cout << "Invalid input. Enter again." << endl << endl;
			break;
		}
	}
	if (userType == 1)
	{
		system("cls");
		cout << "\t\t\t\t\t Enter your credentials " << endl << endl;

		if (Obj.employeeLogin())
		{
			flag = false;
			while (!flag)
			{

				cout << "\nLogged in as: " << Obj.getCurrentEmployee();
				cout << endl << endl;

				cout << "Main Menu: " << endl;
				cout << "1. Register a New Customer\n2. Change Bill Status\n3. View Customer Info\n4. Update Tarrif Tax Info\n5. Get Bills Report\n6. Update Your Password\n7. Log Out" << endl;
				switch (getch())
				{
				case '1':
					system("cls");
					Obj.registerCustomer();
					cout << "Customer Registered Successfully!" << endl;
					break;

				case '2':
					system("cls");
					Obj.setBillStatus();
					break;

				case '3':
					system("cls");
					cout << "\t\t\t\t\t Customer Data " << endl << endl;
					Obj.ViewCustomerInfo();
					break;

				case '4':
					system("cls");
					Obj.updateTarrifFile();
					break;

				case '5':
					system("cls");
					Obj.getBillsReport();
					break;

				case '6':
					system("cls");
					Obj.changeEmployeePassword();
					break;

				case '7':
					system("cls");
					flag = false;
					goto line;
					break;

				default:
					cout << "Invalid input. Enter again." << endl << endl;
					break;
				}
			}
		}
	}

	if (userType == 2)
	{
		system("cls");
		cout << "\t\t\t\t\t Enter your credentials " << endl << endl;

		if (Obj.CustomerMainLogin())
		{
			flag = false;
			while (!flag)
			{

				cout << "\nLogged in as: " << Obj.getCurrentCustomer();

				cout << endl << endl;
				cout << "Main Menu: " << endl;

				cout << "1. View Bill\n2. Log Out" << endl;
				switch (getch())
				{
				case '1':
					system("cls");
					if (Obj.CustomerViewBillLogin())
					{
						Obj.ViewCurrentBill();
						cout << "Customer Bill Loaded Successfully!" << endl;
					}
					break;

				case '2':
					system("cls");
					flag = false;
					goto line;
				}
			}
		}
	}
	system("pause");

}

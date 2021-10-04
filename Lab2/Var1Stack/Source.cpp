#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

class Date {
public:
	Date() {
		Date(1, 1, 1);
	}
	Date(const int& day, const int& month, const int& year) {
		this->setDay(day);
		this->setMonth(month);
		this->setYear(year);
	}
	void setYear(int year) {
		this->year = year;
	}
	void setMonth(int month) {
		this->month = month;
	}
	void setDay(int day) {
		this->day = day;
	}
	int getYear() const {
		return this->year;
	}
	int getMonth() const {
		return this->month;
	}
	int getDay() const {
		return this->day;
	}
private:
	int day;
	int month;
	int year;
};

bool operator<(const Date& ld, const Date& rd) {
	if (ld.getYear() != rd.getYear()) {
		return (ld.getYear() < rd.getYear());
	}
	else if (ld.getMonth() != rd.getMonth()) {
		return (ld.getMonth() < rd.getMonth());
	}
	return (ld.getDay() < rd.getDay());
}

bool operator==(const Date& ld, const Date& rd) {
	return (ld.getYear() == rd.getYear() && ld.getMonth() == rd.getMonth() && ld.getDay() == rd.getDay());
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(2) << setfill('0') << date.getDay() << "\\";
	stream << setw(2) << setfill('0') << date.getMonth() << "\\";
	stream << setw(4) << setfill('0') << date.getYear();
	return stream;
}

struct Record {
public:
	Record(Date date, string record) {
		this->date = date;
		this->record = record;
	}
	Date date;
	string record;
};

ostream& operator<<(ostream& stream, const Record& record) {
	stream << record.date << "\t" << record.record;
	return stream;
}

void ReadDataOrCreate(stack <Record>& st) {
	ifstream input("data.txt");
	string day, month, year, record;
	if (!input.is_open()) {
		ofstream("data.txt");
		cout << "File created" << endl;
	}
	cout << "File is open to reading!" << endl;
	while (input) {
		getline(input, day, '\\');
		getline(input, month, '\\');
		getline(input, year, '\t');
		Date newDate(stoi(day), stoi(month), stoi(year));
		getline(input, record);
		Record newRecord(newDate, record);
		st.push(newRecord);
	}
}

int main() {
	stack <Record> allRecords;
	ReadDataOrCreate(allRecords);
	bool exit = false;
	while (!exit) {
		string command;
		cout << "What you want to do: " << endl;
		cout << "\"Create new record\" is command - \"--c\"" << endl;
		cout << "\"Delete last record\" is command - \"--d\"" << endl;
		cout << "\"Show head record\" is command - \"--s\"" << endl;
		cout << "\"Exit\" is command - \"--q\"" << endl;
		cin >> command;
		if (command == "--c") {
			bool next = true;
			string note;
			int day = 0, month = 0, year = 0;
			while (next) {
				cout << "Enter date in format \"day*month*year\"(where \"*\" is any character like \"/ or | or # etc...\"):  " << endl;
				cin >> day; cin.ignore(1);cin >> month; cin.ignore(1);cin >> year; cin.ignore(1);
				if (day > 31 || day < 1 || month>12 || month < 1 || year < 0) {
					next = true;
					cout << "Please enter correct date!" << endl;
				}
				else {
					next = false;
				}
			}
			Date newDate(day,month,year);
			cout << "Your date is: " << newDate << endl;
			cout << "Now enter your record: " << endl;
			getline(cin, note);
			Record newRecord(newDate, note);
			allRecords.push(newRecord);
		}
		else if (command == "--d") {
			allRecords.pop();
		}
		else if (command == "--s") {
			if (!allRecords.empty()) {
				cout << allRecords.top() << endl;
			}
			else {
				cout << "No records" << endl;
			}
		}
		else if (command == "--q") {
			exit = true;
		}
		else {
			cout << "You entered the wrong command, please try again." << endl;
		}
	}
	return 0;
}
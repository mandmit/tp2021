#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <vector>

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

class Record {
public:
	Record(const Date& date,const string& record) {
		this->date = date;
		this->record = record;
	}
	Date getDate() const {
		return this->date;
	}
	string getRecord() const {
		return this->record;
	}
	void setDate(const Date& date) {
		this->date = date;
	}
	void setRecord(const string& record) {
		this->record = record;
	}
private:
	Date date;
	string record;
};

void CreateNewRecord(stack <Record>& allRecords, vector <Record>& allRecordsToWrite) {
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
	Date newDate(day, month, year);
	cout << "Your date is: " << newDate << endl;
	cout << "Now enter your record: " << endl;
	getline(cin, note);
	Record newRecord(newDate, note);
	allRecords.push(newRecord);
	allRecordsToWrite.push_back(newRecord);
}

ostream& operator<<(ostream& stream, const Record& record) {
	stream << record.getDate() << "\t" << record.getRecord();
	return stream;
}

bool operator<(const Record& lr, const Record& rr) {
	return (lr.getDate() < rr.getDate());
}

void ShowTopRecord(stack <Record> allRecords) {
	if (!allRecords.empty()) {
		cout << allRecords.top() << endl;
	}
	else {
		cout << "No records on this moment" << endl;
	}
}
void PrintAllRecords(const vector <Record>& allRecords) {
	for (auto el : allRecords) {
		cout << el << endl;
	}
}
void DeleteTopRecord(stack <Record>& allRecords, vector <Record>& allRecordsToWrite) {
	allRecords.pop();
	allRecordsToWrite.pop_back();
}

void ReadDataOrCreate(stack <Record>& st, vector <Record>& v) {
	ifstream input("data.txt");
	string day, month, year, record;
	int dayInt = 0, monthInt = 0, yearInt = 0;
	if (!input.is_open()) {
		ofstream("data.txt");
		cout << "File created" << endl;
	}
	else {
		cout << "File is open to reading!" << endl;
		if (isalnum(input.peek())) {
			while (!input.eof()) {
				getline(input, day, '\\');
				getline(input, month, '\\');
				getline(input, year, '\t');
				dayInt = stoi(day);
				monthInt = stoi(month);
				yearInt = stoi(year);
				Date newDate(dayInt, monthInt, yearInt);
				getline(input, record);
				Record newRecord(newDate, record);
				st.push(newRecord);
				v.push_back(newRecord);
			}
		}
	}
	input.close();
}

void RewriteDataInTheFile(const vector <Record>& v) {
	ofstream output("data.txt");
	for (int i = 0; i < v.size(); i++) {
		if (i == v.size() - 1) {
			output << v[i];
		}
		else {
			output << v[i] << endl;
		}
	}
	output.close();
}

int main() {
	stack <Record> allRecords;
	vector <Record> allRecordsToWrite;
	ReadDataOrCreate(allRecords, allRecordsToWrite);
	bool exit = false;
	while (!exit) {
		string command;
		cout << "What you want to do: " << endl;
		cout << "\"Create new record\" is command - \"--c\"" << endl;
		cout << "\"Delete last record\" is command - \"--d\"" << endl;
		cout << "\"Show head record\" is command - \"--s\"" << endl;
		cout << "\"Show all records\" is command - \"--p\"" << endl;
		cout << "\"Exit\" is command - \"--q\"" << endl;
		cin >> command;
		if (command == "--c") {
			CreateNewRecord(allRecords, allRecordsToWrite);
		}
		else if (command == "--d") {
			DeleteTopRecord(allRecords, allRecordsToWrite);
		}
		else if (command == "--s") {
			ShowTopRecord(allRecords);
		}
		else if (command == "--p") {
			PrintAllRecords(allRecordsToWrite);
		}
		else if (command == "--q") {
			exit = true;
			sort(begin(allRecordsToWrite), end(allRecordsToWrite));
			RewriteDataInTheFile(allRecordsToWrite);
			cout << "Your records has been rewrited!" << endl;
		}
		else {
			cout << "You entered the wrong command, please try again." << endl;
		}
	}
	return 0;
}
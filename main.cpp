/*
* ev176P3.cpp
*
* COSC 051 Fall 2015
* Project #3
*
* Due on: NOV 9, 2015
* Author: Erik Van de Water
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

// -- PREPROCESSING --

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

// -- GLOBAL CONSTANTS

const string MESSAGE_GOODBYE = "Thank you for using the ASF System. ";
const string PROMPT_INPUT_FILE = "Please enter complete path and name of input data file: ";
const int SPACER = 10;
const string MESSAGE_WELCOME = "Welcome to Appalachian Shape Fabricators.";
const string MESSAGE_INFO1 = "This app calculates surface area, volume, cost, \n";
const string MESSAGE_INFO2 = "and sales values based upon sales file data entries.";

// -- FUNCTION PROTOTYPES

char displayMenu();
void uploadFile(string fName, bool &loadSuccess, vector<string> &reg, vector<char> &sCode,
                vector<char> &mCode, vector<double> &r, vector<double> &h,
                vector<string> &c, vector<string> &custNum);
void allDetails(const vector<string> &reg, const vector<char> &sCode,
                const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                const vector<string> &c, const vector<string> &custNum);
void customerDetails(const vector<string> &reg, const vector<char> &sCode,
                    const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                    const vector<string> &c, const vector<string> &custNum);
void summaryByShape(const vector<string> &reg, const vector<char> &sCode,
                    const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                    const vector<string> &c, const vector<string> &custNum);
void summaryByRegion(const vector<string> &reg, const vector<char> &sCode,
                     const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                     const vector<string> &c, const vector<string> &custNum);
bool clearAllVectors(vector<string> &reg, vector<char> &sCode, vector<char> &mCode,
                     vector<double> &r, vector<double> &h,
                     vector<string> &c, vector<string> &custNum);

// -- MAIN FUNCTION --

int main(){
    // -- VARIABLES --

    // strings
    string fName =           "";

    // chars

    char choice;

    // bools

    bool loadSuccess = false;
    bool clearBool = false;

    // vectors

    vector<string> reg;
    vector<char> sCode;
    vector<char> mCode;
    vector<double> r;
    vector<double> h;
    vector<string> c;
    vector<string> custNum;

    // -- OUTPUT GREETING --

    cout << "\n\n";
    cout << MESSAGE_WELCOME << endl;
    cout << MESSAGE_INFO1;
    cout << MESSAGE_INFO2;
    cout << "\n\n";

    // -- USER CHOICE OF OPTIONS --

    do {
        choice = displayMenu();
        if (choice == 'U' || choice == 'u') {
            cout << PROMPT_INPUT_FILE << endl;

            getline(cin, fName);

            uploadFile(fName, loadSuccess, reg, sCode, mCode, r, h, c, custNum);
        }
        else if (choice == 'A' || choice == 'a') {
            if (loadSuccess == true) {
                allDetails(reg, sCode, mCode, r, h, c, custNum);
            }
            else {
                cout << "Please enter at least one data file before attempting" <<
                        "to display data" << endl;
                displayMenu();
            }
        }
        else if (choice == 'I' || choice == 'i') {
            if (loadSuccess == true) {
                customerDetails(reg, sCode  , mCode, r, h, c, custNum);
            }
            else {
                displayMenu();
            }
        }
        else if (choice == 'R' || choice == 'r') {
            if (loadSuccess == true) {
                summaryByRegion(reg, sCode, mCode, r, h, c, custNum);
            }
            else {
                displayMenu();
            }
        }
        else if (choice == 'S' || choice == 's') {
            if (loadSuccess == true) {
                summaryByShape(reg, sCode, mCode, r, h, c, custNum);
            }
            else {
                displayMenu();
            }
        }
        else if (choice == 'C' || choice == 'c') {
            clearBool = clearAllVectors(reg, sCode, mCode, r, h, c, custNum);
            if (clearBool) {
                cout << "Successfully cleared data." << endl;
                loadSuccess = false;
            }
        }
        else {
            cout << "Invalid option.  Please try again.";
        }
    } while (choice != 'Q' && choice != 'q');
    cout << MESSAGE_GOODBYE << endl;
    return 0;
}
// -- FUNCTION DECLARATIONS --
char displayMenu() {

    // -- CONSTANTS --

    const string UPLOAD = "Upload a regional sales data file";
    const string DETAILS = "Display details (all loaded data)";
    const string ID = "List sales for particular customer ID";
    const string REGION = "Display summary by region";
    const string SHAPE = "Display summary by shape code";
    const string CLEAR = "Clear all vectors";

    const int MENU = 45;
    const int CHAR = 6;

    // -- MENU OUTPUT --

    // option descriptions

    cout << setw(MENU) << UPLOAD;
    cout << setw(CHAR) << "U" << endl;
    cout << setw(MENU) << DETAILS;
    cout << setw(CHAR) << "A" << endl;
    cout << setw(MENU) << ID;
    cout << setw(CHAR) << "I" << endl;
    cout << setw(MENU) << REGION;
    cout << setw(CHAR) << "R" << endl;
    cout << setw(MENU) << SHAPE;
    cout << setw(CHAR) << "S" << endl;
    cout << setw(MENU) << CLEAR;
    cout << setw(CHAR) << "C" << endl;
    cout << setw(MENU) << "Quit";
    cout << setw(CHAR) << "Q" << endl;

    cout << "Please enter your choice: ";
    // -- CHOICE INPUT --
    char choice;
    cin >> choice;
    cin.ignore(500,'\n');
    return choice;
}
void uploadFile(string fName, bool &loadSuccess, vector<string> &reg, vector<char> &sCode,
                vector<char> &mCode, vector<double> &r, vector<double> &h,
                vector<string> &c, vector<string> &custNum) {

    const string MESSAGE_ERROR_FILE_OPEN = "The input file failed to open.";

    // -- VARIABLES --

    // -- numbers --

    // ints

    int fileYear =        0;
    int fileMonth =       0;
    int fileDay =         0;

    int orderYear =       0;
    int orderMonth =      0;
    int orderDay =        0;

    int currentRow =      0;
    int numErrors =       0;

    int numErrorsBefore = 0;

    int totalRecords =    0;
    int totalRecordsL =   reg.size();
    int recordsAdded =    0;
    int rowsCorrect =     0;
    int rowsIncorrect =   0;

    // doubles

    double radius =       0.0;
    double height =       0.0;

    // -- others --

    // strings

    string line = "----------------------------------------------------------------------------------------";
    string oneRow =          "";
    string headers =         "";
    string newLineAfterDate = "";

    string state =           "";
    string region =          "";
    string orderDate =       "";
    string color =           "";
    string customerNumber =  "";
    string firstName =       "";
    string lastName =        "";
    string address =         "";

    // chars

    char shapeCode =       'a';
    char materialCode =    'a';
    char dateDelimiter =    '/';

    // ifstream

    ifstream  inFileStream; //no initial value

    // -- INPUT FILE --

    inFileStream.open(fName.c_str());

    // -- TEST IF FILE IS VALID --

    if (!inFileStream) {
        cout << MESSAGE_ERROR_FILE_OPEN << endl;
        cout << "check to ensure the file: " << fName << " is valid.\n";
    }
    else {
        cout << fName << "successfully opened for reading.\n";

        // -- file date checking for line 1--

        inFileStream >> fileYear >> dateDelimiter >> fileMonth >> dateDelimiter >> fileDay;
        if (fileYear < 1000 || fileYear > 9999 || fileMonth > 12
           || fileMonth < 1 || fileDay > 31 || fileDay < 1) {
            cout << "ERROR BELOW: Typo in file date";
        }
        getline(inFileStream, newLineAfterDate); // handle newline character

        // -- handling headers --

        getline(inFileStream, headers); // used to store the value of the unused headers of the file

        // -- outputting headers --

        cout << "Region" << setw(6) << "Date" << setw(11) << "Codes" << setw(15) << "Dimensions"
        << setw(8) << "Color" << setw(15) << "Cust. Num." << endl;
        cout << line << endl;

        // -- input values --

        currentRow = 1;

        while (inFileStream >> state >> region >> orderYear >> dateDelimiter >>
               orderMonth >> dateDelimiter >> orderDay >> shapeCode
               >> materialCode >> radius >> height >> color >> customerNumber >>
               firstName >> lastName && getline(inFileStream, address)) {

            // -- validations --

            // orderDate

            if (orderYear < 1000 || orderYear > 9999 || orderMonth > 12
               || orderMonth < 1 || orderDay > 31 || orderDay < 1) {
                cout << "ERROR BELOW: Typo in order date" << endl;
                numErrors++;
            }
            if (orderYear > fileYear) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth > fileMonth) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }
            else if (orderYear == fileYear && orderMonth == fileMonth && orderDay > fileDay) {
                cout << "ERROR BELOW: order date is after file date" << endl;
                numErrors++;
            }

            // shapeCode

            if ((shapeCode != 'o') && (shapeCode != 'y') && (shapeCode != 'p')
                && (shapeCode != 'O') && (shapeCode != 'Y') && (shapeCode != 'P')) {
                cout << "ERROR BELOW: Not a legitimate shape." << endl;
                numErrors++;
            }

            // materialCode

            if ((materialCode != 'k') && (materialCode != 'a') && (materialCode != 'u')
              && (materialCode != 'K') && (materialCode != 'A') && (materialCode != 'U')) {
                cout << "ERROR BELOW: Not a legitimate material." << endl;
                numErrors++;
            }

            // radius

            if ((radius < 3) || (radius > 36)) {
                cout << "ERROR BELOW: The radius entered is outside of limits" << endl;
                numErrors++;
            }

            // height

            if ((shapeCode == 'o') || (shapeCode == 'y') || shapeCode == 'O' || shapeCode == 'Y'){
                if ((height < radius)  || (height > radius * 1.5)){
                  cout << "ERROR BELOW: The height entered is outside of limits" << endl;
                  numErrors++;
                }
            }

            // color

            if (!(color == "Red" || color == "Orange" || color == "Yellow" ||
                        color == "Green" || color == "Blue" ||
                        color == "Indigo" || color == "Violet")) {
                cout << "ERROR BELOW: invalid color." << endl;
                numErrors++;
            }

            // -- output non-calculated values --

            cout << setprecision(2) << fixed << setw(6) << region << setw(5)
            << orderYear << dateDelimiter << setw(2)
            << orderMonth << dateDelimiter << setw(2) << orderDay <<
            setw(3) << shapeCode << setw(3) << materialCode << setw(7) << radius;
            if (height == -1) {
                cout << setw(7) << "n/a" << setw(SPACER) << color <<
                setw(17) << customerNumber;
            }
            else {
                cout << setprecision(2) << fixed << setw(7) <<
                height << setw(SPACER) << color << setw(17) << customerNumber;
            }
            cout << endl;

            // -- CHECK IF ROW IS CORRECT --

            if (numErrorsBefore < numErrors) {
                rowsIncorrect++;
            }
            else {
                rowsCorrect++;

                // -- APPEND TO VECTORS --
                loadSuccess = true;

                reg.push_back(region);
                sCode.push_back(shapeCode);
                mCode.push_back(materialCode);
                r.push_back(radius);
                h.push_back(height);
                c.push_back(color);
                custNum.push_back(customerNumber);
            }
            numErrorsBefore = numErrors;
        }
        currentRow++;
        numErrors = 0;
    }
    recordsAdded = rowsCorrect;
    totalRecords = rowsCorrect + rowsIncorrect;
    totalRecordsL = totalRecordsL + rowsCorrect;

    cout << "Counts: Total Records = " << totalRecords << "   Records with Errors = "
         << rowsIncorrect << "   Records without Errors = " << rowsCorrect << endl;
    cout << totalRecordsL << " records now loaded, " << recordsAdded <<
         " added to vectors." << endl;

    inFileStream.close();
}
void allDetails(const vector<string> &reg, const vector<char> &sCode,
                const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                const vector<string> &c, const vector<string> &custNum) {
    // -- VARIABLES --

    // ints

    int times = reg.size() - 1;

    // doubles

    double slantHeight =     0.0;
    double surfaceArea =     0.0;
    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;
    double price =           0.0;
    double profit =          0.0;

    // strings

    string line = "----------------------------------------------------------------------------------------";

    // -- outputting headers --

    cout << "Region" << setw(11) << "Codes" << setw(15) << "Dimensions"
    << setw(8) << "Color" << setw(14) << "Cust. Num" << setw(8) << "Cost" << setw(12)
    << "Price" <<  setw(10) << "Profit" << endl;
    cout << line << endl;

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {
        // -- output non-calculated values --

        cout << setprecision(2) << fixed << setw(5) << reg[iterator] << setw(6) <<
        sCode[iterator] << setw(3) << mCode[iterator] << setw(10) << r[iterator];
        if (h[iterator] == -1) {
            cout << setw(7) << "n/a";
        }
        else {
            cout << setprecision(2) << fixed << setw(7) << h[iterator];
        }
        cout << setw(SPACER) << c[iterator];

        if (sCode[iterator] == 'o' || sCode[iterator] == 'O') {
            slantHeight = sqrt(pow(r[iterator],2)+pow(h[iterator],2));
            surfaceArea = 3.14*pow(r[iterator],2) + 3.14*r[iterator]*slantHeight;
        }
        else if (sCode[iterator] == 'y' || sCode[iterator] == 'Y'){
            surfaceArea = 2*3.14*r[iterator]*(h[iterator] + r[iterator]);
        }
        else {
            surfaceArea = 4*3.14*pow(r[iterator],2);
        }

        //cost calculations

        if (mCode[iterator] == 'k' || mCode[iterator] == 'K') {
            materialCost = 1.26 * surfaceArea;
            laborCost = 256.27 + (0.4 * materialCost);
        }
        else if (mCode[iterator] == 'a' || mCode[iterator] == 'A') {
            materialCost = 0.49 * surfaceArea;
            laborCost = 32.10 + (0.1 * materialCost);
        }
        else {
            materialCost = 6.32 * surfaceArea;
            laborCost = 785.16 + (0.8 * materialCost);
        }

        // -- individual costs --

        // row output calculation variables

        cost = materialCost + laborCost;
        price = cost * 1.25;
        profit = price - cost;

        // -- calculated row outputs --

        cout << setprecision(2) << fixed << setw(13) << custNum[iterator] << setw(11)
        << cost << setw(11) << price << setw(11) << profit << endl;
    }
}
void customerDetails(const vector<string> &reg, const vector<char> &sCode,
                    const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                    const vector<string> &c, const vector<string> &custNum) {
    // -- VARIABLES --

    // ints
    vector<int> locationV;
    int times = custNum.size() - 1;
    int location = 0;
    // doubles

    double slantHeight =     0.0;
    double surfaceArea =     0.0;
    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;
    double price =           0.0;
    double profit =          0.0;

    // strings

    string line = "----------------------------------------------------------------------------------------";
    string customerNumber = "";

    // bools

    bool found = false;

    // -- PROMPT FOR INPUT --

    cout << "\n\n";
    cout << "Enter a customer ID: ";
    cin >> customerNumber;
    cin.ignore(500, '\n');

    for(int iterator = 0; iterator <= times; iterator++) {
        if (custNum[iterator] == customerNumber) {
            found = true;
            locationV.push_back(iterator);
        }
    }

    times = locationV.size() - 1;

    if (found == true) {
        for (int iterator = 0; iterator <= times; iterator++) {
            location = locationV[iterator];
            // -- outputting headers --

            cout << "Region" << setw(11) << "Codes" << setw(15) << "Dimensions"
            << setw(8) << "Color" << setw(14) << "Cust. Num" << setw(8) << "Cost" << setw(12)
            << "Price" <<  setw(10) << "Profit" << endl;
            cout << line << endl;

            // -- output non-calculated values --

            cout << setprecision(2) << fixed << setw(5) << reg[location] << setw(6) <<
            sCode[location] << setw(3) << mCode[location] << setw(10) << r[location];
            if (h[location] == -1) {
                cout << setw(7) << "n/a";
            }
            else {
                cout << setprecision(2) << fixed << setw(7) << h[location];
            }
            cout << setw(SPACER) << c[location];

            if (sCode[location] == 'o' || sCode[location] == 'O') {
                slantHeight = sqrt(pow(r[location],2)+pow(h[location],2));
                surfaceArea = 3.14*pow(r[location],2) + 3.14*r[location]*slantHeight;
            }
            else if (sCode[location] == 'y' || sCode[location] == 'Y'){
                surfaceArea = 2*3.14*r[location]*(h[location] + r[location]);
            }
            else {
                surfaceArea = 4*3.14*pow(r[location],2);
            }

            //cost calculations

            if (mCode[location] == 'k' || mCode[location] == 'K') {
                materialCost = 1.26 * surfaceArea;
                laborCost = 256.27 + (0.4 * materialCost);
            }
            else if (mCode[location] == 'a' || mCode[location] == 'A') {
                materialCost = 0.49 * surfaceArea;
                laborCost = 32.10 + (0.1 * materialCost);
            }
            else {
                materialCost = 6.32 * surfaceArea;
                laborCost = 785.16 + (0.8 * materialCost);
            }

            // -- individual costs --

            // row output calculation variables

            cost = materialCost + laborCost;
            price = cost * 1.25;
            profit = price - cost;

            // -- calculated row outputs --

            cout << setprecision(2) << fixed << setw(13) << custNum[location] << setw(11)
            << cost << setw(11) << price << setw(11) << profit << endl;
        }
    }
    else { cout << "      Customer number " << customerNumber << " not found."<< endl; }



}
void summaryByShape(const vector<string> &reg, const vector<char> &sCode,
                    const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                    const vector<string> &c, const vector<string> &custNum) {
    // -- VARIABLES --

    // ints

    int times = reg.size() - 1;

    int coneNumber =      0;
    int cylinderNumber =  0;
    int sphereNumber =    0;

    // doubles

    double slantHeight =     0.0;
    double surfaceArea =     0.0;
    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;
    double price =           0.0;
    double profit =          0.0;

    double coneCost =        0.0;
    double conePrice =       0.0;
    double coneProfit =      0.0;

    double cylinderCost =    0.0;
    double cylinderPrice =   0.0;
    double cylinderProfit =  0.0;


    double sphereCost =      0.0;
    double spherePrice =     0.0;
    double sphereProfit =    0.0;

    double totalNumber =     0.0;
    double totalCost =       0.0;
    double totalPrice =      0.0;
    double totalProfit =     0.0;
    double averageNumber =   0.0;
    double averageCost =     0.0;
    double averagePrice =    0.0;
    double averageProfit =   0.0;

    // strings

    string line = "----------------------------------------------------------------------------------------";

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {

        if (sCode[iterator] == 'o' || sCode[iterator] == 'O') {
            slantHeight = sqrt(pow(r[iterator],2)+pow(h[iterator],2));
            surfaceArea = 3.14*pow(r[iterator],2) + 3.14*r[iterator]*slantHeight;
        }
        else if (sCode[iterator] == 'y' || sCode[iterator] == 'Y'){
            surfaceArea = 2*3.14*r[iterator]*(h[iterator] + r[iterator]);
        }
        else {
            surfaceArea = 4*3.14*pow(r[iterator],2);
        }

        //cost calculations

        if (mCode[iterator] == 'k' || mCode[iterator] == 'K') {
            materialCost = 1.26 * surfaceArea;
            laborCost = 256.27 + (0.4 * materialCost);
        }
        else if (mCode[iterator] == 'a' || mCode[iterator] == 'A') {
            materialCost = 0.49 * surfaceArea;
            laborCost = 32.10 + (0.1 * materialCost);
        }
        else {
            materialCost = 6.32 * surfaceArea;
            laborCost = 785.16 + (0.8 * materialCost);
        }
        // row output calculation variables

        cost = materialCost + laborCost;
        price = cost * 1.25;
        profit = price - cost;

        // cylinder

        if (sCode[iterator] == 'y' || sCode[iterator] == 'Y') {
            cylinderNumber++;
            cylinderCost = cylinderCost + cost;
            cylinderPrice = cylinderPrice + price;
            cylinderProfit = cylinderProfit + profit;
        }

        // cone

        else if (sCode[iterator] == 'o' || sCode[iterator] == 'O') {
            coneNumber++;
            coneCost = coneCost + cost;
            conePrice = conePrice + price;
            coneProfit = coneProfit + profit;
        }

        // sphere

        else if (sCode[iterator] == 'p' || sCode[iterator] == 'P') {
            sphereNumber++;
            sphereCost = sphereCost + cost;
            spherePrice = spherePrice + price;
            sphereProfit = sphereProfit + profit;
        }

        // -- totals incrementing --

        totalNumber++;
        totalCost = totalCost + cost;
        totalPrice = totalPrice + price;
        totalProfit = totalProfit + profit;

    }

    // -- calculate averages --

    averageNumber = totalNumber / 3;
    averageCost = totalCost / 3;
    averagePrice = totalPrice / 3;
    averageProfit = totalProfit / 3;

    // -- summary outputs --

    cout << setw(50) << "Total" << endl;
    cout << setw(8) << "Shape" << setw(10) << "Number" << setw(15) << "Cost" <<
    setw(20) << "Price" << setw(20) << "Profit" << endl;

    cout << line << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cone" << setw(7) << coneNumber <<
    setw(20) << coneCost << setw(20) << conePrice << setw(20) << coneProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Cylinder" << setw(7) <<
    cylinderNumber << setw(20) << cylinderCost << setw(20) << cylinderPrice <<
    setw(20) << cylinderProfit << endl;
    cout << setprecision(2) << fixed << setw(8) << "Sphere" << setw(7) <<
    sphereNumber << setw(20) << sphereCost << setw(20) << spherePrice << setw(20) <<
    sphereProfit << endl;
    cout << line << endl;
    cout << setw(8) << "Average" << setw(7) << setprecision(0) << averageNumber <<
    setw(20) << setprecision(2) << averageCost << setw(20) << setprecision(2) <<
    averagePrice << setw(20) << setprecision(2) << averageProfit << endl;

}
void summaryByRegion(const vector<string> &reg, const vector<char> &sCode,
                     const vector<char> &mCode, const vector<double> &r, const vector<double> &h,
                     const vector<string> &c, const vector<string> &custNum) {
    // -- VARIABLES --

    // ints

    int times = reg.size() - 1;

    int northNumber =        0;
    int westNumber =         0;
    int southNumber =        0;
    int eastNumber =         0;
    int otherNumber =        0;

    // doubles

    double slantHeight =     0.0;
    double surfaceArea =     0.0;
    double materialCost =    0.0;
    double laborCost =       0.0;
    double cost =            0.0;
    double price =           0.0;
    double profit =          0.0;

    double northCost =        0.0;
    double northPrice =       0.0;
    double northProfit =      0.0;

    double westCost =    0.0;
    double westPrice =   0.0;
    double westProfit =  0.0;

    double southCost =      0.0;
    double southPrice =     0.0;
    double southProfit =    0.0;

    double eastCost =    0.0;
    double eastPrice =   0.0;
    double eastProfit =  0.0;

    double otherCost =      0.0;
    double otherPrice =     0.0;
    double otherProfit =    0.0;

    double totalNumber =     0.0;
    double totalCost =       0.0;
    double totalPrice =      0.0;
    double totalProfit =     0.0;
    double averageNumber =   0.0;
    double averageCost =     0.0;
    double averagePrice =    0.0;
    double averageProfit =   0.0;

    // strings

    string line = "----------------------------------------------------------------------------------------";

    // -- LOOP THROUGH THE VECTORS

    for (int iterator = 0; iterator <= times; iterator++) {

        if (sCode[iterator] == 'o' || sCode[iterator] == 'O') {
            slantHeight = sqrt(pow(r[iterator],2)+pow(h[iterator],2));
            surfaceArea = 3.14*pow(r[iterator],2) + 3.14*r[iterator]*slantHeight;
        }
        else if (sCode[iterator] == 'y' || sCode[iterator] == 'Y'){
            surfaceArea = 2*3.14*r[iterator]*(h[iterator] + r[iterator]);
        }
        else {
            surfaceArea = 4*3.14*pow(r[iterator],2);
        }

        //cost calculations

        if (mCode[iterator] == 'k' || mCode[iterator] == 'K') {
            materialCost = 1.26 * surfaceArea;
            laborCost = 256.27 + (0.4 * materialCost);
        }
        else if (mCode[iterator] == 'a' || mCode[iterator] == 'A') {
            materialCost = 0.49 * surfaceArea;
            laborCost = 32.10 + (0.1 * materialCost);
        }
        else {
            materialCost = 6.32 * surfaceArea;
            laborCost = 785.16 + (0.8 * materialCost);
        }
        // row output calculation variables

        cost = materialCost + laborCost;
        price = cost * 1.25;
        profit = price - cost;

        // south

        if (reg[iterator] == "South") {
            southNumber++;
            southCost = southCost + cost;
            southPrice = southPrice + price;
            southProfit = southProfit + profit;
        }

        // west

        else if (reg[iterator] == "West") {
            westNumber++;
            westCost = westCost + cost;
            westPrice = westPrice + price;
            westProfit = westProfit + profit;
        }


        // east

        else if (reg[iterator] == "East") {
            eastNumber++;
            eastCost = eastCost + cost;
            eastPrice = eastPrice + price;
            eastProfit = eastProfit + profit;
        }

        // other

        else if (reg[iterator] == "Other") {
            otherNumber++;
            otherCost = otherCost + cost;
            otherPrice = otherPrice + price;
            otherProfit = otherProfit + profit;
        }

        // north

        else if (reg[iterator] == "North") {
            northNumber++;
            northCost = northCost + cost;
            northPrice = northPrice + price;
            northProfit = northProfit + profit;
        }

        // -- totals incrementing --

        totalNumber++;
        totalCost = totalCost + cost;
        totalPrice = totalPrice + price;
        totalProfit = totalProfit + profit;

    }

    // -- calculate averages --

    averageNumber = totalNumber / 5;
    averageCost = totalCost / 5;
    averagePrice = totalPrice / 5;
    averageProfit = totalProfit / 5;

    // -- summary outputs --

    cout << setw(50) << "Total" << endl;
    cout << setw(10) << "Region" << setw(10) << "Number" << setw(15) << "Cost" <<
    setw(20) << "Price" << setw(20) << "Profit" << endl;

    cout << line << endl;

    cout << setprecision(2) << fixed << setw(8) << "North" << setw(7) << northNumber <<
    setw(20) << northCost << setw(20) << northPrice << setw(20) << northProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "West" << setw(7) << westNumber <<
    setw(20) << westCost << setw(20) << westPrice << setw(20) << westProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "South" << setw(7) << southNumber <<
    setw(20) << southCost << setw(20) << southPrice << setw(20) << southProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "East" << setw(7) << eastNumber <<
    setw(20) << eastCost << setw(20) << eastPrice << setw(20) << eastProfit << endl;

    cout << setprecision(2) << fixed << setw(8) << "Other" << setw(7) << otherNumber <<
    setw(20) << otherCost << setw(20) << otherPrice << setw(20) << otherProfit << endl;

    cout << line << endl;

    cout << setw(8) << "Average" << setw(7) << setprecision(0) << averageNumber <<
    setw(20) << setprecision(2) << averageCost << setw(20) << setprecision(2) <<
    averagePrice << setw(20) << setprecision(2) << averageProfit << endl;
}
bool clearAllVectors(vector<string> &reg, vector<char> &sCode, vector<char> &mCode,
                     vector<double> &r, vector<double> &h,
                     vector<string> &c, vector<string> &custNum) {
    reg.clear();
    sCode.clear();
    mCode.clear();
    h.clear();
    c.clear();
    custNum.clear();
    if (reg.size() == 0 && sCode.size() == 0 && mCode.size() == 0
        && h.size() == 0 && c.size() == 0 && custNum.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

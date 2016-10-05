//Programmer: Ethan Chiang
//Programmer ID: 1538719
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"

//structs
struct classCount // to keep track of subjects and sections offered
{
  string subjectCode;
  int count;
};

//prototpyes
void updateClass(DynamicArray<classCount>&, DynamicArray<string>&, const string, const string subjectCode, int&, int&, int&);

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer's ID: 1538719\n"
       << "File: " << __FILE__ << "\n\n";

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  DynamicArray<classCount> record(100); // subject count
  DynamicArray<string> readClass(100); // entered subjectCode

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if(!fin.good()) throw "I/O error";
  
  int count = 0;
  int recordIndex = 0;
  int classIndex = 0;
  int duplication = 0;

  // read the input file
  while(fin.good())
  {
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if(course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    string classCode = term + "." + section;
    updateClass(record, readClass, classCode, subjectCode, classIndex, recordIndex, duplication);

    count++;
    if(count % 1000 == 0)
    {
      cout << ". ";
      cout.flush();
    }
  }
  cout << "\nFinish!\n";
  fin.close();

  for(int i = 0; i < recordIndex; i++)
  {
    for(int j = i + 1; j < recordIndex; j++)
    {
      if(record[i].subjectCode > record[j].subjectCode)
        swap(record[i], record[j]);
    }
  }
  
  for(int i = 0; i < recordIndex; i++)
  {
    if(record[i].count != 0)
    {
      cout << record[i].subjectCode << ", "
           << record[i].count << " section\n";
    }
  }
  cout << "Total duplication: " << duplication << endl;
  return 0;
}

// functions
void updateClass(DynamicArray<classCount>& record, DynamicArray<string>& readClass, const string classCode, const string subjectCode, int& classIndex, int& recordIndex, int& duplication)
{
  bool found = false;

  // found if is a duplication
  for(int i = 0; i < classIndex; i++)
  {
    if(readClass[i] == classCode)
    {
      found = true;
      duplication++;
      break;
    }
  }

  // not a duplication
  if(!found)
  {
    readClass[classIndex] = classCode;
    classIndex++;

    for(int i = 0; i < recordIndex; i++)
    {
      if(record[i].subjectCode.compare(subjectCode) == 0)
      {
        found = true;
        record[i].count++;
        break;
      }
    }
  }

  // create a new record for this subject
  if(!found)
  {
    record[recordIndex].subjectCode = subjectCode;
    record[recordIndex].count = 1;
    recordIndex++;
  }
}

/*******************************************************************************
 * Author:         Kartik Ayalasomayajula
 * CS Login:       Ayalasomayajula
 * 
 * 
 * Credits:        N/A
 * 
 * Course:         CS 368, Fall 2015
 * Assignment:     Programming Assignment 1 
 ******************************************************************************/
 
#include <iostream>
#include <ctype.h>

using namespace std;

//************Database of Students*
struct Student{
	int SID; // student ID
	int credits; // # of credits.
	double gpa;  // current GPA
};
//*********************************

int totalRecs = 0; // holds total number of records within the Database. 
////////////////////////////////////


//***********FIND STUDENT************
int findStudent(int ID, Student DB[]){
   int i;
   int returnVal;
   returnVal = -1; //-1 == error; !-1 == success
   if(totalRecs == 0){ // [1]Check if the list is empty. If so, exit unsuccessfully.
      returnVal = -1;
   }else{
      for(i = 0; i<totalRecs; i++){ //[2]Iterate through current list of students.
         if(DB[i].SID == ID){//[3]Checks if the given student matches the input paramater. 
            returnVal = i;//[4] if student matches, return student's position within DB.
         }
      }
   }
   return returnVal;
}
///////////////////////////////////////


//****************************ADD STUDENT********************
int addStudent(int ID, int credit, double gpa, Student DB[]){
   int returnVal;
   returnVal = -1;
   int testVali;
   testVali = findStudent(ID, DB); //[1]Finds the student.
   //[2]Checks if the student isn't already inside of the Database.
   //[2.1] If so, updates the student's information, increments totalRecs counter, returns 0 for success.
   if(testVali == -1){
      DB[totalRecs].gpa = gpa;
      DB[totalRecs].SID = ID;
      DB[totalRecs].credits = credit;
      totalRecs++;
      returnVal = 0;
   }
   return returnVal;// return -1 if student is already in Database.
}
////////////////////////////////////////////////////////////


//*****************************UPDATE STUDENT********************
int updateStudent(int ID, char grade, int credits, Student DB[]){
   int testVal = -1; //-1 = fail; !-1 = success
   grade = toupper(grade); 
   testVal = findStudent(ID, DB);
   double gradeAdjust;
   double  newGPA;
   
   //[1]Convert the letter grade parameter into GPA value.
   switch(grade){
      case 'A':
         gradeAdjust = 4.0;
         break;
      
      case 'B':
         gradeAdjust = 3.0;
         break;
      case 'C':
         gradeAdjust = 2.0;
         break;
      case 'D':
         gradeAdjust = 1.0;
         break;
      case 'F':
         gradeAdjust = 0.0;
         break;
      default:
         return -1;
         break;
   }

   //[2]Check if user aready exists in database. 
   //Calculate the new GPA.
   //Calculate the new Credits
   //updates both values
   //prints out new information to the user,
   if(testVal != -1){
      newGPA = (((DB[testVal].gpa) * (DB[testVal].credits)) + (gradeAdjust* credits))/(credits + DB[testVal].credits);
      DB[testVal].gpa = newGPA;
      DB[testVal].credits = DB[testVal].credits + credits;
      cout << DB[testVal].SID << ", " << DB[testVal].credits << ", " << DB[testVal].gpa << "\n"; 
      return 0;  
   }else{//[3]If user doesn't exist, exit unsuccessfully.
      return -1;
   }
}
/////////////////////////////////////////////////////////////


//*********COUNT GPA*******************
int countGPA(double GPA, Student DB[]){
   int total = 0;
   int i;
   //[1]Increments through current database.
   for(i = 0; i<totalRecs; i++){
      if(DB[i].gpa >= GPA){ //[2]Check if GPA is higher than the base GPA.
         total++; //[3] If so, increment counter.
         cout << DB[i].SID << ", " << DB[i].credits << ", " << DB[i].gpa << "\n"; //[4]Print out information to user.
      }
   }
   return total; //Returns total number of GPAs found to user.
}
/////////////////////////////////////


//********PRINT STUDENTS*********
void printStudents(Student DB[]){
   int i;
   //[1] Iterate through Database. Print out each value.
   for(i = 0; i<totalRecs; i++){
      cout << DB[i].SID << ", " << DB[i].credits << ", " << DB[i].gpa << "\n";
   }
}
///////////////////////////////

//*************DELETE STUDENT**********
int deleteStudent(int ID, Student* DB){
   int returnVal;
   int tempGPA;
   int tempSID = -1;
   int tempCredits;
   returnVal = -1;
   int testVal;
   testVal = findStudent(ID, DB);//[1]Finds out if the user currently exists within Database.

   //[2] If the user exists. Proceeds delete instructions
   if(testVal != -1){
      //[3]Checks if the user is the last item in the database.
      //If so, deletes user's contents. (set to 0).
      //Decrement total number of items so user's state is unindexable.
      if(testVal == totalRecs-1){
         DB[testVal].gpa = 0;
         DB[testVal].SID = 0;
         DB[testVal].credits = 0;
         totalRecs--;
         return 0;
      //[4]If user is not the last item within the database. 
      }else{
         //[4.1] Store items of last item in database.
         tempGPA  = DB[totalRecs-1].gpa;
         tempSID  = DB[totalRecs-1].SID;
         tempCredits  = DB[totalRecs-1].credits;
         //[4.2] Transfer over the stored items into the place where user's entry was found
         DB[testVal].gpa = tempGPA;
         DB[testVal].SID = tempSID;
         DB[testVal].credits = tempCredits;
         //[4.3] Delete all information for the last item within the database and unindex it.
         DB[totalRecs-1].gpa = 0;
         DB[totalRecs-1].SID = 0;
         DB[totalRecs-1].credits = 0;
         totalRecs--;
         return 0;  
      }
   }else{
      return -1;
   }
}
///////////////////////////////////

int main() {
    //************************************INITIALIZING DATABASE*********************
    bool done = false; //boolean for entire program. False until user exits program.
    char choice; //holds user command selection.
    int studentID; //holds the current user's Student ID.
    int credits; //holds current user's credits.
    double gpa; // holds current user's GPA.
    Student totalDB[7000]; //Array of students (7000 max). 
    
    //***********USER INTERFACE***************************
    // [1]Obtains user input.
    // [2]Switches to different operations based on User commands
    // [3]Re-obtains user input until user quits program
    cout << "Enter your commands at the > prompt:" << endl;
    while (!done) {
        cout << "> "; 
        cin >> choice; //obtaining user input.
        switch (choice) {
            case 'a': //a is the "add" command. Adds user to database; prints error if user is not in database.
		cin >> studentID >> credits >> gpa;
                int returnVal;
                returnVal = addStudent(studentID, credits, gpa, totalDB);
                if(returnVal == -1){
                   cout << "User already Exits.\n";
		   break;
                }
                break;          
            case 'd': //d is the "delete" command. Checks if user is in database. If user is in DB, deletes him/her; otherwise, prints error message.  
                cin >> studentID;  
                int output1;
                output1 = deleteStudent(studentID, totalDB);
                if(output1 == -1){
                   cout << "error - student " <<studentID << " not found\n";
                }
                break;
            case 'u': // u is the "update" command. updates the user's GPA and credits based on user input. Prints error if user isn't in the data base.
                char grade;
                cin >> studentID >> grade >> credits;
                if (grade == 'A' || grade == 'a' ||  grade=='B' || grade == 'b' || grade== 'C' || grade == 'c' || grade=='D' || grade == 'd' || grade=='F' || grade=='f'){
                   int output2;
                   output2 = updateStudent(studentID, grade, credits, totalDB);
                   if(output2 == -1){
                      cout << "error - student " <<studentID << " not found\n";
                   }
                   break; 
                }else{
                   cout << "grade must be (A, B, C, D, or F).\n";
                   break;
                }
                break;
            case 'c': // c is the "check" command. Checks and prints out a list of all users that are above a certain GPA baseline.
                double gpa;
                cin >> gpa;
                int output3;
                output3 = countGPA(gpa, totalDB); 
                if(output3 == 0){
                   cout << "no students found\n";
                }
                break;
            case 'p': // p is the "print" command. Prints out the contents of the User database.
               printStudents(totalDB);
               break;
            case 'q':  // q is the "quit" command. Simply quits the program.
                done = true;
                cout << "quit" << endl;
                break;
              
            default: break;
        } 
    } 
    return 0;
}

/*
  Name: Uyen Thy Duong
  Assignment: 1 - C/C++ Pointers
  Due Date: 02/12/2026
*/
// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <cctype>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
void promptName(std::string message, char* dest, int maxLen);

int main(int argc, char **argv)
{
    Student student;
    double average;

    // Prompt and validate student ID number
    student.id = promptInt("Please enter the student's id number: ", 1, 1000000000);

    student.f_name = new char[128];  // Allocate memory for C-string
    promptName("Please enter the student's first name: ", student.f_name, 128); // Get first name with validation

    student.l_name = new char[128];  // Allocate memory for C-string
    promptName("Please enter the student's last name: ", student.l_name, 128); // Get last name with validation

    // Get number of assignments with validation
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);
    std::cout << "\n";
    
    // Store assignment count in average to pass into the function
    average = (double)student.n_assignments; 

    student.grades = new double[student.n_assignments]; // Dynamic array allocation
    for (int i = 0; i < student.n_assignments; ++i) {
        // Collect each grade with range and type checking
        student.grades[i] = promptDouble("Please enter grade for assignment " + std::to_string(i) + ": ", 0.0, 1000.0);
    }
    std::cout << "\n";
    // Display formatted student summary
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    
    // Perform calculation using void and double pointers
    calculateStudentAverage(student.grades, &average);

    // Free dynamically allocated memory to prevent leaks
    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    return 0;
}

/*
   Validates integer input for data type and range
*/
int promptInt(std::string message, int min, int max)
{
    std::cout << message;
    int result;
    std::cin >> result;
    // Loop until input is a valid integer within the specified range
    while (std::cin.peek() != '\n' || std::cin.fail() || result < min || result > max) {
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
        std::cout << message;
        std::cin.clear(); // Reset fail bit
        std::cin.ignore(1000, '\n'); // Flush invalid buffer
        std::cin >> result;
    }
    std::cin.ignore();  // Clean up buffer for next input
    return result;
}

/*
   Validates double input for data type and range
*/
double promptDouble(std::string message, double min, double max)
{
    std::cout << message;
    double result;
    std::cin >> result;
    // Ensure input is a valid double and non-negative
    while (std::cin.peek() != '\n' || std::cin.fail() || result < min || result > max) {
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
        std::cout << message;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> result;
    }
    std::cin.ignore();  
    return result;
}

/*
   Calculates average score and prints result rounded to 1 decimal
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Extract assignment count from the double pointer
    int num_assignment = (int)*avg;
    double total = 0.0;
    double *gradesArray = (double*)object; // Cast void* to double* for access
    
    for (int i = 0; i < num_assignment; ++i) {
        total += gradesArray[i]; // Accumulate total score
    }
    *avg = total / num_assignment; // Compute final average
    
    // Print formatted output to match example exactly
    printf("  Average grade: %.1f\n", *avg); 
}

/*
   Validates string input to ensure it contains only alphabetic characters
   message: text to output as the prompt
   dest: the char array where the name will be stored
   maxLen: the maximum number of characters to read
*/
void promptName(std::string message, char* dest, int maxLen) {
    while (true) {
        std::cout << message;
        std::cin.getline(dest, maxLen);

        bool isValid = true;
        // Check if input is empty
        if (dest[0] == '\0') {
            isValid = false;
        }

        // Iterate through the C-string to check for numbers or symbols
        for (int i = 0; dest[i] != '\0'; i++) {
            if (!isalpha(dest[i])) { // isalpha returns false for numbers/symbols
                isValid = true; 
                if (isdigit(dest[i]) || ispunct(dest[i])) {
                    isValid = false;
                    break;
                }
            }
        }

        if (!isValid || std::cin.fail()) {
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cin.clear();
            if (std::cin.fail()) {
                std::cin.ignore(10000, '\n'); 
            }
        } else {
            break; // Input is clean
        }
    }
}
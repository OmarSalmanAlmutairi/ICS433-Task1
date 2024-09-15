#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store student information
struct Student {
  char name[50];
  int rollNumber;
  float marks;
};

// Function to read student data from a file
void readStudentData(struct Student *students, int *count, const char *filename) {
  FILE *file = fopen(filename, "r");

  // Error handling if the file cannot be opened
  if (file == NULL) {
    printf("Error: Could not open file '%s'. Please check if the file exists and you have read permissions.\n", filename);
    exit(1);
  }

  *count = 0;
  while (fscanf(file, "%s %d %f", students[*count].name, &students[*count].rollNumber, &students[*count].marks) != EOF) {
    // Ensure no more than 100 students are read (Array Overflow Protection)
    if (*count >= 100) {
      printf("Error: Too many students in the file. Maximum is 100.\n");
      break;
    }
    (*count)++;
  }

  // Error handling for the case when no students are read from the file
  if (*count == 0) {
    printf("Warning: No student data was read from the file.\n");
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  // Ensure exactly one command-line argument (the filename) is provided
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  struct Student students[100]; // Array to store up to 100 student records
  int count;

  // Read student data from the file
  readStudentData(students, &count, argv[1]);

  // Calculate and print the average marks
  if (count > 0) {
    float totalMarks = 0.0f;
    for (int i = 0; i < count; i++) {
      totalMarks += students[i].marks;
    }
    float averageMarks = totalMarks / count;

    printf("The average marks of the students is: %.2f\n", averageMarks);
  } else {
    printf("No student data was found to calculate the average.\n");
  }

  return 0;
}
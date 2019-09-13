

typedef struct {
	char* name;
	int grade;

} student;

student* create_student(char* name, int grade);

void print_student(student* s);

void delete_student(student* s);

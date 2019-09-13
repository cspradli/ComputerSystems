#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

student* create_student(char*name, int grade){
	student* s = (student*) malloc(sizeof(student));
	s->name = (char*) malloc(sizeof(char)* (strlen(name)+1));
	strcpy(s->name, name);
	s->grade = grade;

	return s;
}

void print_student(student* s){
	printf("Student %s has grade %i\n", s->name, s->grade);
}

void delete_student(student *s){
	free(s->name);
	free(s);
}



#include <stdio.h>
#include <stdlib.h>

#include "student.h"

#define CLASS_SIZE 17

int main(){
        int i;
        printf("Demo program\n");

        //just one student
        student* my_student;
        my_student = create_student("name", 1);
        print_student(my_student);
        delete_student(my_student);

	//static class size
	student* cs335_class[CLASS_SIZE];
	char buffer[100];

	for(i=0;i<CLASS_SIZE;i++){
		sprintf(buffer, "Class name %i",i);
		cs335_class[i] = create_student( buffer, 100-i );
	}
	for(i=0;i<CLASS_SIZE;i++){
		print_student( cs335_class[i] );
	}
	for(i=0;i<CLASS_SIZE;i++){
		delete_student(cs335_class[i]);
	}



	//dynamic class size
	student** dynamic_class;
	int num_students = (rand() % 10) + 1;
	printf("num students = %i\n", num_students);
	dynamic_class = (student**) malloc( sizeof(student*) * num_students);	
	
        for( i = 0; i < num_students; i++){
		sprintf(buffer, "Dynamic Name %i", i);
		dynamic_class[i] = create_student(buffer, 100-i);		
	}
 	
	for(i=0;i<num_students;i++){
		print_student(dynamic_class[i]);
	}
	for(i=0;i<num_students;i++){
		delete_student(dynamic_class[i]);
	}

	free(dynamic_class);
	int j = 0;
	int y = (~0 + 1);
	printf("j = %i and y = %i\n",j,y);	
}       


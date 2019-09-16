#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

	int x = 4;
	printf("x = %i\n", (x << 1));	

	int a = 5;
	int b = a << 3;
	int c = (a << 2);
	int d = (a << 1);
	printf(" a should be %i      a = %i\n", (5*14), (b+c+d));	

	a = 4;
	b = a << 5;
	c = a << 3;
	d = a << 2;
	int e = b + c + d;
	printf(" a should be %i      a = %i\n", (4*-44), (~e + 1));	

	a = 4;
	b = a << 10;
	printf(" a should be %i      a = %i\n", (4*1023), b - a);	
	
	x = 23;
	printf("1- %i\n", !(!~x));

	x = 23;
	printf("2- %i\n", !x);

	x = 23;
	printf("3- %i\n", !~(x & 0xff));

	x = -24;
	x = x >> 24;
	x = x & 0xff;
	if (x > 0 || x < 0){
		printf("3- 1\n");
	} else {
		printf("3- 0\n");		
	}
}       


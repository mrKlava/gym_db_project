#ifndef UTILS_INPUT_H
#define UTILS_INPUT_H

#include "types.h"

/* DATA TYPES */
void get_input_string(const char* prompt, char* destination, int length);
int get_input_positive_int(const char* prompt);
double get_input_positive_double(const char* prompt);

/* CUSTOM DATA TYPES */
int get_input_existing_client_id(const char* prompt);
int get_input_existing_instructor_id(const char* prompt);

Gender get_input_gender();
Date get_input_date(const char* prompt);
Time get_input_time(const char* prompt);
DateTime get_input_datetime(const char* prompt);

Client get_client();
Instructor get_instructor();
TrainingSession get_session();

#endif
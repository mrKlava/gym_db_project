#ifndef TYPES_H
#define TYPES_H

enum Gender { M = 1, F };

enum Month {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

typedef struct Date {
	int year;
	Month month;
	int day;
} Date;

typedef struct Time {
	int hour;
	int minute;
} Time;

typedef struct DateTime {
	Date date;
	Time time;
} DateTime;

typedef struct Client {
	int id;
	char name[32];
	char surname[32];
	Date dob;
	Gender gender;
} Client;

typedef struct Instructor {
	int id;
	char name[32];
	char surname[32];
	Gender gender;
} Instructor;

typedef struct TrainingSession {
	int id;
	int instructor_id;
	int client_id;
	double price;
	DateTime start;
	DateTime end;
} TrainingSession;

extern Instructor instructors[];
extern int instructor_count;
extern int instructor_last_id;
extern int next_id_instructor;

#endif
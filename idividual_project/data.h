#ifndef DATA_H
#define DATA_H

#include "constants.h"
#include "types.h"

bool load_data();
bool load_ids();

/* Instructors */
bool load_instructors();
int next_instructor_id();

bool add_instructor(const Instructor& ins);
bool delete_instructor_by_id(int target_id);

void sort_instructors_by_id(bool asc);
void sort_instructors_by_name(bool asc);

/* Clients */
bool load_clients();
int next_client_id();

bool add_client(const Client& client);
bool delete_client_by_id(int target_id)
;
void sort_clients_by_id(bool asc);
void sort_clients_by_name(bool asc);

/* Training Sessions */
bool load_sessions();
int next_session_id();

bool add_session(const TrainingSession& seesion);
bool delete_session_by_id(int target_id);

void sort_sessions_by_id(bool asc);
void sort_sessions_by_client_id(bool asc);
void sort_sessions_by_instructor_id(bool asc);
void sort_sessions_by_price(bool asc);
void sort_sessions_by_start_datetime(bool asc);

int compare_datetimes(const DateTime& a, const DateTime& b);
bool is_end_after_start(const DateTime& start, const DateTime& end);

bool is_client_exists(int client_id);
bool is_instructor_exists(int instructor_id);

#endif
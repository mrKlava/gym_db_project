#ifndef DATA_H
#define DATA_H

#include "constants.h"
#include "types.h"

bool load_data();
bool load_ids();

/* Instructors */
bool load_instructors();
bool add_instructor(const Instructor& ins);
int next_instructor_id();
bool delete_instructor_by_id(int target_id);
void sort_instructors_by_id(bool asc);
void sort_instructors_by_name(bool asc);


/* Clients */
bool load_clients();
bool add_client(const Client& client);
int next_client_id();
bool delete_client_by_id(int target_id);
void sort_clients_by_id(bool asc);
void sort_clients_by_name(bool asc);


#endif
#ifndef DATA_H
#define DATA_H

#include "constants.h"
#include "types.h"

bool load_data();
bool load_ids();

bool load_instructors();
bool add_instructor(const Instructor& ins);
int next_instructor_id();
bool delete_instructor_by_id(int target_id);

#endif
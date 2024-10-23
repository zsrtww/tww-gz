#ifndef TWWGZ_DEFINES_H
#define TWWGZ_DEFINES_H

// Required for keeping certain unused functions/variables from being removed
#define KEEP_FUNC __attribute__((used, visibility("default")))
#define KEEP_VAR __attribute__((visibility("default")))

// Generic macro to get the size of an array
#define ARRAY_COUNT(list) (sizeof(list) / sizeof((list)[0]))

#endif
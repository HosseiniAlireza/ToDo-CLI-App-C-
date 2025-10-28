#ifndef TODO_FUNCTION_H
#define TODO_FUNCTION_H

// Function declarations for ToDo CLI application.

void add(char **argv, int argc);
void list(void);
void clear(void);
void help(void);
int  removefromlist(const char *id_str);
void done(const char *id_str);

#endif // TODO_FUNCTION_H

#ifndef SET_H
#define SET_H

Set * set_create();
void set_destroy(Set *);

STATUS set_add(Set *, Id);
STATUS set_del(Set *, Id);

STATUS set_print(Set *);

#endif

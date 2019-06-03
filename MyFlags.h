#ifndef MYFLAGS_H_INCLUDED
#define MYFLAGS_H_INCLUDED

#define DEBUG 0
#define DEBUG_ARRAY 0

#define FAIL_THEN_RETURN(x) {if (FAIL == x) return FAIL;}

const bool SUCCEED = false;
const bool FAIL = true;

#endif // MYFLAGS_H_INCLUDED

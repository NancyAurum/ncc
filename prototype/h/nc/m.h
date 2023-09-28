/*

m.h: poor man's garbage collection


How does it work?
---------------------
- A number of groups is greated using mGrp()
- Then a context is created using mBegin(GroupPtr) and mEnd().
- Now mAlloc is used instead of malloc, with all allocations, being
  Assigned to current group (picked by mBegin).
- After that all of group's data can be freed in one go using mFree
- mAlloc() allocated can also be changed to another group. Think manual
  generational GC.

*/

//FIXME: this library covers one common use case:
// - hierarchical memory allocation
// Yet another use case is when some object persists in a cycle.
// For that we need MPtr, which will have mSet and mGet
// Setting mPtr will free the existing object, if its reference count gets 0.
// Other use cases are far more complex and justify manual memory management.

#:base

struct MGrp;
typedef struct MGrp MGrp;

//creates a new group
MGrp *mGrp();

//retrieves current group
MGrp *mCurGrp();

//allocs memory inside the current group
void *mAlloc(size_t size);

//frees memory previously allocated bt mAlloc
void mFree(void *ptr);

//starts adding elements to the group grp
//if grp is 0, then creates a temporary group, which gets freed on mEnd
void mBegin(MGrp *grp);

//finishes allocating to the current group.
void mEnd();

//Frees elements of the group grp
//if grp is 0, then grp will be the current group
void mClean(MGrp *grp);

//frees the group's elements and the group itself
//if grp is 0, then frees current group, as well as calling mEnd on it
void mFreeGrp(MGrp *grp);

//get group associated with ptr
//return 0 if ptr was removed from group
MGrp *mGetGrp(void *ptr);

//moves allocated memory to a new group
//if grp is 0, then the memory becomes detached from a group
void *mSetGrp(void *ptr, MGrp *grp);

//does mSetGrp(ptr, grp) for each group object
void mUnmanage(MGrp *grp);

void mDebug();



#endif

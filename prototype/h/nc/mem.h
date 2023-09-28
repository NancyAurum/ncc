#:base
#:m

//new() uses mAlloc allocates memory inside the current group
//so the memory can be quickly free for all objects allocated down the hierarchy

#new(type) ((type*)mAlloc(sizeof(type))).ctor
#delete(o) mFree((o).dtor)

#CTOR(type,{body}) {
inline void type.ctor_i_ {body}
inline type *type.ctor {#<type>_m_ctors_(this); this.ctor_i_; return this;}
}

#DTOR(type,{body}) {
inline void type.dtor_i_ {body}
inline type *type.dtor {this.dtor_i_; #<type>_m_dtors_(this); return this;}
}

char *char.dup;
inline int int.dup {return *this;}

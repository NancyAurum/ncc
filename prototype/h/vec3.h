#include <float.h>
#include <math.h>

#:nc/base

//Linear algebra related stuff
//Needs support for vector extensions:
//https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html


//epsilon - value near zero
#EPS 0.0000000001

#PI 3.141592653589793
#PI2 (2.0*3.141592653589793)

<<<
typedef int ivec3 __attribute__ ((vector_size (16)));
typedef F32 vec3  __attribute__ ((vector_size (16)));


typedef int ivec2  __attribute__ ((vector_size (8)));
typedef F32 vec2  __attribute__ ((vector_size (8)));
>>>

//typedef vec3 mat3[3];

#ME (*this)

class !vec3;
class !vec2;
class !ivec2;
class !ivec3;


inline F32 vec3.x {return ME[0];}
inline F32 vec3.y {return ME[1];}
inline F32 vec3.z {return ME[2];}

inline F32 vec3."x="(F32 v) {ME[0] = v; return v;}
inline F32 vec3."y="(F32 v) {ME[1] = v; return v;}
inline F32 vec3."z="(F32 v) {ME[2] = v; return v;}

inline F32 vec3."x+="(F32 v) {ME[0] += v; return ME[0];}
inline F32 vec3."y+="(F32 v) {ME[1] += v; return ME[1];}
inline F32 vec3."z+="(F32 v) {ME[2] += v; return ME[2];}

inline F32 vec3."x-="(F32 v) {ME[0] -= v; return ME[0];}
inline F32 vec3."y-="(F32 v) {ME[1] -= v; return ME[1];}
inline F32 vec3."z-="(F32 v) {ME[2] -= v; return ME[2];}

inline int ivec3.x {return ME[0];}
inline int ivec3.y {return ME[1];}
inline int ivec3.z {return ME[2];}

inline int ivec3."x="(int v) {ME[0] = v; return ME[0];}
inline int ivec3."y="(int v) {ME[1] = v; return ME[1];}
inline int ivec3."z="(int v) {ME[2] = v; return ME[2];}

inline int ivec3."x+="(int v) {ME[0] += v; return ME[0];}
inline int ivec3."y+="(int v) {ME[1] += v; return ME[1];}
inline int ivec3."z+="(int v) {ME[2] += v; return ME[2];}

inline int ivec3."x-="(int v) {ME[0] -= v; return ME[0];}
inline int ivec3."y-="(int v) {ME[1] -= v; return ME[1];}
inline int ivec3."z-="(int v) {ME[2] -= v; return ME[2];}

inline F32 vec2.x {return ME[0];}
inline F32 vec2.y {return ME[1];}

inline F32 vec2."x="(F32 v) {ME[0] = v; return v;}
inline F32 vec2."y="(F32 v) {ME[1] = v; return v;}

inline int vec2."x+="(int v) {ME[0] += v; return ME[0];}
inline int vec2."y+="(int v) {ME[1] += v; return ME[1];}

inline int vec2."x-="(int v) {ME[0] -= v; return ME[0];}
inline int vec2."y-="(int v) {ME[1] -= v; return ME[1];}

inline int ivec2.x {return ME[0];}
inline int ivec2.y {return ME[1];}

#undef ME

char *vec3.cstr;

typedef struct {
  vec3 X, Y, Z;
} mat3;

#VABS(d,v) {do {
  (d).x = fabsf((v).x);
  (d).y = fabsf((v).y);
  (d).z = fabsf((v).z);
} while(0)}

inline F32 sum(vec3 v) {
  return v.x + v.y + v.z;
}

inline int isum(ivec3 v) {
  return v.x + v.y + v.z;
}

inline F32 dot(vec3 a, vec3 b) {
  return sum(a*b);
}

inline vec3 cross(vec3 a, vec3 b) {
  return (vec3){a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}

inline F32 vlen(vec3 v) {
  return sqrtf(dot(v,v));
}

inline F32 vlen2(vec3 v) {
  return dot(v,v);
}

inline F32 distance(vec3 a, vec3 b) {
  return vlen(a - b);
}

//convert unit vector to spherical coordinates in ranged [0:1]
inline vec2 unit_to_polar(vec3 n) {
  F32 theta = 1.0 - atan2(n.z,n.x)/(PI*2) - 0.5;
  F32 phi = 1.0 - acos(n.y)/PI;
  return (vec2){theta,phi};
}

inline vec3 vmin(vec3 a, vec3 b) {
  return (vec3){fmin(a.x,b.x), fmin(a.y,b.y), fmin(a.z,b.z)};
}

inline vec3 vmax(vec3 a, vec3 b) {
  return (vec3){fmax(a.x,b.x), fmax(a.y,b.y), fmax(a.z,b.z)};
}

inline vec3 vabs(vec3 a) {
  return (vec3){fabsf(a.x), fabsf(a.y), fabsf(a.z)};
}

inline vec3 vfloor(vec3 a) {
  return (vec3){floorf(a.x), floorf(a.y), floorf(a.z)};
}

inline vec3 vceil(vec3 a) {
  return (vec3){ceilf(a.x), ceilf(a.y), ceilf(a.z)};
}

inline vec3 vround(vec3 a) {
  return (vec3){roundf(a.x), roundf(a.y), roundf(a.z)};
}

/*
//not needed. 1.0f/v does the trick.
inline vec3 vinv(vec3 v) {
  return (vec3){1.0f,1.0f,1.0f}/v;
}*/

inline F32 mine(vec3 a) {
  return fmin(a.x,fmin(a.y,a.z));
}

inline F32 maxe(vec3 a) {
  return fmax(a.x,fmax(a.y,a.z));
}

inline vec3 normalized(vec3 v) {
  return v/sqrtf(dot(v,v));
}

inline F32 vangle(vec3 a, vec3 b) {
  return dot(a,b)/(vlen(a)*vlen(b));
}

inline uint32_t v2rgb(vec3 a) {
  uint32_t r = (U32)a.x.clamp_byte;
  uint32_t g = (U32)a.y.clamp_byte;
  uint32_t b = (U32)a.z.clamp_byte;
  return (r<<16) | (g<<8) | b;
}

inline uint32_t vnormal2rgb(vec3 a) {
  uint32_t r = a.x*127.0f + 127.0;
  uint32_t g = a.y*127.0f + 127.0;
  uint32_t b = a.z*127.0f + 127.0;
  return (r<<16) | (g<<8) | b;
}

inline vec3 vrgb2normal(uint32_t c) {
  uint32_t r = (c>>16)&0xFF;
  uint32_t g = (c>> 8)&0xFF;
  uint32_t b = (c    )&0xFF;
  return (vec3){(r-127.0f)/127.0f,(g-127.0f)/127.0f,(b-127.0f)/127.0f};
}

#EPS2ZERO(x) ((fabs(x)<EPS) ? 0.0 : (x))
         
#VEPS2ZERO(a) {
       do { (a).x = EPS2ZERO((a).x);
            (a).y = EPS2ZERO((a).y);
            (a).z = EPS2ZERO((a).z);
          } while(0)}

#VSWAP(a,b) {
   do {vec3 t_ = a;
       a = b;
       b = t_;
     } while(0)}

#DEG2RAD(v) ((v)*PI2/360.0)
#RAD2DEG(v) ((v)*360.0/PI2)

inline vec3 vdeg2rad(vec3 v) {
  return v*(F32)(PI2/360.0);
}

#VDEG2RAD(a,b) {
   do { (a).x = DEG2RAD((b).x);
        (a).y = DEG2RAD((b).y);
        (a).z = DEG2RAD((b).z);
      } while(0)}

//angle between two vectors
#VANGLE(a,b) (dot(a,b)/(vlen(a)*vlen(b)))

#VFLOOR32(a,b) {
   do { (a).x = (F32)(uint32_t)(b).x;
        (a).y = (F32)(uint32_t)(b).y;
        (a).z = (F32)(uint32_t)(b).z;
      } while(0)}

#VPRINT(v) fprintf(stderr, "%f, %f, %f\n", (v).x,(v).y,(v).z);
#IVPRINT(v) fprintf(stderr, "%d, %d, %d\n", (v).x,(v).y,(v).z);

#if 0
inline F32 ddot(vec3 a, vec3 b) {
  return (double)(a.x)*(double)(b.x)
       + (double)(a.y)*(double)(b.y)
       + (double)(a.z)*(double)(b.z);
}
#endif

//vector matrix multiplication
inline vec3 vmm_(vec3 v, mat3 *m) {
  return (vec3){dot((v),(m)->X),dot((v),(m)->Y),dot((v),(m)->Z)};
}
#vmm(v,m) vmm_((v),&(m))

#MMULM(r,a,b) {do {
  (r).X = vmm((b).X,(a));
  (r).Y = vmm((b).Y,(a));
  (r).Z = vmm((b).Z,(a));
  } while(0)}


#MROTX(m,angle) {do {
  F32 c = cos(angle);
  F32 s = sin(angle);
  (m).X = (vec3){1.0,0.0,0.0};
  (m).Y = (vec3){0.0,  c,  s};
  (m).Z = (vec3){0.0, -s,  c};
  } while(0)}

#MROTY(m,angle) {do {
  F32 c = cos(angle);
  F32 s = sin(angle);
  (m).X = (vec3){  c,0.0, -s};
  (m).Y = (vec3){0.0,1.0,0.0};
  (m).Z = (vec3){  s,0.0,  c};
  } while(0)}

#MROTZ(m,angle) {do {
  F32 c = cos(angle);
  F32 s = sin(angle);
  (m).X = (vec3){  c,  s,0.0};
  (m).Y = (vec3){ -s,  c,0.0};
  (m).Z = (vec3){0.0,0.0,1.0};
  } while(0)}

inline mat3 mrotated(mat3 src, vec3 angle) {
  mat3 rx,ry,rz;
  MROTX(rx,angle.x);
  MROTY(ry,angle.y);
  MROTZ(rz,angle.z);
  mat3 t0,t1,dst;
  MMULM(t0 ,rx,src);
  MMULM(t1 ,ry,t0  );
  MMULM(dst,rz,t1  );
  return dst;
}

//computes matrix for the reversed rotation.
inline mat3 mrotated_r(mat3 src, vec3 angle) {
  mat3 rx,ry,rz;
  angle = -angle;
  MROTX(rx,angle.x);
  MROTY(ry,angle.y);
  MROTZ(rz,angle.z);
  mat3 t0,t1,dst;
  MMULM(t0 ,rz,src);
  MMULM(t1 ,ry,t0  );
  MMULM(dst,rx,t1  );
  return dst;
}

inline mat3 midentity() {
  mat3 m;
  m.X = (vec3){1.0,0.0,0.0};
  m.Y = (vec3){0.0,1.0,0.0};
  m.Z = (vec3){0.0,0.0,1.0};
  return m;
}

inline mat3 mscaled(mat3 m, vec3 v) {
  m.X *= v.x;
  m.Y *= v.y;
  m.Z *= v.z;
  return m;
}


inline
F32 ray_plane_hit_dist(vec3 ro, vec3 rd, vec3 plane_coord, vec3 plane_normal) {
  F32 nd = dot(plane_normal,rd);
  F32 d = dot(plane_normal,plane_coord);
  F32 t = (d -  dot(plane_normal,ro))/nd; //length until hit
  return t;
}

inline
vec3 ray_plane_hit(vec3 ro, vec3 rd, vec3 plane_coord, vec3 plane_normal) {
  F32 t = ray_plane_hit_dist(ro, rd, plane_coord, plane_normal);
  return (rd * t) + ro;
}


//from
//https://www.reddit.com/r/learnprogramming/comments/hutij3/raycube_intersection_points/
inline
int ray_box_hit(vec3 *RESTRICT hita, vec3 *RESTRICT hitb //hit points
                ,vec3 ro, vec3 rd //ray origin/direction
                ,vec3 box_min  //min x,y,z corner
                ,vec3 box_max  //max x,y,z corner
          ) {
  vec3 da = box_min - ro;
  vec3 db = box_max - ro;
  
  vec3 dmin = vmin(da,db);
  vec3 dmax = vmax(da,db);

  vec3 rd_inv = (vec3){1,1,1}/(rd + (vec3){FLT_MIN,FLT_MIN,FLT_MIN});

  //first get the times to corner A planes and corner B planes
  vec3 times_A = dmin * rd_inv;
  vec3 times_B = dmax * rd_inv;

  //THEN determine the near and far planes
  vec3 times_min = vmin(times_A,times_B);
  vec3 times_max = vmax(times_A,times_B);

  F32 time_enter = maxe(times_min);
  F32 time_leave = mine(times_max);

  //exit before entrance = no intersection
  if (time_enter >= time_leave) return 0;
  //starting inside or past cube = no intersection
  if (time_enter < 0) return 0;


  *hita = rd*time_enter + ro;
  *hitb = rd*time_leave + ro;

  return 1;
}


inline
int ray_cube_hit(vec3 *RESTRICT hit //hit points
                ,vec3 ro, vec3 rd //ray origin/direction
                ,vec3  o  //min x,y,z
                ,F32 c //max x,y,z
          ) {
  vec3 da = o - ro;
  vec3 db = da + (vec3){c,c,c};

  vec3 rd_inv = (vec3){1,1,1}/(rd + (vec3){FLT_MIN,FLT_MIN,FLT_MIN});

  //first get the times to corner A planes and corner B planes
  vec3 times_A = vmin(da,db) * rd_inv;
  vec3 times_B = vmax(da,db) * rd_inv;

  //THEN determine the near and far planes
  F32 time_enter = maxe(vmin(times_A,times_B));
  F32 time_leave = mine(vmax(times_A,times_B));

  //exit before entrance = no intersection
  if (time_enter >= time_leave) return 0;
  //starting inside or past cube = no intersection
  if (time_enter < 0) return 0;

  *hit = rd*time_enter + ro;
  return 1;
}

inline vec2 ray_box_hit_test(vec3 ro, vec3 rd, vec3 bmin, vec3 bmax) {
  vec3 da = bmin - ro;
  vec3 db = da + bmax-bmin;

  vec3 rd_inv = (vec3){1,1,1}/(rd + (vec3){FLT_MIN,FLT_MIN,FLT_MIN});

  //first get the times to corner A planes and corner B planes
  vec3 times_A = vmin(da,db) * rd_inv;
  vec3 times_B = vmax(da,db) * rd_inv;

  //THEN determine the near and far planes
  F32 time_enter = maxe(vmin(times_A,times_B));
  F32 time_leave = mine(vmax(times_A,times_B));

  //exit before entrance = no intersection
  if (time_enter >= time_leave) return (vec2){INFINITY,INFINITY};
  //starting inside or past cube = no intersection
  //if (time_enter < 0) return (vec2){INFINITY,INFINITY};

  return (vec2){time_enter,time_leave};
}



inline
int solveQuadratic(F32 a, F32 b, F32 c, F32 *x0_, F32 *x1_) { 
  F32 x0, x1;
  F32 discr = b * b - 4 * a * c; 
  if (discr < 0) return 0; 
  else if (discr == 0) x0 = x1 = - 0.5 * b / a; 
  else { 
      F32 q = (b > 0) ? 
          -0.5 * (b + sqrt(discr)) : 
          -0.5 * (b - sqrt(discr)); 
      x0 = q / a; 
      x1 = c / q; 
  } 
  if (x0 > x1) {
    SWAP(x0, x1);
  }

  *x0_=x0, *x1_=x1;
  return 1; 
}

static
int ray_sphere_intersect(F32 *t, vec3 center, F32 radius
                        ,vec3 ro, vec3 rd) { 
  F32 t0, t1; // solutions for t if the ray intersects
  vec3 l;
#if 0
  l = ro - center;
  F32 a = rd*rd;
  F32 b = rd*l*2.0f;
  F32 c = l*l - radius*radius;
  if (!solveQuadratic(a, b, c, &t0, &t1)) return 0;
#else
  l = center - ro;
  F32 tca = dot(l,rd);
  F32 d2 = dot(l,l) - tca*tca;
  F32 radius2 = radius*radius;
  if (d2 > radius2) return 0;
  F32 thc = sqrt(radius2 - d2);
  t0 = tca - thc;
  t1 = tca + thc;
#endif
  if (t0 > t1) {
    SWAP(t0, t1); 
  }

  if (t0 < 0) { 
    t0 = t1; // if t0 is negative (we are inside), let's use t1 instead 
    if (t0 < 0) return 0; // both t0 and t1 are negative, sphere is behind
  }
  *t = t0;
  return 1;
}




inline int ray_aabb_hit_test(vec3 ro, vec3 rd, vec3 bmin, vec3 bmax) {
  vec3 rd_inv = (vec3){1.0f/rd.x, 1.0f/rd.y, 1.0f/rd.z};
  vec3 a = (bmin - ro)*rd_inv;
  vec3 b = (bmax - ro)*rd_inv;
  F32 tmin = maxe(vmin(a,b));
  F32 tmax = mine(vmax(a,b));
  return tmax >= fmax(0.0, tmin); // && tmin < t
}



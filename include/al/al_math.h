#ifndef AL_MATH_H
#define AL_MATH_H

#include "al_glm.h"

#ifndef AL_MIN
#define AL_MIN(x,y) (x<y?x:y)
#endif

#ifndef AL_MAX
#define AL_MAX(x,y) (x>y?x:y)
#endif

#define AL_IS_NAN_FLOAT(v)		((v)!=(v))
#define AL_FIX_NAN_FLOAT(v)		((v)=AL_IS_NAN_FLOAT(v)?0.f:(v))

#define AL_DOUBLE_FLOOR(v) ( (long)(v) - ((v)<0.0 && (v)!=(long)(v)) )
#define AL_DOUBLE_CEIL(v) ( (((v)>0.0)&&((v)!=(long)(v))) ? 1+(v) : (v) )

#define AL_FLOAT_FLOOR(v) ( (int)(v) - ((v)<0.f && (v)!=(int)(v)) )
#define AL_FLOAT_CEIL(v) ( (((v)>0.f)&&((v)!=(int)(v))) ? 1+(v) : (v) )

// this won't work for negative numbers:
#define AL_DOUBLE_FRAC(v) ( ((v)>=0.0) ? (v)-(long)(v) : (-v)-(long)(v) )


inline bool al_isnan(float v) { return v!=v; }
inline float al_fixnan(float v) { return al_isnan(v)?0.f:v; }


inline bool al_isnan(glm::vec2 v) { 
	return al_isnan(v.x) || al_isnan(v.y); 
}
inline bool al_isnan(glm::vec3 v) { 
	return al_isnan(v.x) || al_isnan(v.y) || al_isnan(v.z); 
}
inline bool al_isnan(glm::vec4 v) { 
	return al_isnan(v.x) || al_isnan(v.y) || al_isnan(v.z) || al_isnan(v.w); 
}
inline bool al_isnan(glm::quat v) { 
	return al_isnan(v.x) || al_isnan(v.y) || al_isnan(v.z) || al_isnan(v.w); 
}


inline glm::vec2 al_fixnan(glm::vec2 v) { 
	return glm::vec2( al_fixnan(v.x), al_fixnan(v.y));
}
inline glm::vec3 al_fixnan(glm::vec3 v) { 
	return glm::vec3( al_fixnan(v.x), al_fixnan(v.y), al_fixnan(v.z) );
}
inline glm::vec4 al_fixnan(glm::vec4 v) { 
	return glm::vec4( al_fixnan(v.x), al_fixnan(v.y), al_fixnan(v.z), al_fixnan(v.w) );
}
inline glm::quat al_fixnan(glm::quat v) { 
	return glm::quat( al_fixnan(v.x), al_fixnan(v.y), al_fixnan(v.z), al_fixnan(v.w) );
}

float radians(float degrees) {
	return degrees*0.01745329251994f;
}

float degrees(float radians) {
	return radians*57.29577951308233f;
}

float clip(float in, float min, float max) {
	float v = AL_MIN(in, max);
	return AL_MAX(v, min);
}


// Note: "a - N*floorf(a / N)" does not work due to occasional floating point error
// this is far simpler but N must be nonzero:
template<typename T, typename T1>
T wrap(T a, T1 N) {
	return glm::fract(a / N) * N;
}

template<typename T, typename T1>
inline T wrap(T x, T1 lo, T1 hi) {
	return lo + wrap(x-lo, hi-lo);
}

/*

// The old way I was using before; the glm::fract method above seems numerically stable though

template<typename T>
inline T wrap(T x, T mod) {
	if (mod) {
		if (x > mod) {
			// shift down
			if (x > (mod*T(2))) {
				// multiple wraps:
				T div = x / mod;
				// get fract:
				T divl = (T)(long)div;
				T fract = div - (T)divl;
				return fract * mod;
			} else {
				// single wrap:
				return x - mod;
			}
		} else if (x < T(0)) {
			// negative x, shift up
			if (x < -mod) {
				// multiple wraps:
				T div = x / mod;
				// get fract:
				T divl = (T)(long)div;
				T fract = div - (T)divl;
				T x1 = fract * mod;
				return (x1 < T(0)) ? x1 + mod : x1;	
			} else {
				// single wrap:
				return x + mod;
			}
		} else {
			return x;
		}
	} else {
		return T(0);	// avoid divide by zero
	}
}

glm::vec2 wrap(glm::vec2 v, float dim=1.f) {
	return glm::vec2(
		wrap(v.x, dim), 
		wrap(v.y, dim)
	);
}

glm::vec3 wrap(glm::vec3 v, float dim=1.f) {
	return glm::vec3(
		wrap(v.x, dim), 
		wrap(v.y, dim), 
		wrap(v.z, dim)
	);
}
*/



class rnd {
public: 

	static void seed() {
		srand((unsigned int)time(NULL));
	}

	static int integer(int lim=2) {
		return (int)floorf(glm::linearRand(0.f, lim-0.0000001f));
	}

	static float uni(float lim=1.f) {
		return glm::linearRand(0.f, lim);
	}	

	static float bi(float lim=1.f) {
		return glm::linearRand(-lim, lim);
	}	

};

#endif //AL_MATH_H
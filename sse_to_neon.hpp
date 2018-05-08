//
//  sse_to_neon.hpp
//  neon_test
//
//  Created by Tim Oberhauser on 11/16/13.
//  Copyright (c) 2013 Tim Oberhauser. All rights reserved.
//

#ifndef neon_test_sse_to_neon_hpp
#define neon_test_sse_to_neon_hpp

#include <arm_neon.h>

#if defined(__MM_MALLOC_H)
// copied from mm_malloc.h {
#include <stdlib.h>

/* We can't depend on <stdlib.h> since the prototype of posix_memalign
 may not be visible.  */
#ifndef __cplusplus
extern int posix_memalign (void **, size_t, size_t);
#else
extern "C" int posix_memalign (void **, size_t, size_t) throw ();
#endif

static __inline void *
_mm_malloc (size_t size, size_t alignment)
{
    void *ptr;
    if (alignment == 1)
        return malloc (size);
    if (alignment == 2 || (sizeof (void *) == 8 && alignment == 4))
        alignment = sizeof (void *);
    if (posix_memalign (&ptr, alignment, size) == 0)
        return ptr;
    else
        return NULL;
}

static __inline void
_mm_free (void * ptr)
{
    free (ptr);
}
// } copied from mm_malloc.h
#endif


typedef int16x8_t __m128i;
typedef float32x4_t __m128;

#endif

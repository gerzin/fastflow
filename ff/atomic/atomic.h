/* Massimo: 
 *  This is a slightly modified version of the linux kernel file 
 *   /<source-dir>/include/asm-generic/atomic.h
 *
 */

#ifndef _ASM_GENERIC_ATOMIC_H
#define _ASM_GENERIC_ATOMIC_H
/*
 * Copyright (C) 2005 Silicon Graphics, Inc.
 *	Christoph Lameter <clameter@sgi.com>
 *
 * Allows to provide arch independent atomic definitions without the need to
 * edit all arch specific atomic.h files.
 */


//#include <asm/types.h>

#if __linux__ || __FreeBSD__ || __APPLE__

#if __linux__ || __FreeBSD__
#ifdef __i386__
#include "atomic-i386.h"
#elif __x86_64__
#include "atomic-x86_64.h"
#if !defined(BITS_PER_LONG)
#define BITS_PER_LONG 64
#endif
#elif __ia64__
#error "IA64 not yet supported"
#endif

#elif __APPLE__

#ifdef __i386__
#include "atomic-i386.h"
#elif __x86_64__
#include "atomic-x86_64.h"
#if !defined(BITS_PER_LONG)
#define BITS_PER_LONG 64
#endif
#elif __POWERPC__
#include "atomic-ppc.h"
#endif

#endif

/*
 * Suppport for atomic_long_t
 *
 * Casts for parameters are avoided for existing atomic functions in order to
 * avoid issues with cast-as-lval under gcc 4.x and other limitations that the
 * macros of a platform may have.
 */

#if (BITS_PER_LONG == 64)


typedef atomic64_t atomic_long_t;

#define ATOMIC_LONG_INIT(i)	ATOMIC64_INIT(i)

static inline long atomic_long_read(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_read(v);
}

static inline void atomic_long_set(atomic_long_t *l, long i)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_set(v, i);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_inc(v);
}

static inline long atomic_long_inc_return(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_inc_return(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
	atomic64_t *v = (atomic64_t *)l;

	atomic64_dec(v);
}

static inline void atomic_long_add(long i, atomic_long_t *l)
{
        atomic64_t *v = (atomic64_t *)l;

        atomic64_add(i, v);
}

static inline void atomic_long_sub(long i, atomic_long_t *l)
{
        atomic64_t *v = (atomic64_t *)l;

        atomic64_sub(i, v);
}


static inline long atomic_long_add_unless(atomic_long_t *l, long a, long u)
{
	atomic64_t *v = (atomic64_t *)l;

	return (long)atomic64_add_unless(v, a, u);
}


#define atomic_long_cmpxchg(l, old, new) \
	(atomic64_cmpxchg((atomic64_t *)(l), (old), (new)))

#else

typedef atomic_t atomic_long_t;

#define ATOMIC_LONG_INIT(i)	ATOMIC_INIT(i)

static inline long atomic_long_read(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_read(v);
}

static inline void atomic_long_set(atomic_long_t *l, long i)
{
	atomic_t *v = (atomic_t *)l;

	atomic_set(v, i);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_inc(v);
}

static inline long atomic_long_inc_return(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_inc_return(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_dec(v);
}


static inline void atomic_long_add(long i, atomic_long_t *l)
{
        atomic_t *v = (atomic_t *)l;

        atomic_add(i, v);
}

static inline void atomic_long_sub(long i, atomic_long_t *l)
{
        atomic_t *v = (atomic_t *)l;

        atomic_sub(i, v);
}

static inline long atomic_long_add_unless(atomic_long_t *l, long a, long u)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_add_unless(v, a, u);
}

#define atomic_long_cmpxchg(l, old, new) \
	(atomic_cmpxchg((atomic_t *)(l), (old), (new)))

#endif

#elif (defined(_MSC_VER) || defined(__INTEL_COMPILER)) && defined(_WIN32)
typedef struct { volatile int counter; } atomic_t;
#include "ff/platforms/platform_msvc_windows.h"
#define BITS_PER_LONG (sizeof(long) * 8)
#endif

#endif
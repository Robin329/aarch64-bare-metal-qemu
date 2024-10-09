/*
 *  linux/include/asm-arm/io.h
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Modifications:
 *  16-Sep-1996	RMK	Inlined the inx/outx functions & optimised for both
 *			constant addresses and variable addresses.
 *  04-Dec-1997	RMK	Moved a lot of this stuff to the new architecture
 *			specific IO header files.
 *  27-Mar-1999	PJB	Second parameter of memcpy_toio is const..
 *  04-Apr-1999	PJB	Added check_signature.
 *  12-Dec-1999	RMK	More cleanups
 *  18-Jun-2000 RMK	Removed virt_to_* and friends definitions
 */
#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>
#define __user
#define __kernel
#define __safe
#define __force
#define __nocast
#define __iomem
#define __bitwise
typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;

__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;

typedef __u16 __bitwise __le16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __le32;
typedef __u32 __bitwise __be32;
typedef __u64 __bitwise __le64;
typedef __u64 __bitwise __be64;


typedef __s8 s8;
typedef __u8 u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
typedef __s64 s64;
typedef __u64 u64;

#define __constant_htonl(x) ((__force __be32)___constant_swab32((x)))
#define __constant_ntohl(x) ___constant_swab32((__force __be32)(x))
#define __constant_htons(x) ((__force __be16)___constant_swab16((x)))
#define __constant_ntohs(x) ___constant_swab16((__force __be16)(x))
#define __constant_cpu_to_le64(x) ((__force __le64)(__u64)(x))
#define __constant_le64_to_cpu(x) ((__force __u64)(__le64)(x))
#define __constant_cpu_to_le32(x) ((__force __le32)(__u32)(x))
#define __constant_le32_to_cpu(x) ((__force __u32)(__le32)(x))
#define __constant_cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define __constant_le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define __constant_cpu_to_be64(x) ((__force __be64)___constant_swab64((x)))
#define __constant_be64_to_cpu(x) ___constant_swab64((__force __u64)(__be64)(x))
#define __constant_cpu_to_be32(x) ((__force __be32)___constant_swab32((x)))
#define __constant_be32_to_cpu(x) ___constant_swab32((__force __u32)(__be32)(x))
#define __constant_cpu_to_be16(x) ((__force __be16)___constant_swab16((x)))
#define __constant_be16_to_cpu(x) ___constant_swab16((__force __u16)(__be16)(x))
#define __cpu_to_le64(x) ((__force __le64)(__u64)(x))
#define __le64_to_cpu(x) ((__force __u64)(__le64)(x))
#define __cpu_to_le32(x) ((__force __le32)(__u32)(x))
#define __le32_to_cpu(x) ((__force __u32)(__le32)(x))
#define __cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define __le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define __cpu_to_be64(x) ((__force __be64)__swab64((x)))
#define __be64_to_cpu(x) __swab64((__force __u64)(__be64)(x))
#define __cpu_to_be32(x) ((__force __be32)__swab32((x)))
#define __be32_to_cpu(x) __swab32((__force __u32)(__be32)(x))
#define __cpu_to_be16(x) ((__force __be16)__swab16((x)))
#define __be16_to_cpu(x) __swab16((__force __u16)(__be16)(x))
/*
 * Allow constant folding
 */
#if defined(__GNUC__) && (__GNUC__ >= 2) && defined(__OPTIMIZE__)
#define __swab16(x)                                                            \
	(__builtin_constant_p((__u16)(x)) ? ___swab16((x)) : __fswab16((x)))
#define __swab32(x)                                                            \
	(__builtin_constant_p((__u32)(x)) ? ___swab32((x)) : __fswab32((x)))
#define __swab64(x)                                                            \
  (__builtin_constant_p((__u64)(x)) ? ___swab64((x)) : __fswab64((x)))
#endif
/*
 * provide defaults when no architecture-specific optimization is detected
 */
#ifndef __arch__swab16
#define __arch__swab16(x) ___swab16(x)
#endif
#ifndef __arch__swab32
#define __arch__swab32(x) ___swab32(x)
#endif
#ifndef __arch__swab64
#define __arch__swab64(x) ___swab64(x)
#endif

#ifndef __arch__swab16p
#define __arch__swab16p(x) __swab16(*(x))
#endif
#ifndef __arch__swab32p
#define __arch__swab32p(x) __swab32(*(x))
#endif
#ifndef __arch__swab64p
#define __arch__swab64p(x) __swab64(*(x))
#endif


static __inline__ __u64 __swab64p(const __u64 *x)
{
	return __arch__swab64p(x);
}
static __inline__ void __swab64s(__u64 *addr)
{
	__arch__swab64s(addr);
}
static inline __le64 __cpu_to_le64p(const __u64 *p)
{
	return (__force __le64)*p;
}
static inline __u64 __le64_to_cpup(const __le64 *p)
{
	return (__force __u64)*p;
}
static inline __le32 __cpu_to_le32p(const __u32 *p)
{
	return (__force __le32)*p;
}
static inline __u32 __le32_to_cpup(const __le32 *p)
{
	return (__force __u32)*p;
}
static inline __le16 __cpu_to_le16p(const __u16 *p)
{
	return (__force __le16)*p;
}
static inline __u16 __le16_to_cpup(const __le16 *p)
{
	return (__force __u16)*p;
}
static inline __be64 __cpu_to_be64p(const __u64 *p)
{
	return (__force __be64)__swab64p(p);
}
static inline __u64 __be64_to_cpup(const __be64 *p)
{
	return __swab64p((__u64 *)p);
}
static inline __be32 __cpu_to_be32p(const __u32 *p)
{
	return (__force __be32)__swab32p(p);
}
static inline __u32 __be32_to_cpup(const __be32 *p)
{
	return __swab32p((__u32 *)p);
}
static inline __be16 __cpu_to_be16p(const __u16 *p)
{
	return (__force __be16)__swab16p(p);
}
static inline __u16 __be16_to_cpup(const __be16 *p)
{
	return __swab16p((__u16 *)p);
}
#define __cpu_to_le64s(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __le64_to_cpus(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __cpu_to_le32s(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __le32_to_cpus(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __cpu_to_le16s(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __le16_to_cpus(x)                                                      \
	do {                                                                   \
		(void)(x);                                                     \
	} while (0)
#define __cpu_to_be64s(x) __swab64s((x))
#define __be64_to_cpus(x) __swab64s((x))
#define __cpu_to_be32s(x) __swab32s((x))
#define __be32_to_cpus(x) __swab32s((x))
#define __cpu_to_be16s(x) __swab16s((x))
#define __be16_to_cpus(x) __swab16s((x))

#define cpu_to_le64 __cpu_to_le64
#define le64_to_cpu __le64_to_cpu
#define cpu_to_le32 __cpu_to_le32
#define le32_to_cpu __le32_to_cpu
#define cpu_to_le16 __cpu_to_le16
#define le16_to_cpu __le16_to_cpu
#define cpu_to_be64 __cpu_to_be64
#define be64_to_cpu __be64_to_cpu
#define cpu_to_be32 __cpu_to_be32
#define be32_to_cpu __be32_to_cpu
#define cpu_to_be16 __cpu_to_be16
#define be16_to_cpu __be16_to_cpu
#define cpu_to_le64p __cpu_to_le64p
#define le64_to_cpup __le64_to_cpup
#define cpu_to_le32p __cpu_to_le32p
#define le32_to_cpup __le32_to_cpup
#define cpu_to_le16p __cpu_to_le16p
#define le16_to_cpup __le16_to_cpup
#define cpu_to_be64p __cpu_to_be64p
#define be64_to_cpup __be64_to_cpup
#define cpu_to_be32p __cpu_to_be32p
#define be32_to_cpup __be32_to_cpup
#define cpu_to_be16p __cpu_to_be16p
#define be16_to_cpup __be16_to_cpup
#define cpu_to_le64s __cpu_to_le64s
#define le64_to_cpus __le64_to_cpus
#define cpu_to_le32s __cpu_to_le32s
#define le32_to_cpus __le32_to_cpus
#define cpu_to_le16s __cpu_to_le16s
#define le16_to_cpus __le16_to_cpus
#define cpu_to_be64s __cpu_to_be64s
#define be64_to_cpus __be64_to_cpus
#define cpu_to_be32s __cpu_to_be32s
#define be32_to_cpus __be32_to_cpus
#define cpu_to_be16s __cpu_to_be16s
#define be16_to_cpus __be16_to_cpus


static inline void sync(void)
{
}

/*
 * Generic virtual read/write.  Note that we don't support half-word
 * read/writes.  We define __arch_*[bl] here, and leave __arch_*w
 * to the architecture specific code.
 */
#define __arch_getb(a) (*(volatile unsigned char *)(a))
#define __arch_getw(a) (*(volatile unsigned short *)(a))
#define __arch_getl(a) (*(volatile unsigned int *)(a))
#define __arch_getq(a) (*(volatile unsigned long long *)(a))

#define __arch_putb(v, a) (*(volatile unsigned char *)(a) = (v))
#define __arch_putw(v, a) (*(volatile unsigned short *)(a) = (v))
#define __arch_putl(v, a) (*(volatile unsigned int *)(a) = (v))
#define __arch_putq(v, a) (*(volatile unsigned long long *)(a) = (v))

static inline void __raw_writesb(unsigned long addr, const void *data,
				 int bytelen)
{
	uint8_t *buf = (uint8_t *)data;
	while (bytelen--)
		__arch_putb(*buf++, addr);
}

static inline void __raw_writesw(unsigned long addr, const void *data,
				 int wordlen)
{
	uint16_t *buf = (uint16_t *)data;
	while (wordlen--)
		__arch_putw(*buf++, addr);
}

static inline void __raw_writesl(unsigned long addr, const void *data,
				 int longlen)
{
	uint32_t *buf = (uint32_t *)data;
	while (longlen--)
		__arch_putl(*buf++, addr);
}

static inline void __raw_readsb(unsigned long addr, void *data, int bytelen)
{
	uint8_t *buf = (uint8_t *)data;
	while (bytelen--)
		*buf++ = __arch_getb(addr);
}

static inline void __raw_readsw(unsigned long addr, void *data, int wordlen)
{
	uint16_t *buf = (uint16_t *)data;
	while (wordlen--)
		*buf++ = __arch_getw(addr);
}

static inline void __raw_readsl(unsigned long addr, void *data, int longlen)
{
	uint32_t *buf = (uint32_t *)data;
	while (longlen--)
		*buf++ = __arch_getl(addr);
}

#define __raw_writeb(v, a) __arch_putb(v, a)
#define __raw_writew(v, a) __arch_putw(v, a)
#define __raw_writel(v, a) __arch_putl(v, a)
#define __raw_writeq(v, a) __arch_putq(v, a)

#define __raw_readb(a) __arch_getb(a)
#define __raw_readw(a) __arch_getw(a)
#define __raw_readl(a) __arch_getl(a)
#define __raw_readq(a) __arch_getq(a)

#define ISB asm volatile("isb sy" : : : "memory")
#define DSB asm volatile("dsb sy" : : : "memory")
#define DMB asm volatile("dmb sy" : : : "memory")

/*
 * TODO: The kernel offers some more advanced versions of barriers, it might
 * have some advantages to use them instead of the simple one here.
 */
#define mb() dsb()
#define __iormb() dmb()
#define __iowmb() dmb()

#define writeb(v, c)                                                           \
	({                                                                     \
		u8 __v = v;                                                    \
		__iowmb();                                                     \
		__arch_putb(__v, c);                                           \
		__v;                                                           \
	})
#define writew(v, c)                                                           \
	({                                                                     \
		u16 __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putw(__v, c);                                           \
		__v;                                                           \
	})
#define writel(v, c)                                                           \
	({                                                                     \
		u32 __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putl(__v, c);                                           \
		__v;                                                           \
	})
#define writeq(v, c)                                                           \
	({                                                                     \
		u64 __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putq(__v, c);                                           \
		__v;                                                           \
	})

#define readb(c)                                                               \
	({                                                                     \
		u8 __v = __arch_getb(c);                                       \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readw(c)                                                               \
	({                                                                     \
		u16 __v = __arch_getw(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readl(c)                                                               \
	({                                                                     \
		u32 __v = __arch_getl(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readq(c)                                                               \
	({                                                                     \
		u64 __v = __arch_getq(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})

/*
 * Relaxed I/O memory access primitives. These follow the Device memory
 * ordering rules but do not guarantee any ordering relative to Normal memory
 * accesses.
 */
#define readb_relaxed(c)                                                       \
	({                                                                     \
		u8 __r = __raw_readb(c);                                       \
		__r;                                                           \
	})
#define readw_relaxed(c)                                                       \
	({                                                                     \
		u16 __r = le16_to_cpu((__force __le16)__raw_readw(c));         \
		__r;                                                           \
	})
#define readl_relaxed(c)                                                       \
	({                                                                     \
		u32 __r = le32_to_cpu((__force __le32)__raw_readl(c));         \
		__r;                                                           \
	})
#define readq_relaxed(c)                                                       \
	({                                                                     \
		u64 __r = le64_to_cpu((__force __le64)__raw_readq(c));         \
		__r;                                                           \
	})

#define writeb_relaxed(v, c) ((void)__raw_writeb((v), (c)))
#define writew_relaxed(v, c)                                                   \
	((void)__raw_writew((__force u16)cpu_to_le16(v), (c)))
#define writel_relaxed(v, c)                                                   \
	((void)__raw_writel((__force u32)cpu_to_le32(v), (c)))
#define writeq_relaxed(v, c)                                                   \
	((void)__raw_writeq((__force u64)cpu_to_le64(v), (c)))

/*
 * The compiler seems to be incapable of optimising constants
 * properly.  Spell it out to the compiler in some cases.
 * These are only valid for small values of "off" (< 1<<12)
 */
#define __raw_base_writeb(val, base, off) __arch_base_putb(val, base, off)
#define __raw_base_writew(val, base, off) __arch_base_putw(val, base, off)
#define __raw_base_writel(val, base, off) __arch_base_putl(val, base, off)

#define __raw_base_readb(base, off) __arch_base_getb(base, off)
#define __raw_base_readw(base, off) __arch_base_getw(base, off)
#define __raw_base_readl(base, off) __arch_base_getl(base, off)

/*
 * Clear and set bits in one shot. These macros can be used to clear and
 * set multiple bits in a register using a single call. These macros can
 * also be used to set a multiple-bit bit pattern using a mask, by
 * specifying the mask in the 'clear' parameter and the new bit pattern
 * in the 'set' parameter.
 */

#define out_arch(type, endian, a, v) __raw_write##type(cpu_to_##endian(v), a)
#define in_arch(type, endian, a) endian##_to_cpu(__raw_read##type(a))

#define out_le64(a, v) out_arch(q, le64, a, v)
#define out_le32(a, v) out_arch(l, le32, a, v)
#define out_le16(a, v) out_arch(w, le16, a, v)

#define in_le64(a) in_arch(q, le64, a)
#define in_le32(a) in_arch(l, le32, a)
#define in_le16(a) in_arch(w, le16, a)

#define out_be32(a, v) out_arch(l, be32, a, v)
#define out_be16(a, v) out_arch(w, be16, a, v)

#define in_be32(a) in_arch(l, be32, a)
#define in_be16(a) in_arch(w, be16, a)

#define out_32(a, v) __raw_writel(v, a)
#define out_16(a, v) __raw_writew(v, a)
#define out_8(a, v) __raw_writeb(v, a)

#define in_32(a) __raw_readl(a)
#define in_16(a) __raw_readw(a)
#define in_8(a) __raw_readb(a)

#define clrbits(type, addr, clear)                                             \
	out_##type((addr), in_##type(addr) & ~(clear))

#define setbits(type, addr, set) out_##type((addr), in_##type(addr) | (set))

#define clrsetbits(type, addr, clear, set)                                     \
	out_##type((addr), (in_##type(addr) & ~(clear)) | (set))

#define clrbits_be32(addr, clear) clrbits(be32, addr, clear)
#define setbits_be32(addr, set) setbits(be32, addr, set)
#define clrsetbits_be32(addr, clear, set) clrsetbits(be32, addr, clear, set)

#define clrbits_le32(addr, clear) clrbits(le32, addr, clear)
#define setbits_le32(addr, set) setbits(le32, addr, set)
#define clrsetbits_le32(addr, clear, set) clrsetbits(le32, addr, clear, set)

#define clrbits_32(addr, clear) clrbits(32, addr, clear)
#define setbits_32(addr, set) setbits(32, addr, set)
#define clrsetbits_32(addr, clear, set) clrsetbits(32, addr, clear, set)

#define clrbits_be16(addr, clear) clrbits(be16, addr, clear)
#define setbits_be16(addr, set) setbits(be16, addr, set)
#define clrsetbits_be16(addr, clear, set) clrsetbits(be16, addr, clear, set)

#define clrbits_le16(addr, clear) clrbits(le16, addr, clear)
#define setbits_le16(addr, set) setbits(le16, addr, set)
#define clrsetbits_le16(addr, clear, set) clrsetbits(le16, addr, clear, set)

#define clrbits_16(addr, clear) clrbits(16, addr, clear)
#define setbits_16(addr, set) setbits(16, addr, set)
#define clrsetbits_16(addr, clear, set) clrsetbits(16, addr, clear, set)

#define clrbits_8(addr, clear) clrbits(8, addr, clear)
#define setbits_8(addr, set) setbits(8, addr, set)
#define clrsetbits_8(addr, clear, set) clrsetbits(8, addr, clear, set)

/*
 *  IO port access primitives
 *  -------------------------
 *
 * The ARM doesn't have special IO access instructions; all IO is memory
 * mapped.  Note that these are defined to perform little endian accesses
 * only.  Their primary purpose is to access PCI and ISA peripherals.
 *
 * Note that for a big endian machine, this implies that the following
 * big endian mode connectivity is in place, as described by numerous
 * ARM documents:
 *
 *    PCI:  D0-D7   D8-D15 D16-D23 D24-D31
 *    ARM: D24-D31 D16-D23  D8-D15  D0-D7
 *
 * The machine specific io.h include defines __io to translate an "IO"
 * address to a memory address.
 *
 * Note that we prevent GCC re-ordering or caching values in expressions
 * by introducing sequence points into the in*() definitions.  Note that
 * __raw_* do not guarantee this behaviour.
 *
 * The {in,out}[bwl] macros are for emulating x86-style PCI/ISA IO space.
 */

#define outb(v, p) __raw_writeb(v, __io(p))
#define outw(v, p) __raw_writew(cpu_to_le16(v), __io(p))
#define outl(v, p) __raw_writel(cpu_to_le32(v), __io(p))

#define inb(p)                                                                 \
	({                                                                     \
		unsigned int __v = __raw_readb(__io(p));                       \
		__v;                                                           \
	})
#define inw(p)                                                                 \
	({                                                                     \
		unsigned int __v = le16_to_cpu(__raw_readw(__io(p)));          \
		__v;                                                           \
	})
#define inl(p)                                                                 \
	({                                                                     \
		unsigned int __v = le32_to_cpu(__raw_readl(__io(p)));          \
		__v;                                                           \
	})

#define outsb(p, d, l) __raw_writesb(__io(p), d, l)
#define outsw(p, d, l) __raw_writesw(__io(p), d, l)
#define outsl(p, d, l) __raw_writesl(__io(p), d, l)

#define insb(p, d, l) __raw_readsb(__io(p), d, l)
#define insw(p, d, l) __raw_readsw(__io(p), d, l)
#define insl(p, d, l) __raw_readsl(__io(p), d, l)

#define outb_p(val, port) outb((val), (port))
#define outw_p(val, port) outw((val), (port))
#define outl_p(val, port) outl((val), (port))
#define inb_p(port) inb((port))
#define inw_p(port) inw((port))
#define inl_p(port) inl((port))

#define outsb_p(port, from, len) outsb(port, from, len)
#define outsw_p(port, from, len) outsw(port, from, len)
#define outsl_p(port, from, len) outsl(port, from, len)
#define insb_p(port, to, len) insb(port, to, len)
#define insw_p(port, to, len) insw(port, to, len)
#define insl_p(port, to, len) insl(port, to, len)

#define writesl(a, d, s) __raw_writesl((unsigned long)a, d, s)
#define readsl(a, d, s) __raw_readsl((unsigned long)a, d, s)
#define writesw(a, d, s) __raw_writesw((unsigned long)a, d, s)
#define readsw(a, d, s) __raw_readsw((unsigned long)a, d, s)
#define writesb(a, d, s) __raw_writesb((unsigned long)a, d, s)
#define readsb(a, d, s) __raw_readsb((unsigned long)a, d, s)


#endif /* __ASM_ARM_IO_H */

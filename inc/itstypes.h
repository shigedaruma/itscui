//
// title: itstypes.h
//
// author: Shigeyuki Itoh
// date: 20-05-02
//

// overview: 共通型定義ヘッダ
// description:
//  cygwin-gcc / x86_64-w64-mingw32-gcc のクロスコンパイル環境における
//  型に関する仕様の差分を吸収することを目的としたヘッダファイル

#ifndef ITSTYPES_H
#define ITSTYPES_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef double f64;

// cygwin-gcc
#ifdef CYGWIN_GCC

typedef signed long s64;
typedef unsigned long u64;

#define PI64d(...) "%" #__VA_ARGS__ "ld"
#define PI64u(...) "%" #__VA_ARGS__ "lu"
#define PI64X(...) "%" #__VA_ARGS__ "lX"
#define PI64x(...) "%" #__VA_ARGS__ "lx"

#endif

// x86_64-w64-mingw32-gcc
#ifdef W64_GCC

typedef signed long long s64;
typedef unsigned long long u64;

#define PI64d(...) "%" #__VA_ARGS__ "lld"
#define PI64u(...) "%" #__VA_ARGS__ "llu"
#define PI64X(...) "%" #__VA_ARGS__ "llX"
#define PI64x(...) "%" #__VA_ARGS__ "llx"

#endif

#define PSIZET(...) PI64u(__VA_ARGS__)

#endif // ITSTYPES_H

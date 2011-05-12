/*
 * Copyright (c) 1996-2011 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* Test application (Mutatee) */

/* $Id: test7.mutatee.c,v 1.8 2006/05/03 00:31:24 jodom Exp $ */

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <stdarg.h>

#if defined(i386_unknown_nt4_0) && !defined(__GNUC__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>
#define getpid _getpid
#else
#include <unistd.h>
#endif

#ifdef __cplusplus
int mutateeCplusplus = 1;
#else
int mutateeCplusplus = 0;
#endif

#ifndef COMPILER
#define COMPILER ""
#endif
const char *Builder_id=COMPILER; /* defined on compile line */

int debugPrint = 0;

/* control debug printf statements */
void dprintf(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);

   if(debugPrint)
      vfprintf(stderr, fmt, args);

   va_end(args);

   fflush(stderr);
}


#define TRUE    1
#define FALSE   0

int globalVariable7_1 = 123;
int globalVariable7_2 = 159;
int globalVariable7_3 = 246;
int globalVariable7_4 = 789;
int globalVariable7_5 = 7;
int globalVariable7_6 = 21;
int globalVariable7_7 = 1;
int globalVariable7_8 = 1;
int globalVariable7_9 = 1;
int dummyVal = 0;

void func7_1() { 
    dummyVal += 10;
    
}

void func7_2() { 
  dummyVal += 10;
}

void func7_3() { 
  dummyVal += 10;
}

void func7_4() { 
  dummyVal += 10;
}

void func7_5() { 
  dummyVal += 10;
}

void func7_6() { 
  dummyVal += 10;
}

void func7_7() { 
  dummyVal += 10;
}

void func7_8() { 
  dummyVal += 10;
}

void func7_9() { 
  dummyVal += 10;
}


void delay(int m) {
  int i,j;
  for(i=0; i<m; i++)
    for(j=0; j<m; j++) 
      ;
  assert(i>0 && j>0);
}

#define NUM_READS 9

void mutateeMAIN()
{
#if defined(i386_unknown_nt4_0)
  return;
#endif
  int pid;
  /* fprintf(stderr, "mutatee:  starting fork\n"); */
  pid = fork();
  /* fprintf(stderr, "mutatee:  stopping fork\n"); */

  /* mutatee will get paused here, temporarily, when the mutator receives
     the postForkCallback */

  if (pid == 0) {   /* child */
      dprintf("Child: starting tests\n");
      func7_1();
    func7_2();
    func7_3();
    func7_4();
    func7_5();
    func7_6();
    func7_7();
    func7_8();
    func7_9();
    dprintf("Child: done with tests, exiting\n");
  } else if(pid > 0) {
      dprintf("Parent: starting tests\n");
      func7_1();
    func7_2();
    func7_3();
    func7_4();
    func7_5();
    func7_6();
    func7_7();
    func7_8();
    func7_9();
    dprintf("Parent: done with tests, exiting\n");
  } else if(pid < 0) {
    fprintf(stderr, "error on fork\n");
    exit(pid);  /* error case */
  }
}

int main(int argc, char *argv[])
{                                       
    int i;

    for (i=1; i < argc; i++) {
      if (!strcmp(argv[i], "-verbose")) {
	debugPrint = TRUE;
      }
    }
    if(debugPrint) {
        printf("Mutatee %s [%s]:\"%s\"\n", argv[0], 
                mutateeCplusplus ? "C++" : "C", Builder_id);
    }
    mutateeMAIN();
    return 0;
}

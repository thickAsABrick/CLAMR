/*
 *  Copyright (c) 2011-2012, Los Alamos National Security, LLC.
 *  All rights Reserved.
 *
 *  Copyright 2011-2012. Los Alamos National Security, LLC. This software was produced 
 *  under U.S. Government contract DE-AC52-06NA25396 for Los Alamos National 
 *  Laboratory (LANL), which is operated by Los Alamos National Security, LLC 
 *  for the U.S. Department of Energy. The U.S. Government has rights to use, 
 *  reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR LOS 
 *  ALAMOS NATIONAL SECURITY, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR 
 *  ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is modified
 *  to produce derivative works, such modified software should be clearly marked,
 *  so as not to confuse it with the version available from LANL.
 *
 *  Additionally, redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Los Alamos National Security, LLC, Los Alamos 
 *       National Laboratory, LANL, the U.S. Government, nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE LOS ALAMOS NATIONAL SECURITY, LLC AND 
 *  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
 *  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LOS ALAMOS NATIONAL
 *  SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *  
 *  CLAMR -- LA-CC-11-094
 *  This research code is being developed as part of the 
 *  2011 X Division Summer Workshop for the express purpose
 *  of a collaborative code for development of ideas in
 *  the implementation of AMR codes for Exascale platforms
 *  
 *  AMR implementation of the Wave code previously developed
 *  as a demonstration code for regular grids on Exascale platforms
 *  as part of the Supercomputing Challenge and Los Alamos 
 *  National Laboratory
 *  
 *  Authors: Bob Robey       XCP-2   brobey@lanl.gov
 * 
 */
#ifndef MALLOCPLUS_H_
#define MALLOCPLUS_H_

#include <list>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_CL_DOUBLE
typedef double real;
#else
typedef float real;
#endif

#define REGULAR_MEMORY 0x00000
#define MANAGED_MEMORY 0x00001

using namespace std;

struct malloc_plus_memory_entry {
   void  *mem_ptr;
   size_t mem_capacity;
   size_t mem_nelem;
   size_t mem_elsize;
   int    mem_flags;
   char  *mem_name;
};

class MallocPlus {
   list<malloc_plus_memory_entry> memory_list;
   
public:
   void *memory_malloc(size_t nelem, size_t elsize, const char *name);
   void *memory_malloc(size_t nelem, size_t elsize, int flags, const char *name);

   void *memory_realloc(size_t nelem, size_t elsize, void *malloc_mem_ptr);
   void *memory_realloc(size_t nelem, size_t elsize, const char *name);

   void *memory_request(size_t nelem, size_t elsize, void *malloc_mem_ptr);
   void *memory_request(size_t nelem, size_t elsize, const char *name);

   void memory_realloc_all(size_t nelem);

   void memory_request_all(size_t nelem);

   void *memory_replace(void *malloc_mem_ptr_old, void * const malloc_mem_ptr_new);

   void *memory_add(void *malloc_mem_ptr, size_t nelem, size_t elsize, const char *name);
   void *memory_add(void *malloc_mem_ptr, size_t nelem, size_t elsize, int flags, const char *name);

   real *memory_reorder(real *malloc_mem_ptr, int *iorder);

   void memory_report(void);

   void memory_remove(void *malloc_mem_ptr);
   void memory_remove(const char *name);

   void *memory_begin(void);
   void *memory_next(void);

   size_t get_memory_size(void *malloc_mem_ptr);
   size_t get_memory_capacity(void *malloc_mem_ptr);

   void *get_memory_ptr(const char *name);
};

#endif // ifndef MALLOCPLUS_H_


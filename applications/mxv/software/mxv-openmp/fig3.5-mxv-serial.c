/*

   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

   Copyright 2009 Sun Microsystems, Inc. All rights reserved.

   The contents of this file are subject to the terms of the BSD License("BSD")(the "License"). 
   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt

   The BSD License

   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:

       * Redistribution of source code must retain the above copyright 
         notice, this list of conditions and the following disclaimer.
       * Redistribution in binary form must reproduce the above copyright 
         notice, this list of conditions and the following disclaimer in 
         the documentation and/or other materials provided with the 
         distribution.
       * Neither the name of Sun Microsystems, Inc. or the names of 
         contributors may be used to endorse or promote products derived 
         from this software without specific prior written permission.

   This software is provided "AS IS," without a warranty of any kind. ALL 
   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY 
   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND 
   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A 
   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. 
   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT 
   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR 
   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS 
   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   You acknowledge that this software is not designed, licensed or intended for 
   use in the design, construction, operation or maintenance of any nuclear facility. 

*/
#include "mxv.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define SOFTWARE_ITERATION 100


double software_start;
double software_end;
double software_execution_time;

double getTimestamp()
{
	struct timeval tv;
   	gettimeofday(&tv, NULL);
   	return tv.tv_usec + tv.tv_sec*1e6;
}
void mxv(int m, int n, float *  a,
         float *  b, float *  c);

int main(int argc, char *argv[])
{
   float *a,*b,*c;
   //volatile int i, j, m, n, k;
   int i, j, m, n, k;

   //   printf("Please give m and n: ");
   //   scanf("%d %d",&m,&n);
      n=2000;
      m=2000;
      printf("n=2000 m=2000\n");

   if ( (a=(float *)malloc(m*sizeof(float))) == NULL )
      perror("memory allocation for a");
   if ( (b=(float *)malloc(m*n*sizeof(float))) == NULL )
      perror("memory allocation for b");
   if ( (c=(float *)malloc(n*sizeof(float))) == NULL )
      perror("memory allocation for c");

   printf("Initializing matrix B and vector c\n");
   for (j=0; j<n; j++)
      c[j] = 2.0;
   for (i=0; i<m; i++)
      for (j=0; j<n; j++)
         b[i*n+j] = i;

   printf("Executing mxv function for m = %d n = %d\n",m,n);
   software_start = getTimestamp();
   for (i = 0; i < SOFTWARE_ITERATION; i++) {
	   (void) mxv(m, n, a, b, c);
   }
   software_end = getTimestamp();
   software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
   printf("software execution time  %.6lf ms elapsed\n", software_execution_time);


   software_start = getTimestamp();
   if(DELAY_FOR_POWER_MEASUREMENT != 1) {
	   printf("enter in huge iterations for manual power measurement\n");
	   for (j = 0; j < DELAY_FOR_POWER_MEASUREMENT; j++) {
		   for (k = 0; k < DELAY_FOR_POWER_MEASUREMENT; k++) {
			   mxv(m, n, a, b, c);
		   }
	   }
   }
   software_end = getTimestamp();
   software_execution_time = (software_end-software_start)/(SOFTWARE_ITERATION*1000);
   printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

   for (i=0; i<m; i++)
      for (j=0; j<n; j++)
    	  printf ("a[%d][%d]=%f, ", i, j, a[i*n+j]);


   free(a);free(b);free(c);
   return(0);
}

void mxv(int m, int n, float *  a, float *  b,
         float *  c)
{

   int i, j;
#pragma scop
   for (i=0; i<m; i++)  {
      a[i] = 0.0;
      for (j=0; j<n; j++)
         a[i] += b[i*n+j]*c[j];
   }
#pragma endscop
}

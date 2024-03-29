// Update the mixture coefficients

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "mixture.h"

void update_m
(
	double **x,        // sequence of feature vectors x[t][i]
	int dim,           // dimension of feature vectors
	int nFrames,       // number of feature vectors in x
	struct mixture *l, // GMMs 
	int nGaussians,    // number of Gaussians in the mixture
	double ***m1       // gaussian means m[nGaussians][dim]
)
{
	double **m;       // Gaussian means
	double *num, den, aux; // aux variables
    int i,j,t;          // counters
    	
    m = *m1;
	
	// Allocating memory
	num = malloc(sizeof(double)*dim);
		   
	// Updating Gaussian means
    for (i=0;i<nGaussians;i++)
    {
	//printf("gaussiana = %d\n",i);
    	den = 0.0;
    	for (j=0;j<dim;j++)
    		num[j] = 0.0;
    		
    	for (t=0;t<nFrames;t++)
    	{
        	aux = mixture(x[t],i,l,nGaussians,dim);
        	den += aux;
        	
        	for (j=0;j<dim;j++)
	      		num[j] += aux*x[t][j];

    	}
	//printf("den = %f\n",den);
    	for (j=0;j<dim;j++)
    		m[i][j] = num[j]/den;
    }
   
    // Freeing memory
    free (num);
    
    // Returning updated mean
    *m1 = m;
}

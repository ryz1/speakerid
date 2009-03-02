#include<stdio.h>
#include<stdlib.h>

#include "structs.h"
#include "showgmm.h"
#include "b.h"
#include "mixture.h"
#include "update_p.h"
#include "update_m.h"
#include "update_s.h"
#include "normrnd.h"
#include "testgmm.h"
#include "loadconfig.h"
#include "loadUtterances.h"

// comentatio

int main(int argc, char **argv)
{
	struct mixture *l; // stores the elements of the GMM
	int nGaussians=2; // number of gaussians in the mixture
	int nFrames=30000;    // number of frames in x
	int dim=2;        // dimension of feature vectors
	int i,j,t;            // counters
	double **x; // sequence of observation vectors
	double *p; // aux var to store the mixture coefficients during updating p[nGaussians]
	double **m; // aux var to store the Gaussian means during updating m[nGaussians][dim]
	double **s; // aux var to store the Gaussian variances during updating s[nGaussians][dim]
	int epoch;  // counter
	double dist,p_old, p_new; // aux variables for convergence verification
	char GMMFilename[512]; // file that will store the trained GMM
	char trainingUtterances[512]; // file with training utterances listing
	
    // Reading arguments passed to the program
    if(argc != 2)
    {
    	puts("\nUsage: gmm config.txt\n");
    	puts("where config.txt is a configuration file of the form:\n");
    	puts("Number of Gaussians=2");
    	puts("Dimension of feature vectors=2");
    	puts("Output filename=gmm1.dat");
    	puts("Training utterances=names.txt\n");
    	puts("IMPORTANT: LEAVE A BLANK LINE AT THE END OF CONFIGURATION FILE!!!\n");
    	return 1;
    }
	else
		loadconfig(argv[1],&nGaussians,&dim,GMMFilename,trainingUtterances);

	puts("Configuration settings:\n");
	printf("Configuration file: %s\n",argv[1]);
	printf("Number of Gaussians in the mixture: %d\n",nGaussians);
	printf("Dimension of feature vectors: %d\n",dim);
	printf("Output file: %s\n",GMMFilename);
	printf("File with training utterances: %s\n\n",trainingUtterances);
	
	// Allocating memory
	l = malloc(sizeof(struct mixture)*nGaussians);
	for (i=0;i<nGaussians;i++)
	{
	  l[i].m = malloc(sizeof(double)*dim);
	  l[i].s = malloc(sizeof(double)*dim);
	}
	p = malloc(sizeof(double)*dim);
	m = malloc(sizeof(double *)*nGaussians);
	for (i=0;i<nGaussians;i++)
		m[i] = malloc(sizeof(double)*dim);
	s = malloc(sizeof(double *)*nGaussians);
	for (i=0;i<nGaussians;i++)
		s[i] = malloc(sizeof(double)*dim);
/*
	x = malloc(sizeof(double *)*nFrames);
	for (t=0;t<nFrames;t++)
	  x[t] = malloc(sizeof(double)*dim);
*/	
	// Initializing variables
	for (i=0;i<nGaussians;i++)
	{	
		l[i].p = 1.0/nGaussians;
		for (j=0;j<dim;j++)
		{
			l[i].m[j] = normrnd(1,2);
			l[i].s[j] = 1.0;
		}
	}
	
	// Reading training utterances
	loadUtterances(trainingUtterances,dim,&nFrames,&x);
	
	for (t=0;t<nFrames/2;t++)
	    for(i=0;i<dim;i++)
	        printf("%f\t",x[t][i]);
	    puts(" ");
/*	
	for (t=0;t<nFrames/2;t++)
	{
		x[t][0] = normrnd(1,1);
		x[t][1] = normrnd(3,1);
	}	
	for (t=nFrames/2;t<nFrames;t++)
	{
		x[t][0] = normrnd(5,1);
		x[t][1] = normrnd(7,1);
	}
*/		
	// Training models
	p_old = -INF;
	dist = 1.0;
	epoch = 0;
	while(dist > 0.001)
	{
	    // Updating mixture coefficients
	    update_p(x,dim,nFrames,l,nGaussians,p);	
	    
		// Updating gaussian means
		update_m(x,dim,nFrames,l,nGaussians,&m);
	   
	    // Updating gaussian variances
	    update_s(x,dim,nFrames,l,nGaussians,m,&s);
	    
	    // Copying updated values for the model
	    for (i=0;i<nGaussians;i++)
	    {
	    	l[i].p = p[i];
	    	for (j=0;j<dim;j++)
	    	{
	    		l[i].m[j] = m[i][j];
	    		l[i].s[j] = s[i][j];
	    	}
	    }
	    
	    // Verifying convergence
	    p_new = testgmm(x,dim,nFrames,l,nGaussians);
	    dist = -(p_new-p_old)/p_new;
	    
		// Showing results
		printf("Results after %d training epochs.\n",epoch+1);
		printf("P(X|M) = %f\n",p_new);
		printf("distortion: %f\n\n",dist);
		
		// Updating p_old for the next training epoch
		p_old = p_new;
		epoch++;		
		//showgmm(l,nGaussians,dim); 
		
	}
	
	// Deallocating memory
	for (i=0;i<nGaussians;i++)
	{
	  free(l[i].m);
	  free(l[i].s);
	}
	free(l);
	for (t=0;t<nFrames;t++)
	  free(x[t]);
	free(x);
	free(p);  
	for (i=0;i<nGaussians;i++)
		free(m[i]);
	free(m);
	for (i=0;i<nGaussians;i++)
		free(s[i]);
	free(s);
		
	return 0;
}
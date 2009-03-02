#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int loadUtterances
(
	char *trainingUtterances, // file with the training utterances listing
	int dim,                  // dimension of feature vectors
	int *nFrames1,   		  // total number of read frames
	double ***x1              // stores the utterances
)
{
	FILE *ptr,*ptr1; // file handlers
	char data[512];  // aux variable for file reading
	int size;        // size of each utterance file, in bytes
	double **x;      // stores the utterances
	int nFrames;     // total number of read frames
	int i, frame;           // counters
	
	// Counting the total number of frames
	nFrames = 0;
	
	// Opening utterances file
  	ptr = fopen(trainingUtterances,"rt");
	
  	if (ptr == NULL)
  	{
		printf("Error opening file %s.\n",trainingUtterances);
		return 1;
  	}
	
  	// Reading information
  	fgets(data, 500, ptr);
  	
  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

  	while (!feof(ptr))
  	{
  		// Opening file for reading
  		ptr1=fopen(data,"rb");
  		fseek (ptr1 , 0 , SEEK_END);
        size = ftell (ptr1);
        fclose(ptr1);

  	    nFrames += size/12/sizeof(double);	
  		
  		// Reading new entry from file
		if (!feof(ptr))
			fgets(data, 500, ptr);
		//fscanf(ptr,"%s",data);
		
  		// removing control characters (\r \n) frm the end of string
		while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
			data[strlen(data)-1] = '\0';
  	} // end of utterances file reading
  	
  	// Allocating memory
  	x = malloc(sizeof(double *)*dim);
  	for (i=0;i<dim;i++)
  		x[i] = malloc(sizeof(double)*nFrames);
  	
  	// Reading utterances
  	rewind(ptr);

  	// Reading information
  	fgets(data, 500, ptr);
  	
  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

	frame = 0;
  	while (!feof(ptr))
  	{
  		// Opening file for reading
  		ptr1=fopen(data,"rb");
  		while(!feof(ptr1))
  			fread(x[frame],sizeof(double),dim,ptr1);
        fclose(ptr1);

  		// Reading new entry from file
		if (!feof(ptr))
			fgets(data, 500, ptr);
		//fscanf(ptr,"%s",data);
		
  		// removing control characters (\r \n) frm the end of string
		while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
			data[strlen(data)-1] = '\0';
  	} // end of utterances file reading

	*nFrames1 = nFrames;
	*x1 = x;  	
  	
  	fclose(ptr);
  	return 0;
}

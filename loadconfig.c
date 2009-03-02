// Loads the training setup from a configuration file

#include <stdio.h>
#include <string.h>

int loadconfig
(
  char *configFile,
  int *nGaussians,
  int *dim,
  char *GMMFilename,
  char *trainingUtterances
)
{
	// Local variables
  	FILE *ptr; // file handler
  	char data[512]; // aux variables for file reading

  	// Opening configuration file
  	ptr = fopen(configFile,"rt");
	
  	if (ptr == NULL)
  	{
		printf("Error opening file %s.\n",configFile);
		return 1;
  	}
	
  	// Reading informations
  	fgets(data, 500, ptr);

  	// removing control characters (\r \n) frm the end of string
  	while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
  		data[strlen(data)-1] = '\0';

  	while (!feof(ptr))
  	{
  		// Number of Gaussians in the mixture
        if (strstr(data,"Number of Gaussians=") != NULL)
	  		sscanf(data,"Number of Gaussians=%d",nGaussians);

		// Dimension of feature vectors
		if (strstr(data,"Dimension of feature vectors=") != NULL)
	  		sscanf(data,"Dimension of feature vectors=%d",dim);
	  		
		// Output filename
    	if (strstr(data,"Output filename=") != NULL)
	  		sscanf(data,"Output filename=%s",GMMFilename);
	  		
		// File with training utterances files listing
    	if (strstr(data,"Training utterances") != NULL)
	  		sscanf(data,"Training utterances=%s",trainingUtterances);
	
		// Reading new entry from file
		if (!feof(ptr))
			fgets(data, 500, ptr);
		//fscanf(ptr,"%s",data);
		
  		// removing control characters (\r \n) frm the end of string
		while (data[strlen(data)-1]=='\r' || data[strlen(data)-1]=='\n')
			data[strlen(data)-1] = '\0';
	} // end of configuration file reading

	fclose(ptr);
	
	printf("inside: %s\n",GMMFilename);
	printf("inside: %s\n",trainingUtterances);
		
  return (0);
}

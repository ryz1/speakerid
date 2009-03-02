#ifndef LOADCONFIG_H_
#define LOADCONFIG_H_

int loadconfig
(
  char *configFile,
  int *nGaussians,
  int *dim,
  char *GMMFilename,
  char *trainingUtterances
);

#endif /*LOADCONFIG_H_*/

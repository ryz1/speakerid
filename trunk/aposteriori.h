#ifndef APOSTERIORI_H_
#define APOSTERIORI_H_

// Calculate the a posteriori probabilities
double aposteriori
(
  double *x,         // feature vector
  int i,             // id of Gaussian under analysis
  struct mixture *l, // GMM models
  int nGaussians,    // number of Gaussians in the mixture
  int dim            // dimension of the acoustic vectors
);

#endif /*APOSTERIORI_H_*/

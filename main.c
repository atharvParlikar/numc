#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float *data;
  int ndim;
  size_t *shape;
  size_t items;
  size_t itemsize;
} ndarray;

// every float is 32 bit
ndarray Ndarray(size_t *shape, int ndim) {
  ndarray x;
  int items = 1;
  for (int i = 0; i < ndim; i++) {
    items *= shape[i];
  }
  x.items = items;
  x.data = (float *)malloc(items * sizeof(float));
  x.shape = shape;
  x.ndim = ndim;
  x.itemsize = 32; // (4 byte | 32 bit) floats
  return x;
}

int get_linear_index(size_t *shape, int *indices, int ndim) {
  int linear_index = 0;

  for (int i = 0; i < ndim - 1; i++) {
    linear_index += indices[i] * shape[ndim - i];
  }
  linear_index += indices[ndim];
  return linear_index;
}

float *get_element(ndarray *ndarr, int *indices, int indices_size) {
  if (ndarr->ndim == indices_size) {
    float element =
        ndarr->data[get_linear_index(ndarr->shape, indices, indices_size)];
    float *returning_element = (float *)malloc(sizeof(float));
    returning_element = (float[]){element};
    return returning_element;
  } else {
    if (indices_size > ndarr->ndim) {
      fprintf(stderr, "Index dimensions do not match with ndarray\n");
      exit(1);
    } else { // because of previous conditions this just means
             // index_dimensions < ndim
      //  TODO: Figure out array substringing without copying to allow in memory
      //        array change.
      return (float *)malloc(sizeof(float));
    }
  }
}

void set_element(ndarray *ndarr, int *indices, float value) {
  int index = get_linear_index(ndarr->shape, indices, ndarr->ndim);
  ndarr->data[index] = value;
}

void flatten(ndarray *ndarr) {
  ndarr->ndim = 1;
  ndarr->shape = (size_t[]){1};
}

int main() {
  ndarray x = Ndarray((size_t[]){3, 3, 2}, 3);
  x.data[3] = 69;
  for (int i = 0; i < x.items; i++) {
    printf("%f\n", x.data[i]);
  }
  int indices[3] = {0, 1, 0};
  float *element = get_element(&x, indices, 4);
  printf("Retrieved Element: %f\n", element[0]);
  set_element(&x, indices, 70);
  element = get_element(&x, indices, 3);
  printf("Changed Element: %f\n", element[0]);
  return 0;
}

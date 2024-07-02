#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float *data;
  int ndim;
  size_t *shape;
  size_t *strides;
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
  x.itemsize = 4; // (4 byte | 32 bit) floats
  x.strides = malloc((ndim - 1) * sizeof(float));
  for (int i = 1; i < x.ndim; i++) {
    int stride = 1;
    for (int j = i; j < x.ndim; j++) {
      stride *= x.shape[j];
    }
    x.strides[i - 1] = stride;
  }

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

ndarray get_element(ndarray *ndarr, int *indices, int indices_size) {
  if (ndarr->ndim == indices_size) {
    float element =
        ndarr->data[get_linear_index(ndarr->shape, indices, indices_size)];

    ndarray returning_element = Ndarray((size_t[]){1}, 1);
    returning_element.data[0] = element;

    return returning_element;
  } else {
    if (indices_size > ndarr->ndim) {
      fprintf(stderr, "Index dimensions do not match with ndarray\n");
      exit(1);
    } else { // because of previous conditions this just means
             // index_dimensions < ndim
      //  TODO: Figure out array subscripting without copying to allow in memory
      //        array change.

      int x = ndarr->ndim - indices_size;
      size_t size = 1;

      for (int i = x; i < ndarr->ndim; i++) {
        size *= ndarr->shape[i];
      }

      float *data = (float *)malloc(size * sizeof(float));
      int start_index = 0;
      int ndim = ndarr->ndim - indices_size;
      size_t *shape = (size_t *)malloc(ndim * sizeof(size_t));

      int count = 0;
      for (int i = ndim; i < ndarr->ndim; i++) {
        shape[count++] = ndarr->shape[i];
      }

      for (int i = 0; i < indices_size; i++) {
        start_index += indices[i] * ndarr->strides[i];
      }

      printf("Start Index: %d\n", start_index);
      count = 0;
      for (int i = start_index;
           i < start_index + ndarr->strides[indices_size - 1]; i++) {
        data[count++] = ndarr->data[i];
      }

      ndarray subarr = Ndarray(shape, ndim);
      subarr.data = data;

      return subarr;
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
  ndarray x = Ndarray((size_t[]){3, 3, 3}, 3);

  for (int i = 3; i < 6; i++) {
    x.data[i] = 1.0f;
  }
  for (int i = 0; i < x.items; i++) {
    printf("%f\n", x.data[i]);
  }

  printf("========================\n");

  ndarray element = get_element(&x, (int[]){1}, 1);

  for (int i = 0; i < element.ndim; i++) {
    printf("%zu ", element.shape[i]);
  }

  printf("\n");

  return 0;
}

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
    } else { // index_dimensions < ndim
      //  TODO: Figure out array subscripting without copying to allow in memory
      //        array change.

      int start_index = 0;
      int ndim = ndarr->ndim - indices_size;
      size_t *shape = (size_t *)malloc(ndim * sizeof(size_t));

      int count = 0;
      for (int i = ndim - 1; i < ndarr->ndim; i++) {
        shape[count++] = ndarr->shape[i];
      }

      int size = 1;
      for (int i = 0; i < ndim; i++) {
        size *= shape[i];
      }

      float *data = (float *)malloc(size * sizeof(float));

      for (int i = 0; i < indices_size; i++) {
        start_index += indices[i] * ndarr->strides[i];
      }

      printf("start index: %d\n", start_index);
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

ndarray add(ndarray *arr1, ndarray *arr2) {
  if (arr1->ndim != arr2->ndim) {
    perror("dimensions are not the same of both the arrays");
    exit(1);
  }

  for (int i = 0; i < arr1->ndim; i++) {
    if (arr1->shape[i] != arr2->shape[i]) {
      perror("ndarray shapes are uncompatable");
    }
  }

  size_t *shape = (size_t *)malloc(arr1->ndim * sizeof(size_t));
  for (int i = 0; i < arr1->ndim; i++) {
    shape[i] = arr1->shape[i];
  }

  ndarray arr3 = Ndarray(shape, arr1->ndim);
  for (int i = 0; i < arr1->items; i++) {
    arr3.data[i] = arr1->data[i] + arr2->data[i];
  }

  return arr3;
}

ndarray sub(ndarray *arr1, ndarray *arr2) {
  if (arr1->ndim != arr2->ndim) {
    perror("dimensions are not the same of both the arrays");
    exit(1);
  }

  for (int i = 0; i < arr1->ndim; i++) {
    if (arr1->shape[i] != arr2->shape[i]) {
      perror("ndarray shapes are uncompatable");
    }
  }

  size_t *shape = (size_t *)malloc(arr1->ndim * sizeof(size_t));
  for (int i = 0; i < arr1->ndim; i++) {
    shape[i] = arr1->shape[i];
  }

  ndarray arr3 = Ndarray(shape, arr1->ndim);
  for (int i = 0; i < arr1->items; i++) {
    arr3.data[i] = arr1->data[i] - arr2->data[i];
  }

  return arr3;
}

ndarray mul(ndarray *arr1, ndarray *arr2) {
  if (arr1->ndim != arr2->ndim) {
    perror("encounterd incompatible shapes while multiplying ndarrays\n");
    exit(1);
  }

  for (int i = 0; i < arr1->ndim; i++) {
    if (arr1->shape[i] != arr2->shape[i]) {
      perror("Shapes of ndarray not equal while multiplying\n");
      exit(1);
    }
  }
  // by this point shapes of both the arrays are exactly the same.

  size_t *shape = (size_t *)malloc(arr1->ndim * sizeof(size_t));
  for (int i = 0; i < arr1->ndim; i++) {
    shape[i] = arr1->shape[i];
  }

  ndarray arr3 = Ndarray(shape, arr1->ndim);

  for (int i = 0; i < arr1->items; i++) {
    arr3.data[i] = arr1->data[i] * arr2->data[i];
  }
  return arr3;
}

//  TODO:  Instead of taking value as float, take value as ndarray or
//         make a seprate function for that for convineance.
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
  ndarray y = Ndarray((size_t[]){3, 3, 3}, 3);

  for (int i = 3; i < 6; i++) {
    x.data[i] = 1.0f;
  }

  ndarray z = add(&x, &y);

  printf("==========================\n");

  for (int i = 0; i < z.items; i++) {
    printf("%f\n", z.data[i]);
  }

  return 0;
}

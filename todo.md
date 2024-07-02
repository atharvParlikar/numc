**Attributes:**

1. `ndim`: The number of dimensions in the array.
2. `shape`: A tuple representing the shape of the array (number of elements in each dimension).
3. `size`: The total number of elements in the array.
4. `dtype`: The data type of the array (e.g., `int64`, `float64`, etc.).
5. `itemsize`: The size of each element in bytes.
6. `nbytes`: The total number of bytes used by the array.
7. `flags`: Information about the array's memory layout (e.g., C-contiguous, F-contiguous, etc.).

**Basic Methods:**

1. `reshape(newshape)`: Reshapes the array to a new shape without changing its data.
2. `flatten()`: Returns a 1-D iterator over the array.
3. `ravel()`: Returns a flattened 1-D array.
4. `transpose(*axes)`: Returns a transposed array with the specified axes.
5. `swapaxes(axis1, axis2)`: Swaps the specified axes.
6. `flatten(order='C')`: Returns a flattened 1-D array with the specified order (C or F).
7. `squeeze()`: Removes single-dimensional entries from the shape.
8. `astype(dtype)`: Returns a new array with the specified data type.
9. `copy()`: Returns a copy of the array.
10. `view(dtype)`: Returns a new array with the same data but a different data type.

**Indexing and Slicing:**

1. `__getitem__(index)`: Returns a subset of the array based on the index.
2. `__setitem__(index, value)`: Sets a subset of the array to the specified value.
3. `__delitem__(index)`: Deletes a subset of the array.

**Mathematical Operations:**

1. `__add__(other)`: Element-wise addition.
2. `__sub__(other)`: Element-wise subtraction.
3. `__mul__(other)`: Element-wise multiplication.
4. `__truediv__(other)`: Element-wise division.
5. `__pow__(other)`: Element-wise exponentiation.
6. `dot(other)`: Matrix multiplication.
7. `sum(axis=None)`: Returns the sum of the array along the specified axis.
8. `mean(axis=None)`: Returns the mean of the array along the specified axis.
9. `std(axis=None)`: Returns the standard deviation of the array along the specified axis.
10. `min(axis=None)`: Returns the minimum value of the array along the specified axis.
11. `max(axis=None)`: Returns the maximum value of the array along the specified axis.

**Other Methods:**

1. `fill(value)`: Fills the array with the specified value.
2. `sort(axis=-1)`: Sorts the array along the specified axis.
3. `argsort(axis=-1)`: Returns the indices of the sorted array along the specified axis.
4. `searchsorted(value)`: Returns the indices where the specified value can be inserted to maintain sorted order.
5. `clip(min, max)`: Clips the array values to the specified range.

This is not an exhaustive list, but it covers many of the basic methods and attributes of a NumPy `ndarray` object.

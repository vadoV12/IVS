## Automated Tests (Google Test)

This part of the project focuses on **automated testing** using the **Google Test** framework.
It contains three independent test suites that verify correctness and robustness of individual data structures
and algorithms using different testing approaches.

---

## Black Box Tests – Red-Black Tree

**File:** `black_box_tests.cpp`  
**Tested module:** `red_black_tree.h`

### Description
Black-box tests validate the **public interface** of the Red-Black Tree without relying on internal implementation details.

### Tested functionality
- `InsertNode`
- `DeleteNode`
- `FindNode`

### Test scenarios
- Operations on an **empty tree**
- Operations on a **non-empty tree**
- Insertion of duplicate values
- Deletion of existing and non-existing nodes

### Red-Black Tree axioms verification
The following Red-Black Tree properties are tested:
1. **All leaf nodes are always black**
2. **A red node has only black children**
3. **All paths from a leaf to the root contain the same number of black nodes**

---
## White Box Tests – Hash Map

**File:** `white_box_tests.cpp`  
**Tested module:** `white_box_code.h`

### Description
White-box tests verify both **public behavior** and **internal structure**
of a hash map implementation.

### Tested functionality
- `hash_map_ctor`, `hash_map_dtor`
- `hash_map_put`
- `hash_map_get`
- `hash_map_remove`
- `hash_map_pop`
- `hash_map_clear`
- `hash_map_reserve`
- `hash_map_size`
- `hash_map_capacity`
- `hash_map_contains`

### Edge cases and internal behavior
- Handling of hash collisions
- Different keys mapped to the same hash value
- Reallocation during reserve operation
- Correct behavior after deletion and popping
- Boundary conditions for capacity and memory errors

---

## Technologies Used

- **C++**
- **Google Test (gtest, gmock)**
- STL containers (`vector`, `set`, `stringstream`)

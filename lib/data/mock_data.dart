/// Mock DSA data for the revision app
/// 
/// ⚠️ DEPRECATED: This file is no longer used in the app.
/// The app now loads real DSA content from the dsa/dsa_folder/ directory.
/// See lib/data/dsa_loader.dart for the new implementation.
/// 
/// This file is kept for reference and backward compatibility.
library;

final List<Map<String, String>> dsaNotes = [
  {
    "title": "Arrays",
    "content": """# Arrays

Arrays are contiguous memory data structures that store elements of the same type.

## Key Properties
- Fixed size (in most languages)
- O(1) random access
- O(n) insertion/deletion (except at end)

## Common Operations
- Access: `arr[i]`
- Traverse: `for (int i = 0; i < n; i++)`
- Search: Linear O(n) or Binary O(log n) if sorted

## Use Cases
- When you need fast random access
- When size is known in advance
- Implementing other data structures (stacks, queues)
"""
  },
  {
    "title": "Strings",
    "content": """# Strings

Strings are sequences of characters, typically immutable in most languages.

## Key Properties
- Immutable (in Java, Python, etc.)
- Character array under the hood
- O(n) concatenation in immutable strings

## Common Operations
- Length: `str.length()`
- Substring: `str.substring(start, end)`
- Concatenation: `str1 + str2`
- Comparison: `str1.equals(str2)`

## Common Patterns
- Two pointers
- Sliding window
- String matching (KMP, Rabin-Karp)

## Use Cases
- Text processing
- Pattern matching
- Parsing
"""
  },
  {
    "title": "Linked List",
    "content": """# Linked List

A linked list is a linear data structure where elements are stored in nodes, each pointing to the next node.

## Types
- Singly Linked List
- Doubly Linked List
- Circular Linked List

## Key Properties
- Dynamic size
- O(1) insertion/deletion at known position
- O(n) random access

## Node Structure
```
class Node {
    int data;
    Node next;
}
```

## Common Operations
- Insert at head: O(1)
- Insert at tail: O(n) or O(1) with tail pointer
- Delete: O(n) to find, O(1) to remove
- Traverse: O(n)

## Use Cases
- When frequent insertions/deletions needed
- When size is unknown
- Implementing stacks, queues, graphs
"""
  }
];

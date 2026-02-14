# Data Structures and Their Operations

## 1. Array
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Access | O(1) | Access element by index |
| Search | O(n) | Linear search |
| Insert (end) | O(1) | Append element |
| Insert (middle) | O(n) | Shift elements |
| Delete (end) | O(1) | Remove last |
| Delete (middle) | O(n) | Shift elements |
| Update | O(1) | Update by index |

---

## 2. Linked List (Singly)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Access | O(n) | Traverse to index |
| Search | O(n) | Linear search |
| Insert (head) | O(1) | Add at beginning |
| Insert (tail) | O(n) / O(1)* | Add at end (*with tail pointer) |
| Insert (middle) | O(n) | Find position + insert |
| Delete (head) | O(1) | Remove first |
| Delete (tail) | O(n) | Traverse to second-last |
| Delete (middle) | O(n) | Find + remove |
| Reverse | O(n) | Reverse the list |

---

## 3. Doubly Linked List
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Access | O(n) | Traverse from head/tail |
| Search | O(n) | Linear search |
| Insert (head) | O(1) | Add at beginning |
| Insert (tail) | O(1) | Add at end |
| Insert (middle) | O(n) | Find position + insert |
| Delete (head) | O(1) | Remove first |
| Delete (tail) | O(1) | Remove last |
| Delete (middle) | O(n) | Find + remove |
| Traverse forward | O(n) | Head to tail |
| Traverse backward | O(n) | Tail to head |

---

## 4. Stack (LIFO)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Push | O(1) | Add to top |
| Pop | O(1) | Remove from top |
| Peek/Top | O(1) | View top element |
| isEmpty | O(1) | Check if empty |
| Size | O(1) | Get count |

---

## 5. Queue (FIFO)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Enqueue | O(1) | Add to rear |
| Dequeue | O(1) | Remove from front |
| Front/Peek | O(1) | View front element |
| Rear | O(1) | View rear element |
| isEmpty | O(1) | Check if empty |
| Size | O(1) | Get count |

---

## 6. Circular Queue
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Enqueue | O(1) | Add to rear |
| Dequeue | O(1) | Remove from front |
| Front | O(1) | View front |
| Rear | O(1) | View rear |
| isFull | O(1) | Check if full |
| isEmpty | O(1) | Check if empty |

---

## 7. Deque (Double-Ended Queue)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| InsertFront | O(1) | Add at front |
| InsertRear | O(1) | Add at rear |
| DeleteFront | O(1) | Remove from front |
| DeleteRear | O(1) | Remove from rear |
| GetFront | O(1) | View front |
| GetRear | O(1) | View rear |

---

## 8. Priority Queue
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(log n) | Add with priority |
| ExtractMax/Min | O(log n) | Remove highest/lowest priority |
| Peek | O(1) | View highest/lowest priority |
| ChangePriority | O(log n) | Update priority |
| Delete | O(log n) | Remove specific element |

---

## 9. Hash Table / HashMap
| Operation | Average | Worst | Description |
|-----------|---------|-------|-------------|
| Insert | O(1) | O(n) | Add key-value |
| Search | O(1) | O(n) | Find by key |
| Delete | O(1) | O(n) | Remove by key |
| Update | O(1) | O(n) | Update value |
| ContainsKey | O(1) | O(n) | Check key exists |
| GetKeys | O(n) | O(n) | Get all keys |
| GetValues | O(n) | O(n) | Get all values |

---

## 10. HashSet
| Operation | Average | Worst | Description |
|-----------|---------|-------|-------------|
| Add | O(1) | O(n) | Insert element |
| Remove | O(1) | O(n) | Delete element |
| Contains | O(1) | O(n) | Check existence |
| Size | O(1) | O(1) | Get count |
| Union | O(n) | O(n) | Combine sets |
| Intersection | O(n) | O(n) | Common elements |
| Difference | O(n) | O(n) | Elements in A not in B |

---

## 11. Binary Tree
| Operation | Average | Worst | Description |
|-----------|---------|-------|-------------|
| Insert | O(log n) | O(n) | Add node |
| Search | O(log n) | O(n) | Find node |
| Delete | O(log n) | O(n) | Remove node |
| Inorder Traversal | O(n) | O(n) | Left-Root-Right |
| Preorder Traversal | O(n) | O(n) | Root-Left-Right |
| Postorder Traversal | O(n) | O(n) | Left-Right-Root |
| Level Order | O(n) | O(n) | BFS traversal |
| Height | O(n) | O(n) | Find tree height |
| Count Nodes | O(n) | O(n) | Total nodes |

---

## 12. Binary Search Tree (BST)
| Operation | Average | Worst | Description |
|-----------|---------|-------|-------------|
| Insert | O(log n) | O(n) | Add node |
| Search | O(log n) | O(n) | Find node |
| Delete | O(log n) | O(n) | Remove node |
| FindMin | O(log n) | O(n) | Leftmost node |
| FindMax | O(log n) | O(n) | Rightmost node |
| Successor | O(log n) | O(n) | Next larger |
| Predecessor | O(log n) | O(n) | Next smaller |
| Validate BST | O(n) | O(n) | Check if valid |

---

## 13. AVL Tree (Self-Balancing BST)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(log n) | Add + rebalance |
| Search | O(log n) | Find node |
| Delete | O(log n) | Remove + rebalance |
| Left Rotation | O(1) | Balance operation |
| Right Rotation | O(1) | Balance operation |
| Get Balance Factor | O(1) | Height difference |

---

## 14. Red-Black Tree
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(log n) | Add + fix violations |
| Search | O(log n) | Find node |
| Delete | O(log n) | Remove + fix violations |
| Recolor | O(1) | Change node color |
| Rotation | O(1) | Left/Right rotation |

---

## 15. Heap (Min/Max)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(log n) | Add + heapify up |
| ExtractMin/Max | O(log n) | Remove root + heapify down |
| Peek | O(1) | View root |
| Heapify | O(log n) | Restore heap property |
| Build Heap | O(n) | Create heap from array |
| Delete | O(log n) | Remove specific element |
| Increase/Decrease Key | O(log n) | Update priority |

---

## 16. Trie (Prefix Tree)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(m) | Add word (m = word length) |
| Search | O(m) | Find exact word |
| StartsWith | O(m) | Check prefix exists |
| Delete | O(m) | Remove word |
| AutoComplete | O(m + k) | Get suggestions (k = results) |
| CountWords | O(n) | Total words |
| CountPrefix | O(m) | Words with prefix |

---

## 17. Graph
| Operation | Adjacency List | Adjacency Matrix | Description |
|-----------|----------------|------------------|-------------|
| Add Vertex | O(1) | O(V²) | Add node |
| Add Edge | O(1) | O(1) | Add connection |
| Remove Vertex | O(V + E) | O(V²) | Delete node |
| Remove Edge | O(E) | O(1) | Delete connection |
| Check Edge | O(V) | O(1) | Edge exists? |
| Get Neighbors | O(degree) | O(V) | Adjacent nodes |
| BFS | O(V + E) | O(V²) | Breadth-first search |
| DFS | O(V + E) | O(V²) | Depth-first search |
| Dijkstra | O((V+E)log V) | O(V²) | Shortest path |
| Bellman-Ford | O(V × E) | O(V³) | Shortest path (neg weights) |
| Floyd-Warshall | O(V³) | O(V³) | All pairs shortest path |
| Topological Sort | O(V + E) | O(V²) | DAG ordering |
| Detect Cycle | O(V + E) | O(V²) | Find cycles |
| Kruskal's MST | O(E log E) | O(E log E) | Minimum spanning tree |
| Prim's MST | O((V+E)log V) | O(V²) | Minimum spanning tree |

---

## 18. Segment Tree
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Build | O(n) | Create tree |
| Query | O(log n) | Range query |
| Update | O(log n) | Point update |
| Range Update | O(log n) | Lazy propagation |

---

## 19. Fenwick Tree (Binary Indexed Tree)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Build | O(n log n) | Create tree |
| Point Update | O(log n) | Update single element |
| Prefix Sum | O(log n) | Sum from 0 to i |
| Range Sum | O(log n) | Sum from i to j |

---

## 20. Disjoint Set (Union-Find)
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| MakeSet | O(1) | Create new set |
| Find | O(α(n)) ≈ O(1) | Find set representative |
| Union | O(α(n)) ≈ O(1) | Merge two sets |
| Connected | O(α(n)) ≈ O(1) | Check same set |

---

## 21. LRU Cache
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Get | O(1) | Retrieve value |
| Put | O(1) | Insert/Update |
| Delete | O(1) | Remove entry |

---

## 22. Bloom Filter
| Operation | Time Complexity | Description |
|-----------|-----------------|-------------|
| Insert | O(k) | Add element (k = hash functions) |
| Contains | O(k) | Check membership (may have false positives) |

---

## Space Complexity Summary

| Data Structure | Space Complexity |
|----------------|------------------|
| Array | O(n) |
| Linked List | O(n) |
| Stack | O(n) |
| Queue | O(n) |
| Hash Table | O(n) |
| Binary Tree | O(n) |
| BST | O(n) |
| AVL Tree | O(n) |
| Heap | O(n) |
| Trie | O(alphabet × m × n) |
| Graph (Adj List) | O(V + E) |
| Graph (Adj Matrix) | O(V²) |
| Segment Tree | O(n) |
| Fenwick Tree | O(n) |
| Disjoint Set | O(n) |

/// Loads DSA content from markdown files in the dsa/dsa_folder directory
/// Replaces mock data with real filesystem content
library;

import 'dart:io';
import 'package:flutter/services.dart' show rootBundle;

/// Model for a DSA topic with title and markdown content
class DSATopic {
  final String title;
  final String content;
  final String filename;

  DSATopic({
    required this.title,
    required this.content,
    required this.filename,
  });
}

/// Loads all DSA markdown files from the dsa/dsa_folder directory
/// Returns a list of DSATopic objects sorted by filename
Future<List<DSATopic>> loadDSATopics() async {
  final List<DSATopic> topics = [];

  // List of markdown files to load (excluding README and data_structures_operations)
  final List<String> mdFiles = [
    '01_array.md',
    '02_singly_linked_list.md',
    '03_doubly_linked_list.md',
    '04_stack.md',
    '05_queue.md',
    '06_hash_table.md',
    '07_binary_tree.md',
    '08_binary_search_tree.md',
    '09_heap.md',
    '10_trie.md',
    '11_graph.md',
    '12_disjoint_set.md',
    '13_segment_tree.md',
    '14_fenwick_tree.md',
    '15_avl_tree.md',
    '16_priority_queue.md',
    '17_lru_cache.md',
    '18_sorting_algorithms.md',
    '19_searching_algorithms.md',
  ];

  print('📚 Loading ${mdFiles.length} DSA topics from assets...');

  // Load each markdown file
  for (final filename in mdFiles) {
    try {
      final assetPath = 'dsa/dsa_folder/$filename';
      print('   Loading: $assetPath');
      
      // Read file content from assets
      final content = await rootBundle.loadString(assetPath);
      
      print('   ✅ Loaded $filename (${content.length} chars)');
      
      // Extract title from filename
      final title = _extractTitle(filename);
      
      topics.add(DSATopic(
        title: title,
        content: content,
        filename: filename,
      ));
    } catch (e) {
      print('❌ Error loading $filename: $e');
      // Continue loading other files even if one fails
    }
  }

  print('✅ Successfully loaded ${topics.length} topics');
  return topics;
}

/// Extracts a human-readable title from the filename
/// Example: "01_array.md" -> "Array"
/// Example: "02_singly_linked_list.md" -> "Singly Linked List"
String _extractTitle(String filename) {
  // Remove .md extension
  String name = filename.replaceAll('.md', '');
  
  // Remove number prefix (e.g., "01_")
  name = name.replaceAll(RegExp(r'^\d+_'), '');
  
  // Replace underscores with spaces
  name = name.replaceAll('_', ' ');
  
  // Capitalize each word
  return name.split(' ').map((word) {
    if (word.isEmpty) return word;
    return word[0].toUpperCase() + word.substring(1);
  }).join(' ');
}

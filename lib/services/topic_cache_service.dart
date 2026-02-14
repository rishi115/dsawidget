/// Service for caching DSA topic data in SharedPreferences
/// Allows the Android widget to access topic data without loading from assets
library;

import 'dart:convert';
import 'package:flutter/foundation.dart';
import 'package:shared_preferences/shared_preferences.dart';
import '../data/dsa_loader.dart';

/// Caches all DSA topics in SharedPreferences for widget access
/// Should be called when the app starts or when topics are loaded
Future<void> cacheTopicsForWidget(List<DSATopic> topics) async {
  try {
    debugPrint('💾 Caching ${topics.length} topics for widget access...');
    
    final prefs = await SharedPreferences.getInstance();
    
    // Store total count
    await prefs.setInt('cached_topics_count', topics.length);
    
    // Store each topic's title and full content (cleaned up for widget display)
    for (int i = 0; i < topics.length; i++) {
      final topic = topics[i];
      
      // Extract full content without truncation for scrollable widget
      final cleanedContent = _extractPreview(topic.content, maxLength: 999999);
      
      // Store title and full cleaned content with index-based keys
      await prefs.setString('topic_${i}_title', topic.title);
      await prefs.setString('topic_${i}_preview', cleanedContent);
    }
    
    debugPrint('✅ Successfully cached ${topics.length} topics');
  } catch (e) {
    debugPrint('❌ Error caching topics: $e');
  }
}

/// Gets a cached topic by index
/// Returns null if topic not found in cache
Future<Map<String, String>?> getCachedTopic(int index) async {
  try {
    final prefs = await SharedPreferences.getInstance();
    
    final title = prefs.getString('topic_${index}_title');
    final preview = prefs.getString('topic_${index}_preview');
    
    if (title != null && preview != null) {
      return {
        'title': title,
        'preview': preview,
      };
    }
    
    return null;
  } catch (e) {
    debugPrint('❌ Error getting cached topic: $e');
    return null;
  }
}

/// Gets the total number of cached topics
Future<int> getCachedTopicsCount() async {
  try {
    final prefs = await SharedPreferences.getInstance();
    return prefs.getInt('cached_topics_count') ?? 0;
  } catch (e) {
    debugPrint('❌ Error getting cached topics count: $e');
    return 0;
  }
}

/// Extracts a formatted preview from markdown content with visual separators
String _extractPreview(String markdown, {int maxLength = 150}) {
  String preview = markdown;
  
  // Mark code blocks with visual separators BEFORE removing markers
  preview = preview.replaceAll(RegExp(r'```cpp\n'), '\n━━━ CODE ━━━\n');
  preview = preview.replaceAll(RegExp(r'```[a-z]*\n'), '\n━━━ CODE ━━━\n');
  preview = preview.replaceAll(RegExp(r'```\s*$', multiLine: true), '\n━━━━━━━━━━━━\n');
  
  // Convert markdown headers to emphasized text with arrows
  preview = preview.replaceAllMapped(RegExp(r'^###\s+(.+)$', multiLine: true), (match) => '▸ ${match.group(1)}');
  preview = preview.replaceAllMapped(RegExp(r'^##\s+(.+)$', multiLine: true), (match) => '▸▸ ${match.group(1)}');
  preview = preview.replaceAllMapped(RegExp(r'^#\s+(.+)$', multiLine: true), (match) => '▸▸▸ ${match.group(1)}');
  
  // Keep tables but make them more readable
  preview = preview.replaceAll(RegExp(r'\|'), ' │ ');
  
  // Remove bold markers but keep the text
  preview = preview.replaceAll('**', '');
  
  // Remove italic markers
  preview = preview.replaceAll(RegExp(r'[*_]'), '');
  
  // Remove inline code markers
  preview = preview.replaceAll('`', '');
  
  // Convert bullet points to better symbols
  preview = preview.replaceAll(RegExp(r'^\s*[-*]\s+', multiLine: true), '  • ');
  
  // Add spacing around sections
  preview = preview.replaceAll(RegExp(r'\n\s*\n+'), '\n\n');
  
  // Trim whitespace
  preview = preview.trim();
  
  // Truncate to maxLength if needed
  if (preview.length > maxLength) {
    // Try to break at a sentence or word boundary
    int breakPoint = preview.lastIndexOf('. ', maxLength);
    if (breakPoint == -1 || breakPoint < maxLength - 50) {
      breakPoint = preview.lastIndexOf(' ', maxLength);
    }
    if (breakPoint > 0) {
      preview = '${preview.substring(0, breakPoint)}...';
    } else {
      preview = '${preview.substring(0, maxLength)}...';
    }
  }
  
  return preview;
}

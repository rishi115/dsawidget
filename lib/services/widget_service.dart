/// Widget service for synchronizing app state with Android home widget
/// Handles data extraction, formatting, and communication with HomeWidget package
library;

import 'package:flutter/foundation.dart';
import 'package:home_widget/home_widget.dart';

/// Updates the Android home widget with the current topic information
/// 
/// Takes the full [title] and [content] of the current topic, extracts a
/// preview from the content, and synchronizes the data with the home widget.
/// 
/// This function handles all errors gracefully and logs them without throwing,
/// ensuring the app continues to function even if widget updates fail.
/// 
/// Parameters:
/// - [title]: The title of the current DSA topic
/// - [content]: The full markdown content of the topic
/// - [currentIndex]: The current topic index (0-based)
/// - [totalTopics]: The total number of topics
/// 
/// Example:
/// ```dart
/// await updateHomeWidget('Arrays', '# Arrays\n\nArrays are...', 0, 3);
/// ```
Future<void> updateHomeWidget(String title, String content, int currentIndex, int totalTopics) async {
  try {
    debugPrint('📱 Flutter: updateHomeWidget called');
    debugPrint('   Title: $title');
    debugPrint('   Index: $currentIndex / $totalTopics');
    
    // Extract a plain text preview from the markdown content
    final preview = extractPreview(content, maxLength: 150);
    
    debugPrint('   Preview length: ${preview.length} chars');
    
    // Create counter string (e.g., "1 / 3")
    final counter = '${currentIndex + 1} / $totalTopics';
    
    // Save the title, preview, counter, and total topics to widget storage
    await HomeWidget.saveWidgetData<String>('widget_title', title);
    await HomeWidget.saveWidgetData<String>('widget_content', preview);
    await HomeWidget.saveWidgetData<String>('widget_counter', counter);
    await HomeWidget.saveWidgetData<int>('widget_total_topics', totalTopics);
    
    debugPrint('   💾 Data saved to HomeWidget storage');
    debugPrint('      Total topics: $totalTopics');
    
    // Trigger the widget to update with the new data
    await HomeWidget.updateWidget(
      androidName: 'DSAWidgetProvider',
    );
    
    debugPrint('   ✅ Widget update triggered successfully');
  } catch (e) {
    // Log error but don't throw - widget failure shouldn't crash the app
    debugPrint('❌ Error updating widget: $e');
  }
}

/// Extracts a plain text preview from markdown content
/// 
/// Removes markdown formatting characters and truncates the text to the
/// specified maximum length. If the content exceeds the max length, it
/// adds an ellipsis ("...") at the end.
/// 
/// Markdown elements removed:
/// - Headers: `#`, `##`, `###`, etc.
/// - Bold: `**text**`
/// - Italic: `*text*` and `_text_`
/// - Code: `` `code` `` and ``` ```code``` ```
/// 
/// Parameters:
/// - [markdown]: The markdown-formatted content to process
/// - [maxLength]: Maximum length of the preview (default: 150)
/// 
/// Returns: A plain text string suitable for widget display
/// 
/// Example:
/// ```dart
/// final preview = extractPreview('# Header\n\n**Bold** text', maxLength: 20);
/// // Returns: "Bold text"
/// ```
/// 
/// Note: This function is public to allow for testing, but is primarily
/// intended for internal use by updateHomeWidget.
String extractPreview(String markdown, {int maxLength = 150}) {
  // Start with the original markdown
  String preview = markdown;
  
  // Remove markdown headers (# at start of lines, with or without space)
  preview = preview.replaceAll(RegExp(r'^#+\s*', multiLine: true), '');
  
  // Remove bold markers (**)
  preview = preview.replaceAll('**', '');
  
  // Remove italic markers (* and _)
  preview = preview.replaceAll(RegExp(r'[*_]'), '');
  
  // Remove code block markers (```)
  preview = preview.replaceAll('```', '');
  
  // Remove inline code markers (`)
  preview = preview.replaceAll('`', '');
  
  // Trim whitespace
  preview = preview.trim();
  
  // Truncate to maxLength and add ellipsis if needed
  if (preview.length > maxLength) {
    preview = '${preview.substring(0, maxLength)}...';
  }
  
  return preview;
}

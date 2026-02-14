import 'package:flutter/material.dart';
import 'package:flutter_markdown/flutter_markdown.dart';
import 'package:shared_preferences/shared_preferences.dart';
import '../data/dsa_loader.dart';
import '../services/widget_service.dart';
import '../services/topic_cache_service.dart';

/// Home screen that displays DSA topics with markdown rendering
/// Uses StatefulWidget for simple state management
class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  /// Current index in the dsaNotes list
  int currentIndex = 0;
  
  /// List of loaded DSA topics from filesystem
  List<DSATopic> dsaTopics = [];
  
  /// Loading state
  bool isLoading = true;
  
  /// Error message if loading fails
  String? errorMessage;

  @override
  void initState() {
    super.initState();
    _loadDSATopics();
  }
  
  /// Load DSA topics from filesystem
  Future<void> _loadDSATopics() async {
    try {
      debugPrint('🔄 Starting to load DSA topics...');
      final topics = await loadDSATopics();
      
      debugPrint('✅ Loaded ${topics.length} topics from filesystem');
      if (topics.isNotEmpty) {
        debugPrint('   First topic: ${topics[0].title}');
        debugPrint('   Content length: ${topics[0].content.length} chars');
      }
      
      setState(() {
        dsaTopics = topics;
        isLoading = false;
      });
      
      debugPrint('💾 Caching topics for widget...');
      // Cache topics for widget access
      await cacheTopicsForWidget(topics);
      
      // Load saved index after topics are loaded
      await _loadCurrentIndex();
    } catch (e, stackTrace) {
      debugPrint('❌ Error loading DSA topics: $e');
      debugPrint('   Stack trace: $stackTrace');
      setState(() {
        errorMessage = 'Failed to load DSA topics: $e';
        isLoading = false;
      });
    }
  }

  /// Load the current index from SharedPreferences
  /// Defaults to 0 if no saved index exists or on error
  /// Validates that loaded index is within bounds
  Future<void> _loadCurrentIndex() async {
    if (dsaTopics.isEmpty) return;
    
    try {
      final prefs = await SharedPreferences.getInstance();
      final savedIndex = prefs.getInt('currentIndex') ?? 0;
      
      // Validate loaded index is within bounds
      if (savedIndex >= 0 && savedIndex < dsaTopics.length) {
        setState(() {
          currentIndex = savedIndex;
        });
      } else {
        // Invalid saved index, reset to 0
        setState(() {
          currentIndex = 0;
        });
      }
    } catch (e) {
      // Error loading index, default to 0
      debugPrint('Error loading index: $e');
      setState(() {
        currentIndex = 0;
      });
    }
    
    // Update widget after loading index
    _updateWidget();
  }

  /// Update the home widget with the current topic
  Future<void> _updateWidget() async {
    if (dsaTopics.isEmpty) return;
    
    final currentTopic = dsaTopics[currentIndex];
    await updateHomeWidget(
      currentTopic.title,
      currentTopic.content,
      currentIndex,
      dsaTopics.length,
    );
  }

  /// Save the current index to SharedPreferences
  Future<void> _saveCurrentIndex() async {
    try {
      final prefs = await SharedPreferences.getInstance();
      await prefs.setInt('currentIndex', currentIndex);
    } catch (e) {
      // Log error but don't block navigation
      debugPrint('Error saving index: $e');
    }
  }

  /// Save the current index and update the widget
  Future<void> _saveAndUpdateWidget() async {
    await _saveCurrentIndex();
    await _updateWidget();
  }

  /// Navigate to the next topic
  void _goToNext() {
    debugPrint('➡️ Next button clicked in app');
    if (currentIndex < dsaTopics.length - 1) {
      setState(() {
        currentIndex++;
      });
      debugPrint('   New index: $currentIndex');
      _saveAndUpdateWidget();
    } else {
      debugPrint('   Already at last topic');
    }
  }

  /// Navigate to the previous topic
  void _goToPrevious() {
    debugPrint('⬅️ Previous button clicked in app');
    if (currentIndex > 0) {
      setState(() {
        currentIndex--;
      });
      debugPrint('   New index: $currentIndex');
      _saveAndUpdateWidget();
    } else {
      debugPrint('   Already at first topic');
    }
  }

  @override
  Widget build(BuildContext context) {
    // Get theme colors for proper contrast
    final theme = Theme.of(context);
    final colorScheme = theme.colorScheme;

    // Show loading indicator while loading topics
    if (isLoading) {
      return Scaffold(
        appBar: AppBar(
          title: const Text('DSA Revision'),
          backgroundColor: colorScheme.inversePrimary,
        ),
        body: const Center(
          child: CircularProgressIndicator(),
        ),
      );
    }

    // Show error message if loading failed
    if (errorMessage != null) {
      return Scaffold(
        appBar: AppBar(
          title: const Text('DSA Revision'),
          backgroundColor: colorScheme.inversePrimary,
        ),
        body: Center(
          child: Padding(
            padding: const EdgeInsets.all(16.0),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(
                  Icons.error_outline,
                  size: 64,
                  color: colorScheme.error,
                ),
                const SizedBox(height: 16),
                Text(
                  errorMessage!,
                  style: theme.textTheme.bodyLarge?.copyWith(
                    color: colorScheme.error,
                  ),
                  textAlign: TextAlign.center,
                ),
              ],
            ),
          ),
        ),
      );
    }

    // Show empty state if no topics loaded
    if (dsaTopics.isEmpty) {
      return Scaffold(
        appBar: AppBar(
          title: const Text('DSA Revision'),
          backgroundColor: colorScheme.inversePrimary,
        ),
        body: const Center(
          child: Text('No DSA topics found'),
        ),
      );
    }

    // Get current topic data
    final currentTopic = dsaTopics[currentIndex];
    final title = currentTopic.title;
    final content = currentTopic.content;
    
    debugPrint('🎨 Rendering topic: $title');
    debugPrint('   Content length: ${content.length} chars');
    debugPrint('   Content preview: ${content.substring(0, content.length > 100 ? 100 : content.length)}...');

    return Scaffold(
      appBar: AppBar(
        title: Text(title),
        backgroundColor: colorScheme.inversePrimary,
        elevation: 2,
      ),
      body: Column(
        children: [
          // Scrollable markdown content with padding
          Expanded(
            child: Padding(
              padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
              child: Markdown(
                data: content,
                selectable: true,
                styleSheet: MarkdownStyleSheet(
                  // Ensure proper text contrast in both light and dark modes
                  p: theme.textTheme.bodyLarge?.copyWith(
                    color: colorScheme.onSurface,
                    height: 1.5,
                  ),
                  h1: theme.textTheme.headlineLarge?.copyWith(
                    color: colorScheme.onSurface,
                    fontWeight: FontWeight.bold,
                    height: 1.3,
                  ),
                  h2: theme.textTheme.headlineMedium?.copyWith(
                    color: colorScheme.onSurface,
                    fontWeight: FontWeight.bold,
                    height: 1.3,
                  ),
                  h3: theme.textTheme.headlineSmall?.copyWith(
                    color: colorScheme.onSurface,
                    fontWeight: FontWeight.bold,
                    height: 1.3,
                  ),
                  // Style code blocks with proper background and contrast
                  code: theme.textTheme.bodyMedium?.copyWith(
                    fontFamily: 'monospace',
                    backgroundColor: colorScheme.surfaceContainerHighest,
                    color: colorScheme.onSurfaceVariant,
                  ),
                  codeblockDecoration: BoxDecoration(
                    color: colorScheme.surfaceContainerHighest,
                    borderRadius: BorderRadius.circular(8),
                    border: Border.all(
                      color: colorScheme.outlineVariant,
                      width: 1,
                    ),
                  ),
                  codeblockPadding: const EdgeInsets.all(12),
                  // Style list items
                  listBullet: theme.textTheme.bodyLarge?.copyWith(
                    color: colorScheme.onSurface,
                  ),
                  // Add spacing between blocks
                  blockSpacing: 12.0,
                  listIndent: 24.0,
                ),
              ),
            ),
          ),
          // Navigation buttons at bottom with elevation and proper spacing
          Container(
            padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 16.0),
            decoration: BoxDecoration(
              color: colorScheme.surface,
              boxShadow: [
                BoxShadow(
                  color: colorScheme.shadow.withOpacity(0.1),
                  blurRadius: 8,
                  offset: const Offset(0, -2),
                ),
              ],
            ),
            child: SafeArea(
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  ElevatedButton.icon(
                    onPressed: currentIndex > 0 ? _goToPrevious : null,
                    icon: const Icon(Icons.arrow_back),
                    label: const Text('Previous'),
                    style: ElevatedButton.styleFrom(
                      elevation: 3,
                      padding: const EdgeInsets.symmetric(
                        horizontal: 20,
                        vertical: 12,
                      ),
                    ),
                  ),
                  Text(
                    '${currentIndex + 1} / ${dsaTopics.length}',
                    style: theme.textTheme.titleMedium?.copyWith(
                      color: colorScheme.onSurface,
                      fontWeight: FontWeight.w500,
                    ),
                  ),
                  ElevatedButton.icon(
                    onPressed: currentIndex < dsaTopics.length - 1 ? _goToNext : null,
                    label: const Text('Next'),
                    icon: const Icon(Icons.arrow_forward),
                    style: ElevatedButton.styleFrom(
                      elevation: 3,
                      padding: const EdgeInsets.symmetric(
                        horizontal: 20,
                        vertical: 12,
                      ),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}

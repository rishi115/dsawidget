import 'package:flutter_test/flutter_test.dart';
import 'package:widgetapp/services/widget_service.dart';
import 'package:widgetapp/data/mock_data.dart';

void main() {
  group('Widget Service Integration Tests', () {
    test('extractPreview works with actual Arrays topic', () {
      final topic = dsaNotes[0];
      final preview = extractPreview(topic['content']!, maxLength: 150);
      
      // Should not contain markdown formatting
      expect(preview.contains('#'), isFalse);
      expect(preview.contains('**'), isFalse);
      expect(preview.contains('`'), isFalse);
      
      // Should contain actual content
      expect(preview, contains('Arrays'));
      
      // Should be within length limit
      expect(preview.length, lessThanOrEqualTo(153)); // 150 + '...'
      
      print('Arrays preview: $preview');
    });

    test('extractPreview works with actual Strings topic', () {
      final topic = dsaNotes[1];
      final preview = extractPreview(topic['content']!, maxLength: 150);
      
      // Should not contain markdown formatting
      expect(preview.contains('#'), isFalse);
      expect(preview.contains('**'), isFalse);
      
      // Should contain actual content
      expect(preview, contains('Strings'));
      
      // Should be within length limit
      expect(preview.length, lessThanOrEqualTo(153));
      
      print('Strings preview: $preview');
    });

    test('extractPreview works with actual Linked List topic', () {
      final topic = dsaNotes[2];
      final preview = extractPreview(topic['content']!, maxLength: 150);
      
      // Should not contain markdown formatting
      expect(preview.contains('#'), isFalse);
      expect(preview.contains('```'), isFalse);
      
      // Should contain actual content
      expect(preview, contains('linked list'));
      
      // Should be within length limit
      expect(preview.length, lessThanOrEqualTo(153));
      
      print('Linked List preview: $preview');
    });

    test('all topics generate valid previews', () {
      for (final topic in dsaNotes) {
        final preview = extractPreview(topic['content']!, maxLength: 150);
        
        // All previews should be non-empty
        expect(preview.isNotEmpty, isTrue);
        
        // All previews should be within length limit
        expect(preview.length, lessThanOrEqualTo(153));
        
        // No preview should contain markdown formatting
        expect(preview.contains('**'), isFalse);
        expect(preview.contains('```'), isFalse);
      }
    });
  });
}

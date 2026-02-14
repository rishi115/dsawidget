import 'package:flutter_test/flutter_test.dart';
import 'package:widgetapp/services/widget_service.dart';

void main() {
  group('Widget Service Tests', () {
    test('updateHomeWidget function exists with correct signature', () {
      // This test verifies the function signature is correct
      expect(updateHomeWidget, isA<Function>());
    });

    group('extractPreview function tests', () {
      test('removes markdown headers', () {
        const markdown = '# Header\n\nSome content';
        final result = extractPreview(markdown);
        expect(result.contains('#'), isFalse);
        expect(result, contains('Some content'));
      });

      test('removes bold markers', () {
        const markdown = '**Bold text** and normal text';
        final result = extractPreview(markdown);
        expect(result.contains('**'), isFalse);
        expect(result, equals('Bold text and normal text'));
      });

      test('removes italic markers with asterisks', () {
        const markdown = '*Italic* text';
        final result = extractPreview(markdown);
        expect(result.contains('*'), isFalse);
        expect(result, equals('Italic text'));
      });

      test('removes italic markers with underscores', () {
        const markdown = '_Italic_ text';
        final result = extractPreview(markdown);
        expect(result.contains('_'), isFalse);
        expect(result, equals('Italic text'));
      });

      test('removes inline code markers', () {
        const markdown = 'Use `code` here';
        final result = extractPreview(markdown);
        expect(result.contains('`'), isFalse);
        expect(result, equals('Use code here'));
      });

      test('removes code block markers', () {
        const markdown = '```\ncode block\n```';
        final result = extractPreview(markdown);
        expect(result.contains('```'), isFalse);
        expect(result, contains('code block'));
      });

      test('truncates long text and adds ellipsis', () {
        final markdown = 'A' * 200;
        final result = extractPreview(markdown, maxLength: 150);
        expect(result.length, equals(153)); // 150 + '...'
        expect(result.endsWith('...'), isTrue);
      });

      test('does not add ellipsis for short text', () {
        const markdown = 'Short text';
        final result = extractPreview(markdown, maxLength: 150);
        expect(result, equals('Short text'));
        expect(result.endsWith('...'), isFalse);
      });

      test('respects custom maxLength parameter', () {
        final markdown = 'A' * 100;
        final result = extractPreview(markdown, maxLength: 50);
        expect(result.length, equals(53)); // 50 + '...'
        expect(result.endsWith('...'), isTrue);
      });

      test('handles complex markdown with multiple formatting types', () {
        const markdown = '''# Header

**Bold** and *italic* text with `code` and more.

```
code block
```

Regular text.''';
        final result = extractPreview(markdown);
        expect(result.contains('#'), isFalse);
        expect(result.contains('**'), isFalse);
        expect(result.contains('*'), isFalse);
        expect(result.contains('`'), isFalse);
        expect(result, contains('Bold'));
        expect(result, contains('italic'));
        expect(result, contains('code'));
      });

      test('trims whitespace', () {
        const markdown = '# Header\n\nContent   ';
        final result = extractPreview(markdown);
        // After removing # and trimming, we should get clean text
        expect(result, equals('Header\n\nContent'));
      });

      test('handles empty string', () {
        const markdown = '';
        final result = extractPreview(markdown);
        expect(result, equals(''));
      });

      test('handles string with markdown formatting at line start', () {
        const markdown = '# Header\n## Subheader\n**bold** text';
        final result = extractPreview(markdown);
        // Should remove header markers at line start
        expect(result.contains('Header'), isTrue);
        expect(result.contains('Subheader'), isTrue);
        expect(result.contains('bold'), isTrue);
        // Should not contain formatting characters
        expect(result.contains('**'), isFalse);
      });
    });
  });
}

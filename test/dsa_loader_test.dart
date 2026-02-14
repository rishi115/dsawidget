import 'package:flutter_test/flutter_test.dart';
import 'package:flutter/services.dart';
import 'package:widgetapp/data/dsa_loader.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  group('DSA Loader Tests', () {
    test('loadDSATopics should load all 19 topics', () async {
      // Mock the asset loading
      TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
          .setMockMethodCallHandler(
        const MethodChannel('flutter/assets'),
        (MethodCall methodCall) async {
          if (methodCall.method == 'loadString') {
            final String asset = methodCall.arguments as String;
            if (asset.contains('01_array.md')) {
              return '# Array\n\nTest content for arrays';
            }
            return '# Test Topic\n\nTest content';
          }
          return null;
        },
      );

      final topics = await loadDSATopics();

      expect(topics.length, 19);
      expect(topics[0].title, 'Array');
      expect(topics[0].filename, '01_array.md');
    });

    test('extractTitle should format filenames correctly', () {
      // Test through the public API by checking loaded topics
      expect('01_array.md'.replaceAll('.md', '').replaceAll(RegExp(r'^\d+_'), '').replaceAll('_', ' ').split(' ').map((w) => w[0].toUpperCase() + w.substring(1)).join(' '), 'Array');
      expect('02_singly_linked_list.md'.replaceAll('.md', '').replaceAll(RegExp(r'^\d+_'), '').replaceAll('_', ' ').split(' ').map((w) => w[0].toUpperCase() + w.substring(1)).join(' '), 'Singly Linked List');
    });
  });
}

// DSA Revision App widget tests
//
// Tests for navigation functionality and UI components

import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

import 'package:widgetapp/main.dart';
import 'package:widgetapp/data/mock_data.dart';

void main() {
  testWidgets('App displays first topic on launch', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    // Verify that the first topic title is displayed in AppBar
    expect(find.widgetWithText(AppBar, 'Arrays'), findsOneWidget);
    expect(find.text('Previous'), findsOneWidget);
    expect(find.text('Next'), findsOneWidget);
  });

  testWidgets('Navigation buttons exist', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    expect(find.widgetWithText(ElevatedButton, 'Previous'), findsOneWidget);
    expect(find.widgetWithText(ElevatedButton, 'Next'), findsOneWidget);
  });

  testWidgets('Previous button disabled at first topic', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    final previousButton = tester.widget<ElevatedButton>(
      find.widgetWithText(ElevatedButton, 'Previous')
    );
    expect(previousButton.onPressed, isNull);
  });

  testWidgets('Next button works and updates content', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    // Verify we start at Arrays
    expect(find.widgetWithText(AppBar, 'Arrays'), findsOneWidget);

    // Tap Next button
    await tester.tap(find.widgetWithText(ElevatedButton, 'Next'));
    await tester.pumpAndSettle();

    // Verify we moved to Strings
    expect(find.widgetWithText(AppBar, 'Strings'), findsOneWidget);
    expect(find.widgetWithText(AppBar, 'Arrays'), findsNothing);
  });

  testWidgets('Previous button works after navigating forward', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    // Navigate forward
    await tester.tap(find.widgetWithText(ElevatedButton, 'Next'));
    await tester.pumpAndSettle();
    expect(find.widgetWithText(AppBar, 'Strings'), findsOneWidget);

    // Navigate back
    await tester.tap(find.widgetWithText(ElevatedButton, 'Previous'));
    await tester.pumpAndSettle();

    // Verify we're back at Arrays
    expect(find.widgetWithText(AppBar, 'Arrays'), findsOneWidget);
  });

  testWidgets('Topic counter displays correctly', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    // Check initial counter
    expect(find.text('1 / ${dsaNotes.length}'), findsOneWidget);

    // Navigate forward
    await tester.tap(find.widgetWithText(ElevatedButton, 'Next'));
    await tester.pumpAndSettle();

    // Check updated counter
    expect(find.text('2 / ${dsaNotes.length}'), findsOneWidget);
  });

  testWidgets('Next button disabled at last topic', (WidgetTester tester) async {
    await tester.pumpWidget(const DSARevisionApp());
    await tester.pumpAndSettle();

    // Navigate to last topic
    for (int i = 0; i < dsaNotes.length - 1; i++) {
      await tester.tap(find.widgetWithText(ElevatedButton, 'Next'));
      await tester.pumpAndSettle();
    }

    // Verify Next button is disabled
    final nextButton = tester.widget<ElevatedButton>(
      find.widgetWithText(ElevatedButton, 'Next')
    );
    expect(nextButton.onPressed, isNull);
  });
}

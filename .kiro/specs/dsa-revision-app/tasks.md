# Implementation Plan: DSA Revision App

## Overview

This implementation plan breaks down the DSA Revision App into discrete coding tasks. The app will be built incrementally, starting with the core Flutter UI and navigation, then adding persistence, and finally integrating the Android home screen widget. Each task builds on previous work, with testing integrated throughout to catch errors early.

## Tasks

- [x] 1. Set up Flutter project structure and dependencies
  - Create new Flutter project with `flutter create dsa_revision_app`
  - Add required dependencies to `pubspec.yaml`: `flutter_markdown`, `shared_preferences`, `home_widget`
  - Configure Android minimum SDK version to 21 in `android/app/build.gradle`
  - Set up Material 3 theme configuration in `main.dart`
  - _Requirements: 11.1, 9.1, 9.2_

- [x] 2. Create mock DSA data structure
  - Create a `lib/data/mock_data.dart` file
  - Define `dsaNotes` list with Map<String, String> structure
  - Add three sample topics: Arrays, Strings, Linked List
  - Include markdown-formatted content with headers, lists, and code blocks
  - _Requirements: 3.1, 3.2, 3.4_

- [ ] 3. Implement main app entry point
  - [x] 3.1 Create `lib/main.dart` with DSARevisionApp widget
    - Configure MaterialApp with Material 3 themes (light and dark)
    - Set themeMode to ThemeMode.system for automatic dark mode
    - Initialize WidgetsFlutterBinding in main()
    - Register HomeWidget background callback
    - _Requirements: 9.1, 9.2, 11.4_
  
  - [ ]* 3.2 Write unit tests for app configuration
    - Test Material 3 is enabled in both themes
    - Test themeMode is set to system
    - _Requirements: 9.1, 9.2_

- [ ] 4. Build home screen UI with markdown rendering
  - [x] 4.1 Create `lib/screens/home_screen.dart` with StatefulWidget
    - Define state variables: `currentIndex` (int, default 0)
    - Import mock data from `mock_data.dart`
    - Build Scaffold with AppBar showing current topic title
    - Add Expanded widget containing Markdown widget from flutter_markdown
    - Make markdown content selectable and scrollable
    - _Requirements: 1.1, 1.2, 1.3, 1.4, 7.1, 7.4_
  
  - [x] 4.2 Add navigation buttons at bottom
    - Create Row with Previous and Next ElevatedButtons
    - Add topic counter display (e.g., "2 / 3") between buttons
    - Wrap in Padding widget for spacing
    - _Requirements: 2.1_
  
  - [ ]* 4.3 Write unit tests for UI layout
    - Test app displays first topic on launch
    - Test navigation buttons exist
    - Test topic title is displayed
    - Test markdown widget is present
    - _Requirements: 1.1, 2.1, 1.4_

- [ ] 5. Implement navigation logic
  - [x] 5.1 Create navigation methods in HomeScreen state
    - Implement `_goToNext()` method: increment currentIndex if not at end, call setState
    - Implement `_goToPrevious()` method: decrement currentIndex if not at start, call setState
    - Wire methods to button onPressed callbacks
    - Disable Previous button when currentIndex == 0
    - Disable Next button when currentIndex == dsaNotes.length - 1
    - _Requirements: 2.2, 2.3, 2.4, 2.5, 7.3_
  
  - [ ]* 5.2 Write property test for navigation
    - **Property 1: Navigation Updates Index and Content**
    - Test with 100 iterations across different starting indices
    - Verify Next increments index and updates displayed content
    - Verify Previous decrements index and updates displayed content
    - **Validates: Requirements 2.2, 2.3, 2.6**
  
  - [ ]* 5.3 Write unit tests for edge cases
    - Test Previous button disabled at first topic
    - Test Next button disabled at last topic
    - _Requirements: 2.4, 2.5_

- [x] 6. Checkpoint - Verify basic navigation works
  - Run the app and test navigation between topics
  - Verify markdown rendering displays correctly
  - Verify buttons enable/disable at boundaries
  - Ensure all tests pass, ask the user if questions arise

- [ ] 7. Add SharedPreferences persistence
  - [x] 7.1 Implement index persistence methods
    - Create `_loadCurrentIndex()` method in initState: load from SharedPreferences, default to 0
    - Create `_saveCurrentIndex()` method: save currentIndex to SharedPreferences
    - Call `_saveCurrentIndex()` in both navigation methods
    - Add error handling for SharedPreferences failures (try-catch, default to 0)
    - Validate loaded index is within bounds before using
    - _Requirements: 4.1, 4.2, 4.3_
  
  - [ ]* 7.2 Write property test for persistence round-trip
    - **Property 2: Index Persistence Round-Trip**
    - Test with 100 iterations across different indices
    - Save index, load index, verify they match
    - **Validates: Requirements 4.1, 4.2**
  
  - [ ]* 7.3 Write unit tests for persistence edge cases
    - Test default to index 0 when no saved index exists
    - Test invalid saved index (out of bounds) defaults to 0
    - Test persistence error handling doesn't crash app
    - _Requirements: 4.3_

- [ ] 8. Create widget service for home widget synchronization
  - [x] 8.1 Create `lib/services/widget_service.dart`
    - Implement `updateHomeWidget(String title, String content)` function
    - Implement `_extractPreview(String markdown, {int maxLength})` helper function
    - Remove markdown formatting (headers #, bold **, italic *, code ```)
    - Truncate to maxLength and add "..." if needed
    - Use HomeWidget.saveWidgetData to save 'widget_title' and 'widget_content'
    - Call HomeWidget.updateWidget with androidName: 'DSAWidgetProvider'
    - Add try-catch error handling, log errors but don't throw
    - _Requirements: 6.2, 6.3, 8.2_
  
  - [ ]* 8.2 Write property test for preview extraction
    - **Property 4: Content Preview Extraction**
    - Test with various markdown strings and max lengths
    - Verify markdown formatting is removed
    - Verify length limit is respected
    - Verify ellipsis added when truncated
    - **Validates: Requirements 5.2**
  
  - [ ]* 8.3 Write unit tests for widget service
    - Test updateHomeWidget function exists with correct signature
    - Test preview extraction with specific examples
    - Test error handling doesn't throw exceptions
    - _Requirements: 8.2_

- [ ] 9. Integrate widget service with navigation
  - [x] 9.1 Call widget service from home screen
    - Import widget_service.dart in home_screen.dart
    - Create `_updateWidget()` method that calls updateHomeWidget with current topic
    - Call `_updateWidget()` at end of `_loadCurrentIndex()`
    - Create `_saveAndUpdateWidget()` method that saves index then updates widget
    - Call `_saveAndUpdateWidget()` in both navigation methods
    - _Requirements: 6.1, 6.3_
  
  - [ ]* 9.2 Write property test for widget synchronization
    - **Property 3: Widget Data Synchronization**
    - Test that navigation triggers widget data save
    - Verify widget title and content are updated
    - Verify updateWidget is called
    - **Validates: Requirements 6.1, 6.2, 6.3**

- [ ] 10. Configure Android widget infrastructure
  - [x] 10.1 Update AndroidManifest.xml
    - Add widget receiver declaration in `android/app/src/main/AndroidManifest.xml`
    - Set receiver name to "DSAWidgetProvider"
    - Add APPWIDGET_UPDATE intent filter
    - Add meta-data pointing to widget info XML
    - _Requirements: 11.2, 10.4_
  
  - [x] 10.2 Create widget info XML
    - Create `android/app/src/main/res/xml/dsa_widget_info.xml`
    - Set minWidth: 250dp, minHeight: 110dp
    - Set updatePeriodMillis: 0 (manual updates only)
    - Set initialLayout to @layout/dsa_widget_layout
    - Enable horizontal and vertical resizing
    - _Requirements: 11.3_
  
  - [x] 10.3 Create widget layout XML
    - Create `android/app/src/main/res/layout/dsa_widget_layout.xml`
    - Use LinearLayout with vertical orientation
    - Add TextView for title (id: widget_title, bold, 18sp, maxLines: 1)
    - Add TextView for content (id: widget_content, 14sp, maxLines: 3)
    - Add padding and background drawable
    - _Requirements: 5.1, 5.2, 5.4, 11.3_
  
  - [ ]* 10.4 Write unit tests for Android configuration
    - Test AndroidManifest contains widget receiver
    - Test widget info XML exists
    - Test widget layout XML exists
    - _Requirements: 11.2, 11.3_

- [ ] 11. Implement Android widget provider in Kotlin
  - [x] 11.1 Create DSAWidgetProvider.kt
    - Create file in `android/app/src/main/kotlin/com/example/dsa_revision_app/`
    - Extend AppWidgetProvider class
    - Override onUpdate method
    - Get widget data using HomeWidgetPlugin.getData(context)
    - Retrieve 'widget_title' and 'widget_content' from data
    - Create RemoteViews with dsa_widget_layout
    - Set text for widget_title and widget_content TextViews
    - Create PendingIntent to open MainActivity on widget tap
    - Update all widget instances with appWidgetManager.updateAppWidget
    - _Requirements: 5.1, 5.2, 5.5, 10.2_
  
  - [x] 11.2 Add background callback in main.dart
    - Create `@pragma('vm:entry-point')` annotated backgroundCallback function
    - Register callback with HomeWidget.registerBackgroundCallback in main()
    - _Requirements: 11.4_

- [x] 12. Checkpoint - Test widget functionality
  - Run app on Android device/emulator
  - Add widget to home screen
  - Verify widget displays current topic
  - Navigate in app and verify widget updates
  - Test app restart restores correct topic
  - Ensure all tests pass, ask the user if questions arise

- [ ] 13. Polish UI and add final touches
  - [x] 13.1 Enhance UI styling
    - Add proper spacing and padding throughout
    - Ensure text contrast works in both light and dark modes
    - Add elevation to buttons
    - Style markdown code blocks appropriately
    - _Requirements: 9.4, 9.5_
  
  - [x] 13.2 Add widget background drawable
    - Create `android/app/src/main/res/drawable/widget_background.xml`
    - Define rounded rectangle shape with gradient or solid color
    - Ensure visibility on various launcher backgrounds
    - _Requirements: 5.3_
  
  - [ ]* 13.3 Write integration tests
    - Test complete navigation flow
    - Test persistence across app restarts
    - Test widget updates on navigation
    - _Requirements: 2.6, 4.1, 6.1_

- [x] 14. Final checkpoint - Complete testing and validation
  - Run all unit tests and property tests
  - Verify 80%+ code coverage
  - Test on multiple Android versions (API 21+)
  - Test in both light and dark modes
  - Verify widget works on different launchers
  - Ensure all tests pass, ask the user if questions arise

## Notes

- Tasks marked with `*` are optional and can be skipped for faster MVP
- Each task references specific requirements for traceability
- Property tests validate universal correctness properties with 100+ iterations
- Unit tests validate specific examples and edge cases
- Checkpoints ensure incremental validation at key milestones
- The implementation follows a bottom-up approach: UI → Navigation → Persistence → Widget
- All async operations use proper error handling to prevent crashes

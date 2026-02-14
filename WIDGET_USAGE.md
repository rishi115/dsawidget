# DSA Revision App - Widget Usage Guide

## How the Widget Works

The DSA Revision App includes an Android home screen widget that displays your current DSA topic with navigation buttons.

### Widget Features

1. **Topic Title** - Shows the current DSA topic name (e.g., "Arrays", "Strings", "Linked List")
2. **Content Preview** - Displays the first 150 characters of the topic content (markdown formatting removed)
3. **Topic Counter** - Shows your position (e.g., "1 / 3")
4. **Previous Button** - Navigate to the previous topic
5. **Next Button** - Navigate to the next topic

### How to Add the Widget

1. Long-press on your Android home screen
2. Tap "Widgets"
3. Find "widgetapp" in the list
4. Drag the DSA Revision widget to your home screen

### How Navigation Works

The widget has **two ways** to navigate between topics:

#### Option 1: Navigate in the App
1. Open the DSA Revision app
2. Use the Previous/Next buttons at the bottom of the app
3. The widget on your home screen will automatically update to show the new topic

#### Option 2: Navigate from the Widget
1. Tap the "Previous" or "Next" button directly on the widget
2. The widget will update immediately to show the new topic
3. When you open the app, it will show the same topic

### Data Synchronization

- The app and widget share the same data through SharedPreferences
- Changes in the app are reflected in the widget
- Changes in the widget are reflected in the app
- Your current topic position is saved and restored when you restart the app

### Troubleshooting

**Widget shows "DSA Revision" / "Open app to view content":**
- This is the default state before the app has been opened
- Solution: Open the app once, and the widget will update with the first topic

**Widget doesn't update when clicking buttons:**
- Make sure you've rebuilt the app after the latest changes
- Try removing and re-adding the widget to your home screen
- Check that the app has proper permissions

**Widget shows old data:**
- The widget updates automatically, but sometimes Android caches widget data
- Solution: Remove the widget and add it again

### Technical Details

- **Widget Provider**: `DSAWidgetProvider.kt`
- **Widget Layout**: `dsa_widget_layout.xml`
- **Widget Service**: `widget_service.dart`
- **Data Storage**: SharedPreferences (key: `flutter.currentIndex`)
- **Update Mechanism**: Manual updates triggered by navigation actions

### Current Topics

The app currently includes 3 DSA topics:
1. **Arrays** - Contiguous memory data structures
2. **Strings** - Sequences of characters
3. **Linked List** - Linear data structure with nodes

You can navigate between these topics using either the app or the widget buttons.

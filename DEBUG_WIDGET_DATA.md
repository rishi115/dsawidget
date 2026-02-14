# Widget Data Debugging Guide

## How to View Widget Logs

The widget now has extensive logging to show exactly what data it has access to.

### Step 1: Install the App
```bash
fvm flutter install
```

### Step 2: Open the App
Open the app on your device to load the DSA topics and cache them.

### Step 3: Add Widget to Home Screen
Long-press on your home screen and add the DSA Widget.

### Step 4: View Logs
Run this command to see all widget logs:
```bash
adb logcat -s DSAWidget:D Flutter:D
```

Or use the batch file:
```bash
view_logs.bat
```

## What the Logs Will Show

### When Widget Updates:
```
🎨 updateAppWidget called for widget ID: 123

🔍 Checking FlutterSharedPreferences:
   Flutter: flutter.currentIndex = 0
   Flutter: flutter.cached_topics_count = 19
   Flutter: flutter.topic_0_title = Array
   Flutter: flutter.topic_0_preview = Dynamic array implementation...

🔍 Checking HomeWidgetPreferences:
   Home: widget_title = Array
   Home: widget_content = Dynamic array implementation with all operations...
   Home: widget_counter = 1 / 19
   Home: widget_total_topics = 19

🔍 Checking HomeWidgetPlugin.getData():
   Plugin: widget_title = Array
   Plugin: widget_content = Dynamic array implementation with all operations...
   Plugin: widget_counter = 1 / 19

📝 Final widget data to display:
   Title: Array
   Content: Dynamic array implementation with all operations. Time Complexity | Operation | Time | |-----------|------...
   Content length: 150 chars
   Counter: 1 / 19

✅ Text set on RemoteViews
```

### When You Click Previous/Next:
```
🔔 onReceive called with action: com.example.widgetapp.ACTION_NEXT

➡️ Next button clicked!

🔄 navigateTopic called with direction: 1
   Current index: 0
   Total topics: 19
   New index (after bounds check): 1
   ✅ Index changed! Loading new topic data...
   📖 Loaded topic: Singly Linked List
      Preview: A linear data structure where elements are stored in nodes...
      Counter: 2 / 19
   💾 Data saved to HomeWidget storage
   🔄 Updating 1 widget(s)
   ✅ Widget update complete!
```

## Troubleshooting Based on Logs

### Issue 1: No Data in FlutterSharedPreferences
**Logs show:**
```
🔍 Checking FlutterSharedPreferences:
   (empty or no topic data)
```

**Cause:** App hasn't cached the topics yet.

**Solution:**
1. Open the app
2. Wait for topics to load
3. Close and reopen the app
4. Check widget again

### Issue 2: No Data in HomeWidgetPreferences
**Logs show:**
```
🔍 Checking HomeWidgetPreferences:
   (empty)
```

**Cause:** Widget hasn't been updated by Flutter yet.

**Solution:**
1. Open the app
2. Click Next or Previous in the app
3. Check widget again

### Issue 3: Content is Null or Empty
**Logs show:**
```
⚠️ WARNING: Content is null or empty!
```

**Cause:** Data not being saved properly.

**Solution:**
1. Check Flutter logs for errors
2. Verify topics are loading: `flutter logs | grep "Loading"`
3. Check if caching is working: `flutter logs | grep "Caching"`

### Issue 4: Content Exists But Not Visible
**Logs show:**
```
Content: Dynamic array implementation...
Content length: 150 chars
```

But you don't see it on the widget.

**Possible causes:**
1. **Text color issue** - white text on white background
2. **Layout issue** - TextView is hidden or has 0 height
3. **Widget not refreshing** - old widget still showing

**Solutions:**
1. Remove widget and add it again
2. Restart your device
3. Check if title and counter are visible (if yes, it's a content-specific issue)

## Manual Data Check

You can manually check what data is stored:

### Check FlutterSharedPreferences:
```bash
adb shell
run-as com.example.widgetapp
cat shared_prefs/FlutterSharedPreferences.xml
```

Look for:
- `flutter.currentIndex`
- `flutter.cached_topics_count`
- `flutter.topic_0_title`
- `flutter.topic_0_preview`

### Check HomeWidgetPreferences:
```bash
adb shell
run-as com.example.widgetapp
cat shared_prefs/HomeWidgetPreferences.xml
```

Look for:
- `widget_title`
- `widget_content`
- `widget_counter`
- `widget_total_topics`

## Expected Data Format

### FlutterSharedPreferences should contain:
```xml
<long name="flutter.currentIndex" value="0" />
<int name="flutter.cached_topics_count" value="19" />
<string name="flutter.topic_0_title">Array</string>
<string name="flutter.topic_0_preview">Dynamic array implementation with all operations. Time Complexity...</string>
<string name="flutter.topic_1_title">Singly Linked List</string>
<string name="flutter.topic_1_preview">A linear data structure where elements are stored in nodes...</string>
... (for all 19 topics)
```

### HomeWidgetPreferences should contain:
```xml
<string name="widget_title">Array</string>
<string name="widget_content">Dynamic array implementation with all operations...</string>
<string name="widget_counter">1 / 19</string>
<int name="widget_total_topics" value="19" />
```

## Quick Test

1. Install app: `fvm flutter install`
2. Open app and wait for it to load
3. Start logging: `adb logcat -s DSAWidget:D Flutter:D`
4. Add widget to home screen
5. Check logs for the data shown above
6. Click Next on widget
7. Check logs to see if data changes

## If Content Still Not Visible

After checking logs, if you see:
- ✅ Data is in FlutterSharedPreferences
- ✅ Data is in HomeWidgetPreferences
- ✅ Content length > 0
- ❌ But still not visible on widget

Then it's a **UI/rendering issue**. Try:

1. **Increase text size** in widget layout
2. **Change text color** to pure white (#FFFFFF)
3. **Remove maxLines** limit
4. **Check if TextView is actually visible** (not hidden behind something)

Let me know what the logs show and I can help further!

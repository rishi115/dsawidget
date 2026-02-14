# Debug Logs Guide

## How to View Widget Logs

I've added comprehensive logging to help debug the widget functionality. Here's how to view the logs:

### Method 1: Using Android Studio Logcat

1. **Open Android Studio**
2. **Click on "Logcat" tab** at the bottom
3. **Filter by tag**: Type `DSAWidget` in the search box
4. **Run your app** and interact with the widget

### Method 2: Using Command Line (ADB)

```bash
# View all logs with DSAWidget tag
adb logcat -s DSAWidget

# Or view both Flutter and Widget logs
adb logcat | grep -E "DSAWidget|flutter"
```

### Method 3: Using Flutter Run

When you run the app with `fvm flutter run`, you'll see Flutter logs in the console. For Android native logs, use one of the methods above.

## What to Look For

### When You Click Widget Buttons

You should see logs like this:

```
🔔 onReceive called with action: com.example.widgetapp.ACTION_NEXT
➡️ Next button clicked!
🔄 navigateTopic called with direction: 1
   Current index: 0
   New index (after bounds check): 1
   ✅ Index changed! Updating data...
   New topic: Strings
   Counter: 2 / 3
   💾 Data saved to SharedPreferences
   🔄 Updating 1 widget(s)
🎨 updateAppWidget called for widget ID: 123
   📝 Widget data:
      Title: Strings
      Content: Strings are sequences of characters, typically...
      Counter: 2 / 3
   🔘 Previous button PendingIntent created
   🔘 Next button PendingIntent created
   ✅ Widget UI updated successfully
   ✅ Widget update complete!
```

### When You Navigate in the App

You should see logs like this:

```
➡️ Next button clicked in app
   New index: 1
📱 Flutter: updateHomeWidget called
   Title: Strings
   Index: 1 / 3
   Preview length: 150 chars
   💾 Data saved to HomeWidget storage
   ✅ Widget update triggered successfully
```

## Troubleshooting Based on Logs

### If you see NO logs when clicking widget buttons:

**Problem**: The button clicks aren't being received
**Solutions**:
1. Remove the widget and add it again
2. Rebuild the app: `fvm flutter clean && fvm flutter run`
3. Check if the widget receiver is registered in AndroidManifest.xml

### If you see "onReceive" but NO "navigateTopic":

**Problem**: The action isn't matching
**Check**: Look for the action name in the log. It should be:
- `com.example.widgetapp.ACTION_PREVIOUS`
- `com.example.widgetapp.ACTION_NEXT`

### If you see "Index unchanged, skipping update":

**Problem**: You're at the boundary (first or last topic)
**Solution**: This is normal behavior. Try clicking the other button.

### If you see "Widget data" with default values:

**Problem**: Data isn't being saved properly
**Check**:
1. Look for "Data saved to SharedPreferences" log
2. Check if the app has been opened at least once
3. Try navigating in the app first

### If widget doesn't update visually but logs show success:

**Problem**: Android widget cache issue
**Solutions**:
1. Remove and re-add the widget
2. Restart your device
3. Clear app data and reinstall

## Testing Checklist

Run through these tests and check the logs:

1. ✅ **Open app** - Should see "Flutter: updateHomeWidget called"
2. ✅ **Click Next in app** - Should see "Next button clicked in app"
3. ✅ **Click Previous in app** - Should see "Previous button clicked in app"
4. ✅ **Click Next on widget** - Should see "onReceive" and "Next button clicked!"
5. ✅ **Click Previous on widget** - Should see "onReceive" and "Previous button clicked!"
6. ✅ **Click at boundaries** - Should see "Index unchanged" or "Already at first/last topic"

## Quick Test Command

Run this to see live logs while testing:

```bash
# Clear logs and start fresh
adb logcat -c

# Watch logs in real-time
adb logcat -s DSAWidget:D flutter:I
```

Then interact with your widget and watch the logs appear!

## Log Emoji Guide

- 📱 = App/Widget initialization
- 🔔 = Event received
- ➡️ = Next action
- ⬅️ = Previous action
- 🔄 = Processing/updating
- ✅ = Success
- ❌ = Error
- ⚠️ = Warning
- 💾 = Data saved
- 📝 = Data retrieved
- 🔘 = Button setup
- 🎨 = UI update
- ❓ = Unknown/unexpected

This makes it easy to scan through logs quickly!

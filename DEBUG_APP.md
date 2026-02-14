# Debug Guide - MD Text Not Visible Issue

## Quick Checks

### 1. Check if app is showing loading indicator or error
When you open the app, you should see one of these states:
- **Loading**: CircularProgressIndicator (spinning wheel)
- **Error**: Red error icon with error message
- **Content**: The markdown content should be visible

### 2. Check Flutter logs
Run this command to see detailed logs:
```bash
flutter run --verbose
```

Look for these log messages:
- `📚 Loading 19 DSA topics from assets...`
- `✅ Loaded 01_array.md (XXXX chars)`
- `✅ Successfully loaded 19 topics`

### 3. Common Issues and Solutions

#### Issue: "Failed to load asset"
**Cause**: Assets not properly bundled
**Solution**: 
```bash
fvm flutter clean
fvm flutter pub get
fvm flutter build apk --debug
```

#### Issue: Blank white screen
**Cause**: Loading state stuck or error not displayed
**Solution**: Check if `isLoading` is stuck at `true`

#### Issue: Error message displayed
**Cause**: Asset loading failed
**Solution**: Check the error message for details

## Manual Test Steps

1. **Install the app**:
   ```bash
   fvm flutter install
   ```

2. **Watch logs while opening app**:
   ```bash
   flutter logs
   ```

3. **Look for these specific messages**:
   - `📚 Loading 19 DSA topics from assets...`
   - `Loading: dsa/dsa_folder/01_array.md`
   - `✅ Loaded 01_array.md (XXXX chars)`

4. **If you see errors**:
   - Note the exact error message
   - Check which file failed to load
   - Verify the file exists in `dsa/dsa_folder/`

## Verify Assets Are Bundled

Check if assets are in the APK:
```bash
# Extract APK
unzip -l build/app/outputs/flutter-apk/app-debug.apk | grep "dsa/dsa_folder"
```

You should see all 19 .md files listed.

## Alternative: Use Flutter DevTools

1. Run app in debug mode:
   ```bash
   fvm flutter run
   ```

2. Open DevTools when prompted

3. Check the Logging tab for detailed output

4. Look for any exceptions or errors

## What Should Happen

### Expected Flow:
1. App starts → Shows "DSA Revision" in AppBar
2. Loading indicator appears (spinning wheel)
3. Logs show: "📚 Loading 19 DSA topics from assets..."
4. Each file loads: "✅ Loaded 01_array.md (XXXX chars)"
5. Loading completes: "✅ Successfully loaded 19 topics"
6. Screen shows "Array" title with markdown content
7. Counter shows "1 / 19"
8. Previous button is disabled, Next button is enabled

### If Content Not Visible:
- Check if you see the title "Array" in the AppBar
- Check if you see the counter "1 / 19" at the bottom
- Check if the Previous/Next buttons are visible
- If buttons are visible but no content, the markdown might be rendering as white text on white background

## Color/Theme Issue Check

If the content is there but not visible, it might be a color issue. Try:

1. Enable dark mode on your device
2. Check if text becomes visible
3. If yes, it's a theme/color issue

## Quick Fix: Add Debug Print

If you want to see what's being loaded, you can temporarily add this to `home_screen.dart`:

```dart
// In _loadDSATopics(), after topics are loaded:
print('🔍 DEBUG: Loaded ${topics.length} topics');
if (topics.isNotEmpty) {
  print('🔍 First topic: ${topics[0].title}');
  print('🔍 Content length: ${topics[0].content.length}');
  print('🔍 Content preview: ${topics[0].content.substring(0, 100)}...');
}
```

## Contact Info

If issue persists, provide:
1. Exact error message (if any)
2. Screenshot of the app screen
3. Output of `flutter logs` command
4. Android version of your device

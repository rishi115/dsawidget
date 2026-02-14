package com.example.widgetapp

import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.Context
import android.content.Intent
import android.app.PendingIntent
import android.widget.RemoteViews
import es.antonborri.home_widget.HomeWidgetPlugin

class DSAWidgetProvider : AppWidgetProvider() {
    
    companion object {
        const val ACTION_PREVIOUS = "com.example.widgetapp.ACTION_PREVIOUS"
        const val ACTION_NEXT = "com.example.widgetapp.ACTION_NEXT"
    }
    
    override fun onUpdate(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetIds: IntArray
    ) {
        android.util.Log.d("DSAWidget", "📱 onUpdate called for ${appWidgetIds.size} widgets")
        for (appWidgetId in appWidgetIds) {
            android.util.Log.d("DSAWidget", "   Updating widget ID: $appWidgetId")
            updateAppWidget(context, appWidgetManager, appWidgetId)
        }
    }
    
    override fun onAppWidgetOptionsChanged(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetId: Int,
        newOptions: android.os.Bundle
    ) {
        android.util.Log.d("DSAWidget", "📐 Widget size changed for ID: $appWidgetId")
        
        // Get widget dimensions
        val minWidth = newOptions.getInt(AppWidgetManager.OPTION_APPWIDGET_MIN_WIDTH)
        val maxWidth = newOptions.getInt(AppWidgetManager.OPTION_APPWIDGET_MAX_WIDTH)
        val minHeight = newOptions.getInt(AppWidgetManager.OPTION_APPWIDGET_MIN_HEIGHT)
        val maxHeight = newOptions.getInt(AppWidgetManager.OPTION_APPWIDGET_MAX_HEIGHT)
        
        android.util.Log.d("DSAWidget", "   Width: $minWidth-$maxWidth dp, Height: $minHeight-$maxHeight dp")
        
        // Update widget with new size
        updateAppWidget(context, appWidgetManager, appWidgetId)
        
        super.onAppWidgetOptionsChanged(context, appWidgetManager, appWidgetId, newOptions)
    }
    
    override fun onReceive(context: Context, intent: Intent) {
        super.onReceive(context, intent)
        
        android.util.Log.d("DSAWidget", "🔔 onReceive called with action: ${intent.action}")
        
        when (intent.action) {
            ACTION_PREVIOUS -> {
                android.util.Log.d("DSAWidget", "⬅️ Previous button clicked!")
                navigateTopic(context, -1)
            }
            ACTION_NEXT -> {
                android.util.Log.d("DSAWidget", "➡️ Next button clicked!")
                navigateTopic(context, 1)
            }
            else -> {
                android.util.Log.d("DSAWidget", "❓ Unknown action: ${intent.action}")
            }
        }
    }
    
    private fun navigateTopic(context: Context, direction: Int) {
        android.util.Log.d("DSAWidget", "🔄 navigateTopic called with direction: $direction")
        
        val prefs = context.getSharedPreferences("FlutterSharedPreferences", Context.MODE_PRIVATE)
        
        // Flutter stores as Long, so we need to handle both Int and Long
        val currentIndex = try {
            prefs.getInt("flutter.currentIndex", 0)
        } catch (e: ClassCastException) {
            // If it's stored as Long, get it as Long and convert to Int
            prefs.getLong("flutter.currentIndex", 0L).toInt()
        }
        
        // Get total topics count from cached data
        val totalTopics = try {
            prefs.getInt("flutter.cached_topics_count", 19)
        } catch (e: ClassCastException) {
            prefs.getLong("flutter.cached_topics_count", 19L).toInt()
        }
        
        android.util.Log.d("DSAWidget", "   Current index: $currentIndex")
        android.util.Log.d("DSAWidget", "   Total topics: $totalTopics")
        
        var newIndex = currentIndex + direction
        
        // Ensure index stays within bounds
        if (newIndex < 0) newIndex = 0
        if (newIndex >= totalTopics) newIndex = totalTopics - 1
        
        android.util.Log.d("DSAWidget", "   New index (after bounds check): $newIndex")
        
        // Only update if index actually changed
        if (newIndex != currentIndex) {
            android.util.Log.d("DSAWidget", "   ✅ Index changed! Loading new topic data...")
            
            // Save the new index as Long (Flutter's format)
            prefs.edit().putLong("flutter.currentIndex", newIndex.toLong()).apply()
            
            // Load topic data from cached SharedPreferences
            val title = prefs.getString("flutter.topic_${newIndex}_title", "DSA Topic") ?: "DSA Topic"
            val preview = prefs.getString("flutter.topic_${newIndex}_preview", "Loading...") ?: "Loading..."
            val counter = "${newIndex + 1} / $totalTopics"
            
            android.util.Log.d("DSAWidget", "   📖 Loaded topic: $title")
            android.util.Log.d("DSAWidget", "      Preview: ${preview.take(50)}...")
            android.util.Log.d("DSAWidget", "      Counter: $counter")
            
            // Save to HomeWidget storage for widget display
            val homeWidgetPrefs = context.getSharedPreferences("HomeWidgetPreferences", Context.MODE_PRIVATE)
            val editor = homeWidgetPrefs.edit()
            editor.putString("widget_title", title)
            editor.putString("widget_content", preview)
            editor.putString("widget_counter", counter)
            editor.putInt("widget_total_topics", totalTopics)
            editor.apply()
            
            android.util.Log.d("DSAWidget", "   💾 Data saved to HomeWidget storage")
        } else {
            android.util.Log.d("DSAWidget", "   ⚠️ Index unchanged, skipping update")
        }
        
        // Update the widget
        val appWidgetManager = AppWidgetManager.getInstance(context)
        val appWidgetIds = appWidgetManager.getAppWidgetIds(
            android.content.ComponentName(context, DSAWidgetProvider::class.java)
        )
        
        android.util.Log.d("DSAWidget", "   🔄 Updating ${appWidgetIds.size} widget(s)")
        
        for (appWidgetId in appWidgetIds) {
            updateAppWidget(context, appWidgetManager, appWidgetId)
        }
        
        android.util.Log.d("DSAWidget", "   ✅ Widget update complete!")
    }
    
    private fun updateAppWidget(
        context: Context,
        appWidgetManager: AppWidgetManager,
        appWidgetId: Int
    ) {
        android.util.Log.d("DSAWidget", "🎨 updateAppWidget called for widget ID: $appWidgetId")
        
        // Get widget size options
        val options = appWidgetManager.getAppWidgetOptions(appWidgetId)
        val minHeight = options.getInt(AppWidgetManager.OPTION_APPWIDGET_MIN_HEIGHT, 100)
        val maxHeight = options.getInt(AppWidgetManager.OPTION_APPWIDGET_MAX_HEIGHT, 200)
        val minWidth = options.getInt(AppWidgetManager.OPTION_APPWIDGET_MIN_WIDTH, 100)
        
        android.util.Log.d("DSAWidget", "   📐 Widget size: ${minWidth}x${minHeight} dp")
        
        // Determine widget size category
        val isSmall = minHeight < 120
        val isMedium = minHeight >= 120 && minHeight < 200
        val isLarge = minHeight >= 200
        
        android.util.Log.d("DSAWidget", "   📏 Size category: ${when {
            isSmall -> "Small"
            isMedium -> "Medium"
            isLarge -> "Large"
            else -> "Unknown"
        }}")
        
        // Log ALL SharedPreferences data for debugging
        android.util.Log.d("DSAWidget", "   🔍 Checking FlutterSharedPreferences:")
        val flutterPrefs = context.getSharedPreferences("FlutterSharedPreferences", Context.MODE_PRIVATE)
        val flutterEntries = flutterPrefs.all
        for ((key, value) in flutterEntries) {
            if (key.contains("topic") || key.contains("Index") || key.contains("count")) {
                android.util.Log.d("DSAWidget", "      Flutter: $key = $value")
            }
        }
        
        android.util.Log.d("DSAWidget", "   🔍 Checking HomeWidgetPreferences:")
        val homePrefs = context.getSharedPreferences("HomeWidgetPreferences", Context.MODE_PRIVATE)
        val homeEntries = homePrefs.all
        for ((key, value) in homeEntries) {
            android.util.Log.d("DSAWidget", "      Home: $key = $value")
        }
        
        // Get widget data from HomeWidgetPlugin
        val widgetData = HomeWidgetPlugin.getData(context)
        
        android.util.Log.d("DSAWidget", "   🔍 Checking HomeWidgetPlugin.getData():")
        val allEntries = widgetData.all
        for ((key, value) in allEntries) {
            android.util.Log.d("DSAWidget", "      Plugin: $key = $value")
        }
        
        // Create RemoteViews with the widget layout
        val views = RemoteViews(context.packageName, R.layout.dsa_widget_layout)
        
        // Set up the ListView with RemoteViewsService
        val serviceIntent = Intent(context, DSAWidgetService::class.java)
        views.setRemoteAdapter(R.id.widget_content_list, serviceIntent)
        
        // Set empty view
        views.setEmptyView(R.id.widget_content_list, android.R.id.empty)
        
        // Retrieve widget_title, widget_content, and widget_counter from data
        val title = widgetData.getString("widget_title", "DSA Revision")
        val content = widgetData.getString("widget_content", "Open app to view content")
        val counter = widgetData.getString("widget_counter", "1 / 3")
        
        android.util.Log.d("DSAWidget", "   📝 Final widget data to display:")
        android.util.Log.d("DSAWidget", "      Title: $title")
        android.util.Log.d("DSAWidget", "      Content: ${content?.take(100) ?: "null"}...")
        android.util.Log.d("DSAWidget", "      Content length: ${content?.length ?: 0} chars")
        android.util.Log.d("DSAWidget", "      Counter: $counter")
        
        // Check if content is null or empty
        if (content.isNullOrEmpty()) {
            android.util.Log.e("DSAWidget", "   ⚠️ WARNING: Content is null or empty!")
        }
        
        // Adjust text sizes based on widget height
        val titleSize = when {
            isSmall -> 14f
            isMedium -> 16f
            isLarge -> 18f
            else -> 16f
        }
        
        val contentSize = when {
            isSmall -> 11f
            isMedium -> 13f
            isLarge -> 14f
            else -> 13f
        }
        
        val counterSize = when {
            isSmall -> 11f
            isMedium -> 13f
            isLarge -> 14f
            else -> 13f
        }
        
        android.util.Log.d("DSAWidget", "   🎨 Text sizes: title=${titleSize}sp, content=${contentSize}sp, counter=${counterSize}sp")
        
        // Set text for widget views (title and counter only, content is in ListView)
        views.setTextViewText(R.id.widget_title, title ?: "DSA Revision")
        views.setTextViewText(R.id.widget_counter, counter ?: "1 / 3")
        
        // Set text sizes
        views.setTextViewTextSize(R.id.widget_title, android.util.TypedValue.COMPLEX_UNIT_SP, titleSize)
        views.setTextViewTextSize(R.id.widget_counter, android.util.TypedValue.COMPLEX_UNIT_SP, counterSize)
        
        // Notify ListView to refresh data
        appWidgetManager.notifyAppWidgetViewDataChanged(appWidgetId, R.id.widget_content_list)
        
        android.util.Log.d("DSAWidget", "   ✅ Text set on RemoteViews and ListView notified")
        
        // Create PendingIntent to open MainActivity on title tap
        val openAppIntent = Intent(context, MainActivity::class.java)
        val openAppPendingIntent = PendingIntent.getActivity(
            context,
            0,
            openAppIntent,
            PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
        )
        views.setOnClickPendingIntent(R.id.widget_title, openAppPendingIntent)
        
        // Create PendingIntent for Previous button
        val previousIntent = Intent(context, DSAWidgetProvider::class.java).apply {
            action = ACTION_PREVIOUS
        }
        val previousPendingIntent = PendingIntent.getBroadcast(
            context,
            1,
            previousIntent,
            PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
        )
        views.setOnClickPendingIntent(R.id.widget_button_previous, previousPendingIntent)
        
        android.util.Log.d("DSAWidget", "   🔘 Previous button PendingIntent created")
        
        // Create PendingIntent for Next button
        val nextIntent = Intent(context, DSAWidgetProvider::class.java).apply {
            action = ACTION_NEXT
        }
        val nextPendingIntent = PendingIntent.getBroadcast(
            context,
            2,
            nextIntent,
            PendingIntent.FLAG_UPDATE_CURRENT or PendingIntent.FLAG_IMMUTABLE
        )
        views.setOnClickPendingIntent(R.id.widget_button_next, nextPendingIntent)
        
        android.util.Log.d("DSAWidget", "   🔘 Next button PendingIntent created")
        
        // Update the widget
        appWidgetManager.updateAppWidget(appWidgetId, views)
        
        android.util.Log.d("DSAWidget", "   ✅ Widget UI updated successfully")
    }
}

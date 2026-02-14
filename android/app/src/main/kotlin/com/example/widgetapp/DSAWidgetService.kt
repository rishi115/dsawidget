package com.example.widgetapp

import android.content.Context
import android.content.Intent
import android.widget.RemoteViews
import android.widget.RemoteViewsService

class DSAWidgetService : RemoteViewsService() {
    override fun onGetViewFactory(intent: Intent): RemoteViewsFactory {
        return DSAWidgetRemoteViewsFactory(this.applicationContext, intent)
    }
}

class DSAWidgetRemoteViewsFactory(
    private val context: Context,
    intent: Intent
) : RemoteViewsService.RemoteViewsFactory {

    private var contentLines = mutableListOf<String>()
    private var lineTypes = mutableListOf<Int>() // Track type of each line
    
    companion object {
        const val TYPE_NORMAL = 0
        const val TYPE_HEADER = 1
        const val TYPE_CODE = 2
        const val TYPE_TABLE = 3
        const val TYPE_SEPARATOR = 4
    }

    override fun onCreate() {
        // Initialize
        android.util.Log.d("DSAWidget", "📜 RemoteViewsFactory onCreate")
    }

    override fun onDataSetChanged() {
        // Load content from SharedPreferences
        android.util.Log.d("DSAWidget", "📜 onDataSetChanged called")
        
        val flutterPrefs = context.getSharedPreferences("FlutterSharedPreferences", Context.MODE_PRIVATE)
        val homePrefs = context.getSharedPreferences("HomeWidgetPreferences", Context.MODE_PRIVATE)
        
        // Get current index
        val currentIndex = try {
            flutterPrefs.getInt("flutter.currentIndex", 0)
        } catch (e: ClassCastException) {
            flutterPrefs.getLong("flutter.currentIndex", 0L).toInt()
        }
        
        android.util.Log.d("DSAWidget", "   Current index: $currentIndex")
        
        // Get full content from cached topic
        val fullContent = flutterPrefs.getString("flutter.topic_${currentIndex}_preview", null)
        
        android.util.Log.d("DSAWidget", "   Full content length: ${fullContent?.length ?: 0}")
        
        if (fullContent != null && fullContent.isNotEmpty()) {
            // Split content into lines
            val lines = fullContent.split("\n").toMutableList()
            
            contentLines.clear()
            lineTypes.clear()
            
            var inCodeBlock = false
            
            for (line in lines) {
                // Skip completely empty lines
                if (line.isBlank()) continue
                
                // Detect line type and add with appropriate styling
                when {
                    line.contains("━━━ CODE ━━━") || line.contains("━━━━━━━━━━━━") -> {
                        contentLines.add(line)
                        lineTypes.add(TYPE_SEPARATOR)
                        inCodeBlock = !inCodeBlock
                    }
                    inCodeBlock -> {
                        contentLines.add(line)
                        lineTypes.add(TYPE_CODE)
                    }
                    line.startsWith("▸") -> {
                        contentLines.add(line.replace("▸", "").trim())
                        lineTypes.add(TYPE_HEADER)
                    }
                    line.contains("│") -> {
                        contentLines.add(line)
                        lineTypes.add(TYPE_TABLE)
                    }
                    else -> {
                        contentLines.add(line)
                        lineTypes.add(TYPE_NORMAL)
                    }
                }
            }
            
            android.util.Log.d("DSAWidget", "   ✅ Loaded ${contentLines.size} lines")
            
            // Log first few lines for debugging
            contentLines.take(3).forEachIndexed { index, line ->
                android.util.Log.d("DSAWidget", "      Line $index (type ${lineTypes[index]}): ${line.take(50)}...")
            }
        } else {
            android.util.Log.e("DSAWidget", "   ❌ No content found!")
            contentLines = mutableListOf("No content available", "Please open the app first")
            lineTypes = mutableListOf(TYPE_NORMAL, TYPE_NORMAL)
        }
    }

    override fun onDestroy() {
        contentLines.clear()
        lineTypes.clear()
    }

    override fun getCount(): Int {
        val count = contentLines.size
        android.util.Log.d("DSAWidget", "📜 getCount: $count")
        return count
    }

    override fun getViewAt(position: Int): RemoteViews {
        android.util.Log.d("DSAWidget", "📜 getViewAt: $position / ${contentLines.size}")
        
        if (position >= contentLines.size) {
            val views = RemoteViews(context.packageName, R.layout.widget_list_item)
            views.setTextViewText(R.id.widget_list_item_text, "")
            android.util.Log.w("DSAWidget", "   ⚠️ Position out of bounds!")
            return views
        }
        
        val line = contentLines[position]
        val type = lineTypes[position]
        
        // Choose layout based on line type
        val layoutId = when (type) {
            TYPE_HEADER -> R.layout.widget_list_item_header
            TYPE_CODE -> R.layout.widget_list_item_code
            TYPE_TABLE -> R.layout.widget_list_item_table
            TYPE_SEPARATOR -> R.layout.widget_list_item_separator
            else -> R.layout.widget_list_item
        }
        
        val views = RemoteViews(context.packageName, layoutId)
        views.setTextViewText(R.id.widget_list_item_text, line)
        
        android.util.Log.d("DSAWidget", "   ✅ Set text (type=$type, ${line.length} chars): ${line.take(50)}...")
        
        return views
    }

    override fun getLoadingView(): RemoteViews? {
        return null
    }

    override fun getViewTypeCount(): Int {
        return 5 // We have 5 different view types
    }

    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    override fun hasStableIds(): Boolean {
        return true
    }
}

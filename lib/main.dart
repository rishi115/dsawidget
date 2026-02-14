import 'package:flutter/material.dart';
import 'package:home_widget/home_widget.dart';
import 'screens/home_screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  // ignore: deprecated_member_use
  await HomeWidget.registerBackgroundCallback(backgroundCallback);
  runApp(const DSARevisionApp());
}

/// Background callback for HomeWidget interactions
/// This function is called when the widget needs to handle background updates
@pragma('vm:entry-point')
void backgroundCallback(Uri? uri) {
  // Handle widget taps or other interactions
  // Currently not used, but required by home_widget package
}

class DSARevisionApp extends StatelessWidget {
  const DSARevisionApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'DSA Revision',
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(
          seedColor: Colors.deepPurple,
          brightness: Brightness.light,
        ),
      ),
      darkTheme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(
          seedColor: Colors.deepPurple,
          brightness: Brightness.dark,
        ),
      ),
      themeMode: ThemeMode.system,
      home: const HomeScreen(),
    );
  }
}

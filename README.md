# Secure Incident Reporter

A simple C++ console application that helps citizens securely log incidents, optionally upload media files, and store reports safely on disk.

## 🔒 Features
- Unique Report ID & Timestamp
- Optional anonymous reporting
- Media file path support
- Category selection with validation
- View previous reports
- Admin-only deletion of all reports

## 🛠 Build & Run

### Compile
```bash
g++ main.cpp incident_reporter.cpp -o reporter

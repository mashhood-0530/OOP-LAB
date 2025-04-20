#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

/*
    Logger class - Centralized logging service that:
    - Stores logs internally with severity levels
    - Enforces maximum log capacity
    - Provides secure read-only access to authenticated auditors
*/
class Logger {
private:
    vector<string> logs;               // Internal log storage (private)
    const size_t MAX_LOG_COUNT = 1000; // Hard limit for stored logs

    /*
        Private helper method that handles:
        - Log formatting with severity prefix
        - Enforces maximum log count by removing oldest entries
    */
    void addLog(const string& severity, const string& message) {
        string formattedLog = "[" + severity + "] " + message;
        
        // Remove oldest log if we've reached capacity
        if (logs.size() >= MAX_LOG_COUNT) {
            logs.erase(logs.begin());
        }
        
        logs.push_back(formattedLog);
    }

public:
    /*
        Public logging interface - three severity levels
        Each forwards to the private addLog() method
    */
    void logInfo(const string& message) {
        addLog("INFO", message);
    }

    void logWarning(const string& message) {
        addLog("WARN", message);
    }

    void logError(const string& message) {
        addLog("ERROR", message);
    }

    /*
        Secure log access method:
        - Only returns logs if auditor is authenticated
        - Returns const reference to prevent modification
        - Throws exception if unauthorized access attempted
    */
    const vector<string>& getLogs(bool isAuthenticated) const {
        if (!isAuthenticated) {
            throw runtime_error("Access denied: Authentication required");
        }
        return logs;
    }
};

/*
    Auditor class - demonstrates secure log retrieval
    Shows how to properly access logs through the Logger interface
*/
class Auditor {
public:
    void auditLogs(const Logger& logger, bool hasAccess) {
        try {
            cout << "\n=== AUDIT ATTEMPT ===" << endl;
            const auto& logs = logger.getLogs(hasAccess);
            
            cout << "Success! Retrieved " << logs.size() << " logs:" << endl;
            for (const auto& log : logs) {
                cout << log << endl;
            }
        } catch (const exception& e) {
            cerr << "Audit failed: " << e.what() << endl;
        }
    }
};

/*
    Simulated system modules that generate logs
    Demonstrates how different parts of a system would use the logger
*/
class NetworkModule {
private:
    Logger& logger;
    
public:
    NetworkModule(Logger& logService) : logger(logService) {}
    
    void connect() {
        logger.logInfo("Network: Connection established");
    }
    
    void timeout() {
        logger.logWarning("Network: Connection timeout");
    }
};

class DatabaseModule {
private:
    Logger& logger;
    
public:
    DatabaseModule(Logger& logService) : logger(logService) {}
    
    void query() {
        logger.logInfo("Database: Executed query");
    }
    
    void fail() {
        logger.logError("Database: Connection failed!");
    }
};

int main() {
    // Create centralized logger
    Logger systemLogger;
    
    // Simulate different system modules using the logger
    NetworkModule network(systemLogger);
    DatabaseModule database(systemLogger);
    
    // Generate test logs
    network.connect();
    database.query();
    network.timeout();
    database.fail();
    
    // Stress test by exceeding log limit
    cout << "\nGenerating 1005 logs to test limit enforcement..." << endl;
    for (int i = 0; i < 1005; i++) {
        systemLogger.logInfo("System: Maintenance check #" + to_string(i));
    }
    
    // Demonstrate audit functionality
    Auditor securityAuditor;
    
    // Attempt unauthorized access (should fail)
    securityAuditor.auditLogs(systemLogger, false);
    
    // Attempt authorized access (should succeed)
    securityAuditor.auditLogs(systemLogger, true);
    
    return 0;
}